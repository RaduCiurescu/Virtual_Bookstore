// cartile vor fi introduse astfel: Primul cuvant este tipul cartii, fictiune sau nonfictiune, in cazul in care este fictiune dupa tip urmeaza numarul de pagini, in caz contrar anul publicarii.
//dupa urmeaza titlul scris impreuna, pretul, numarul de carti valabile in stoc iar la final autorii iar dupa ultimul autor . (punct)

#include<list>
#include <iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<regex>
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
int email_valid(string e)
{
    regex pattern("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
    if (regex_match(e, pattern))
        return 1;
    return 0;
        
}
int email_unic(list<utilizator*> u, string e)
{
    for (auto i : u)
    {
        if (i->getemail() == e && email_valid(i->getemail())==1)
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
int carte_existenta(list<carte*>carti, string nume)
{
    for (auto i : carti)
    {
        if (i->gettitlu() == nume)
            return 1;
    }
    return 0;
}
void contact(utilizator* u)
{
    char opt;
    ofstream fout("sesizari.txt", ios::app);
    string nume, prenume, cnp, email, problema;
    cout << "\nBookstoreApp.\n\nIn cazul in care inalniti dificultati echipa de suport va sta la dispozitie.\nTot ce trebuie sa faceti este sa completati urmatorul formular in care trebuie descrisa problema\nAlegeti o optiune:\n1.Trimitere sesizare\n2.Inapoi\n";
    cin >> opt;
    try {
        switch (opt)
        {
        case '1':
            if (u == 0)
            {
                cout << "Numele:"; cin >> nume;
                cout << "\nPrenumele:"; cin >> prenume;
                cout << "\nCNP:"; cin >> cnp;
                cout << "\nEmail:"; cin >> email;
                cin.ignore(1, '\n');
                cout << "\nIntroduceti problema intampinata:"; getline(cin, problema);
                fout << "\n\nBuna ziua,\nSubsemnatul: " << nume << " " << prenume << ",avand CNP: " << cnp << "\n" << problema << "\nMultumesc,\n" << nume << " " << prenume;
                cout << "\nSesizarea a fost trimisa cu succes.";
            }
            else
            {

                cin.ignore(1, '\n');
                cout << "\nIntroduceti problema intampinata:"; getline(cin, problema);
                fout << "\n\nBuna ziua,\nSubsemnatul: " << u->getnume() << " " << u->getprenume() << ",avand CNP: " << u->getcnp() << "\n" << problema << "\nMultumesc,\n" << u->getnume() << " " << u->getprenume();
                cout << "\nSesizarea a fost trimisa cu succes.";
            }

            fout.close();

            //WinExec("curl smtps://smtp.gmail.com:465 -v --mail-from \"ciurescuradu@gmail.com\" --mail-rcpt \"receptor@gmail.com\" --ssl-reqd --user ciurescuradu@gmail.com:agrafe123 -T \"email.txt\" -k --anyauth", SW_HIDE);
            break;
        case '2':
            break;
        default:
            throw new exception("optiunea introdusa nu exista\n");
            break;
        };
    }
    catch (exception* e)
    {
        ofstream zout("log.txt", ios::app);
        cout << e->what();
        zout << e->what();
        zout.close();
    }

}
void inregistrare(list<utilizator*>& utilizatori)
{
    ofstream fout("log.txt", ios::app);
    string nume, prenume, cnp, email, parola;
    
        cout << "\nintrodu nume: "; cin >> nume;
        cout << "\nintrodu prenume: "; cin >> prenume;
        do {
            try
            {
                cout << "\nintrodu cnp unic: "; cin >> cnp;
                if (cnp_unic(utilizatori, cnp) == 1)
                    throw new exception("CNP-ul introdus nu este unic, va rugam reintroduceti un cnp unic\n");
            }
            catch (exception* e)
            {
                cout << e->what();
                fout << e->what();
            }
        } while (cnp_unic(utilizatori, cnp) == 1);

        do {
            try {
                cout << "\nintrodu email unic: "; cin >> email;
                if (email_valid(email) == 0 || email_unic(utilizatori,email)==1)
                    throw new exception("email-ul introdus este invalid, va rugam sa introduceti un email valid\n");
            }
            catch (exception* e)
            {
                cout << e->what();
                fout << e->what();
            }
        } while (email_valid(email) == 0 || email_unic(utilizatori, email) == 1);
        do {
            try {
                cout << "\nintrodu parola: "; cin >> parola;
                if (parola.length() < 3)
                    throw new exception("parola introdusa are mai putin de 3 caractere\n");
            }
            catch (exception* e)
            {
                cout << e->what();
                fout << e->what();
            }
        } while (parola.length() < 3);
   

        fout.close();
    utilizatori.push_back((utilizator*)new utilizator(nume, prenume, cnp, email, parola));
}
void afisare_utilizatori(list<utilizator*>utilizatori)
{
    for (auto i : utilizatori)
        i->afisare_utilizator();
}
istream& operator>>(istream& in, list<utilizator*>&utilizatori)
{
    inregistrare(utilizatori);
    return in;
}
void resetare_parola(list<utilizator*>utilizatori)
{
    ofstream fout("log.txt", ios::app);
    string email,parola;
    cout << "\nIntrodu  adresa de email pentru care vrei sa resetezi parola: "; cin >> email;
    try {
        if (email_unic(utilizatori, email) == 0)
            throw new exception("Nu exista cont creat cu acest email\n"); //!!
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
    catch (exception* e)
    {
        cout << e->what();
        fout << e->what();
    }
    fout.close();
    
}
void meniu_autentificat(utilizator* utilizator,list<carte*>carti)
{
    string titlu;
    char opt, opt2;
    do {
        cout << "\nAlegeti o optiune:\n1. Achizitie/Imprumut\n2. Istoric\n3. Contact\n4.Delogare\n"; cin >> opt;
        try{
        switch (opt)
        {
        case '1':
            for (auto i : carti)
            {
                i->afisare_carte();
                cout << "\n";
            }
            do{
            cout << "\nalegeti optiunea:\n1.Achizitioneaza\n2.Imprumut\n3.Inapoi\n"; cin >> opt2;
            try{
            switch (opt2)
            {
            case '1':
                cout << "Introdu titlul cartii pe care vrei sa o cumperi: "; cin >> titlu;
                try {
                    if (carte_existenta(carti, titlu) == 0)
                        throw new exception("Cartea nu exista in magazinul nostru\n");
                    else
                        for (auto i : carti)
                        {
                            if (i->gettitlu() == titlu)
                                if (i->getstoc() == 0)
                                    cout << "Stoc epuizat!";
                                else
                                {
                                    i->diminuare_stoc();
                                    utilizator->crestecheltuiala(i->getpret());
                                    utilizator->adaugacarteinistoric(i);
                                    cout << "Cartea a fost achizitionata cu succes.";
                                    break;
                                }
                        }
                }
                catch (exception* e)
                {
                    ofstream fout("log.txt", ios::app);
                    cout << e->what();
                    fout << e->what();
                    fout.close();
                }
                break;

            case '2':
                cout << "Introdu titlul cartii pe care vrei sa o imprumuti: "; cin >> titlu;
                try {
                    if (carte_existenta(carti, titlu) == 0)
                        throw new exception("Cartea nu exista in magazinul nostru\n");
                    else
                        for (auto i : carti)
                        {
                            if (i->checkimprumut() == true)

                                cout << "\nCartea nu e disponibila!";
                            else
                            {
                                i->seteaza_imprumut();
                                cout << "Cartea a fost imprumutata cu succes.";
                            }
                            break;
                        }
                }
                    catch (exception* e)
                    {
                        ofstream fout("log.txt", ios::app);
                        cout << e->what();
                        fout << e->what();
                        fout.close();
                    }
                break;
            case '3':
                break;
            default:
                throw new exception("optiunea introdusa nu exista\n");
                break;
            };
            }
            catch (exception* e)
            {
                ofstream zout("log.txt", ios::app);
                cout << e->what();
                zout << e->what();
                zout.close();
            }
            } while (opt2 != '3');
            break;
        case '2':
            utilizator->afisareistoric();
            break;
        case '3':
            contact(utilizator);
            break;
        case '4':
            break;
        default:
            throw new exception("optiunea introdusa nu exista\n");
            break;
        };
        }
        catch (exception* e)
        {
            ofstream zout("log.txt", ios::app);
            cout << e->what();
            zout << e->what();
            zout.close();
        }
    } while (opt != '4');
}
void conectare(list<utilizator*>&utilizatori,list<carte*>carti)
{
    ofstream fout("log.txt", ios::app);
    utilizator* u;
    char opt;
    cout << "\nAlegeti o optiune:\n1.Inregistrare\n2.Autentificare\n3.Resetare parola\n4.Inapoi\n";

    cin >> opt;
    try{
    switch (opt)
    {
    case '1':
        cin>>utilizatori;
        break;
    case '2':
            u = autentificare(utilizatori);
            try {
                if (u != 0)
                {
                    cout << "autentificare cu succes\n";
                    meniu_autentificat(u, carti);
                }
                else {
                    throw new exception("Nu ati introdus datele corect, va rog sa verificati sau sa va creati un cont in caz ca nu aveti\n");//!!
                }
            }
            catch (exception* e)
            {
                cout << e->what();
                fout << e->what();
            }
        break;
    case '3':
        resetare_parola(utilizatori);
        break;
    case '4':
        break;
    default:
        throw new exception("optiunea introdusa nu exista\n");
        break;
    };
    }
    catch (exception* e)
    {
        ofstream zout("log.txt", ios::app);
        cout << e->what();
        zout << e->what();
        zout.close();
    }
    fout.close();
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

int main()
{
    list<utilizator*>utilizatori;
    list<carte*>carti;
    char opt,opt2;
    citire_carti(carti);

    do
    {
        try {
            cout << "\nBookstoreApp.\n\nAlege o optiune: \n1)Conectare\n2)Contact\n3)exit\n";
            cin >> opt;
            switch (opt)
            {
            case '1':
                conectare(utilizatori, carti);
                break;
            case '2':
                contact(0);
                break;
            case '3':
                exit(0);
                break;
            default:
                throw new exception("optiunea introdusa nu exista\n");
                break;
            };
        }catch (exception* e)
                {
                    ofstream fout("log.txt", ios::app);
                    cout << e->what();
                    fout << e->what();
                    fout.close();
                }
    }while (1);
}
