#include "lib/jg_baselayer.h"

#include "src/cogen/mccode.h"
#include "src/cogen/mccogen.h"

void RunProgram() {
    TimeFunction;

    printf("Executing program ...\n");
}


int main (int argc, char **argv) {
    TimeProgram;

    if (CLAContainsArg("--help", argc, argv) || CLAContainsArg("-h", argc, argv)) {
        printf("--help:          display help (this text)\n");
        printf("--test:          run essential test routines\n");
    }
    else if (CLAContainsArg("--test", argc, argv)) {
        printf("There are no tests yet\n");
    }
    else {
        InitBaselayer();
        RunProgram();
    }
}

