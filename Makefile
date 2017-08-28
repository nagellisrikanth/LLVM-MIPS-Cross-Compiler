parser: 
	bison -oparser.c parser.y -d -v
	flex -oscanner.c scanner.l
	g++ -g  parser.c \
        scanner.c \
        SymbolTable.cc \
        Type.cc \
        -o parser \
        `llvm-config --cppflags` \
        `llvm-config --ldflags` \
        -lLLVM-3.4 \
        -std=c++11
clean:
	 rm -f lex.yy.c \
         scanner.c \
         parser.c\
         parser.output \
         scanner.cc\
         parser.cc\
         parser\
         parser.h\
         parser.hh \
         pass.so   \
         reaching-def.so \
	 mips.so \




l2m:
	 g++ -fPIC -shared *.cc -o mips.so -std=c++11 `llvm-config --cppflags`

t1:
	 cat test.ll | opt -load ./mips.so -mips
t2: 	
	cat while.ll | opt -load ./mips.so -mips
t3:
	cat whileif.ll | opt -load ./mips.so -mips
opti:
	cat test.ll | opt -load ./mips.so -opti
