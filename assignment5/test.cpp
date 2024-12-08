#include<iostream>
#include<vector>
#include<stack>
#include <climits>
#include<algorithm>
#include<string>
#include <iomanip>
#include <queue>

using namespace std;

float frac_knapsack(int number_of_items, int capacity, float item_value[], float item_weight[]){

    vector<tuple<float, float, float>> value_by_weight;

    for(int i = 0; i < number_of_items; i++){
        value_by_weight.push_back({item_value[i] / item_weight[i], item_value[i], item_weight[i]});
    }

    //Sort in descending order based on the first element
    sort(value_by_weight.begin(), value_by_weight.end(),
              [](const tuple<float, float, float>& a, const tuple<float, float, float>& b) {
                  return get<0>(a) > get<0>(b); //Descending order based on the first element
              });


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

    vector<tuple<float, float, float>> value_by_weight;

    for(int i = 0; i < number_of_items; i++){
        value_by_weight.push_back({item_value[i] / item_weight[i], item_value[i], item_weight[i]});
    }

    //Sort in descending order based on the first element
    sort(value_by_weight.begin(), value_by_weight.end(),
              [](const tuple<float, float, float>& a, const tuple<float, float, float>& b) {
                  return get<0>(a) > get<0>(b); //Descending order based on the first element
              });


    float value = 0;
    int j = 0;

    while (capacity > 0 && j < number_of_items){

        if (get<2>(value_by_weight[j]) <= capacity){
            value += get<1>(value_by_weight[j]);
            capacity -= get<2>(value_by_weight[j]);

        } else {
            break;
        }
        j += 1;
    }

    return value;

}

float dp_0_1_knapsack(int number_of_items, int capacity, float item_value[], float item_weight[]){
// float dp_0_1_knapsack(int number_of_items, int capacity, float item_value[], float item_weight[]){

    for (int i = 0; i < number_of_items; i++){
        cout << item_weight[i] << endl;

    }
    
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
            } else {
                V[i][j] = V[i - 1][j];  
            }
        }

    }

    return V[number_of_items][capacity];

}






int main(){

    int number_of_test_cases;
    cin >> number_of_test_cases;

    for (int i = 0; i < number_of_test_cases; i++){


        int choice;
        cin >> choice;

        int num_of_items;
        cin >> num_of_items;

        int capacity;
        cin >> capacity;

        float items_val[num_of_items];
        float weights[num_of_items];

        for (int i = 0; i < num_of_items; i++){
            cin >> items_val[i];
        }

        for (int i = 0; i < num_of_items; i++){
            cin >> weights[i];
        }

        if (choice == 1){

            cout << fixed << setprecision(2) << frac_knapsack(num_of_items, capacity, items_val, weights) << endl;
        
        }else if (choice == 2){

            cout << fixed << setprecision(2) << greedy_0_1_knapsack(num_of_items, capacity, items_val, weights) << endl;

        }else {

            cout << fixed << setprecision(2) << dp_0_1_knapsack(num_of_items, capacity, items_val, weights) << endl;
            // cout << dp_0_1_knapsack(num_of_items, capacity, items_val, weights) << endl;

        }


    }

    return 0;

}