
#include <iostream>
using namespace std;

//for creating a tree node
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


//this class contains all the BST and AVL tree related functions
class BST {

public:

    TreeNode* root;
    int number_of_leaves;
    int number_of_nodes;

    //initializing the root and other paraeters
    BST(){
        root = nullptr;
        number_of_leaves = 0;
        number_of_nodes = 0;
    }

    //code for insertion in BST
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


    //function to update heights in case AVL rotations change the height of node
    void update_heights(TreeNode* node){

        if (node == nullptr){
            return;
        }

        node->height = height(node) - 1;
        update_heights(node->left);
        update_heights(node->right);

    }

    //function to calculate the balance factor of a node
    int balance_factor(TreeNode* p){
        
        int hl;
        int hr;

        hl = height(p->left);
        hr = height(p->right);

        return hl-hr;
    }

    //function to perform LL rotation in AVL tree
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

    //function to perform LR rotation in AVL tree
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

    //function to perform RR rotation in AVL tree
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

    //function to perform RL rotation in AVL tree
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

    //function to insert node in AVL tree
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

        //recursively update the heights of node in case of rotations
        p->height = height(p);


        //check if balance factor of node is acceptable if not then perform appropriate rotation
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


    //function to find node in a tree
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


    //function to calculate number of leaves in tree
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

    //function to calculate number of nodes in tree
    void number_of_nodes1(TreeNode* node){

        if (node == nullptr){
            return;
        } else {
            number_of_nodes += 1;
        }

        number_of_nodes1(node->left);
        number_of_nodes1(node->right);
    }


    //function to print inorder traversal of a tree
    void inorder(TreeNode* node){

        if (node == nullptr){
            return;
        }
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    //function to print preorder traversal of a tree
    void preorder(TreeNode* node){

        if (node == nullptr){
            return;
        }
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    }

    //function to print postorder traversal of a tree
    void postorder(TreeNode* node){

        if (node == nullptr){
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
    }


    //function to calculate height of a tree
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

    //function to calculate lowest common ancestor of a 2 nodes
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


    //function to print boundry traversal of a tree
    void print_boundry_clockwise(){

        if (root == nullptr){
            return;
        }

        cout << root->val << " ";

        print_boundry_right(root->right);
        print_boundry_leaves(root);
        print_boundry_left(root->left);
    }

    //helper function to print right side boundry nodes of a tree
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

    //helper function to print left side boundry nodes of a tree
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

    //helper function to print leaf boundry of a tree
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


    //helper function to search element in an array
    int search(int arr[],int a,int n){

        for(int i=0;i<n;i++){
            if (arr[i] == a){
                return i;
            }
        }
        return -1;
    }

    //function for printing post order from preorder and inorder
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
    TreeNode* buildTreeHelper(int inorder[], int postorder[], int inStart, int inEnd, int postStart, int postEnd) {
        // Base case: no elements to process
        if (inStart > inEnd || postStart > postEnd) {
            return nullptr;
        }

        // The root is the last element in postorder
        int rootVal = postorder[postEnd];
        TreeNode* root1 = new TreeNode(rootVal);

        // Find the index of the root in the inorder traversal
        int rootIndex = -1;
        for (int i = inStart; i <= inEnd; ++i) {
            if (inorder[i] == rootVal) {
                rootIndex = i;
                break;
            }
        }

        int leftSize = rootIndex - inStart;

        // Recursively build left and right subtrees
        root1->left = buildTreeHelper(inorder, postorder, inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
        root1->right = buildTreeHelper(inorder, postorder, rootIndex + 1, inEnd, postStart + leftSize, postEnd - 1);

        return root1;
    }

    // Main function to build the tree from inorder and postorder to find preorder traversal
    TreeNode* buildTree(int inorder[], int postorder[], int n) {
        return buildTreeHelper(inorder, postorder, 0, n - 1, 0, n - 1);
    }


    
    //function for finding inorder predecessor
    TreeNode* InPre(TreeNode* p){
        while (p && p->right != NULL){
            p=p->right;
        }

        return p;
    }

    //function for finding inorder sucessor
    TreeNode* InSuc(TreeNode* p){
        while (p && p->left != NULL){
            p=p->left;
        }

        return p;
    }
    

    //function to remove node from BST
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

    //function to delete node form AVL tree
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
 
        // checking balance factor of a node if it is unacceptable then performing necessary rotations
        if (balance_factor(p) == 2 && balance_factor(p->left) == 1) {
            return LL_rotation(p);
        } else if (balance_factor(p) == 2 && balance_factor(p->left) == -1){  
            return LR_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == -1){  
            return RR_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == 1){ 
            return RL_rotation(p);
        } else if (balance_factor(p) == 2 && balance_factor(p->left) == 0){ 
            return LL_rotation(p);
        } else if (balance_factor(p) == -2 && balance_factor(p->right) == 0){
            return RR_rotation(p);
        }
 
        return p;
    }

    //function to delete a tree nodes recursively
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


    void print_no(){
        cout  << "No";
        cout << endl;
    }

    void print_yes(){
        cout  << "Yes";
        cout << endl;
    }


};


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