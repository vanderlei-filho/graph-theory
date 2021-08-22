#include "Graph.h"


int main() {
    cout << "Hello world from graph.cpp!" << endl;
    vector<set<string>> x = {{"a","b"}, {"a","e"}, {"b", ""}};

    Graph g = Graph(false, x);

    cout << g << endl;

    return 1;
}