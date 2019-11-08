#include "RBT.h"
#include <sstream> // Used in toString to convert numbers to strings
#include <string>
#include <stack>
using namespace std;

template <class KeyType>
RBT<KeyType>::RBT(){
  root = NULL;

}

template <class KeyType>
RBT<KeyType>::~RBT(){
  del(root);
  root = NULL;
}

template <class KeyType>
RBT<KeyType>::RBT(const RBT<KeyType>& tree){
  root = NULL;

  copy(tree.getRoot());

}

template <class KeyType>
void RBT<KeyType>::copy(Node<KeyType>* x){

        if(x!=NULL){
        KeyType y = x->k;
        KeyType* z = &y;

        this->insert(z);
        copy(x->left);
        copy(x->right);
        }
}

template <class KeyType>
void RBT<KeyType>::operator=(const RBT& tree){

  del(root);
  root = NULL;
  copy(tree.getRoot());

}
template <class KeyType>
void RBT<KeyType>::del(Node<KeyType>* x){

        if(x!=NULL){
            del(x->left);
            del(x->right);
            delete x;
        }

}

template <class KeyType>
Node<KeyType>* RBT<KeyType>::getRoot() const //Same as KeyType* minimum() const; but instead of returning the keytype it return the node
{
	return root;
}

template <class KeyType>
bool RBT<KeyType>::empty() const{
  if(root == NULL){
    return true;
  }
  else{
    return false;
  }

}

template <class KeyType>
void RBT<KeyType>::insert(KeyType *k){
  Node<KeyType>* temp = new Node<KeyType>(*k);
  Node<KeyType>* x;
  Node<KeyType>* y;



  temp->right =NULL;
  temp->left =NULL;
  temp->parent=NULL;
  temp->k=*k;

  x = root;
  y = NULL;

  while(x!=NULL){
    y=x;

    if(*k<y->k){
      x=x->left;
    }
    else{
      x=x->right;
    }

  }
  temp->parent = y;

  if(y==NULL){ //if it is the root
    root = temp;
    root.isRed ==false;
  }
  else if(temp->k < y->k){ //if should be left 
    y->left=temp;
    y->left->parent = y;
    Node<KeyType>* p = y;
    //Here I am trying to create a loop to re color if color of x’s parent is not BLACK and x is not root.
  //   while(){
  //     if(isUncleRed(y)){
  //       (y->parent).isRed =false;
  //       //Change color of uncle to black
  //       (y->parent->parent).isRed=true;
  //     }

  //   }

  }
  else{ //if should be right 
    y->right=temp;
    y->right->parent = y;
  }

}

template<class KeyType>
Node<KeyType>* RBT<KeyType>::get(const KeyType& k) const{


  Node<KeyType>* x;
  x = root;
  while(x!=NULL && k!=x->k){

    if(k < x->k){
      x=x->left;
    }
    else {
      x=x->right;
    }
  }
  if(x==NULL){
    cout<<"Error No Key"<<endl;
    throw KeyError();
  }
  return x;
}

template<class KeyType>
KeyType* RBT<KeyType>::get2(const KeyType& k) const{


  Node<KeyType>* x;
  x = root;
  if(x==NULL){
    cout<<"Error empty"<<endl;
    throw EmptyError();
  }
  while(x!=NULL && k!=x->k){

    if(k < x->k){
      x=x->left;
    }
    else {
      x=x->right;
    }
  }
  if(k!=x->k){
    cout<<"Error No Key"<<endl;
    throw KeyError();
  }

  KeyType h = x->k;
  KeyType* y = &h;
  return y;
}

template<class KeyType>
KeyType*  RBT<KeyType>:: minimum(){
  KeyType x;
  KeyType* y;
  Node<KeyType>* c = root;

  while(c->left!=NULL){
    c=c->left;
  }
  if(c==NULL){
    cout<<"Error Empty"<<endl;
    throw EmptyError();
  }
  x = c->k;
  y = &x;

  return y;
}


template<class KeyType>
KeyType*  RBT<KeyType>:: maximum(){
  KeyType x;
  KeyType* y;
  Node<KeyType>* c = root;

  while(c->right!=NULL){
    c=c->right;
  }
  if(c==NULL){
    cout<<"Error Empty"<<endl;
    throw EmptyError();
  }
  x = c->k;
  y = &x;

  return y;
}

template<typename KeyType>
void RBT<KeyType>::Transplant(Node<KeyType>* u, Node<KeyType>* v){

    if(u->parent==NULL ){
        root=v;
    }
    else if(u==u->parent->left){
        u->parent->left=v;
    }
    else
    {
        u->parent->right=v;
    }
    if(v!=NULL){
        v->parent=u->parent;
    }

}


template<typename KeyType>
void RBT<KeyType>::remove(const KeyType& k)
{
    Node<KeyType>* z;
    Node<KeyType>* y;
    z=get(k);
    if(z->left==NULL){
        Transplant(z,z->right);
    }
    else if(z->right==NULL){
        Transplant(z,z->left);

    }
    else
    {
        y=findMinimum(z->right);
        if(y->parent!=z){
            Transplant(y,y->right);
            y->right=z->right;
        }
    }


}



template<typename KeyType>
Node<KeyType>* RBT<KeyType>::findMinimum(Node<KeyType>* root) const //Same as KeyType* minimum() const; but instead of returning the keytype it return the node
{
    if(root==NULL){
      cout<<"Error Empty"<<endl;
      throw EmptyError();
    }
	while (root->left)
		root = root->left;

	return root;
}
template<typename KeyType>
Node<KeyType>* RBT<KeyType>::findMaximum(Node<KeyType>* root) const //Same as KeyType* maximum() const; but instead of returning the keytype it return the node
{
    if(root==NULL){
      cout<<"Error Empty"<<endl;
      throw EmptyError();
    }
	while (root->right)
		root = root->right;

	return root;
}

template <class KeyType>
KeyType* RBT<KeyType>::successor(const KeyType& k) const
{
    KeyType s;
    KeyType* z;


    Node<KeyType>* x;
    Node<KeyType>* y;
    x=get(k);
    if (x->right!=NULL){
        y=findMinimum(x->right);
        s= y->k;
        z= &s;
        return z;
    }
    y=x->parent;
    while(y==NULL && x==y->right){
        x=y;
        y=y->parent;
    }
    s= y->k;
    z= &s;
    return z;



}

template <class KeyType>
KeyType* RBT<KeyType>::predecessor(const KeyType& k) const
{
    KeyType s;
    KeyType* z;


    Node<KeyType>* x;
    Node<KeyType>* y;
    x=get(k);
    if (x->left!=NULL){
        y=findMaximum(x->left);
        s= y->k;
        z= &s;
        return z;
    }
    y=x->parent;
    while(y==NULL && x==y->right){
        x=y;
        y=y->parent;
    }
    s= y->k;
    z= &s;
    return z;
}

template <class KeyType>
string RBT<KeyType>::inOrder(){
  s="";

    string res= inOrder2(root);

    return res;
}

template <class KeyType>
string RBT<KeyType>::inOrder2(Node<KeyType> * x)
{

    if(x!=NULL){

         inOrder2(x->left);
         s+=to_string(x->k)+" ";
         inOrder2(x->right);

     }
     return s;

}


template <class KeyType>
string RBT<KeyType>::preOrder()
{

   string res= preOrder2(root);
   return res;



}

template <class KeyType>
string RBT<KeyType>::preOrder2(Node<KeyType> * x)
{
    if(x!=NULL){

         s+=to_string(x->k)+" ";
         preOrder2(x->left);
         preOrder2(x->right);

     }

    return s;
}



template <class KeyType>
string RBT<KeyType>::postOrder()
{

   string res = postOrder2(root);
   return res;

}


template <class KeyType>
string RBT<KeyType>::postOrder2(Node<KeyType> * x)
{
    if(x!=NULL){

         postOrder2(x->left);
         postOrder2(x->right);
         s+=to_string(x->k)+" ";

     }

    return s;
}
template <class KeyType>
bool RBT<KeyType>:: isUncleRed(Node<KeyType>* n){ //need to fix to figure out if current (parent?) is a right or left child
  if((n->parent->parent->right).isRed){ // uncle on right side
    return true;
  }
  if((n->parent->parent->left).isRed){ //uncle on left side
    return true;
  }
  return false;

}
