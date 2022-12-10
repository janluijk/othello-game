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
    char krijgKleur();
    void krijgZet();
    
    void afdrukken();
    void doeZet(Vec, char);
    void ritsMap();
    void isZetMogelijk(Vec, char, bool);
    void trekLijn(int, int, char, Bordvakje*);

    // Constructor
    Othellobord() {
      mapgrootte = 8;
      ritsMap();
      
      doeZet((Vec){4, 4} ,'z');
      doeZet((Vec){4, 5} ,'w');
      doeZet((Vec){5, 5} ,'z');
      doeZet((Vec){5, 4} ,'w');
      
      /*
      doeZet((Vec){5, 5} ,'z');
      doeZet((Vec){5, 4} ,'w');
      doeZet((Vec){5, 3} ,'w');
      doeZet((Vec){5, 2} ,'w');
      */
    }
};

