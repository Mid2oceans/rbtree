//
//  rbtree.h
//  Project 7
//
//  Xinduo
//

#ifndef rbtree_hpp
#define rbtree_hpp

#include <stdio.h>
#include<iostream>
#include <string>
#include <cstdlib>

using namespace std;

template<class KeyType>
class Node
{
public:
    KeyType* key;
    bool isRed; //true == red; false == black
    Node<KeyType>* left;
    Node<KeyType>* right;
    Node<KeyType>* parent;
    string toString() const;
    Node(KeyType k){
        this->key = new KeyType(k);
        this->left = this->right = this->parent = NULL;
        this->isRed = true;
    }
    Node();
};

template <class KeyType>
bool operator<=(const Node<KeyType>& lnode,const Node<KeyType>& rnode)
{return ( *(lnode.key) <= *(rnode.key) );};

template <class KeyType>
bool operator<(const Node<KeyType>& lnode,const Node<KeyType>& rnode)
{return ( *(lnode.key) < *(rnode.key) );};

template <class KeyType>
bool operator>(const Node<KeyType>& lnode,const Node<KeyType>& rnode)
{return ( *(lnode.key) > *(rnode.key) );};

template<class KeyType>
class rbtree
{
protected:
  Node<KeyType>* root;
  //the resursive methods for delete,copy, insert, turning into string from a given traversal
  void post_order_delete(Node<KeyType>* x);
  void pre_order_copy(Node<KeyType>* current, Node<KeyType>* x);
  Node<KeyType>* insert(KeyType* k, Node<KeyType>* n,Node<KeyType>* p);
  void rbInsertFixUp(Node<KeyType>* z);
  void leftRotation(Node<KeyType>* n);
  void rightRotation(Node<KeyType>* n);
  std::string inOrderString(const Node<KeyType>* x) const;
  std::string preOrderString(const Node<KeyType>* x) const;
  std::string postOrderString(const Node<KeyType>* x) const;

  Node<KeyType>* getn(const KeyType& k, Node<KeyType> *n) const;// return first node with key equal to k
  Node<KeyType>* subtreemin(Node<KeyType>* k)const;//return the min node in the subtree rooted at node k
  KeyType* subtreemax(Node<KeyType>* k)const;//return the max item in the subtree rooted at node k
  //void Transplant(Node<KeyType>* u,Node<KeyType>* v);// Transplant the subtree rooted at node v to node u
  void deepCopy(const rbtree<KeyType>& rbtree1);//deepcopy the given rbtree
  std::string toString(int order) const;//giving the traversal type, transform the rbtree to string


public:
  rbtree();               // default constructor
  rbtree(const rbtree<KeyType> & rbtree1);    // copy constructor
  virtual ~rbtree();        //destructor

  rbtree& operator =(const rbtree & rbtree1);     // assignment operator

  bool empty() const;                           // return true if empty; false o/w
  KeyType *get(const KeyType& k) const;         // return first item with key equal to k
  virtual void insert(KeyType *k);                      // insert k into the tree
  //void remove(const KeyType& k);                // delete first item with key equal to k
  KeyType *maximum() const;                     // return the maximum item
  KeyType *minimum()const ;                     // return the minimum item
  KeyType *successor(const KeyType& k) const;   // return the successor of k
  KeyType *predecessor(const KeyType& k) const; // return the predecessor of k
  std::string inOrder() const;              // return string of items from an inorder traversal
  std::string preOrder() const;             // return string of items from a preorder traversal
  std::string postOrder() const;            // return string of items from a postorder traversal

};

template <class KeyType>
std::ostream& operator<<(std::ostream& stream, const rbtree<KeyType>& rbtree1){
  return (stream << rbtree1.inOrder());
};

class EmptyError { }; // rbtree empty exception
class KeyError { }; // rbtree key exception

#include "rbtree.cpp"

#endif /* rbtree_h */
