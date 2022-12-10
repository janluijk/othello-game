#include <iostream>
#include "othellobord.h"
#include "main.h"

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
    while (1)
    {
        switch (kleur)
        {
            case 'w':
            case 'W':
                return 'w';
                break;
            case 'z':
            case 'Z':
                return 'z';
                break;
            default:
                cout << "Geef een juist karakter op svp" << endl;
                break;
        }

    }
    
}

void Othellobord::zetPositie() {
    Vec positie;
    Bordvakje* posPtr;
    char kleur;

    positie = krijgCoordinaten();
    kleur   = krijgKleur();
    posPtr  = elementPtr(positie);
    posPtr->kleur = kleur;
}


//  ┌─┬─┬─┐
//  │x│x│x│
//  └─┴─┴─┘

Bordvakje* Othellobord::elementPtr(Vec pos) {
    
    int diagonaalStap; 
    int rechtStap;
    bool omlaag = false;

    pos.x--; // Array start op 0, coordinaten start op 1!
    pos.y--;

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
    Bordvakje* rijIngang;
    Bordvakje* boven;
    Bordvakje* rechtsboven;
    Bordvakje* linksboven;
    Bordvakje* vorige;

    for (int i = 0; i < mapgrootte; i++) {
        for (int j = 0; j < mapgrootte; j++) {
            
            Bordvakje* temp = new Bordvakje;
            
            if(j == 0 && i == 0) {
                ingang = temp;
                rijIngang = temp;
                vorige = temp;
                            
                continue;
            }

            if(j == 0) {
                rijIngang = temp;       
                
                temp->buren[0] = boven;
                boven->buren[4] = temp;

                temp->buren[1] = rechtsboven;
                rechtsboven->buren[5] = temp;                
                
                vorige = temp;
                linksboven = boven;
                boven = rechtsboven;
                rechtsboven = rechtsboven->buren[2];

                continue;
            }

            if(i == 0) {
                
                temp->buren[6] = vorige;
                vorige->buren[2] = temp;

                vorige = temp;
                continue;
            }
            
            if(j == mapgrootte - 1) {
                temp->buren[6] = vorige;
                vorige->buren[2] = temp;
                
                temp->buren[7] = linksboven;
                linksboven->buren[3] = temp;
                
                temp->buren[0] = boven;
                boven->buren[4] = temp;

                continue;
            }

            temp->buren[6] = vorige;
            vorige->buren[2] = temp;

            
            temp->buren[7] = linksboven;
            linksboven->buren[3] = temp;

            
            temp->buren[0] = boven;
            boven->buren[4] = temp;

            temp->buren[1] = rechtsboven;
            rechtsboven->buren[5] = temp;
            
            vorige = temp;
            linksboven = boven;
            boven = rechtsboven;
            rechtsboven = rechtsboven->buren[2];
        }

        boven = rijIngang;
        rechtsboven = boven->buren[2];

        cout << endl;
    }
}