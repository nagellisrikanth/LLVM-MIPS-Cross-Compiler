#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CFG.h"
#include "BasicBlock.h"
#include "Function.h"
#include "Instruction.h"
#include <iostream>
namespace
{
class MIPSPass : public llvm::FunctionPass
{
public:
    // Identifier
    static char ID;
    
    // MIPS function
    mips::Function *mips_function;
    
    // Constructor. The first argument of the parent constructor is
    // a unique pass identifier.
    MIPSPass() : llvm::FunctionPass(ID) { }
    // Virtual function overridden to implement the pass functionality.
    bool runOnFunction(llvm::Function &llvm_function) override;
    void TranslateBasicBlock(llvm::BasicBlock *llvm_basic_block,mips::BasicBlock *mips_basic_block);
    void TranslateInstruction(llvm::Instruction *llvm_instruction,mips::BasicBlock *mips_basic_block);
};

bool MIPSPass::runOnFunction(llvm::Function &llvm_function)
{
    // Create MIPS function
    mips_function = new mips::Function();
    // Add '__entry' basic block
    mips::BasicBlock *mips_entry_basic_block = mips_function->getEntryBasicBlock();
    mips_function->addBasicBlock(mips_entry_basic_block);
    // Create all basic blocks
    for (llvm::Function::iterator llvm_basic_block = llvm_function.begin(),e = llvm_function.end();llvm_basic_block != e;++llvm_basic_block)
    {
         mips::BasicBlock *mips_basic_block =new mips::BasicBlock(llvm_basic_block->getName());
         mips_function->addBasicBlock(mips_basic_block);
    }
    // Set first basic block as successor of function's entry basic block
    llvm::BasicBlock *llvm_first_basic_block = &llvm_function.getEntryBlock();
    mips::BasicBlock *mips_first_basic_block = mips_function->getBasicBlock(llvm_first_basic_block->getName());
    mips_entry_basic_block->addSuccessor(mips_first_basic_block);
    // Code generation for basic blocks
    for (llvm::Function::iterator llvm_basic_block = llvm_function.begin(),e = llvm_function.end();llvm_basic_block != e;++llvm_basic_block)
    {
         mips::BasicBlock *mips_basic_block =mips_function->getBasicBlock(llvm_basic_block->getName());
         TranslateBasicBlock(llvm_basic_block, mips_basic_block);
    }
    // Add '__exit' basic block
    mips::BasicBlock *mips_exit_basic_block = mips_function->getExitBasicBlock();
    mips_function->addBasicBlock(mips_exit_basic_block);
    // Emit 'jr $31' in '__exit' basic block
    mips::Instruction *mips_instruction = new mips::Instruction(mips::Instruction::OpcodeJr);
    mips::Register *mips_register = new mips::Register(31,mips::Register::DirectionInput);
    mips_instruction->addArgument(mips_register);
    mips_exit_basic_block->addInstruction(mips_instruction);
    // Print MIPS function
    mips_function->dump();
    // Function was not modified
    return false;
}

void MIPSPass::TranslateBasicBlock(llvm::BasicBlock *llvm_basic_block,mips::BasicBlock *mips_basic_block)
{
	
   // Traverse instructions
    for (llvm::BasicBlock::iterator llvm_instruction = llvm_basic_block->begin(),e = llvm_basic_block->end();llvm_instruction != e;++llvm_instruction)
    {
         TranslateInstruction(llvm_instruction, mips_basic_block);
    } 
}
void MIPSPass::TranslateInstruction(llvm::Instruction *llvm_instruction,mips::BasicBlock *mips_basic_block)
{
    
     switch (llvm_instruction->getOpcode())
    {
    case llvm::Instruction::Alloca:
    {
         // Get alloca instruction
         llvm::AllocaInst *alloca_inst = llvm::cast<llvm::AllocaInst>(llvm_instruction);
         // Check type
         llvm::Type *type = alloca_inst->getAllocatedType();
         if (!type->isIntegerTy(32))
         {
              std::cerr << "Unsupported type in alloca\n";
		exit(1); 
	 }
	// Get '__entry' and '__exit' basic block
     	mips::Instruction *mips_instruction;
     	mips::BasicBlock *mips_entry_basic_block = mips_function->getEntryBasicBlock();
     	mips::BasicBlock *mips_exit_basic_block = mips_function->getExitBasicBlock();
     	// Emit 'addi $sp, $sp, -4' in '__entry' basic block
     	mips_instruction = new mips::Instruction(mips::Instruction::OpcodeAddi);
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionOutput));
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionInput));
     	mips_instruction->addArgument(new mips::Constant(-4));
     	mips_entry_basic_block->addInstruction(mips_instruction);
     	// Emit 'move $temp, $sp' in '__entry' basic block.
     	// Store '$temp' in symbol table
     	mips_instruction = new mips::Instruction(mips::Instruction::OpcodeMove);
     	mips::Register *dest = mips::Register::newRegister(mips::Register::DirectionOutput);
     	mips_instruction->addArgument(dest);
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionInput));
     	mips_entry_basic_block->addInstruction(mips_instruction);
     	mips_function->addSymbol(llvm_instruction->getName(), dest);
     	// Emit 'addi $sp, $sp, 4' in '__exit' basic block
     	mips_instruction = new mips::Instruction(mips::Instruction::OpcodeAddi);
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionOutput));
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionInput));
     	mips_instruction->addArgument(new mips::Constant(4));
     	mips_exit_basic_block->addInstruction(mips_instruction);
	break; 
   }
   case llvm::Instruction::Load:
   {
     // Emit 'load $dest, 0($address)'
     mips::Instruction *mips_instruction = new mips::Instruction(mips::Instruction::OpcodeLw);
     // Data
     mips::Register *dest = mips::Register::newRegister(mips::Register::DirectionOutput);
     mips_instruction->addArgument(dest);
     mips_function->addSymbol(llvm_instruction->getName(), dest);
     // Offset
     mips_instruction->addArgument(new mips::Constant(0));
     // Base address
     llvm::Value *llvm_address = llvm_instruction->getOperand(0);
     mips::Register *mips_address = mips_function->translateLLVMValue(mips_basic_block,llvm_address,mips::Register::DirectionInput,true);
     mips_instruction->addArgument(mips_address);
     // Add instruction
     mips_basic_block->addInstruction(mips_instruction);
     break; 
    }
   case llvm::Instruction::Store: 
   {
     // Emit 'store $src, 0($address)'
     mips::Instruction *mips_instruction = new mips::Instruction(mips::Instruction::OpcodeSw);
     // Data
     llvm::Value *llvm_data = llvm_instruction->getOperand(0);
     mips::Register *mips_data = mips_function->translateLLVMValue(mips_basic_block,llvm_data,mips::Register::DirectionInput);
     mips_instruction->addArgument(mips_data);
     // Offset
     mips_instruction->addArgument(new mips::Constant(0));
     // Base address
     llvm::Value *llvm_address = llvm_instruction->getOperand(1);
     mips::Register *mips_address = mips_function->translateLLVMValue(mips_basic_block,llvm_address,mips::Register::DirectionInput,true);
     mips_instruction->addArgument(mips_address);
     // Add instruction
     mips_basic_block->addInstruction(mips_instruction);
     break; 
    }
    case llvm::Instruction::ICmp:
    {
    	 // Destination register
     	mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
     	mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
     	// First operand
     	llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
	mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
     	// Second operand
     	llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
 	mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
     	// Operation depending on condition
     	llvm::ICmpInst *icmp_instruction = llvm::cast<llvm::ICmpInst>(llvm_instruction);
     	llvm::CmpInst::Predicate pred = icmp_instruction->getSignedPredicate();
     	//llvm::errs() <<pred<<"\n";
	switch (pred)
     	{
     		case llvm::ICmpInst::ICMP_SGT:
     		{
         		// Emit 'slt' instruction
         		mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSlt);
         		mips_basic_block->addInstruction(mips_instruction);
         		mips_instruction->addArgument(mips_dest);
         		// Invert order of src1 and src2
         		mips_instruction->addArgument(mips_src2);
         		mips_instruction->addArgument(mips_src1);
         		break;
		}
		// Added support---project //
		case llvm::ICmpInst::ICMP_SLT:
		{
			// Emit 'slt' instruction
			mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSlt);
			mips_basic_block->addInstruction(mips_instruction);
                        mips_instruction->addArgument(mips_dest);
		        mips_instruction->addArgument(mips_src1);
                        mips_instruction->addArgument(mips_src2);
			break;
               }
	   	case llvm::ICmpInst::ICMP_SLE:
	   	{
			//Emit 'sle' instruction 
			mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSlt);	
			mips_basic_block->addInstruction(mips_instruction);
			mips_instruction->addArgument(mips_dest);
                	mips_instruction->addArgument(mips_src1);
                	mips_instruction->addArgument(mips_src2);
			mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeXori);
			mips_basic_block->addInstruction(instruction);
			instruction->addArgument(mips_dest);
			instruction->addArgument(mips_src1);
			instruction->addArgument(new mips::Constant(1));
			break;
 	  	}

	       case llvm::ICmpInst::ICMP_EQ:
	       {
			mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSub);
                        mips_basic_block->addInstruction(mips_instruction);
                        mips_instruction->addArgument(mips_dest);
                        mips_instruction->addArgument(mips_src1);
                        mips_instruction->addArgument(mips_src2);
                        mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeSltu);
                        mips_basic_block->addInstruction(instruction);
                        instruction->addArgument(mips_dest);
                        instruction->addArgument(new mips::Constant(0));
                        instruction->addArgument(mips_src1);
			mips::Instruction *xinstruction =new mips::Instruction(mips::Instruction::OpcodeXori);
                        mips_basic_block->addInstruction(xinstruction);
                        xinstruction->addArgument(mips_dest);
                        xinstruction->addArgument(mips_src1);
                        xinstruction->addArgument(new mips::Constant(1));
                        break;


	       }
            case llvm::ICmpInst::ICMP_NE:
	    {
			mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSub);
                        mips_basic_block->addInstruction(mips_instruction);
                        mips_instruction->addArgument(mips_dest);
                        mips_instruction->addArgument(mips_src1);
                        mips_instruction->addArgument(mips_src2);
                        mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeSltu);
                        mips_basic_block->addInstruction(instruction);
                        instruction->addArgument(mips_dest);
                        instruction->addArgument(new mips::Constant(0));
                        instruction->addArgument(mips_src1);
			break;
            }		 
		default:
         	std::cerr << "icmp predicate not supported\n";
		exit(1); 
	}
		break; 
      }
	case llvm::Instruction::Br:
	{
     		// Get branch instruction
     		llvm::BranchInst *branch_inst = llvm::cast<llvm::BranchInst>(llvm_instruction);
     		// Conditional branches
     		if (branch_inst->isConditional())
     		{
         		// Emit 'beq $src, $zero, succ2
         		mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeBeq);
         		mips_basic_block->addInstruction(instruction);
         		// First argument
         		llvm::Value *llvm_cond = llvm_instruction->getOperand(0);
         		mips::Register *mips_cond = mips_function->lookupSymbol(llvm_cond->getName());
         		mips_cond = new mips::Register(mips_cond->getNumber(),mips::Register::DirectionInput);
         		instruction->addArgument(mips_cond);
         		// Second argument
         		mips::Register *mips_zero = new mips::Register(0,mips::Register::DirectionInput);
         		instruction->addArgument(mips_zero);
         		// Third argument
         		mips::BasicBlock *succ2 = mips_function->getBasicBlock(branch_inst->getSuccessor(1)->getName());
         		mips::Label *label = new mips::Label(succ2);
         		instruction->addArgument(label);
     		}
     		// Emit 'j succ1'
     		mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     		mips::BasicBlock *succ1 = mips_function->getBasicBlock(branch_inst->getSuccessor(0)->getName());
     		mips::Label *label = new mips::Label(succ1);
     		instruction->addArgument(label);
     		mips_basic_block->addInstruction(instruction);
     		break;
	}
	case llvm::Instruction::Ret:
	{
     		// Emit 'j __exit'
     		mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     		mips::Label *label = new mips::Label(mips_function->getExitBasicBlock());
     		instruction->addArgument(label);
     		mips_basic_block->addInstruction(instruction);
     		// Set exit basic block as successor
     		mips_basic_block->addSuccessor(mips_function->getExitBasicBlock());
     		break;
	}
	case llvm::Instruction::Add:
	{	
	   //mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeAdd);
	   mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
           mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
	   llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
           mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
	   llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
          // mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
           if(llvm_src1->getName()==""||llvm_src2->getName()=="")
           {
                mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeAddi);
                mips_basic_block->addInstruction(instruction);
                instruction->addArgument(mips_dest);
                instruction->addArgument(mips_src1);
                llvm::ConstantInt* constant_src=llvm::dyn_cast<llvm::ConstantInt>(llvm_src2);
                int csrc=constant_src->getSExtValue();
                instruction->addArgument(new mips::Constant(csrc));

          }
          else
          {
                mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
                mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeAdd);
                mips_basic_block->addInstruction(instruction);
                instruction->addArgument(mips_dest);
                instruction->addArgument(mips_src1);
                instruction->addArgument(mips_src2);
          }
           break;

       } 
        // Added support //
	case llvm::Instruction::Sub:
       {

		mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
           	mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
           	llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
           	mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
           	llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
           	mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
                mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeSub);
                mips_basic_block->addInstruction(instruction);
                instruction->addArgument(mips_dest);
                instruction->addArgument(mips_src1);
                instruction->addArgument(mips_src2);
 		break;        
  

       }
	//Added Support //
	case llvm::Instruction::Mul:
       {

                mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
                mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
                llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
                mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
                llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
                mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
                mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeMult);
                mips_basic_block->addInstruction(instruction);
               // instruction->addArgument(mips_dest);
                instruction->addArgument(mips_src1);
                instruction->addArgument(mips_src2);
                break;


       }	
	default:
	std::cerr << "Unsupported LLVM instruction: ";
	llvm_instruction->dump();
	std::cerr << '\n';
	exit(1);
    }
}
//Added support//
/* This is a Optimization for MIPS which will generate a compact Optimized code*/
//MIPS Optimization Pass 
class MIPSOptiPass : public llvm::FunctionPass
{
public:
    // Identifier
    static char ID;
    
    // MIPS function
    mips::Function *mips_function;
    
    // Constructor. The first argument of the parent constructor is
    // a unique pass identifier.
    MIPSOptiPass() : llvm::FunctionPass(ID) { }
    // Virtual function overridden to implement the pass functionality.
    bool runOnFunction(llvm::Function &llvm_function) override;
    void TranslateBasicBlock(llvm::BasicBlock *llvm_basic_block,mips::BasicBlock *mips_basic_block);
    void TranslateInstruction(llvm::Instruction *llvm_instruction,llvm::Instruction *next_llvm_instruction,llvm::Instruction *previous_llvm_instruction , mips::BasicBlock *mips_basic_block);

};

bool MIPSOptiPass::runOnFunction(llvm::Function &llvm_function)
{
    // Create MIPS function
    mips_function = new mips::Function();
    // Add '__entry' basic block
    mips::BasicBlock *mips_entry_basic_block = mips_function->getEntryBasicBlock();
    mips_function->addBasicBlock(mips_entry_basic_block);
    // Create all basic blocks
    for (llvm::Function::iterator llvm_basic_block = llvm_function.begin(),e = llvm_function.end();llvm_basic_block != e;++llvm_basic_block)
    {
         mips::BasicBlock *mips_basic_block =new mips::BasicBlock(llvm_basic_block->getName());
         mips_function->addBasicBlock(mips_basic_block);
    }
    // Set first basic block as successor of function's entry basic block
    llvm::BasicBlock *llvm_first_basic_block = &llvm_function.getEntryBlock();
    mips::BasicBlock *mips_first_basic_block = mips_function->getBasicBlock(llvm_first_basic_block->getName());
    mips_entry_basic_block->addSuccessor(mips_first_basic_block);
    // Code generation for basic blocks
    for (llvm::Function::iterator llvm_basic_block = llvm_function.begin(),e = llvm_function.end();llvm_basic_block != e;++llvm_basic_block)
    {
         mips::BasicBlock *mips_basic_block =mips_function->getBasicBlock(llvm_basic_block->getName());
         TranslateBasicBlock(llvm_basic_block, mips_basic_block);
    }
    // Add '__exit' basic block
    mips::BasicBlock *mips_exit_basic_block = mips_function->getExitBasicBlock();
    mips_function->addBasicBlock(mips_exit_basic_block);
    // Emit 'jr $31' in '__exit' basic block
    mips::Instruction *mips_instruction = new mips::Instruction(mips::Instruction::OpcodeJr);
    mips::Register *mips_register = new mips::Register(31,mips::Register::DirectionInput);
    mips_instruction->addArgument(mips_register);
    mips_exit_basic_block->addInstruction(mips_instruction);
    // Print MIPS function
    mips_function->dump();
    // Function was not modified
    return false;
}


void MIPSOptiPass::TranslateBasicBlock(llvm::BasicBlock *llvm_basic_block,mips::BasicBlock *mips_basic_block)
{
 
   llvm::BasicBlock::iterator next;
   llvm::BasicBlock::iterator previous;
    for (llvm::BasicBlock::iterator llvm_instruction = llvm_basic_block->begin(),e = llvm_basic_block->end();llvm_instruction != e;++llvm_instruction)
    {
       	next=llvm_instruction;
	previous=llvm_instruction;
        if(llvm_instruction!=llvm_basic_block->end())
		next++;
	if(llvm_instruction!=llvm_basic_block->begin())
		previous--;
	TranslateInstruction(llvm_instruction,next,previous, mips_basic_block);


    } 
}
void MIPSOptiPass::TranslateInstruction(llvm::Instruction *llvm_instruction,llvm::Instruction *next_llvm_instruction,llvm::Instruction *previous_llvm_instruction,mips::BasicBlock *mips_basic_block)
{
   //llvm::errs()<< next_llvm_instruction->getOpcodeName()<<'\n';
    switch (llvm_instruction->getOpcode())
    {
    case llvm::Instruction::Alloca:
    {
         // Get alloca instruction
         llvm::AllocaInst *alloca_inst = llvm::cast<llvm::AllocaInst>(llvm_instruction);
         // Check type
         llvm::Type *type = alloca_inst->getAllocatedType();
         if (!type->isIntegerTy(32))
         {
              std::cerr << "Unsupported type in alloca\n";
		exit(1); 
	 }
	// Get '__entry' and '__exit' basic block
     	mips::Instruction *mips_instruction;
     	mips::BasicBlock *mips_entry_basic_block = mips_function->getEntryBasicBlock();
     	mips::BasicBlock *mips_exit_basic_block = mips_function->getExitBasicBlock();
     	// Emit 'addi $sp, $sp, -4' in '__entry' basic block
     	mips_instruction = new mips::Instruction(mips::Instruction::OpcodeAddi);
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionOutput));
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionInput));
     	mips_instruction->addArgument(new mips::Constant(-4));
     	mips_entry_basic_block->addInstruction(mips_instruction);
     	// Emit 'move $temp, $sp' in '__entry' basic block.
     	// Store '$temp' in symbol table
     	mips_instruction = new mips::Instruction(mips::Instruction::OpcodeMove);
     	mips::Register *dest = mips::Register::newRegister(mips::Register::DirectionOutput);
     	mips_instruction->addArgument(dest);
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionInput));
     	mips_entry_basic_block->addInstruction(mips_instruction);
     	mips_function->addSymbol(llvm_instruction->getName(), dest);
     	// Emit 'addi $sp, $sp, 4' in '__exit' basic block
     	mips_instruction = new mips::Instruction(mips::Instruction::OpcodeAddi);
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionOutput));
     	mips_instruction->addArgument(new mips::Register(29,mips::Register::DirectionInput));
     	mips_instruction->addArgument(new mips::Constant(4));
     	mips_exit_basic_block->addInstruction(mips_instruction);
	break; 
   }
   case llvm::Instruction::Load:
   {
     // Emit 'load $dest, 0($address)'
     mips::Instruction *mips_instruction = new mips::Instruction(mips::Instruction::OpcodeLw);
     // Data
     mips::Register *dest = mips::Register::newRegister(mips::Register::DirectionOutput);
     mips_instruction->addArgument(dest);
     mips_function->addSymbol(llvm_instruction->getName(), dest);
     // Offset
     mips_instruction->addArgument(new mips::Constant(0));
     // Base address
     llvm::Value *llvm_address = llvm_instruction->getOperand(0);
     mips::Register *mips_address = mips_function->translateLLVMValue(mips_basic_block,llvm_address,mips::Register::DirectionInput,true);
     mips_instruction->addArgument(mips_address);
     // Add instruction
     mips_basic_block->addInstruction(mips_instruction);
     break; 
    }
   case llvm::Instruction::Store: 
   {
     // Emit 'store $src, 0($address)'
     mips::Instruction *mips_instruction = new mips::Instruction(mips::Instruction::OpcodeSw);
     // Data
     llvm::Value *llvm_data = llvm_instruction->getOperand(0);
     mips::Register *mips_data = mips_function->translateLLVMValue(mips_basic_block,llvm_data,mips::Register::DirectionInput);
     mips_instruction->addArgument(mips_data);
     // Offset
     mips_instruction->addArgument(new mips::Constant(0));
     // Base address
     llvm::Value *llvm_address = llvm_instruction->getOperand(1);
     mips::Register *mips_address = mips_function->translateLLVMValue(mips_basic_block,llvm_address,mips::Register::DirectionInput,true);
     mips_instruction->addArgument(mips_address);
     // Add instruction
     mips_basic_block->addInstruction(mips_instruction);
     break; 
    }
    case llvm::Instruction::ICmp:
    {
    	 // Destination register
     	mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
     	mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
     	// First operand
     	llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
	mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
     	// Second operand
     	llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
 	mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
     	// Operation depending on condition
     	llvm::ICmpInst *icmp_instruction = llvm::cast<llvm::ICmpInst>(llvm_instruction);
     	llvm::CmpInst::Predicate pred = icmp_instruction->getSignedPredicate();
	switch (pred)
     	{
     		case llvm::ICmpInst::ICMP_SGT:
     		{
			// check if ther is a 'br' inst after ICmp inst 
			if(next_llvm_instruction->getOpcode()==2)     			
			{	
				llvm::BranchInst *branch_inst = llvm::cast<llvm::BranchInst>(next_llvm_instruction);		
				// Conditional branches
     				if (branch_inst->isConditional())
     				{
         				// Emit 'bgt $src, $temp, succ2
         				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeBgt);
         				mips_basic_block->addInstruction(instruction);
         				// First argument
         				llvm::Value *llvm_cond = llvm_instruction->getOperand(0);
         				mips::Register *mips_cond = mips_function->lookupSymbol(llvm_cond->getName());
         				mips_cond = new mips::Register(mips_cond->getNumber(),mips::Register::DirectionInput);
         				instruction->addArgument(mips_cond);
         				// Second argument
         				llvm::Value *llvm_cond1 = llvm_instruction->getOperand(1);
                                        mips::Register *mips_cond1 = mips_function->lookupSymbol(llvm_cond1->getName());
                                        mips_cond1 = new mips::Register(mips_cond1->getNumber(),mips::Register::DirectionInput);
                                        instruction->addArgument(mips_cond1);

					//mips::Register *mips_zero = new mips::Register(0,mips::Register::DirectionInput);
         				//instruction->addArgument(mips_zero);
         				// Third argument
         				mips::BasicBlock *succ2 = mips_function->getBasicBlock(branch_inst->getSuccessor(0)->getName());
         				mips::Label *label = new mips::Label(succ2);
         				instruction->addArgument(label);
     				}
     				// Emit 'j succ1'
     				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     				mips::BasicBlock *succ1 = mips_function->getBasicBlock(branch_inst->getSuccessor(1)->getName());
     				mips::Label *label = new mips::Label(succ1);
     				instruction->addArgument(label);
     				mips_basic_block->addInstruction(instruction);
			}
			//ICmp is not followed by 'br' instruction
			else
			{
         			// Emit 'slt' instruction
         			mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSlt);
         			mips_basic_block->addInstruction(mips_instruction);
         			mips_instruction->addArgument(mips_dest);
         			// Invert order of src1 and src2
         			mips_instruction->addArgument(mips_src2);
         			mips_instruction->addArgument(mips_src1);

			}
		      break;
		}

		case llvm::ICmpInst::ICMP_SLT:
		{
			//Check if ICMP_SLT is follwed by a br inst  
			if(next_llvm_instruction->getOpcode()==2)     			
			{	
				llvm::BranchInst *branch_inst = llvm::cast<llvm::BranchInst>(next_llvm_instruction);		
				// Conditional branches
     				if (branch_inst->isConditional())
     				{
         				// Emit 'blt $src, $temp, succ2
         				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeBlt);
         				mips_basic_block->addInstruction(instruction);
         				// First argument
         				llvm::Value *llvm_cond = llvm_instruction->getOperand(0);
         				mips::Register *mips_cond = mips_function->lookupSymbol(llvm_cond->getName());
         				mips_cond = new mips::Register(mips_cond->getNumber(),mips::Register::DirectionInput);
         				instruction->addArgument(mips_cond);
         				// Second argument
         				llvm::Value *llvm_cond1 = llvm_instruction->getOperand(1);
                                        mips::Register *mips_cond1 = mips_function->lookupSymbol(llvm_cond1->getName());
                                        mips_cond1 = new mips::Register(mips_cond1->getNumber(),mips::Register::DirectionInput);
                                        instruction->addArgument(mips_cond1);
					//mips::Register *mips_zero = new mips::Register(0,mips::Register::DirectionInput);
         				//instruction->addArgument(mips_zero);
         				// Third argument
         				mips::BasicBlock *succ2 = mips_function->getBasicBlock(branch_inst->getSuccessor(0)->getName());
         				mips::Label *label = new mips::Label(succ2);
         				instruction->addArgument(label);
     				}
     				// Emit 'j succ1'
     				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     				mips::BasicBlock *succ1 = mips_function->getBasicBlock(branch_inst->getSuccessor(1)->getName());
     				mips::Label *label = new mips::Label(succ1);
     				instruction->addArgument(label);
     				mips_basic_block->addInstruction(instruction);
			}
			//There no br inst after ICMP_SLT
			else
			{			
				// Emit 'slt' instruction
				mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSlt);
				mips_basic_block->addInstruction(mips_instruction);
                        	mips_instruction->addArgument(mips_dest);
		        	mips_instruction->addArgument(mips_src1);
                        	mips_instruction->addArgument(mips_src2);
			}
			break;
               }
	   	case llvm::ICmpInst::ICMP_SLE:
	   	{
			//Check if ICMP_SLE is follwed by a br inst 
			if(next_llvm_instruction->getOpcode()==2)     			
			{	
				llvm::BranchInst *branch_inst = llvm::cast<llvm::BranchInst>(next_llvm_instruction);		
				// Conditional branches
     				if (branch_inst->isConditional())
     				{
         				// Emit 'beq $src, $zero, succ2
         				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeBle);
         				mips_basic_block->addInstruction(instruction);
         				// First argument
         				llvm::Value *llvm_cond = llvm_instruction->getOperand(0);
         				mips::Register *mips_cond = mips_function->lookupSymbol(llvm_cond->getName());
         				mips_cond = new mips::Register(mips_cond->getNumber(),mips::Register::DirectionInput);
         				instruction->addArgument(mips_cond);
         				// Second argument
         				llvm::Value *llvm_cond1 = llvm_instruction->getOperand(1);
                                        mips::Register *mips_cond1 = mips_function->lookupSymbol(llvm_cond1->getName());
                                        mips_cond1 = new mips::Register(mips_cond1->getNumber(),mips::Register::DirectionInput);
                                        instruction->addArgument(mips_cond1);
					//mips::Register *mips_zero = new mips::Register(0,mips::Register::DirectionInput);
         				//instruction->addArgument(mips_zero);
         				// Third argument
         				mips::BasicBlock *succ2 = mips_function->getBasicBlock(branch_inst->getSuccessor(0)->getName());
         				mips::Label *label = new mips::Label(succ2);
         				instruction->addArgument(label);
     				}
     				// Emit 'j succ1'
     				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     				mips::BasicBlock *succ1 = mips_function->getBasicBlock(branch_inst->getSuccessor(1)->getName());
     				mips::Label *label = new mips::Label(succ1);
     				instruction->addArgument(label);
     				mips_basic_block->addInstruction(instruction);
			}			
			//There no br inst after ICMP_SLE
			else
			{			
				//Emit 'sle' instruction 
				mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSlt);	
				mips_basic_block->addInstruction(mips_instruction);
				mips_instruction->addArgument(mips_dest);
                		mips_instruction->addArgument(mips_src1);
                		mips_instruction->addArgument(mips_src2);
				mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeXori);
				mips_basic_block->addInstruction(instruction);
				instruction->addArgument(mips_dest);
				instruction->addArgument(mips_src1);
				instruction->addArgument(new mips::Constant(1));
			}
			break;
 	  	}

	       case llvm::ICmpInst::ICMP_EQ:
	       {
			//Check if ICMP_EQ is follwed by a br inst 
			if(next_llvm_instruction->getOpcode()==2)     			
			{	
				llvm::BranchInst *branch_inst = llvm::cast<llvm::BranchInst>(next_llvm_instruction);		
				// Conditional branches
     				if (branch_inst->isConditional())
     				{
         				// Emit 'beq $src, $zero, succ2
         				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeBeq);
         				mips_basic_block->addInstruction(instruction);
         				// First argument
         				llvm::Value *llvm_cond = llvm_instruction->getOperand(0);
         				mips::Register *mips_cond = mips_function->lookupSymbol(llvm_cond->getName());
         				mips_cond = new mips::Register(mips_cond->getNumber(),mips::Register::DirectionInput);
         				instruction->addArgument(mips_cond);
         				// Second argument
         				llvm::Value *llvm_cond1 = llvm_instruction->getOperand(1);
                                        mips::Register *mips_cond1 = mips_function->lookupSymbol(llvm_cond1->getName());
                                        mips_cond1 = new mips::Register(mips_cond1->getNumber(),mips::Register::DirectionInput);
                                        instruction->addArgument(mips_cond1);
				//	mips::Register *mips_zero = new mips::Register(0,mips::Register::DirectionInput);
         			//	instruction->addArgument(mips_zero);
         				// Third argument
         				mips::BasicBlock *succ2 = mips_function->getBasicBlock(branch_inst->getSuccessor(0)->getName());
         				mips::Label *label = new mips::Label(succ2);
         				instruction->addArgument(label);
     				}
     				// Emit 'j succ1'
     				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     				mips::BasicBlock *succ1 = mips_function->getBasicBlock(branch_inst->getSuccessor(1)->getName());
     				mips::Label *label = new mips::Label(succ1);
     				instruction->addArgument(label);
     				mips_basic_block->addInstruction(instruction);
			}
			// There is no br inst after ICMP_EQ			
			else
			{
				mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSub);
                        	mips_basic_block->addInstruction(mips_instruction);
                        	mips_instruction->addArgument(mips_dest);
                        	mips_instruction->addArgument(mips_src1);
                        	mips_instruction->addArgument(mips_src2);
                        	mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeSltu);
                        	mips_basic_block->addInstruction(instruction);
                        	instruction->addArgument(mips_dest);
                        	instruction->addArgument(new mips::Constant(0));
                        	instruction->addArgument(mips_src1);
				mips::Instruction *xinstruction =new mips::Instruction(mips::Instruction::OpcodeXori);
                        	mips_basic_block->addInstruction(xinstruction);
                        	xinstruction->addArgument(mips_dest);
                        	xinstruction->addArgument(mips_src1);
                        	xinstruction->addArgument(new mips::Constant(1));
			}
                        break;


	       }
            case llvm::ICmpInst::ICMP_NE:
	    {
			//Check if ICMP_NE is follwed by a br inst 
			if(next_llvm_instruction->getOpcode()==2)     			
			{	
				llvm::BranchInst *branch_inst = llvm::cast<llvm::BranchInst>(next_llvm_instruction);		
				// Conditional branches
     				if (branch_inst->isConditional())
     				{
         				// Emit 'beq $src, $zero, succ2
         				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeBne);
         				mips_basic_block->addInstruction(instruction);
         				// First argument
         				llvm::Value *llvm_cond = llvm_instruction->getOperand(0);
         				mips::Register *mips_cond = mips_function->lookupSymbol(llvm_cond->getName());
         				mips_cond = new mips::Register(mips_cond->getNumber(),mips::Register::DirectionInput);
         				instruction->addArgument(mips_cond);
         				// Second argument
         				llvm::Value *llvm_cond1 = llvm_instruction->getOperand(0);
                                        mips::Register *mips_cond1 = mips_function->lookupSymbol(llvm_cond1->getName());
                                        mips_cond1 = new mips::Register(mips_cond1->getNumber(),mips::Register::DirectionInput);
                                        instruction->addArgument(mips_cond1);
			//	mips::Register *mips_zero = new mips::Register(0,mips::Register::DirectionInput);
         			//	instruction->addArgument(mips_zero);
         				// Third argument
         				mips::BasicBlock *succ2 = mips_function->getBasicBlock(branch_inst->getSuccessor(0)->getName());
         				mips::Label *label = new mips::Label(succ2);
         				instruction->addArgument(label);
     				}
     				// Emit 'j succ1'
     				mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     				mips::BasicBlock *succ1 = mips_function->getBasicBlock(branch_inst->getSuccessor(1)->getName());
     				mips::Label *label = new mips::Label(succ1);
     				instruction->addArgument(label);
     				mips_basic_block->addInstruction(instruction);
			}
			//There is no br inst after  ICMP_NE 	
			else
			{			
				mips::Instruction *mips_instruction =new mips::Instruction(mips::Instruction::OpcodeSub);
                        	mips_basic_block->addInstruction(mips_instruction);
                        	mips_instruction->addArgument(mips_dest);
                        	mips_instruction->addArgument(mips_src1);
                        	mips_instruction->addArgument(mips_src2);
                        	mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeSltu);
                        	mips_basic_block->addInstruction(instruction);
                        	instruction->addArgument(mips_dest);
                        	instruction->addArgument(new mips::Constant(0));
                        	instruction->addArgument(mips_src1);
			}
			break;
            }		 
		default:
         	std::cerr << "icmp predicate not supported\n";
		exit(1); 
	}
		break; 
      }
	case llvm::Instruction::Br:
	{
     		
		//llvm::errs()<<previous_llvm_instruction->getOpcode()<<"\n";
  		if(previous_llvm_instruction->getOpcode()==46)
		{
				break;	
		}
    		else
		{
			// Get branch instruction
			llvm::BranchInst *branch_inst = llvm::cast<llvm::BranchInst>(llvm_instruction);
			//Conditional branches
			if (branch_inst->isConditional())
    			{
      			// Emit 'beq $src, $zero, succ2
         			mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeBeq);
         			mips_basic_block->addInstruction(instruction);
         			// First argument
         			llvm::Value *llvm_cond = llvm_instruction->getOperand(0);
         			mips::Register *mips_cond = mips_function->lookupSymbol(llvm_cond->getName());
         			mips_cond = new mips::Register(mips_cond->getNumber(),mips::Register::DirectionInput);
         			instruction->addArgument(mips_cond);
         			// Second argument
         			mips::Register *mips_zero = new mips::Register(0,mips::Register::DirectionInput);
         			instruction->addArgument(mips_zero);
         			// Third argument
         			mips::BasicBlock *succ2 = mips_function->getBasicBlock(branch_inst->getSuccessor(1)->getName());
         			mips::Label *label = new mips::Label(succ2);
         			instruction->addArgument(label);
     			}
     			// Emit 'j succ1'
     			mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     			mips::BasicBlock *succ1 = mips_function->getBasicBlock(branch_inst->getSuccessor(0)->getName());
     			mips::Label *label = new mips::Label(succ1);
     			instruction->addArgument(label);
			mips_basic_block->addInstruction(instruction);
 
   		}
     		break;
	}
	case llvm::Instruction::Ret:
	{
     		// Emit 'j __exit'
     		mips::Instruction *instruction = new mips::Instruction(mips::Instruction::OpcodeJ);
     		mips::Label *label = new mips::Label(mips_function->getExitBasicBlock());
     		instruction->addArgument(label);
     		mips_basic_block->addInstruction(instruction);
     		// Set exit basic block as successor
     		mips_basic_block->addSuccessor(mips_function->getExitBasicBlock());
     		break;
	}
	case llvm::Instruction::Add:
	{	
	   //mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeAdd);
	   mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
           mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
	   llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
           mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
	   llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
         //  mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
          if(llvm_src1->getName()==""||llvm_src2->getName()=="")
 	  {
	   	mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeAddi);
           	mips_basic_block->addInstruction(instruction);
           	instruction->addArgument(mips_dest);
           	instruction->addArgument(mips_src1);
		llvm::ConstantInt* constant_src=llvm::dyn_cast<llvm::ConstantInt>(llvm_src2);
		int csrc=constant_src->getSExtValue();
           	instruction->addArgument(new mips::Constant(csrc));

	 }  
	 else
	 {
	 	mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
		mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeAdd);
       	 	mips_basic_block->addInstruction(instruction);
	   	instruction->addArgument(mips_dest);
           	instruction->addArgument(mips_src1);
           	instruction->addArgument(mips_src2);
         }
	   break;
       } 
        // Added support //
	case llvm::Instruction::Sub:
       {

	  	mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
           	mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
           	llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
           	mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
           	llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
                mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
                mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeSub);
                mips_basic_block->addInstruction(instruction);
                instruction->addArgument(mips_dest);
                instruction->addArgument(mips_src1);
                instruction->addArgument(mips_src2);
 		break;        
  

       }
	//Added Support //
	case llvm::Instruction::Mul:
       {

                mips::Register *mips_dest = mips::Register::newRegister(mips::Register::DirectionOutput);
                mips_function->addSymbol(llvm_instruction->getName(), mips_dest);
                llvm::Value *llvm_src1 = llvm_instruction->getOperand(0);
                mips::Register *mips_src1 = mips_function->translateLLVMValue(mips_basic_block,llvm_src1,mips::Register::DirectionInput);
                llvm::Value *llvm_src2 = llvm_instruction->getOperand(1);
                mips::Register *mips_src2 = mips_function->translateLLVMValue(mips_basic_block,llvm_src2,mips::Register::DirectionInput);
                mips::Instruction *instruction =new mips::Instruction(mips::Instruction::OpcodeMult);
                mips_basic_block->addInstruction(instruction);
               // instruction->addArgument(mips_dest);
                instruction->addArgument(mips_src1);
                instruction->addArgument(mips_src2);
                break;


       }	
	default:
	std::cerr << "Unsupported LLVM instruction: ";
	llvm_instruction->dump();
	std::cerr << '\n';
	exit(1);
    }
}

// Pass identifier
char MIPSPass::ID = 0;
char MIPSOptiPass::ID=0;
// Pass registration
static llvm::RegisterPass<MIPSPass> X("mips","MIPS code generation pass",false,false);
static llvm::RegisterPass<MIPSOptiPass> Y("opti","MIPS code optimization pass", false,false);
}
