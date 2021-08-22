#include<iostream>
#include<ostream>
#include<vector>
#include<set>
#include<map>
using namespace std;


class Graph {
    public:
        map<string,set<string>> _graph;
        bool _directed = false;  // Graph is undirected by default

        Graph(bool directed, vector<set<string>> edges) {
            /* Initialize a map collection for the Graph representation */
            map<string,set<string>> g_map;
            /* Iterate the input vector with edge information and populate g_map */
            vector<set<string>>::iterator v_itr;
            for (v_itr=edges.begin(); v_itr!=edges.end(); ++v_itr) {
                /* 
                    For each edge = (string, string) representation, check
                    if it is already in the g_map Graph representation.
                */ 
                string begin_node = *(*v_itr).begin();
                string end_node = *++(*v_itr).begin();
                cout << "----------- PROCESSING NODE: -----------" << endl;
                cout << "(" << begin_node << "," << end_node << ")" << endl;
                /*
                    If map key already present, insert new node label to the
                    respective set<string>; if not, create a new map entry and
                    then insert the new node label.
                */
                map<string,set<string>>::iterator found = g_map.find(begin_node);
                if (found != g_map.end()) {
                    /* Adding the existing destination node to an existing set */
                    found -> second.insert(end_node);
                    cout << "Adding {" << end_node << "} to existing g_map key" << endl;
                } else {
                    /* Creating a new map entry for the new node label */
                    set<string> new_map_entry;
                    new_map_entry.insert(end_node);
                    g_map.insert(make_pair(begin_node, new_map_entry));
                    cout << "Adding {" << end_node << "} to new g_map key" << endl;
                }
                /* If Graph is undirected, repeat insertions for key = end_node */
                if (directed == false) {
                    map<string,set<string>>::iterator found = g_map.find(end_node);
                    if (found != g_map.end()) {
                        found -> second.insert(begin_node);
                        cout << "Adding {" << begin_node << "} to existing g_map key (only for undirected graphs)" << endl;
                    } else {
                        set<string> new_map_entry;
                        new_map_entry.insert(begin_node);
                        g_map.insert(make_pair(end_node, new_map_entry));
                        cout << "Adding {" << begin_node << "} to new g_map key (only for undirected graphs)" << endl;
                    }
                }
            }
            // assign constructed Graph class values
            _directed = directed;
            _graph = g_map;
        }

        friend ostream& operator<< (ostream& os, const Graph &obj) {
            for (const auto &map_entry : obj._graph) {
                /* Print departure node */
                os << "Node " << map_entry.first << " -> {";
                /* Print destination nodes */
                set<string>::iterator itr;
                for (itr=map_entry.second.begin(); itr!=map_entry.second.end(); ++itr) {
                    os << (*itr) << ",";
                };
                os << "}" << endl;
            }
            return os;

            /*std::ostream & operator <<(std::ostream &os, const std::map<std::string, std::vector<int>> &m)
            {
                for (const auto &p : m)
                {
                    os << p.first << ": ";
                    for (int x : p.second) os << x << ' ';
                    os << std::endl;
                }

                return os;
            }*/
        }

};


int main() {
    cout << "Hello world from graph.cpp!" << endl;
    set<string> e1; e1.insert("A"); e1.insert("B");
    set<string> e2; e2.insert("A"); e2.insert("C");
    set<string> e3; e3.insert("B"); e3.insert("D");
    set<string> e4; e4.insert("D"); e4.insert("E");
    set<string> e5; e5.insert("B"); e5.insert("C");
    vector<set<string>> x = {e1,e2,e3,e4,e5};

    Graph g = Graph(true, x);

    cout << g << endl;

    return 1;
}