#include <stdio.h>

int N, M;
int p_sum[1001][1001] = { 0 }; // 부분합 저장 배열


int main(void)
{
	 //freopen("input.txt", "r", stdin);
	 scanf("%d", &N);
	 int val;
	 for (int i = 0; i < N; i++) {
		 for (int j = 0; j < N; j++) {
			scanf("%d", &val);
			p_sum[i+1][j+1] = p_sum[i + 1][j] + val ;// 1칸 전의 col과 현재 col에 들어갈 값을 더해서 저장 하면서 col 단위로 부분합을 만든다.
													// i,j 에 각각 1을 더한 이유는 0부터 더하면서 시작하도록 0 padding을 넣은것이다.
		 }
	 }
	 for (int i = 0; i <= N; i++) { // 세로 축으로 부분합을 더한다. 이 부분합은 이전에 가로축으로 누적시킨 데이터 배열에 수행한다.
		 for (int j = 1; j <= N; j++) {
			 p_sum[j][i] = p_sum[j-1][i] + p_sum[j][i];
		 }
	 }
	 
	 scanf("%d", &M);
	 int sri, sci, eri, eci;
	 long long int result;
	 for (int i = 0; i < M; i++) {
		 scanf("%d %d %d %d", &sri, &sci, &eri, &eci);
		 result = p_sum[eri][eci] - p_sum[eri][sci-1] - p_sum[sri-1][eci] + p_sum[sri-1][sci-1]; // 주어진 부분합의 결과값은 위의 수식을 계산 하면 된다.
		 printf("%lld\n",result);
	 }

	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}
