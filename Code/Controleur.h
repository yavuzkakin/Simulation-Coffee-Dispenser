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
#include "Monnayeur.h"
#include "IHM.h"
#include "Luxe.h"
#include "Normale.h"


class Controleur {
    IHM* ihm;
    Monnayeur* monnayeur;
    Cafe* cafe;
public:
    Controleur(IHM* ihm, Monnayeur* monnayeur);
    ~Controleur();
    /*********************************************** On entre dans les details de chaque fonction ***********************************************/
    void AfficherOptions(); // Affiche les options et permet de personaliser le cafe, on peut egalement entrer en mode admin

    void Payer(); // Traite la somme a payer et l'argent a rendre

    void DispenseProduit(); // creer et dispense le produit 
};
