#pragma once
#include "group.h"
//function that saves a group
//if called for the first time creates a file
//otherwise it just creates a new one
void saveWithName(const Group&, const string&);
//void saveScreen();