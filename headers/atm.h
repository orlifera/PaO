#pragma once
#include "pressure.h"
class AtmPressureSensor : public PressureSensor {
    private:
    static double atmThreshold;
    public:
    AtmPressureSensor(string, vector<Data>);
    int isInThreshold() const override;
};