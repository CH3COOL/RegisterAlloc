#ifndef DU_BLOCK_H
#define DU_BLOCK_H
#include "machine.h"
#include <deque>
class du_instruction{
private:
public:
    std::vector<int>Read_regs;
    std::vector<int>Write_regs;
    std::vector<int>Jmp_labels;
    bool Exit;
    du_instruction():Exit(false){}
    void emit(std::ostream& s);
    void input(std::istream& s);
};
class du_function;
class du_unit;
class du_block : public MachineBlock<du_instruction*,du_function*>{
public:
    du_block(int id):MachineBlock(id){}
    void emit(std::ostream& s);
    void input(std::istream& s);
};
class du_function : public MachineFunction<du_block*,du_unit*>{
public:
    du_function(std::string name):MachineFunction(name){}
    void emit(std::ostream& s);
    void input(std::istream& s);
};
class du_unit : public MachineUnit<du_function*>{
public:
    void emit(std::ostream& s);
    void input(std::istream& s);
};
#endif