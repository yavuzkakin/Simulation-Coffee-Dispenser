
#include "Controleur.h"

Controleur::Controleur(IHM*ihm,Monnayeur*monnayeur) : ihm(ihm),monnayeur(monnayeur) {}
Controleur::~Controleur()  {
    delete cafe; // le destructeur de distributeur s'en occupe d'ihm et de monnayeur
}
void Controleur::AfficherOptions(){ 
    int bouton_qual = 0;
    while (bouton_qual == 0) { // On passe au payement des que la qualite est choisit
        cout << "\nAppuyez sur 0 pour le sucre, appuyez sur 1 pour du cafe long : \n" 
            << "Ensuite appuez sur 2 ou 3 pour choisir respectivement luxe ou normale et lancer la production\n\n";
        int choix;
        cin >> choix;
        switch (choix) {
        case 0:
            ihm -> SetSucre();
            cout << "Votre cafe contient " << ihm->GetSucre() << " sucre\n";
            break; 
        case 1:
            ihm ->SetType();
            if (ihm->GetType())
                cout << "Vous avez choisi un cafe long\n\n";
            else
                cout << "Vous avez choisi un cafe court\n\n";
            break; 
        case 2:
            ihm->SetLuxe();
            cout << "Vous avez choisi un cafe luxe\n\n";
            bouton_qual = 1; // On passe au payement
            break;
        case 3 :
            ihm->SetNormale();
            cout << "Vous avez choisi un cafe normale\n\n";
            bouton_qual = 1; // On passe au payement
            break;
        default: 
            cout << "demande non comprise, choisissez une autre option\n";
            break;
            
        }
    }
}

void Controleur::Payer() {
    float prix = (ihm->GetQualite() == NORMALE) ? (float)1.5 : (float)2; // On choisit le prix selon la qualite
    float choix;
    while (monnayeur->GetSomme() < prix) { // Tant que la somme verser est inferieure au prix du cafe on ne lance pas la production
        // Le monnayeur n'accepte plus de pieces si la somme cumulee depasse 2 euros
        cout << "Inserer votre monnaies, les seules pieces acceptees sont 0.5, 1 ou 2 euros : \n";        
        cin >> choix;
        
        if ((choix == (float)0.5) || (choix == (float)1) || (choix == (float)2)) { // piece acceptees
            monnayeur->AjoutePiece(choix);
            cout << "vous avec inserer au total: " << monnayeur->GetSomme()<<"\n\n"; 
           
        }
        else if ((choix == (float)0.05) || (choix == (float)0.01) || (choix == (float)0.02) || (choix == (float)0.1) || (choix == (float)0.2)) {
            //pieces non acceptes et automatiquement rendues
            cout << "vous avec inserer au total: " << monnayeur->GetSomme() << "\n\n";
            cout << "La machine rend : " << choix << "\n\n";
        }
        else
            cout << "Cette piece n'existe pas \n\n"; // vous etes tres malin
    }   
    monnayeur->CalculRendu(ihm); // On rend le surplus
}

void Controleur::DispenseProduit() { 
    // On cree la classe cafe selon la qualite
    if (ihm->GetQualite() == LUXE) 
        cafe = new Luxe(ihm->GetType(), ihm->GetSucre());
    else
        cafe = new Normale(ihm->GetType(), ihm->GetSucre());

        if (ihm->GetType()==LONG) { // Si le cafe est long, on attend 5 secondes le temps que la vanne d'eau verse l'eau dans le gobelet
            cout << "Votre cafe va etre dispense dans:\n";
            for (int i = 0; i < 5; i++) {
                cout << 5 - i << "\n";
                sleep_for(1s);
            }
            string qual = (ihm->GetQualite() == LUXE) ? "luxe" : "normale";
            cout << "La machine dispense un cafe :\n-Long\n-" << qual;
            cout << " avec " << ihm->GetSucre() << " sucre\n";
        }
        else {
            cout << "Votre cafe va etre dispense dans:\n"; // Si le cafe est court on attend 3 secondes
            for (int i = 0; i < 3; i++) {
                cout << 3 - i << "\n";
                sleep_for(1s);
            }
            string qual = (ihm->GetQualite() == LUXE) ? "luxe" : "normale";
            cout << "La machine dispense un cafe :\n-Court\n-" << qual;
            cout << " avec " << ihm->GetSucre() << " sucre\n";

        }
}
