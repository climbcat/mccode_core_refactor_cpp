#include "lib/jg_baselayer.h"

#include "src/cogen/mccode.h"


#include "src/cogen/instrument.tab.h"
#include "src/cogen/mccogen.h"

#include "src/cogen/lex.yy.c"
#include "src/cogen/instrument.tab.c"


void RunProgram() {
    TimeFunction;

    FILE *file;
    int err;

    yydebug = 0;      // If 1, then bison gives verbose parser debug info.

    palloc(instrument_definition); // Allocate instrument def. structure.
    // init root instrument to NULL
    instrument_definition->formals   = NULL;
    instrument_definition->name      = NULL;
    instrument_definition->decls     = NULL;
    instrument_definition->inits     = NULL;
    instrument_definition->saves     = NULL;
    instrument_definition->finals    = NULL;
    instrument_definition->compmap   = NULL;
    instrument_definition->groupmap  = NULL;
    instrument_definition->complist  = NULL;
    instrument_definition->grouplist = NULL;
    instrument_definition->metadata  = NULL;
    instrument_definition->has_included_instr=0;
    comp_instances      = NULL;
    comp_instances_list = NULL;
    group_instances     = NULL;
    group_instances_list= NULL;
    parse_command_line(g_argc, g_argv);
    if(!strcmp(instr_current_filename, "-"))
    {
        instrument_definition->source = str_dup("<stdin>");
        file = fdopen(0, "r");  // Lone '-' designates stdin.
    }
    else
    {
        instrument_definition->source = str_dup(instr_current_filename);
        file = fopen(instr_current_filename, "r");
    }
    if(file == NULL) {
        fatal_error(MCCODE_NAME ": Instrument definition file `%s' not found\n", instr_current_filename);
    }
    instrument_definition->quoted_source = str_quote(instrument_definition->source);
    if (verbose) {
        fprintf(stderr, MCCODE_NAME " version " MCCODE_VERSION "\n");
        fprintf(stderr, "Analyzing file            %s\n", instrument_definition->quoted_source);
    }
    instr_current_line = 1;
    lex_new_file(file);
    read_components = symtab_create(); // Create table of components.
    lib_instances   = symtab_create(); // Create table of libraries.
    err = mc_yyparse();
    if (err != 0 && !error_encountered) {
        error_encountered++;
    }
    if(error_encountered != 0)
    {
        //print_error(MCCODE_NAME ": %i Errors encountered during parse of %s.\n", error_encountered, instr_current_filename);
        if (verbose) {
            fprintf(stderr, "Please check the usual grammar:\n");
            fprintf(stderr, "DEFINE INSTRUMENT\n");
            fprintf(stderr, "DECLARE\n");
            fprintf(stderr, "INITIALIZE\n");
            fprintf(stderr, "TRACE\n");
            fprintf(stderr, "  {SPLIT} COMPONENT name = comp(parameters) {WHEN condition}\n");
            fprintf(stderr, "  AT (...) [RELATIVE [reference|PREVIOUS] | ABSOLUTE]\n");
            fprintf(stderr, "  {ROTATED {RELATIVE [reference|PREVIOUS] | ABSOLUTE} }\n");
            fprintf(stderr, "  {GROUP group_name}\n");
            fprintf(stderr, "  {EXTEND C_code}\n");
            fprintf(stderr, "  {JUMP [reference|PREVIOUS|MYSELF|NEXT] [ITERATE number_of_times | WHEN condition]\n");
            fprintf(stderr, "END\n");
            fprintf(stderr, "as well as '%%{ ... %%}' blocks.\n\n");
        }
        exit(1);
    }
    fclose(file);

    if (verbose) {
        fprintf(stderr, "Starting to create C code %s\n", output_filename);
    }
    cogen(output_filename, instrument_definition);

    if (verbose) {
        fprintf(stderr, "Generated          C code %s from %s\n", output_filename, instrument_definition->source);
    }
    fprintf(stderr, "CFLAGS=%s\n", instrument_definition->dependency);
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

