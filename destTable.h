#ifndef DEST_H
#define DEST_H

#include <unordered_map>
#include <string>

using namespace std;

struct DestTable{
//dest table that stores the dest binary value given the dest string
unordered_map<string,string> destTable = {
    {"NULL", "000"},
    {"M",    "001"},
    {"D",    "010"},
    {"MD",   "011"},
    {"A",    "100"},
    {"AM",   "101"},
    {"AD",   "110"},
    {"AMD",  "111"},
    };

    //finds the correct desination binary value given dest string
    string find(string toFind){
        string stringFound = destTable.at(toFind);
        return stringFound;
    }
};
#endif
