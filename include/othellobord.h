#include <main.h>

class Bordvakje 
{
  public:
    char kleur;           //     7 0 1
    Bordvakje* buren[8];  //     6   2
    Bordvakje() {
      kleur = '.';
      for (int i = 0; i < 8; i++) {
        buren[i] = nullptr;
      }
    }
    //~Bordvakje();

};//bordvakje

class Othellobord 
{
  private:
    // Variablen
    Bordvakje* Ingang;
    Othellobord* vorige;
    Othellobord* volgende;
    
    // Functies
    Bordvakje* elementPtr(Vec2);
    void trekLijn(int, int, Bordvakje*);
    void ritsMap();
    void speelZet(Vec2, char, int, int, Bordvakje*);

  public:
    // Variablen
    // Geinitialiseerd door speler:
    int Lengte;
    int Hoogte;
    int Vervolgpartijen = 0;
    bool Bot1 = false;
    bool Bot2 = false;

    char Speler1;
    char Speler2;

    bool DoeZetWel = true;
    bool DoeZetNiet = false;

    Vec2 BesteZet;
    int MaxIteraties = 5;
    
    bool SpelIsOver = false;
  
    // Data van spelers
    Vec2 krijgCoordinaten(); 
    char krijgKleur();
    void krijgZet();
    void krijgParameters();

    int recursiefEvaluatie(int);
    bool isZetMogelijk(bool, Vec2); // Als bool waar: zet wordt meteen uitgevoerd.
    void speelBesteZet();
    void maakKopie(Othellobord* kopie);
    
    // Handige functies
    void zetSteen(Vec2, char);
    void draaiSpeler();
    void afdrukken();
    void winnen();
    int telMogelijkeZetten();
    void stopSpel();
    void verwijderen();
    void speelSpel();
    void spelerZet();
    void menuSpel();
    void randomZet();
    char isSpelOver();
    void spelerOpties(char);
    Vec2 ptrNaarPos(Bordvakje*);
    void startPositie();
    void maakOngedaan();

    // Constructor
    Othellobord();
    Othellobord(int, int, char, char);
    // Destructor
    ~Othellobord();
};
