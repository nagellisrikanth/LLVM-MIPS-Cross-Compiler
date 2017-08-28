#ifndef MIPS_ARGUMENT_H
#define MIPS_ARGUMENT_H
namespace mips
{
	// Forward declarations
	class BasicBlock;
	class Argument
	{
	public:
    		// Dump the argument (abstract function)
    		virtual void dump() = 0;
	};
class Register : public Argument
{
	public:
    		// Data-flow direction
    		enum Direction
    		{
         		DirectionInvalid,
         		DirectionInput,
         		DirectionOutput
    		};
	private:
    		// Input or output register
    		Direction direction = DirectionInvalid;
    		// Register number
    		int number;
    		// True if register is a base address
    		bool base;
    		// Register ID counter
    		static int next_number;
	public:
    		// Return whether a generic argument object is a base register. This is
    		// used for instruction printing purposes.
    		static bool isBaseRegister(Argument *argument)
    		{
         		Register *r = dynamic_cast<Register *>(argument);
         		return r && r->isBase();
    		}

		// Return a new register argument.
		static Register *newRegister(Direction direction, bool base = false)
		{
     			return new Register(next_number++, direction, base);
		}
		// Constructor
		Register(int number, Direction direction, bool base = false) :number(number),direction(direction),base(base){ }

    		// Return input or output direction
    		Direction getDirection() { return direction; }
    	
		// Return register number
    		int getNumber() { return number; }
    		
		// Return whether register is a base register
    		bool isBase() { return base; }
    	
		// Print argument
    		void dump();
};


class Constant : public Argument
{
    // Value of the constant
    int value;
public:
    // Constructor
    Constant(int value) : value(value){ }
    // Return constant value
    int getValue() { return value; }
    // Print argument
    void dump();
};


class Label : public Argument
{
    // Associated basic block
    BasicBlock *basic_block;
public:
    // Constructor
    Label(BasicBlock *basic_block) : basic_block(basic_block){ }
    // Print argument
    void dump();
};

} 
#endif

