#ifndef _BTREE_H_
#define _BTREE_H_

#include <cstdint>
#include <cstddef>
#include <utility>
#include <iostream>

template<typename VALUE, size_t N>
struct BTreeNode{
    typedef BTreeNode<VALUE,N> Node;
    VALUE  valueField_[N];
    Node*  subs_[N+1];
    Node*  parent_;
    size_t size_;
    BTreeNode()
        :size_(0)
        ,parent_(nullptr)
    {
        for(size_t i = 0; i < N; ++i) {
            valueField_[i] = VALUE();
            subs_[i] = nullptr;
        }
    }
};

template<typename VALUE>
struct KeyOfValue__{
    VALUE operator()(const VALUE& value) {
        return value;
    }
};

template<typename KEY, typename VALUE, typename KeyOfValue = KeyOfValue__<VALUE>, size_t N = 3>
class BTree{
    typedef BTreeNode<VALUE, N> Node;
public:
    BTree()
        :root_(nullptr) 
    {
    }

    std::pair<Node*, int32_t> Find(const KEY& key) {
        Node* pcur = root_;
        Node* pParent = nullptr;
        while(pcur) {
            size_t i = 0;
            for(; i < pcur->size_; ++i) {
                if(key < KeyOfValue()(pcur->valueField_[i]))
                    break;
                else if(key == KeyOfValue()(pcur->valueField_[i]))
                    return std::make_pair(pcur, i);
            }

            pParent = pcur;
            pcur = pcur->subs_[i];
        }

        return std::make_pair(pParent, -1);
    }

    bool Insert(const VALUE& value) {
        //case 1:空树，直接插入
        if(nullptr == root_) {
            root_ = new Node();
            root_->valueField_[root_->size_] = value;
            ++root_->size_;
            ++size_;
            return true;
        }

        //case 2.1:非空，先查找当前值是否存在
        std::pair<Node*, int32_t> ret = Find(KeyOfValue()(value));
        if(ret.second != -1) 
            return false;

        //没找到则进行插入
        Node* pcur = ret.first;
        insertValue(pcur, value, nullptr);

        //如果饱和则进行分裂
        while(pcur->size_ >= N) {
            int mid = pcur->size_ / 2;
            Node* newNode = new Node;

            size_t i = mid + 1, j = 0;
            size_t curSize = pcur->size_;
            for(; i < curSize; ++j, ++i) {
                newNode->valueField_[j] = pcur->valueField_[i];
                pcur->valueField_[i] = VALUE();
                --pcur->size_;

                newNode->subs_[j] = pcur->subs_[i];
                if(newNode->subs_[j])
                    newNode->subs_[j]->parent_ = newNode;
                ++newNode->size_;
                pcur->subs_[i] = nullptr;
            }

            newNode->subs_[j] = pcur->subs_[i];
            if(newNode->subs_[j])
                newNode->subs_[j]->parent_ = newNode;
            pcur->subs_[i] = nullptr;

            //将中间节点插入父节点
            if(root_ == pcur) {
                root_ = new Node;
                insertValue(root_, pcur->valueField_[mid], newNode);
                root_->subs_[0] = pcur;
                pcur->parent_ = root_;
                newNode->parent_ = root_;
            }
            else{
                Node* parent_ = pcur->parent_;
                insertValue(parent_, pcur->valueField_[mid], newNode);
            }

            pcur->valueField_[mid] = VALUE();
            --pcur->size_;
            pcur = pcur->parent_;
        }

        ++size_;
        return true;
    }

    void InOrder() {
        std::cout << "Inorder: ";
        inOrder(root_);
        std::cout << std::endl;
    }

private:
    void insertValue(Node* cur, const VALUE& value, Node* sub) {
        int end = cur->size_;
        for(; end > 0; --end) {
            if(KeyOfValue()(value) < KeyOfValue()(cur->valueField_[end - 1])) {
                cur->valueField_[end] = cur->valueField_[end - 1];
                cur->subs_[end + 1] = cur->subs_[end];
            }
            else
                break;
        }

        cur->valueField_[end] = value;
        cur->subs_[end + 1] = sub;

        if(sub)
            sub->parent_ = cur;

        ++cur->size_;
    }

    void inOrder(Node* root) {
        if(nullptr == root)
            return;

        size_t i = 0;
        for(; i < root->size_; ++i){
            inOrder(root->subs_[i]);
            std::cout << root->valueField_[i] << ' ';
        }

        inOrder(root->subs_[i]);
    }

private:
    Node*  root_;
    size_t size_ = 10; 
};

#endif
