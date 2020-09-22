#ifndef _BTREE_H_
#define _BTREE_H_

#include <utility>
#include <iostream>

template<typename K, typename V, size_t N = 4>
struct BTreeNode
{
	std::pair<K, V> kvs_[N];
	BTreeNode<K,V,N>* subs_[N + 1];
	BTreeNode<K,V,N>* parent_;
	size_t     size_;

	BTreeNode()
		:parent_(nullptr)
		,size_(0)
	{
		for (size_t i = 0; i < N; ++i) {
			subs_[i] = nullptr;
		}
	}
};

template<typename K, typename V, size_t N>
class BTree {
	typedef BTreeNode<K, V, N> Node;
public:
	BTree()
		:root_(nullptr)
		, size_(0)
	{
	}

	std::pair<Node*, int> Find(const K& key) {
		Node* parent = nullptr;
		Node* pcur = root_;
		while (pcur) {
			size_t i = 0;
			while (i < pcur->size_) {
				if (pcur->kvs_[i].first > key)
					break;
				else if (pcur->kvs_[i].first < key)
					++i;
				else
					return std::make_pair(pcur, i);
			}

			parent = pcur;
			pcur = pcur->subs_[i];
		}

		return std::make_pair(parent, -1);
	}

	bool Insert(const std::pair<K,V>& kv) {
		if (root_ == nullptr) {
			root_ = new Node();
			root_->kvs_[0] = kv;
			++root_->size_;
			++size_;

			return true;
		}

		std::pair<Node*, int> ret = Find(kv.first);
		//树中已经存在该key
		if (ret.second != -1) return false;

		Node* pcur = ret.first;
		Node* sub = nullptr;
		insert(pcur, kv, sub);

		//节点饱和则进行分裂
		while (pcur->size_ >= N) {
			int mid = N / 2;
			Node* newNode = new Node();

			size_t i = mid + 1, j = 0;
			size_t curr_size = pcur->size_;
			for (; i < curr_size; ++j, ++i) {
				newNode->kvs_[j] = pcur->kvs_[i];
				pcur->kvs_[i] = kv;
				--pcur->size_;

				newNode->subs_[j] = pcur->subs_[i];
				if (newNode->subs_[j])
					newNode->subs_[j]->parent_ = newNode;
				++newNode->size_;
				pcur->subs_[i] = nullptr;
			}

			newNode->subs_[j] = pcur->subs_[i];
			if (newNode->subs_[j])
				newNode->subs_[j]->parent_ = newNode;
			pcur->subs_[i] = nullptr;

			if (root_ == pcur) {
				root_ = new Node;
				insert(root_, pcur->kvs_[mid], newNode);
				root_->subs_[0] = pcur;
				pcur->parent_ = root_;
				newNode->parent_ = root_;
			}
			else {
				Node* parent = pcur->parent_;
				insert(parent, pcur->kvs_[mid], newNode);
			}

			pcur->kvs_[mid] = kv;
			--pcur->size_;
			pcur = pcur->parent_;
		}

		++size_;
		return true;
	}

	void InOrder() {
		std::cout << "Inorder:";
		inOrder(root_);
		std::cout << std::endl;
	}

private:
	void inOrder(Node* root) {
		if (nullptr == root)
			return;

		size_t i = 0;
		for (; i < root->size_; ++i) {
			inOrder(root->subs_[i]);
			std::cout << root->kvs_[i].first << ' ';
		}

		inOrder(root->subs_[i]);
	}


	void insert(Node* pcur, const std::pair<K, V>& kv, Node* sub) {
		size_t end = pcur->size_;
		for (; end > 0; --end) {
			//如果小于当前值，则当前值往后挪
			//从当前节点最大值开始检索
			if (kv.first < pcur->kvs_[end - 1].first) {
				pcur->kvs_[end] = pcur->kvs_[end - 1];
				pcur->subs_[end + 1] = pcur->subs_[end];
			}else{
					break;
			}
		}

		pcur->kvs_[end] = kv;
		pcur->subs_[end + 1] = sub;

		if (sub)
			sub->parent_ = pcur;

		++pcur->size_;
	}

private:
	size_t size_;
	Node* root_;
};

template<typename K, size_t N>
struct BPTreeNonLeafNode
{
	K keys_[N];
	void* subs_[N];
	BPTreeNonLeafNode<K, N>* parent_;
	size_t size_;
};

template<typename K, typename V, size_t N>
struct BPTreeLeafNode
{
	std::pair<K,V> kvs_[N];
	BPTreeLeafNode<K, V, N>* next_;
	BPTreeLeafNode<K, V, N>* prev_;
	BPTreeNonLeafNode<K, N>* parent_;
	size_t size_;
};

template<typename K, typename V, size_t N>
class BPTree {
	typedef BPTreeLeafNode<K, V, N> LeafNode;
	typedef BPTreeNonLeafNode<K, N> NonLefNode;

private:
	NonLefNode* root_;
	LeafNode* head_;
};

#endif // !_BTree_H_

