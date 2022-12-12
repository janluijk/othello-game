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
    Bordvakje* ingang;
    
    // Functies
    Bordvakje* elementPtr(Vec2);
    void trekLijn(int, int, char, Bordvakje*);
    void ritsMap();
    void speelZet(Vec2, char, int, int, Bordvakje*);

  public:
    // Variablen
    // Geinitialiseerd door speler:
    int Lengte;
    int Hoogte;
    int Vervolgpartijen;
    char Speler; // 0 = player v player, 1 = player v bot, 2 = bot v bot

    char Beurt;
    char BeurtTegenstander;
    Vec2 BesteZet;
    int MaxIteraties = 5;

    // Leesbaarheid
    bool ZetNiet = false;
    bool ZetWel = true;
  
    // Data van spelers
    Vec2 krijgCoordinaten(); 
    char krijgKleur();
    void krijgZet();

    int recursiefEvaluatie(int);
    bool isZetMogelijk(Vec2, char, bool); // Als bool waar: zet wordt meteen uitgevoerd.
    void speelBesteZet();
    void maakKopie(Othellobord & kopie);
    
    // Handige functies
    void zetSteen(Vec2, char);
    void draaiBeurt();
    void afdrukken();
    int winnen();
    int telMogelijkeZetten();
    void stopSpel();
    void verwijderen();

    // Constructor
    Othellobord(int lengte = 8, int hoogte = 8, char speler = 'z', int vervolgpartijen = 0) {
      Lengte = lengte;
      Hoogte = hoogte;
      Speler = speler;
      Vervolgpartijen = vervolgpartijen;

      Beurt = 'z';
      BeurtTegenstander = 'w';

      ritsMap();

      // Startpositie (Kan dit beter?)
      Vec2 startpositie = {Lengte/2, Hoogte/2};
      zetSteen(startpositie,'w');
      startpositie.x++;
      zetSteen(startpositie ,'z');
      startpositie.y++;
      zetSteen(startpositie ,'w');
      startpositie.x--;
      zetSteen(startpositie ,'z');
    }
    // Destructor
    //~Othellobord();
};
