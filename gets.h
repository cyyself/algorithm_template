namespace cyy {
	void gets(char *s) {
		char c = getchar();
		while (c != '\n') {
			*s = c;
			s ++;
			c = getchar();
		}
		*s = '\0';
	}
}
