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
// Array of boolean values stored as bits (1's/0's)
#include <bitset>

using namespace std;

// Reflects what each node represents...
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
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

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}

bool itemsAreSafe(bitset<4> item)
{
    // (==) = is with
    if(item[wolf] == item[goat]) { //  if wolf is with goat
        if(item[me] == item[wolf] && item[me] == item[goat]) // but im with them both
            return true; // then items are safe
    }
    else if(item[goat] == item[cabbage]) { // if goat is with cabbage
        if(item[me] == item[goat] && item[me] == item[cabbage]) // but im with them both
            return true; // then items are safe
    }
    // Items do not conflict with each other
    else
        return true;
    // Items do conflict with each other
    return false;
}

void build_graph()
{
    // Create bitset for size 4 (0, 0, 0, 0)
    const int items = 4;
    bitset<items> initState;            // = 0000
    bitset<items> goalState("1111");// = 1111

    // While initState != 1111
    while(initState != goalState) {
        for(int i = 0; i < items; i++) {
            // initState[3] == initState[i]
            if(initState[me] == initState[i]) {
                bitset<items> temp = initState;

                // bitset.flip() - flips index to opposing bool value (1->0, 0->1)
                temp[me].flip();
                if (i != me)
                    temp[i].flip();
                else
                    temp[i] = false;

                // Check if item positions conflict with each other (ex: wolf alone with goat)
                if(itemsAreSafe(temp)) {
                    // bitset.to_ulong() returns int value of bitset (1111->15)
                    int current = (int)initState.to_ulong(); // cast from unsigned long to int
                    int next = (int)temp.to_ulong(); // cast from unsigned long to int
                    // Items deemed safe are made to pair
                    nbrs[current].push_back(next);
                    edge_label[make_pair(current,next)] = neighbor_label(current,next);
                }
            }
        }
        // Move to next bit state
        initState = (int)initState.to_ulong() + 1;
    }
}
/*
int main(void)
{
  build_graph();

  state start = 0, end = 15;
  
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}
*/