struct value_block {
	int blk_sum[1000];
	int cnt[maxn];
	void clear() {
		for (int i=0;i<n;i++) cnt[i] = 0;
		for (int i=0;i<blk+1;i++) blk_sum[i] = 0;
	}
	value_block() {
		clear();
	}
	void add(int x) {
		if (x >= n) return;
		if (cnt[x] == 0) {
			blk_sum[x/blk] ++;
		}
		cnt[x] ++;
	}
	void del(int x) {
		if (x >= n) return;
		if (cnt[x] == 1) {
			blk_sum[x/blk] --;
		}
		cnt[x] --;
	}
	int mex() {
		for (int i=0;i<blk+1;i++) if (blk_sum[i] != blk) {
			for (int j=blk*i;j<blk*i+blk;j++) if (!cnt[j]) {
				return j;
			}
		}
		return -1;//inf
	}
};
