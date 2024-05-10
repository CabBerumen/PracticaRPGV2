//
// Created by cbeww on 09/05/2024.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#import <fstream>

using namespace std;

class FileHandler
{
private:

    ifstream readStream;
    ofstream writeStream;

public:

    void writeToFile(char* targetFilePath, char* buffer, unsigned int bufferSize);
    char* readFromFile(char* targetFilePath, char* buffer, unsigned int bufferSize);

};

#endif //FILEHANDLER_H
