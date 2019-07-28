void work_R() {
	stack <int> s;
	for (int i=1;i<=n;i++) {
		while (!s.empty()) {
			if (a[s.top()] > a[i]) {
				R[s.top()] = i - 1;
				s.pop();
			}
			else break;
		}
		s.push(i);
	}
	while (!s.empty()) {
		R[s.top()] = n;
		s.pop();
	}
}
void work_L() {
	stack <int> s;
	for (int i=n;i>=1;i--) {
		while (!s.empty()) {
			if (a[s.top()] > a[i]) {
				L[s.top()] = i + 1;
				s.pop();
			}
			else break;
		}
		s.push(i);
	}
	while (!s.empty()) {
		L[s.top()] = 1;
		s.pop();
	}
}
