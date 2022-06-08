#ifndef SD_CARD
#define SD_CARD

#include "SdFat.h"
//#include "Arduino_AVRSTL.h"

class SDCard{
public:
    SDCard(){};
    SDCard(int cspin);
    bool initialize();
    String path();
    bool makeDirectory(String dirName);
    bool removeDirectory(String dirName);
    bool deleteFile(String fileName);
    String getFileName(File file);
    void printDirectory();
    void printDirectory(File dir, int numTabs);
    bool enter(String dirName);
private:
    SdFat SD;
    int SD_CS_PIN = 6;
    int MAX_CHAR = 25;
    File currentFile;
    String currentDirectory = "/";
    String directories;
};
#endif
