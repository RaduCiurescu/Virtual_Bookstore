// cartile vor fi introduse astfel: Primul cuvant este tipul cartii, fictiune sau nonfictiune, in cazul in care este fictiune dupa tip urmeaza numarul de pagini, in caz contrar anul publicarii.
//dupa urmeaza titlul scris impreuna, pretul, numarul de carti valabile in stoc iar la final autorii iar dupa ultimul autor . (punct)


#include<list>
#include <iostream>
#include<fstream>
#include<string>
#include<Windows.h>
using namespace std;

class carte {
private:
    string titlu, editura;
    list<string>nume_autori;
    float pret;
    int stock;
    bool imprumut=false;
public:
    carte(string _titlu, list<string> _numele_autorilor, string _editura, float _pret, int _stock)
    {
        this->titlu = _titlu;
        this->nume_autori = _numele_autorilor;
        this->editura = _editura;
        this->stock = _stock;
        this->pret = _pret;
    }

    virtual float getpret()
    {
        return pret;
    }
    virtual string tip()
    {
        return "nu are";
    }
    void diminuare_stoc()
    {
        stock =stock- 1;
    }
    void seteaza_imprumut()
    {
        imprumut = true;
    }
    bool checkimprumut()
    {
        return imprumut;
    }
    virtual void afisare_carte()
    {
        cout << titlu <<" sunt in stoc "<<stock<<" exemplare de la editura " << editura << " scrisa de ";
        for (auto i : nume_autori)
            cout << i << " ";
    }
    string gettitlu()
    {
        return titlu;
    }
    int getstoc()
    {
        return stock;
    }
};
class carte_fictiune : public carte
{
private:
    int nr_pagini;
public:
    carte_fictiune(string _titlu, list<string> _numele_autorilor, string _editura, float _pret, int _stock, int _nr_pagini) : carte(_titlu, _numele_autorilor, _editura, _pret, _stock)
    {
        this->nr_pagini = _nr_pagini;
    }

    float getpret()override
    {
        return carte::getpret() + nr_pagini;
    }
    string tip()override {
        return "fictiune";
    }
    void afisare_carte()override
    {
        cout <<"Tip: "<< tip() << " titlu: ";
        carte::afisare_carte();
        cout << " costa: " << getpret()<<" lei si are "<<nr_pagini<<" pagini.";
    }
};
class carte_nonfictiune : public carte
{
private:
    int an_publicare;
public:
    carte_nonfictiune(string _titlu, list<string> _numele_autorilor, string _editura, float _pret,int _stock, int _an_publicare) :carte(_titlu, _numele_autorilor, _editura, _pret, _stock)
    {
        this->an_publicare = _an_publicare;
    }

    float getpret()override
    {
        return carte::getpret() - (25 * an_publicare);
    }
    string tip()override {
        return "nonfictiune";
    }
    void afisare_carte()override
    {
        cout << "Tip: " << tip() << " titlu: ";
        carte::afisare_carte();
        cout << ", costa: " << getpret()<<" lei si a fost publicata in anul "<<an_publicare<<".";
    }
};
class utilizator
{
private:
    string nume, prenume, CNP, email, parola;
    list<carte*> istoric;
    float cheltuit=0;
public:
    
    utilizator(string nume, string prenume, string CNP, string email, string parola)
    {
        this->nume = nume;
        this->prenume = prenume;
        this->CNP = CNP;
        this->email = email;
        this->parola = parola;
        this->cheltuit = 0;
    }
    bool checkmail(string email)
    {
        return this->email == email;
    }
    bool checkparola(string parola)
    {
        return this->parola == parola;
    }
    string getnume()
    {
        return this->nume;
    }
    string getprenume()
    {
        return this->prenume;
    }
    string getemail()
    {
        return this->email;
    }
    string getcnp()
    {
        return this->CNP;
    }
    void afisare_utilizator()
    {
        cout << "\nnume: " << this->nume << " prennume: " << this->prenume << " cnp: " << this->CNP << " email: " << this->email << " parola: " << this->parola;
    }
    void reset_parola(string parola_)
    {
        parola = parola_;
    }
    void adaugacarteinistoric(carte *carte)
    {
        istoric.push_back(carte);  //!
    }
    void crestecheltuiala(float suma)
    {
        cheltuit = cheltuit + suma; //!
    }
    void afisareistoric()
    {
        cout << "utilizatorul: " << nume << " a achizitionat urmatoarele carti: \n";
        for (auto i : istoric)
        {
           cout<< i->gettitlu()<<"; ";
            
        }
        cout << "\nTotal cheltuit: " << cheltuit << " lei\n";
    }
};


utilizator* autentificare(list<utilizator*>utilizatori)
{
    int k = 0;
    string email, parola;
        cout << "Introdu email: "; cin >> email;
        cout << "Introdu parola: "; cin >> parola;
        for (auto i : utilizatori)
        {
            if (i->checkmail(email) == 1 && i->checkparola(parola) == 1)
            {
                return i;
            }
        }
        return 0;
}
int email_unic(list<utilizator*> u, string e)
{
    for (auto i : u)
    {
        if (i->getemail() == e)
            return 1;
    }
    return 0;
}
int cnp_unic(list<utilizator*> u, string c)
{
    for (auto i : u)
    {
        if (i->getcnp() == c)
            return 1;
    }
    return 0;
}
void inregistrare(list<utilizator*>& utilizatori)
{
    string nume, prenume, cnp, email, parola;
    cout << "\nintrodu nume: "; cin >> nume;
    cout << "\nintrodu prenume: "; cin >> prenume;
    do {
        cout << "\nintrodu cnp unic: "; cin >> cnp;
        if (cnp_unic(utilizatori, cnp) == 1)
            cout << "\nCNP-ul introdus nu este unic, va rugam reintroduceti un cnp unic";
    } while (cnp_unic(utilizatori,cnp)==1);

    do {
        cout << "\nintrodu email unic: "; cin >> email;
        if(email_unic(utilizatori,email)==1)
            cout << "\nemail-ul introdus nu este unic, va rugam reintroduceti un email unic";
    } while (email_unic(utilizatori, email) == 1);
    do {
        cout << "\nintrodu parola: "; cin >> parola;
        if (parola.length() < 3)
            cout << "\nparola introdusa are mai putin de 3 caractere";
    } while (parola.length() < 3);
    utilizatori.push_back((utilizator*)new utilizator(nume, prenume, cnp, email, parola));
}
void afisare_utilizatori(list<utilizator*>utilizatori)
{
    for (auto i : utilizatori)
        i->afisare_utilizator();
}
void resetare_parola(list<utilizator*>utilizatori)
{
    string email,parola;
    cout << "\nIntrodu  adresa de email pentru care vrei sa resetezi parola: "; cin >> email;
    if (email_unic(utilizatori, email) == 0)
        cout << "\nNu exista cont creat cu acest email";
    else {
        for (auto user : utilizatori)
        {
            if (user->getemail() == email)
            {
                cout << "\nintrodu noua parola: "; cin >> parola;
                user->reset_parola(parola);
                break;
            }
        }
    }
    
}
void meniu_autentificat(utilizator* utilizator,list<carte*>carti) //zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
{
    string titlu;
    int opt, opt2;
    do {
        cout << "\nAlegeti o optiune:\n1. Achizitie/Imprumut\n2. Istoric\n3. Contact\n4.Inapoi\n"; cin >> opt;
        switch (opt)
        {
        case 1:
            for (auto i : carti)
            {
                i->afisare_carte();
                cout << "\n";
            }
            do{
            cout << "\nalegeti optiunea:\n1.Achizitioneaza\n2.Imprumut\n3.Inapoi\n"; cin >> opt2;
            switch (opt2)
            {
            case 1:
                cout << "Introdu titlul cartii pe care vrei sa o cumperi: "; cin >> titlu;
                for (auto i : carti)
                {
                    if (i->gettitlu() == titlu)
                        if (i->getstoc() == 0)
                            cout << "\nStoc epuizat!";
                        else
                        {
                            i->diminuare_stoc();
                            utilizator->crestecheltuiala(i->getpret());
                            utilizator->adaugacarteinistoric(i);/// ??
                            break;
                        }
                }

                break;

            case 2:
                cout << "Introdu titlul cartii pe care vrei sa o imprumuti: "; cin >> titlu;
                for (auto i : carti)
                {
                    if (i->checkimprumut() == true)

                        cout << "\Cartea nu e disponibila!";
                    else
                    {
                        i->seteaza_imprumut();
                    }
                    break;
                }
                break;
            case 3:
                break;
            };
            }while (opt2 != 3);
            break;
        case 2:
            utilizator->afisareistoric();
            break;
        case 3:

            break;
        case 4:
            break;


        };
    } while (opt!=4);
}
void conectare(list<utilizator*>&utilizatori,list<carte*>carti)
{
    utilizator* u;
    int opt;
    cout << "\nAlegeti o optiune:\n1.Inregistrare\n2.Autentificare\n3.Resetare parola\n4.Inapoi\n";

    cin >> opt;
    switch (opt)
    {
    case 1:
        inregistrare(utilizatori);
        break;
    case 2:
            u = autentificare(utilizatori);
        if (u != 0)
        {
            cout << "autentificare cu succes\n";
        meniu_autentificat(u,carti);
        }
        else {
            cout << "Nu ati introdus datele corect, va rog sa verificati sau sa va creati un cont in caz ca nu aveti";
        }
        break;
    case 3:
        resetare_parola(utilizatori);
        break;
    case 4:
        break;
    }

}
void citire_carti(list<carte*>& carti)
{
    list<string>autori;
    string titlu, editura, autor, tip;
    int nr_pag, an_pub;
    int stoc;
    float pret;
    ifstream fin("carti.txt");
    while (fin >> tip)
    {
        if (tip == "fictiune")
            fin >> nr_pag;
        else if (tip == "nonfictiune")
            fin >> an_pub;
        fin >> titlu >> editura >> pret >> stoc;
        autori.clear();
        while (fin >> autor && autor != ".")
            autori.push_back(autor);

        if (tip == "fictiune")
            carti.push_back(new carte_fictiune(titlu, autori, editura, pret, stoc, nr_pag));
        else if (tip == "nonfictiune")
            carti.push_back(new carte_nonfictiune(titlu, autori, editura, pret, stoc, an_pub));
    }
}

void contact()
{
    int opt;
    cout << "\nBookstoreApp.\n\nIn cazul in care inalniti dificultati echipa de suport va sta la dispozitie.\nTot ce trebuie sa faceti este sa completati urmatorul formular in care trebuie descrisa problema\nAlegeti o optiune:\n1.Trimitere sesizare\n2.Inapoi\n";
    cin >> opt;
    switch (opt)
    {
    case 1:

        break;
    case 2:
        break;
    };

}
int main()
{
    list<utilizator*>utilizatori;
    list<carte*>carti;
    int opt,opt2;
    citire_carti(carti);

    do
    {
        cout << "\nBookstoreApp.\n\nAlege o optiune: \n1)Conectare\n2)Contact\n3)afisare utilizatori inregistrati\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            conectare(utilizatori,carti);
            break;
        case 2:
            contact();
            
            break;
        case 3:
            afisare_utilizatori(utilizatori);
        };

    }while (1);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
