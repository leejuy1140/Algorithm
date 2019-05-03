#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int V_MAX = 11;
const int N_MAX = 51;
const int INF = 99999999;
enum { EMPTY = 0, WALL, VIRUS };

int wallCnt; // n * n���� wallCnt�� �� ���� ���� Ȱ���Ǿ�� ��.
int answer = INF;
int n, m, map[N_MAX][N_MAX];

bool active[V_MAX]; // �ش� ���̷��� ���� �� true;
bool visited[N_MAX][N_MAX];
vector<pair<int, int>> virus; // �ʱ� ���̷��� ��ġ ����.

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
		int qsz = q.size(); // ���� �ʿ� Ȯ��� Ȱ�� ����.

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
				if (map[next_r][next_c] == WALL) continue; // �����δ� Ȯ�� �Ұ���.
				if (visited[next_r][next_c]) continue; // �̹� Ȯ��� ��.
				
				// ��Ȱ�� ���̷����� �ִ� ������ �����ؼ�
				// Ȱ�� ���̷����� ������ٸ�, ���̷��� ������ ī���� X.
				if (map[next_r][next_c] != VIRUS) virusCnt++;

				q.push({ next_r, next_c });
				visited[next_r][next_c] = true;
			}
		}

		// �̹� ��� ĭ�� ���̷����� �����ٸ�, Ż��.
		if (virusCnt == (n * n) - wallCnt) break;
	}

	// ���̷����� ��� ĭ�� �����ٸ�, ���� �ð� ��ȯ.
	if (virusCnt == (n * n) - wallCnt) return time;
	else							   return INF;
}

void SelectVirus(int v, int cnt)
{
	active[v] = true;

	// m�� ����������, Ȱ��ȭ��Ų �� �۶߸�.
	if (cnt == m)
	{
		int curTime = SpreadVirus();
		answer = answer < curTime ? answer : curTime;
		return;
	}

	// �������� Ȱ��ȭ��ų ���̷��� ����.
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

	// �̹� ��� ĭ�� ���̷������ �ٷ� ���.
	if (virus.size() == (n * n) - wallCnt)
	{
		cout << 0;
		return 0;
	}
	
	// Ȱ������ �ٲ� ���̷��� m�� ����.
	for (int i = 0; i < virus.size(); i++)
	{
		SelectVirus(i, 1);
		active[i] = false;
	}

	// ��� ĭ�� ���̷����� Ȯ���� �� ������ -1.
	if (answer == INF) answer = -1;
	cout << answer;

	return 0;
}