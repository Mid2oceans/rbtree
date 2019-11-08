#include<iostream>
#include<string>
#include "rbtree.cpp"

using namespace std;

int main()
{
    int a = 12;
    int b = 13;
    int c = 3;
    int d = 22;
    int e = 5;
    int f = 4;
    int g = 1;
    int h = 15;
    int i = 18;
    rbtree<int> tree1;
    tree1.insert(&a);
    tree1.insert(&b);
    tree1.insert(&c);
    tree1.insert(&d);
    // tree1.insert(&e);
    // tree1.insert(&f);
    // tree1.insert(&g);
    // tree1.insert(&h);
    // tree1.insert(&i);


    return 0;
}
