#pragma once

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
#include "enum.h"


class IHM {
public:
    IHM();
    void SetType(); //Choisir Court ou Long 
    void SetLuxe() { qualite = LUXE; } // Choisir Luxe
    void SetNormale() { qualite = NORMALE; } // Choisir Normale
    void SetSucre(); // Choisir si on veut du sucre ou pas
    Type GetType() { return type; } // Fetch court ou long
    Qualite GetQualite() { return qualite; } // Fetch qualite
    bool GetSucre() { return sucre; } // Fetch sucre
private:
    Type type;
    Qualite qualite;
    bool sucre;
};

