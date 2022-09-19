
#include <math.h>
#include <map>
#include <vector>
#include <iostream>

// Example:
// Indices  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
// Values = 5, 1, 2, 3, 4, 5, 6, 5, 7, 8,  9,  3

// Purpose: This function searches a collection for a pair of identical integral values located within a given predefined range
// Input: Collections of numbers, range
// Output: true - at least one pair of such elements is found; false otherwise
bool FindTwoIdenticalNumbersWithinGivenRange(const std::vector<int>& collection, int range);

int main(int argc, char** argv)
{
	const int range = 2;
	std::vector<int> pair_exists = { 5, 1, 2, 3, 4, 5, 6, 5, 7, 8, 9, 3 };
	std::vector<int> pair_does_not_exist = { 5, 1, 2, 3, 4, 5, 6, 2, 7, 8, 9, 3 };

	if (FindTwoIdenticalNumbersWithinGivenRange(pair_exists, range))
		std::cout << "A pair within range " << range << " has been located\n";
	else
		std::cout << "Bad luck\n";

	if (FindTwoIdenticalNumbersWithinGivenRange(pair_does_not_exist, range))
		std::cout << "A pair within range " << range << " has been located\n";
	else
		std::cout << "Bad luck\n";

	return 0;
}


bool FindTwoIdenticalNumbersWithinGivenRange(const std::vector<int>& collection, int range)
{
	// Declare ordered associative container to store unique elements along with their associated indices
	std::map<int, int> ordered_map;

	// Traverse the collection of integral values
	for (int ind = 0; ind < collection.size(); ind++)
	{
		// Check to see whether the integral value already exists in the map
		std::map<int, int>::iterator found = ordered_map.find(collection[ind]);

		if (found == ordered_map.end())
		{
			// The unique integral value does NOT yet exist in the map

			// Insert a new pair (integral value, its index) in the map
			// ordered_map.insert(std::make_pair(collection[ind], ind));
			ordered_map.insert({ collection[ind], ind });
			
			// For testing
			//int val = collection[ind];
			//int val_ind = ordered_map[val];
		}
		else 
		{
			// The unique integral value already exists in the map

			// Check to see whether the two identical integral values are located no further apart than the predefined range
			// That is, the difference between the location of the indices of the two integral values in question is less or equal to the given range
			if (abs(ordered_map[collection[ind]] - ind) <= range)
			{
				return true;
			}

			// Update the index of the existing integral value 
			ordered_map[collection[ind]] = ind;
		}
	}

	return false;
}