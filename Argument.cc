#include <iostream>
#include "Argument.h"
#include "BasicBlock.h"
namespace mips
{
int Register::next_number = 32;
void Register::dump()
{
    // Base registers
    if (base)
        std::cout << "(";
    // Register number
    std::cout << "$" << number;
    // Base register
    if (base)
         std::cout << ")";
}
void Constant::dump()
{
    std::cout << value;
}
void Label::dump()
{
    std::cout << basic_block->getName();
}
}
