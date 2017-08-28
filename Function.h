#ifndef MIPS_FUNCTION_H
#define MIPS_FUNCTION_H
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "Argument.h"
#include <unordered_map>
namespace mips
{
// Forward declarations
class BasicBlock;
class Register;
class Function
{
    // Table of basic blocks, indexed by name
    std::unordered_map<std::string, BasicBlock *> basic_block_table;
    
    // List of basic blocks, preseving the LLVM order
    std::list<BasicBlock *> basic_blocks;
    
    // Entry and exit basic blocks
    BasicBlock *entry_basic_block;
    BasicBlock *exit_basic_block;

    // Symbol table, associating LLVM variable names to MIPS registers
    std::unordered_map<std::string, Register *> symbol_table;

public:
    // Constructor. It creates an entry and exit basic blocks for the
    // function.
    Function();
    
    // Add a basic block
    void addBasicBlock(BasicBlock *basic_block);
    
    // Get basic block given its label, or nullptr if it doesn't exist.
    BasicBlock *getBasicBlock(const std::string &name);
    
    // Return entry basic block
    BasicBlock *getEntryBasicBlock() { return entry_basic_block; }
    
    // Return exit basic block
    BasicBlock *getExitBasicBlock() { return exit_basic_block; }
    
    // Add symbol to symbol table
    void addSymbol(const std::string &name, Register *reg)
    {
         symbol_table[name] = reg;
    }
    
    // Lookup symbol table, and produce error if symbol not found.
    Register *lookupSymbol(const std::string &name);
    // If the given value is an LLVM variable, return a new register
    // associated with the symbol as read from the symbol table. If the
    // value is an LLVM constant, emit an 'li' instruction in the given
    // basic block, and return the register that was assigned the constant.
    Register *translateLLVMValue(BasicBlock *basic_block,llvm::Value *llvm_value,Register::Direction direction,bool base = false);
    
    // Print it
    void dump();
};

} 
#endif


