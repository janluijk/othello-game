#include <main.h>

class Bordvakje 
{
  public:
    char kleur;           //     7 0 1
    Bordvakje* buren[8];  //     6   2
    Bordvakje()           //     5 4 3
    {         
      kleur = '.';
      for (int i = 0; i < 8; i++) {
        buren[i] = nullptr;
      }

    }
    ~Bordvakje() {}

};//bordvakje

class Othellobord 
{
  private:
    // Variables
    Bordvakje* ingang;
    
    // Functions
    Bordvakje* elementPtr(Vec2);
    void trekLijn(int, int, char, Bordvakje*);
    void ritsMap();

  public:
    // Variablen
    int Lengte;
    int Hoogte;
    char Speler; // 0 = player v player, 1 = player v bot, 2 = bot v bot
    int Vervolgpartijen;
    
    char beurt;
    
    
    
    // Functions
    Vec2 krijgCoordinaten(); // Van speler gevraagd:
    char krijgKleur();
    void krijgZet();

    int gaZettenAf(Othellobord &, int);
    void kopieerMap();
    void evalueerZet();
    void volgendeBeurt();


    bool isZetMogelijk(Vec2, char, bool); // Als bool waar: zet wordt meteen uitgevoerd.
    void afdrukken();
    void zetSteen(Vec2, char);
    void maakKopie(Bordvakje* ingang, Othellobord & kopie);
      
    // Constructor
    Othellobord(int lengte = 8, int hoogte = 8, char speler = 0, int vervolgpartijen = 0) {
      Lengte = lengte;
      Hoogte = hoogte;
      Speler = speler;
      Vervolgpartijen = vervolgpartijen;

      beurt = 'z';

      ritsMap();

      // Startpositie
      Vec2 startpositie = {Lengte/2, Hoogte/2};
      zetSteen(startpositie,'w');
      startpositie.x++;
      zetSteen(startpositie ,'z');
      startpositie.y++;
      zetSteen(startpositie ,'w');
      startpositie.x--;
      zetSteen(startpositie ,'z');
    }
};

