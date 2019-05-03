#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int V_MAX = 11;
const int N_MAX = 51;
const int INF = 99999999;
enum { EMPTY = 0, WALL, VIRUS };

int wallCnt; // n * n에서 wallCnt를 뺀 수가 전부 활성되어야 함.
int answer = INF;
int n, m, map[N_MAX][N_MAX];

bool active[V_MAX]; // 해당 바이러스 선택 시 true;
bool visited[N_MAX][N_MAX];
vector<pair<int, int>> virus; // 초기 바이러스 위치 저장.

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int SpreadVirus()
{
	memset(visited, false, sizeof(visited));

	queue<pair<int, int>> q;
	for (int i = 0; i < virus.size(); i++)
	{
		if (active[i])
		{
			q.push(virus[i]);
			visited[virus[i].first][virus[i].second] = true;
		}
	}

	int time = 0;
	int virusCnt = virus.size();
	
	while (!q.empty())
	{
		time++;
		int qsz = q.size(); // 현재 초에 확산될 활성 개수.

		while (qsz--)
		{
			int cur_r = q.front().first;
			int cur_c = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int next_r = cur_r + dr[i];
				int next_c = cur_c + dc[i];
				if (next_r < 0 || next_r >= n || next_c < 0 || next_c >= n) continue;
				if (map[next_r][next_c] == WALL) continue; // 벽으로는 확산 불가능.
				if (visited[next_r][next_c]) continue; // 이미 확산된 곳.
				
				// 비활성 바이러스가 있는 곳으로 도착해서
				// 활성 바이러스로 만들었다면, 바이러스 개수는 카운팅 X.
				if (map[next_r][next_c] != VIRUS) virusCnt++;

				q.push({ next_r, next_c });
				visited[next_r][next_c] = true;
			}
		}

		// 이미 모든 칸에 바이러스가 퍼졌다면, 탈출.
		if (virusCnt == (n * n) - wallCnt) break;
	}

	// 바이러스가 모든 칸에 퍼졌다면, 현재 시간 반환.
	if (virusCnt == (n * n) - wallCnt) return time;
	else							   return INF;
}

void SelectVirus(int v, int cnt)
{
	active[v] = true;

	// m개 선택했으면, 활성화시킨 후 퍼뜨림.
	if (cnt == m)
	{
		int curTime = SpreadVirus();
		answer = answer < curTime ? answer : curTime;
		return;
	}

	// 다음으로 활성화시킬 바이러스 선택.
	for (int i = v + 1; i < virus.size(); i++)
	{
		SelectVirus(i, cnt + 1);
		active[i] = false;
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == WALL) wallCnt++;
			if (map[i][j] == VIRUS) virus.push_back({ i, j });
		}
	}

	// 이미 모든 칸이 바이러스라면 바로 출력.
	if (virus.size() == (n * n) - wallCnt)
	{
		cout << 0;
		return 0;
	}
	
	// 활성으로 바꿀 바이러스 m개 선택.
	for (int i = 0; i < virus.size(); i++)
	{
		SelectVirus(i, 1);
		active[i] = false;
	}

	// 모든 칸에 바이러스를 확산할 수 없으면 -1.
	if (answer == INF) answer = -1;
	cout << answer;

	return 0;
}