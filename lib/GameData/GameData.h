#ifndef GameData_h
#define GameData_h


#include "Arduino.h"
#include "CSVFile.h"
#include "SdFat.h"
#include "Adafruit_Thermal.h"

#define FILENAME "table.csv"
#define FILENAMESIZE 6


class GameData
{
public:
  GameData(int _fields, int _lines);
  void init();
  void init(boolean _printer);
  void report(boolean _debug);
  void grab();
  void search(int _team, int _duration, int _minAge, int maxAge, int _cat);
  void search(int _team, int _duration, int _minAge, int _maxAge, int _cat, bool _ball);
  void printData();
  int getGame();

  int** fields;
  int** images;
  String files[130];
  void print();
  void print(int _game);
  void print(String _game, int _w, int _h);

private:

  int game;


protected:
  boolean debug;
  boolean hasPrinter;

  void grabData();
  void grabFiles();
  void grabImages();


  void initSdFile();
  void initSdCard();
  void initPrinter();

  int LINES;
  int FIELDS;

  SdFatSdio sd;
  CSVFile csv;

  int numBuffer = 0;


};

#endif
