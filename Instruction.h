#ifndef MIPS_INSTRUCTION_H
#define MIPS_INSTRUCTION_H
#include <iostream>
#include <list>
#include "Argument.h"
namespace mips
{
class Instruction
{
public:
    // Instruction kinds
    enum Opcode
    {
         OpcodeInvalid = 0,
         OpcodeAdd,
         OpcodeAddi,
         OpcodeAddiu,
         OpcodeAddu,
         OpcodeSub,
         OpcodeSubu,
         OpcodeAnd,
         OpcodeAndi,
         OpcodeNor,
         OpcodeOr,
         OpcodeOri,
         OpcodeXor,
         OpcodeXori,
         OpcodeSll,
         OpcodeSrl,
         OpcodeSra,
         OpcodeSllv,
         OpcodeSrav,
         OpcodeSlt,
         OpcodeSlti,
         OpcodeSltiu,
         OpcodeSltu,
         OpcodeBeq,
         OpcodeBne,
         OpcodeBlt,
         OpcodeBgt,
         OpcodeBle,
         OpcodeBge,
         OpcodeJ,
         OpcodeJal,
         OpcodeJr,
         OpcodeJalr,
         OpcodeMove,
         OpcodeLb,
         OpcodeLbu,
         OpcodeLh,
         OpcodeLhu,
         OpcodeLui,
         OpcodeLw,
         OpcodeLi,
         OpcodeLa,
         OpcodeSb,
         OpcodeSh,
         OpcodeSw,
         OpcodeDiv,
         OpcodeDivu,
         OpcodeMult,
         OpcodeMultu,
         OpcodeMfhi,
         OpcodeMflo,
         OpcodeSyscall,
         OpcodeMax 
};
private:
    // Instruction names
    static std::string names[OpcodeMax];
    
    // Opcode
    Opcode opcode;
    
    // List of arguments
    std::list<Argument *> arguments;

public:
    // Constructor
    Instruction(Opcode opcode) : opcode(opcode){}
    // Add an argument
    void addArgument(Argument *argument)
    {
         arguments.push_back(argument);
    }
    // Print instruction
    void dump();
};

} 
#endif

