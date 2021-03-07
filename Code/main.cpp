
#include "Distributeur.h"


int main()
{
    Distributeur D(411); // 411 est l'ID du distributeur
    /*D.~Distributeur();
    cout << "test\n";*/
    while (D.GetGobelets()>0)  //tant qu'on a des gobelets les utilisateurs peuvent commander
    D.Programme();
    cout << "\nIl n'y a plus de gobelets, le responsable maintenance va s'en charger\n";
}

