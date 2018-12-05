
#include <iostream>
#include "Graph.h"
#include "_util.h"


int main(int argc, char *argv[]){
  graph g;
  std::vector<graph::vertex_label> dfs_rpt;
  bool has_cycle;

  header(argc, argv);

  if(argc != 3) {
    std::cout << "usage:  ./dfs <filename> <source-vertex>\n";
    return 0;
  }
  else {
    if(!g.read_file(argv[1])){
      std::cout << "could not open file '" << argv[1] << "'\n";
      return 0;
    }
  }

  show_graph(g);

  if(!g.dfs(argv[2], dfs_rpt, has_cycle)) {
    std::cout << "dfs failed -- bad source vertex name '" <<
      argv[2] << "'\n";
    return 0;
  }
  else {
    std::cout << "\nDFS COMPLETE\n\n";
    if(has_cycle) 
      std::cout << "   cycle found!\n";
    else
      std::cout << "   no cycle found\n";
    std::cout << "\nDFS REPORT:\n\n";
    disp_report(g, dfs_rpt, 0,0,0,0,1);
    std::cout << "\nEND DFS REPORT\n\n";
  }
  return 0;
}

