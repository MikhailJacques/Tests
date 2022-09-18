
#include <math.h>
#include <map>
#include <vector>
#include <iostream>

bool ArrayProcessing(const std::vector<int>& collection, int range);

int main(int argc, char** argv)
{
	int range = 2;
	std::vector<int> kewl = { 5, 1, 2, 3, 4, 5, 6, 5, 7, 8, 9, 3 };

	bool result = ArrayProcessing(kewl, range);

	std::cout << result;

	return 0;

}

// Find a pair of elements 
// Indices  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// Values = 5, 1, 2, 3, 4, 5, 6, 5, 7, 8, 9, 3
// 
// Range = 3
bool ArrayProcessing(const std::vector<int>& collection, int range)
{
	std::map<int, int> map1;

	for (int ind = 0; ind < collection.size(); ind++)
	{
		int val = collection[ind];

		std::map<int, int>::iterator found = map1.find(val);

		if (found == map1.end())
		{
			map1.insert({ collection[ind], ind });

			int temp1 = collection[ind];
			int temp2 = map1.at(collection[ind]);
		}
		else
		{
			if (abs(map1[collection[ind]] - ind) < range)
				return true;

			map1.insert({ collection[ind], ind });
		}
	}

	return false;
}


//for (auto it = collection.rbegin(); it != collection.rend(); it++)