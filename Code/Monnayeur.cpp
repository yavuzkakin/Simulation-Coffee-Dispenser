
#include "Monnayeur.h"


Monnayeur ::Monnayeur () : somme(0){}
void Monnayeur::CalculRendu(IHM * choix) {
    float prix = (choix->GetQualite() == NORMALE) ? 1.5 : 2;
    cout << "La machine rend: " << somme - prix << "\n";
    somme = 0;
}
