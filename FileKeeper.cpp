//
// Created by pacman29 on 23.10.17.
//

#include <fstream>
#include "FileKeeper.h"

FileKeeper::FileKeeper(const char* filename) {
    this->filename = filename;
    this->fileRow = vector<unsigned int>();
    ifstream ifs;
    ifs.open(filename);

    if(ifs.is_open()){
        unsigned int buff;
        while(!ifs.eof()){
            ifs >> buff;
            this->fileRow.push_back(buff);
        }
    }


    ifs.close();
}

unsigned int FileKeeper::getLine(unsigned int i) {
    return this->fileRow.at(i);
}
