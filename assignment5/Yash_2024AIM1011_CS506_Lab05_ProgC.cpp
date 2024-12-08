#include<iostream>
#include<vector>
#include<stack>
#include <climits>
#include<algorithm>
#include<string>
#include <iomanip>
#include <queue>

using namespace std;

//Dijkstra's algorithm for a single source
vector<int> dijkstra(vector<vector<int>> &adjMatrix, int src){
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    //min-heap  
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; 

    //distance from source to itself is always 0
    dist[src] = 0;
    //push the source with distance 0  
    pq.push({0, src});

    while (!pq.empty()){
        //get the vertex with the minimum distance
        int u = pq.top().second; 
        pq.pop();

        //traverse all adjacent vertices of u
        for (int v = 0; v < n; v++) {
            //if there is an edge from u to v
            if (adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX){
                //relaxation step
                if (dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    //push the updated distance to the priority queue
                    pq.push({dist[v], v});
                }
            }
        }
    }
    return dist;
}


void john(vector<vector<int>> &adjMatrix, int n){

    // add aditional node to adj matrix
    int new_size = n + 1;
    int placeholder = INT_MAX;
    vector<pair<int, pair<int,int>>> edges;

    //replace no edge with INT MAX
    for (int i=0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (adjMatrix[i][j] == 0){
                adjMatrix[i][j] = placeholder;
            } else {
                edges.push_back({adjMatrix[i][j], {i+1,j+1}});
            }
        }
    }

    //need these matrix
    vector<vector<int>> cpy_adjMatrix = adjMatrix;

    //add edges source to all vertices
    for (int i = 1; i<n+1; i++){
        edges.push_back({0, {0,i}});

    }

    //add a zero to the end of each existing row
    for (auto& row : adjMatrix) {
        row.push_back(placeholder);
    }

    //add a new row of zeros
    adjMatrix.insert(adjMatrix.begin(), vector<int>(new_size, 0));
    adjMatrix[0][0] = placeholder;

    //apply bellman-ford algo on modified graph
    vector<int> d(new_size, placeholder);
    d[0] = 0;

    for (int i = 0; i < n; i++){
        for (auto it : edges) {
            int weight = it.first;
            int u = it.second.first;
            int v = it.second.second;

            if (d[u] != placeholder && d[u] + weight < d[v]){
                d[v] = d[u] + weight;
            }
        }

    }

    //update weights to non-negative weights
    for (auto it = edges.begin(); it != edges.end();) {
        int weight = it->first;
        int u = it->second.first;
        int v = it->second.second;

        if (u == 0){
            it = edges.erase(it);
        }else {
            weight = d[u] + weight - d[v];
            it->first = weight;

            it->second.first -= 1;
            it->second.second -= 1;

            cpy_adjMatrix[it->second.first][it->second.second] = weight;
            it++;

        }

    
    }

    //apply dijkstra algorithm
    vector<vector<int>> res_mat;

    for (int i = 0; i < n; i++){
        res_mat.push_back(dijkstra(cpy_adjMatrix, i));
    }

    // revert back to the original weights 
    d.erase(d.begin());

    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
        
            if (res_mat[i][j] != INT_MAX){
                res_mat[i][j] = res_mat[i][j] + d[j] - d[i];
            }
            
        }

    }

    //print the all pairs shortest path
    for (int i=0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (res_mat[i][j] == INT_MAX){
                cout << "X ";
            } else {
                cout << res_mat[i][j] << " ";
            }
        }
        cout << endl;
    }
}


int main(){

    int number_of_test_cases;
    cin >> number_of_test_cases;

    for (int i = 0; i < number_of_test_cases; i++){

        int number_of_nodes;
        cin >> number_of_nodes;

        vector<vector<int>> adjMatrix(number_of_nodes, vector<int>(number_of_nodes, 0));

            for (int i = 0; i < number_of_nodes; i++){
                for (int j = 0; j < number_of_nodes; j++){
                    cin >> adjMatrix[i][j];
                }
            }

        john(adjMatrix, number_of_nodes);

    }


}