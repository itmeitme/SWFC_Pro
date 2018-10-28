#include <stdio.h>
#include <malloc.h>

int main(void) {
	int n, m;
	scanf("%d", &n);

	int **map = (int**)malloc(sizeof(int*)* (n + 1));

	for (int i = 0; i <= n; i++)
		map[i] = (int*)malloc(sizeof(int)* (n + 1));

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0) {
				map[i][j] = 0;
				continue;
			}

			scanf("%d", &map[i][j]);
			map[i][j] += map[i][j - 1];
		}

		if (i == 0)
			continue;

		for (int j = 1; j <= n; j++) {
			map[i][j] += map[i - 1][j];
		}
	}

	scanf("%d", &m);
	int sri, sci, eri, eci;
	long long int result = 0;

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &sri, &sci, &eri, &eci);
		result = map[eri][eci] - map[eri][sci - 1] - map[sri - 1][eci] + map[sri - 1][sci - 1];
		printf("%d\n", result);
	}

	for (int i = 0; i <= n; i++)
		free(map[i]);
	free(map);

	return 0;
}