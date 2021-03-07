

#include<chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

enum Qualite {LUXE, NORMALE};
enum Type {COURT, LONG};

class Cafe {
public:
    virtual void f() = 0; // Pour que la classe soit virtuelle
    Cafe(Type t, bool s, Qualite q);
private:
    Type type;
    bool sucre;
    Qualite qualite;
    float prix;
};

Cafe::Cafe(Type t, bool s, Qualite q) : type(t), sucre(s), qualite(q) {
    prix = (qualite == NORMALE) ? (float)1.5 : (float)2;
}


class Gobelets {
public:    
    Gobelets();
    int GetQuantite() { return quantite; } //Renvoie la quantite de gobelets restante
    void sert(); // Enleve 1 gobelets du stock
    void approvisionner(int quan); // Permet a l'administrateur de reapprovisionner en gobelets
private :
    int quantite;
};

Gobelets::Gobelets() : quantite (5) {}
void Gobelets::sert() { quantite--; }
void Gobelets::approvisionner(int quan) { quantite += quan; }

class IHM {
public:
    IHM();
    void SetType(); //Choisir Court ou Long 
    void SetLuxe() { qualite = LUXE; } // Choisir Luxe
    void SetNormale() { qualite = NORMALE; } // Choisir Normale
    void SetSucre(); // Choisir si on veut du sucre ou pas
    Type GetType() { return type; } // Fetch court ou long
    Qualite GetQualite() { return qualite; } // Fetch qualite
    bool GetSucre() { return sucre; } // Fetch sucre
private:
    Type type;
    Qualite qualite;
    bool sucre;
};

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

class Luxe : public Cafe { 
public:
    Luxe(Type t, bool sucre) : Cafe(t,sucre,LUXE) {}
    virtual void f() { cout <<"0"; } // Pour rendre Luxe non abstraite
};

class Normale : public Cafe {
public:
    Normale(Type t, bool sucre) : Cafe(t, sucre, NORMALE) {}
    virtual void f() { cout << "0"; } // Pour rendre Normale non abstraite
};

class Monnayeur {
public:
    Monnayeur();
    void AjoutePiece(float piece) { somme += piece; } //On accumule les pieces pour payer un cafe
    float GetSomme() { return somme; } // Fetch la somme accumule
    void CalculRendu(IHM* choix); // Calcul l'argent a rendre et rend se qu'il faut, ensuite elle remet la somme a 0
private:
    float somme;
};
Monnayeur ::Monnayeur () : somme(0){}
void Monnayeur::CalculRendu(IHM * choix) {
    float prix = (choix->GetQualite() == NORMALE) ? 1.5 : 2;
    cout << "La machine rend: " << somme - prix << "\n";
    somme = 0;
}

class Sucre { // Similaire a gobelets
public:
    Sucre() : quantite(1) {}
    void verse() { quantite -= 1; }
    void approvisionner(int quan) { quantite += quan; }
    int GetQuantite() { return quantite; }   
private:
    int quantite;
};

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

int main()
{
    Distributeur D(411); // 411 est l'ID du distributeur
    /*D.~Distributeur();
    cout << "test\n";*/
    while (D.GetGobelets()>0)  //tant qu'on a des gobelets les utilisateurs peuvent commander
    D.Programme();
    cout << "\nIl n'y a plus de gobelets, le responsable maintenance va s'en charger\n";
}

