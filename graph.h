#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

class Graph{
  public:
    void createGraph(const string& filename); //reads input file and creates adjacency list from the actors and movies
    void write_to_output(const string& input_file, const string& output_file); //runs program to get desired output and writes to the output file
 
  private:
    unordered_map<string, vector<pair<string, string>>> graph;
    void addEdge(const string& actor1, const string& actor2, const string& movie);
    vector<string> findPath(string& actor1, string& actor2); //finds the shortest path between the actors
    vector<string> findPath(unordered_map<string, pair<string, string>>& mp, const string& actor1, const string& actor2);//helper function for findPath
};

#endif
