
#include <iostream>
#include "Graph.h"
#include "_util.h"


int main(int argc, char *argv[]){
  graph g;
  std::vector<graph::vertex_label> rpt;

  header(argc, argv);

  if(argc != 2) {
    std::cout << "usage:  ./cpaths <filename> \n";
    return 0;
  }
  else {
    if(!g.read_file(argv[1])){
      std::cout << "could not open file '" << argv[1] << "'\n";
      return 0;
    }
  }

  show_graph(g);

  if(!g.dag_critical_paths(rpt)) {
    std::cout << "dag_critical_paths failed -- Not a DAG?\n";
    return 0;
  }
  else {
    std::cout << "\nCPATHS REPORT CRITICAL PATH LEN AND # CRIT PATHS DISPLAYED:\n" 
      << "     [NOTES:  'state' not necessarily meaningful\n"
      << "              'npaths' not necessarily meaningful]\n\n";
    // g.disp_report(rpt, true);
    disp_report(g, rpt, 1,0,0,1,0);
    std::cout << "\nEND CPATHS REPORT\n\n";
  }

  return 0;
}

