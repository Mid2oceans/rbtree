#include<iostream>
#include<string>
#include "rbtree.cpp"
#include <vector>
#include "assert.h"

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
    tree1.insert(&e);
    tree1.insert(&f);
    tree1.insert(&g);
    tree1.insert(&h);
    // tree1.insert(&i);

    // vector<int> values = {a,b,c,d,e,f,g,h};
    // for(int x: values){
    //   Node<int>* x = tree1.getn(x);
    //   cout<<x->
    // }

    int* dd = &a;
    assert(*(tree1.get(a))==12);



    return 0;
}
