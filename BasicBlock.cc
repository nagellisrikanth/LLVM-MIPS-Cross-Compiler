#include "BasicBlock.h"
#include "Instruction.h"
namespace mips
{
void BasicBlock::dump()
{
    std::cout << name<<":\n"; 
    for (Instruction *instruction : instructions)
    {
         std::cout << "\t";
         instruction->dump();
    }
} 

}
