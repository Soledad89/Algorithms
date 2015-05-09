#include <vector>
#include <unordered_map>

int longestConsecutive(const vector<int. &num)
{
	unordered_map<int, bool> used;
	int longest = 0;
	for (auto i : num)
	{
		if (used[i]) continue;
		int length = 0;
		used[i] = true;
		for (int j = i + 1; used.find(j) != used.end(); ++j)
		{
			used[j] = true;
			++length;
		}

		for (int j = i - 1; used.find(j) != used.end(); --j)
		{
			used[j] = true;
			++length;
		}
		longest = max(longest, length);
	}
	return longest;
}


