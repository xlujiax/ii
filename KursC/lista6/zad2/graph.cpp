// Maciej Pacut
// zadanie 2, lista 6

// ! program w C++ nie w C
// program jest interaktywny, po uruchomieniu mozna tworzyc graf, dodawac polaczenia i wykonywac serie zapytan o najkrotsza sciezke

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

  void Print()
  {
    for(map<string, Node>::iterator i = nodes.begin(); i != nodes.end(); ++i)
      {
	cout << (*i).first << ": ";

	Node& n = (*i).second;
	for(map<string, Edge>::iterator j = n.edges.begin(); j != n.edges.end(); ++j)
	  cout << (*j).first << " (" << (*j).second.distance << "), ";
	cout << endl;
      }
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
    distances[a] = 0;
    
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
      }

    list<string> path;
    string actual = b;
    while(true)
      {
	path.push_back(actual);
	if(predecessors.find(actual) == predecessors.end())
	  break;
	actual = predecessors[actual];
      }
    path.reverse();
    return path;
  }
};



int main()
{
  Graph g;
  
  string command;
  while(true)
    {
      cout << "(s)hortest path, add (n)ode, add (c)onnection, (p)rint graph or (q)uit?" << endl;
      cin >> command;
      if(command == "s")
	{
	  cout << "from? ";
	  string from;
	  cin >> from;

	  cout << "to? ";
	  string to;
	  cin >> to;

	  list<string> path = g.ShortestPath(from, to);
	  for(list<string>::iterator i = path.begin(); i != path.end(); ++i)
	    cout << *i << endl;
	}
      else if(command == "n")
	{
	  cout << "name of node? ";
	  string name;
	  cin >> name;
	  g.AddNode(name);
	}
      else if(command == "c")
	{
	  cout << "from? ";
	  string from;
	  cin >> from;

	  cout << "to? ";
	  string to;
	  cin >> to;
	  
	  cout << "distance? ";
	  int distance;
	  cin >> distance;
	  
	  g.AddConnection(from, to, distance);
	  g.AddConnection(to, from, distance);
	}
      else if(command == "p")
	{
	  g.Print();
	}
      else if(command == "q")
	{
	  break;
	}
    }
  return 0;
}
