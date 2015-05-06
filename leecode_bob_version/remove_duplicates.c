
int remove_duplicates(int a[], int num)
{
	if (num == 0) return 0;
	int i, index = 0;
	for (i = 1; i < num; i++)
		if (a[index] != a[i])
			a[++index] = a[i];
	return index+1;
}

