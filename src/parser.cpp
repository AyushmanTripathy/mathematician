#include "iostream"
#include "fstream"

#include "parser.h"

using namespace std;

Network * parse_network(char * filepath) {
  ifstream network_file;

  network_file.open(filepath);
  int layer_count;
  network_file >> layer_count;

  Network * net = new Network(layer_count);

  int curr_count, prev_count;

  for (int i = 0; i < layer_count; i++) {
    network_file >> curr_count >> prev_count;
    if (i == 0) net->input_node_count = prev_count;

    Layer l = Layer(curr_count, prev_count);

    for (int x = 0; x < curr_count; x++) {
      Node n = Node(prev_count);
      network_file >> n.bias;
      for (int y = 0; y < prev_count; y++)
        network_file >> n.weights[y];
      l.add_node(n);
    }

    net->add_layer(l);
  }
  net->output_node_count = curr_count;

  network_file.close();
  return net;
}

void stringify_network(Network * net, char * filepath) {
  ofstream network_file;
  network_file.open(filepath);
  net->stringify(network_file);
  network_file.close();
}
