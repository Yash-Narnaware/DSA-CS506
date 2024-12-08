
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class TreeNode {

public:

    TreeNode* left;
    TreeNode* right;
    int val;
    int height;

    TreeNode(int val2){
        val = val2;
        left = nullptr;
        right = nullptr;
    }

};

class BST {

public:

    TreeNode* root;
    int number_of_leaves;
    int number_of_nodes;

    BST(){
        root = nullptr;
        number_of_leaves = 0;
        number_of_nodes = 0;
    }

    void insert_in_BST(int a){

        if (a <= 0) {
            return;
        }
        
        TreeNode* newNode = new TreeNode(a);

        
        if (root == nullptr){
            root = newNode;
            return;
        }

        TreeNode* parent = findNode(a);

        if (a == parent->val){
            return;
        } else if (a < parent->val){
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }



        
    }

    void update_heights(TreeNode* node){

        if (node == nullptr){
            return;
        }

        node->height = height(node) - 1;
        update_heights(node->left);
        update_heights(node->right);

    }


    int balance_factor(TreeNode* p){
        
        int hl;
        int hr;

        hl = height(p->left);
        hr = height(p->right);

        return hl-hr;
    }

    TreeNode* LL_rotation(TreeNode* p){

        TreeNode* pl = p->left;
        TreeNode* plr = pl->right;

        pl->right = p;
        p->left = plr;

        p->height = height(p);
        pl->height = height(pl);

        if (p == root){
            root = pl;
        }

        return pl;


    }

    TreeNode* LR_rotation(TreeNode* p){

        TreeNode* pl = p->left;
        TreeNode* plr = pl->right;

        pl->right = plr->left;
        p->left = plr->right;

        plr->left = pl;
        plr->right = p;

        
        pl->height = height(pl);
        p->height = height(p);
        plr->height = height(plr);


        if (p == root){
            root = plr;
        }

        return plr;


    }

    TreeNode* RR_rotation(TreeNode* p){

        TreeNode* pr = p->right;
        TreeNode* prl = pr->left;

        pr->left = p;
        p->right = prl;

        p->height = height(p);
        pr->height = height(pr);

        if (p == root){
            root = pr;
        }

        return pr;


    }

    TreeNode* RL_rotation(TreeNode* p){

        TreeNode* pr = p->right;
        TreeNode* prl = pr->left;

        pr->left = prl->right;
        p->right = prl->left;

        prl->right = pr;
        prl->left = p;

        
        pr->height = height(pr);
        p->height = height(p);
        prl->height = height(prl);


        if (p == root){
            root = prl;
        }

        return prl;


    }

    TreeNode* insert_in_AVL(TreeNode* p,int a){


        TreeNode* t = nullptr;

        if (p == nullptr){

            t = new TreeNode(a);
            t->height = 1;

            if (root == nullptr){
                root = t;
            }

            return t;
        }

        if (a < p->val){
            p->left = insert_in_AVL(p->left,a);
        } else if (a > p->val){
            p->right = insert_in_AVL(p->right,a); 
        }

        p->height = height(p);


        if (balance_factor(p) == 2 && balance_factor(p->left) == 1){
            return LL_rotation(p);
        } else if (balance_factor(p) == 2 && balance_factor(p->left) == -1){
            return LR_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == -1){
            return RR_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == 1){
            return RL_rotation(p);
        }

        return p;



    }




    TreeNode* findNode(int b){
        if (root == nullptr){
            return nullptr;
        }

        TreeNode* cur_node = root;
        TreeNode* prev = nullptr;

        
        while (cur_node != nullptr){

            prev = cur_node;
            if (cur_node->val == b){
                return cur_node;
            } else if (cur_node->val < b){    
                cur_node = cur_node->right;
            } else {
                cur_node = cur_node->left;
            }
        }

        return prev;
        
    }



    void number_of_leaves1(TreeNode* node){

        if (node == nullptr){
            return;
        }

        if (node->left == nullptr && node->right == nullptr){

            number_of_leaves += 1;
            return;

        }
        number_of_leaves1(node->left);
        number_of_leaves1(node->right);
    }

    void number_of_nodes1(TreeNode* node){

        if (node == nullptr){
            return;
        } else {
            number_of_nodes += 1;
        }

        number_of_nodes1(node->left);
        number_of_nodes1(node->right);
    }


    void inorder(TreeNode* node){

        if (node == nullptr){
            return;
        }
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    void preorder(TreeNode* node){

        if (node == nullptr){
            return;
        }
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(TreeNode* node){

        if (node == nullptr){
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
    }


    int height(TreeNode* node) {

        if (node == nullptr){
            return 0;
        }

        int left1 = height(node->left);
        int right1 = height(node->right);

        int max;

        if (left1 >= right1){
            max = left1;
        } else {
            max = right1;
        }

        return 1 + max;
    }

    TreeNode* lca(TreeNode* node,int a, int b){

        if (node == nullptr){
            return nullptr;
        }

        if (node->val > a && node->val > b) {
            return lca(node->left,a,b);
        }

        if (node->val < a && node->val < b) {
            return lca(node->right,a,b);
        }

        return node;

    }

    void print_boundry_clockwise(){

        if (root == nullptr){
            return;
        }

        cout << root->val << " ";

        print_boundry_right(root->right);
        print_boundry_leaves(root);
        print_boundry_left(root->left);
    }

    void print_boundry_right(TreeNode* node){

        if (node == nullptr){
            return;
        }

        if (node->right != nullptr){
            cout << node->val << " ";
            print_boundry_right(node->right);

        } else if (node->left != nullptr) {
            cout << node->val << " ";
            print_boundry_right(node->left);

        }

    }

    void print_boundry_left(TreeNode* node){

        if (node == nullptr){
            return;
        }

        if (node->left != nullptr){

            print_boundry_left(node->left);
            cout << node->val << " ";
            

        } else if (node->right != nullptr){
            
            print_boundry_left(node->right);
            cout << node->val << " ";

        }

    }

    void print_boundry_leaves(TreeNode* node){

        if (node == nullptr){
            return;
        }

        

        print_boundry_leaves(node->right);
        if (node->left == nullptr && node->right == nullptr && node != root){
            cout << node->val << " ";
        }
        print_boundry_leaves(node->left);


    }


    int search(int arr[],int a,int n){

        for(int i=0;i<n;i++){
            if (arr[i] == a){
                return i;
            }
        }
        return -1;
    }

    void print_post_order(int inorder[],int preorder[],int n){

        int root1 = search(inorder,preorder[0],n);

        if (root1 != 0){
            print_post_order(inorder,preorder + 1,root1);
        }

        if (root1 != n-1){
            print_post_order(inorder+root1+1,preorder+root1+1,n-root1-1);
        }

        cout << preorder[0] << " ";
    }

    // Helper function to build the tree recursively
    TreeNode* buildTreeHelper(vector<int>& inorder, vector<int>& postorder, unordered_map<int, int>& inorderIndexMap,
                          int inStart, int inEnd, int postStart, int postEnd) {
        // Base case: no elements to process
        if (inStart > inEnd || postStart > postEnd) {
            return nullptr;
        }

        // The root is the last element in postorder
        int rootVal = postorder[postEnd];
        TreeNode* root1 = new TreeNode(rootVal);

        // Find the index of the root in inorder traversal
        int rootIndex = inorderIndexMap[rootVal];
        int leftSize = rootIndex - inStart;

        // Recursively build left and right subtrees
        root1->left = buildTreeHelper(inorder, postorder, inorderIndexMap, inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
        root1->right = buildTreeHelper(inorder, postorder, inorderIndexMap, rootIndex + 1, inEnd, postStart + leftSize, postEnd - 1);

        return root1;
    }


    // Main function to build the tree
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // Map to store indices of inorder elements for quick access
        unordered_map<int, int> inorderIndexMap;
        for (int i = 0; i < inorder.size(); ++i) {
            inorderIndexMap[inorder[i]] = i;
        }

        return buildTreeHelper(inorder, postorder, inorderIndexMap, 0, inorder.size() - 1, 0, postorder.size() - 1);
    }


    
    
    TreeNode* InPre(TreeNode* p){
        while (p && p->right != NULL){
            p=p->right;
        }

        return p;
    }

    TreeNode* InSuc(TreeNode* p){
        while (p && p->left != NULL){
            p=p->left;
        }

        return p;
    }
    

    
    TreeNode* remove(TreeNode* p,int key){

        
        TreeNode* q;
        
        if (p == nullptr){
            return nullptr;
        }

        if (p->left == nullptr && p->right == nullptr){

            if (p == root){
                root = nullptr;
            }
            free(p);
            return nullptr;
        }


        if (key < p->val){
            p->left = remove(p->left,key);
        } else if (key > p->val){
            p->right = remove(p->right,key);
        }else {

            q = InSuc(p->right);

            if (q != nullptr){
                p->val = q->val;
                p->right = remove(p->right,q->val);
                
            } else {
                q = InPre(p->left);
                p->val = q->val;
                p->left = remove(p->left,q->val);
            }


        }

        return p;       
 
    }


    TreeNode* AVL_Delete(TreeNode* p, int key) {
        if (p == nullptr){
            return nullptr;
        }
 
        if (p->left == nullptr && p->right == nullptr){
            if (p == root){
                root = nullptr;
            }
            delete p;
            return nullptr;
        }
 
        if (key < p->val){
            p->left = AVL_Delete(p->left, key);
        } else if (key > p->val){
            p->right = AVL_Delete(p->right, key);
        } else {
            TreeNode* q;
            q = InSuc(p->right);

            if (q != nullptr){
                p->val = q->val;
                p->right = AVL_Delete(p->right,q->val);
                
            } else {
                q = InPre(p->left);
                p->val = q->val;
                p->left = AVL_Delete(p->left,q->val);
            }
            // if (height(p->left) > height(p->right)){
            //     q = InPre(p->left);
            //     p->val = q->val;
            //     p->left = AVL_Delete(p->left, q->val);
            // } else {
            //     q = InSuc(p->right);
            //     p->val = q->val;
            //     p->right = AVL_Delete(p->right, q->val);
            // }
        }
 
        // Update height
        p->height = height(p);
 
        // Balance Factor and Rotation
        if (balance_factor(p) == 2 && balance_factor(p->left) == 1) {  // L1 Rotation
            return LL_rotation(p);
        } else if (balance_factor(p) == 2 && balance_factor(p->left) == -1){  // L-1 Rotation
            return LR_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == -1){  // R-1 Rotation
            return RR_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == 1){  // R1 Rotation
            return RL_rotation(p);
        } else if (balance_factor(p) == 2 && balance_factor(p->left) == 0){  // L0 Rotation
            return LL_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == 0){  // R0 Rotation
            return RR_rotation(p);
        }
 
        return p;
    }


    void eraseTree(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        
        // Recursively delete left and right subtrees
        eraseTree(node->left);
        eraseTree(node->right);
        
        // Delete the current node
        delete node;
    }





};


int main() {


    // BST b1;

    // b1.insert_in_BST(5);
    // b1.insert_in_BST(7);
    // b1.insert_in_BST(8);
    // b1.insert_in_BST(6);
    // b1.insert_in_BST(4);
    // b1.insert_in_BST(3);
    // b1.insert_in_BST(2);
    // b1.insert_in_BST(1);

    // b1.inorder(b1.root);

    // int mn = 4;

    // if (b1.findNode(mn) == nullptr || b1.findNode(mn)->val != mn){
    //     cout << "No" << endl;
    // } else if (b1.findNode(mn)->val == mn){
    //     cout << "Yes" << endl;

    // }

    // b1.number_of_leaves1(b1.root);

    // cout << "Number of leaves:" << b1.number_of_leaves << endl;

    // b1.number_of_nodes1(b1.root);

    // cout << "Number of nodes:" << b1.number_of_nodes;

    // cout << "Height:" << b1.height(b1.root) - 1<< endl;

    // cout << "LCA" << b1.lca(b1.root,8,1)->val << endl;

    // //boundry traversal
    // b1.print_boundry_clockwise();

    // cout << endl;

    // //postorder from other 2 traversals
    // int as[] = {1,2,3,4,5,6,7,8};
    // int bs[] = {5,4,3,2,1,7,6,8};
    

    // b1.print_post_order(as,bs,8);
    // cout << endl;



    // //preorder from other 2 traversals
    // vector<int> inorder1 = {1,2,3,4,5,6,7,8};
    // vector<int> postorder1 = {1,2,3,4,6,8,7,5};


    // b1.preorder(b1.buildTree(inorder1, postorder1));

    // cout << endl << endl;
    
    
    
    // //delete (first check if element present in tree or not)
    // TreeNode* p1;
    // p1 = b1.remove(b1.root,60);

    // b1.inorder(b1.root);

    // cout << endl << b1.root->val;



    BST b1;

    // b1.root = b1.insert_in_AVL(b1.root,5);
    // b1.insert_in_AVL(b1.root,7);
    // b1.insert_in_AVL(b1.root,8);
    // b1.insert_in_AVL(b1.root,6);
    // b1.insert_in_AVL(b1.root,4);
    // b1.insert_in_AVL(b1.root,3);
    // b1.insert_in_AVL(b1.root,2);
    // b1.insert_in_AVL(b1.root,1);
    // // b1.insert_in_AVL(b1.root,40);
    // // b1.insert_in_AVL(b1.root,50);
    // // b1.insert_in_AVL(b1.root,60);

    // cout << b1.root->val << endl;

    // b1.preorder(b1.root);

    // b1.AVL_Delete(b1.root,8);

    // cout << endl;

    // b1.preorder(b1.root);

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

            if (operation == 'B'){
                //cout << "Its a B";

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
                //cout << b1.root << endl;
                //b1.inorder(b1.root);




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
                //cout << b1.root << endl;
                //b1.inorder(b1.root);
                




            } else if (operation == 'I'){




                int ins;
                //cout << "Enter int to insert:";

                cin >> ins;

                if (tree_type == -1 || tree_type == 0){
                    tree_type == 0;
                    b1.insert_in_BST(ins); 


                } else {

                    //cout << "inserted in AVL";

                    b1.insert_in_AVL(b1.root,ins);

                }

                

                //cout << b1.root << endl;
                //b1.inorder(b1.root);




                
            } else if (operation == 'R'){





                int rm;
                //cout << "Enter int to remove:";

                cin >> rm;

                if (tree_type == 0){

                    //cout << "removed in BST";
                    if (b1.root != nullptr){
                        TreeNode* node = b1.findNode(rm);
                        if (node != nullptr && node->val == rm){
                            b1.remove(b1.root,rm);
                        }
                    } 


                } else if (tree_type == 1){

                    //cout << "removed in AVL";

                    if (b1.root != nullptr){
                        TreeNode* node = b1.findNode(rm);
                        if (node != nullptr && node->val == rm){
                            b1.AVL_Delete(b1.root,rm);
                        }
                    }

                }

                

                //cout << b1.root << endl;
                //b1.inorder(b1.root);




                
            } else if (operation == 'F'){




                int elem;
                //cout << "Enter element to find:";
                cin >> elem;

                if (b1.findNode(elem) == nullptr || b1.findNode(elem)->val != elem){
                    cout  << "No";
                    cout << endl;
                } else if (b1.findNode(elem)->val == elem){
                    cout<< "Yes";
                    cout << endl;

                }





                
            } else if (operation == 'L'){




                b1.number_of_leaves1(b1.root);

                cout << b1.number_of_leaves;
                //cout << endl;




                
            } else if (operation == 'N'){


                b1.number_of_nodes = 0;
                b1.number_of_nodes1(b1.root);

                //cout << b1.number_of_nodes << endl;
                cout << b1.number_of_nodes;
                cout << endl;




                
            } else if (operation == 'Q'){



                b1.inorder(b1.root);
                cout << endl;



                
            } else if (operation == 'W'){



                b1.preorder(b1.root);
                cout << endl;



                
            } else if (operation == 'E'){



                b1.postorder(b1.root);
                cout << endl;



                
            } else if (operation == 'H'){


                cout << b1.height(b1.root) - 1;
                cout << endl;




                
            } else if (operation == 'M'){



                b1.print_boundry_clockwise();
                //cout << endl;



                
            } else if (operation == 'C'){



                int a1;
                int a2;

                //cout << "Enter 2 numbers:";

                cin >> a1;
                cin >> a2;

                bool e_a1;
                bool e_a2;

                if (b1.findNode(a1) == nullptr || b1.findNode(a1)->val != a1){
                    //cout << "No" << endl;
                    e_a1 = false;
                } else if (b1.findNode(a1)->val == a1){
                    e_a1 = true;

                }

                if (b1.findNode(a2) == nullptr || b1.findNode(a2)->val != a2){
                    //cout << "No" << endl;
                    e_a2 = false;
                } else if (b1.findNode(a2)->val == a2){
                    e_a2 = true;

                }

                if (!e_a2 || !e_a1){
                    cout << -1 << endl;
                } else if (a1 == a2){
                    cout << a1 << endl;
                } else {
                    cout << b1.lca(b1.root,a1,a2)->val << endl;
                }



                
            } else if (operation == 'Z'){




                int N;

                //cout << "Enter N:";

                cin >> N;

                // int pre[N];
                // int in[N];

                int* pre = new int[N];
                int* in = new int[N];

                for(int i=0;i<N;i++){

                    cin >> pre[i];

                }

                for(int i=0;i<N;i++){

                    cin >> in[i];

                }

                b1.print_post_order(in,pre,N);
                cout << endl;





                
            } else if (operation == 'Y'){



                int N1;
                //cout << "Enter N:";
                cin >> N1;
                
                vector<int> pos;
                vector<int> in1;


                

                for(int i=0;i<N1;i++){

                    int temp2;

                    cin >> temp2;

                    pos.push_back(temp2);



                }

                for(int i=0;i<N1;i++){

                    int temp3;
                    cin >> temp3;

                    in1.push_back(temp3);

                }

                b1.preorder(b1.buildTree(in1, pos));

                cout << endl;


                



            } else if (operation == 'K'){



                b1.eraseTree(b1.root);
                b1.root = nullptr;


                
            }else if (operation == 'D'){
                // cout << endl;
                break;
                cout << endl;
            }


        }
        cout << endl;


    }

    







}