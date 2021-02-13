#pragma once

#include "markov_engine.h"
#include "parser.h"

void terminal(istream& input_stream);
int enter_menu();
void set_system(istream& input_stream,markov_engine& me, parser& p);
void enter_word(markov_engine& me, parser& p);
void help_m();