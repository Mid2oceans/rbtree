#include<iostream>
#include<string>
#include "rbtree.cpp"

using namespace std;

int main()
{
    Node<int> a (12);
    Node<int> b (13);
    Node<int> c (3);
    Node<int> d (22);
    rbtree<Node<int> > tree1;
    tree1.insert(&a);
    tree1.insert(&b);
    tree1.insert(&c);
    tree1.insert(&d);

    
    return 0;
}

