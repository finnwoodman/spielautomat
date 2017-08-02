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

  void printData();

  int** fields;
  int** images;
  char** files;

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
