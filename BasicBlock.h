#ifndef MIPS_BASIC_BLOCK_H
#define MIPS_BASIC_BLOCK_H
#include <iostream>
#include <list>
#include <cassert>
namespace mips
{
// Forward declarations
class Instruction;

class BasicBlock
{
    // Label name
    std::string name;
    
    // List of instructions
    std::list<Instruction *> instructions;
    
    // List of successors and predecessors
    std::list<BasicBlock *> succ;
    std::list<BasicBlock *> pred;

public:
    // Constructor
    BasicBlock(const std::string &name) : name(name)
    {
    }
    
    // Add instruction to basic block
    void addInstruction(Instruction *instruction)
    {
         instructions.push_back(instruction); 
    }
    
    // Add a basic block B2 to the list of successors of the current basic
    // block B1. Also, add B1 to the list of predecessors of B2.
    void addSuccessor(BasicBlock *basic_block)
    {
         assert(this != basic_block);
         succ.push_back(basic_block);
         basic_block->pred.push_back(this);
    }
    
    // Return label name
    const std::string &getName() { return name; }
    
    // Print basic block
    void dump();
};

} 
#endif
