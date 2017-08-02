#include "Arduino.h"
#include "GameData.h"
#include "SdFat.h"
#include "CSVFile.h"

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
  //Create 2D Array for games data
  fields = (int **) malloc(LINES * sizeof(int*));
  for (int i = 0; i < LINES; i++) {
    fields[i] = (int*) malloc(FIELDS * sizeof(int));
  }

  //Create Array of strings for games filename
  files = (char **) malloc(LINES * sizeof(char*));
  for (int i = 0; i < LINES; i++) {
    files[i] = (char*) malloc(FILENAMESIZE * sizeof(char));
  }

  //Create 2D Array for image sizes
  images = (int **) malloc(LINES * sizeof(int*));
  for (int i = 0; i < LINES; i++) {
    images[i] = (int*) malloc(2 * sizeof(int));
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
  const byte BUFFER_SIZE = 5;
  char buffer[BUFFER_SIZE + 1];
  buffer[BUFFER_SIZE] = '\0';


  csv.gotoLine(2);
  csv.gotoField(1);
  for (int i = 0; i < LINES; i++) {
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


void GameData::grabImages(){
  const byte BUFFER_SIZE = 5;
  char buffer[BUFFER_SIZE + 1];
  buffer[BUFFER_SIZE] = '\0';

  csv.gotoLine(2);
  for (int i = 0; i < LINES; i++) {
    int numBuffer = 0;
    csv.gotoField(14);
    csv.readField(numBuffer, buffer, BUFFER_SIZE);
    images[i][0] = numBuffer;
    csv.gotoField(15);
    csv.readField(numBuffer, buffer, BUFFER_SIZE);
    images[i][1] = numBuffer;
    csv.nextLine();
  }
}

void GameData::grabFiles(){
  const byte BUFFER_SIZE = 5;
  char buffer[BUFFER_SIZE + 1];
  buffer[BUFFER_SIZE] = '\0';

  csv.gotoLine(2);
  for (int i = 0; i < LINES; i++) {
    csv.gotoField(13);
    csv.readField(buffer, BUFFER_SIZE);
    files[i] = buffer;
    csv.nextLine();
  }
}

void GameData::init(){
  initSdCard();
  initSdFile();
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

void GameData::report(boolean _debug){
  if (!Serial){
    Serial.begin(9600);
  }
  debug = _debug;
  Serial.println("GameData ::: report() :: ACTIVE");
}

void GameData::printData(){
  report(true);
  for (int i = 0; i < LINES; i++) {
    Serial.println(files[i]);
    Serial.print(i);
    Serial.println(" ::");
    for (int j = 0; j < FIELDS; j++) {
      Serial.print(fields[i][j]);
      Serial.print("  ");
    }
    Serial.println();
    Serial.println("File = ");
    Serial.print("  ");
    Serial.print(images[i][0]);
    Serial.print(" x ");
    Serial.println(images[i][1]);
    /* code */
  }
}
