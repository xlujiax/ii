#include <iostream>
#include <list>
#include <set>
#include <map>
#include <string>
using namespace std;

struct Node;
struct Edge;

struct Node
{
  map<string, Edge> edges;
};

struct Edge
{
  int distance;
  map<int,int> hours; // czas odjazdu i przyjazdu
  Edge(int dist = 9999999) : distance(dist) {}
};

struct Graph
{
  map<string, Node> nodes;
  void AddNode(string name)
  {
    nodes[name] = Node();
  }
  void RemoveNode(string name)
  {
    nodes.erase(nodes.find(name));
  }
  void AddConnection(string a, string b, int dist)
  {
    nodes[a].edges[b] = Edge(dist);
  }
  void AddConnectionHour(string a, string b, int start, int end)
  {
    nodes[a].edges[b].hours.insert(make_pair(start, end));
  }

  // Dijkstra; nie zwraca uwagi na to czy istnieje godzina o ktorej da sie dojechac z a do b
  list<string> ShortestPath(string a, string b)
  {
    map<int, string> priorityQueue; // kolejka priorytetowa
    map<string, int> distances; // odwrotnosc kolejki priorytetowej; szuka kosztu majac identyfikator
    map<string, string> predecessors; // potrzebne do konstrukcji sciezki
    set<string> visited; // dubluje informacje z predecessors i distances, ale uzyty jest dla czytelnosci

    // wszystkie wezly na poczatku maja distance 9999999
    for(map<string, Node>::iterator i = nodes.begin(); i != nodes.end(); ++i)
      distances[(*i).first] = 99999999;

    priorityQueue.insert(make_pair(0, a));
    while(!priorityQueue.empty())
      {
	string minimumID = (*priorityQueue.begin()).second;

	if(minimumID == b)
	  {
	    break;
	  }
	
	priorityQueue.erase(priorityQueue.begin());
	Node& minimum = nodes[minimumID];

	visited.insert(minimumID);

	for(map<string, Edge>::iterator next = minimum.edges.begin(); next != minimum.edges.end(); ++next)
	  {
	    string nextID = (*next).first;
	    Edge& edge = (*next).second;
	    if(visited.find(nextID) == visited.end())
	      {
		if(distances[nextID] > edge.distance + distances[minimumID])
		  {
		    predecessors[nextID] = minimumID;
		    distances[nextID] = edge.distance + distances[minimumID];

		    priorityQueue.insert(make_pair(distances[nextID], nextID));
		  }
	      }
	  }

	list<string> path;
	string actual = b;
	while(predecessors.find(actual) != predecessors.end())
	  {
	    path.push_back(actual);
	    actual = predecessors[actual];
	  }
	path.reverse();
	return path;
      }
  }
};



int main()
{  
  return 0;
}
