#include "functions.h"

void saveWithName(const Group& group, const string& filename) {
    json jsonData;
    //opens file "filename" and checks it there is data in it
    ifstream inFile(filename);
    if (inFile.is_open()) {
        //puts data in variable jsonData
        inFile >> jsonData;
        inFile.close();
    }
    //creates a group
    json newGroup;
    //gets the name
    newGroup["name"] = group.getGroupName();
    //creates an array of sensors
    json sensorsArray;
    //for each sensor
    for (const auto& sensor: group.getSensors()) {
        //create a data
        json sensorData;
        //gets sensor's name
        sensorData["name"] = sensor->getName();
        //creates an infoArray
        json infoArray;
        //for each data in infoArray
        for (const auto& data: sensor.getArray()) {
            //creates a infoData
            json infoData;
            //gets info's time
            infoData["time"] = data.getTime();
            //gets info's value
            infoData["value"] = data.getValue();
            //pushes the data in the array
            infoArray.push_back(infoData);
        }
        //assigns infoArray as sensor's info
        sensorData["info"] = infoArray;
        //pushes sensor in the sensorsArray
        sensorsArray.push_back(sensorData);
    }
    //assigns sensorsArray to the group's sensors
    newGroup["sensors"] = sensorsArray;
    //pushes the group in the jsonData
    jsonData.push_back(newGroup);
    //new file "filename"
    ofstream outFile(filename);
    //insert data in file with indentation
    outFile << setw(4) << jsonData << endl;
}