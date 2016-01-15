#ifndef _PARSER_H_
#define _PARSER_H_

#include "options.h"

void outputCommands();
void parseOptionsFromArgs(int argc, char* argv[], options_t &options);
void parseOptionsManually(options_t &options, bool START_FROM_SCRATCH = 0);

#endif