
#include "IHM.h"



IHM::IHM () : type(COURT),sucre(false),qualite(NORMALE){}
void IHM::SetSucre(){
    sucre = !sucre;
}
void IHM::SetType() {
    if (type == LONG)
        type = COURT;
    else
        type = LONG;
}
