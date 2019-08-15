#include <bits/stdc++.h>


template <typename TKey, typename TGenerator = std::mt19937> 
class DynamicPrefSum {
private:
    struct Node;
	using priority_type	= typename TGenerator::result_type;
	using node_const	= const Node* const;
	using node_ptr		= std::unique_ptr<Node>;
	using node_pair		= std::pair<node_ptr,node_ptr>;

    struct Node {
		TKey			m_key, m_sum;
		size_t			m_size;
		priority_type	m_priority;
		node_ptr		mp_left, mp_right;
 
		Node(TKey key, priority_type priority)
			: m_key		{ key }
            , m_sum     { key }
			, m_size	{ 1 }
			, m_priority { priority }
		{}
 
		void setLeft(node_ptr left) {
			mp_left.swap(left);
			update();
		}
 
		void setRight(node_ptr right) {
			mp_right.swap(right);
			update();
		}
 
		void update() {
			m_size = 1;
            m_sum = m_key;
			if (mp_left)  {
                m_size += mp_left->m_size;
                m_sum += mp_left->m_sum;
            }
            if (mp_right) {
                m_size += mp_right->m_size;
                m_sum += mp_right->m_sum;
            }
        }
	};

	node_pair split(node_ptr node, size_t pos, size_t add) {
		if (!node)
			return std::make_pair(nullptr , nullptr);

        int cur = (node->mp_left ? node->mp_left->m_size : 0) + add;
		if (pos > cur) {
			auto splitted_node = split(std::move(node->mp_right), pos, cur + 1);
			node->setRight(std::move(splitted_node.first));
			return { std::move(node) , std::move(splitted_node.second) };
		} else {
			auto splitted_node = split(std::move(node->mp_left), pos, add);
			node->setLeft(std::move(splitted_node.second));
			return { std::move(splitted_node.first) , std::move(node) };
		}
	}

	node_ptr merge(node_ptr a, node_ptr b) {
		if (!a) return std::move(b);
		if (!b) return std::move(a);
 
		if (a->m_priority > b->m_priority) {
			a->setRight(merge(std::move(a->mp_right), std::move(b)));
			return std::move(a);
		}
		else {
			b->setLeft(merge(std::move(a), std::move(b->mp_left)));
			return std::move(b);
		}
	}

    
public:
    TKey getPrefSum(size_t pos) {
        auto spl_node = split(std::move(mp_root), pos + 1, 0);
        TKey res = (spl_node.first ? spl_node.first->m_sum : 0);
        mp_root = merge(std::move(spl_node.first), std::move(spl_node.second));
        return res;
    }

    void insert(size_t pos, TKey val) {
        auto spl_node = split(std::move(mp_root), pos, 0);
        node_ptr newNode = std::make_unique<Node>(val, m_generator());
        auto temp = merge(std::move(spl_node.first), std::move(newNode));
        mp_root = merge(std::move(temp), std::move(spl_node.second));
    }

	void remove(size_t pos) {
		auto spl1 = split(std::move(mp_root), pos, 0);
		auto spl2 = split(std::move(spl1.second), 1, 0);
		mp_root = merge(std::move(spl1.first), std::move(spl2.second));
	}

    DynamicPrefSum() 
        : m_generator { std::chrono::steady_clock::now().time_since_epoch().count() }
    {}

private:
	node_ptr	mp_root;
	TGenerator	m_generator;
};