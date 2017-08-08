#ifndef GameData_h
#define GameData_h


#include "Arduino.h"
#include "CSVFile.h"
#include "SdFat.h"

#define FILENAME "table.csv"
#define FILENAMESIZE 6


class GameData
{
public:
  GameData(int _fields, int _lines);
  void init();
  void report(boolean _debug);
  void grab();
  void search(int _team, int _duration, int _minAge, int maxAge, int _cat);
  void printData();
  int getGame();

  int** fields;
  int** images;
  char** files;
  void print();
  
private:
  int game;


protected:
  boolean debug;

  void grabData();
  void grabFiles();
  void grabImages();


  void initSdFile();
  void initSdCard();

  int LINES;
  int FIELDS;

  SdFatSdio sd;
  CSVFile csv;

  int numBuffer = 0;


};

#endif
