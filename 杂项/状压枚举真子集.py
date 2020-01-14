def f(x):
	s = x
	while (s):
		s = x & (s - 1)
		print(bin(s))
