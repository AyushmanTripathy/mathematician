#include "parser.h"

int main(int argc, char ** argv) {
  if (argc < 2) return 1;
  Network * net = parse_network(argv[1]);
}
