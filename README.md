A refactoring of the mccode core, goals: 

- easilly build the code generator (mcstas/mxtrace tools) with only the core source files + flex/bison
- port the code generator core to C++ (for extended tool usage)
- port the simulation runtime to C++
- more easilly debug the generated / runtime code while also editing the code generation, by having only the cogen and simulation core code in the project

Current status: 

- essential source code for code generation and simulation were extracted from the main McCode repository and re-organized into a simple structure, along with many of the .comp and .instr files, etc.
- code generation core ported to C++, which compiles
- ported memory allcoation and list usage for C++
- ported flex/bison files instrument.l and instrument.y to C++
- flex/bison output files are slightly edited, currently (but easy to generate and diff)
- using "flex intstrument.l" and "bison --header instrument.y"
- the compiled tool is able to run and allocate memory, but the parser is broken
- possibly the flex/bison calls could be missing some args
- possibly: try one more time to generate for C++ with "bison --header instrument -LC++"

- tldr: cogen core code was ported to C++, but the generated parser code faults. consequently, no experiments or efforts were done to port the simulation code code.

Compiling:

<pre>
g++ main.cpp -o mcstas_pp</code>
./mcstas_pp                                            # prints help text
./mcstas_pp comps/examples/PSI/PSI_DMC/PSI_DMC.instr   # seg faults during parser step
</pre>

or 

<pre>
mkdir build
cd build
cmake ..
make
</pre>

