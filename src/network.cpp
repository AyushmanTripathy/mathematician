#include "network.h"
#include "cmath"
#include "iostream"

using namespace std;

extern Network * net;
const double h = 0.0000001;

double activation_function(double x) {
  return 1 / (1 + exp(-1 * x));
}

double Node::evaluate(double * input) {
  double x = 0;
  for (int i = 0; i < this->input_count; i++) {
    x += this->weights[i] * input[i];
  }

  x += this->bias;
  this->weighted_input = x;
  this->activation_value = activation_function(x);

  return this->activation_value;
}

void Node::apply_gradient(double learn_rate) {
  for (int i = 0; i < this->input_count; i++) {
    this->weights[i] -= this->weights_gradient[i] * learn_rate;
    this->weights_gradient[i] = 0;
  }
  this->bias -= this->bias_gradient * learn_rate;
  this->bias_gradient = 0;
}

void Layer::evaluate(double * input, double * output) {
  for (int i = 0; i < this->input_count; i++)
    this->input_activations[i] = input[i];
  for (int i = 0; i < this->node_count; i++)
    output[i] = this->nodes[i].evaluate(input);
}

void Layer::apply_gradient(double learn_rate) {
  for (int i = 0; i < this->node_count; i++)
    this->nodes[i].apply_gradient(learn_rate);
}

void Node::update_gradient(double * input_activations) {
  for (int i = 0; i < this->input_count; i++) {
    this->weights_gradient[i] += input_activations[i] * this->node_value;
  }

  this->bias_gradient += 1 * this->node_value;
}

// for output layer
void Layer::learn(double * expected_outputs) {
  for (int i = 0; i < this->node_count; i++) {
    this->nodes[i].update_node_value(expected_outputs[i]);
    this->nodes[i].update_gradient(this->input_activations);
  }
}

// for output layer
void Node::update_node_value(double expected_output) {
  this->node_value = 2 * (this->activation_value - expected_output);
  this->node_value *= this->activation_value * (1 - this->activation_value);
}

// for middle layers
void Layer::learn(Layer& output_layer) {
  for (int i = 0; i < this->node_count; i++) {
    this->nodes[i].update_node_value(i, output_layer.nodes, output_layer.node_count);
    this->nodes[i].update_gradient(this->input_activations);
  }
}

// for middle layers
void Node::update_node_value(int self_index, Node * output_nodes, int output_node_count) {
  this->node_value = 0;
  for (int i = 0; i < output_node_count; i++) {
    this->node_value += output_nodes[i].weights[self_index] * output_nodes[i].node_value;
  }
  this->node_value *= this->activation_value * (1 - this->activation_value);
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
  double * output = new double[20];
  double * prev = new double[20];

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
  for (int i = 0; i < data->length; i++) {
    this->evaluate(data->inputs[i], this->input_node_count);

    Layer output_layer = this->layers[this->layer_count - 1];
    output_layer.learn(data->outputs[i]);
    for (int x = layer_count - 2; x >= 0; x--)
      this->layers[x].learn(this->layers[x + 1]);
  }
  this->apply_gradient(1.0 / data->length);
}

void Network::stringify(ofstream& output_file) {
  output_file << this->layer_count << " " << this->bit_length << endl;
  for (int i = 0; i < this->layer_count; i++)
    this->layers[i].stringify(output_file);
}
