#pragma once

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
#include "enum.h"
#include "Cafe.h"

class Luxe : public Cafe { 
public:
    Luxe(Type t, bool sucre) : Cafe(t,sucre,LUXE) {}
    virtual void f() { cout <<"0"; } // Pour rendre Luxe non abstraite
};
