#include <iostream>
#include <othellobord.h>
#include <main.h>

using namespace std;

int hoofdMenu(Othellobord & othellobord) {
    char keuze;
    do {
        cout << "Kies uit: [s]toppen, " << endl
             << "          [a]fdrukken, [z]etten" << endl
             << "Uw keuze: ";
        cin >> keuze;
        switch (keuze)
        {
        case 's':
        case 'S':
            cout << "Dat was het dan ..." << endl;
            break;
        case 'a':
        case 'A':
            othellobord.afdrukken();
            break;
        case 'l':
        case 'L':
            break;
        case 'z':
        case 'Z':
            othellobord.krijgZet();
            leegTerminal();
            othellobord.afdrukken();
            break;
        default:
            cout << "Niet toegestane menukeuze ..." << endl;
        } // switch
    }     // do 
    while( !(keuze == 's') && !(keuze == 'S'));

    return 1;
}

int kopieerMap(Othellobord &othellobord, Othellobord &kopie) {
    Bordvakje* othIngang   = othellobord.elementPtr( (Vec) {1, 1} );
    Bordvakje* kopieIngang = kopie.elementPtr( (Vec) {1, 1});

    Bordvakje* othOmlaagptr = othIngang;
    Bordvakje* othRechtsptr;

    Bordvakje* kopieOmlaagptr = kopieIngang;
    Bordvakje* kopieRechtsptr;
 
    while(othOmlaagptr) {
        othRechtsptr = othOmlaagptr;
        kopieRechtsptr = kopieOmlaagptr;

        while(othRechtsptr) {
            kopieRechtsptr->kleur = othRechtsptr->kleur;
            othRechtsptr = othRechtsptr->buren[2];
        }
        othOmlaagptr = othOmlaagptr->buren[4];
        kopieOmlaagptr = kopieOmlaagptr->buren[4];
    }
}

void gaZettenAf(char kleur, Othellobord & othellobord, Othellobord & kopie) {
    Vec positie = {0, 0};
    for (int i = 0; i < 8; i++) {
        positie.x = i;
        for (int j = 0; j < 8; j++) {
            positie.y = j;
            if(othellobord.isZetMogelijk(positie, kleur, 0)) {
                kopieerMap(othellobord, kopie);
                kopieerMap.isZetMogelijk(positie, kleur, 1);
                aantalMogelijkeZetten(kopie);
            }   
        }   
    }
}

int main() {
    Othellobord othellobord;
    Othellobord kopie;

    hoofdMenu(othellobord);
    
    return 0;
}