int remove_duplicates2(int a[], int num)
{
	if (num == 0) return 0;
	int i, flag = 0, index = 0;
	for (i = 1; i < num; i++)
		if (a[index] != a[i])
			a[++index] = a[i];
		else{
			if (a[i] == a[i+1])
				i++;
			else
				a[++index] = a[i];
		}

	return index+1;
}

int remove_duplicates3(int a[], int num)
{
	if (num < 3) return num;
	int i, index = 2;
	for (i = 2; i < num; i++)
		if (a[i] != a[index-2])
			a[index++] = a[i];
	return index;
}

