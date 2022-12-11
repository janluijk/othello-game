#include <iostream>
#include "othellobord.h"
#include "main.h"

using namespace std;
// Private
Bordvakje* Othellobord::elementPtr(Vec2 pos) {
    
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

// Zal waarschijnlijk niet werken bij elementen uit eerste kolom naar rechtsboven!
void Othellobord::ritsMap() {
    Bordvakje* rijIngang;
    Bordvakje* boven = nullptr;
    Bordvakje* rechtsboven = nullptr;
    Bordvakje* linksboven = nullptr;
    Bordvakje* vorige = nullptr;

    for (int i = 0; i < mapgrootte; i++) {
        for (int j = 0; j < mapgrootte; j++) {

            Bordvakje* temp = new Bordvakje; // Nieuw vakje wordt aangemaakt

            if(!i && !j) { // Eerste vakje wordt ingang
                ingang = temp;
            }
            
            
            if(!j) { // Iedere volgende rij wordt de pointer naar het eerste element opgeslagen
                rijIngang = temp;
            }
            
            if(vorige) { // Als er een vakje voor zit, dan linken
                temp->buren[6] = vorige;
                vorige->buren[2] = temp;
            }
            if(linksboven) { // Als er een vakje linksboven zit...
                temp->buren[7] = linksboven;
                linksboven->buren[3] = temp;
            }
            if(boven) {
                temp->buren[0] = boven;
                boven->buren[4] = temp;
            }
            if(rechtsboven) {
                temp->buren[1] = rechtsboven;
                rechtsboven->buren[5] = temp;
            }                

            // Na het linken: 
            vorige = temp;
            if(boven) {
                linksboven = boven;
            }
            if(rechtsboven) {
                boven = rechtsboven;
                if(rechtsboven->buren[2]) {
                    rechtsboven = rechtsboven->buren[2];
                }
            }
        } // Na iedere rij:

        vorige = nullptr;
        boven = rijIngang;
        rechtsboven = boven->buren[2];
    }
}



// Public
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

Vec2 Othellobord::krijgCoordinaten() {
    Vec2 position; 
    cout << "Geef het eerste coordinaat (x) ";
    position.x = krijgGetal();
    cout << "Geef het tweede coordinaat (y) ";
    position.y = krijgGetal();
    return position;
}
char Othellobord::krijgKleur() {
    char kleur; 
    
    while (1)
    {
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
                cout << "Geef een juist karakter op svp" << endl;
                break;
        }

    }
    
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
void Othellobord::krijgZet() {
    Vec2 positie;
    char kleur;
    bool zetSteen = true;

    positie = krijgCoordinaten();
    kleur   = krijgKleur();
    zetSteen(positie, kleur);
    isZetMogelijk(positie, kleur, zetSteen);
}

void Othellobord::zetSteen(Vec2 positie, char kleur) {
    Bordvakje* posPtr;
    posPtr  = elementPtr(positie);
    
    posPtr->kleur = kleur;
}
bool Othellobord::isZetMogelijk(Vec2 positie, char kleur, bool zetSteen = false) {
    Bordvakje* vakPtr = elementPtr(positie); // Pointer naar vakje wordt nog opgeslagen
    Bordvakje* huidig = vakPtr; 
    char kleurVijand;
    char huidigKleur;
    int counter = 0;

    for (int richting = 0; richting < 8; richting++) {
        counter = 0;
        if(!huidig->buren[richting]) {
            continue;
        }

        huidigKleur = huidig->buren[richting]->kleur;
        
        while(huidigKleur == kleurVijand) {
            counter++;
            cout << counter << endl;

            huidig = huidig->buren[richting];    
            huidigKleur = huidig->buren[richting]->kleur;
        }

        if(huidigKleur == kleur && counter) {
            // Zet is mogelijk
            // Op een of andere manier de zet opslaan
            
            if(zetSteen) {
                trekLijn(richting, counter, kleur, huidig);
            }
            else {
                return true;
            }
        }
        else {
            cout << "test" << endl;
            if(counter) {
                huidig = vakPtr;
            }
            continue;
        }
    }
}
void Othellobord::trekLijn(int richting, int counter, char kleur, Bordvakje* huidig) {
    int terug = (richting + 4) % 8;
    for (int i2 = 0; i2 < counter; i2++) {
        huidig->kleur = kleur;
        huidig = huidig->buren[terug];
    }

}

// Structuur minmax:
void Othellobord::kopieerMap();
void Othellobord::gaZettenAf() {
    
    for (int i = 0; i < mapgrootte; i++)
    {
        for (int j = 0; j < mapgrootte; j++)
        {
            kopie.isZetMogelijk();
            kopie.evalueerZet(); // Hoeveel zetten zijn er mogelijk na de zet
            gaZettenAf();

             

        }
        
    }
    
}