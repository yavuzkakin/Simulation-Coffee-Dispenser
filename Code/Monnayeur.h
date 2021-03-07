#pragma once

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
#include "enum.h"
#include "IHM.h"


class Monnayeur {
public:
    Monnayeur();
    void AjoutePiece(float piece) { somme += piece; } //On accumule les pieces pour payer un cafe
    float GetSomme() { return somme; } // Fetch la somme accumule
    void CalculRendu(IHM* choix); // Calcul l'argent a rendre et rend se qu'il faut, ensuite elle remet la somme a 0
private:
    float somme;
};
