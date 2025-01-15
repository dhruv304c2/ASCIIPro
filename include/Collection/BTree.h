#ifndef BTREE_H
#define BTREE_H

#include <functional>
template <typename T>
class BTreeNode{
public:
    BTreeNode<T>(T* value){
        item = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    ~BTreeNode<T>(){
        delete item;
        delete left;
        delete right;
    }

    T* item;
    BTreeNode<T>* left;
    BTreeNode<T>* right;
    BTreeNode<T>* parent;

    bool canAddLeft(){
        return left == nullptr;
    }

    bool canAddRight(){
        return right == nullptr;
    }

    bool canAdd(){
        return canAddLeft() || canAddRight();
    }

    void addLeft(BTreeNode<T>* node){
        left = node;
        node->parent = this;
    }

    void addRight(BTreeNode<T>* node){
        right = node;
        node->parent = this;
    }

    void add(BTreeNode<T>* item){
        if(canAddLeft()){
            addLeft(item);
            return;
        }
        if(canAddRight()){
            addRight(item);
            return;
        }
    }

    void forEach(std::function<void(T*)> action){
        action(item);
        if(left != nullptr) left->forEach(action);
        if(right != nullptr) right->forEach(action);
    }

    void forEachRight(std::function<void(T*)> action){
        action(item);
        if(right != nullptr) right->forEachRight(action);
    }

    void forEachLeft(std::function<void(T*)> action){
        action(item);
        if(left != nullptr) left->forEachLeft(action);
    }
};

template <typename T>
class BTree {
public:
    BTree<T> (){
        _root = nullptr;
    }

    BTree<T> (T* item) {
        addFirst(item);
    }

    ~BTree<T>(){
        delete _root;
    }

    BTreeNode<T>* root(){
        return _root;
    }

    BTreeNode<T>* rightMostNode(){
        BTreeNode<T>* it = _root;
        while(it->right != nullptr){
            it = it->right;
        }
        return it;
    }

    BTreeNode<T>* leftMostNode(){
        BTreeNode<T>* it = _root;
        while(it->left != nullptr){
            it = it->left;
        }
        return it;

    }

    void addRightMost(T* item){
        auto node = BTreeNode<T>(item);
        rightMostNode()->addRight(node);
    }

    void addLeftMost(T* item){
        auto node = BTreeNode<T>(item);
        leftMostNode()->addLeft(node);
    } 

private:
    BTreeNode<T>* _root;
    void addFirst(T* item){
        auto node = new BTreeNode<T>(item);
        _root = node;
    }
};

#endif
