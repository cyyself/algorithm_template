int qpow(int a, int b){
	int ans = 1;
	while(b>0){
		if(b % 2)ans = ans * a;
		b = b/2;
		a = a * a;
	}
	return ans;
}