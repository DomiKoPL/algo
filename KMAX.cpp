template<typename T>
class KMaxQueue
{
private:
	deque<pair<int, T> > Q;
	vector<T> val;
public:

	void init(int n, vector<T> & v)
	{
		val = v;
	}

	void add(int id)
	{
		int count = 0;
		while(Q.size() and val[Q.back().first] <= val[id])
		{
			count += Q.back().second + 1;
			Q.pop_back();
		}

		Q.push_back()
	}

	void pop()
	{
		if(Q.front().second == 0)
			Q.pop_front();
		else 
			Q.front().second--;
	}

	int query()
	{
		if(Q.empty())
			return -1;
		return Q.front().first;	
	}
};