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
    rbtree<int> tree1;
    tree1.insert(&a);
    tree1.insert(&b);
    tree1.insert(&c);
    tree1.insert(&d);


    return 0;
}
