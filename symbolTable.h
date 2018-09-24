#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

struct SymbolTable{
//symbol table that stores the address value given the variable name
unordered_map<string,int> symbolTable = {
    {"SP",    0},
    {"LCL",   1},
    {"ARG",   2},
    {"THIS",  3},
    {"THAT",  4},
    {"R0",    0},
    {"R1",    1},
    {"R2",    2},
    {"R3",    3},
    {"R4",    4},
    {"R5",    5},
    {"R6",    6},
    {"R7",    7},
    {"R8",    8},
    {"R9",    9},
    {"R10",   10},
    {"R11",   11},
    {"R12",   12},
    {"R13",   13},
    {"R14",   14},
    {"R15",   15},
    {"SCREEN",16384},
    {"KBD",   24576},
    };

    //inserts a value given a user variable name and address value
    void insert(string tableKey, int value){
        symbolTable.insert({tableKey, value});
    }

    //finds the correct address according to key, and returns the binary equivalent
    string find(string toFind){
        stringstream stringFound;
        bitset<15> stringTemp(symbolTable.at(toFind));
        stringFound << stringTemp;
        return stringFound.str();
    }

};
#endif
