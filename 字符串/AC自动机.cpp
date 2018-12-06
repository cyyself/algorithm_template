//给定n个模式串和1个文本串，求有多少个模式串在文本串里出现过。
#include <bits/stdc++.h>
using namespace std;
struct node {
	int cnt;
	int next;//匹配不上时走的节点
	int ch[26];
}tr[1000005];
int ncnt = 0;
void insert(char *s) {
	int cur = 0;
	int len = strlen(s);
	for (int i=0;i<len;i++) {
		int v = s[i]-'a';
		if (!tr[cur].ch[v]) tr[cur].ch[v] = ++ncnt;
		cur = tr[cur].ch[v];
	}
	tr[cur].cnt ++;
}
void build_tree() {
	queue <int> q;//一定要广搜
	for (int i=0;i<26;i++) {
		if (tr[0].ch[i]) {
			tr[tr[0].ch[i]].next = 0;
			q.push(tr[0].ch[i]);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i=0;i<26;i++) {
			int &v = tr[u].ch[i];
			if (v) {
				tr[v].next = tr[tr[u].next].ch[i];
				q.push(v);
			}
			else {
				v = tr[tr[u].next].ch[i];
			}
		}
	}
}
int getans(char *s) {
	int len = strlen(s);
	int cur = 0;
	int ans = 0;
	for (int i=0;i<len;i++) {
		int v = s[i]-'a';
		cur = tr[cur].ch[v];
		for (int j=cur;j&&~tr[j].cnt;j=tr[j].next) {
			ans += tr[j].cnt;
			tr[j].cnt = -1;
		}
	}
	return ans;
}
char s[1000005];
int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%s",s);
		insert(s);
	}
	build_tree();
	scanf("%s",s);
	printf("%d\n",getans(s));
	return 0;
}
