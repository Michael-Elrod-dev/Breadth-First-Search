#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <bitset>

using namespace std;

// Represents the state of each item on the left (0) or right (1) side of the river
typedef int state;

// Constants for each item
const int wolf = 0, goat = 1, cabbage = 2, me = 3;

// Checks if the given bit is set in the given integer
bool bit(int x, int i) { return (x >> i) & 1; }

// Data structures for BFS
map<state, bool> visited;                  // Visited states
map<state, state> pred;                    // Predecessor states
map<state, int> dist;                      // Distances from the source node
map<state, vector<state>> nbrs;            // Neighboring states
map<pair<state, state>, string> edge_label;// Edge labels for path reconstruction

// Breadth-first search algorithm
void search(state source_node) {
    queue<state> to_visit;
    to_visit.push(source_node);
    visited[source_node] = true;
    dist[source_node] = 0;

    while (!to_visit.empty()) {
        state curnode = to_visit.front();
        to_visit.pop();
        for (state n : nbrs[curnode]) {
            if (!visited[n]) {
                pred[n] = curnode;
                dist[n] = 1 + dist[curnode];
                visited[n] = true;
                to_visit.push(n);
            }
        }
    }
}

// Returns a string representation of the state
string state_string(state s) {
    string items[4] = {"wolf", "goat", "cabbage", "you"}, result = "";
    for (int i = 0; i < 4; i++)
        if (!bit(s, i)) result += items[i] + " ";
    result += " |river| ";
    for (int i = 0; i < 4; i++)
        if (bit(s, i)) result += items[i] + " ";
    return result;
}

// Prints the path from the source to the target state
void print_path(state s, state t) {
    if (s != t) {
        print_path(s, pred[t]);
        cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
    } else {
        cout << "Initial state: " << state_string(s) << "\n";
    }
}

// Returns the label for the edge between two states
string neighbor_label(int s, int t) {
    string items[3] = {"wolf", "goat", "cabbage"}, which_cross;
    if (bit(s, me) == bit(t, me)) return "";  // Must cross river
    int cross_with = 0;
    for (int i = 0; i < 3; i++) {
        if (bit(s, i) != bit(t, i) && bit(s, i) == bit(s, me)) { cross_with++; which_cross = items[i]; }
        if (bit(s, i) != bit(t, i) && bit(s, i) != bit(s, me)) return "";
    }
    if (cross_with > 1) return "";
    if (cross_with == 0) return "Cross alone";
    else return "Cross with " + which_cross;
}

// Checks if the items are safe in the current configuration
bool itemsAreSafe(bitset<4> item) {
    if (item[wolf] == item[goat]) { // If wolf is with goat
        if (item[me] == item[wolf] && item[me] == item[goat]) // If you are with them both
            return true; // Then items are safe
    }
    else if (item[goat] == item[cabbage]) { // If goat is with cabbage
        if (item[me] == item[goat] && item[me] == item[cabbage]) // If you are with them both
            return true; // Then items are safe
    }
    else
        return true; // Items do not conflict with each other

    return false; // Items do conflict with each other
}

// Builds the graph by adding safe neighboring states
void build_graph() {
    const int items = 4;
    bitset<items> initState;          // Initial state = 0000
    bitset<items> goalState("1111");  // Goal state = 1111

    while (initState != goalState) {
        for (int i = 0; i < items; i++) {
            if (initState[me] == initState[i]) {
                bitset<items> temp = initState;
                temp[me].flip();
                if (i != me)
                    temp[i].flip();
                else
                    temp[i] = false;

                if (itemsAreSafe(temp)) {
                    int current = (int)initState.to_ulong();
                    int next = (int)temp.to_ulong();
                    nbrs[current].push_back(next);
                    edge_label[make_pair(current, next)] = neighbor_label(current, next);
                }
            }
        }
        initState = (int)initState.to_ulong() + 1;
    }
}

int main() {
    build_graph();

    state start = 0, end = 15;

    search(start);
    if (visited[end])
        print_path(start, end);
    else
        cout << "No path!\n";

    return 0;
}
