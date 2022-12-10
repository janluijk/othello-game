#include <iostream>
#include <othellobord.h>
#include <main.h>

using namespace std;

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
        case 'z':
        case 'Z':
            othellobord.zetPositie();
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