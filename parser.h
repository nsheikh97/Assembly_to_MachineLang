#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
class Parser{
private:
    string filename;
    int lineNumber = 0;
    vector<vector<string>> parsedFields;

    Parser();
    //stores the address value or address variable name
    string Address(string line){
        string newString;
        for(int i = 0; i < line.length()-1; i++){
            if(line[i] != '@') newString += line[i];
        }
        line = newString;
        return line;
    }
    //stores label name
    string Label(string line){
        string newString;
        for(int i = 0; i < line.length()-1; i++){
            if(line[i] != '(' && line[i] != ')') newString += line[i];
        }
        line = newString;
        return line;
    }
    //stores destination
    string Dest(string line){
        string newString;

            for(int i = 0; line[i] != '='; i++){
                newString += line[i];
            }
            line = newString;
            return line;
    }
    //stores comp
    string Comp(string line){
        string newString;
        //if line contains a jump, comp is taken before ; token
        if(line.find(';') != string::npos){
            for(int i = 0; line[i] != ';'; i++){
                newString += line[i];
            }
            line = newString;
            return line;
        }
        else{
            //if = token is on line, comp is taken after = token
            for(int i = line.find('=') + 1; i < line.length()-1; i++){
                newString += line[i];
            }
            line = newString;
            return line;
        }
    }
    //if ; token is on line, jump command is taken after ; token
    string Jump(string line){
        string newString;
        for(int i = line.find(';')+1; i < line.length()-1; i++){
            newString += line[i];
        }
        line = newString;
        return line;
    }
public:
    //constructor takes a filename
    Parser(string filename) : filename(filename) {};
    vector<vector<string>> parseFile(){
        //creating input file object with filename
        ifstream file {filename};
        string line;
        //read file line by line, then stores into vector with proper fields:
        //A-instruction vector : {commandType_Flag, line #, address string parsed}
        //C-instruction vector : {commandType_Flag, destination parsed, comp parsed, jump parsed} / NULL is used if comp or dest are empty
        while(getline(file,line)){
            //remove spaces,tabs, returns, and comments from line
            string newString;
            for(int i = 0; (i < line.length() && line[i-1] != '/'); i++){
                if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n') newString += line[i];
            }
            line = newString;

            //check if A-instruction
            if(line.find("@") != string::npos){
                string address = Address(line);
                //cout << lineNumber << ": Address instruction: " << address << endl;
                vector<string> tempVector = {"a", to_string(lineNumber), Address(line)};
                parsedFields.push_back(tempVector);
                lineNumber++;
            }
            //Check if C-instruction
            else if (line.find("=") != string::npos){
                    //cout << lineNumber << ": C-instruction: " << Dest(line) << "/" << Comp(line) << endl;
                    vector<string> tempVector = {"c", Dest(line), Comp(line), "NULL"};
                    parsedFields.push_back(tempVector);
                    lineNumber++;
            }//Check for Jump
            else if (line.find(";") != string::npos){
                   //cout << lineNumber << ": C-instruction: " << Comp(line) << "/" << Jump(line) << endl;
                    vector<string> tempVector = {"c", "NULL", Comp(line), Jump(line)};
                    parsedFields.push_back(tempVector);
                    lineNumber++;
            }
            //check for Label
            else if(line.find('(') != string::npos){
                //cout << lineNumber << ": Label: " << Label(line) << endl;
                vector<string> tempVector = {"label", to_string(lineNumber), Label(line)};
                parsedFields.push_back(tempVector);
            }

        }
        //return parsed vector
        return parsedFields;
    }
    //returns line number which ignores appropriate lines
    int getLineNumber() {return lineNumber;}
};
#endif
