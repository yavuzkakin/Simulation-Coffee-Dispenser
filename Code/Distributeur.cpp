

#include "Distributeur.h"

Distributeur::Distributeur(int val) {
    gobelets = new Gobelets;
    sucre = new Sucre;
    ihm = new IHM;
    monnayeur = new Monnayeur;
    control = new Controleur(ihm, monnayeur);
    Id = val;
}

Distributeur::~Distributeur() {
    delete control;
    delete ihm;
    delete monnayeur;
}

void Distributeur::Programme() {
            
    cout << "Etes vous un administrateur ?\n" << "Entrez 0 pour entrer en mode admin\nEntrer 1 pour acheter un cafe\n"; 
    // On ajoute un mode admin pour reapprovisionner la machine si besoin
    int admin;
    cin >> admin;
    if (!admin) {
        cout << "Veuillez entrer votre mot de passe : "; //Pour securiser le mode admin on a ajoute un mot de passe
        int mdp;
        cin >> mdp;
        if (mdp == 3012) { // le mot de passe est 3012
            cout << "Voulez vous reapprovisionner : tapez 0 les gobbelets\t1 le sucre\n";
            int approv;
            cin >> approv;
            if (approv) {
                cout << "Combien de sucres voulez vous rajouter ? : ";
                int quant;
                cin >> quant;
                sucre->approvisionner(quant);
            }
            else {
                cout << "Combien de gobelets voulez vous rajouter ? : ";
                int quant;
                cin >> quant;
                gobelets->approvisionner(quant);
            }
        }
        else
            cout << "Mauvais mot de passe\n"; // Si vous n'etes pas administrateur
    }
    else {
        if ((gobelets->GetQuantite() == 0))
            cout << "Il n'y a plus de gobelets, le responsable maintenance va s'en charger\n"; // utile uniquement si on commence avec 0 gobelet

        else { 
            control->AfficherOptions();
            control->Payer();
            if ((sucre->GetQuantite() > 0)) {//On verifie s'il y a encore du sucre en stock
                gobelets->sert();
                if (ihm->GetSucre())
                    sucre->verse();
                control->DispenseProduit();
            }

            else { // Si on est en rupture de stock en sucre, on gere les deux cas possibles : 
                if (ihm->GetSucre()) { //L'utilisateur a choisi un cafe avec sucre
                    cout << "Il n'y a plus de sucre\nVoulez vous un cafe sans sucre ?\nEntrer : 0 pour NON\t1 pour OUI\n";
                    int choix;
                    cin >> choix;
                    if (choix) { // Le premier cas est si il veut changer sa commande et poursuivre sans sucre
                        gobelets->sert();
                        if (ihm->GetType() == LONG) {

                            cout << "Votre cafe va etre dispense dans:\n";
                            for (int i = 0; i < 5; i++) {
                                cout << 5 - i << "\n";
                                sleep_for(1s);
                            }
                            string qual = (ihm->GetQualite() == LUXE) ? "Luxe" : "Normale";
                            cout << "La machine dispense un cafe :\n-Long\n-" << qual;
                            cout << " sans" << " sucre\n";
                        }
                        else {

                            cout << "Votre cafe va etre dispense dans:\n";
                            for (int i = 0; i < 3; i++) {
                                cout << 3 - i << "\n";
                                sleep_for(1s);
                            }
                            string qual = (ihm->GetQualite() == LUXE) ? "Luxe" : "Normale";
                            cout << "La machine dispense un cafe :\n-Court\n-" << qual;
                            cout << " sans" << " sucre\n";
                        }
                    }
                    else { // Il decide de ne plus commander un cafe, on lui rend son argent
                        cout << "Excusez nous pour ce probleme, le responsable maintenance va s'en charger\n";
                        float prix = (ihm->GetQualite() == NORMALE) ? 1.5 : 2;
                        cout << "La machine rend : " << prix << "euros\n";
                    }
                }
                else { //On n'a plus de sucres mais l'utilisateur n'en a pas demande 
                    gobelets->sert();
                    control->DispenseProduit();
                }
            }
            if (ihm->GetSucre()) // On remet tout aux valeurs par defaults
                ihm->SetSucre();
            if (ihm->GetType())
                ihm->SetType();

        }
    }
}
