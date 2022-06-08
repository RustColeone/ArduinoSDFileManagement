/*
  Listfiles

  This example shows how print out the files in a
  directory on a SD card

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 2 Feb 2014
  by Scott Fitzgerald

  This example code is in the public domain.

*/
#include <SPI.h>

#include "SDCard.h"
//const uint8_t SD_CS_PIN = 6;


SDCard sdCard;

bool phraseCommand(String raw, String * parameters, int paraSize ){
    int lastIndex = 0;
    int count = 0;
    raw += ' ';
    for(int i = 0; i < raw.length(); i++){
        if(raw[i] == ' '){
            parameters[count++] = raw.substring(lastIndex, i);
            if(++i >= raw.length()){
                break;
            }
            lastIndex = i;
            if(count >= paraSize){
                break;
            }
        }
    }
}

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.print("Initializing SD card...");

    while (!sdCard.initialize()){
        Serial.println(" failed...");
        delay(1000);
    }
    Serial.println(" Successful.");
    //sdCard.printDirectory();
    Serial.print(sdCard.path() + ">");
}

void loop() {
    if(Serial.available()) {
        bool commandSucceed = false;
        String userInput = Serial.readString();
        String commands[3] = {"", "", ""};
        phraseCommand(userInput, commands, 3);
        
        for(int i = 0; i < 3; i++){
            Serial.print(commands[i]);
            Serial.print(" ");
        }
        Serial.println("");
        //Serial.print("Which is phrased from: ");
        //Serial.println(userInput);
        if(commands[0] == "ls"){
            sdCard.printDirectory();
            commandSucceed = true;
        }
        else if(commands[0] == "mkdir"){
            commandSucceed = sdCard.makeDirectory(commands[1]);
        }
        else if(commands[0] == "rmdir"){
            commandSucceed = sdCard.removeDirectory(commands[1]);
        }
        else if(commands[0] == "rm"){
            commandSucceed = sdCard.deleteFile(commands[1]);
        }
        else if(commands[0] == "cd"){
            commandSucceed = sdCard.enter(commands[1]);
        }

        if(!commandSucceed){
            Serial.println("\n" + commands[0] + "was not understood");
        }
        Serial.print(sdCard.path() + ">");
    }
    delay(100);
}
