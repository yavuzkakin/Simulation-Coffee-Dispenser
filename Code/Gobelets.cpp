
#include "Gobelets.h"

Gobelets::Gobelets() : quantite (5) {}
void Gobelets::sert() { quantite--; }
void Gobelets::approvisionner(int quan) { quantite += quan; }
