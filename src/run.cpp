#include "parser.h"

using namespace std;

int main(int argc, char ** argv) {
  double inputs[] = { 0.1, 0.2, 0, 0 };
  int input_count = 2;

  if (argc < 2) return 1;
  Network * net = parse_network(argv[1]);

  double * output = net->evaluate(inputs, input_count);
  cout << "[TRUE]\t" << output[0] << endl;
  cout << "[FALSE]\t" << output[1] << endl;

  delete[] output;
}
