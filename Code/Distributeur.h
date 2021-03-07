#pragma once

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
#include "enum.h"
#include "Monnayeur.h"
#include "IHM.h"
#include "Controleur.h"
#include "Cafe.h"
#include "Sucre.h"
#include "Gobelets.h"



class Distributeur {
    Gobelets* gobelets;
    Sucre* sucre;
    Controleur* control;
    IHM* ihm;
    Monnayeur* monnayeur;
    int Id;
public:  
    ~Distributeur();
    Distributeur(int);
    int GetGobelets() { return gobelets->GetQuantite(); }; // Renvoie la quantite de gobelets restantes, pour voir si on peut produire
    void Programme();
};
