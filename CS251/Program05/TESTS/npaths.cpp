
#include <iostream>
#include "Graph.h"
#include "_util.h"


int main(int argc, char *argv[]){
  graph g;
  std::vector<graph::vertex_label> rpt;

  header(argc, argv);

  if(argc != 2) {
    std::cout << "usage:  ./npaths <filename> \n";
    return 0;
  }
  else {
    if(!g.read_file(argv[1])){
      std::cout << "could not open file '" << argv[1] << "'\n";
      return 0;
    }
  }

  // show_graph(g);

  if(!g.dag_num_paths(rpt)) {
    std::cout << "dag_num_paths failed -- Not a DAG?\n";
    return 0;
  }
  else {
    std::cout << "\nNPATHS REPORT:\n\n";
    std::cout << "    [NOTES:  'state' not necessarily meaningful\n" 
              << "             'pred' not meaningful ]\n"
              << "             'dist' not meaningful ]\n\n";

    disp_report(g, rpt, 0,0,0,1,0);
    std::cout << "\nEND NPATHS REPORT\n\n";
  }

  return 0;
}

