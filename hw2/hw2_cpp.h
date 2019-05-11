#include <cstdio>
#include <assert.h>

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

    Node* uncle() {
        // if no parent or grandparent, uncle is NULL
        if(parent == NULL || parent -> parent == NULL) return NULL;

        // Check parent is left child of grandparent
        if(parent -> isLeftChild()) {
            // uncle is the right child of grandparent
            return parent -> parent -> right;
        } else {
            // uncle is the left child of grandparent
            return parent -> parent -> left;
        }
    }

    // Checks if self is the left child of parent
    bool isLeftChild() { return this == parent -> left; }

    Node* sibling() { // returns pointer to sibling
        if(parent == NULL) return NULL;
        if(isLeftChild()) return parent -> right;
        return parent -> left;
    }

    // pull the node down and set newParent in its place
    void moveDown(Node* newParent) {
        if(parent != NULL) {
            if(isLeftChild()) parent -> left = newParent;
            else parent -> right = newParent;
        }
        newParent -> parent = parent;
        parent = newParent;
    } // don't have to update sizes here
};

class Tree {
private:
    Node *root;
    void updateSize(Node* node); // update size
    Node* replace(Node* node); // find node to replace node when deleting node
    void insertFixUp(Node* node); // Fix tree on insert
    void leftRotate(Node* node); // left rotation
    void rightRotate(Node* node); // right rotation
    void transplant(Node* u, Node* v);
    void deleteFixUp(Node* node); // Fix tree on delete

    // Todo
    Node* deleteNode(Node* node); // delete node from the tree
public:
    // Node* insert(Node* root, Node* newNode); // Insert newNode at subtree rooted at root
    Tree() { root = NULL; } // Constructor
    Node* getRoot(); // return root
    int insert(int x); // Insert x
    Node* search(int x); // search for x
    int deleteVal(int x); // delete node with key x
    void inOrder(Node* node); // print inorder traversal starting at node
};

//////////////////////////////////////////////////////////////////////////////////////

Node* Tree::getRoot() {
    return root;
}

/* Insert newNode at subtree rooted at root
Node* Tree::insert(Node* root, Node* newNode) {
    if(root == NULL) {
        newNode -> color = RED;
        return newNode;
    }
    if(newNode -> data < root -> data) {
        root -> left = insert(root -> left, newNode);
        root -> left -> parent = root;
    } else if(newNode -> data > root -> data) {
        root -> right = insert(root -> right, newNode);
        root -> right -> parent = root;
    }
    return root;
}
//*/

// Swap node colors of u and v
void swapColor(Node* u, Node* v) {
    bool tmp;
    tmp = u -> color;
    u -> color = v -> color;
    v -> color = tmp;
}

// Left Rotation
void Tree::leftRotate(Node* node) {
    Node* newParent = node -> right;
    int tmp = node -> size;

    // root needs to be updated in this case
    if(node == root) root = newParent;

    node -> moveDown(newParent);

    // left subtree of newParent should be the right subtree of node
    node -> right = newParent -> left;

    // update size
    node -> size = node -> left -> size + node -> right -> size + 1;

    // set node as parent if not null
    if(newParent -> left != NULL) newParent -> left -> parent = node;

    // set left subtree of newParent as node
    newParent -> left = node;

    // update size
    newParent -> size = node -> size + newParent -> right -> size + 1;

    assert(tmp == newParent -> size);
}

// Right Rotation
void Tree::rightRotate(Node* node) {
    Node* newParent = node -> left;
    int tmp = node -> size;

    // root needs to be updated in this case
    if(node == root) root = newParent;

    node -> moveDown(newParent);

    // right subtree of newParent should be the left subtree of node
    node -> left = newParent -> right;

    // update size
    node -> size = node -> right -> size + node -> left -> size + 1;

    // set node as parent if not null
    if(newParent -> right != NULL) newParent -> right -> parent = node;

    // set right subtree of newParent as node
    newParent -> right = node;

    // update size
    newParent -> size = node -> size + newParent -> left -> size + 1;

    assert(tmp == newParent -> size);
}


// Fix the tree on insert
void Tree::insertFixUp(Node *node) {
    if(node == root) { // if root, color it black and return
        printf("??? insertFixUp(root) has been called!\n");
        node -> color = BLACK;
        return;
    }

    Node* parent = node -> parent;
    Node* grand = parent -> parent;
    Node *uncle = node -> uncle();

    // grandparent is not null
    // if grandparent is null, parent must have been root
    // which is black, and this if-then clause is not executed
    if(parent -> color != BLACK) { // only if parent color is red
        if(uncle != NULL && uncle -> color == RED) { // case 1
            parent -> color = BLACK;
            uncle -> color = BLACK;
            grand -> color = RED;
            insertFixUp(grand);
        } else {
            if(parent -> isLeftChild()) { // parent is on left
                if(node -> isLeftChild()) { // node is left child
                    swapColor(parent, grand);
                } else { // node is right child
                    leftRotate(parent);
                    swapColor(node, grand);
                }
                rightRotate(grand);
            } else { // parent is on right
                if(node -> isLeftChild()) { // node is left child
                    rightRotate(parent);
                    swapColor(node, grand);
                } else { // node is right child
                    swapColor(parent, grand);
                }
                leftRotate(grand);
            }
        }
    }
}

// Insert x to the tree
// if insert is successful, return x
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
    insertFixUp(newNode);

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

// Delete x from the tree
// if delete is successful, return x
// else return 0
int Tree::deleteVal(int x) {
    if(root == NULL) return 0; // empty tree

    // Search for node with key x
    Node* del = search(x);

    // Note that search does not return NULL
    if(del -> data != x) return 0; // delete fails

    deleteNode(del); // delete node and fix up colors here

    return x;
}

// find node to replace node when deleting node
// Node* Tree::replace(Node* node) {
//     if(node -> left) {
//         if(node -> right) { // node has 2 children
//             // return least element in right subtree
//             Node* tmp = node -> right;
//             while(tmp -> left) tmp = tmp -> left;
//             return tmp;
//         } else { // has only left child
//             return node -> left;
//         }
//     } else if(node -> right) { // has only right child
//         return node -> right;
//     } else return NULL; // leaf
// }

// Replace the subtree rooted at node u with the subtree rooted at node v
void Tree::transplant(Node* u, Node* v) {
    if(u -> parent == NULL) root = v;
    else if(u -> isLeftChild()) u -> parent -> left = v;
    else u -> parent -> right = v;
    // if(v != NULL)
    v -> parent = u -> parent;
}

// Delete node with node from the tree, do fixups
Node* Tree::deleteNode(Node* node) {
    Node* tmp = node;
    Node* v;
    Node* nil = new Node(-1); // node for nil
    nil -> size = 0;
    bool orig_color = node -> color;

    if(node -> left == NULL) { // no left child
        v = node -> right; // v may be null here
        if(v == NULL) {
            v = nil;
            node -> right = nil;
            nil -> parent = node;
        }
        transplant(node, node -> right); // replace with right child
    } else if(node -> right == NULL) { // no right child
        v = node -> left; // not null here
        transplant(node, node -> left); // replace with left child
    } else { // node has both child
        // get minimum element from the right subtree
        tmp = node -> right;
        while(tmp -> left) tmp = tmp -> left;
        orig_color = tmp -> color; // tmp is not null

        v = tmp -> right; // v may be null here
        if(v == NULL) {
            tmp -> right = nil;
            v = nil;
            nil -> parent = tmp;
        }
        if(tmp -> parent == node) { // right subtree of node has no left child
            if(v != NULL) v -> parent = tmp;  // Does nothing ???
        } else {
            transplant(tmp, tmp -> right); // replace
            // Set right subtree of tmp as right subtree of node
            tmp -> right = node -> right;
            tmp -> right -> parent = tmp;
        }
        transplant(node, tmp); // replace node with tmp
        // Set left subtree of tmp as left subtree of node
        tmp -> left = node -> left;
        tmp -> left -> parent = tmp;
        tmp -> color = node -> color; // update color
    }
    delete node;
    updateSize(v);
    if(v -> isLeftChild()) {
        v -> parent -> left = NULL;
    } else {
        v -> parent -> right = NULL;
    }
    nil = 0;
    delete nil;


    if(orig_color == BLACK) deleteFixUp(v);
    // Node* tmp = replace(node); // find node to replace

    // // check black-black
    // bool blackflag = ((tmp == NULL || tmp -> color == BLACK) && (node -> color == BLACK));
    // Node* parent = node -> parent;
    //
    // if(tmp == NULL) {
    //     // tmp is NULL, so node must be leaf
    //     if(node == root) root = NULL;
    //     else {
    //         if(blackflag) {
    //             fixBlackBlack(node);
    //         } else {
    //             if(node.sibling() != NULL) {
    //                 node.sibling() -> color = RED;
    //             }
    //         }
    //     }
    // }

    return tmp;
}

// Fix tree on deletion
void Tree::deleteFixUp(Node* node) {

}

// Update sizes
void Tree::updateSize(Node* node) {
    if(node == NULL) return;
    Node* tmp = node -> parent;
    while(tmp) { // while tmp != NULL
        int nsize = 1;
        if(tmp -> left) nsize += tmp -> left -> size;
        if(tmp -> right) nsize += tmp -> right -> size;
        tmp -> size = nsize;
        tmp = tmp -> parent;
    }
}

// Inorder traversal, for debugging purposes
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
// if insert is successful, return x
// else return 0
int os_insert(int x) {
    return tree.insert(x);
}

// Delete x from the tree
// if delete is successful, return x
// else return 0
int os_delete(int x) {
    return tree.deleteVal(x);
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
