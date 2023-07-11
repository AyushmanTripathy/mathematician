#include "network.h"
#include "dataset.h"
#include "parser.h"
#include "generate.h"

using namespace std;

Network * net;

int main(int argc, char ** argv) {
  if (argc < 3) return 1;

  string dataset_location(argv[2]);
  net = parse_network(argv[1]);

  int batch_count;
  ifstream stats;
  stats.open(dataset_location + "/stats.ssv");
  stats >> batch_count;
  stats.close();

  generate(dataset_location);
  while(1) {
    for (int iter = 0; iter < 100; iter++) {
      double avg = 0;
      for(int i = 1; i <= batch_count; i++) {
        Dataset * data = load_dataset(dataset_location, i);

        net->learn(data);
        avg += net->cost(data);
        free_dataset(data);
      }
      cout << "batch average over iter " << avg / batch_count << endl;
    }
    stringify_network(net, argv[1]);
    cin.get();
  }
}
