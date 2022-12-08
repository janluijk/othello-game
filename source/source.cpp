#include <iostream>
#include <othellobord.h>
using namespace std;


// Returnt EERSTE karakter: van invoer
char leesInvoer() {
    char input;

    do { // Alle tabs en enters worden weggehaald
        input = cin.get();
    } while (input == '\n' || input == '\t');
    return input;
}

// Leegt de terminal, maakt alles mooier
void leegTerminal() {
    // std::system("CLS");
    /*
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    */
}

void Afdrukken(Bordvakje *ingang) {
    Bordvakje* omlaagptr = ingang;
    Bordvakje* rechtsptr;

    while(omlaagptr) {
        rechtsptr = omlaagptr;
        while(rechtsptr) {
            cout << (rechtsptr->kleur) << " | ";
            rechtsptr = rechtsptr->buren[2];
        }
        cout << "\n";
        omlaagptr = omlaagptr->buren[4];
    }
}

void Toevoegen (Bordvakje* & ingang, char kleur) {
  Bordvakje* p;  // hulppointertje
  p = new Bordvakje;

  p->kleur = kleur;
  p->buren[2] = ingang;
  ingang = p;
}

void Verwijderen(Bordvakje *&ingang)
{
    Bordvakje *p = ingang; // hulppointertje
    if (ingang != nullptr) {
        ingang = ingang->buren[2];
        delete p;             // in deze volgorde
    }                         // if
} // Verwijderen


void Othellobord::ritsMap(int mapgrootte, Bordvakje* ingang) {
    Bordvakje* hoofdIngang = NULL; 
    Bordvakje* vorige, *boven = new Bordvakje;
    
    for (int i = 0; i < mapgrootte; i++) {
        Bordvakje* rijIngang; //row-wise head of list.
        Bordvakje *vorige = new Bordvakje; // dummy node to mark start of left pointer.
        for (int j = 0; j < mapgrootte; j++) {
            Bordvakje* temp = new Bordvakje;
 
            if (j == 0) {
                head_row = temp;
            }
            if (i == 0 && j == 0) {
                head_main = temp;
            } 

            temp->buren[6] = vorige;
            vorige->buren[2] = temp;
            
            if (i == mapgrootte - 1) temp->buren[4] = NULL;
 
            //This is only used for 1st row.
            if (!boven->buren[2]) {
                boven->buren[2] = new Bordvakje;
            }
            boven = boven->buren[2];
 
            temp->buren[0] = boven;
            boven->buren[4] = temp;
            vorige = temp;
 
            if (j == mapgrootte - 1) {
                vorige->buren[2] = NULL;
            }
        }
        boven = rijIngang->buren[6];
    }
}

void geefKleur(char &kleur) {
    cout << "Geef een kleur op:";
    cin >> kleur;
}

void geefIndex(int &index) {
    char input;
    cout << "Geef een index op: ";
    cin >> input;
    if( !(input < '0') && !(input > '9')) {
        index = (int)(input - '0');
    }
    else {
        index = 0;
    }
}

char krijgKleur(Bordvakje *ingang, int index)
{
    Bordvakje *p = ingang; // pointertje om lijst mee door te lopen
    int counter = 0;
    while (p != nullptr) {
        cout << p->kleur;
        if(counter == index) {
            return p->kleur;
        }        
        counter++;
        p = p->buren[2];
    } // while
    return '-';
}

int hoofdMenu(Othellobord & othellobord) {
    char keuze;
    char kleur;
    int index;
    Bordvakje *ingang = NULL;

    do {
        cout << "Kies uit: [s]toppen, [t]oevoegen, [l]ezen, [r]itsen  " << endl
             << "          [a]fdrukken, [v]erwijderen" << endl
             << "Uw keuze: ";
        cin >> keuze;
        leegTerminal();
        switch (keuze)
        {
        case 's':
        case 'S':
            cout << "Dat was het dan ..." << endl;
            break;
        case 't':
        case 'T':
            geefKleur(kleur);
            Toevoegen(ingang, kleur);
            Afdrukken(ingang);
            break;
        case 'a':
        case 'A':
            Afdrukken(ingang);
            break;
        case 'l':
        case 'L':
            geefIndex(index);
            cout << krijgKleur(ingang, index) << endl;
        case 'v':
        case 'V':
            Verwijderen(ingang);
            Afdrukken(ingang);
            break;
        case 'r':
        case 'R':
            ingang = othellobord.ritsMap(0, 0, NULL);
            Afdrukken(ingang);
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