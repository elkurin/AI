/****************************************************************
すいませんすいませんすいませんデバッグ間に合いませんでしたクソ雑魚ですすいませんすいません
****************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <math.h>
#include <random>
#include <utility>
#include <array>

using namespace std;

#define vec vector 
#define pb push_back

typedef struct {
	int id;
	int hp;
	int x;
	int y;
} Creep;

typedef struct {
	int range;
	int damage;
	int cost;
} Tower;

typedef struct
{
	pair<int, int> place;
	int towernum;
} Find;

const int time_finish = 2000;

int n, m;
int money;
int creephp;
int creepmoney;
vec<string> board;
vec<Tower> towers;
vec<pair<int, int>> base;
vec<Find> baseput;

int givetower(int min)
{
	// if (strategy == 0) {
		int give = 0;
		int max = 0;
		// cout << "may the force be with you " << towers.size() << endl;
		for (int i = 0; i < (int)towers.size(); i++) {
			if (towers[i].range < min) continue;
			if (max < towers[i].damage + towers[i].range) {
				// cout << "hoge " << towers[i].damage + towers[i].range << endl;
				max = towers[i].damage + towers[i].range;
				give = i;
			}
		}
		return give;
	// } else if (strategy == 1) {
	// 	int give = 0;
	// 	int max = - 100;
	// 	for (int i = 0; i < towers.size(); i++) {
	// 		if (towers[i].range < min) continue;
	// 		if (max < towers[i].range - towers[i].cost * 3) {
	// 			max = towers[i].range - towers[i].cost * 3;
	// 			give = i;
	// 		}
	// 	}
	// 	return give;
	// }
}

int outside(pair<int, int> p, pair<int, int> x)
{
	int ret = 0;
	if (p.first + x.first < 0 || p.first + x.first >= n || p.second + x.second < 0 || p.second + x.second >= n) ret = 1;
	return ret;
}


Find find(pair<int, int> p, int strategy)
{
	vec<pair<int, int>> d1(4);
    d1 = {{1, 0}, {- 1, 0}, {0, 1}, {0, - 1}};
	vec<pair<int, int>> d2(8);
	d2 = {{2, 0}, {- 2, 0}, {0, 2}, {0, - 2},
		  {1, 1}, {- 1, 1}, {- 1, 1}, {- 1, - 1}};
	vec<pair<int, int>> d3(12);
	d3 = {{3, 0}, {- 3, 0}, {0, 3}, {0, - 3},
		  {2, 1}, {- 2, 1}, {2, - 1}, {- 2, - 1},
		  {1, 2}, {- 1, 2}, {1, - 2}, {- 1, - 2}};
	vec<pair<int, int>> d4(16);
	d4 = {{4, 0}, {- 4, 0}, {0, 4}, {0, - 4},
		  {3, 1}, {- 3, 1}, {3, - 1}, {- 3, - 1},
		  {1, 3}, {- 1, 3}, {1, - 3}, {- 1, - 3},
		  {2, 2}, {- 2, 2}, {2, - 2}, {- 2, - 2}};
	vec<vec<pair<int, int>>> d;
	d.pb(d1);
	d.pb(d2);
	d.pb(d3);
	d.pb(d4);
	// cout << "in find" << endl;
	int min = 1;
	vec<pair<int, int>> v;
	int first = 1;
	int keep;
	// cout << "before while" << endl;
	while(min < 5) {
		// cout << "in while " << min << endl;
		for (int i = 0; i < min * 4; i++) {
			// cout << "  " << i << endl;
			// cout << "  " << p.first + d[min][i].first << " " << p.second + d[min][i].second << endl;
			if (outside(d[min][i], p)) continue;
			if (board[p.first + d[min][i].first][p.second + d[min][i].second] == '#') {
				v.pb({p.first + d[min][i].first, p.second + d[min][i].second});
			}
		}
		// for (int i = 0; i < min; i++) {
		// 	if (board[p.first + min - i][p.second + i] == '#') {
		// 		v.pb({p.first + min - i, p.second + i});
		// 	} 
		// 	if (board[p.first + i][p.second + min - i] == '#') {
		// 		v.pb({p.first + i, p.second + min - i}):
		// 	} 
		// 	if (board[p.first - min - i][p.second + i] == '#') {
		// 		v.pb({p.first - min - i, p.second + i});
		// 	}
		// 	if (board[p.first + i][p.second - min - i] == '#') {
		// 		v.pb({p.first + i, p.second - min - i});
		// 	}
		if (v.size() && first == 1) {
			keep = min;
			first = 0;
		}
		if (v.size() >= 3) break;
		min++;
	}
	int max = - 1;
	int second = - 1;
	int third = - 1;
	pair<int, int> keep1, keep2, keep3;
	for (int j = 0; j < (int)v.size(); j++) {
		int count = 0;
		for (int l = 1; l <= keep; l++) {
			for (int i = 0; i < 4 * l; i++) {
				if (outside(d[l][i], v[j])) continue;
				if (board[v[j].first + d[l][i].first][v[j].second + d[l][i].second] == '.') {
					count += min - l;
				}
			}
		}
		if (count > max) {
			third = second;
			second = max;
			max = count;
			keep3 = keep2;
			keep2 = keep1;
			keep1 = v[j];
		} else if (count > second) {
			third = second;
			second = count;
			keep3 = keep2;
			keep2 = v[j];
		} else if (count > third) {
			third = count;
			keep3 = v[j];
		}
	}
	// cout << "before tower" << endl;
	int get = givetower(2);
	Find give;
	if (strategy == 0) {
		give = {keep1, get};
	} else if (strategy == 1) {
		give = {keep2, get};
	} else {
		give = {keep3, get};
	}
	return give;
}

vec<pair<int, int>> beside(vec<vec<bool>> built)
{
	vec<pair<int, int>> give;
	vec<pair<int, int>> d1(4);
    d1 = {{1, 0}, {- 1, 0}, {0, 1}, {0, - 1}};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (built[i][j]) continue;
			int count = 0;
			for (int k = 0; k < 4; k++) {
				if (outside({i, j}, d1[k])) continue;
				if (board[i + d1[k].first][j + d1[k].second] == '.') count++;
			}
			if (count) give.pb({i, j});
		}
	}
	return give;
}

int main(void)
{
	srand(1);
	// cout << "start" << endl;
	cin >> n;
	cin >> money;

	vec<vec<bool>> built(n, vec<bool>(n, false));

	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		board.pb(str);
		// cout << "no more segmentation fault" << endl;
		for (int j = 0; j < n; j++) {
			if (board[i][j] != '#') built[i][j] = 1;
			if (board[i][j] != '.' && board[i][j] != '#') {
				// cout << "in loop" << endl;
				pair<int, int> p = {i, j};
				base.pb(p);
			}
		}
	}

	cin >> creephp;
	cin >> creepmoney;

	cin >> m;

	for (int i = 0; i < m; i++) {
		// cout << "towertower" << endl;
		Tower t;
		cin >> t.range;
		cin >> t.damage;
		cin >> t.cost;
		towers.pb(t);
	}

	for (int i = 0 ; i < (int)base.size(); i++) {
		Find q = find(base[i], 0);
		baseput.pb(q);
	}

	// cout << "oooooooooooooooo" << board[10][15] << " " << built[10][15] << endl;
	vec<pair<int, int>> roadside = beside(built);
	// for (int i = 0; i < (int)roadside.size(); i++) {
	// 	cout << roadside[i].first << " " << roadside[i].second << endl;
	// }

	int l = 0;
	vec<int> prev_basehp(n);

	// cout << "befor t loop" << endl;

	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		cout << built[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	for (int t = 0; t < time_finish; t++) {
		// cout << "gimme money" << endl;
		int strategy = 0;
		cin >> money;
		int creepnum;
		cin >> creepnum;

		vec<Creep> creeps;
		// cout << "before creep" << endl;
		for (int i = 0; i < creepnum; i++) {
			Creep crp;
			cin >> crp.id;
			cin >> crp.hp;
			cin >> crp.x;
			cin >> crp.y;
			creeps.pb(crp);
		}

		if (creepnum > 15) strategy = 1;

		// cout << "end of creep" << endl;

		int basenum;
		cin >> basenum;
		vec<int> basehp;
		for (int i = 0; i < basenum; i++) {
			// cout << "booooo " << basenum << " " << i << endl;
			int hp;
			cin >> hp;
			basehp.pb(hp);
		}
		// cout << "end of base" << endl;
		vec<int> yavai;
		if (t != 0) {
			for (int i = 0; i < basenum; i++) {
				if (basehp[i] != prev_basehp[i]) strategy = 1;
				yavai.pb(i);
			}
		}
		for (int i = 0; i < basenum; i++) {
			prev_basehp[i] = basehp[i];
		}
		vec<Find> out;
		while(l < (int)base.size()) {
			// cout << " " << l << endl;
			if (money - towers[baseput[l].towernum].cost >= 0) {
				out.pb(baseput[l]);
				money -= towers[baseput[l].towernum].cost;
				// cout << "before built" << endl;
				// cout << " " << baseput[l].place.first << " " << baseput[l].place.second << endl;
				// cout << built[14][13] << endl;
				built[baseput[l].place.first][baseput[l].place.second] = 1;
				// cout << "ha~~ kireso~~" << endl;
			} else break;
			l++;
		}

		// for (int o = 0; o < 10; o++) {
		// 	pair<int, int> g = roadside[rand() % (int)roadside.size()];
		// 	// cout << g.first << " " << g.second << endl;
		// 	if (built[g.first][g.second]) continue;
		// 	out.pb({g, baseput[0].towernum});
		// }

		if (strategy) {
			// for (int i = 0; i < (int)yavai.size(); i++) {
			// 	if (money - towers[baseput[yavai[i]].towernum].cost >= 0) {
			// 		Find p = find(base[i], 1);
			// 		// cout << "^o^/~~" << endl;
			// 		if (!built[p.place.first][p.place.second]) {
			// 			out.pb(find(base[i], 1));
			// 			built[p.place.first][p.place.second] = 1;
			// 		} else {
			// 			p = find(base[i], 2);
			// 			if (!built[p.place.first][p.place.second]) {
			// 				out.pb(find(base[i], 1));
			// 				built[p.place.first][p.place.second] = 1;
			// 			}
			// 		}
			// 	}
			// 	// cout << "catch me if U can" << endl;
			// }
			for (int o = 0; o < 1; o++) {
				pair<int, int> g = roadside[rand() % (int)roadside.size()];
				if (built[g.first][g.second]) continue;
				out.pb({g, baseput[0].towernum});
				built[g.first][g.second] = 1;
			}
		}

		if (t == 1500) {
			for (int o = 0; o < 5; o++) {
				pair<int, int> g = roadside[rand() % (int)roadside.size()];
				if (built[g.first][g.second]) continue;
				out.pb({g, baseput[0].towernum});
				built[g.first][g.second] = 1;
			}
		}

					
		cout << out.size() << endl;
		for (int i = 0; i < (int)out.size(); i++) {
			cout << out[i].place.second << " " << out[i].place.first << " " << out[i].towernum << endl;
		}
	}
}
