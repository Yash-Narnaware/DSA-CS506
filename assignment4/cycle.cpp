#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int time1 = 0;
int number_of_tree_edges = 0;

void topo_DFS(int i, vector<vector<int>> &adjMatrix, int n, vector<bool> &visited, stack<int> &Stack1, int entry[], int exit[]){

    visited[i] = true;
    time1 = time1 + 1;

    entry[i] = time1;

    for (int j = 0; j < n; j++){
        if (adjMatrix[i][j] == 1 && !visited[j]) {
            number_of_tree_edges += 1;
            topo_DFS(j, adjMatrix, n, visited, Stack1, entry, exit);
        }
    }

    time1 = time1 + 1;

    exit[i] = time1;

    Stack1.push(i);




}


//fix code to correctly calculate tree and forward edges
void edge_classifier(int entry[], int exit[], vector<vector<int>> &adjMatrix, int n){

    
    //int number_of_forward_edges = 0;
    int number_of_back_edges = 0;
    int number_of_cross_edges = 0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){

            if (adjMatrix[i][j] == 1){

                if (entry[i] < entry[j] && exit[i] > exit[j]){

                    continue;

                //     if (entry[j] - entry[i] == 1){ // Immediate child
                //         number_of_tree_edges += 1;
                //     }else {
                //         number_of_forward_edges += 1;
                //     }
                    
                //}else 
                
                }else if (entry[i] > entry[j] && exit[i] < exit[j]){

                    number_of_back_edges += 1;

                }else if (exit[i] < entry[j] || exit[j] < entry[i]){
                   number_of_cross_edges += 1; 
                }

            }
        }
    }

    int number_of_forward_edges = n - (number_of_tree_edges + number_of_back_edges + number_of_cross_edges);

    if (number_of_back_edges > 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    cout << number_of_back_edges << " ";
    cout << number_of_forward_edges << " ";
    cout << number_of_cross_edges << " ";
    cout << number_of_tree_edges << " ";




}

void cycle_detection(vector<vector<int>> &adjMatrix, int n){

    int entry[n];
    int exit[n];
    vector<bool> visited(n, false);
    stack<int> Stack1;
    // int time = 0;


    for (int i = 0; i < n; i++){
        if (!visited[i]){
            topo_DFS(i, adjMatrix, n, visited, Stack1, entry, exit);
        }

    }

    edge_classifier(entry, exit, adjMatrix, n);

    cout << endl;

    for (int i = 0; i < n; i++){
        cout << entry[i] << " ";
    }

    cout << endl;
    for (int i = 0; i < n; i++){
        cout << exit[i] << " ";
    }

    cout << endl;



}



int main(){
    

    // int n = 6; // Number of vertices
    // // Example adjacency matrix for a directed unweighted graph
    // vector<vector<int>> adjMatrix = {
    //     {0, 1, 0, 0, 0, 0}, // Node 0 -> Node 1
    //     {0, 0, 1, 1, 0, 0}, // Node 1 -> Node 2, Node 3
    //     {0, 0, 0, 0, 1, 0}, // Node 2 -> Node 4
    //     {0, 0, 0, 0, 1, 1}, // Node 3 -> Node 4, Node 5
    //     {0, 0, 0, 0, 0, 0}, // Node 4
    //     {0, 0, 0, 0, 0, 0}  // Node 5
    // };



    int n = 4; // Number of vertices
    // Example adjacency matrix for a directed unweighted graph
    vector<vector<int>> adjMatrix = {
        {0, 1, 0, 0}, // Node 0 -> Node 1
        {0, 0, 1, 0}, // Node 1 -> Node 2, Node 3
        {0, 0, 0, 1}, // Node 2 -> Node 4 // Node 4
        {1, 0, 0, 0}  // Node 5
    };


    cycle_detection(adjMatrix, n);




    return 0;



}