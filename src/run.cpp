#include "parser.h"
#include "cmath"

using namespace std;

Network * net;

int main(int argc, char ** argv) {
  if (argc < 2) return 1;
  net = parse_network(argv[1]);

  int input_count = net->input_node_count / net->bit_length;
  double * inputs = new double[net->input_node_count];

  int x;
  for (int i = 0; i < input_count; i++) {
    cout << "input[" << i << "]> ";
    cin >> x;

    int r = pow(2, net->bit_length - 1);
    for (int j = 0; j < net->bit_length;j++) {
      (inputs + (i * net->bit_length))[j] = x / r;
      x = x % r;
      r = r / 2;
    }
  }
  
  double * outputs = net->evaluate(inputs, net->input_node_count);

  /*
  for (int i = 0; i < input_count; i++) {
    for (int j = 0; j < net->bit_length; j++) {
      cout << inputs[i * net->bit_length + j] << " ";
    }
    cout << endl;
  }
  */

  if (outputs[0] > outputs[1]) cout << "[TRUE]";
  else cout << "[FALSE]";
  cout << endl << "surety: " << outputs[0] - outputs[1] << endl;

  cout << "[TRUE]\t" << outputs[0] << endl;
  cout << "[FALSE]\t" << outputs[1] << endl;
  delete[] outputs;
}
