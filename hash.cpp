struct Hash {                        
    vector <long long> h1;
    vector <long long> h2;
    static int const P = 33533;
    static int const M1 = 999999937;
    static int const M2 = 1000000007;
    static int const M = 100500;
   	vector <long long> POWS1, POWS2;
    	
    Hash(string const & s) : h1(s.size()), h2(s.size()), POWS1(M), POWS2(M) {
		POWS1[0] = POWS2[0] = 1;
		for (int i = 1; i < M; i++) {
	 		POWS1[i] = POWS1[i - 1] * P % M1;
	 		POWS2[i] = POWS2[i - 1] * P % M2;
		}
    	long long c1 = 0;
    	long long c2 = 0;
    	for (size_t i = 0; i < s.length(); i++) {
    		c1 = c1 * P + s[i];
    	 	c2 = c2 * P + s[i];
    	 	c1 %= M1;
    	 	c2 %= M2;
    	 	h1[i] = c1;
    	 	h2[i] = c2;
    	}
    }

    long long getHash(int l, int r) const {
   		long long c1 = h1[r - 1];
    	long long c2 = h2[r - 1];
    	if (l > 0) {
    		c1 -= POWS1[r - l] * h1[l - 1] % M1;
    	 	c2 -= POWS2[r - l] * h2[l - 1] % M2;
    	 	if (c1 < 0) c1 += M1;
    	 	if (c2 < 0) c2 += M2;
    	}
    	return (c1 << 32) | c2;
	}
};
