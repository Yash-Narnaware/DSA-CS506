
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

//time1 for entry and exit time of a node while traversing
int time1 = 0;
int number_of_tree_edges = 0;


void topo_DFS(int i, vector<vector<int>> &adjMatrix, int n, vector<bool> &visited, stack<int> &Stack1){
