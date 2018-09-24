#ifndef JUMP_H
#define JUMP_H

#include <unordered_map>
#include <string>

using namespace std;

struct JumpTable{
//jump table that stores the jump binary value given the jump string
unordered_map<string,string> jumpTable = {
    {"NULL", "000"},
    {"JGT",    "001"},
    {"JEQ",    "010"},
    {"JGE",   "011"},
    {"JLT",    "100"},
    {"JNE",   "101"},
    {"JLE",   "110"},
    {"JMP",  "111"},
    };

     //finds the correct jump according to key, and returns the binary equivalent
    string find(string toFind){
        string stringFound = jumpTable.at(toFind);
        return stringFound;
    }
};
#endif
