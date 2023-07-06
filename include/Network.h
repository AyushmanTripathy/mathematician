#ifndef NETWORK_H
#define NETWORK_H

class Node {
  public:
    double bias;
    double * weights;

    Node() {};
    Node(int input_count) {
      this->weights = new double[input_count];
    }
};

class Layer {
  int node_count;
  int input_count;
  Node * nodes;

  private:
    int nodes_index;
  public:
    Layer() {};
    Layer(int node_count, int input_count) {
      this->node_count = node_count;
      this->input_count = input_count;
      this->nodes = new Node[node_count];
      this->nodes_index = 0;
    };

    void add_node(Node n) {
      this->nodes[this->nodes_index] = n;
      this->nodes_index++;
    }
};

class Network {
  int layer_count;
  Layer * layers;

  private:
   int layer_index;
  public:
    Network(int layer_count) {
      this->layer_count = layer_count;
      this->layer_index = 0;
      this->layers = new Layer[layer_count];
    };

    void add_layer(Layer l) {
      this->layers[this->layer_index] = l;
      this->layer_index++;
    }
};

#endif
