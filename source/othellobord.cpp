#include <iostream>
#include <othellobord.h>
using namespace std;

// TODO


/*

Initialiseer bord perfect: customisable met grootte
fix: - Bots
fix: - Beurt
fix: - isZetMogelijk
fix: - DoeZet
fix: - aantalZetten
fix: - aantalStenen
fix: - winnen

doeRandomZet
Vervolgzetten
SlimmeZet
Undo
Grafiek

bord
while(1) {
    speler1.zet
    speler2.zet
    winnen
}



main() {
    maakBord(lijst_van_parameters);
    constructor_bord(parameters);
    
    memberfuncties:

}






*/





// Verwijderen -> constructor
Bordvakje* Othellobord::elementPtr(Vec2 pos) { 
    
    int diagonaalStap; 
    int rechtStap;
    bool omlaag = false;

    pos.x--; // Array start op 0, coordinaten start op 1!
    pos.y--;

    // Er wordt hier wat meer moeite gedaan om in MINIMALE aantal zetten
    // bij bestemming te komen
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
void Othellobord::trekLijn(int richting, int counter, char kleur, Bordvakje* huidig) {
    int terug = (richting + 4) % 8;
    for (int i2 = 0; i2 < counter; i2++) {
        huidig->kleur = kleur;
        huidig = huidig->buren[terug];
    }

}
void Othellobord::speelZet(Vec2 pos, char kleur, int richting, int stappen, Bordvakje* huidigPtr) {
    zetSteen(pos, kleur);
    trekLijn(richting, stappen, kleur, huidigPtr);
}
void Othellobord::zetSteen(Vec2 positie, char kleur) {
    Bordvakje* posPtr;
    posPtr  = elementPtr(positie);
    
    posPtr->kleur = kleur;
}
bool Othellobord::isZetMogelijk(Vec2 positie, char kleur, bool doeZet) {
    Bordvakje* vakPtr = elementPtr(positie); // Pointer naar vakje wordt nog opgeslagen
    Bordvakje* huidig = vakPtr; 
    char kleurVijand = 'z';
    char huidigKleur;
    int stappen = 0;
    bool zetIsMogelijk = false;
    bool uitWhileLoop = false;

    if(kleur == 'z') {
        kleurVijand = 'w';
    }

    if(vakPtr->kleur == kleur || vakPtr->kleur == kleurVijand) {
        return zetIsMogelijk;
    }
    for (int richting = 0; richting < 8; richting++) {
        stappen = 0;

        if(!(huidig->buren[richting])) {
            continue;
        }
        huidigKleur = huidig->buren[richting]->kleur;

        while(huidigKleur == kleurVijand) {
            stappen++;
            
            huidig = huidig->buren[richting];
            
            if(!(huidig->buren[richting])) {
                huidig = vakPtr;
                richting++;
                break;
            } 
            huidigKleur = huidig->buren[richting]->kleur;
        }
        if(uitWhileLoop) {
            continue;
        }

        if(huidigKleur == kleur && stappen) {
            zetIsMogelijk = true;
            if(doeZet) {
                zetSteen(positie, kleur);
                trekLijn(richting, stappen, kleur, huidig);
            }
        }
        else {
            if(stappen) {
                huidig = vakPtr;
            }
        }

    }
    
    return zetIsMogelijk;
}
int Othellobord::recursiefEvaluatie(int iteraties) {
    Vec2 huidig; // 
    int score = 0; //Score wordt bepaald door het aantal mogelijke zetten
    int teller = 0;

    int aantalItteraties = iteraties;
    int maxIteraties = 5;
    //if(mogelijkheden) {
    //    maxIteraties = 100;
    //}

    bool nogVerder = true;
    
    int minimum = 32768; // Groot getal zonder betekenis 
    int maximum = 0;
    
    if(aantalItteraties == maxIteraties) {
        nogVerder = false;
    }

    for (int y = 1; y <= Hoogte; y++) {
        huidig.y = y; 
        for (int x = 1; x <= Lengte; x++) {
            huidig.x = x;

            if(isZetMogelijk(huidig, Beurt, ZetNiet)) {
                teller++;
                // Maak nieuw bord aan
                
                Othellobord kopie;
                maakKopie(kopie);
 
                // Doe de zet
                // Een speedup is hier wel mogelijk
                kopie.isZetMogelijk(huidig, Beurt, ZetWel);
                // Evualuatie:
                // Het aantal zetten is de maat voor de kwaliteit van een zet
                // Daarom wordt met score het aantal mogelijke zetten bijgehouden
                score++;
                if(nogVerder) {
                    aantalItteraties++;
                    draaiBeurt();
                    kopie.Beurt = Beurt;
                    draaiBeurt();
                    score = kopie.recursiefEvaluatie(aantalItteraties);
                    kopie.verwijderen();
                    aantalItteraties--;

                    if(aantalItteraties % 2) {
                        maximum = max(score, maximum);
                        score = maximum;
                    }
                    else {
                        minimum = min(score, minimum);
                        score = minimum;
                        if(!aantalItteraties) {
                            BesteZet = huidig;
                        }
                    }
                }
            }
        }
    }
    return score;
}

// Basisfuncties
bool Othellobord::spelerZet() {
    char letterKeuze;
    int getalKeuze;
    Vec2 zetPositie;

    // Invoeren van coordinaten:
    cout << "Geef x-coordinaat: " << endl;
    krijgInvoer(letterKeuze, getalKeuze);
    if(getalKeuze) {
        zetPositie.x = getalKeuze;
    }
    if(verwerkInvoer(letterKeuze)) {
        return 1;
    };
    getalKeuze = 0;
    letterKeuze = '.';

    cout << "Geef y-coordinaat: " << endl;
    krijgInvoer(letterKeuze, getalKeuze);
    if(getalKeuze) {
        zetPositie.y = getalKeuze;
        isZetMogelijk(zetPositie, Beurt, true);
    }
    if(verwerkInvoer(letterKeuze)) {
        return 1;
    }
    getalKeuze = 0;
    letterKeuze = '.';

    // Winnen

    draaiBeurt();
    leegTerminal();
    afdrukken();
    return 0;
}
int  Othellobord::winnen() {             // Heeft speler gewonnen
    Vec2 huidig;
    Vec2 stenen = {0, 0}; // Zwart = x, Wit = y
    Bordvakje* huidigPtr;

    for (int y = 1; y <= Hoogte; y++) {
        huidig.y = y; 
        for (int x = 1; x <= Lengte; x++) {
            huidig.x = x;

            if(isZetMogelijk(huidig, Beurt, ZetNiet)) {
                return 0; // Niet gewonnen
            }

            huidigPtr = elementPtr(huidig);
            if(huidigPtr->kleur == 'z') {
                stenen.x++;
            }
            else if (huidigPtr->kleur == 'w') {
                stenen.y++;
            }
            
        }
    }
    if(stenen.x > stenen.y) {
        return 1; // Zwart wint
    }
    if(stenen.y < stenen.x) {
        return 2; // Wit wint
        cout << "e" << endl;
    }
    if (stenen.x == stenen.y){
        return 3; // Remise
    }
    else {
        return 0;
    }
}
int  Othellobord::telMogelijkeZetten() { // Hoeveel zetten speelbaar 
    Vec2 huidig;
    int aantalZetten = 0;

    for (int y = 1; y <= Hoogte; y++) {
        huidig.y = y; 
        for (int x = 1; x <= Lengte; x++) {
            huidig.x = x;
            if(isZetMogelijk(huidig, Beurt, ZetNiet)) {
                aantalZetten++;
            }
        }
    }
    return aantalZetten;
}
void Othellobord::verwijderen() {        // Verwijderen
Bordvakje* p = ingang;
    Bordvakje* q = ingang;
    Bordvakje* temp;

    while(q != nullptr) {
        q = q->buren[4];
        while(p != nullptr) {
            temp = p->buren[2];
            for (int i = 0; i < 8; i++)
            {
                p->buren[i] = nullptr;
            }
            delete p;
            p = temp;
        }
        p = q;
    }
}
void Othellobord::afdrukken() {          // Afdrukken
    Bordvakje* omlaag = ingang;
    Bordvakje* rechts;
 
    while(omlaag) {
        rechts = omlaag;
        while(rechts) {
            cout << (rechts->kleur) << " | ";
            rechts = rechts->buren[2];
        }
        cout << "\n";
        omlaag = omlaag->buren[4];
    }
}
void Othellobord::draaiBeurt() {         // Speler wordt tegenstander
    if(Beurt == 'z') {
        Beurt = 'w';
        BeurtTegenstander = 'z';
        return;
    }
    Beurt = 'z';
    BeurtTegenstander = 'w';
    return;
}
void Othellobord::speelBesteZet() {      // speelt goede zet
    isZetMogelijk(BesteZet, Beurt, true); 
}
void Othellobord::randomZet() {}         // Zet random zet
Vec2 Othellobord::krijgCoordinaten() {   // Coordinaten van 
    Vec2 position; 
    char keuze;
    int getal;

    cout << "Geef het eerste coordinaat (x) ";
    while(!getal) {
        krijgInvoer(keuze, getal);
    }
    position.x = getal;

    cout << "Geef het tweede coordinaat (y) ";
    while(!getal) {
        krijgInvoer(keuze, getal);
    }
    position.y = getal;

    return position;
}




// Menufuncties
void Othellobord::menuSpel() {

    while(1) {
        leegTerminal();
        afdrukken();
        cout << "toets 'U' voor ongedaan maken" << endl <<
                "toets 'A' voor het aantal mogelijke zetten" << endl <<
                "toets 'S' om te stoppen met het spel" << endl <<
                "-- ZWART" << endl;
        if(Bot1) {
            cout << "Computer denkt na..." << endl;
            recursiefEvaluatie(0);
            speelBesteZet();
            afdrukken();
            draaiBeurt();
            // Winnen
        }
        else {
            spelerZet();
            
        }
        leegTerminal();
        afdrukken();
        cout << "--WIT--" << endl;
        if(Bot2) {
            cout << "Computer denkt na...";
            recursiefEvaluatie(0);
            speelBesteZet();
            afdrukken();
            draaiBeurt();
            // Winnen
            
        }
        else {
            // Spelerzet      
        }
    }
}
bool verwerkInvoer(char letterKeuze) {
    switch (letterKeuze)
    {
    case 'U':
    case 'u':
        //maakOngedaan();
        break;
    case 'S':
    case 's':
        cout << "Het spel stopt...";
        return 1;
    case 'A':
    case 'a':
        int aantal = 1;
        //aantal = telMogelijkeZetten();
        cout << "Er zijn " << aantal << " mogelijke posities." << endl;
        break;
    case '.':
        break;
    default:
        break;
    }
    return 0;
}




// Beginfuncties
void Othellobord::ritsMap() {
    Bordvakje* rijIngang = nullptr;
    Bordvakje* boven = nullptr;
    Bordvakje* rechtsboven = nullptr;
    Bordvakje* linksboven = nullptr;
    Bordvakje* vorige = nullptr;

    for (int i = 0; i < Hoogte; i++) {
        for (int j = 0; j < Lengte; j++) {

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
void Othellobord::maakKopie(Othellobord & kopie) {
    Bordvakje* omlaag = ingang; // Functie is zelfde als afdrukken() maar kopieert waarden
    Bordvakje* rechts;

    // is er een manier om vec2 meteen in argument van functie te initialiseren?
    Vec2 begin = {1, 1};
    Bordvakje* kopieOmlaag = kopie.elementPtr(begin);
    Bordvakje* kopieRechts;
    
    while(omlaag) {
        rechts = omlaag;
        kopieRechts = kopieOmlaag; 
        while(rechts) {

            kopieRechts->kleur = rechts->kleur;

            rechts = rechts->buren[2];
            kopieRechts = kopieRechts->buren[2];
        }
        omlaag = omlaag->buren[4];
        kopieOmlaag = kopieOmlaag->buren[4];
    }
}





// Input van speler
void Othellobord::krijgZet() {
    Vec2 positie;
    char kleur = Beurt;
    bool doeZet = true;

    positie = krijgCoordinaten();
    if(!isZetMogelijk(positie, kleur, doeZet)) {
        cout << "Zet is niet mogelijk!" << endl;
    }
    else {
        draaiBeurt();
    }
}