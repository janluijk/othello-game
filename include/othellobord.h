class Bordvakje {
  public:
    char kleur;           //     7 0 1
    Bordvakje* buren[8];  //     6   2
    Bordvakje() {         //     5 4 3
      kleur = '.';
      for (int i = 0; i < 8; i++)
      {
        buren[i] = NULL;
      }
    }

};//bordvakje


class Othellobord {
  private:
    Bordvakje* ingang;
    // TODO
  public:
    int mapgrootte;
    
    Bordvakje* ritsMap(int, Bordvakje*);
    Othellobord() {
      mapgrootte = 8;
    }
    // TODO
};//othellobord