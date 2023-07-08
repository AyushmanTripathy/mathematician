#ifndef DATASET_H
#define DATASET_H

#include "stdexcept"
#include "iostream"
#include "fstream"
#include "network.h"

Dataset * load_dataset(std::string&, int);
void free_dataset(Dataset *);

#endif
