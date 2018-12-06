int strmin(char *s) {//给一个字符串s，返回字典序最小循环子串的开始位置
	int i=0,j=1,k=0;
	int len = strlen(s);
	while (i < len && j < len && k < len) {
		int d = s[(i+k)%len] - s[(j+k)%len];
		if (d == 0) k ++;
		else {
			if (d > 0) i = i + k + 1;
			else j = j + k + 1;
			if (i == j) j ++;
			k = 0;
		}
	}
	return min(i,j);
}
