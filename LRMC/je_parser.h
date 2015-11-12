#ifndef _JE_PARSER_H_
#define _JE_PARSER_H_

#include "je_options.h"

void outputCommands();
void parseOptionsFromArgs(int argc, char* argv[], OPTIONS &options);
void parseOptionsManually(OPTIONS &options, bool START_FROM_SCRATCH = 0);

#endif