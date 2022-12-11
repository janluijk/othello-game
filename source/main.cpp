#include <iostream>
#include <main.h>
#include <othellobord.h>
using namespace std;

// Returnt EERSTE karakter van invoer
char krijgInvoer() {
    char input;

    do { // Alle tabs en enters worden weggehaald
        input = cin.get();
    } while (input == '\n' || input == '\t');
    return input;
}

// Returnt getal, leest alleen eerste getal!
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

// Leegt de terminal, maakt alles mooier
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

void krijgParameters(Othellobord & othellobord, Othellobord & kopie) {
    char keuze;
    int lengte, hoogte;

    while(1) {
        cout << "Wie spelen er? Wit wordt gespeeld door een: \n [Persoon], [Computer], [S]toppen \n :  " << endl;
        keuze = krijgInvoer();
        
        switch (keuze)
        {
        case 'S':
        case 's':
            cout << "Het spel stopt! " << endl;
            return;
        case 'p':
        case 'P':
            continue;
        case 'c':
        case 'C':
            othellobord.Speler++;
            continue;
        default:
            cout << "Niet toegestane menukeuze ..." << endl;
        } 
    }
    while(1) {
        cout << "\n Zwart wordt gespeeld door een: \n [Persoon], [Computer], [S]toppen \n :  " << endl;
        keuze = krijgInvoer();

        switch (keuze)
        {
        case 'S':
        case 's':
            cout << "Het spel stopt! " << endl;
            return;
        case 'p':
        case 'P':
            break;
        case 'c':
        case 'C':
            othellobord.Speler++;
            break;
        default:
            cout << "Niet toegestane menukeuze ..." << endl;
        } 
    }
    
    cout << "Stel nu de mapgrootte in: \n De lengte van de map wordt: \n : " << endl;
    lengte = krijgGetal();
    cout << "\n De hoogte van de map wordt: \n : " << endl;
    hoogte = krijgGetal();

    if(othellobord.Speler == 2) {
        int vervolgpartijen;

        cout << "Hoeveel vervolgpartijen wil je spelen? \n :  " << endl;
        vervolgpartijen = krijgGetal();
        
    }
    return;
}

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

int main() {
    Othellobord othellobord;
    Othellobord kopie;

    krijgParameters(othellobord, kopie);
    hoofdMenu(othellobord);
    
    return 0;
}
 