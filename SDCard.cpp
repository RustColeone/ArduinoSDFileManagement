#include "SDCard.h"

SDCard::SDCard(int cspin){
    SD_CS_PIN = cspin;
}
bool SDCard::initialize(){
    if(!SD.begin(SD_CS_PIN)){
        return false;
    }else{
        currentFile = SD.open("/");
        return true;
    }
}
String SDCard::path(){
    return currentDirectory;
}
bool SDCard::makeDirectory(String dirName){
    String dir = currentDirectory;
    currentFile = SD.open(currentDirectory);
    if(currentDirectory == "/"){
        dir = dirName;
    }else{
        dir = currentDirectory + "/" + dirName;
    }
    //Serial.println("Trying to make a new directory at ");
    //Serial.print(dir);
    if(SD.mkdir(dir)){
        //Serial.println("...successful");
        return true;
    }else{
        //Serial.println("...failed");
        return false;
    }
}
bool SDCard::removeDirectory(String dirName){
    String dir = currentDirectory;
    currentFile = SD.open(currentDirectory);
    if(currentDirectory == "/"){
        dir = dirName;
    }else{
        dir = currentDirectory + "/" + dirName;
    }
    //Serial.println("Trying to remove a directory at ");
    //Serial.print(dir);
    if(SD.rmdir(dir)){
        //Serial.println("...successful");
        return true;
    }else{
        //Serial.println("...failed");
        return false;
    }
}
bool SDCard::deleteFile(String fileName){
    String dir = currentDirectory;
    currentFile = SD.open(currentDirectory);
    if(currentDirectory == "/"){
        dir = fileName;
    }else{
        dir = currentDirectory + "/" + fileName;
    }
    //Serial.println("Trying to delete a file at ");
    //Serial.print(dir);
    if(SD.remove(dir)){
        //Serial.println("...successful");
        return true;
    }else{
        //Serial.println("...failed");
        return false;
    }
}
String SDCard::getFileName(File file){
    char FILE_NAME[MAX_CHAR];
    file.getName(FILE_NAME, MAX_CHAR);
    return String(FILE_NAME);
}
void SDCard::printDirectory() {
    currentFile = SD.open(currentDirectory);
    while (true) {
        File entry =  currentFile.openNextFile();
        if (! entry) {
            // no more files
            //Serial.print("No File to print");
            break;
        }
        Serial.print(getFileName(entry));
        
        if (entry.isDirectory()) {
            Serial.println("/");
            //printDirectory(entry, numTabs + 1);
        } else {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}
void SDCard::printDirectory(File dir, int numTabs) {
    while (true) {
        File entry =  dir.openNextFile();
        if (! entry) {
            // no more files
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++) {
            Serial.print('\t');
        }
        Serial.print(getFileName(entry));
        
        if (entry.isDirectory()) {
            Serial.println("/");
            //printDirectory(entry, numTabs + 1);
        } else {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}
bool SDCard::enter(String dirName){
    String dir = currentDirectory;
    //Serial.println(currentDirectory);
    if(currentDirectory == "/"){
        dir = currentDirectory + dirName;
    }else if(dirName == ".."){
        int count = 0;
        int stringMaxIndex = currentDirectory.length() - 1;
        for(int i = stringMaxIndex; i >= 0; i--){
            if(currentDirectory[i] == '/'){
                count++;
            }
            if(count >= 1){
                dir.remove(i, stringMaxIndex + 1 - i);
                if(dir == ""){
                    dir = "/";
                }
                break;
            }
        }
    }
    else{
        dir = currentDirectory + "/" + dirName;
    }
    //Serial.print("Now trying to access directory: ");
    //Serial.println(dir);
    File currentFile = SD.open(dir);
    if(!currentFile){
        return false;
    }
    currentDirectory = dir;
    if(currentFile.isDirectory()){
        //printDirectory(currentFile, 0);
        ;
    }else{
        //Serial.println(getFileName(currentFile));
        //Serial.println(" Open Successful");
        ;
    }
}
