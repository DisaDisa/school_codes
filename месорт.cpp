void merge(int i, int j, int m, int r, int l) {
	int k = 0;
	while (i <= m && j <= r){
		if (a[i].n <= a[j].n) {
			b[k++] = a[i++];
		} else {
			b[k++] = a[j++];
		}
	}
	while (i <= m) {
		b[k++]=a[i++];
	}
	while (j <= r) {
		b[k++] = a[j++];
	}
	k = 0;
	for (i = l; i <= r; i++) {
		a[i] = b[k++];
	}
}

void qsort(int l, int r){
	if(l == r)
		return ;
	int m = (l + r) / 2;
	qsort(l, m);
	qsort(m + 1, r);
	merge(l, m + 1, m, r, l);
}

qsort(0,q-1);