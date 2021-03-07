
#include "Cafe.h"

Cafe::Cafe(Type t, bool s, Qualite q) : type(t), sucre(s), qualite(q) {
    prix = (qualite == NORMALE) ? (float)1.5 : (float)2;
}
