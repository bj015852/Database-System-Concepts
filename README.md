# Data-structures-and-Algorithms

Some very important data structures and algorithms for database systems, involving __indexing and hashing__, __query processing__ and __query optimization__.

Implementing them using C++ in a very simplified mode. However, there're a very complicated schema in real DBMS.

##1. Basic data structures

* Left-leaning red-black tree: A in-memory red-black tree, left-leaning model using recursive insertion mode, which is introduced in _Algorithms Fourth Edition_ by _Robert Sedgewick_ and _Kevin Wayne_.

* B Tree: A simple B tree data structure, witch is barely used in real DBMS. It is worth noting about its insertion and deletion algorithms.

* B+ Tree: A complete implementation of B+ tree demon, trying to simulate an ordered, dense indexing schema.

* Dynamic hash table: Dynamic hash structure.

###1.1 Left-leaning red-black tree

Actually, red-black tree is commonly used in in-memory databases rather than in relational databases, because of its binary tree property. Red-black tree is a kind of balanced search tree, which has a trade-off between the balance operation and cost, on account of maintaining a perfect balance for dynamic insertions or deletions is too expensive.

Here, we implement a left-learn red-black tree, which could corrospond to an unique format perfectly balanced 2-3 search tree. The properties of left-learn red-black tree are as following:

* Red links lean left.
* No node has two red links connected to it.
* The tree has perfect black balance : every path from the root to a null link has the same number of black links.

There is a 1-1 correspondence between red-black BSTs defined in this way and 2-3 trees.

```cpp
#include <iostream>
#include "RedBlackTree.hpp"

int main()
{
    RBTree<double, unsigned int> rbtree; // value type: double, key type: unsigned int.
    rbtree.put(2.991, 5);
    rbtree.put(2.334, 10);
    rbtree.put(3.112, 8);
    rbtree.put(-2.21, 13);
    double* pvalue;
    pvalue =  rbtree.get(13);
    if(pvalue)
        std::cout << *pvalue << std::endl;
    pvalue = rbtree.get(8);
    if(pvalue)
        std::cout << *pvalue << std::endl;
    return 0;
}
```




###1.2 B Tree

###1.3 B+ Tree


##2. Query Processing

* External merge sort: 
