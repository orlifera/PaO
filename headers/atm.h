#pragma once
#include "pressure.h"
class AtmPressureSensor : public PressureSensor {
    public:
    AtmPressureSensor(string, vector<Data>, double =0);
};