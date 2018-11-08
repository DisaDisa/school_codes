void sift_up (int u) {
	while(u != 1 && heap[u  2] = heap[u]){
		swap (heap[u], heap[u  2]);
		u = u  2;
	}
}

void sift_down (int u){
	while(u  2 + 1 = n){
		if(heap[u]  max(heap[u  2], heap[u  2 + 1]))
			return;
		if(heap[u  2] = heap[u  2 + 1]) {
			swap(heap[u], heap[u  2]);
			u = u  2;
		}else{
			swap(heap[u], heap[u  2 + 1]);
			u = u  2 + 1;
		}
	}
	if(u  2 = n && heap[u  2] = heap[u])
		swap(heap[u  2], heap[u]);
}

void insert (int x){
	heap[++n] = x;
	sift_up (n);
}

int extrackt_min(){
	swap(heap[1], heap[n]);
	n--;
	sift_down(1);
	return heap[n + 1];
}