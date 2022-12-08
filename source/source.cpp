#include <iostream>
#include <othellobord.h>
#include <main.h>

using namespace std;

/*
// Class
class Puzzel {
    public:
        Puzzel() { // Constructor
            // Array initialiseren met alle waarden op 0
            for (int y = 0; y < MAX; y++) {
                for (int x = 0; x < MAX; x++) {
                    map[y][x]       = 0; // Array vullen met lampen uit (o)
                    oplossing[y][x] = 0;
                }
            }

            // Mapgrootte
            hoogte  = 5;
            breedte = 5;

            // Cursorvariablen
            cursorX = 0;
            cursorY = 0;
            actieveCursor = 0;

            // Parameters
            percentage = 50;
            isTorus    = 0;
            valsSpel   = 0;
            tweedeVeeg = 0;

            aantalZetten    = 0;
            aantalLampenAan = 0;
            isOplosbaar     = 1;

            // karakters van display
            karLampAan = 'x';
            karLampUit = '.';
            karCursor  = 'C';
        }

        // Memberfuncties
        void drukAf();
        void vulMap();
        void leegPuzzel();
        void zetPercentage();
        void tekenMenu();
        void puzzelMenu();
        void parameterMenu();
        void doeZet(int, int, bool);
        void zetMapGrootte();
        void veegPuzzel();
        void beweegCursor();
        void verwerkZet();
        bool eindPositie();
        void genereerPuzzel();
        void cursorOpties();
        void keerOmLamp(int, int);
        bool isOpgelost();
        void vulOplossingRandom();
        void vulMapRandom();
        void losPuzzelOp();
        void displayOpties();
        void cursorFunctie();

    private:
        // Map arrays
        bool map[MAX][MAX];
        bool oplossing[MAX][MAX];

        int  aantalZetten; // Tellers
        int  aantalLampenAan;
        bool isOplosbaar;

        bool isTorus; // Parameters
        bool valsSpel;
        int  percentage;
        int  hoogte, breedte;
        bool tweedeVeeg;

        char karLampAan = '*';
        char karLampUit = '0';
        char karCursor  = 'C';

        bool actieveCursor; // Cursorvariablen
        bool cursorheeftFunctie;
        bool cursorZetAan;
        int  cursorX, cursorY;
};

void infoBlokje() {
    cout << "LIGHTS OUT\n"
         << "Dit programma is gemaakt door Vitto van Leeuwen en Jan Luijk.\n"
         << "In dit programma kan je het spel LIGHTS OUT spelen. \nDe "
         << "bedoelingvan het spel is om alle lichten in het spel uit te "
         << "krijgen. \nDit doe je door zetten te doen. \nEen zet veranderd"
         << " de status van de lamp en van de aangrenzende buren. \n"
         << "Om dit spel te spelen moet je eerst een puzzel genereren. \nGa "
         << "dan naar het tekenmenu.\nDat doe je door de juiste karakter in te "
         << "voeren.\nIn het tekenmenu zie je een aantal opties die je kunt"
         << " doen. \nEen van deze opties is het genereren van de puzzel. "
         << "\nNa hetgenereren van een puzzel kun je gaan oplossen. \n"
         << "Ga terug naar het hoofdmenu met de letter [T].\n"
         << "Ga dan naar puzzelmenu -> zet. Hier kan je zetten invoeren. \nDat "
         << "doe je door bordlocaties op te geven, net als in bij schaken.\n"
         << "Veel plezier! \n\n"
         << " Een aantal andere opties die dit spel kan doen: \n"
         << " - Oplossen van puzzels \n - Veranderen van mapgrootte\n -"
         << " Aanpassen van karakter voor"
         << "lampen aan en uit\n - Gebruik van het volgalgoritme\n "
         << " " << endl;
}

// Geeft een random getal
int rng() {
    static int seed = 42;        // Static: seed wordt 1 keer geinitialiseerd
    unsigned int m = 2147483647; // Lehmer random number generator
    unsigned int a = 16807;      // Dit zijn specifiek gekozen constanten

    seed = seed * a % m;
    return seed;
}


// Klemt waarde tussen een ondergrens en bovengrens en returnt deze
int klem(int getal, int ondergrens, int bovengrens) {
    if (getal < ondergrens) {
        getal = ondergrens;
    }
    if (getal > bovengrens) {
        getal = bovengrens;
    }
    return getal;
}
*/


int hoofdMenu(Othellobord & othellobord) {
    char keuze;

    do {
        cout << "Kies uit: [s]toppen, [l]ezen, [r]itsen  " << endl
             << "          [a]fdrukken, [z]etten" << endl
             << "Uw keuze: ";
        cin >> keuze;
        leegTerminal();
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
        case 'r':
        case 'R':
            othellobord.ritsMap();
            othellobord.afdrukken();
            break;
        default:
            cout << "Niet toegestane menukeuze ..." << endl;
        } // switch
    }     // do 
    while( !(keuze == 's') && !(keuze == 'S'));

    return 1;
}

int main() {
    Othellobord othellobord;

    hoofdMenu(othellobord);
    
    return 0;
    
}