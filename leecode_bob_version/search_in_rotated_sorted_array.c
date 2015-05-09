

int search_in_rotated_sorted_array(int x, int A[], int num)
{
    int first = 0, last = num;
    while (first != last)
    {
        const int mid = first + (last - first) / 2;
        if (A[mid] == x)
            return mid;
        if (A[first] <= A[mid])
        {
            if (A[first] <= x && x < A[mid])
                last = mid;
            else
                first = mid + 1;
        }
        else
        {
            if (A[mid] < x && x <= A[last - 1])
                first = mid - 1;
            else
                last = mid;
        }
    }
    return -1;

}
