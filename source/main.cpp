#include <iostream>
#include <othellobord.h>
using namespace std;

// Krijg
char krijgInvoer() {
    char input;

    do { // Alle tabs en enters worden weggehaald
        input = cin.get();
    } while (input == '\n' || input == '\t');
    return input;
}
int krijgGetal() {
    char input;
    int  getal    = 0;
    int  decimaal = 0;

    input = krijgInvoer(); // eerste niet-enter
    while(input < '0' || input > '9') { // zolang geen getal, verder zoeken
        input = cin.get();
    }
    while(input >= '0' && input <= '9') { // zolang integer: maak getal van
        decimaal = input - '0'; // converteren van karakter naar integer
        getal = getal * 10 + decimaal;

        input = cin.get();
    }
    return getal;
}
bool krijgParameters(int& lengte, int& hoogte, int& speler, int& vervolgpartijen) {
    char keuze;

    cout << "Wie spelen er? Wit wordt gespeeld door een: \n[Persoon], [Computer] \n:  ";
    keuze = krijgInvoer();
    
    switch (keuze)
    {
    case 'p':
    case 'P':
        break;
    case 'c':
    case 'C':
        speler++;
        break;
    default:
        cout << "Geen geldige waarde opgegeven, het spel zal starten met de standaardwaarden!" << endl;
        return false;
    }

    cout << "\nZwart wordt gespeeld door een: \n[Persoon], [Computer], \n:  ";
    keuze = krijgInvoer();

    switch (keuze)
    {
    case 'p':
    case 'P':
        break;
    case 'c':
    case 'C':
        speler++;
        break;
    default:
        cout << "Geen geldige waarde opgegeven, het spel zal starten met de standaardwaarden!" << endl;
        return false;
    }
    
    cout << "Stel nu de mapgrootte in: \nDe lengte van de map wordt: \n: ";
    lengte = krijgGetal();
    cout << "\n De hoogte van de map wordt: \n: ";
    hoogte = krijgGetal();

    vervolgpartijen = 0;

    if(speler == 2) {
        cout << "Hoeveel vervolgpartijen wil je spelen? \n: ";
        vervolgpartijen = krijgGetal();
    }

    return true; 
}

// Util
void leegTerminal() {
    //std::system("CLS");

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int min(int a, int b) {
    int result = (a < b) ? a : b;
    return result;
}

int max(int a, int b) {
    int result = (a > b) ? a : b;
    return result;
}

// Menu
int hoofdMenu(Othellobord & othellobord) {
    char keuze;
    leegTerminal();
    
    do {
        othellobord.afdrukken();
        cout << "Kies uit: [s]toppen, [t]el mogelijke zetten" << endl
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
        case 't':
        case 'T':
            othellobord.recursiefEvaluatie(0);
            othellobord.speelBesteZet();
            break;
        case 'z':
        case 'Z':
            othellobord.krijgZet();
            leegTerminal();
            //winnen();
            break;
        default:
            cout << "Niet toegestane menukeuze ..." << endl;
        } // switch
    }     // do 
    while( !(keuze == 's') && !(keuze == 'S'));

    return 1;
}

int main() {
    int lengte;
    int hoogte;
    int speler;
    int vervolgpartijen;
    vervolgpartijen = 5;

    if(krijgParameters(lengte, hoogte, speler, vervolgpartijen)) {
        Othellobord othellobord(lengte, hoogte, speler, vervolgpartijen);
        hoofdMenu(othellobord);
    }
    else {
        Othellobord othellobord;
        hoofdMenu(othellobord);
    }
    return 0;
}
 