#include <iostream>
#include "othellobord.h"
using namespace std;


// Returnt EERSTE karakter: van invoer
char leesInvoer() {
    char input;

    do { // Alle tabs en enters worden weggehaald
        input = cin.get();
    } while (input == '\n' || input == '\t');
    return input;
}

// Leegt de terminal, maakt alles mooier
void leegTerminal() {
    // std::system("CLS");

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Afdrukken(Bordvakje *ingang) {
    Bordvakje *p = ingang; // pointertje om lijst mee door te lopen
    while (p != nullptr) {
        cout << " # " << p->kleur << " | ";
        p = p->buren[2];
    } // while
    cout << endl;
} // Afdrukken

void Toevoegen(Bordvakje *&ingang, char kleur)
{
    Bordvakje *p; // hulppointertje
    while(p != nullptr) {
        p = p->buren[2];
    }
    p = new Bordvakje;
    p->kleur = kleur;
    p->buren[2] = ingang;
    ingang = p;
} // Toevoegen

void Verwijderen(Bordvakje *&ingang)
{
    Bordvakje *p = ingang; // hulppointertje
    if (ingang != nullptr) {
        ingang = ingang->buren[2];
        delete p;             // in deze volgorde
    }                         // if
} // Verwijderen

void geefKleur(char &kleur) {
    cout << "Geef een kleur op:";
    cin >> kleur;
}


void geefIndex(int &index) {
    char input;
    cout << "Geef een index op: ";
    cin >> input;
    if( !(input < '0') && !(input > '9')) {
        index = (int)(input - '0');
    }
    else {
        index = 0;
    }
}

char krijgKleur(Bordvakje *ingang, int index)
{
    Bordvakje *p = ingang; // pointertje om lijst mee door te lopen
    int counter = 0;
    while (p != nullptr) {
        cout << p->kleur;
        if(counter == index) {
            return p->kleur;
        }        
        counter++;
        p = p->buren[2];
    } // while
    return '-';
}

int main() {

    Bordvakje *ingang = nullptr; // ingang van de op te bouwen lijst (of NULL)
    char keuze;              // wat wil de gebruiker?
    char kleur;
    int index;

    do {
        cout << "Kies uit: [s]toppen, [t]oevoegen, [l]ezen,  " << endl
             << "          [a]fdrukken, [v]erwijderen" << endl
             << "Uw keuze: ";
        cin >> keuze;
        leegTerminal();
        switch (keuze)
        {
        case 's':
        case 'S':
            cout << "Dat was het dan ..." << endl;
            break;
        case 't':
        case 'T':
            geefKleur(kleur);
            Toevoegen(ingang, kleur);
            Afdrukken(ingang);
            break;
        case 'a':
        case 'A':
            Afdrukken(ingang);
            break;
        case 'l':
        case 'L':
            geefIndex(index);
            cout << krijgKleur(ingang, index) << endl;
        case 'v':
        case 'V':
            Verwijderen(ingang);
            Afdrukken(ingang);
            break;
        default:
            cout << "Niet toegestane menukeuze ..." << endl;
        } // switch
    }     // do 

    while( !(keuze == 's') && !(keuze == 'S'));


    return 0;
    
}