#include <iostream>
#include <main.h>
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
