#include <iostream>
#include <string.h>
using namespace std;

#define us us
#define CS 10000

template <typename T>
class vector
{
private:
	T* arr;
	int len;
public:
	vector()
		: arr(NULL), len(0)
	{}
	~vector()
	{
		delete[] arr;
	}
	void push_back(T& in)
	{
		if (len%CS == 0)
		{
			T *tmp = new T[len + CS];
			memcpy(tmp, arr, sizeof(T)*len);
			delete[] arr;
			arr = tmp;
		}
		arr[len++] = in;
	}
	int size()
	{
		return len;
	}
	T& operator[](int idx)
	{
		return arr[idx];
	}
};


typedef struct vertex
{
	vector<us> node;
	int late = 0;
	int early = 0;
	bool visit = false;
}vertex;

void dfs(vertex* tree, int idx);

int main(void)
{
	int num = 0;
	us pidx = 0, cidx = 0;

	cin >> num;

	vertex* tree = new vertex[num + 1];

	for (int i = 0; i < num - 1; i++)
	{
		cin >> pidx >> cidx;
		//pidx -= 1; cidx -= 1;

		tree[pidx].node.push_back(cidx);
		tree[cidx].node.push_back(pidx);
	}

	dfs(tree, 1);
	cout << (tree[1].early < tree[1].late ? tree[1].early : tree[1].late) << endl;
	//cout << (tree[0].early < tree[0].late ? tree[0].early : tree[0].late) << endl;

	delete[]tree;
}

void dfs(vertex* tree, int idx)
{
	tree[idx].visit = true;
	tree[idx].early = 1;
	tree[idx].late = 0;

	for (int i = 0; i < tree[idx].node.size(); i++)
	{
		int nidx = tree[idx].node[i];

		if (!tree[nidx].visit)
		{
			dfs(tree, nidx);
			tree[idx].early += tree[nidx].early < tree[nidx].late ? tree[nidx].early : tree[nidx].late;
			tree[idx].late += tree[nidx].early;
		}
	}
}