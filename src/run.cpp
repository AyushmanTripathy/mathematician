#include "parser.h"

using namespace std;

Network * net;

int main(int argc, char ** argv) {
  if (argc < 2) return 1;
  net = parse_network(argv[1]);
  double * inputs = new double[net->input_node_count];

  for (int i = 0; i < net->input_node_count; i++) {
    cout << "input[" << i << "]> ";
    cin >> inputs[i];
  }

  cout << "x = " << inputs[0] << ", ";
  cout << "y = " << inputs[1] << endl;
  double * outputs = net->evaluate(inputs, net->input_node_count);
  cout << "[TRUE]\t" << outputs[0] << endl;
  cout << "[FALSE]\t" << outputs[1] << endl;
  delete[] outputs;
}
