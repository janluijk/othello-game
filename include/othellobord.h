//#include <main.h>


Vec2 a = Vec2{5, 6};

class Bordvakje {
  public:
    char kleur;           //     7 0 1
    Bordvakje* buren[8];  //     6   2
    Bordvakje() {         //     5 4 3
      kleur = '.';
      for (int i = 0; i < 8; i++)
      {
        buren[i] = nullptr;
      }
    }

};//bordvakje

class Othellobord {
  private:
    // Variables
    int mapgrootte;
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
    
    // Functions
    Vec2 krijgCoordinaten(); // Van speler gevraagd:
    char krijgKleur();
    void krijgZet();

    void gaZettenAf();
    void kopieerMap();
    void evalueerZet();


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
      
      ritsMap();

      // Startpositie
      zetSteen((struct Vec2){Lengte/2,Hoogte/2},'w');
      zetSteen((struct Vec2){Lengte/2 + 1, Hoogte/2} ,'z');
      zetSteen((struct Vec2){Lengte/2, Hoogte/2 + 1} ,'z');
      zetSteen((struct Vec2){Lengte/2 + 1, Hoogte/2 + 1} ,'w');
    }
};

