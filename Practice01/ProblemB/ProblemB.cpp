#include <iostream>
#include <vector>
using namespace std;

typedef struct vertex
{
	vector<int> node;
	int late = 0;
	int early = 0;
	bool visit = false;
}vertex;

void dfs(vertex* tree, int idx);

int main(void)
{
	int num = 0;
	int pidx = 0, cidx = 0;

	cin >> num;

	vertex* tree = new vertex[num];

	for (int i = 0; i < num - 1; i++)
	{
		cin >> pidx >> cidx;
		pidx -= 1; cidx -= 1;

		tree[pidx].node.push_back(cidx);
	}

	dfs(tree, 0);
	cout << (tree[0].early < tree[0].late ? tree[0].early : tree[0].late) << endl;

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