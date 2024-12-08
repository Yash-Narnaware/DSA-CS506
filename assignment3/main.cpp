int main() {


    cout << endl;

    //i defined what type of tree we have through this integer: -1 means no tree exists, 0 means current tree is BST and 1 means current tree is AVL tree
    int tree_type = -1;

    int number_of_test_cases;
    //cout << "Enter number of testcases:";
    cin >> number_of_test_cases;
    
    for(int i =0;i<number_of_test_cases;i++){

        BST b1;

        while(true){

            char operation;
            //cout << "Enter the operation:";
            cin >> operation;
            cin.ignore();
       
            if (operation == 'B'){

                tree_type = 0;

                int no_of_BST_op;
                //cout << "Enter the number of operations on BST:";
                cin >> no_of_BST_op;
            
                for(int k=0;k<no_of_BST_op;k++){
                
                    int j;
                    cin >> j;
               
                    if (j>0){
                            
                        b1.insert_in_BST(j);

                    } else if (j<0){
                        j = j*(-1);
                        if (b1.root != nullptr){
                            TreeNode* node = b1.findNode(j);
                            if (node != nullptr && node->val == j){
                                b1.remove(b1.root,j);
                            }
                        }
            
                    }

                }

            } else if (operation == 'A'){

                tree_type = 1;

                int no_of_AVL_op;
                //cout << "Enter the number of operations on AVL:";
                cin >> no_of_AVL_op;
       
                for(int k=0;k<no_of_AVL_op;k++){
                
                    int j;
                    cin >> j;
         
                    if (j>0){
                            
                        b1.insert_in_AVL(b1.root,j);

                    } else if (j<0){
                        j = j*(-1);
                        if (b1.root != nullptr){
                            TreeNode* node = b1.findNode(j);
                            if (node != nullptr && node->val == j){
                                b1.AVL_Delete(b1.root,j);
                            }
                        }
            
                    }   

                }

            } else if (operation == 'I'){

                int ins;
                //cout << "Enter int to insert:";

                cin >> ins;
         
                if (tree_type == -1 || tree_type == 0){
                    tree_type == 0;
                    b1.insert_in_BST(ins); 

                } else {

                    b1.insert_in_AVL(b1.root,ins);

                }
  
            } else if (operation == 'R'){

                int rm;
                //cout << "Enter int to remove:";

                cin >> rm;
         
                if (tree_type == 0){

                    if (b1.root != nullptr){
                        TreeNode* node = b1.findNode(rm);
                        if (node != nullptr && node->val == rm){
                            b1.remove(b1.root,rm);
                        }
                    } 


                } else if (tree_type == 1){

                    if (b1.root != nullptr){
                        TreeNode* node = b1.findNode(rm);
                        if (node != nullptr && node->val == rm){
                            b1.AVL_Delete(b1.root,rm);
                        }
                    }

                }

                
            } else if (operation == 'F'){

                int elem;
                //cout << "Enter element to find:";
                cin >> elem;
          
                if (b1.findNode(elem) == nullptr || b1.findNode(elem)->val != elem){
                    b1.print_no();
                    // cout  << "No";
                    // cout << endl;
                } else if (b1.findNode(elem)->val == elem){
                    b1.print_yes();
                    // cout<< "Yes";
                    // cout << endl;

                }
    
            } else if (operation == 'L'){

                b1.number_of_leaves1(b1.root);

                cout << b1.number_of_leaves;
                cout << endl;

    
            } else if (operation == 'N'){
    
                b1.number_of_nodes = 0;
                b1.number_of_nodes1(b1.root);

                cout << b1.number_of_nodes;
                cout << endl;

                  
            } else if (operation == 'Q'){

                if (b1.root != nullptr){
                    b1.inorder(b1.root);
                    cout << endl;
                }
    
            } else if (operation == 'W'){

                if (b1.root != nullptr){
                    b1.preorder(b1.root);
                    cout << endl;
                }
    
            } else if (operation == 'E'){

                if (b1.root != nullptr){
                    b1.postorder(b1.root);
                    cout << endl;
                }

    
            } else if (operation == 'H'){

                if (b1.root != nullptr){
                    cout << b1.height(b1.root) - 1;
                    cout << endl;
                }

    
            } else if (operation == 'M'){

                b1.print_boundry_clockwise();
                cout << endl;
                
            } else if (operation == 'C'){

                int a1;
                int a2;

                cin >> a1;
                cin >> a2;
                cin.ignore();

                bool e_a1;
                bool e_a2;

                if (b1.findNode(a1) == nullptr || b1.findNode(a1)->val != a1){
                   
                    e_a1 = false;
                } else if (b1.findNode(a1)->val == a1){
                    e_a1 = true;

                }

                if (b1.findNode(a2) == nullptr || b1.findNode(a2)->val != a2){
                  
                    e_a2 = false;
                } else if (b1.findNode(a2)->val == a2){
                    e_a2 = true;

                }

                if (!e_a2 || !e_a1){
                    cout << -1 << endl;
                } else if (a1 == a2){
                    cout << a1 << endl;
                } else {
                    cout << b1.lca(b1.root,a1,a2)->val;
                    cout << endl;
                }

                
            } else if (operation == 'Z'){

                int N;

                //cout << "Enter N:";

                cin >> N;

                int* pre = new int[N];
                int* in = new int[N];

                for(int i=0;i<N;i++){

                    cin >> pre[i];
                    cin.ignore();

                }

                for(int i=0;i<N;i++){

                    cin >> in[i];
                    //cin.ignore();

                }

                b1.print_post_order(in,pre,N);
                cout << endl;
                
            } else if (operation == 'Y'){

                int N1;
                cin >> N1;

                int* pos = new int[N1];
                int* in1 = new int[N1];

                for (int i = 0; i < N1; i++) {
                    cin >> pos[i];
                }

                for (int i = 0; i < N1; i++) {
                    cin >> in1[i];
                }

                b1.preorder(b1.buildTree(in1, pos, N1));

                cout << endl;


            } else if (operation == 'K'){

                b1.eraseTree(b1.root);
                b1.root = nullptr;
                b1.number_of_leaves = 0;
                b1.number_of_nodes = 0;
    
            }else if (operation == 'D'){
                // cout << endl;
                break;
            }

        }

    }


}