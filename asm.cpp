#include "symbolTable.h"
#include "destTable.h"
#include "compTable.h"
#include "jumpTable.h"
#include "parser.h"
#include <fstream>
using namespace std;


int main(int argc, char const *argv[]) {
    Parser parser9000(argv[1]);
    //creating table objects that store appropriate binary values
    SymbolTable symTable;
    DestTable destTable;
    CompTable compTable;
    JumpTable jmpTable;
    //keeps track of user defined variables
    int count = 16;
    vector<vector<string>> parsedFile = parser9000.parseFile();

    //outpute file
    ofstream jackFile;
    jackFile.open ("test.hack");

    //stores label in symbol table using the assembly line number / vector{a_Command, line #, string}
    for(auto v : parsedFile){
        if(v.at(0) == "label"){
            symTable.insert(v.at(2), stoi(v.at(1)));
        }
    }
    //stores user defined variables that are not labels
    for(auto v : parsedFile){
        //stores user defined symbol in symbol table
        if(v.at(0) == "a"){
            //if the variable contains alpha characters it is not a direct address
            if(v.at(2).find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") != string::npos){
                int size = symTable.symbolTable.size();
                symTable.insert(v.at(2), count);
                //if a user variable was actually stored, the count increases
                if (symTable.symbolTable.size() != size) count++;
            }
            else{
                //direct address is stored
                symTable.insert(v.at(2), stoi(v.at(2)));
            }
        }
    }

    //output binary to file using hash map
    //a-ins / vector{a_Command, line #, string}
    //c-ins / vector{c_Command ,dest, comp, jump}
    for(auto v : parsedFile){
        //a instruction
        if(v.at(0) == "a"){
            jackFile << "0"<< symTable.find(v.at(2)) << endl;
        }
        //c-instruction
        else if (v.at(0) == "c"){
            jackFile << "111"<< compTable.find(v.at(2)) << destTable.find(v.at(1)) << jmpTable.find(v.at(3)) << endl;
        }

    }

    //close file
    jackFile.close();

  //   //print out
  //   for (auto& x: symTable.symbolTable) {
  //   std::cout << x.first << ": " << x.second << std::endl;
  // }

    return 0;
}
