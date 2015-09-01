#ifndef __BTREE_H
#define __BTREE_H
//@Author: Liu JD
// Created in 2015

// Basic B Tree structre.
// We only illustrate the insert and delete algorithm here. So the node structure is extremely simplified, represented by an array data and children.

// t = BRANCHING_FACTOR/2. Here the Branching Factor is even.
// 1. Every node other than the root must have at least t-1 keys. Every internal node other than the root thus has at least t children. If the tree is nonempty, the root must have at least one key.
// 2. Every node may contain at most 2t-1 keys. Therefore, an internal node may have at most 2t children.
// Now, the minimum degree t of the B-tree is 4.
#define BRANCHING_FACTOR 8

template<typename T, typename KEY>  struct DATA{
        T value;
        KEY key;
};

template<typename T, typename KEY> class BTree;

template<typename T, typename KEY> class BTNode
{
    friend class BTree<T, KEY>;
    protected:
        int n;                                                             // the number of keys currently stored in the node, equels to BRANCHING_FACTOR-1
        DATA<T, KEY> data[BRANCHING_FACTOR - 1];            // the keys and data themselves, data[0].key, x[1].key, ..., stored in nondecreasing order, so that data[0].key <= data[1].key <= ... <= data[n].key
        BTNode *children[BRANCHING_FACTOR];                 // pointers to its children
        bool leaf;                                                                      // a boolean value that is TRUE if this is a leaf and FALSE if this is an internal node
    public:
        BTNode():  n(BRANCHING_FACTOR/2 - 1), leaf(false) {};
};


template<typename T, typename KEY> class BTree
{
    private:
        BTNode<T, KEY> *pRoot;

    public:
        // Recursive insertion:
        void BTSplit(BTNode<T, KEY> *, int i);                                              // Split the node's ind child.
        void BTInsert(T Value, KEY Key);                                                       // Insert a data into B Tree from root.
        void BTInsertNonFull(BTNode<T, KEY> *, T Value, KEY Key);         // Recursive insertion operation on a non-full node. If the child which is going to be inserted of this node is full , split the child than insert.

    public:
        // Retrieve data.
        T *BTSearch (KEY);
        DATA<T, KEY> *BTSearch (BTNode<T, KEY> *, KEY);

    public:
        BTree() ;
        ~BTree() {};

};

template<typename T, typename KEY> BTree<T, KEY>::BTree()
{
    pRoot = new BTNode<T, KEY>();     // Allocate a new node as root node.
    pRoot->leaf = true;                                                       // Initialized as a leaf node.
    pRoot->n = 0;                                                                 // Root node hasn't key and data when being initialized.
}

// Make sure that x->children[i] is a full node.
// Then split  x->children[i] into two node. The left node is y and the right is z.
// It is worth noting when x->n == 0  and x has only one child.
template<typename T, typename KEY> void BTree<T, KEY>::BTSplit(BTNode<T, KEY> *x, int i)
{
    int t = BRANCHING_FACTOR/2;
    BTNode<T, KEY> *z = new BTNode<T, KEY>();
    BTNode<T, KEY> *y = x->children[i];
    z->leaf = y->leaf;
    z->n = t -1;                                                  // Must having at least t-1 keys.
    for ( int j=0; j< t-1; ++j)            // Copy the second half of y.key to z.key, but reserve the middle, that is y->data[t-1].
        z->data[j] = y->data[j+t];
    if (!y->leaf)
    {
        for( int j=0; j<t; ++j)
            z->children[j] = y->children[j+t];      //  Copy the second half of y.chidren to z.children.
    }
    y->n = t-1;                                                 // Both y and z have the same size of keys and datas.
    for ( int j=x->n; j>=i; --j)            // Second half of x.children right shift.
        x->children[j+1] = x->children[j];
    x->children[i+1] = z;                                   // Add z to x's children.
    for ( int j=x->n-1; j>=i-1; --j)      // Second half of x.data right shift.
        x->data[j+1] = x->data[j];
    x->data[i] = y->data[t-1];                            // Add the middle data to  x.
    ++(x->n);
}

template<typename T, typename KEY> void BTree<T, KEY>::BTInsert(T Value, KEY Key)
{
    BTNode<T, KEY> *r = pRoot;                      // Save the root pointer.
    if(pRoot->n == BRANCHING_FACTOR-1)
    {
        BTNode<T, KEY> *s = new BTNode<T, KEY>();   // If the root node is full, allocate a new root node and split the old one as two children of the new root.
        pRoot = s;
        s->leaf = false;
        s->n = 0;
        s->children[0] = r;
        BTSplit(s, 0);
        BTInsertNonFull(s, Value, Key);
    }
    else
    {
        BTInsertNonFull(r, Value, Key);                        // If the root isn't full, traverse down to insert.
    }
}

template<typename T, typename KEY> void BTree<T, KEY>::BTInsertNonFull(BTNode<T, KEY> *x,  T Value, KEY Key)
{
    int i = x->n - 1;
    if (x->leaf)
    {
        while(i>=0 and Key<x->data[i].key)
        {
            x->data[i+1] = x->data[i];                   // We will detect if this current node is full in the former recursion. So here we can guarantee the current node won't be full.
            --i;
        }
        x->data[i+1].key = Key;                         // Insert the new data and increase the data number.
        x->data[i+1].value = Value;
        ++ (x->n);
    }
    else
    {
        while(i>=0 and Key<x->data[i].key)                              // Detect the child of the current node if it is full.
            --i;
        ++i;
        if (x->children[i]->n == BRANCHING_FACTOR-1)         // The child if full.
        {
            BTSplit(x->children[i], i);                                           // Spliting.
            if (Key > x->data[i].key)                                             // Then comparing the new key.
                ++i;
        }
        BTInsertNonFull(x->children[i], Value, Key);                // Traverse down the tree for insertion.
    }
}


template<typename T, typename KEY> T *BTree<T, KEY>::BTSearch(KEY Key)
{
    DATA<T, KEY> *pData;
    if (pRoot)                                      // Actually  no need to judge.
    {
        pData = BTSearch(pRoot, Key);
        return &pData->value;
    }
    return NULL;
}

template<typename T, typename KEY> DATA<T, KEY> *BTree<T, KEY>::BTSearch(BTNode<T, KEY> *pNode, KEY Key)
{
    int i = 0;
    while( (i < pNode->n) && (pNode->data[i].key < Key) )   // Sequential searching.
        ++i;
    if ( (i< pNode->n) && ( pNode->data[i].key == Key ))        // The proper key is found.
        return &pNode->data[i];
    else if (pNode->leaf == true)                                       // Searching to the leaf and still can' t find the key, return nil.
        return NULL;
    return BTSearch(pNode->children[i], Key);             // Hasn't find the key but this is the internal node.
}








#endif
