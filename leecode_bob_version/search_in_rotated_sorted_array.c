

int search_in_rotated_sorted_array(int x, int A[], int num)
{
	int index; 
	for (index = 0; index < num; index++)
		if ( A[index] > A[index+1])
			break;
    return index;

}
