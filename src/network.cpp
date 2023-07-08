#include "network.h"
#include "cmath"
#include "iostream"

using namespace std;

extern Network * net;
const double h = 0.001;

double activation_function(double x) {
  return 1 / (1 + exp(x));
}

double Node::evaluate(double * input, int length) {
  double x = 0;
  for (int i = 0; i < length; i++) {
    x += this->weights[i] * input[i];
  }
  return activation_function(x + this->bias);
}

void Node::apply_gradient(double learn_rate) {
  for (int i = 0; i < this->input_count; i++) {
    this->weights[i] -= this->weights_gradient[i] * learn_rate;
  }
  this->bias -= this->bias_gradient * learn_rate;
}

void Node::learn(double cost, Dataset * data) {
  for (int i = 0; i < this->input_count; i++) {
    this->weights[i] += h;
    double slope = (net->cost(data) - cost) / h;
    this->weights[i] -= h;
    this->weights_gradient[i] = slope;
  }

  this->bias += h;
  double slope = (net->cost(data) - cost) / h;
  this->bias -= h;
  this->bias_gradient = slope;
}

void Layer::evaluate(double * input, double * output) {
  for (int i = 0; i < this->node_count; i++)
    output[i] = this->nodes[i].evaluate(input, this->input_count);
}

void Layer::apply_gradient(double learn_rate) {
  for (int i = 0; i < this->node_count; i++)
    this->nodes[i].apply_gradient(learn_rate);
}

void Layer::learn(double cost, Dataset * data) {
  for (int i = 0; i < this->node_count; i++)
    this->nodes[i].learn(cost, data);
}

void Layer::stringify(ofstream& output_file) {
  output_file << this->node_count << " " << this->input_count << endl;
  for (int i = 0; i < this->node_count; i++) {
    output_file << this->nodes[i].bias << " ";
    for (int j = 0; j < this->input_count; j++)
      output_file << this->nodes[i].weights[j] << " ";
    output_file << endl;
  }
}

double * Network::evaluate(double * inputs, int input_count) {
  double * output = new double[10];
  double * prev = new double[10];

  for (int i = 0; i < this->layer_count; i++) {
    this->layers[i].evaluate(i == 0 ? inputs: prev, output);
    input_count = this->layers[i].node_count;

    if (i + 1 != this->layer_count) {
      for (int x = 0; x < input_count; x++)
        prev[i] = output[i];
    }
  }

  delete[] prev;
  return output;
}

double Network::cost(Dataset * data) {
  double cost = 0;
  for (int i = 0; i < data->length; i++) {
    double * output = this->evaluate(data->inputs[i], this->input_node_count);
    for (int x = 0; x < this->output_node_count; x++)
      cost += pow(output[x] - data->outputs[i][x],2);
    delete[] output;
  }
  return cost / data->length;
}

void Network::apply_gradient(double learn_rate) {
  for (int i = 0; i < this->layer_count; i++)
    this->layers[i].apply_gradient(learn_rate);
}

void Network::learn(Dataset * data) {
  double cost = this->cost(data);
  for (int i = 0; i < this->layer_count; i++)
    this->layers[i].learn(cost, data);
}

void Network::stringify(ofstream& output_file) {
  output_file << this->layer_count << " " << this->bit_length << endl;
  for (int i = 0; i < this->layer_count; i++)
    this->layers[i].stringify(output_file);
}
