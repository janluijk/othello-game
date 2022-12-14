#include <iostream>
#include <othellobord.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
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

Bordvakje::Bordvakje() {
    kleur = '.';
    for (int i = 0; i < 8; i++) {
        buren[i] = nullptr;
    }
}

Bordvakje::~Bordvakje() {
    for (int i = 0; i < 8; i++) {
        buren[i] = nullptr;
    }
}


// Handige functies
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

void Othellobord::draaiSpeler() {       // Speler wordt tegenstander
    char tempSpeler;
    bool tempBot;

    tempSpeler = Speler1; // Speler 1 is altijd de huidige speler
    Speler1 = Speler2;
    Speler2 = tempSpeler;

    tempBot = Bot1;
    Bot1 = Bot2;
    Bot2 = tempBot;
}

Bordvakje* Othellobord::elementPtr(Vec2 pos) { // positie naar pointer
    Bordvakje* huidige = Ingang;

    for (int i = 1; i < pos.x; i++) {
        if(huidige->buren[2]!= nullptr) {
            huidige = huidige->buren[2];

        }
    }
    for (int j = 1; j < pos.y; j++) {
        if(huidige->buren[4] != nullptr) {
            huidige = huidige->buren[4];
        }
    }
    return huidige;   
}

void Othellobord::maakKopie(Othellobord*  kopie) { // kopie van bord en gelinkt
    Bordvakje* omlaag = Ingang; // Functie is zelfde als afdrukken() maar kopieert waarden
    Bordvakje* rechts;

    // is er een manier om vec2 meteen in argument van functie te initialiseren?
    Bordvakje* kopieOmlaag = kopie->Ingang;
    Bordvakje* kopieRechts;
    
    while(omlaag != nullptr) {
        rechts = omlaag;
        kopieRechts = kopieOmlaag; 
        while(rechts != nullptr) {

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

void Othellobord::zetSteen(Vec2 positie, char kleur) { // zet 1 steen en doe verder niks
    Bordvakje* posPtr;
    posPtr  = elementPtr(positie);
    
    posPtr->kleur = kleur;
}

void Othellobord::trekLijn(int richting, int stappen, Bordvakje* huidigPtr) { // draai stenen tussen twee punten

    huidigPtr->kleur = Speler1;
    int terug = (richting + 4) % 8; // Richting terug
    for (int i = 0; i < stappen; i++) {
        huidigPtr->kleur = Speler1;
        huidigPtr = huidigPtr->buren[terug];
    }

}



// Winnen en toekomst
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

char Othellobord::winnen() {            // Wat als gewonnen
    char winnaar = isSpelOver();

    if(winnaar) {
        
        if(!Bot1 || !Bot2) {
            leegTerminal();
            afdrukken();
        }
        SpelIsOver = true;
    }
    return winnaar;
}

char Othellobord::isSpelOver() {        // is spel afgelopen
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

int Othellobord::aantalVervolgzetten() { // Returnt aantal vervolgzetten
    Vec2 positie;
    int mogelijkeZetten = 0;

    for (int y = 1; y <= Hoogte; y++) {
        positie.y = y; 
        for (int x = 1; x <= Lengte; x++) {
            positie.x = x;
            

            if(isZetMogelijk(DoeZetNiet, positie)) {
                
                
                mogelijkeZetten++;
                // Maak nieuw bord aan
                
                Othellobord kopie(Lengte, Hoogte, Speler1, Speler2, Bot1, Bot2);
                maakKopie(&kopie);
                // Doe de zet
                // Een speedup is hier wel mogelijk
                kopie.isZetMogelijk(DoeZetWel, positie);


                kopie.draaiSpeler();
                mogelijkeZetten += kopie.aantalVervolgzetten();
            }
        }
    }
    return mogelijkeZetten;
}

bool Othellobord::isZetMogelijk(bool doeZet, Vec2 beginPositie) { // is zet mogelijk
    int stappen;
    Bordvakje* beginPtr = elementPtr(beginPositie); // Pointer naar vakje wordt nog opgeslagen
    Bordvakje* huidigPtr;
    char huidigKleur;
    bool nietMogelijk;
    bool zetIsMogelijk = false;

    if(beginPtr->kleur == Speler1 || beginPtr->kleur == Speler2) {
        return zetIsMogelijk;
    }

    for (int richting = 0; richting < 8; richting++) {
        stappen = 1;
        huidigPtr = beginPtr;
        nietMogelijk = false;
        
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

        if(nietMogelijk) { continue; }
        if(huidigKleur == Speler1 && stappen > 1) {
            zetIsMogelijk = true;
            if(doeZet) {
                trekLijn(richting, stappen, huidigPtr);
            }
        }
    }
    return zetIsMogelijk;
}



// Zet functies
bool Othellobord::spelerOpties(char letterKeuze) { // Geeft aantal opties als bv. ongedaan maken

    switch (letterKeuze)
    {
    case 'U':
    case 'u':
        Undo = true;
        return true;
        break;
    case 'S':
    case 's': 
        SpelIsOver = true;
        Vervolgpartijen = 0; 
        return true;
    case 'A':
    case 'a':
        cout << "Er zijn " << telMogelijkeZetten() << " mogelijke zetten." << endl;
        break;
    case 'V':
    case 'v':
        cout << aantalVervolgzetten() << endl;
    default:
        return false;
    }
    return false;
}

void Othellobord::randomZet() {         // Computer speelt random zet
    Vec2 positie;
    bool zetIsMogelijk = false;
    while(!zetIsMogelijk) {
        int random = rand();
        positie.x = (random % Lengte) + 1;
        random = rand();
        positie.y = (random % Hoogte) + 1;

        zetIsMogelijk = isZetMogelijk(DoeZetWel, positie);
    }
}

void Othellobord::spelerZet() {         // Speler speelt zet
    char letterKeuze;
    int getalKeuze;
    
    // Variablen voor zet
    Vec2 zet;
    bool zetIsMogelijk;

    while(!zetIsMogelijk) {
        cout << "Geef x-coordinaat: " << endl;
        
        krijgInvoer(letterKeuze, getalKeuze);
        if(getalKeuze) { zet.x = getalKeuze; }
        if(spelerOpties(letterKeuze)) { return; }
        getalKeuze = 0;
        letterKeuze = '.';

        cout << "Geef y-coordinaat: " << endl;
        
        krijgInvoer(letterKeuze, getalKeuze);
        if(getalKeuze) { zet.y = getalKeuze; }
        if(spelerOpties(letterKeuze)) { return; }
        getalKeuze = 0;
        letterKeuze = '.';


        zetIsMogelijk = isZetMogelijk(DoeZetWel, zet);
        
        if(!zetIsMogelijk) {
            cout << "de zet was niet mogelijk, voer juiste coordinaten in!" << endl;
        }
    }
}

int Othellobord::recursiefBesteZet(int iteraties) {
    Vec2 positie;
    int aantalZetten = 0;

    

    int aantalGoedeZetten = 0;

    int aantalIteraties = iteraties;
    int maxIteraties = 4;
    
    int minimum = 32768; // Groot getal zonder betekenis 
    int maximum = 0;

    for (int y = 1; y <= Hoogte; y++) {
        positie.y = y; 
        for (int x = 1; x <= Lengte; x++) {
            positie.x = x;

            if(isZetMogelijk(DoeZetNiet, positie)) {
                aantalZetten++;
                // Maak nieuw bord aan
                
                Othellobord kopie(Lengte, Hoogte, Speler1, Speler2, Bot1, Bot2);
                maakKopie(&kopie);
 
                kopie.isZetMogelijk(DoeZetWel, positie);

                if(aantalIteraties < maxIteraties) {
                    aantalIteraties++;
                    
                    kopie.draaiSpeler();

                    aantalZetten = kopie.recursiefBesteZet(aantalIteraties);
                    
                    aantalIteraties--;

                    if(aantalIteraties % 2 == 0) {
                        maximum = max(aantalZetten, maximum);
                        aantalZetten = maximum;
                    }
                    else {
                        minimum = min(aantalZetten, minimum);
                        aantalZetten = minimum;
                        if(!aantalIteraties ) {
                            if(aantalGoedeZetten < 10) {
                                goedeZetten[aantalGoedeZetten] = positie;
                                aantalGoedeZetten++; 
                            }
                        }
                    }
                }
            }
        }
    }
    while(!aantalIteraties && aantalGoedeZetten < 10) {
        goedeZetten[aantalGoedeZetten] = goedeZetten[1];
        aantalGoedeZetten++; 
    }

    return aantalZetten;
}



// Init functions
void Othellobord::startPositie() {      // Zet startpositie
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

void Othellobord::krijgParameters() {   // Parameters constructor
    char keuze;

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
    Lengte = krijgGetal();

    cout << "\n De hoogte van de map wordt: \n: ";
    Hoogte = krijgGetal();

    if(Bot1 && Bot2) {
        cout << "Hoeveel vervolgpartijen wil je spelen? \n: ";
        
        Vervolgpartijen = krijgGetal();
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
            
            if(vorige != nullptr) { // Als er een vakje voor zit, dan linken
                temp->buren[6] = vorige;
                vorige->buren[2] = temp;
            }
            if(linksboven != nullptr) { // Als er een vakje linksboven zit...
                temp->buren[7] = linksboven;
                linksboven->buren[3] = temp;
            }
            if(boven != nullptr) {
                temp->buren[0] = boven;
                boven->buren[4] = temp;
            }
            if(rechtsboven != nullptr) {
                temp->buren[1] = rechtsboven;
                rechtsboven->buren[5] = temp;
            }                

            // Na het linken: 
            vorige = temp;
            if(boven != nullptr) {
                linksboven = boven;
            }
            if(rechtsboven != nullptr) {
                boven = rechtsboven;
                if(rechtsboven->buren[2] != nullptr) {
                    rechtsboven = rechtsboven->buren[2];
                }
                else {
                    rechtsboven = nullptr;
                }
            }
        } // Na iedere rij:
        vorige = nullptr;
        linksboven = nullptr;
        boven = rijIngang;
        rechtsboven = boven->buren[2];
    }
}

void Othellobord::simulatieSpel() {
    int spelTeller = 0;
    startPositie();
    string uitvoer = "uitvoer.txt";
    char winnaar;
    bool beurt = false;

    ofstream output(uitvoer);

    while(Vervolgpartijen >= spelTeller) {
        //randomZet();
        if(beurt) {
            beurt = false;
            randomZet();
        }
        else {
            beurt = true;
            recursiefBesteZet(0);
            isZetMogelijk(DoeZetWel, goedeZetten[rand() % 10]);
        }

        //leegTerminal();
        //afdrukken();

        draaiSpeler();
        winnaar = winnen();

        if(SpelIsOver) {
            output.put(winnaar);
            spelTeller++;
            SpelIsOver = false; 
            startPositie();
        }
    }
}

void Othellobord::menuSpel() {          // Menu
    int spelTeller = 0;
    startPositie();

    Othellobord* huidig = this;
    Othellobord* temp;


    while(huidig->Vervolgpartijen >= spelTeller) {
        Othellobord* kopie = new Othellobord(huidig->Lengte, huidig->Hoogte, huidig->Speler1, huidig->Speler2, huidig->Bot1, huidig->Bot2);
        huidig->maakKopie(kopie);

        leegTerminal();
        huidig->afdrukken();
        cout << "toets 'U' voor ongedaan maken" << endl <<
                    "toets 'A' voor het aantal mogelijke zetten" << endl <<
                    "toets 'S' om te stoppen met het spel" << endl <<
                    "toets 'V' voor het aantal vervolgstappen" << endl <<
                    "--" << huidig->Speler1 << "--" << endl;
        
        if(huidig->Bot1) {  
            cout << "Computer denkt na..." << endl;

            //recursiefEvaluatie(0);
            //speelBesteZet();

            kopie->randomZet();
        }
        else {
            kopie->spelerZet(); 
        }

        if(SpelIsOver) {
            spelTeller++;
            SpelIsOver = false;
            kopie->startPositie();
        }
        else {
            if(kopie->Undo && huidig->vorige != nullptr) {
                huidig = huidig->vorige;
                kopie->Undo = false;
            }
            else {
                kopie->draaiSpeler();
                kopie->winnen();

                temp = huidig;
                huidig = huidig->volgende;
                huidig->vorige = temp;
            }
        }
    }
}

Othellobord::Othellobord() {            // Default constructor
    Speler1 = 'z';
    Speler2 = 'w';

    srand(time(NULL));
    krijgParameters();
    ritsMap();

    vorige = nullptr;
    volgende = nullptr;
}

Othellobord::Othellobord(int lengte, int hoogte, char speler1, char speler2, bool bot1, bool bot2) {
    Lengte = lengte;
    Hoogte = hoogte;

    Speler1 = speler1;
    Speler2 = speler2;

    Bot1 = bot1;
    Bot2 = bot2;

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



*/