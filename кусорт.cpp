void qsort(int *a, int n){
	if(n <= 1)
		return ;
	int c = a[rand () % n];
	int j = 0;int cnt = 0;
	for(int i = 0; i < n; i++) {
		if(a[i] == c) {
			cnt++;
		}
		if(a[i] < c || (a[i] == c && cnt % 2 == 1)) {
			swap(a[i], a[j]);
			j++; 
		}
	}
		qsort(a, j);
		qsort(a + j, n - j);
}


qsort(a,n);