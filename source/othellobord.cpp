#include <iostream>
#include <othellobord.h>
#include <main.h>

using namespace std;

void Othellobord::afdrukken() {
    Bordvakje* omlaagptr = ingang;
    Bordvakje* rechtsptr;

    while(omlaagptr) {
        rechtsptr = omlaagptr;
        while(rechtsptr) {
            cout << (rechtsptr->kleur) << " | ";
            rechtsptr = rechtsptr->buren[2];
        }
        cout << "\n";
        omlaagptr = omlaagptr->buren[4];
    }
}

Vec Othellobord::krijgCoordinaten() {
    Vec position; 
    cout << "Geef het eerste coordinaat (x) ";
    position.x = krijgGetal();
    cout << "Geef het tweede coordinaat (y) ";
    position.y = krijgGetal();
    return position;
}

char Othellobord::krijgKleur() {
    char kleur; 
    kleur = krijgInvoer();
    switch (kleur)
    {
    case 'w':
    case 'W':
        return 'w';
    case 'z':
    case 'Z':
        return 'z';
    default:
    // cout
        break;
    }
}

void Othellobord::zetPositie() {
    Vec positie;
    Bordvakje* posPtr;
    char kleur;

    positie = krijgCoordinaten();
    kleur   = krijgKleur();
    posPtr  = elementPtr(positie);
}

Bordvakje* Othellobord::elementPtr(Vec pos) {
    
    int diagonaalStap; 
    int rechtStap;
    bool omlaag;

    if(pos.x < pos.y) {
        diagonaalStap = pos.x;
        rechtStap = pos.y - pos.x;
        omlaag = true;
    }
    else {
        diagonaalStap = pos.y;
        rechtStap = pos.x - pos.y;
    }

    Bordvakje* huidige = ingang;

    for (int i = 0; i < diagonaalStap; i++) {
        if(huidige) {
            huidige = huidige->buren[3];
        }
        else {
            return NULL;
        }
    }
    for (int i = 0; i < rechtStap; i++) {
        if(huidige) {
            if(huidige) {
                if(omlaag) {
                    huidige = huidige->buren[4];
                }
                else {
                    huidige = huidige->buren[2];
                }
            }
            else {
                return NULL;
            }
        }
    }
    return huidige;   
}

void Othellobord::ritsMap() {

    Bordvakje* boven = new Bordvakje;
    
    for (int i = 0; i < mapgrootte; i++) {
        Bordvakje* rijIngang; //row-wise head of list.
        Bordvakje *vorige = new Bordvakje; // dummy node to mark start of left pointer.
        for (int j = 0; j < mapgrootte; j++) {
            Bordvakje* temp = new Bordvakje;
 
            if (j == 0) {
                rijIngang = temp;
            }
            if (i == 0 && j == 0) {
                ingang = temp;
            } 

            temp->buren[6] = vorige;
            vorige->buren[2] = temp;
            
            if (i == mapgrootte - 1) temp->buren[4] = NULL;
 
            //This is only used for 1st row.
            if (!boven->buren[2]) {
                boven->buren[2] = new Bordvakje;
            }
            boven = boven->buren[2];
 
            temp->buren[0] = boven;
            boven->buren[4] = temp;
            vorige = temp;
 
            if (j == mapgrootte - 1) {
                vorige->buren[2] = NULL;
            }
        }
        boven = rijIngang->buren[6];
    }
}