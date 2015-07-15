int singleNumber2(int A[], int n){
	const int W = sizeof(int) * 8;
	int count[W];
	fill_n(&count[0], W, 0);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < W; j++){
			count[j] += (A[i] >> j) & 1;
			count[j] %= 3;
		}
	}

	int result = 0; 
	for(int i = 0; i < W; i++)
		result += (count[i] << i);

	return result;
}



