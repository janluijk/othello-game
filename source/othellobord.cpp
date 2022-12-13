#include <iostream>
#include <othellobord.h>
#include <cstdlib>
using namespace std;

// TODO


/*

Initialiseer bord perfect: customisable met grootte
fix: - aantalZetten
fix: - aantalStenen
fix: - constructors
fix: - destructors

Vervolgzetten
SlimmeZet
Undo
Grafiek

*/

void Othellobord::maakOngedaan() {
    // Ga terug naar vorige
    delete this;

    // delete
}

void Othellobord::maakKopie(Othellobord*  kopie) {
    Bordvakje* omlaag = Ingang; // Functie is zelfde als afdrukken() maar kopieert waarden
    Bordvakje* rechts;

    // is er een manier om vec2 meteen in argument van functie te initialiseren?
    Vec2 begin = {1, 1};
    Bordvakje* kopieOmlaag = kopie->elementPtr(begin);
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
    volgende = kopie;
    kopie->vorige = volgende;
}

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

    Bordvakje* huidige = Ingang;

    for (int i = 0; i < diagonaalStap; i++) {
        if(huidige) {
            huidige = huidige->buren[3];
        }
        else {
            return nullptr;
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
                return nullptr;
            }
        }
    }
    return huidige;   
}

Vec2 Othellobord::ptrNaarPos(Bordvakje* posPtr) {
    Vec2 position = {0, 0};

    while (posPtr->buren[6] != nullptr)
    {
        position.x++;
        posPtr = posPtr->buren[6];
    }
    while (posPtr->buren[0] != nullptr)
    {
        position.y++;
        posPtr = posPtr->buren[0];
    }
    return position;
}

void Othellobord::winnen() {            // Heeft speler gewonnen
    char winnaar = isSpelOver();

    if(winnaar) {
        leegTerminal();
        afdrukken();
        cout << "Speler "<< winnaar << " heeft gewonnen!" << endl;
        SpelIsOver = true;
    }
}

void Othellobord::draaiSpeler() {         // Speler wordt tegenstander
    char tempSpeler;
    bool tempBot;

    tempSpeler = Speler1; // Speler 1 is altijd de huidige speler
    Speler1 = Speler2;
    Speler2 = tempSpeler;

    tempBot = Bot1;
    Bot1 = Bot2;
    Bot2 = tempBot;
}

char Othellobord::isSpelOver() {
    int stenenSpeler1 = 0;
    int stenenSpeler2 = 0;
    int maxStenen;
    Bordvakje* posPtr;
    
    // zet
    Vec2 positie;
    bool zetIsMogelijk = false;
   

    for (int y = 1; y <= Hoogte; y++) {
        positie.y = y; 
        for (int x = 1; x <= Lengte; x++) {
            positie.x = x;
            zetIsMogelijk = isZetMogelijk(DoeZetNiet, positie);
            if(zetIsMogelijk) {
                return 0;
            }
            posPtr = elementPtr(positie);
            if(posPtr->kleur == Speler1) {
                stenenSpeler1++;
            }
            else if(posPtr->kleur == Speler2) {
                stenenSpeler2++;
            }
        }
    }
    maxStenen = max(stenenSpeler1, stenenSpeler2);
    if(maxStenen == stenenSpeler1) { return Speler1; }
    else { return Speler2; }
}

int  Othellobord::telMogelijkeZetten() { // Hoeveel zetten speelbaar 
    int aantalZetten = 0;
    
    // zet
    Vec2 positie;
   

    for (int y = 1; y <= Hoogte; y++) {
        positie.y = y; 
        for (int x = 1; x <= Lengte; x++) {
            positie.x = x;
            if(isZetMogelijk(DoeZetNiet, positie)) {
                aantalZetten++;
            }
        }
    }
    return aantalZetten;
}

void Othellobord::spelerOpties(char letterKeuze) {
    switch (letterKeuze)
    {
    case 'U':
    case 'u':
        //maakOngedaan();
        break;
    case 'S':
    case 's':
        cout << "Het spel stopt...";
        SpelIsOver = true;
        Vervolgpartijen = 0;
        return;
    case 'A':
    case 'a':
        int aantal;
        aantal = telMogelijkeZetten();
        cout << "Er zijn " << aantal << " mogelijke posities." << endl;
        break;
    default:
        break;
    }
}

void Othellobord::spelerZet() {
    char letterKeuze;
    int getalKeuze;
    
    // Variablen voor zet
    Vec2 zet;
    bool zetIsMogelijk;

    
    while(!zetIsMogelijk) {
        cout << "Geef x-coordinaat: " << endl;
        
        krijgInvoer(letterKeuze, getalKeuze);
        if(getalKeuze) { zet.x = getalKeuze; }
        spelerOpties(letterKeuze);
        getalKeuze = 0;
        letterKeuze = '.';

        cout << "Geef y-coordinaat: " << endl;
        
        krijgInvoer(letterKeuze, getalKeuze);
        if(getalKeuze) { zet.y = getalKeuze; }
        spelerOpties(letterKeuze);
        getalKeuze = 0;
        letterKeuze = '.';


        zetIsMogelijk = isZetMogelijk(DoeZetWel, zet);
        
        if(!zetIsMogelijk) {
            cout << "de zet was niet mogelijk, voer juiste coordinaten in!" << endl;
        }
    }
}

void Othellobord::zetSteen(Vec2 positie, char kleur) {
    Bordvakje* posPtr;
    posPtr  = elementPtr(positie);
    
    posPtr->kleur = kleur;
}

void Othellobord::trekLijn(int richting, int stappen, Bordvakje* huidigPtr) {

    huidigPtr->kleur = Speler1;
    int terug = (richting + 4) % 8; // Richting terug
    for (int i = 0; i < stappen; i++) {
        huidigPtr->kleur = Speler1;
        huidigPtr = huidigPtr->buren[terug];
    }

}

bool Othellobord::isZetMogelijk(bool doeZet, Vec2 beginPositie) {
    int stappen;
    Bordvakje* beginPtr = elementPtr(beginPositie); // Pointer naar vakje wordt nog opgeslagen
    Bordvakje* huidigPtr;
    char huidigKleur;
    bool nietMogelijk = false;
    bool zetIsMogelijk = false;

    if(beginPtr->kleur == Speler1 || beginPtr->kleur == Speler2) {
        return zetIsMogelijk;
    }

    for (int richting = 0; richting < 8; richting++) {
        stappen = 1;
        huidigPtr = beginPtr; 

        if(huidigPtr->buren[richting] == nullptr) {
            continue;
        }

        huidigKleur = huidigPtr->buren[richting]->kleur;

        while(huidigKleur == Speler2) {
            stappen++;
            
            huidigPtr = huidigPtr->buren[richting];
            
            if(huidigPtr->buren[richting] == nullptr) {
                nietMogelijk = true;
                break;
            } 
            huidigKleur = huidigPtr->buren[richting]->kleur;
        }

        if(nietMogelijk) {
            continue;
        }

        if(huidigKleur == Speler1 && stappen > 1) {
            zetIsMogelijk = true;
            if(doeZet) {
                trekLijn(richting, stappen, huidigPtr);
            }
        }
    }
    return zetIsMogelijk;
}

void Othellobord::randomZet() {
    Vec2 positie;
    bool zetIsMogelijk = false;
    while(!zetIsMogelijk) {
        int random;
        random = rand();
        positie.x = (random % Lengte) + 1;
        random = rand();
        positie.y = (random % Hoogte) + 1;

        zetIsMogelijk = isZetMogelijk(DoeZetWel, positie);
    }
}

void Othellobord::afdrukken() {         // Afdrukken
    Bordvakje* omlaag = Ingang;
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

void Othellobord::menuSpel() {          // Menu
    int spelTeller = 0;
    startPositie();

    while(Vervolgpartijen >= spelTeller) {
        //Othellobord* kopie;
        //maakKopie(kopie);
        


        
        if(!Bot1 || !Bot2) {
            leegTerminal();
            afdrukken();
            cout << "toets 'U' voor ongedaan maken" << endl <<
                    "toets 'A' voor het aantal mogelijke zetten" << endl <<
                    "toets 'S' om te stoppen met het spel" << endl <<
                    "--" << Speler1 << "--" << endl;
        }
        
        if(Bot1) {
            if(!Bot1 || !Bot2) {
                cout << "Computer denkt na..." << endl;
            }
            //recursiefEvaluatie(0);
            
            //speelBesteZet();
            randomZet();
            
        }
        else {
            spelerZet(); 
        }
        draaiSpeler();
        winnen();
        if(SpelIsOver) { // clever shit
            spelTeller++;
            SpelIsOver = false;
            startPositie();
        }
    }

}

void Othellobord::ritsMap() {           // Pointerstructuur van map
    Bordvakje* rijIngang = nullptr;
    Bordvakje* boven = nullptr;
    Bordvakje* rechtsboven = nullptr;
    Bordvakje* linksboven = nullptr;
    Bordvakje* vorige = nullptr;

    
    for (int i = 0; i < Hoogte; i++) {
        for (int j = 0; j < Lengte; j++) {

            Bordvakje* temp = new Bordvakje; // Nieuw vakje wordt aangemaakt

            if(!i && !j) { // Eerste vakje wordt ingang
                Ingang = temp;
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

void Othellobord::krijgParameters() {   // Parameters constructor
    char keuze;
    int getal;

    cout << "Wie spelen er? Zwart wordt gespeeld door een: \n[Persoon], [Computer] \n:  ";
    keuze = krijgChar();
    
    switch (keuze)
    {
    case 'p':
    case 'P':
        Bot1 = false;
        break;
    case 'c':
    case 'C':
        Bot1 = true;
        break;
    default:
        cout << "Geen geldige waarde opgegeven, standaardwaarde wordt gebruikt!" << endl;
    }

    cout << "\nWit wordt gespeeld door een: \n[Persoon], [Computer], \n:  ";
    keuze = krijgChar();

    switch (keuze)
    {
    case 'p':
    case 'P':
        Bot2 = false;
        break;
    case 'c':
    case 'C':
        Bot2 = true;
        break;
    default:
        cout << "Geen geldige waarde opgegeven, standaardwaarde wordt gebruikt!" << endl;
    }
    
    cout << "Stel nu de mapgrootte in: \nDe lengte van de map wordt: \n: ";
    getal = krijgGetal();
    Lengte = getal; 

    cout << "\n De hoogte van de map wordt: \n: ";
    getal = krijgGetal();
    
    Hoogte = getal;

    if(Bot1 && Bot2) {
        cout << "Hoeveel vervolgpartijen wil je spelen? \n: ";
        
        getal = krijgGetal();
        Vervolgpartijen = getal;
        cout << Vervolgpartijen << endl;
    }
}

void Othellobord::startPositie() {
    Bordvakje* omlaag = Ingang;
    Bordvakje* rechts;
 
    while(omlaag) {
        rechts = omlaag;
        while(rechts) {
            rechts->kleur = '.';
            rechts = rechts->buren[2];
        }
        omlaag = omlaag->buren[4];
    }

    Vec2 positie = {Lengte/2, Hoogte/2};
    zetSteen(positie, Speler2);
    positie.x++;
    zetSteen(positie , Speler1);
    positie.y++;
    zetSteen(positie , Speler2);
    positie.x--;
    zetSteen(positie , Speler1);
}

Othellobord::Othellobord() {            // Default constructor
    Speler1 = 'z';
    Speler2 = 'w';

    krijgParameters();
    ritsMap();

    vorige = nullptr;
    volgende = nullptr;
}

Othellobord::Othellobord(int lengte, int hoogte, char speler1, char speler2) {
    Lengte = lengte;
    Hoogte = hoogte;

    Speler1 = speler1;
    Speler2 = speler2;

    ritsMap();
}

Othellobord::~Othellobord() {           // Destructor
    Bordvakje* rechts = Ingang;
    Bordvakje* omlaag = Ingang;
    Bordvakje* temp;

    while(omlaag != nullptr) {
        omlaag = omlaag->buren[4];
        while(rechts != nullptr) {
            temp = rechts->buren[2];
            for (int i = 0; i < 8; i++)
            {
                rechts->buren[i] = nullptr;
            }
            delete rechts;
            rechts = temp;
        }
        rechts = omlaag;
    }

}

  
/*



void Othellobord::speelZet(Vec2 pos, char kleur, int richting, int stappen, Bordvakje* huidigPtr) {
    zetSteen(pos, kleur);
    trekLijn(richting, stappen, kleur, huidigPtr);
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



void Othellobord::verwijderen() {        // Verwijderen

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





bool spelerOpties(char letterKeuze) {
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
*/