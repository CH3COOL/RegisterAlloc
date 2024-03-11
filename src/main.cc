#include "du_block.h"
#include <fstream>
#include <iostream>
std::ifstream fin;
du_unit unit;
int main(int argc,char** argv){
    // std::string name;
    // fin>>name;
    // std::cout<<name;
    if(argc != 2){
        printf("argc != 2\n");
        return 0;
    }
    fin.open(argv[1]);
    unit.input(fin);
    unit.emit(std::cout);
    fin.close();
    return 0;
}