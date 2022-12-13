#include <iostream>
#include <othellobord.h>
using namespace std;

unsigned int seed = 0;

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

char krijgChar() {
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

    input = krijgChar(); // eerste niet-enter
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

int randomNumber() {
    // Static: seed wordt 1 keer geinitialiseerd
    int m = 2147483647; // Lehmer random number generator
    int a = 1103515245 ;      // Dit zijn specifiek gekozen constanten
    int c = 12345;

    seed = (a * seed + c) % m;
    return seed;
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

    Othellobord othellobord;
    othellobord.menuSpel();
    while (1)
    {
    }
    
    return 0;
}