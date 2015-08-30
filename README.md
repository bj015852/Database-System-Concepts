# Database system concepts and implementation

This article is focusing on database implementation, introducing some very important data structures, algorithms and techniques for database systems. The database system involves two main aspects: __Data Storage and Querying__ and __Transaction Management__. The former contains __indexing and hashing__, __query processing__ and __query optimization__, while the latter includes __transactions__, __concurrency control__, and etc.

All relative concepts are mainly inspired by Silberschatz [2010]. All the codes are implemented using C++ in a simplified and intuitive mode. However, that's a real complicated work in real DBMS.

## Data Storage and Querying

###1. indexing and hashing

* Left-leaning red-black tree: A in-memory red-black tree, left-leaning model using recursive insertion mode, which is introduced in Sedgewick [2011].

* B Tree: A simple B tree data structure, witch is barely used in real DBMS. It is worth noting about its insertion and deletion algorithms.

* B+ Tree: A complete implementation of B+ tree demon, trying to simulate an ordered, dense indexing schema.

* Dynamic hash table: Dynamic hash structure.

####1.1 Left-leaning red-black tree

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




####1.2 B Tree

####1.3 B+ Tree


###2. Query Processing

* External merge sort: 


## Transaction Management


## Bibliography

__[Sedgewick 2011]__    Robert Sedgewick, Kevin Wayne, _Algorithms Fourth Edition_ (2011)

__[Silberschatz 2010]__    Abraham Silberschatz, Henry F. Korth, S. Sudarshan, _Database System Concepts(Sixth Edition)_ (2010)

