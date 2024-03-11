#include "du_block.h"
void du_instruction::emit(std::ostream& s){
    s<<".";
    if(Exit){
        s<<"| Exit ";
    }
    if(!Write_regs.empty()){
        s<<"| Write:";
        for(auto w : Write_regs){
            s<<"R"<<w<<" ";
        }
    }
    if(!Read_regs.empty()){
        s<<"| Read:";
        for(auto r : Read_regs){
            s<<"R"<<r<<" ";
        }
    }
    if(!Jmp_labels.empty()){
        s<<"| Jmp:";
        for(auto l : Jmp_labels){
            s<<"#L"<<l<<" ";
        }
    }
    s<<"\n";
}

void du_block::emit(std::ostream& s){
    s<<"\t#L"<<label_id<<":\n";
    for(auto ins:instructions){
        s<<"\t\t";
        ins->emit(s);
        // s<<"\n";
    }
}

void du_function::emit(std::ostream& s){
    s<<"^"<<func_name<<":\n";
    for(auto block : blocks){
        block->emit(s);
    }
    s<<"\n";
}

void du_unit::emit(std::ostream& s){
    for(auto function : functions){
        function->emit(s);
    }
}