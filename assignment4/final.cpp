#include<iostream>
#include<vector>
#include<stack>
#include <climits>
#include<algorithm>

using namespace std;


// Disjoint Set class (Union-Find)
class DisjointSet {
    vector<int> parent, rank;

public:
    // Constructor to initialize n sets
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;  // Initially, each vertex is its own parent
        }
    }

    // Find the representative of a set (with path compression)
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);  // Path compression
        }
        return parent[u];
    }

    // Union two sets by rank
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};


int time1 = 0;
int number_of_tree_edges = 0;


void topo_DFS(int i, vector<vector<int>> &adjMatrix, int n, vector<bool> &visited, stack<int> &Stack1){

    visited[i] = true;

    for (int j = 0; j < n; j++){
        if (adjMatrix[i][j] == 1 && !visited[j]) {
            topo_DFS(j, adjMatrix, n, visited, Stack1);
        }
    }

    Stack1.push(i);

}


void cycle_DFS(int i, vector<vector<int>> &adjMatrix, int n, vector<bool> &visited, stack<int> &Stack1, int entry[], int exit[]){

    visited[i] = true;
    time1 = time1 + 1;
    entry[i] = time1;

    for (int j = 0; j < n; j++){
        if (adjMatrix[i][j] == 1 && !visited[j]) {
            number_of_tree_edges += 1;
            cycle_DFS(j, adjMatrix, n, visited, Stack1, entry, exit);
        }
    }

    time1 = time1 + 1;
    exit[i] = time1;
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
        cout << Stack1.top() << " ";
        Stack1.pop();
    }
    cout << endl;
}


int cyclic_edges(vector<vector<int>> &adjMatrix, int n){

    int temp = 0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (adjMatrix[i][j] > 0){
                temp += 1;
            }
        }
    }

    return temp;
}


vector<int> edge_classifier(int entry[], int exit[], vector<vector<int>> &adjMatrix, int n){

    
    //vector to store different edge numbers idx 1 - back, 2 - forward, 3 - cross, 4 - tree
    vector<int> number_of_edges(4,0);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){

            if (adjMatrix[i][j] != 0){

                if (entry[i] < entry[j] && exit[i] > exit[j]){

                    continue;
                
                }else if (entry[i] > entry[j] && exit[i] < exit[j]){

                    number_of_edges[0] += 1;

                }else if (exit[i] < entry[j] || exit[j] < entry[i]){
                   number_of_edges[2] += 1; 
                }

            }
        }
    }

    number_of_edges[3] = number_of_tree_edges;

    if (number_of_edges[0] > 0){
        int no_of_edges_in_cyclic_graph;

        no_of_edges_in_cyclic_graph = cyclic_edges(adjMatrix, n);

        number_of_edges[1] = no_of_edges_in_cyclic_graph - (number_of_edges[3] + number_of_edges[0] + number_of_edges[2]);
    } else {

        number_of_edges[1] = n - 1 - (number_of_edges[3] + number_of_edges[0] + number_of_edges[2]);

    }

    return number_of_edges;

}


void cycle_detection(vector<vector<int>> &adjMatrix, int n){

    int entry[n];
    int exit[n];
    vector<bool> visited(n, false);
    stack<int> Stack1;
    vector<int> edges;

    for (int i = 0; i < n; i++){
        if (!visited[i]){
            cycle_DFS(i, adjMatrix, n, visited, Stack1, entry, exit);
        }
    }

    edges = edge_classifier(entry, exit, adjMatrix, n);

    //cycle detection - non zero number of back edges
    if (edges[0] > 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    //print number of edges
    for (int i = 0; i < 4; i++){
        cout << edges[i] << " ";
    }

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


void prim(vector<vector<int>> &adjMatrix, int n){


    vector<vector<int>> MST(n, vector<int>(n, 0));
    vector<bool> inMST(n,false);

    //start with minimum edge weight
    int min = INT_MAX;
    int s;
    int e;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (adjMatrix[i][j] > 0 && adjMatrix[i][j] < min){
                min = adjMatrix[i][j];
                s = i;
                e = j;
            }
        }
    }

    inMST[s] = true;
    inMST[e] = true;

    int nodes_in_MST = 2;

    MST[s][e] = min;
    MST[e][s] = min;

    while (nodes_in_MST != n){

        int min2 = INT_MAX;
        int s1;
        int e1;
        for (int i = 0; i < n; i++){
            if (inMST[i] == true){

                for (int j = 0; j < n; j++){
                    if (inMST[j] == false && adjMatrix[i][j] > 0 && adjMatrix[i][j] < min2){
                        min2 = adjMatrix[i][j];
                        s1 = i;
                        e1 = j;

                    }
                }

            }
        }

        inMST[e1] = true;
        MST[s1][e1] = min2;
        MST[e1][s1] = min2;
        nodes_in_MST += 1;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << MST[i][j] << " ";
        }
        cout << endl;
    }


}

// //fix this algo - cycle detection - union find - disjoint sets
// void krushkal(vector<vector<int>> &adjMatrix, int n){


//     vector<vector<int>> MST(n, vector<int>(n, 0));

//     //vector<bool> inMST(n,false);

//     vector<vector<int>> inMST(n, vector<int>(n, 0));

//     //start with minimum edge weight

//     int min = INT_MAX;
//     int s;
//     int e;

//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < n; j++){
//             if (adjMatrix[i][j] > 0 && adjMatrix[i][j] < min){
//                 min = adjMatrix[i][j];
//                 s = i;
//                 e = j;
//             }
//         }
//     }

//     cout << "s min:" << min << " " << s << " " << e << endl;

//     inMST[s][e] = 1;
//     inMST[e][s] = 1;

//     int nodes_in_MST = 2;

//     MST[s][e] = min;
//     MST[e][s] = min;


//     while (nodes_in_MST != n){
//         //cout << "hello";
//         int min2 = INT_MAX;
//         int s1;
//         int e1;
//         for (int i = 0; i < n; i++){
            

//             for (int j = 0; j < n; j++){
//                 if ((inMST[i][j] == 0) && adjMatrix[i][j] > 0 && adjMatrix[i][j] < min2){
//                     min2 = adjMatrix[i][j];
//                     s1 = i;
//                     e1 = j;

//                 }
//             }

            
//         }

//         //cout << "min2:" << min2 << endl;

//         inMST[s1][e1] = 1;
//         inMST[e1][s1] = 1;

//         MST[s1][e1] = min2;
//         MST[e1][s1] = min2;


//         nodes_in_MST += 1;
//     }

//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < n; j++){
//             cout << MST[i][j] << " ";
//         }
//         cout << endl;
//     }

// }

void krushkal2(vector<vector<int>> &adjMatrix, int n){

    vector<vector<int>> MST(n, vector<int>(n, 0));
    vector<pair<int, pair<int,int>>> edges;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (adjMatrix[i][j] > 0){
                edges.push_back({adjMatrix[i][j], {i,j}});
            }
        }
    }

    DisjointSet ds(n);
    sort(edges.begin(), edges.end());

    for (auto it : edges) {
        int weight = it.first;
        int u = it.second.first;
        int v = it.second.second;

        if (ds.find(u) != ds.find(v)) {
            MST[u][v] = weight;
            MST[v][u] = weight;
            ds.unionSets(u,v);
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << MST[i][j] << " ";
        }
        cout << endl;
    }

}


int main(){

    int operation;
    cin >> operation;

    if (operation == 1){

        //topo
        int no_of_test_cases;
        cin >> no_of_test_cases;

        for (int i = 0; i < no_of_test_cases; i++){

            int n;
            cin >> n;

            vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    cin >> adjMatrix[i][j];
                }
            }

            topologicalSort(adjMatrix, n);
        }
    } else if (operation == 2){

        //dfs
        int no_of_test_cases;
        cin >> no_of_test_cases;

        for (int i = 0; i < no_of_test_cases; i++){

            int n;
            cin >> n;

            vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
            number_of_tree_edges = 0;

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    cin >> adjMatrix[i][j];
                }
            }

            time1 = 0;
            cycle_detection(adjMatrix, n);

        }

    } else if (operation == 3){

        //prim
        int no_of_test_cases;
        cin >> no_of_test_cases;

        for (int i = 0; i < no_of_test_cases; i++){

            int n;
            cin >> n;

            vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
            number_of_tree_edges = 0;

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    cin >> adjMatrix[i][j];
                }
            }

            prim(adjMatrix, n);

        }
    } else if (operation == 4){

        //krushkal
        int no_of_test_cases;
        cin >> no_of_test_cases;

        for (int i = 0; i < no_of_test_cases; i++){

            int n;
            cin >> n;

            vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
            number_of_tree_edges = 0;

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    cin >> adjMatrix[i][j];
                }
            }

            krushkal2(adjMatrix, n);

        }

    }

    return 0;
}