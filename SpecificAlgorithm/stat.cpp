#include <map>
#include <string>
#include <iostream>
using namespace std;

int main() {
	map<string, int> words;
	map<string, int>::iterator iter;
	string t;
	while (cin >> t)
		words[t]++;
	for ( iter =words.begin(); iter != words.end(); iter++) 
		cout << iter->first << " "<< iter->second << "\n";

	return 0;
}

