/*
 * Name:Michael Elrod
 * Date Submitted: 11/29/2022
 * Lab Section: 001
 * Assignment Name: Lab 10 - Using Breadth First Search4
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
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

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph()
{
    // Get initial state of the water jugs
    state initState = make_pair(0,0);
    int a = 3;
    int b = 4;
    // Get stopping point
    state stopState = make_pair(a,b);

    while(initState != stopState)
    {
        state next;

        // string actions[0] = "Fill A"
        next = make_pair(a,initState.second);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState,next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[0];
        }

        // string actions[1] = "Fill B"
        next = make_pair(initState.first,b);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState,next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[1];
        }

        // string actions[2] = "Empty A"
        next = make_pair(0,initState.second);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState,next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[2];
        }
        // string actions[3] = "Empty B"
        next = make_pair(initState.first,0);
        if(next != initState) {
            pair<state,state> edge = make_pair(initState,next);
            nbrs[initState].push_back(next);
            edge_label[edge] = actions[3];
        }

        int a2 = initState.first;
        int b2 = initState.second;
        // string actions[4] = "Pour A into B"
        if(initState.second < b) {
            while(a2 > 0 && b2 < b) {
                b2++;
                a2--;
            }
            next = make_pair(a2,b2);

            if(next != initState) {
                pair<state,state> edge = make_pair(initState,next);
                nbrs[initState].push_back(next);
                edge_label[edge] = actions[4];
            }
        }

        // string actions[5] = "Pour B into A"
        a2 = initState.first;
        b2 = initState.second;
        if(initState.first < a) {
            while(a2 < a && b2 > 0) {
                a2++;
                b2--;
            }
            next = make_pair(a2,b2);

            if(next != initState) {
                pair<state,state> edge = make_pair(initState,next);
                nbrs[initState].push_back(next);
                edge_label[edge] = actions[5];
            }
        }

        if(initState.second == b)
            initState = make_pair(initState.first + 1,0);
        else
            initState = make_pair(initState.first, initState.second + 1);
    }
}
/*
int main()
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
 */
