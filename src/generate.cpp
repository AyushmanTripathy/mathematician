#include "iostream"
#include "fstream"
#include "cmath"

using namespace std;

ofstream output_file;

const int input_count = 2;
const int output_count = 2;
const int range[] = { 1, 4 };

void relation(int * inputs) {
  if (inputs[0] > inputs[1]) output_file << "1 " << "0";
  else output_file << "0 " << "1";
}

void print_permutation(int * inputs, int index) {
  for (int i = 0; i < input_count; i++) output_file << inputs[i] << " ";
  relation(inputs);
  output_file << endl;
}

void permutation(int * inputs, int index = 0) {
  void (* func) (int *, int) = &permutation;
  if (index == input_count - 1) func = &print_permutation;
  for (int i = range[0]; i < range[1]; i++) {
    inputs[index] = i;
    func(inputs, index + 1);
  }
}

int main(int argc, char ** argv) {
  if (argc < 2) return 1;

  int * inputs = new int[input_count];
  for (int i = 0; i < input_count; i++) inputs[i] = range[0];

  output_file.open(argv[1]);
  output_file << pow(range[1] - range[0], input_count) << endl;
  output_file << input_count << " " << output_count << endl;
  permutation(inputs);
  output_file.close();

  delete[] inputs;
}
