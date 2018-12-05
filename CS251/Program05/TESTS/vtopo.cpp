
#include <iostream>
#include "Graph.h"

#include "_util.h"


int main(int argc, char *argv[]){
  graph g;
  vector<int> id_order;
  vector<string> name_order;

  header(argc, argv);

  if(argc != 3) {
    std::cout << "usage:  ./vtopo <graph-file> <vertex-order-file>\n";
    return 0;
  }
  else {
    if(!g.read_file(argv[1])){
      std::cout << "could not open file '" << argv[1] << "'\n";
      return 0;
    }
  }

  if(!file2name_vec(g, argv[2], name_order)){
    std::cout << "failed reading vertex-order file '" <<
      argv[2] << "'\n";
    return 0;
  }
  if(!name_vec2id_vec(g, name_order, id_order)) {
    std::cout << "failed converting name-vec to id-vec (SHOULD NOT HAPPEN!)\n";
    return 0;
  }


  show_graph(g);


  if(g.valid_topo_order(id_order)) {
    std::cout << "@      RESULT: valid_topo_order() SAYS:  YES!\n\n";
  }
  else {
    std::cout << "@      RESULT: valid_topo_order() SAYS:  NO!\n\n";
  }

  return 0;
}

