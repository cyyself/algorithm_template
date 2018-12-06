#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int a[20000];
vector<int> b;
queue<int> q;
stack<int> s;

int main() {
  int n;
  cin >> n;
  for(int i=0;i<n;i++) {
    cin >> a[i];
    b.push_back(a[i]);
  }
  sort(a, a+n);
  sort(b.begin(), b.end());

  for(int i=0;i<n;i++) cout << a[i] << " ";
  cout << endl;
  for(int i=0;i<b.size();i++) cout << b[i] << " ";
  cout << endl;

  q.push(1); q.push(2); q.push(3);
  s.push(1); s.push(2); s.push(3);
  while(!q.empty()) {
    cout << q.front() << " ";
    q.pop();
  }
  cout << endl;
  while(!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }

  return 0;
}