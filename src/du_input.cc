#include "du_block.h"
#include <cstdio>
#include <cstring>
void du_instruction::input(std::istream& s){
    s.get();
    char str[80];
    s.getline(str,80);
    char* p = strtok(str," ");
    while(p != NULL){
        int no;
        if(p[0] != 'E' && p[0] != 'e'){
            sscanf(p+1,"%d",&no);
        }
        switch(p[0]){
            case 'W':
            case 'w':
            Write_regs.push_back(no);
            break;
            case 'R':
            case 'r':
            Read_regs.push_back(no);
            break;
            case 'J':
            case 'j':
            Jmp_labels.push_back(no);
            break;
            case 'E':
            case 'e':
            Exit = true;
            default:
            std::cerr<<"Unknown op type\n";
        }
        p = strtok(NULL," ");
    }
}
void du_block::input(std::istream& s){
    std::string labelName;
    s>>labelName;
    int id;
    sscanf(labelName.c_str(),"#L%d:",&id);
    label_id = id;
    while(!s.eof()){
        char c = s.get();
        if(c == '^' || c == '#'){
            s.putback(c);
            return;
        }
        if(c == '.'){
            s.putback(c);
            auto cur_ins = new du_instruction();
            cur_ins->input(s);
            instructions.push_back(cur_ins);
        }
    }
}
void du_function::input(std::istream& s){
    std::string name;
    s>>name;
    // std::cout<<name;
    if(*(name.end()-1) != ':'){
        // std::cerr<<"du_function label must end with :\n";
        return;
    }
    this->func_name = name.substr(1,name.length()-2);
    while(!s.eof()){
        char c = s.get();
        if(c == '^'){
            s.putback(c);
            return;
        }
        if(c == '#'){
            s.putback(c);
            auto cur_blk = new du_block(-1);
            cur_blk->input(s);
            blocks.push_back(cur_blk);
        }
    }
}
void du_unit::input(std::istream& s){
    while(!s.eof()){
        auto cur_func = new du_function("");
        cur_func->input(s);
        functions.push_back(cur_func);
    }
}