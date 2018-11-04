#include <stdio.h>
#include <malloc.h>
#define min(x,y) (x<y ? x:y)

const int maxN = 1000000;
int N;
int child[maxN + maxN + 1];
int sibling[maxN + maxN + 1];
int last_child[maxN + 1];
int visit[maxN + 1];
int order[maxN + 1];
int d[maxN + 1][2];


typedef struct _LINK {
	int val;
	struct _LINK *prev;
	struct _LINK *next;
}LINK;

typedef struct _QUEUE {
	LINK head;
	LINK tail;

	_QUEUE() {
		head.val = 0;
		head.next = &tail;
		head.prev = NULL;
		tail.prev = &head;
		tail.next = NULL;
	}

	void push(int val) {
		LINK *p = (LINK*)malloc(sizeof(LINK));
		p->val = val;
		tail.prev->next = p;
		p->prev = tail.prev;

		p->next = &tail;
		tail.prev = p;
	}
	bool empty() {
		if (head.next == &tail)
			return 1;
		return 0;
	}
	int front() {
		return head.next->val;
	}
	void pop() {
		LINK *p;
		p = head.next;
		head.next->next->prev = &head;
		head.next = head.next->next;
		free(p);
	}

}QUEUE;

QUEUE q;

int edge_num = 2;
void setG(int p, int s)
{
	child[edge_num] = s;
	sibling[edge_num] = last_child[p];
	last_child[p] = edge_num++;
}


int main()
{
	//freopen("input.txt","r",stdin);
	scanf("%d", &N);
	int a, b;
	for (int n = 1; n < N; n++)
	{
		
		scanf("%d %d", &a, &b);
		setG(a, b); // 엣지 추가
		setG(b, a);
	}
	for (int n = 1; n <= N; n++)
	{
		d[n][1] = 1;
	}
	
	
	
	q.push(1);
	int cnt = 1;
	order[cnt++] = 1;
	while (!q.empty())
	{
		int par = q.front(); q.pop();
		//printf("node : %d\n",par);
		int x = last_child[par]; //par의 가장 마지막 child를 저장하는 엣지번호를 x에 저장
		visit[par] = 1;
		while (x)
		{
			int chi = child[x]; // 엣지 노드에서 child 값을 불러 들여서 chi에 저장
			x = sibling[x]; // 이전 형제 노드 번호를 x에 저장
			if (visit[chi]) continue;
			order[cnt++] = chi; // 노드 순서를 order에 저장
			q.push(chi);
		}
	}
	/*
	printf("        \t");
	for (int n = 0; n < edge_num; n++)
	{
		printf("%3d", n);
	}
	printf("\nchild      :\t");
	for (int n = 0; n < edge_num; n++)
	{
		printf("%3d", child[n]);
	}
	printf("\nsibling    :\t");
	for (int n = 0; n < edge_num; n++)
	{
		printf("%3d", sibling[n]);
	}
	printf("\nlast_child :\t");
	for (int n = 0; n < edge_num; n++)
	{
		printf("%3d", last_child[n]);
	}
	printf("\norder       :\t");
	for (int n = 0; n < cnt; n++)
	{
		printf("%3d", order[n]);
	}
	printf("\n");
	*/
	for (int c = cnt - 1; c >= 1; c--)// 아래에서 부터 위로 탐색실시
	{
		visit[order[c]] = 0; // 방문했다면 0으로 표시
		int x = last_child[order[c]]; // 마지막 자식노드의 엣지 값 저장
		//printf("oreder c: %d  x : %d\n",order[c],x);
		while (x) // 형제 노드가 있다면 형제 노드를 모두 계산해서 부모 노드에 더한다.
		{
			int par = child[x]; // par에 현재의 노드(order[c])의 child를 저장
			x = sibling[x]; //형제 노드를 가리키는 엣지 번호 저장
			if (visit[par]) continue; // 만약 이미 방문한 곳이 아니라면 즉 par가 자식 노드가 아닌, 상위 노드라면 continue로 패스
			//printf("d[%d][0] += d[%d][1]\n", order[c], par );
			d[order[c]][0] += d[par][1]; // 부모 노드가 얼리 어덥터가 아닐때 자식 노드가 모두 얼리 어덥터인 값을 모두 더한다.
			d[order[c]][1] += min(d[par][0], d[par][1]);// 부모가 얼리 어덥터 일 경우 자식 노드가 얼리 어덥터 인것과 아닌 것 중 최소값을 더한다.
		}
	}

	printf("%d\n", min(d[1][0], d[1][1])); //
	return 0;
}

