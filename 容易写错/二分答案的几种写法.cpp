//求最小答案
int l = 0;
int r = INF;
while (l < r) {
	int mid = (l + r) / 2;
	if (judge(mid)) r = mid;
	else l = mid + 1;
}
//求最大答案
int l = 0;
int r = INF;
while (l < r) {
	int mid = (l + r + 1) / 2;
	if (judge(mid)) l = mid;
	else r = mid - 1;
}
//通用求最小
int l = 0;
int r = INF;
int ans = -1;
while (l <= r) {
	int mid = (l + r) / 2;
	if (judge(mid)) {
		ans = mid;
		r = mid - 1;
	}
	else l = mid + 1;
}
//通用求最大
int l = 0;
int r = INF;
int ans = -1;
while (l <= r) {
	int mid = (l + r) / 2;
	if (judge(mid)) {
		ans = mid;
		l = mid + 1;
	}
	else r = mid - 1;
}
