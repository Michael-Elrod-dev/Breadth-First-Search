#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Represents a state with units of water in jugs A and B
typedef pair<int,int> state;

// Possible actions for each state
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// Data structures for search algorithm
map<state, bool> visited;         // Records whether a state has been visited
map<state, state> pred;           // Stores the predecessor state
map<state, int> dist;             // Stores the distance (# of hops) from source node
map<state, vector<state>> nbrs;   // Stores neighboring states for each state

map<pair<state,state>, string> edge_label;

// Breadth-first search algorithm
void search(state source_node)
{
    queue<state> to_visit;
    to_visit.push(source_node);
    visited[source_node] = true;
    dist[source_node] = 0;

    while (!to_visit.empty()) {
        state curnode = to_visit.front();
        to_visit.pop();
        for (state n : nbrs[curnode])
            if (!visited[n]) {
                pred[n] = curnode;
                dist[n] = 1 + dist[curnode];
                visited[n] = true;
                to_visit.push(n);
            }
    }
}

// Prints the path from source state 's' to target state 't'
void print_path(state s, state t)
{
    if (s != t) {
        print_path(s, pred[t]);
        cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
    } else {
        cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
    }
}

// Builds the graph of states and transitions
void build_graph()
{
    state initState = make_pair(0,0);
    int a = 3;
    int b = 4;
    state stopState = make_pair(a,b);

    while(initState != stopState)
    {
        state next;

        // Fill A
        next = make_pair(a, initState.second);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState, next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[0];
        }

        // Fill B
        next = make_pair(initState.first, b);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState, next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[1];
        }

        // Empty A
        next = make_pair(0, initState.second);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState, next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[2];
        }

        // Empty B
        next = make_pair(initState.first, 0);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState, next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[3];
        }

        // Pour A into B
        int a2 = initState.first;
        int b2 = initState.second;
        if(initState.second < b) {
                        while(a2 > 0 && b2 < b) {
                b2++;
                a2--;
            }
            next = make_pair(a2, b2);

            if(next != initState) {
                pair<state,state> edge = make_pair(initState, next);
                nbrs[initState].push_back(next);
                edge_label[edge] = actions[4];
            }
        }

        // Pour B into A
        a2 = initState.first;
        b2 = initState.second;
        if(initState.first < a) {
            while(a2 < a && b2 > 0) {
                a2++;
                b2--;
            }
            next = make_pair(a2, b2);

            if(next != initState) {
                pair<state,state> edge = make_pair(initState, next);
                nbrs[initState].push_back(next);
                edge_label[edge] = actions[5];
            }
        }

        // Move to next state
        if(initState.second == b)
            initState = make_pair(initState.first + 1, 0);
        else
            initState = make_pair(initState.first, initState.second + 1);
    }
}

int main()
{
    build_graph();

    state start = make_pair(0, 0);
    
    for (int i = 0; i < 5; i++)
        nbrs[make_pair(i, 5 - i)].push_back(make_pair(-1, -1));
    search(start);
    if (visited[make_pair(-1, -1)]) 
        print_path(start, pred[make_pair(-1, -1)]);
    else
        cout << "No path!\n";
    
    return 0;
}
