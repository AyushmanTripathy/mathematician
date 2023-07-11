#ifndef NETWORK_H
#define NETWORK_H

#include "fstream"

typedef struct {
  double ** inputs;
  double ** outputs;
  int length;
} Dataset;

class Node;

class Node {
  private:
    double bias_gradient;
    double * weights_gradient;

    double node_value;
    double activation_value;
    double weighted_input;

    int input_count;

  public:
    double bias;
    double * weights;

    Node() {};
    Node(int input_count) {
      this->weights = new double[input_count];
      this->input_count = input_count;

      this->weights_gradient = new double[input_count];
      for (int i = 0; i < input_count; i++)
        this->weights_gradient[i] = 0;
      this->bias_gradient = 0;
    };
    double evaluate(double *);
    void update_gradient(double *);
    void update_node_value(double);
    void update_node_value(int, Node *, int);
    void apply_gradient(double);
};

class Layer {
  private:
    double * input_activations;
    int nodes_index;
    Node * nodes;

  public:
    int node_count;
    int input_count;

    Layer() {};
    Layer(int node_count, int input_count) {
      this->node_count = node_count;
      this->input_count = input_count;
      this->input_activations = new double[input_count];
      this->nodes = new Node[node_count];
      this->nodes_index = 0;
    };

    void add_node(Node n) {
      if (this->nodes_index == this->node_count)
        throw ("Node Overflow");
      this->nodes[this->nodes_index] = n;
      this->nodes_index++;
    }
    void evaluate(double *, double *);
    void stringify(std::ofstream&);

    void learn(double *);
    void learn(Layer&);

    void apply_gradient(double);
};

class Network {
  private:
    int layer_index;
    Layer * layers;

  public:
    int layer_count;
    int bit_length;
    int input_node_count;
    int output_node_count;

    Network(int layer_count, int bit_length) {
      this->layer_count = layer_count;
      this->bit_length = bit_length;
      this->layer_index = 0;
      this->layers = new Layer[layer_count];
    };

    void add_layer(Layer l) {
      if (this->layer_index == this->layer_count)
        throw ("Layer Overflow");
      this->layers[this->layer_index] = l;
      this->layer_index++;
    }

    double * evaluate(double *, int);
    double cost(Dataset *);
    void learn(Dataset *);
    void stringify(std::ofstream&);
    void apply_gradient(double);
};

#endif
