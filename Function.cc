#include "BasicBlock.h"
#include "Function.h"
#include "Instruction.h"
namespace mips
{

	Function::Function()
	{
    		entry_basic_block = new BasicBlock("__entry");
    		exit_basic_block = new BasicBlock("__exit");
	}
	void Function::addBasicBlock(BasicBlock *basic_block)
	{
    		basic_block_table[basic_block->getName()] = basic_block;
    		basic_blocks.push_back(basic_block);
	}
	BasicBlock *Function::getBasicBlock(const std::string &name)
	{
    		auto it = basic_block_table.find(name);
    		return it == basic_block_table.end() ? nullptr : it->second;
	}
	Register *Function::lookupSymbol(const std::string &name)
	{
    		auto it = symbol_table.find(name);
    		if (it == symbol_table.end())
    		{
         		std::cerr << "Error: symbol '" << name << "' not found\n";
			exit(1); 
		}
    		return it->second;
	}
	Register *Function::translateLLVMValue(BasicBlock *basic_block,llvm::Value *llvm_value,Register::Direction direction,bool base)
	{
    		if (llvm_value->getValueID() == llvm::Value::ConstantIntVal)
    		{
         		// Emit 'li $dest, value'
         		Instruction *instruction = new Instruction(Instruction::OpcodeLi);
         		basic_block->addInstruction(instruction);
         		// First Argument
         		Register *dest = Register::newRegister(Register::DirectionOutput);
         		instruction->addArgument(dest);
         		// Second argument
         		llvm::ConstantInt *llvm_constant = llvm::cast<llvm::ConstantInt>(llvm_value);
         		Constant *constant = new Constant(llvm_constant->getSExtValue());
         		instruction->addArgument(constant);
         		// Return copy of created register
         		return new Register(dest->getNumber(), direction, base);
    		}
		else
 		{
         		Register *reg = lookupSymbol(llvm_value->getName());
         		return new Register(reg->getNumber(), direction, base);
    		}
	}
	void Function::dump()
	{
    		// Print all basic blocks
    		for (BasicBlock *basic_block : basic_blocks) 
			basic_block->dump();
	}
}	

