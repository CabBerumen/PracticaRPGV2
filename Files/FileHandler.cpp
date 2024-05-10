//
// Created by cbeww on 09/05/2024.
//

#include "FileHandler.h"

void FileHandler::writeToFile(char* targetFilePath, char* buffer, unsigned int bufferSize)
{
    writeStream.open(targetFilePath, ios::binary);
    writeStream.write(buffer, bufferSize);
    writeStream.close();

}

char* FileHandler::readFromFile(char* targetFilePath, char* buffer, unsigned int bufferSize)
{
    readStream.open(targetFilePath, ios::binary);

    if (readStream)
    {
        readStream.read(buffer, bufferSize);
        readStream.close();
        return buffer;
    }

    throw 1;
}

