#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h

#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )             --> Insert x
// void remove( x )             --> Remove x
// bool contains( x )           --> Return true if x is present
// Comparable findMin( )        --> Return smallest item
// Comparable findMax( )        --> Return largest item
// boolean isEmpty( )           --> Return true if empty; else false
// void makeEmpty( )            --> Remove all items
// void printTree( )            --> Print tree in sorted order
// 
// Comparable get_parent( x )   --> Return the value stored in the parent of the Node storing x
 // ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h

public:
    class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

    BinarySearchTree() : root{nullptr} {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root)} {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return (contains(x, root) != nullptr);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        } else {
            //inorder(root, out);
            preorder(root, out);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root);
        //std::cout << "inserted " << x << '\n';
        //printTree();
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    }


    /**
     * Find the parent of the Node containing x and return its stored value.
     */
    const Comparable get_parent( const Comparable& x) const {
        /*if (isEmpty()) {
            throw UnderflowException{};
        }*/
        Node* temp = contains(x, root);

        return (temp && temp->parent) ? temp->parent->element : Comparable{};

    }

private:
    Node *root;

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node* insert(const Comparable& x, Node* t, Node* parent = nullptr) {
        if (t == nullptr) { //empty subtree
            t = new Node{ x, nullptr, nullptr, parent };
            //std::cout << "New node " << x << " inserted\n";
        }

        else if (x < t->element) {
            /*if (t->left == nullptr) {
                t->left = new Node(x, nullptr, nullptr, t);
                std::cout << "Inserted leaf " << x <<" on left of " << t->element << '\n';
                //return t;
                return t->left;
            }*/
            //std::cout << "Recursive call left \n";
            t->left = insert(x, t->left, t);

        }

        else if (t->element < x) {
            /*if (t->right == nullptr) {
                t->right = new Node(x, nullptr, nullptr, t);
                std::cout << "Inserted leaf " << x << " on right of " << t->element << '\n';
                return t->right;
                //return t;
            }*/
            //std::cout << "Recursive call right \n";
            t->right = insert(x, t->right, t);

        }

        else {
            // Duplicate; do nothing
          //std::cout << "Duplicate found \n";
        }
        return t;
    }


            //Node* insert(const Comparable& x, Node* t) {
            //    if (t == nullptr) {
            //        t = new Node{ x, nullptr, nullptr };
            //    }
            //    else if (x < t->element) {
            //        t->left = insert(x, t->left);
            //    }
            //    else if (t->element < x) {
            //        t->right = insert(x, t->right);
            //    }
            //    else {
            //        ;  // Duplicate; do nothing
            //    }
            //    return t;
            //}


    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node *remove(const Comparable &x, Node *t) {
        if (t == nullptr) {
            return t;  // Item not found
        }

        if (x < t->element) {
            t->left = remove(x, t->left);
        }
        
        else if (t->element < x) {
            t->right = remove(x, t->right);
        }
        
        else if (t->left != nullptr && t->right != nullptr) {  // Two children
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
        }
        
        else {
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            
            
            if (t) {
                t->parent = oldNode->parent;
            }
            
            delete oldNode;
        }

        return t;
    }

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    Node *findMin(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    Node *findMax(Node *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return t;  // Match
        }
    }
    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }
        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node *makeEmpty(Node *t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node *t, std::ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }

    /**
     * Private member function to print a subtree rooted at t using pre-order.
     * In-order traversal is used
     */
    void preorder(Node* t, std::ostream& out, uint16_t depth = 0) const {

        out << std::setw((std::streamsize)(2*(depth+1))) << t->element << '\n';
     
        if (t->left != nullptr) {
            preorder(t->left, out, depth+1);
        }
        if (t->right != nullptr) {
            preorder(t->right, out, depth+1);
        }


        /*if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }*/
    }


    /**
     * Private member function to clone subtree.
     */
    Node *clone(Node *t/*, Node* parent = nullptr*/) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            Node* left = clone(t->left);


            return new Node{t->element, clone(t->left/*, parent*/), clone(t->right/*, parent*/), clone(t->parent)};
        }
    }
};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"