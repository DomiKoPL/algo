template<typename TKey, typename TComparator = std::less<TKey>, typename TGenerator = std::mt19937>
class Treap
{
private:
	struct Node;
 
	using priority_type	= typename TGenerator::result_type;
	using node_const	= const Node* const;
	using node_ptr		= std::unique_ptr<Node>;
	using node_pair		= std::pair<node_ptr,node_ptr>;
 
	struct Node
	{
		TKey			m_key;
		size_t			m_size;
		priority_type	m_priority;
		node_ptr		mp_left, mp_right;
	 
 
		Node(TKey key, priority_type priority)
			: m_key		{ key }
			, m_size	{ 1 }
			, m_priority { priority }
		{}
 
		void SetLeft(node_ptr left)
		{
			mp_left.swap(left);
			UpdateSize();
		}
 
		void SetRight(node_ptr right)
		{
			mp_right.swap(right);
			UpdateSize();
		}
 
		void UpdateSize()
		{
			m_size = 1;
			if (mp_left)  m_size += mp_left->m_size;
			if (mp_right) m_size += mp_right->m_size;
		}
 
	};
 
   
	node_pair _Split(node_ptr node, TKey key)
	{
		if (!node)
			return std::make_pair(nullptr , nullptr);
 
		if (m_comparator(node->m_key , key))
		{
			auto splitted_node = _Split(std::move(node->mp_right) , key);
			node->SetRight(std::move(splitted_node.first));
			return { std::move(node) , std::move(splitted_node.second) };
		}
		else
		{
			auto splitted_node = _Split(std::move(node->mp_left), key);
			node->SetLeft(std::move(splitted_node.second));
			return { std::move(splitted_node.first) , std::move(node) };
		}
	}
 
	node_ptr _Merge(node_ptr a, node_ptr b)
	{
		if (!a) return std::move(b);
		if (!b) return std::move(a);
 
		if (a->m_priority > b->m_priority)
		{
			a->SetRight(_Merge(std::move(a->mp_right), std::move(b)));
			return std::move(a);
		}
		else
		{
			b->SetLeft(_Merge(std::move(a), std::move(b->mp_left)));
			return std::move(b);
		}
	}
 
	node_ptr _Insert(node_ptr node, TKey key, priority_type priority)
	{
		if (!node)
			return std::make_unique<Node>(key, priority);
 
		if (node->m_priority < priority)
		{
			auto splitted_node = _Split(std::move(node), key);
			auto new_node = std::make_unique<Node>(key, priority);
			new_node->SetLeft(std::move(splitted_node.first));
			new_node->SetRight(std::move(splitted_node.second));
			return std::move(new_node);
		}
	   
		if (m_comparator(node->m_key , key))
		{
			node->SetRight(_Insert(std::move(node->mp_right), key, priority));
		}
		else
		{
			node->SetLeft(_Insert(std::move(node->mp_left), key, priority));
		}
 
		return std::move(node);
	}
 
	node_ptr _Erase(node_ptr node, TKey key)
	{
		if (!node)
			return nullptr;

		if(m_comparator(node->m_key , key))
		{
			node->SetRight(_Erase(std::move(node->mp_right), key));
		}
		else if(m_comparator(key , node->m_key))
		{
			node->SetLeft(_Erase(std::move(node->mp_left), key));
		}
		else
		{
			return _Merge(std::move(node->mp_left), std::move(node->mp_right));
		}

		return std::move(node);
	}
 
	node_const _KthNode(node_const node, size_t k) const
	{
		size_t size_of_left_subtree = (node->mp_left ? node->mp_left->m_size : 0);
		if (size_of_left_subtree + 1 == k)
			return node;
		else if (size_of_left_subtree >= k)
			return _KthNode(node->mp_left.get(), k);
		else
			return _KthNode(node->mp_right.get(), k - size_of_left_subtree - 1);
	}
 
	size_t _LowerBound(node_const node, TKey key) const
	{
		if (!node)
			return 0;
		
		if(m_comparator(node->m_key , key))
		{
			size_t size_of_left_subtree = (node->mp_left ? node->mp_left->m_size : 0);
			return _LowerBound(node->mp_right.get(), key) + size_of_left_subtree + 1;	
		}
		else
		{
			return _LowerBound(node->mp_left.get(), key);	
		}
	}

	bool _Equals(const TKey& val1, const TKey& val2) const
	{
		return !m_comparator(val1, val2) && !m_comparator(val2, val1);
	}
 
public:
	explicit Treap(TComparator comparator = TComparator())
		: m_generator	{ std::chrono::steady_clock::now().time_since_epoch().count() }
		, m_comparator	{ comparator }
	{}
	
	template<typename Iterator>
	Treap(Iterator begin_it, Iterator end_it, TComparator comparator = TComparator())
		: Treap(comparator)
	{
		while(begin_it != end_it)
			Insert(*begin_it++);
	}
 
	void Insert(TKey value)
	{
		mp_root = _Insert(std::move(mp_root), value, m_generator());
	}
 
	void Erase(TKey value)
	{
		if(!Contains(value))
			return;
		mp_root = _Erase(std::move(mp_root), value);
	}
 
	TKey KthElement(size_t k) const
	{
		if(k >= Size())
			throw std::out_of_range("");
		return _KthNode(mp_root.get(), k + 1)->m_key;
	}
	
	size_t OrderOfKey(TKey value) const
	{
		auto count_lower_than_value = _LowerBound(mp_root.get(), value);
		if(_Equals(KthElement(count_lower_than_value), value))
			return count_lower_than_value;
		else
			return static_cast<size_t>(-1);
	}
	
	bool Contains(TKey value) const
	{
		return static_cast<size_t>(-1) != OrderOfKey(value);
	}
	
	size_t Size() const
	{
		return mp_root ? mp_root->m_size : 0;
	}
	
	bool Empty() const
	{
		return 0 == Size();
	}
 
private:
	node_ptr	mp_root;
	TGenerator	m_generator;
	TComparator	m_comparator;
};
