#include <cstdio>

#ifndef HW2
#define HW2

char str[2][10] = {"RED", "BLACK"};
enum Color {RED, BLACK};

struct Node {
    int data; // key value
    Node *left, *right, *parent; // left, right child, parent node
    int size; // number of nodes in the tree including self
    bool color; // 1 for black, 0 for red

    Node(int x) { // create node with key x
        data = x;
        left = right = parent = NULL;
        color = RED; // default color red
        size = 1;
    }
};

class Tree {
// private:
public:
    Node *root;
    // Node* insert(Node* root, Node* newNode); // Insert newNode at subtree rooted at root
    Node* fixRedRed(Node* node);
    Tree() { root = NULL; } // Constructor
    int insert(int x); // Insert x
    Node* search(int x); // search for x
    void updateSize(Node* node);
    void inOrder(Node* node); // print inorder traversal starting at node
};

//////////////////////////////////////////////////////////////////////////////////////

// Insert newNode at subtree rooted at root
// Node* Tree::insert(Node* root, Node* newNode) {
//     if(root == NULL) {
//         newNode -> color = RED;
//         return newNode;
//     }
//     if(newNode -> data < root -> data) {
//         root -> left = insert(root -> left, newNode);
//         root -> left -> parent = root;
//     } else if(newNode -> data > root -> data) {
//         root -> right = insert(root -> right, newNode);
//         root -> right -> parent = root;
//     }
//     return root;
// }

// Insert x to the tree
// if insert is successful, return 0
// else return 0
int Tree::insert(int x) {
    Node* newNode = new Node(x);
    if(root == NULL) { // if root is null
        root = newNode;
        root -> color = BLACK; // set as root and color it black
        return x;
    }
    // search for a place to insert
    Node* tmp = search(x);

    // If node with x already exists, return 0
    if(tmp -> data == x) return 0;

    // If such node doesn't exist, search will return the place to insert the new node
    newNode -> parent = tmp;
    if(x < tmp -> data) tmp -> left = newNode;
    else tmp -> right = newNode;

    // update sizes of left and right subtree
    updateSize(newNode);

    // fix Red-Red at newNode
    // fixRedRed(newNode);

    return x;
}

// search for node with key x
// if node exists, returns pointer to that node
// else, returns the current node
Node* Tree::search(int x) {
    Node* tmp = root;
    while(tmp) { // while tmp != NULL
        if(x < tmp -> data) {
            if(tmp -> left == NULL) break;
            else tmp = tmp -> left;
        } else if(x > tmp -> data) {
            if(tmp -> right == NULL) break;
            else tmp = tmp -> right;
        } else break;
    }
    return tmp;
}

void Tree::updateSize(Node* node) {
    Node* tmp = node -> parent;
    while(tmp) { // while tmp != NULL
        int nsize = 1;
        if(tmp -> left) nsize += tmp -> left -> size;
        if(tmp -> right) nsize += tmp -> right -> size;
        tmp -> size = nsize;
        tmp = tmp -> parent;
    }
}

// Inorder traversal, for debuggin purposes
void Tree::inOrder(Node* node) {
    if(node == NULL) return;
    inOrder(node -> left);
    printf("key: %5d, ", node -> data);
    if(node -> parent) {
        printf("P: %5d, ", node -> parent -> data);
    } else {
        printf("P:  NULL, ");
    }
    if(node -> left) {
        printf("L: %5d, ", node -> left -> data);
    } else {
        printf("L:  NULL, ");
    }
    if(node -> right) {
        printf("R: %5d, ", node -> right -> data);
    } else {
        printf("R:  NULL, ");
    }
    printf("size: %5d, color: %s\n", node -> size, str[node -> color]);
    inOrder(node -> right);
}

//////////////////////////////////////////////////////////////////

Tree tree;

void init() { // initialize
    tree = Tree();
}

// Insert x to the tree
// if insert is successful, return 0
// else return 0
int os_insert(int x) {
    return tree.insert(x);
}

// Delete x from the tree
// if delete is successful, return 0
// else return 0
int os_delete(int x) {
    return -1;
}

int os_select(int i) { // select i-th element
    return -1;
}

int os_rank(int x) { // rank of element with key x
	return -1;
}

bool check(int opt_seq[], int in_seq[], int out_seq[], int n){
    init();
    for(int i = 0; i < n; ++i) {
		if(opt_seq[i] == 0) {
            if(os_insert(in_seq[i]) != out_seq[i]) {
                return false;
            }
        } else if(opt_seq[i] == 1) {
            if(os_delete(in_seq[i]) != out_seq[i]) {
                return false;
            }
        } else if(opt_seq[i] == 2) {
            if(os_select(in_seq[i]) != out_seq[i]) {
                return false;
            }
        } else if(opt_seq[i] == 3) {
            if(os_rank(in_seq[i]) != out_seq[i]) {
                return false;
            }
        }
    }
    return true;
}

#endif
