#pragma once

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
#include "enum.h"

class Cafe {
public:
    virtual void f() = 0; // Pour que la classe soit virtuelle
    Cafe(Type t, bool s, Qualite q);
private:
    Type type;
    bool sucre;
    Qualite qualite;
    float prix;
};
