// PROIECT POO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<list>
#include <iostream>
#include<fstream>
#include<string>
using namespace std;

class utilizator
{
private:
    string nume, prenume, CNP, email, parola;
public:
    utilizator(string nume, string prenume, string CNP, string email, string parola)
    {
        this->nume = nume;
        this->prenume = prenume;
        this->CNP = CNP;
        this->email = email;
        this->parola = parola;
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
};

utilizator* autentificare(list<utilizator*>utilizatori)
{
    int k = 0;
    string email, parola;
        cout << "Introdu email: "; cin >> email;
        cout << "Introdu parola: "; cin >> parola;
        for (auto i : utilizatori)
        {
            if (i->checkmail(email) == i->checkparola(parola) == 1)
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
        cout << "\nintrodu email unic"; cin >> email;
        if(email_unic(utilizatori,email)==1)
            cout << "\nemail-ul introdus nu este unic, va rugam reintroduceti un email unic";
    } while (email_unic(utilizatori, email) == 1);
    do {
        cout << "\n introdu parola: "; cin >> parola;
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
void conectare(list<utilizator*>&utilizatori)
{
    utilizator* u;
    int opt;
    cout << "\nAlegeti o optiune:\n1.Autentificare\n2.Inregistrare\n3.Resetare parola\n4.Inapoi\n";
    cin >> opt;
    switch (opt)
    {
    case 1:
        if (autentificare(utilizatori) != 0)
            cout << "autentificare cu succes";
            u=autentificare(utilizatori);

        break;
    case 2:
        inregistrare(utilizatori);
        break;
    case 3:

        break;
    case 4:
        break;
    }

}
void pagina_autentificat(utilizator* utilizator) //zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
{

}
int main()
{
    list<utilizator*>utilizatori;
    int opt;
    

    do
    {
        cout << "BookstoreApp.\n\nAlege o optiune: \n1)Conectare\n2)Contact\n3)afisare useri";
        cin >> opt;
        switch (opt)
        {
        case 1:
            conectare(utilizatori);
            break;
        case 2:
            //contact
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
