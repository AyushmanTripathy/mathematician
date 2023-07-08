#include "dataset.h"

using namespace std;

extern Network * net;

Dataset * load_dataset(string& dataset_location, int index) {
  ifstream dataset;
  dataset.open(dataset_location + "/" + to_string(index) + ".ssv");

  Dataset * data = new Dataset;
  int input_count, output_count, bit_length;
  dataset >> data->length;
  dataset >> input_count >> output_count >> bit_length;

  if (input_count != net->input_node_count)
    throw invalid_argument("Input Node Count not matching!");
  if (output_count != net->output_node_count)
    throw invalid_argument("Output Node Count not matching!");
  if (bit_length != net->bit_length)
    throw invalid_argument("Bit length not matching!");

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

void free_dataset(Dataset * data) {
  for (int i = 0; i < data->length; i++) {
    delete[] data->inputs[i];
    delete[] data->outputs[i];
  }
  delete data;
}
