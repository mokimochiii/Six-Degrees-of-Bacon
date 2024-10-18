#include "graph.h"
using namespace std;

void Graph :: addEdge(const string& actor1, const string& actor2, const string& movie){
  graph[actor1].emplace_back(actor2, movie);
  //in this case we use emplace back to avoid creating a temporary pair to add into the map
  //this is more efficient than using push_back
}

vector<string> Graph :: findPath(string& actor1, string& actor2){
  if(graph.find(actor1) == graph.end() || graph.find(actor2) == graph.end()) return {"Not present"}; //if the actors are not in the graph
  if(actor1 == actor2) return {actor1};

  unordered_map<string, pair<string, string>> mp; //to construct final path
  unordered_set<string> visited; //keep track of visited vertices to avoid cycles
  queue<string> q; //use a queue for BFS to visit each vertex layer by layer

  q.push(actor1);
  visited.insert(actor1);

  while(!q.empty()){
    string current = q.front();
    q.pop();

    for(const auto& neighbor : graph[current]){ //for every neighbors of the current vertex
      if(visited.find(neighbor.first) == visited.end()){ //if not visited
        mp[neighbor.first] = make_pair(current, neighbor.second); //creating new map of same format map[actor1] = {actor2, movie}
        //this is like leaving breadcrumbs to trace actor1 from actor2 when the path is found
        if(neighbor.first == actor2) return findPath(mp, actor1, actor2); //backtracking from actor2 to actor1 to find path
        visited.insert(neighbor.first);
        q.push(neighbor.first);
      }
    }
  }
  return {"Not present"};
}

vector<string> Graph :: findPath(unordered_map<string, pair<string, string>>& mp, const string& actor1, const string& actor2){
  //note that this function will only be called if it is certain that there is a path between actor1 and actor2
  vector<string> path;
  string current = actor2;

  while(current != actor1){
    const auto& [parent, movie] = mp.at(current); //backtracking the map from actor2 to find the path to actor1
    path.push_back(current);
    path.push_back("-(" + movie + ")- ");
    current = parent;
  }
  path.push_back(actor1); //completed backtracking
  reverse(path.begin(), path.end()); //correct formatting
  return path;
}

//will create graph from cleaned_movielist.txt
void Graph :: createGraph(const string& filename){
  ifstream file(filename);
  string line;

  while(getline(file, line)){ //parsing input data
    istringstream iss(line); //create copy of each line
    string movie;
    iss >> movie; //first string of each line is the movie name 
    //the rest of the line contains the actors

    vector<string> actors;
    string actor;
    //make a list of the cast for each movie
    while(iss >> actor){
      actors.push_back(actor);
    }

    //we create the graph datastructure by adding specifying that all the actors in the movie are connected
    //will run through all combinations of actors
    //we create edges both from actor1 to actor2 and vice versa so that the graph is not directed
    //the graph is not directed because we are keeping track of groups rather than individual values
    for(size_t i = 0; i < actors.size(); ++i){
      for(size_t j = i + 1; j < actors.size(); ++j){
        addEdge(actors[i], actors[j], movie);
        addEdge(actors[j], actors[i], movie);
      }
    }
  }
}

//will take care of input output operations
void Graph :: write_to_output(const string& input_file, const string& output_file){
  ifstream input(input_file);
  ofstream output(output_file);
  string line;

  while(getline(input, line)){
    istringstream iss(line);
    string actor1, actor2;
    iss >> actor1 >> actor2;

    vector<string> path = findPath(actor1, actor2);

    if(path.size() == 1){ //only one actor
      output << path[0] << endl;
    }else{
      for(size_t i = 0; i < path.size(); ++i){
        output << path[i];
        if(i < path.size() - 1 && i % 2 == 0) output << " ";
      }
      output << endl;
    }
  }
}

int main(int argc, char** argv){
  if (argc < 3){ // must provide two arguments as input
    throw std::invalid_argument("Usage: ./listwrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
  }

  Graph g;
  g.createGraph("cleaned_movielist.txt");
  g.write_to_output(argv[1], argv[2]);
  return 0;
}
