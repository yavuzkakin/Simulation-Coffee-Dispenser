#pragma once

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
#include "enum.h"


class Sucre { // Similaire a gobelets
public:
    Sucre() : quantite(1) {}
    void verse() { quantite -= 1; }
    void approvisionner(int quan) { quantite += quan; }
    int GetQuantite() { return quantite; }   
private:
    int quantite;
};
