#include "generate.h"
#include "string"

using namespace std;

int main(int argc, char ** argv) {
  if (argc < 2) return 1;

  string dataset_location(argv[1]);
  generate(dataset_location);
}
