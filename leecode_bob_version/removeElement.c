int removeElement(int A[], int n, int target)
{
	int index = 0;
	int i;
	for (i = 0; i < n; ++i)
	{
		if (A[i] != elem) 
			A[index++] = A[i];
	}
	return index;
}

