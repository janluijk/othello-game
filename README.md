Compile command:
g++ -std=c++11 -O2 -Wall -o build/othello.exe source/*.cpp -I include && build/source.exe 

-- TODO --
  - Maken van een constructor en destructor
  - Keuze tussen: PvP, PvBot, BotvBot
    - Beide bots -> statistieken
      - Meer dan 1 potje, niet afdrukken
  - Makefile
  - Aantal vervolgpartijen uitrekenen
    - Winnen (aantal vervolgpartijen = 0)
    - Vervolgzetten recursief
  - Ongedaan maken van zetten
    - Alle tussenstanden worden op een stapel bijgehouden
  
