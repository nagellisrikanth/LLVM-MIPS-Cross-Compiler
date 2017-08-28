#include "Instruction.h"
namespace mips
{
std::string Instruction::names[Instruction::OpcodeMax] = {
    "",
    "add",
    "addi",
    "addiu",
    "addu",
    "sub",
    "subu",
    "and",
    "andi",
    "nor",
    "or",
    "ori",
    "xor",
    "xori",
    "sll",
    "srl",
    "sra",
    "sllv",
    "srav",
    "slt",
    "slti",
    "sltiu",
    "sltu",
    "beq",
    "bne",
    "blt",
    "bgt",
    "ble",
    "bge",
    "j",
    "jal",
    "jr",
    "jalr",
    "move",
    "lb",
    "lbu",
    "lh",
    "lhu",
    "lui",
    "lw",
    "li",
    "la",
    "sb",
    "sh",
    "sw",
    "div",
    "divu",
    "mult",
    "multu",
    "mfhi",
    "mflo",
    "syscall"
};

void Instruction::dump()
{
    // Instruction name
   std::cout << names[opcode];
    
    // Arguments
    std::string comma = " ";
    for (Argument *argument : arguments)
    {
         // Print comma (only if argument is not a base register)
         
	if (!Register::isBaseRegister(argument))
		std::cout << comma;
	
	 // Print argument
        argument->dump();
         // Update comma
	comma = ", ";
     }	
     // Done
    std::cout << "\n";    
}

}
