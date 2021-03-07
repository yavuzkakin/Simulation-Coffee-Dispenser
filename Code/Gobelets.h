#pragma once

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
#include "enum.h"


class Gobelets {
public:    
    Gobelets();
    int GetQuantite() { return quantite; } //Renvoie la quantite de gobelets restante
    void sert(); // Enleve 1 gobelets du stock
    void approvisionner(int quan); // Permet a l'administrateur de reapprovisionner en gobelets
private :
    int quantite;
};
