#include "main.h"

class Bordvakje 
{
  public:
    char kleur;           //     7 0 1
    Bordvakje* buren[8];  //     6   2
    Bordvakje();
    ~Bordvakje();

};//bordvakje

class Othellobord 
{
  private:
    Bordvakje* Ingang;
    Othellobord* vorige;
    Othellobord* volgende;
    
    // Functies
    Bordvakje* elementPtr(Vec2);
    void trekLijn(int, int, Bordvakje*);

    // Undo
    void maakKopie(Othellobord* kopie);

  public:
    // Geinitialiseerd door speler:
    int Lengte = 8;
    int Hoogte = 8;
    int Vervolgpartijen = 0;
    bool Bot1 = false;
    bool Bot2 = false;

    char Speler1 = 'z';
    char Speler2 = 'w';

    // Leesbaarheid
    bool DoeZetWel = true;
    bool DoeZetNiet = false;

    // Globals
    bool SpelIsOver = false;
    bool Undo = false;
    Vec2 GoedeZet;
    int MaxIteraties = 5;

    // Init
    void startPositie();
    void zetSteen(Vec2, char);
    void menuSpel();
    void simulatieSpel();
    void krijgParameters();
    void ritsMap();

    // Handig
    void draaiSpeler();
    void afdrukken();
    

    // Winnen en tellen
    char winnen();
    int telMogelijkeZetten();
    int aantalVervolgzetten();
    char isSpelOver();
    bool isZetMogelijk(bool, Vec2); // Als bool waar: zet wordt meteen uitgevoerd.
    
    // Spelen
    void spelerZet();
    void randomZet();
    bool spelerOpties(char);
    int recursiefBesteZet(int);

    // Constructor en destructor
    Othellobord();
    Othellobord(int, int, char, char, bool, bool);
    ~Othellobord();
};
