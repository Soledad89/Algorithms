int binsearch(int x, int A[], int n)
{
	int low, mid, high;
	low = 0; 
	high = n-1;
	while (low <= high)
	{
		mid = (low + high)/2;
		if (x < A[mid])
			high = mid - 1;
		else if (x > A[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}



