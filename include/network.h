#ifndef NETWORK_H
#define NETWORK_H

class Layer;

class Node {
  private:
    int expected_input_count;

  public:
    double bias;
    double * weights;

    Node() {};
    Node(int input_count) {
      this->weights = new double[input_count];
    };
    double evaluate(double *, int);
};

class Layer {
  private:
    int nodes_index;
    Node * nodes;

  public:
    int node_count;
    int input_count;

    Layer() {};
    Layer(int node_count, int input_count) {
      this->node_count = node_count;
      this->input_count = input_count;
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
};

class Network {
  private:
   int layer_index;
   int layer_count;
   Layer * layers;

  public:
    int input_node_count;
    int output_node_count;

    Network(int layer_count) {
      this->layer_count = layer_count;
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
};

#endif
