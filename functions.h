#ifndef FUCNTIONS.H
#define FUNCTIONS.H

#include<iostream>
#include<string>
#include<vector>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ostream;

class Time {
    private:
    unsigned int sec;
    public:
    Time(unsigned int =0, unsigned int =0, unsigned int =0);
    unsigned int Hour() const;
    unsigned int Mins() const;
    unsigned int Secs() const;
    //operator int();
};

class Data {
    private:
    double value;
    Time time;
    public:
    //Si potrebbe fare in modo che una funzione
    //generi randomicamente o secondo una distribuzione
    //il valore da assegnare al dato.
    Data(double, Time);
    double getValue() const;
    Time getTime() const;
};

class Sensor {
    private:
    string name;
    vector<Data> infoArray;
    public:
    //Da controllare il costruttore e costruttore di copia.
    Sensor(string, vector<Data>);
    Data getInfo(int) const;
    string getName() const;
    vector<Data> getArray() const;
    void addData(Data);
    void removeData();
    void renameSensor(string);
    virtual int isInThreshold() const = 0;
    virtual ~Sensor() = default;
};

class TemperatureSensor : public Sensor {
    private:
    const bool contact; //chiedere
    double temp;
    public: 
    TemperatureSensor(string, vector<Data>, bool, double);
    bool isContact() const;
    double getTemp() const;
    void setTemp(double); 
};

class VinesTemperatureSensor : public TemperatureSensor {
    private:
    static double vineThreshold;
    public:
    VinesTemperatureSensor(string, vector<Data>, double);
    int isInThreshold() const override;
};

class MustTemperatureSensor : public TemperatureSensor {
    private:
    static double mustThreshold;
    public:
    MustTemperatureSensor(string, vector<Data>, double);
    int isInThreshold() const override;
};

class HumiditySensor : public Sensor {
    private:
    const bool capacity;
    double humidity;
    public:
    HumiditySensor(string, vector<Data>, bool, double);
    bool isCapacity() const;
    double getHumidity() const;
    void setHumidity(double);
};

class AirHumiditySensor : public HumiditySensor {
    private:
    static double airThreshold;
    public:
    AirHumiditySensor(string, vector<Data>, double);
    int isInThreshold() const override;
};

class SoilHumiditySensor : public HumiditySensor {
    private:
    static double soilThreshold;
    public:
    SoilHumiditySensor(string, vector<Data>, double);
    int isInThreshold() const override;
};

class PressureSensor : public Sensor {
    private:
    double pressure;
    public:
    PressureSensor(string, vector<Data>, double);
    double getPressure() const;
    void setPressure(double);
};

class AtmPressureSensor : public PressureSensor {
    private:
    static double atmThreshold;
    public:
    AtmPressureSensor(string, vector<Data>);
    int isInThreshold() const override;
};

class BarrelSensor : public PressureSensor {
    private:
    static double barrelThreshold;
    public:
    int isInThreshold() const override;
};

class Group {
    private:
    string groupName;
    vector<Sensor*> sensors;
    public:
    Group(string, vector<Sensor*>);
    string getGroupName() const;
    vector<Sensor*> getSensors() const;
    void addSensor(Sensor*);
    void removeSensor();
    Sensor* find(string) const;
    void renameGroup(string);
    //Group& operator=(const Group&);
};

#endif