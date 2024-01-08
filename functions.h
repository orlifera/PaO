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

class Data {
    private:
    double value;
    string date;
    public:
    //Si potrebbe fare in modo che una funzione
    //generi randomicamente o secondo una distribuzione
    //il valore da assegnare al dato.
    Data(double, string);
    double getValue() const;
    string getDate() const;
};

class Sensor {
    private:
    string name;
    vector<Data> infoArray;
    public:
    //Da controllare il costruttore e costruttore di copia.
    Sensor(string, vector<Data>);
    Sensor(const Sensor&);
    Data getInfo(int) const;
    string getName() const;
    vector<Data> getArray() const;
    void addData(Data, int);
    void removeData(Data, int);
    virtual int isInThreshold() const = 0;
    virtual ~Sensor() = 0;
};

class TemperatureSensor : public Sensor {
    private:
    const bool contact; //chiedere
    double temp;
    public: 
    TemperatureSensor(string, vector<Data>, bool, double);
    TemperatureSensor(const TemperatureSensor&);
    bool isContact() const;
    double getTemp() const;
    void setTemp(double); 
};

class VinesTemperatureSensor : public TemperatureSensor {
    private:
    static double vineThreshold;
    public:
    VinesTemperatureSensor(string, vector<Data>);
    int isInThreshold() const override;
};

double VinesTemperatureSensor::vineThreshold = 0;

class WineryTemperatureSensor : public TemperatureSensor {
    private:
    static double wineryThreshold;
    public:
    WineryTemperatureSensor(string, vector<Data>);
    int isInThreshold() const override;
};

double VinesTemperatureSensor::wineryThreshold = 0;

class MustTemperatureSensor : public TemperatureSensor {
    private:
    static double mustThreshold;
    public:
    MustTemperatureSensor(string, vector<Data>);
    int isInThreshold() const override;
};

double VinesTemperatureSensor::mustThreshold = 0;

class HumiditySensor : public Sensor {
    private:
    const bool capacity;
    double humidity;
    public:
    HumiditySensor(string, vector<Data>, bool);
    HumiditySensor(const HumiditySensor&);
    bool isCapacity() const;
    double getHumidity() const;
    void setHumidity(double);
    virtual bool isInHumidity(Data) const = 0;
};

class AirHumiditySensor : public HumiditySensor {
    public:
    AirHumiditySensor(string, vector<Data>);
    bool isInHumidity(Data) override const;
};

class SoilHumiditySensor : public HumiditySensor {
    public:
    SoilHumiditySensor(string, vector<Data>);
    bool isInHumidity(Data) override const;
};

class PressureSensor : public Sensor {
    private:
    double pressure;
    public:
    double getPressure() const;
    void setPressure(double);
    virtual bool isInPressure(Data) const = 0;
};

class AtmPressureSensor : public PressureSensor {
    public:
    AtmPressureSensor(string, vector<Data>);
    bool isInPressure(Data) override const;
};

class BarrelSensor : public PressureSensor {
    public:
    BarrelSensor(string, vector<Data>);
    bool isInPressure(Data) override const;
};

class Group {
    private:
    string groupName;
    vector<Sensor*> sensors;
    public:
    Group(string, vector<Sensor*>);
    Group(const Group&);
    string getGroupName() const;
    vector<Sensor*> getSensors() const;
    void addSensor(Sensor*, int);
    void removeSensor(Sensor*, int);
    Sensor find(string) const;
    void rename(string);
    Group& operator=();
    ~Group();
};

#endif