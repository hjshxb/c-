#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <cassert>

template <typename T>
struct BSNode{
    T data;
    BSNode<T> *lchild;
    BSNode<T> *rchild;
    
    BSNode(const T value)
    {
        data = value;
        lchild = nullptr;
        rchild = nullptr;
    }
};


template <typename T>
class Bstree
{
    typedef BSNode<T> Node;
private:
    BSNode<T> *root;
public:
    Bstree():root(nullptr) {}
    Bstree(Bstree<T> &bstree);   //浅拷贝
    ~Bstree();
    bool isempty() const
     {return root == nullptr;}
    void insert(T key);  // 二叉排序数插入(外部接口)
    void inorder();  // 中序遍历(外部接口)
    int treehigh();  // 获取树的高度
    int countleaf(); // 获取叶子节点个数
    Bstree<T>& clone(); // 拷贝二叉树
    BSNode<T>* find(T key);  // 查找
    T findmax();                 // 找到最大值
    T findmin();                 // 找到最小值
    void remove(T key);    // 删除
    template <typename U>
    friend std::ostream& operator<<(std::ostream &os, Bstree<U> &bstree);
    template <typename U>
    friend std::istream& operator>>(std::istream &in, Bstree<U> &bstree);

protected:
    BSNode<T> *_insert(Node *node, T key);
    void _inorder(Node *node);
    int _treehigh(Node *node);
    int _countleaf(Node *node);
    void _destroy(Node * &node);
    BSNode<T>* _clone(Node *node);
    BSNode<T>* _find(Node *node, T key);
    T _findmax(Node *node);
    T _findmin(Node *node);
    BSNode<T>* _remove(Node *node, T key);
};


/*
@brief:浅拷贝函数
@param bstree 拷贝对象
*/
template <typename T>
Bstree<T>::Bstree(Bstree<T> &bstree)
{
    *this->root = bstree.root;
}


/*
@brief: 递归实现二叉排序数的插入
@param: key 插入的值
*/
template <typename T>
void Bstree<T>::insert(T key)
{
    root =  _insert(root, key);
}

// 内部功能实现
template <typename T>
BSNode<T>* Bstree<T>::_insert(Node *node, T key)
{
    if (node == nullptr)
    {
        node = new BSNode<T>(key);
        node->lchild = nullptr;
        node->rchild = nullptr;
    }
    else
    {
        if (key < node->data)
            node->lchild = _insert(node->lchild, key);  //小的在左子树
        else
            node->rchild = _insert(node->rchild, key);  //大的在右子树
        
    }
    
    return node;
} 


/*
@brief: 实现中序遍历
*/
template <typename T>
void Bstree<T>::inorder()
{
    _inorder(root);
}

template <typename T>
void Bstree<T>::_inorder(Node *node)
{
    if (node == nullptr)
        return;
    else
    {
        _inorder(node->lchild);   // 先输出左子树
        std::cout << node->data <<"\t";
        _inorder(node->rchild);
    }
    
}


/*
@breif: 获取树的高度
*/
template <typename T>
int Bstree<T>::treehigh()
{
    return _treehigh(root);
}

// 内部实现
template <typename T>
int Bstree<T>::_treehigh(Node *node)
{
    if (node == nullptr)
        return 0;
    else
    {
        int lhigh = _treehigh(node->lchild);
        int rhigh = _treehigh(node->rchild);
        if (lhigh > rhigh)
            return lhigh + 1;
        else 
            return rhigh + 1;
    }
    
}


/*
@brief: 获取叶子数
*/
template <typename T>
int Bstree<T>::countleaf()
{
    return _countleaf(root);
}

//内部实现
template <typename T>
int Bstree<T>::_countleaf(Node *node)
{
    if (node == nullptr)
        return 0;
    else if (node->lchild == nullptr && node->rchild == nullptr)
    {
        return 1;
    }
    return _countleaf(node->lchild) + _countleaf(node->rchild);
}


/*
@brief:拷贝二叉树, 深拷贝，需要申请新的内存存放
*/
template <typename T>
Bstree<T>& Bstree<T>::clone()
{
    Bstree<T>  *bstree = new Bstree<T>;
    if(root == nullptr)
        return *bstree;
    else
    {
        bstree->root = _clone(root);
        return *bstree;
    }
}
//内部接口
template <typename T>
BSNode<T>* Bstree<T>::_clone(Node *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        BSNode<T> *nd = new BSNode<T>(node->data);
        nd->lchild = _clone(node->lchild);
        nd->rchild = _clone(node->rchild);
        return nd;
    }
    
} 


/*
@brief:查找值
@param key 要查找的值
*/
template <typename T>
BSNode<T>* Bstree<T>::find(T key)
{
    return _find(root, key);
}

//内部实现
template <typename T>
BSNode<T>* Bstree<T>::_find(Node *node, T key)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (key < node->data)
        return _find(node->lchild, key);
    else if (key > node->data)
        return _find(node->rchild, key);
    else
        return node;
}


/*
@brief: 返回最大值
*/
template <typename T>
T Bstree<T>:: findmax()
{
    return _findmax(root);
}

//内部实现
template <typename T>
T Bstree<T>:: _findmax(Node *node)
{
    assert(node != nullptr);
    if (node->rchild == nullptr)
        return node->data;
    else 
        return _findmax(node->rchild);
}


/*
@brief: 返回最大值
*/
template <typename T>
T Bstree<T>:: findmin()
{
    return _findmin(root);
}

//内部实现
template <typename T>
T Bstree<T>:: _findmin(Node *node)
{
    assert(node != nullptr);
    if (node->lchild == nullptr)
        return node->data;
    else 
        return _findmin(node->lchild);
}


/*
@ brief: 删除值
@ param: key 要删除的值
*/
template <typename T> 
void Bstree<T>::remove(T key)
{
    root = _remove(root, key);
}

//内部实现
template <typename T>
BSNode<T>* Bstree<T>::_remove(Node *node, T key)
{
    assert(node != nullptr);
    if (key < node->data)  
        node->lchild = _remove(node->lchild, key);
    else if (key > node->data) 
        node->rchild = _remove(node->rchild, key);
    else
    {
        // 要删除的值有两个孩子， 找其右孩子的最小值替代
        if (node->lchild && node->rchild)
        {
            T right_min = _findmin(node->rchild);
            node->data = right_min;
            node->rchild = _remove(node->rchild, node->data);
        }
        else
        {
            // 一个或无孩子
            BSNode<T> * TmpNode = nullptr;
            TmpNode = node;
            if (node->lchild == nullptr)
                node = node->rchild;
            else if (node->rchild == nullptr)
                node = node->lchild;
            delete TmpNode;
        }
    }
    return node;
}


/*
@ brief:重载<<函数
*/
template <typename U>
std::ostream& operator<<(std::ostream &os, Bstree<U> &bstree)
{
    bstree.inorder();
    os << std::endl;
    return os;
}


/*
@brief:重载>>函数
*/
template <typename U>
std::istream& operator>>(std::istream &in, Bstree<U> &bstree)
{
    U key;
    in >> key;
    bstree.insert(key);
    return in;
}


/*
@brief:析构函数 实现内存回收
*/
template <typename T>
Bstree<T>::~Bstree()
{
    _destroy(root);
} 

//内部实现
template <typename T>
void Bstree<T>::_destroy(Node * &node)  //delete指针时需要使用指针的引用
{
    if (node != nullptr)
    {
        if (node->lchild != nullptr)
            _destroy(node->lchild);
        if (node->rchild != nullptr)
            _destroy(node->rchild);
        delete node;
        node = nullptr;
    }
}

#endif