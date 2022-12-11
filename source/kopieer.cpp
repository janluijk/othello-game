#include <iostream>
#include <main.h>
#include <othellobord.h>


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