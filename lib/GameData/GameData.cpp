#include "Arduino.h"
#include "GameData.h"
#include "SdFat.h"
#include "CSVFile.h"
#include "Adafruit_Thermal.h"

Adafruit_Thermal printer(&Serial1,2);
/**
GameData class
GameData.cpp
Purpose: Transfer table content of an CSV into an array.
@author Max von Elverfeldt f. RaktiPiepEkti
@version 0.1 31/07/17
*/

/**
* Constructor for CSV Library.
* @param _lines  Number of lines to read in the CSV.
* @param _fields Number of integer fields to read in each line.
*/

GameData::GameData( int _lines, int _fields){
  FIELDS = _fields;
  LINES = _lines;
  debug = false;
  hasPrinter = true;
  game = 0;
  randomSeed(analogRead(A3));
  //Create 2D Array for games data
  fields = (int **) malloc(LINES * sizeof(int*));
  for (int i = 0; i < LINES; i++) {
    fields[i] = (int*) malloc(FIELDS * sizeof(int));
  }

  //Create 2D Array for image sizes
  images = (int **) malloc(LINES * sizeof(int*));
  for (int i = 0; i < LINES; i++) {
    images[i] = (int*) malloc(2 * sizeof(int));
  }
}

//Version mit Ball.
void GameData::search(int _team, int _duration, int _minAge, int _maxAge, int _cat, bool _ball){
  int _game[10];
  _game[0] = 666;
  int _pointer = 0;
  for (int i = 0; i < LINES; i++) {
    if (debug == true){
      Serial.print("/");
    }
    if ((fields[i][0] <= _team) && (fields[i][1] >= _team)) {
      if ((fields[i][2] <= _duration) && (fields[i][3] >= _duration)) {
        if ((fields[i][4] <= _minAge) && (fields[i][5] >= _maxAge)) {
          if (fields[i][5 + _cat] == 1) {
            if ((_ball == true) && (fields[i][11] == 1)){
              _game[_pointer] = i;
              _pointer++;
              if (debug == true){
                Serial.println("*");
              }
              if (_pointer == 9) {
                break;
              }
            }
            if ((_ball == false) && (fields[i][11] == 0)){
              _game[_pointer] = i;
              _pointer++;
              if (debug == true){
                Serial.println("*");
              }
              if (_pointer == 9) {
                break;
              }
            }
          }
        }
      }
    }
  }
  if (debug == true){
    Serial.println();
  }

  if (_pointer > 1){
    _pointer = random(0, _pointer+1);
    if (debug == true){
      Serial.println("GameData:::Search()::Found several games :-)");
    }
  }
  else {
    _pointer = 0;
  }

  if (debug == true){
    Serial.print("Selected::: ");
    Serial.println(_game[_pointer]);
  }
  game = _game[_pointer];

}

void GameData::print(){
  if (hasPrinter == true) {
    String sdFiName = "test.bin";
    const char * c = sdFiName.c_str();
    File sdCardFile = sd.open (c, FILE_READ);
    while (sdCardFile.available()) {
      Serial.println("Printing");
      printer.printBitmap(384, 1128, dynamic_cast<Stream*>(&sdCardFile));
    }
    sdCardFile.close();
    printer.feed(10);
  }
}

void GameData::print(int _game){

  if (hasPrinter == true) {
    String sdFiName;
    if(_game != 666){
      Serial.println("NAME ->");
      Serial.println(files[_game]);
      sdFiName = files[_game];
      sdFiName+=".bin";
      Serial.println(sdFiName);
      const char * c = sdFiName.c_str();
      File sdCardFile = sd.open (c, FILE_READ);
      while (sdCardFile.available()) {
        Serial.println("Printing");
        printer.printBitmap(images[_game][0], images[_game][1], dynamic_cast<Stream*>(&sdCardFile));
      }
      sdCardFile.close();
    }
    if(_game == 666){
      sdFiName="zonk.bin";
      const char * c = sdFiName.c_str();
      File sdCardFile = sd.open (c, FILE_READ);
      while (sdCardFile.available()) {
        Serial.println("Printing");
        printer.printBitmap(384, 384, dynamic_cast<Stream*>(&sdCardFile));
      }
      sdCardFile.close();
    }
    printer.feed(10);
  }
}

void GameData::grab(){
  grabData();
  grabFiles();
  grabImages();
}
/**
* Transfers CSV data into an 2D array.
*/
void GameData::grabData(){
  if (debug == true) {
    Serial.println("GameData ::: grabData() ::Started.");
  }
  const byte BUFFER_SIZE = 5;
  char buffer[BUFFER_SIZE + 1];
  buffer[BUFFER_SIZE] = '\0';
  csv.gotoLine(2);
  csv.gotoField(1);
  boolean _tmp = true;
  for (int i = 0; i < LINES; i++) {
    if (debug == true) {
      Serial.print("GameData ::: grabData() :: Line: ");
      Serial.println(i);
    }
    for (int j = 0; j < FIELDS; j++) {
      int numBuffer = 0;
      csv.readField(numBuffer, buffer, BUFFER_SIZE);
      fields[i][j] = numBuffer;
      csv.nextField();
    }
    csv.nextLine();
    csv.gotoField(1);
  }
}

/**
* Returns the currently selectec game.
* @return Integer pointing to game in table.
*/
int GameData::getGame(){
  return game;
}

/**
* Transfers the image sizes from csv to 2D array images[][]
*/
void GameData::grabImages(){
  if (debug == true) {
    Serial.println("GameData ::: grabImages() ::Started.");
  }
  const byte BUFFER_SIZE = 5;
  char buffer[BUFFER_SIZE + 1];
  buffer[BUFFER_SIZE] = '\0';
  boolean _tmp = true;
  csv.gotoLine(2);
  for (int i = 0; i < LINES; i++) {
    if (debug == true) {
      if (_tmp == true){
        Serial.print("GameData ::: grabImages() :: ");
        _tmp = false;
      }
      else {
        Serial.print("/");
      }
    }
    int numBuffer = 0;
    csv.gotoField(14);
    csv.readField(numBuffer, buffer, BUFFER_SIZE);
    images[i][0] = numBuffer;
    csv.gotoField(15);
    csv.readField(numBuffer, buffer, BUFFER_SIZE);
    images[i][1] = numBuffer;
    csv.nextLine();
  }
  if (debug == true) {
    Serial.println(">");
  }
}

/**
* Transfers the image file's names to an array named files.
*/
void GameData::grabFiles(){
  if (debug == true) {
    Serial.println("GameData ::: grabFiles() ::Started.");
  }
  const byte BUFFER_SIZE = 5;
  char buffer[BUFFER_SIZE + 1];
  buffer[BUFFER_SIZE] = '\0';
  csv.gotoLine(2);
  boolean _tmp = true;
  for (int i = 0; i < LINES; i++) {
    if (debug == true) {
      if (_tmp == true){
        Serial.print("GameData ::: grabFiles() :: ");
        _tmp = false;
      }
      else {
        Serial.print("/");
      }
    }
    csv.gotoField(13);
    csv.readField(buffer, BUFFER_SIZE);
    files[i] = String(buffer);
    csv.nextLine();
  }
  if ((debug == true) && (_tmp == false)) {
    Serial.println(">");
  }
}

/*
* Init SD card and file
*/
void GameData::init(){
  initSdCard();
  initSdFile();
  if (hasPrinter == true){
    initPrinter();
  }
}

/*
* Init SD card and file
*/
void GameData::init(boolean _printer){
  hasPrinter = _printer;
  initSdCard();
  initSdFile();
  if (hasPrinter == true){
    initPrinter();
  }
}

void GameData::initPrinter(){
  Serial1.begin(19200);
  printer.begin(100);
  printer.feed(10);
  if(debug == true){
    Serial.println("GameData ::: initPrinter() ::Successfully started.");
  }
}
/**
* Open SD file once.
*/
void GameData::initSdFile()
{
  if (!csv.open(FILENAME, O_RDWR | O_CREAT)) {
    if (debug == true){
      Serial.println("GameData ::: initSdFile() ::Failed open file");
    }
    return;

  }
  else {
    if (debug == true){
      Serial.println("GameData ::: initSdFile() ::Successfully opened file");
    }
    csv.gotoBeginOfFile();
  }
}

/**
* Init SD card first.
*/
void GameData::initSdCard(){
  if (!sd.begin())
  {
    if (debug == true){
      Serial.println("GameData ::: initSdCard() :: SD card begin error.");
    }
    return;
  }
  else{
    if (debug == true){
      Serial.println("GameData ::: initSdCard() :: SD card begin.");
    }
  }
}
/**
* Enable / Disable report
* @param _debug [description]
*/
void GameData::report(boolean _debug){
  debug = _debug;
  if (debug == true){
    if (!Serial){
      Serial.begin(9600);
    }
  }
}

/**
* Print all transferred data.
*/
void GameData::printData(){
  report(true);
  for (int i = 0; i < LINES; i++) {
    Serial.print(i);
    Serial.println(" ::");
    for (int j = 0; j < FIELDS; j++) {
      Serial.print(fields[i][j]);
      Serial.print("  ");
    }
    Serial.println();
    Serial.print("File = ");
    Serial.print(String(files[i]));
    Serial.print(" with ");
    Serial.print(images[i][0]);
    Serial.print(" x ");
    Serial.println(images[i][1]);
    Serial.println("------");
  }
}
