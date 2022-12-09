struct Vec
{
    int x;
    int y;
};

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

    Bordvakje* ingang;
    
    // Variables
    int mapgrootte;

    // Functions
    Bordvakje* elementPtr(Vec);
  public:
    
    // Functions
    Vec krijgCoordinaten();
    void afdrukken();
    void zetPositie();
    char krijgKleur();
    void ritsMap();

    // Constructor
    Othellobord() {
      ritsMap();
      mapgrootte = 8;
    }
};

