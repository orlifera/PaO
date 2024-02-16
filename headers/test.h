class AirHumiditySensor : public HumiditySensor
{
private:
    static double alpha; // parametro per la distribuzione beta
    static double beta;  // parametro per la distribuzione beta
public:
    AirHumiditySensor(string, double, double = 0);
    void generate();
    // funzione statica che crea distribuzione beta
    static double beta_distribution(double, double, default_random_engine &);
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};

class AtmPressureSensor : public PressureSensor
{
private:
    static double stdDeviation; // deviazione standard
    static double meanPoisson;  // numero medio di eventi improvvisi per unità di tempo
public:
    AtmPressureSensor(string, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};
class BarrelPressureSensor : public PressureSensor
{
private:
    static double stdDeviation; // deviazione standard
public:
    BarrelPressureSensor(string, double, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};

class BodyWidget : public QWidget
{
    Q_OBJECT;

private:
    Tab *tab;                 // puntatore alla tab che contiene questo body
    QWidget *left;            // puntatore alla parte sinistra contenuta in body
    QListWidget *listWidget;  // puntatore alla lista di widget nella parte sinistra
    QWidget *right;           // puntatore alla parte destra contenuta nel body
    QVBoxLayout *rightlayout; // puntatore al layout della parte sinistra

public:
    BodyWidget(Tab *, QWidget *parent = 0);
    // creazione di left
    void createLeft();
    // creazione di right
    void createRight(Sensor *);
    // funzione di filtraggio per la ricerca di sensori nella listWidget
    void filterList(const QString &);
    // funzione di creazione dei bottoni nella listWidget e il loro collegamento a right
    void connection(Sensor *);
    // refresh di tutto il body per aggiornare i cambiamenti avvenuti
    void refresh();
    // creazione del chart del sensore
    QWidget *createChart(Sensor *);
private slots:
    // creazione nuovo sensore
    void newSensor();
    // caricamento nuovo sensore
    void loadSensor();
    // effettivo collegamento tra il bottone in listWidget e la creazione di right
    void viewRight(Sensor *);
    // generazione dati
    void generate(Sensor *);
    // salvataggio del singolo sensore puntato
    void saveSensor(Sensor *);
    // eliminazione del sensore dal gruppo selezionato (non elimina file salvati)
    void deleteSensor(Sensor *);
    // modifica dinamica del sensore
    void modifySensor(Sensor *, SensorInfo *);
};

class Data
{
private:
    double value; // valore dato
    Time time;    // orario nella quale viene misurato
public:
    Data(double = 0.0, Time = 0);
    // ritorna il valore del dato
    double getValue() const;
    // assegna un nuovo valore (misurazione)
    void setValue(double);
    // ritorna l'orario  in secondi come stringa
    int getTime() const;
    // assegna l'orario
    void setTime(unsigned int = 0, unsigned int = 0, unsigned int = 0);
};

class Group
{
private:
    string groupName;         // nome del gruppo
    vector<Sensor *> sensors; // vettore di puntatori ai sensori contenuti nel gruppo

public:
    Group(string);
    // ritorna il nome del gruppo
    string getGroupName() const;
    // ritorna il vettore dei puntatori ai sensori
    vector<Sensor *> getSensors() const;
    // aggiunge un sensore
    void addSensor(Sensor *);
    // rimuove un sensore
    void removeSensor(Sensor *);
    // rimuove un sensore dato il nome
    void removeSensor(string);
    // rimuove un senore data la posizione
    void removeSensor(int);
    // trova un sensore dal nome
    bool find(string) const;
    // rinomina gruppo
    void rename(string);
    // salva gruppo
    void save(string) const;
    // carica grupppo
    static Group *load(string);
    // carica sensore nel gruppo
    Sensor *loadSensor(string);
    // crea nuovo sensore nel gruppo
    Sensor *newSensor(string, double, double, string);
};
class HeadWidget : public QWidget
{
    Q_OBJECT;

private:
    Tab *tab;               // puntatore alla tab che contiene l'head
    QLabel *title;          // puntatore al titolo del gruppo
    QPushButton *saveBtn;   // puntatore al bottone di salvataggio del gruppo
    QPushButton *renameBtn; // puntatore al bottone di modifica del gruppo
    QPushButton *deleteBtn; // puntatore al bottone di eliminazione del gruppo

public:
    HeadWidget(QString, Tab *, QWidget *parent = 0);
    // refresh dell'intero head
    void refresh(QString);
};

class HumiditySensor : public Sensor
{
private:
    const bool capacity; // tipologia di sensore (costante e definito alla creazione)
public:
    HumiditySensor(string, bool, double, double);
    // check se sensore è capacitativo o meno
    bool isCapacity() const;
    string getIcon() const;
    string getUnit() const;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT;

private:
    QTabWidget *tabs; // puntatore al widget che gestisce le tabs
    QLabel *welcome;  // label di benvenuto inizale
    bool checked;     // attributo booleano per la chiusura delle tabs

public:
    MainWindow(QWidget *parent = 0);
    // impone la visione o meno della label di benvenuto in base alla presenza di tabs
    void firstView();
private slots:
    // apre un gruppo salvato
    void openGroup();
    // crea un nuovo gruppo
    void newGroup();
    // chiude l'app
    void closeApp();
    // gestione della chiusura di una tab
    void closeTab(int);
};

class MustTemperatureSensor : public TemperatureSensor
{
private:
    static double timer; // timer di fermentazione
    static double range; // deviazione standard
public:
    MustTemperatureSensor(string, double, double);
    void generate();
    // ritorna il valore del timer
    double getTimer() const;
    // imposta il valore del timer
    void setTimer(double);
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};

class PressureSensor : public Sensor
{
public:
    PressureSensor(string, double, double);
    string getIcon() const;
    string getUnit() const;
};

class Sensor
{
private:
    string name;            // nome del sensore
    vector<Data> infoArray; // valori effettivi - dati misurati
    double expectedValue;   // valore atteso dallo specifico sensore
    double threshold;       // soglia

public:
    Sensor(string, double, double);
    // ritorna dato fornendo la posizione
    Data getInfo(int) const;
    // ritorna stringa con il nome dell'icona differenziato per tipologia di sensore
    virtual string getIcon() const = 0;
    // ritorna stringa con unità di misura per tipologia di sensore
    virtual string getUnit() const = 0;
    // ritorna nome
    string getName() const;
    // ritorna il vettore dati
    vector<Data> getArray() const;
    // reset del vettore dei dati
    void clear();
    // ritorna il valore atteso
    double getExpValue() const;
    // ritorna la soglia
    double getThreshold() const;
    // assegna nuovo valore atteso
    void setExpValue(double);
    // assegna nuova soglia
    void setThreshold(double);
    // metodo astratto per la generazione dei dati
    virtual void generate() = 0;
    // rinomina il sensore
    void rename(string);
    // controlla che l'ultimo dato del sensore sia all'interno della soglia
    int isInThreshold() const;
    // permette il push di un Data in infoArray (privato)
    void push(Data &);
    // permette il push di un vettore di dati ovvero l'assegnazione
    void push(vector<Data>);
    // ritorna il nome della classe e caratteristiche specifiche del sensore polimorficamente
    virtual QJsonObject classSensor() const = 0;
    // scrive su un oggetto json le caratteristiche del sensore
    QJsonObject writeSensor() const;
    // salva sensore
    void save(string) const;
    // carica sensore
    static Sensor *load(string);
    // crea nuovo sensore
    static Sensor *newSensor(string, double, double, string);
    // accettazione del visitor per polimorfismo nella GUI
    virtual void accept(SensorVisitor &) = 0;
    // distruttore di default virtuale
    virtual ~Sensor() = default;
};

class SensorInfo : public SensorVisitor
{
private:
    QWidget *widget; // puntatore ad un widget contenitore di informazioni sui sensori
    bool ismust;     // attributo booleano per individuare un sensore di temperatura del mosto

public:
    // ritorna il widget
    QWidget *getWidget();
    void visitAir();
    void visitAtm();
    void visitBarrel();
    void visitMust(MustTemperatureSensor &);
    void visitSoil();
    void visitVines();
    void visitWinery();
    // ritorna il valore booleano
    bool isMust();
};

class SensorVisitor
{
public:
    // funzioni per visitare ogni sottoclasse concreta di sensore
    virtual void visitAir() = 0;
    virtual void visitAtm() = 0;
    virtual void visitBarrel() = 0;
    virtual void visitMust(MustTemperatureSensor &) = 0;
    virtual void visitSoil() = 0;
    virtual void visitVines() = 0;
    virtual void visitWinery() = 0;
    // distruttore virtuale
    virtual ~SensorVisitor() = default;
};

class SoilHumiditySensor : public HumiditySensor
{
private:
    static double logStdDeviation; // logaritmo della deviazione standard
public:
    SoilHumiditySensor(string, double, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};

class Tab : public QWidget
{

    Q_OBJECT;

private:
    HeadWidget *head; // puntatore all'intestazione contenuta nella tab
    BodyWidget *body; // puntatore al corpo della tab
    QTabWidget *tabs; // puntatore al tabwidget che contiene la tab
    string path;      // path di salvataggio del gruppo associato alla tab
    Group *group;     // gruppo associato alla tab

public:
    Tab(Group *, QTabWidget *, string = "", QWidget *parent = 0);
    // ritorna il vettore dei puntatori a sensore del gruppo associato alla tab
    vector<Sensor *> getVector() const;
    // ritorna il puntatore al gruppo
    Group *getGroup() const;
public slots:
    // salvataggio del gruppo
    void save();
    // modifica del gruppo
    void rename();
    // eliminazione del gruppo
    void deleteGroup();
};

class TemperatureSensor : public Sensor
{
private:
    const bool contact; // tipologia di sensore di temperatura (costante e definito alla creazione)
public:
    TemperatureSensor(string, bool, double, double);
    // check se il sensore è a contatto o meno
    bool isContact() const;
    string getIcon() const;
    string getUnit() const;
};

class Time
{
private:
    unsigned int sec;

public:
    Time(unsigned int = 0, unsigned int = 0, unsigned int = 0);
    // ritorna le ore
    unsigned int Hour() const;
    // ritorna i minuti
    unsigned int Mins() const;
    // ritorna i secondi
    unsigned int Secs() const;
    // ritorna una stringa con l'orario
    unsigned int getTime() const;
    // setting del time come costruttore alternativo
    void setTime(unsigned int);
};

class VinesTemperatureSensor : public TemperatureSensor
{
private:
    static double stdDeviation; // deviazione standard
    static double amplitude;    // ampiezza per la distribuzione sinusoidale
public:
    VinesTemperatureSensor(string, double, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};

class WineryTemperatureSensor : public TemperatureSensor
{
private:
    static double range; // deviazione standard
public:
    WineryTemperatureSensor(string, double, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};