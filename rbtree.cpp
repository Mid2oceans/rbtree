//
//  rbtree.cpp
//  Project 7
//
//  Xinduo Fan
//
#include<iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "rbtree.h"
using namespace std;

#ifndef _rbtree_cpp
#define _rbtree_cpp


/*================================================
defaul constructtor
postcondition: an empty rbtree is created
================================================*/
template<class KeyType>
rbtree<KeyType>:: rbtree(){
  this->root = NULL;
}

/*================================================
copy constructtor
postcondition: a rbtree with the same key values as the given rbtree is created
================================================*/
template<class KeyType>
rbtree<KeyType>::rbtree(const rbtree<KeyType>& rbtree1){
  if (rbtree1.root!=NULL) {
    deepCopy(rbtree1);
  }else {
    rbtree();
  }
}

/*================================================
deepCopy
precondition: this rbtree is empty
postcondition: this rbtree has the same key values as the given rbtree
================================================*/
template<class KeyType>
void rbtree<KeyType>::deepCopy(const rbtree<KeyType>& rbtree1){
  if (rbtree1.root!=NULL){
    this->root = new Node<KeyType>;
    this->root->parent = NULL;
    pre_order_copy(this->root, rbtree1.root);
  }else{
    rbtree();
  }
}

/*================================================
pre_order_copy
precondition: the current node is empty
postcondition: the subtree rooted at current node having the same structure and values as the one rooted at node x
================================================*/
template<class KeyType>
void rbtree<KeyType>::pre_order_copy(Node<KeyType>* current, Node<KeyType>* x){
    current->key = new KeyType;
    *(current->key) = *(x->key);
    current->isRed = x->isRed;
    if ((x->left)!=NULL){
      current->left = new Node<KeyType>;
      current->left->parent = current;
      pre_order_copy(current->left,x->left);
    }
    if ((x->right)!=NULL) {
      current->right = new Node<KeyType>;
      current->right->parent = current;
      pre_order_copy(current->right,x->right);
    }
}

//================================================
//destructor
//================================================
template<class KeyType>
rbtree<KeyType>:: ~rbtree(){
  post_order_delete(this->root);
}

/*================================================
post_order_delete
postcondition: the subtree rooted at node x is deleted
================================================*/
template<class KeyType>
void rbtree<KeyType>::post_order_delete(Node<KeyType>* x){
    if (x!=NULL){
      post_order_delete(x->left);
      post_order_delete(x->right);
      delete x;
    }
}
/*================================================
pre_order_copy
precondition: both this rbtree and the given rbtree1 exist
postcondition: this rbtree have the same structure and values as rbtree1
================================================*/
template<class KeyType>
rbtree<KeyType>& rbtree<KeyType>::operator=(const rbtree<KeyType>& rbtree1){
  if (this->root != rbtree1.root){
    post_order_delete(this->root);
    deepCopy(rbtree1);
  }
  return *this;
}

//================================================
// return true if empty; false o/w
//================================================
template<class KeyType>
bool rbtree<KeyType> :: empty() const{
  return (this->root == NULL);
}

//================================================
// return first item with key equal to k
//================================================
template<class KeyType>
KeyType* rbtree<KeyType> :: get(const KeyType& k) const{
  Node<KeyType> *x;
  x = this->root;
  while (x!=NULL && *(x->key)!=k){
    if(k < *(x->key))  x = x->left;
    else  x = x->right;
  }
  if (x==NULL) throw KeyError();
  return (x->key);
}

template<class KeyType>
Node<KeyType>* rbtree<KeyType> :: getn(const KeyType& k, Node<KeyType> *n) const{
  Node<KeyType> *x = n;
  while (x!=NULL && *(x->key)!=k){
    if(k < *(x->key))  x = x->left;
    else  x = x->right;
  }
  if (x==NULL) throw KeyError();
  return x;
}


//================================================
// insert k into the tree
//================================================
template<class KeyType>
void rbtree<KeyType> :: insert(KeyType* k) {
  // this->root = insert(k, this->root,NULL);
  Node<KeyType>* z = new Node<KeyType>(*k);
  Node<KeyType>* y = NULL;
  Node<KeyType>* x = root;
  while(x!=NULL){ //this goes down the tree to find the node's place
    y = x;
    if( *z < *x ){ //if smaller go left
      x = x->left;
    }
    else{ //else go right
      x = x->right;
    }
  }
  z->parent = y;
  if (y==NULL){ //if y is empty means the list was empty so the root needs to be z
    root = z;
  }
  else if( *z < *y){
    y->left = z;
  }
  else{
    y->right = z;
    z->left = NULL;
    z->right = NULL;
    z->isRed = true;
    rbInsertFixUp(z);
  }

}

template<class KeyType>
void rbtree<KeyType>:: rbInsertFixUp(Node<KeyType>* z){
  while (z->parent->isRed){
    if(z->parent->parent!= NULL){ //The grandparent and uncle need to exist in order for this to run
      //CASE 1

      if (z->parent->parent->left!= NULL && z->parent == z->parent->parent->left){ // if z's parent is a left child ERROr
        Node<KeyType>* y = z->parent->parent->right; //y is z's uncle
        if (y->isRed){
          z->parent->isRed = false;
          y->isRed = false;
          z->parent->parent->isRed = true;
          z = z->parent->parent;
          if(z->parent==NULL){
            break;
          }
        }
        else{
          if (z == z->parent->right){
            z = z->parent;
            leftRotation(z);
          }
          z->parent->isRed = false;
          z->parent->parent->isRed = true;
          rightRotation(z);
        }
      }
      //CASE 2
      else if (z->parent->parent->right!= NULL){      // is z's parent is a right child
        Node<KeyType>* y = z->parent->parent->left; //y is z's uncle
        if (y->isRed){
          z->parent->isRed = false;
          y->isRed = false;
          z->parent->parent->isRed = true;
          z = z->parent->parent;
          if(z->parent==NULL){
            break;
          }
        }
        else{
          if (z == z->parent->left){
            z = z->parent;
            rightRotation(z);
          }
          z->parent->isRed = false;
          z->parent->parent->isRed = true;
          leftRotation(z);
        }
      }
    }
    this->root->isRed = false;
  }
}

template<class KeyType>
void rbtree<KeyType>:: leftRotation(Node<KeyType>* n){
    Node<KeyType>* y = n->right;
    n->right = y->left;
    if (y->left != NULL) y->left->parent = n;
    y->parent = n->parent;
    if (n->parent == NULL) this->root = y;
    else if ( n == n->parent->left) n->parent->left = y;
    else n->parent->right = y;
    y->left = n;
    n->parent = y;
}

template<class KeyType>
void rbtree<KeyType>:: rightRotation(Node<KeyType>* y){
  Node<KeyType>* n = y->left;
  y->left = n->right;
  if (n->right != NULL) n->right->parent = y;
  n->parent = y->parent;
  if (y->parent == NULL) this->root = n;
  else if ( y == y->parent->left) y->parent->left = n;
  else y->parent->right = n;
  n->left = y;
  y->parent = n;
}



template<class KeyType>
KeyType* rbtree<KeyType>:: maximum() const{
  if (this->root==NULL) throw EmptyError();
  return subtreemax(this->root);
}                     // return the maximum item

template<class KeyType>
KeyType* rbtree<KeyType>:: subtreemax(Node<KeyType>* k)const{
  Node<KeyType> *x = k;
  while (x->right != NULL){
    x = x->right;
  }
  return (x->key);
}

template<class KeyType>
KeyType* rbtree<KeyType>::minimum()const{
  if (root==NULL) throw EmptyError();
  return ((subtreemin(this->root))->key);
}                     // return the minimum item

template<class KeyType>
Node<KeyType>* rbtree<KeyType>:: subtreemin(Node<KeyType>* k)const{
  Node<KeyType> *x = k;
  while (x->left != NULL){
    x = x->left;
  }
  return x;
}

template<class KeyType>
KeyType* rbtree<KeyType>::successor(const KeyType& k) const{
  Node<KeyType> *x = getn(k,this->root);
  if (x->right!=NULL){
    while (*(x->right->key) == *(x->key)) x = x->right;
    return ((subtreemin(x->right))->key);
  }
  Node<KeyType>* y = x->parent;
  while (y!=NULL && x == y->right){
    x = y;
    y = y->parent;
  }
  return (y->key);
}   // return the successor of k

template<class KeyType>
KeyType* rbtree<KeyType>::predecessor(const KeyType& k) const{
  Node<KeyType> *x = getn(k,this->root);
  if (x->left!=NULL) return subtreemax(x->left);
  Node<KeyType> *y = x->parent;
  while (y!=NULL && x == y->left){
    x = y;
    y = y->parent;
  }
  return (y->key);
} // return the predecessor of k




template<class KeyType>
std::string Node<KeyType>:: toString() const{
  if (this->key != NULL) {
    string x = "";
    try {
      throw (*key);
    }
    catch(string s){
      x= (*key);
      if (isRed) x+= ":r";
      else x+= ":b";
      return x;
    }catch(char c){
    x= (*key);
    if (isRed) x+= ":r";
    else x+= ":b";
    return x;
  }catch(...){
      ostringstream stream;
      stream << (*key);
      x = stream.str();
      if (isRed) x+= ":r";
      else x+= ":b";
      return x;
  }
 }
 return "";
}

template<class KeyType>
std::string rbtree<KeyType>:: toString(int order) const{
  string result = "[";
  if (this->root == NULL) {
    result +="]";
  }else{
    switch (order){
      case 1:
        result += inOrderString(this->root);
        result.pop_back();
        break;
      case 2:
        result += preOrderString(this->root);
        result.pop_back();
        break;
      case 3:
        result += postOrderString(this->root);
        result.pop_back();
        break;
    }
    result +="]";
  }
  return result;
}

template<class KeyType>
std::string rbtree<KeyType>:: inOrder() const{
  return toString(1);
}              // return string of items from an inorder traversal

template<class KeyType>
std::string rbtree<KeyType>:: inOrderString(const Node<KeyType>* x) const{
  string result="";
  if (x!=NULL){
      result = inOrderString(x->left) + (*x).toString()+","+inOrderString(x->right);
  }
  return result;
}

template<class KeyType>
std::string rbtree<KeyType>:: preOrder() const{
  return toString(2);
}             // return string of items from a preorder traversal


template<class KeyType>
std::string rbtree<KeyType>:: preOrderString(const Node<KeyType>* x) const{
  string result="";
  if (x!=NULL){
      result = (*x).toString() + "," + preOrderString(x->left) + preOrderString(x->right);
  }
  return result;
}             // return string of items from a preorder traversal


template<class KeyType>
std::string rbtree<KeyType>:: postOrder() const{
    return toString(3);
}

template<class KeyType>
std::string rbtree<KeyType>:: postOrderString(const Node<KeyType>* x) const{
  string result="";
  if (x!=NULL){
      result = postOrderString(x->left) + postOrderString(x->right) + (*x).toString() + ",";
  }
  return result;
}

#endif
