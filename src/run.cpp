#include "parser.h"

using namespace std;

Network * net;

int main(int argc, char ** argv) {
  double inputs[] = { 100, 2, 0, 0 };
  int input_count = 2;

  if (argc < 2) return 1;
  net = parse_network(argv[1]);

  cout << "x = " << inputs[0] << ", ";
  cout << "y = " << inputs[1] << endl;
  double * outputs = net->evaluate(inputs, input_count);
  cout << "[TRUE]\t" << outputs[0] << endl;
  cout << "[FALSE]\t" << outputs[1] << endl;
  delete[] outputs;
}
