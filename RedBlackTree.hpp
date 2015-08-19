#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

// @Author Liu JD
// left-leaning red black tree.
// insert node method is in recursive.

#define RED true
#define BLACK false

template<typename T, typename KEY> class RBTree;

template<typename T, typename KEY> class RBTNode
{
    friend class RBTree<T, KEY>;
    protected:
        KEY key;
        T value;
        bool color;
        RBTNode<T, KEY> *pLeft;
        RBTNode<T, KEY> *pRight;
        RBTNode<T, KEY> *pParent;
        T *getvalue();

    public:
        RBTNode(T v, KEY k, bool c=BLACK): value(v), key(k), color(c) {pLeft = NULL; pRight = NULL; pParent = NULL;}
        void print() const;
};

template<typename T, typename KEY> void RBTNode<T, KEY>::print() const
{
    std::cout << key << ": " << value << ", ";
    if (color == RED)
        std::cout << "red";
    else
        std::cout << "black";
    std::cout << std::endl;
}

template<typename T, typename KEY> T *RBTNode<T, KEY>::getvalue()
{
    T *pvalue = &this->value;
    return pvalue;
}

template<typename T, typename KEY> class RBTree
{
    private:
        RBTNode<T, KEY> *pRoot;

    public:
        RBTree() { pRoot = NULL; }
        //~RBTree() { while(pRoot != NULL) deleteone(pRoot->key);  } // simply way to delete the entire tree.
        ~RBTree();

    private:
        bool isRed(RBTNode<T, KEY> *h) const;
        RBTNode<T, KEY> *RotateLeft(RBTNode<T, KEY> *);
        RBTNode<T, KEY> *RotateRight(RBTNode<T, KEY> *);
        void flipcolors(RBTNode<T, KEY> *);
        void regaincolors(RBTNode<T, KEY> *);
        RBTNode<T, KEY> *MoveRedLeft(RBTNode<T, KEY> *);
        RBTNode<T, KEY> *MoveRedRight(RBTNode<T, KEY> *);
        void setnull(RBTNode<T, KEY> *);

    public:
        // retrieve data from a given key
        T *get(KEY Key);
        RBTNode<T, KEY> *getmin();
    protected:
        RBTNode<T, KEY> *get(RBTNode<T, KEY> *h, KEY Key);
        RBTNode<T, KEY> *getmin(RBTNode<T, KEY> *h);

    public:
        // insert a new node given a value and a key.
        // Key should be comparable and value should has a copy constructor and operator =.
        void put(T Value, KEY Key);
    protected:
        RBTNode<T, KEY> *put(RBTNode<T, KEY> *h, T Value,  KEY Key);

    public:
        // delete the minimum or maximum value.
        void deletemin();
        void deletemax();
        // delete a specified node.
        void deleteone(KEY Key);
    protected:
        RBTNode<T, KEY> *deletemin(RBTNode<T, KEY> *h);
        RBTNode<T, KEY> *deletemax(RBTNode<T, KEY> *h);
        RBTNode<T, KEY> *deleteone(RBTNode<T, KEY> *h, KEY Key);

    public:
        // Traverse the RBTree
        void Inorder_Tree_Walk();
    protected:
        void Inorder_Tree_Walk(RBTNode<T, KEY> *p);
};

template<typename T, typename KEY> RBTree<T, KEY>::~RBTree()
{
    setnull(pRoot);
}

template<typename T, typename KEY> void RBTree<T, KEY>::setnull(RBTNode<T, KEY> *h)
{
    if (h == NULL)
    {
        return;
    }
    setnull(h->pLeft);
    setnull(h->pRight);
    {
        //std::cout << "delete " << h->key << std::endl;
        delete h;
        h = NULL;
    }
}

template<typename T, typename KEY> bool RBTree<T, KEY>::isRed(RBTNode<T, KEY> *h) const
{
    if ( h != NULL)
        return h->color;
    return BLACK;
}


template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::RotateLeft(RBTNode<T, KEY> *h)
{
    RBTNode<T, KEY> *x = h->pRight;
    h->pRight = x->pLeft;
    x->pLeft = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::RotateRight(RBTNode<T, KEY> *h)
{
    RBTNode<T, KEY> *x = h->pLeft;
    h->pLeft = x->pRight;
    x->pRight = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

template<typename T, typename KEY> void RBTree<T, KEY>::flipcolors(RBTNode<T, KEY> *h)
{
    h->color = RED;
    h->pLeft->color = BLACK;
    h->pRight->color = BLACK;
}

template<typename T, typename KEY> void RBTree<T, KEY>::regaincolors(RBTNode<T, KEY> *h)
{
    h->color = BLACK;
    if (h->pLeft)
        h->pLeft->color = RED;
    if (h->pRight)
        h->pRight->color = RED;
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::MoveRedLeft(RBTNode<T, KEY> *h)
{
    regaincolors(h);
    if (isRed(h->pRight->pLeft))
    {
        h->pRight = RotateRight(h->pRight);
        h = RotateLeft(h);
        flipcolors(h);
    }
    return h;
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::MoveRedRight(RBTNode<T, KEY> *h)
{
    regaincolors(h);
    if (isRed(h->pLeft->pLeft))
    {
        h = RotateRight(h);
        flipcolors(h);
    }
    return h;
}


template<typename T, typename KEY> void RBTree<T, KEY>::put(T Value, KEY Key)
{
    pRoot = put(pRoot, Value, Key);
    pRoot->color = BLACK;
    //std::cout << "Insert new node: " << Key << " Value:" << Value << ", Root: " << pRoot->key << std::endl;
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::put(RBTNode<T, KEY> *h, T Value, KEY Key)
{
    if (h == NULL)
    {
        h = new RBTNode<T, KEY>(Value, Key, RED);
        return h;
    }
    if (h->key > Key) h->pLeft = put(h->pLeft, Value, Key);
    else if (h->key < Key) h->pRight = put(h->pRight, Value, Key);
    else h->value = Value;

    if (!isRed(h->pLeft) && isRed(h->pRight)) { h = RotateLeft(h); }
    if (isRed(h->pLeft) && isRed(h->pLeft->pLeft)) { h=RotateRight(h); }
    if (isRed(h->pLeft) && isRed(h->pRight)) { flipcolors(h); }

    return h;
}

template<typename T, typename KEY> void RBTree<T, KEY>::deletemin()
{
    if (pRoot) // check if the tree is empty.
    {
        if (!isRed(pRoot->pLeft))   // Root contains only one node. Both its left and right child are black.
            pRoot->color = RED;
        pRoot = deletemin(pRoot);
        if (pRoot)
            pRoot->color = BLACK;
    }
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::deletemin(RBTNode<T, KEY> *h)
{
    if (h->pLeft == NULL)
    {
        // be careful here hasn't check if the h is empty.
        //std::cout << "Delete min " << h->key << std::endl;
        delete h;
        return NULL;
    }
    if (!isRed(h->pLeft) && !isRed(h->pLeft->pLeft))
        h = MoveRedLeft(h);
    h->pLeft = deletemin(h->pLeft);
    if (isRed(h->pRight))
        h = RotateLeft(h);
    return h;
}

template<typename T, typename KEY> void RBTree<T, KEY>::deletemax()
{
    if (pRoot) // check if the tree is empty.
    {
        if (!isRed(pRoot->pLeft))
            pRoot->color = RED;
        pRoot = deletemax(pRoot);
        if (pRoot)
            pRoot->color = BLACK;
    }
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::deletemax(RBTNode<T, KEY> *h)
{
    if (isRed(h->pLeft))
        h = RotateRight(h);
    if (h->pRight == NULL)
    {
        // be careful here hasn't check if the h is empty.
        //std::cout << "Delete max " << h->key << std::endl;
        delete h;
        return NULL;
    }
    if (!isRed(h->pRight) && !isRed(h->pRight->pLeft))
        h = MoveRedRight(h);
    h->pRight = deletemax(h->pRight);
    if (isRed(h->pRight))
        h = RotateLeft(h);
    return h;
}

template<typename T, typename KEY> void RBTree<T, KEY>::deleteone(KEY Key)
{
    if (pRoot)
    {
        //std::cout << "Deleting: " << Key << std::endl;
        if (!isRed(pRoot->pLeft))
            pRoot->color = RED;
        pRoot = deleteone(pRoot, Key);
        if (pRoot)
            pRoot->color = BLACK;
    }
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::deleteone(RBTNode<T, KEY> *h, KEY Key)
{
    // Delete a node.
    // However will be not sure Key exists in the tree. Check if the Key exists before deleting.
    if (Key < h->key)
    {
        if (!isRed(h->pLeft) && !isRed(h->pLeft->pLeft))
            h = MoveRedLeft(h);
        h->pLeft = deleteone(h->pLeft, Key);
    }
    else{
        if (isRed(h->pLeft))
            h = RotateRight(h);
        if ((Key == h->key) && !(h->pRight) )
        {
            //std::cout << "Delete one specified node: " << h->key << ", value: " << h->value << std::endl;
            delete h;
            return NULL;
        }
        if (!isRed(h->pRight) && !isRed(h->pRight->pLeft))
            h = MoveRedRight(h);
        if (Key == h->key)
        {
            //std::cout << "To delete " << h->key << ", delete subtree's min node" << std::endl;
            RBTNode<T, KEY> *temp = getmin(h->pRight);
            h->value = temp->value;
            h->key = temp->key;
            h->pRight = deletemin(h->pRight);
        }
        else
            h->pRight = deleteone(h->pRight, Key);
    }
    if (isRed(h->pRight))
        h = RotateLeft(h);
    return h;
}

template<typename T, typename KEY> T *RBTree<T, KEY>::get(KEY Key)
{
    if (pRoot)
    {
        RBTNode<T, KEY> *pNode = get(pRoot, Key);
        return pNode->getvalue();
    }
    else return NULL;
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::get(RBTNode<T, KEY> *h, KEY Key)
{
    if ((h == NULL) || (Key == h->key) )
        return h;
    if (Key < h->key)
        return get(h->pLeft, Key);
    else
        return get(h->pRight, Key);
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::getmin()
{
    if (pRoot)
        return getmin(pRoot);
    else
        return NULL;
}

template<typename T, typename KEY> RBTNode<T, KEY> *RBTree<T, KEY>::getmin(RBTNode<T, KEY> *h)
{
    if (h->pLeft)
        return getmin(h->pLeft);
    else return h;
}

template<typename T, typename KEY> void RBTree<T, KEY>::Inorder_Tree_Walk()
{
    Inorder_Tree_Walk(pRoot);
    if (pRoot)
    {
        std::cout << "Root: ";
        pRoot->print();
    }
    else
        std::cout << "RBTree Empty!" << std::endl;
}

template<typename T, typename KEY> void RBTree<T, KEY>::Inorder_Tree_Walk(RBTNode<T, KEY> *p)
{
    if (p != NULL)
    {
        Inorder_Tree_Walk(p->pLeft);
        p->print();
        Inorder_Tree_Walk(p->pRight);
    }
}


#endif
