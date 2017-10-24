//
// Created by pacman29 on 23.10.17.
//

#include <string.h>
#include <sstream>
#include <limits>
#include <bitset>
#include "IpConverter.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

unordered_map<string, string> IpConverter::converter(unsigned int ip) {
    unordered_map<string,string> map = unordered_map<string,string>();
    stringstream buff;
    buff<< bitset<numeric_limits<unsigned int>::digits>(ip);
    map.insert({"2",buff.str()});
    buff.str(string());

    buff<< showbase << oct << ip;
    map.insert({"8",buff.str()});
    buff.str(string());

    buff<< showbase << dec << ip;
    map.insert({"10",buff.str()});
    buff.str(string());
    
    buff<< showbase << hex << ip;
    map.insert({"16",buff.str()});
    return map;
}
