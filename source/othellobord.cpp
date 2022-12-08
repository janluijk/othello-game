#include <iostream>
#include <othellobord.h>
using namespace std;

void Othellobord::afdrukken(Bordvakje *ingang) {
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


// Acces nth element
void Othellobord::getElementPtr(int pos_x, int pos_y, Bordvakje* ingang) {
    
    int diagonaalStap; 
    int rechtStap;
    bool omlaag = false;

    if(pos_x < pos_y) {
        diagonaalStap = pos_x;
        rechtStap = pos_y - pos_x;
        omlaag = true;
    }
    else {
        diagonaalStap = pos_y;
        rechtStap = pos_x - pos_y;
    }

    Bordvakje* huidige;

    for (int i = 0; i < diagonaalStap; i++) {
        if(huidige) {
            huidige = huidige->buren[3];
        }
        else {
            return 1;
        }
    }
    for (int i = 0; i < rechtStap; i++) {
        if(huidige) {
            if() {

            }
        }
    }
    
}

Bordvakje* Othellobord::ritsMap() {
    
    Bordvakje* hoofdIngang;
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
                hoofdIngang = temp;
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
    return hoofdIngang;
}


