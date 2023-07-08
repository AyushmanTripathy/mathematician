#include "generate.h"

using namespace std;

ofstream output_file;

double random_int(int min, int max) {
  return (int) (((double) rand() / RAND_MAX) * (max - min)) + min;
}

void number(int x) {
  int r = pow(2, bit_length - 1);
  for(int i = bit_length - 1; i >= 0; i--) {
    output_file << x / r << " ";
    x = x % r;
    r = r / 2;
  }
}

void print_permutation(int * inputs) {
  number(inputs[0]);
  number(inputs[1]);
  if (inputs[0] > inputs[1]) output_file << "1 " << "0";
  else output_file << "0 " << "1";
  output_file << endl;
}

void generate(string& dataset_location) {
  int * inputs = new int[input_count];

  output_file.open(dataset_location + "/stats.ssv");
  output_file << batch_count << endl;
  output_file << batch_size << endl;
  output_file.close();

  srand(time(0));
  for(int i = 1; i <= batch_count; i++) {
    output_file.open(dataset_location + "/" + to_string(i) + ".ssv");
    output_file << batch_size << endl;
    output_file << input_count * bit_length << " " << output_count << " " << bit_length << endl;
    for (int x = 0; x < batch_size; x++) {
      for (int o = 0; o < input_count; o++) 
        inputs[o] = random_int(range[0], range[1]);
      print_permutation(inputs);
    }
    output_file.close();
  } 
  delete[] inputs;
}
