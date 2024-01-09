#pragma once
#include "pressure.h"
class BarrelSensor : public PressureSensor {
    private:
    static double barrelThreshold;
    public:
    int isInThreshold() const override;
};