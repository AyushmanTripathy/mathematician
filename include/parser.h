#ifndef PARSER_H
#define PARSER_H

#include "iostream"
#include "network.h"

Network * parse_network(char *);
void stringify_network(Network *, char *);

#endif
