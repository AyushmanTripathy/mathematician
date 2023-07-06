#include "network.h"
#include "iostream"

using namespace std;

double sigmod(double x) {
  return (double) 1 / x;
}

double Node::evaluate(double * input, int length) {
  double x = 0;
  for (int i = 0; i < length; i++) {
    x += this->weights[i] * input[i];
  }
  return sigmod(x - this->bias);
}

void Layer::evaluate(double * input, double * output) {
  for (int i = 0; i < this->node_count; i++)
    output[i] = this->nodes[i].evaluate(input, this->input_count);
}

double * Network::evaluate(double * inputs, int input_count) {
  if (this->input_node_count != input_count) 
    throw ("Invalid input");

  double * tmp, * output = new double[4];
  for (int i = 0; i < this->layer_count; i++) {
    this->layers[i].evaluate(inputs, output);
    input_count = this->layers[i].node_count;

    tmp = inputs;
    inputs = output;
    output = tmp;
  }

  return inputs;
}
