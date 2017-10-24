//
// Created by pacman29 on 23.10.17.
//

#ifndef LAB02_FILEKEEPER_H
#define LAB02_FILEKEEPER_H

#include <iostream>
#include <vector>

using namespace std;


class FileKeeper {
private:
    const char* filename;
    vector<unsigned int> fileRow;
public:
    FileKeeper(const char* filename);
    unsigned int getLine(unsigned int i);
};


#endif //LAB02_FILEKEEPER_H
