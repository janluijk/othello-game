#include <iostream>
#include <othellobord.h>
using namespace std;

// Input van speler
void krijgInvoer(char& krijgLetter, int& krijgGetal) {
    char letterInput;
    int getal = 0;
    int decimaal;

    do {
        letterInput = cin.get();
    } while (letterInput == '\n' || letterInput == '\t');

    if('0' <= letterInput && letterInput <= '9') {
        krijgLetter = '.';
        decimaal = letterInput - '0';
        getal = getal * 10 + decimaal;
        letterInput = cin.get();
        while ('0' <= letterInput && letterInput <= '9') {
            decimaal = letterInput - '0';
            getal = getal * 10 + decimaal;
            letterInput = cin.get();
        }
        krijgGetal = getal;
        return;
    }
    else {
        krijgGetal = 0;
        krijgLetter = letterInput;
    }
}

char krijgChar() {}

int krijgInt() {}

bool krijgParameters(int& lengte, int& hoogte, int& vervolgpartijen, bool& bot1, bool& bot2) {
    char keuze;
    int getal;

    cout << "Wie spelen er? Zwart wordt gespeeld door een: \n[Persoon], [Computer] \n:  ";
    krijgInvoer(keuze, getal);
    
    switch (keuze)
    {
    case 'p':
    case 'P':
        bot1 = false;
        break;
    case 'c':
    case 'C':
        bot1 = true;
        break;
    default:
        cout << "Geen geldige waarde opgegeven, het spel zal starten met de standaardwaarden!" << endl;
        return false;
    }

    cout << "\nWit wordt gespeeld door een: \n[Persoon], [Computer], \n:  ";
    krijgInvoer(keuze, getal);

    switch (keuze)
    {
    case 'p':
    case 'P':
        bot2 = false;
        break;
    case 'c':
    case 'C':
        bot2 = true;
        break;
    default:
        cout << "Geen geldige waarde opgegeven, het spel zal starten met de standaardwaarden!" << endl;
        return false;
    }
    
    cout << "Stel nu de mapgrootte in: \nDe lengte van de map wordt: \n: ";
    while(!getal) {
        krijgInvoer(keuze, getal);
    }
    lengte = getal; 
    getal = 0;

    cout << "\n De hoogte van de map wordt: \n: ";
    while(!getal) {
        krijgInvoer(keuze, getal);
    }
    hoogte = getal;
    getal = 0;

    vervolgpartijen = 0;

    if(bot1 && bot2) {
        cout << "Hoeveel vervolgpartijen wil je spelen? \n: ";
        while(!getal) {
            krijgInvoer(keuze, getal);
        }
        vervolgpartijen = getal;
        getal = 0;
    }

    return true; 
}



// Utilities
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



// Main
int main() {
    // Variablen
    int lengte, hoogte;
    bool bot1, bot2;
    int vervolgpartijen;



    krijgParameters(lengte, hoogte, vervolgpartijen, bot1, bot2);

    Othellobord othellobord(lengte, hoogte, vervolgpartijen, bot1, bot2);
    
    othellobord.speelSpel();

    return 0;
}