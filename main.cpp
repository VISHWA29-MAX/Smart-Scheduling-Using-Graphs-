#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Backtracking function
bool backtrack(int v, int k, vector<vector<int>>& graph,
               vector<int>& assigned) {

    if (v == graph.size())
        return true;

    for (int color = 1; color <= k; color++) {

        bool available = true;

        for (int neighbor : graph[v]) {
            if (assigned[neighbor] == color) {
                available = false;
                break;
            }
        }

        if (available) {
            assigned[v] = color;

            if (backtrack(v + 1, k, graph, assigned))
                return true;

            assigned[v] = 0;
        }
    }

    return false;
}

// Validate graph coloring
bool isValid(vector<vector<int>>& graph, vector<int>& assigned) {

    for (int v = 0; v < graph.size(); v++) {

        for (int neighbor : graph[v]) {

            if (assigned[v] == assigned[neighbor])
                return false;
        }
    }

    return true;
}

int main() {

    int n;

    cout << "GRAPH COLORING PLANNER\n";

    cout << "Enter number of classes (1-30): ";
    cin >> n;

    if (n < 1 || n > 30) {
        cout << "Invalid number of classes.";
        return 0;
    }

    vector<string> names(n);

    cout << "Enter class names:\n";

    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    vector<vector<int>> graph(n);

    int edges;

    cout << "Enter number of conflicts: ";
    cin >> edges;

    if (edges < 0 || edges > n * (n - 1) / 2) {
        cout << "Invalid number of conflicts.";
        return 0;
    }

    cout << "Enter conflicting class pairs:\n";

    for (int i = 0; i < edges; i++) {

        int a, b;

        cin >> a >> b;

        if (a < 1 || a > n || b < 1 || b > n || a == b) {
            cout << "Invalid conflict pair.";
            return 0;
        }

        a--;
        b--;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int k;

    cout << "Enter number of available time slots: ";
    cin >> k;

    if (k < 1 || k > 30) {
        cout << "Invalid number of time slots.";
        return 0;
    }

    int method;

    cout << "Choose method:\n";
    cout << "1. Greedy\n";
    cout << "2. Backtracking\n";

    cin >> method;

    if (method != 1 && method != 2) {
        cout << "Invalid method.";
        return 0;
    }

    vector<int> assigned(n, 0);

    bool possible = true;

    // GREEDY COLORING
    if (method == 1) {

        for (int v = 0; v < n; v++) {

            for (int color = 1; color <= k; color++) {

                bool available = true;

                for (int neighbor : graph[v]) {

                    if (assigned[neighbor] == color) {
                        available = false;
                        break;
                    }
                }

                if (available) {
                    assigned[v] = color;
                    break;
                }
            }

            if (assigned[v] == 0) {
                possible = false;
                break;
            }
        }
    }

    // BACKTRACKING COLORING
    else {

        possible = backtrack(0, k, graph, assigned);
    }

    // Output
    if (possible && isValid(graph, assigned)) {

        cout << "\nValid Schedule Found!\n";

        for (int i = 0; i < n; i++) {

            cout << names[i] << " -> Time Slot "
                 << assigned[i] << endl;
        }

        vector<bool> used(k + 1, false);

        int count = 0;

        for (int color : assigned) {

            if (!used[color]) {
                used[color] = true;
                count++;
            }
        }

        cout << "\nColors Used: " << count << endl;

        cout << "Validation: Successful\n";
    }

    else {

        if (method == 1) {
            cout << "\nGreedy could not find a valid schedule.\n";
            cout << "Try Backtracking for an exact solution.\n";
        }

        else {
            cout << "\nNo valid schedule exists with "
                 << k << " time slots.\n";
        }
    }

    return 0;
}