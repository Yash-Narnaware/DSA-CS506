#include<iostream>
#include<vector>
#include<stack>

using namespace std;



void topo_DFS(int i, vector<vector<int>> &adjMatrix, int n, vector<bool> &visited, stack<int> &Stack1){

    visited[i] = true;

    for (int j = 0; j < n; j++){
        if (adjMatrix[i][j] == 1 && !visited[j]) {
            topo_DFS(j, adjMatrix, n, visited, Stack1);
        }
    }

    Stack1.push(i);




}


void topologicalSort(vector<vector<int>> &adjMatrix, int n){

    stack<int> Stack1;

    vector<bool> visited(n,false);


    

    for (int i = 0; i < n; i++){

        
        if (!visited[i]) {
            topo_DFS(i, adjMatrix, n, visited, Stack1);
        }
        
    }


    while (!Stack1.empty()) {
        
        cout << Stack1.top() + 1 << " ";
        Stack1.pop();
    }
    cout << endl;
    






}

int main(){


    // cout << "Hello World";
    

    int n = 6; // Number of vertices
    // Example adjacency matrix for a directed unweighted graph
    vector<vector<int>> adjMatrix = {
        {0, 1, 0, 0, 0, 0}, // Node 0 -> Node 1
        {0, 0, 1, 1, 0, 0}, // Node 1 -> Node 2, Node 3
        {0, 0, 0, 0, 1, 0}, // Node 2 -> Node 4
        {0, 0, 0, 0, 1, 1}, // Node 3 -> Node 4, Node 5
        {0, 0, 0, 0, 0, 0}, // Node 4
        {0, 0, 0, 0, 0, 0}  // Node 5
    };

    topologicalSort(adjMatrix, n);


    return 0;



}