#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
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
                /*
                    If map key already present, insert new node label to the
                    respective set<string>; if not, create a new map entry and
                    then insert the new node label.
                */
                map<string,set<string>>::iterator found = g_map.find(begin_node);
                if (found != g_map.end()) {
                    /* Adding the existing destination node to an existing set */
                    found -> second.insert(end_node);
                } else {
                    /* Creating a new map entry for the new node label */
                    set<string> new_map_entry;
                    new_map_entry.insert(end_node);
                    g_map.insert(make_pair(begin_node, new_map_entry));
                }
                /* If Graph is undirected, repeat insertions for key = end_node */
                if (directed == false) {
                    map<string,set<string>>::iterator found = g_map.find(end_node);
                    if (found != g_map.end()) {
                        found -> second.insert(begin_node);
                    } else {
                        set<string> new_map_entry;
                        new_map_entry.insert(begin_node);
                        g_map.insert(make_pair(end_node, new_map_entry));
                    }
                }
            }
            /* assign constructed Graph class values */
            _graph = g_map;
            _directed = directed;
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
        }
        
};

#endif