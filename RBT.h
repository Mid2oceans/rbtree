#ifndef RBT_H
#define RBT_H
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

template<class KeyType>
class Node
{
public:
    Node(KeyType key){
      k=key;
      left =NULL;
      right=NULL;
      parent=NULL;
    }
    KeyType k;
    Node * parent;
    Node * left;
    Node * right;
    bool isRed =true;
};


template <class KeyType>
class RBT
{
    public:
        ~RBT();
        RBT();
        void operator=(const RBT& tree);
        RBT(const RBT<KeyType>& tree);
        void copy(Node<KeyType>* x);
        Node<KeyType>* getRoot() const;
        void del(Node<KeyType>* x);
        bool empty() const;  // return true if empty; false o/w
        Node<KeyType>* get(const KeyType& k) const; // return first item with key equal to k
        KeyType* get2(const KeyType& k) const; // return first item with key equal to k
        bool isUncleRed();

        void insert(KeyType *k); // insert k into the tree
        void remove(const KeyType& k); // delete first item with key equal to k
        void Transplant(Node<KeyType>* u, Node<KeyType>* v);
        Node<KeyType>* findMinimum(Node<KeyType>* root) const;
        Node<KeyType>* findMaximum(Node<KeyType>* root) const;
        KeyType* maximum(); // return the maximum item
        KeyType* minimum(); // return the minimum item
        KeyType* successor(const KeyType& k) const; // return the successor of k
        KeyType* predecessor(const KeyType& k) const; // return the predecessor of k
        string inOrder(); // return string of items from an inorder traversal
        string preOrder(); // return string of items from a preorder traversal
        string postOrder(); // return string of items from a postorder traversal
        string inOrder2(Node<KeyType> * x); // return string of items from an inorder traversal
        string preOrder2(Node<KeyType>* x); // return string of items from a preorder traversal
        string postOrder2(Node<KeyType>* x); // return string of items from a postorder traversal
        bool isUncleRed(Node<KeyType>* n); //maybe change to getUncle so we can have the node pointer
        




    protected:
        string s;
        Node<KeyType> * root;
        KeyType k;


};

class FullError { }; // full exception
class EmptyError { }; // empty exception
class KeyError { }; // key exception

#endif
