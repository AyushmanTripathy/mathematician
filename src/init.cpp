#include "fstream"
#include "random"
#include "iostream"
#include "string"

using namespace std;

ifstream input_file;
ofstream output_file;

int input_count;
int output_count;
int bit_length;

int hidden_layer_count = 0;
int hidden_layer_size = 8;

double random_double(int min, int max) {
  return (((double) rand() / RAND_MAX) * (max - min)) + min;
}

void create_network() {
  int curr_count = hidden_layer_size, prev_count = input_count;
  output_file << hidden_layer_count + 1 << " " << bit_length << endl;

  for (int i = 0; i <= hidden_layer_count; i++) {
    if (i == hidden_layer_count) curr_count = output_count;
    output_file << curr_count << " " << prev_count << endl;

    for (int x = 0; x < curr_count; x++) {
      output_file << random_double(-1, 1) << " ";
      for (int y = 0; y < prev_count; y++)
        output_file << random_double(-1, 1) << " ";
      output_file << endl;
    }

    prev_count = curr_count;
  }
}

int main(int argc, char ** argv) {
  if (argc < 3) return 1;

  string dataset_location(argv[1]);
  input_file.open(dataset_location + "/1.ssv");
  input_file.ignore(256, '\n');
  input_file >> input_count >> output_count >> bit_length;
  input_file.close();

  output_file.open(argv[2]);
  create_network();
  output_file.close();
}
