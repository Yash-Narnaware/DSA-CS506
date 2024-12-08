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

    //Backtrack to find the LCS
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

    //Reverse the LCS as we constructed it backwards
    reverse(lcs.begin(), lcs.end());

    return lcs;



}


int main(){

    int number_of_test_cases;
    cin >> number_of_test_cases;

    for (int i = 0; i < number_of_test_cases; i++){

        string a;
        string b;
        string c;

        cin >> a;
        cin >> b;
        cin >> c;

        cout << LCS(a,b,c) << endl;

    }

    return 0;
}