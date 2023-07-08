#include "generate.h"
#include "parser.h"
#include "dataset.h"
#include "network.h"

#include "cstdio"

using namespace std;

Network * net;

const int test_count = 255;

int random_int(int min, int max) {
  return (((double) rand() / RAND_MAX) * (max - min)) + min;
}

void print_failed_case(int * nums, double * output) {
  cout << nums[0] << " > " << nums[1] << " ";
  printf("\t%f\t", output[0]);
  printf("%f\n", output[1]);
}

int main(int argc, char ** argv) {
  if (argc < 2) return 1;

  net = parse_network(argv[1]);
  double * inputs = new double[net->input_node_count];

  int input_count = net->input_node_count / net->bit_length;
  int * nums = new int[input_count];

  srand(time(0));
  int passed = 0;
  for (int i = 0; i < test_count; i++) {
    for (int x = 0; x < net->input_node_count; x++)
      inputs[x] = (double) random_int(0, 2);

    for (int i = 0; i < input_count; i++)
      nums[i] = 0;

    for (int i = 0; i < input_count; i++) {
      int r = pow(2, net->bit_length - 1);
      for (int x = 0; x < net->bit_length; x++) {
        nums[i] += r * inputs[i * net->bit_length + x];
        r = r / 2;
      }
    }

    double * output = net->evaluate(inputs, net->input_node_count);

    if (nums[0] > nums[1]) {
      if (output[0] > output[1]) passed++;
      else print_failed_case(nums, output);
    } else {
      if (output[0] < output[1]) passed++;
      else print_failed_case(nums, output);
    }

    delete[] output;
  }

  cout << "passing " << ((double) passed / test_count) * 100 << "%" << endl;
}
