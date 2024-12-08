#include<iostream>
#include<vector>
#include<stack>
#include <climits>
#include<algorithm>
#include<string>
#include <iomanip>
#include <queue>

using namespace std;


string LCS(string p, string q, string r){

    int L[p.size() + 1][q.size() + 1][r.size() + 1];



    for (int i = 0; i <= p.size(); i++){
        for (int j = 0; j <= q.size(); j++){
            for (int k = 0; k <= r.size(); k++){
                L[i][j][k] = 0;
            }

        }

    }


    for (int i = 1; i <= p.size(); i++){
        for (int j = 1; j <= q.size(); j++){
            for (int k = 1; k <= r.size(); k++){
                if (p[i-1] == q[j-1] && q[j-1] == r[k-1]){
                    L[i][j][k] = 1 + L[i-1][j-1][k-1];
                } else {

                    L[i][j][k] = max(max(L[i-1][j][k], L[i][j-1][k]), L[i][j][k-1]);

                }

            }
        }

    }

    if (L[p.size()][q.size()][r.size()] == 0){
        return "<None>";
    }

    // Backtrack to find the LCS
    string lcs;
    int i = p.size(), j = q.size(), k = r.size();

    while (i > 0 && j > 0 && k > 0) {
        if (p[i - 1] == q[j - 1] && q[j - 1] == r[k - 1]) {
            lcs += p[i - 1]; // or q[j - 1] or r[k - 1] as they are equal
            i--;
            j--;
            k--;
        } else {
            //Move in the direction of the maximum value
            if (L[i - 1][j][k] >= L[i][j - 1][k] && L[i - 1][j][k] >= L[i][j][k - 1]) {
                i--; 
            } else if (L[i][j - 1][k] >= L[i - 1][j][k] && L[i][j - 1][k] >= L[i][j][k - 1]) {
                j--;
            } else {
                k--;
            }
        }
    }
    // cout << p.size() << endl;
    // cout << q.size() << endl;
    // cout << r.size() << endl;

    // return L[p.size()][q.size()][r.size()];

    //Reverse the LCS as we constructed it backwards
    reverse(lcs.begin(), lcs.end());

    return lcs;



}

float frac_knapsack(int number_of_items, int capacity, float item_value[], float item_weight[]){


    // float value_by_weight[number_of_items];

    vector<tuple<float, float, float>> value_by_weight;

    for(int i = 0; i < number_of_items; i++){
        // value_by_weight[i] = item_value[i] / item_weight[i];
        value_by_weight.push_back({item_value[i] / item_weight[i], item_value[i], item_weight[i]});
    }

    // sort(value_by_weight, value_by_weight + number_of_items, greater<int>());
    // sort(value_by_weight.begin(),value_by_weight.end(), greater<float>())

    // for(int i = 0; i < number_of_items; i++){
    //     cout << get<0>(value_by_weight[i]) << " ";
    // }


    // Sort in descending order based on the first element
    sort(value_by_weight.begin(), value_by_weight.end(),
              [](const tuple<float, float, float>& a, const tuple<float, float, float>& b) {
                  return get<0>(a) > get<0>(b); // Descending order based on the first element
              });

    // for(int i = 0; i < number_of_items; i++){
    //     cout << get<0>(value_by_weight[i]) << " ";
    // }

    float value = 0;

    int j = 0;

    while (capacity > 0 && j < number_of_items){

        if (get<2>(value_by_weight[j]) <= capacity){
            value += get<1>(value_by_weight[j]);
            capacity -= get<2>(value_by_weight[j]);

        } else {
            value += (capacity / get<2>(value_by_weight[j]))*get<1>(value_by_weight[j]);
            capacity = 0;
        }

        j += 1;

    }

    return value;







}

float greedy_0_1_knapsack(int number_of_items, int capacity, float item_value[], float item_weight[]){

    // float value_by_weight[number_of_items];

    vector<tuple<float, float, float>> value_by_weight;

    for(int i = 0; i < number_of_items; i++){
        // value_by_weight[i] = item_value[i] / item_weight[i];
        value_by_weight.push_back({item_value[i] / item_weight[i], item_value[i], item_weight[i]});
    }

    // sort(value_by_weight, value_by_weight + number_of_items, greater<int>());
    // sort(value_by_weight.begin(),value_by_weight.end(), greater<float>())

    // for(int i = 0; i < number_of_items; i++){
    //     cout << get<0>(value_by_weight[i]) << " ";
    // }


    // Sort in descending order based on the first element
    sort(value_by_weight.begin(), value_by_weight.end(),
              [](const tuple<float, float, float>& a, const tuple<float, float, float>& b) {
                  return get<0>(a) > get<0>(b); // Descending order based on the first element
              });

    // for(int i = 0; i < number_of_items; i++){
    //     cout << get<0>(value_by_weight[i]) << " ";
    // }

    float value = 0;

    int j = 0;

    while (capacity > 0 && j < number_of_items){

        if (get<2>(value_by_weight[j]) <= capacity){
            value += get<1>(value_by_weight[j]);
            capacity -= get<2>(value_by_weight[j]);

        } else {
            // value += (capacity / get<2>(value_by_weight[j]))*get<1>(value_by_weight[j]);
            // capacity = 0;
            break;
        }

        j += 1;

    }

    return value;


}


float dp_0_1_knapsack(int number_of_items, int capacity, float item_value[], float item_weight[]){


    float V[number_of_items + 1][capacity + 1];



    for (int i = 0; i <= number_of_items; i++){
        for (int j = 0; j <= capacity; j++){
            V[i][j] = 0;
            
        }

    }

    
    for (int i = 1; i <= number_of_items; i++){
        for (int j = 1; j <= capacity; j++){

            if (item_weight[i - 1] <= j) {

                V[i][j] = max(V[i-1][j], V[i-1][j-int(item_weight[i-1])] + item_value[i-1]);
            }

        }

    }

    return V[number_of_items][capacity];


}



// Dijkstra's algorithm for a single source
vector<int> dijkstra(vector<vector<int>> &adjMatrix, int src) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);    // Distance values initialized to INT_MAX
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // Min-heap

    dist[src] = 0;  // Distance from source to itself is always 0
    pq.push({0, src}); // Push the source with distance 0

    while (!pq.empty()) {
        int u = pq.top().second; // Get the vertex with the minimum distance
        pq.pop();

        // Traverse all adjacent vertices of u
        for (int v = 0; v < n; v++) {
            // If there is an edge from u to v
            if (adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX) {
                // Relaxation step
                if (dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    pq.push({dist[v], v}); // Push the updated distance to the priority queue
                }
            }
        }
    }
    return dist;
}






void john(vector<vector<int>> &adjMatrix, int n){

    // add aditional node to adj matrix

    int new_size = n + 1;
    int placeholder = INT_MAX; // Define no edge as INT_MAX
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

    // cout << "New size:" << new_size << endl;

    //Add a zero to the end of each existing row
    for (auto& row : adjMatrix) {
        row.push_back(placeholder);
    }

    //Add a new row of zeros
    adjMatrix.insert(adjMatrix.begin(), vector<int>(new_size, 0));

    adjMatrix[0][0] = placeholder;

    

    // Display the updated matrix
    for (const auto& row : adjMatrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }


    // apply bellman-ford algo on modified graph

    vector<int> d(new_size, placeholder);
    d[0] = 0;

    // for (int i = 0; i < n+1; i++){
    //     cout << d[i] << " ";
    // }

    for (int i = 0; i < n; i++){
        for (auto it : edges) {
            int weight = it.first;
            int u = it.second.first;
            int v = it.second.second;

            cout << "edge: (" << u << " ," << v << ") weight: " << weight << endl;
            if (d[u] != placeholder && d[u] + weight < d[v]){
                d[v] = d[u] + weight;
            }
            //cout << vec[i] << " ";
        }

        cout << endl;
    }



    // Display the updated matrix
    // for (const auto& row : adjMatrix) {
    //     for (int value : row) {
    //         cout << value << " ";
    //     }
    //     cout << endl;
    // }


    // update the weights to a non negative weights

    // d.erase(d.end());


    cout << endl << "d[]:";
    for (int i = 0; i < n+1; i++){
        cout << d[i] << " ";
    }

    for (auto it = edges.begin(); it != edges.end();) {
        int weight = it->first;
        int u = it->second.first;
        int v = it->second.second;

        if (u == 0){
            it = edges.erase(it);
        }else {
            cout << "updating edge: (" << u << ", " << v << ")" << endl;
            weight = d[u] + weight - d[v];
            cout << "new weight: " << weight << endl;
            it->first = weight;

            it->second.first -= 1;
            it->second.second -= 1;

            cpy_adjMatrix[it->second.first][it->second.second] = weight;
            it++;

        }

    
    }



    // cout << "I am here";
    for (auto it : edges) {
        int weight = it.first;
        int u = it.second.first;
        int v = it.second.second;

        cout << "(" << u << ", " << v << ") weight: " << weight << endl;
    }


    //Display the updated matrix
    // for (const auto& row : cpy_adjMatrix) {
    //     for (int value : row) {
    //         cout << value << " ";
    //     }
    //     cout << endl;
    // }



    // apply dijkstra algorithm


    vector<vector<int>> res_mat;

    for (int i = 0; i < n; i++){
        res_mat.push_back(dijkstra(cpy_adjMatrix, i));
    }

    for (const auto& row : res_mat) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
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


    // print the all pairs shortest path

    cout << endl;
    // for (const auto& row : res_mat) {
    //     for (int value : row) {
    //         cout << value << " ";
    //     }
    //     cout << endl;
    // }

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


    // cout << LCS("s","ti","k");

    // float items[] = {120,100,60};
    // float weights[] = {30,20,10}; 
    // cout << fixed << setprecision(2) << frac_knapsack(3, 50, items, weights);


    // float items[] = {120,100,60};
    // float weights[] = {30,20,10}; 
    // cout << fixed << setprecision(2) << greedy_0_1_knapsack(3, 50, items, weights);


    // float items[] = {120,100,60};
    // float weights[] = {30,20,10}; 
    // cout << fixed << setprecision(2) << dp_0_1_knapsack(3, 50, items, weights);



    // Example 2D vector (adjacency matrix)
    // vector<std::vector<int>> adj_matrix = {
    //     {0, 4, 0, 0, 1},
    //     {0, 0, 0, 0, 0},
    //     {0, 7, 0, -2, 0},
    //     {0, 1, 0, 0, 0},
    //     {0, 0, 0, -5, 0}
    // };

    // vector<std::vector<int>> adj_matrix = {
    //     {0, -3, 0, 2},
    //     {5, 0, 3, 0},
    //     {1, 0, 0, 0},
    //     {-1, 0, 4, 0}
    // };

    // vector<std::vector<int>> adj_matrix = {
    //     {0, -5, 2, 3},
    //     {0, 0, 4, 0},
    //     {0, 0, 0, 1},
    //     {0, 0, 0, 0}
    // };

    // john(adj_matrix, 4);






    return 0;
}