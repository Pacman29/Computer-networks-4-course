//
// Created by pacman29 on 23.10.17.
//

#ifndef LAB02_IPCONVERTER_H
#define LAB02_IPCONVERTER_H

#include <iostream>
#include <unordered_map>

using namespace std;

class IpConverter {
public:
    static unordered_map<string,string> converter(unsigned int ip);
};


#endif //LAB02_IPCONVERTER_H
