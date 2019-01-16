namespace cyy {
	bool gets(char *s) {
		char c = getchar();
		if (c == EOF) return false;
		while (c != '\n' && c != EOF) {
			*s = c;
			s ++;
			c = getchar();
		}
		*s = '\0';
		return true;
	}
}
