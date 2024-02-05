#pragma once
#include "include.h"

class Item {
    public:
    virtual void save(string) const =0;
    virtual void load() const =0;
    virtual void rename(string) =0;
};