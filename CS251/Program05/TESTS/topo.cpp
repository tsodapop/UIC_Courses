
#include <iostream>
#include "Graph.h"
#include "_util.h"


int main(int argc, char *argv[]){
  graph g;
  std::vector<int> id_order;
  std::vector<string> name_order;

  header(argc, argv);

  if(argc != 2) 
    std::cout << "usage:  topo <dag-filename>\n";
  else {
    if(!g.read_file(argv[1]))
      std::cout << "could not open file '" << argv[1] << "'\n";
  }

  show_graph(g);

  if(g.topo_sort(id_order)) 
    std::cout << "topo sort succeeded!\n";
  else 
    std::cout << "topo sort failed (cycle?)!\n";

  g.ids2names(id_order, name_order);

  std::cout << "here is the topological order produced:\n\n";

  pvec(name_order);


  return 0;
}

