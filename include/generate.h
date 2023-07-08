#ifndef GENERATE_H
#define GENERATE_H

#include "iostream"
#include "fstream"
#include "cmath"
#include "string"
#include "ctime"

const int bit_length = 8;
const int input_count = 2;
const int output_count = 2;

const int batch_size = 100;
const int batch_count = 100;
const int range[] = { 0, 255 };

void generate(std::string&);

#endif
