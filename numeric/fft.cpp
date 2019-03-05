namespace fft
{
	using namespace std;
	typedef complex<double> comp;
	const int MAXN = 40000;//set to max
	comp omega[MAXN];
	comp a1[MAXN], a2[MAXN];
	comp z1[MAXN], z2[MAXN];

	int n;
	void fft(comp *a, comp *b, int m = n)
	{
		if (m == 1)
		{
			b[0] = a[0];
			return;
		}

		int s = n / m;
		m /= 2;

		fft(a, b, m);
		fft(a + s, b + m, m);

		for (int i = 0; i < m; i++)
		{
			comp c = omega[s*i] * b[m + i];
			b[m + i] = b[i] - c;
			b[i] += c;
		}
	}

	vector<long long> mult(vector<long long> &a, vector<long long> &b)
	{
		int len = (int)a.size() + (int)b.size() - 1;
		n = len;
		while (n & (n - 1)) ++n;

		fill(a1, a1 + n, 0);
		fill(a2, a2 + n, 0);

		copy(a.begin(), a.end(), a1);
		copy(b.begin(), b.end(), a2);

		for (int i = 0; i < n; i++)
		{
			omega[i] = polar(1.0, 2 * M_PI / n * i);
		}

		fft(a1, z1, n);
		fft(a2, z2, n);

		for (int i = 0; i < n; i++)
		{
			omega[i] = comp(1, 0) / omega[i];
			a1[i] = z1[i] * z2[i] / comp(n, 0);
		}

		fft(a1, z1, n);

		vector<long long> res(len);
		for (int i = 0; i < len; i++)
		{
			res[i] = ((long long)round(z1[i].real()));
		}
		return res;
	}
}