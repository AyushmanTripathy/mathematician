#include "parser.h"

#include "iostream"
#include "fstream"

using namespace std;

Network * net;

Dataset * load_dataset(char * filepath) {
  ifstream dataset;
  dataset.open(filepath);

  Dataset * data = new Dataset;
  int input_count, output_count;
  dataset >> data->length;
  dataset >> input_count >> output_count;

  if (input_count != net->input_node_count)
    throw "Input Node Count not matching!";
  if (output_count != net->output_node_count)
    throw "Output Node Count not matching!";

  data->inputs = new double * [data->length];
  data->outputs = new double * [data->length];

  for (int i = 0; i < data->length; i++) {
    double * input = new double[input_count];
    double * output = new double[output_count];

    for (int x = 0; x < input_count; x++)
      dataset >> input[x];
    for (int x = 0; x < output_count; x++)
      dataset >> output[x];

    data->inputs[i] = input;
    data->outputs[i] = output;
  }

  dataset.close();
  return data;
}

int main(int argc, char ** argv) {
  if (argc < 3) return 1;

  net = parse_network(argv[1]);
  Dataset * data = load_dataset(argv[2]);

  for(int iter = 0; iter < 50; iter++) {
    net->learn(data);
    net->apply_gradient(0.1);
    cout << net->cost(data) << endl;
  }
  stringify_network(net, argv[1]);
}
