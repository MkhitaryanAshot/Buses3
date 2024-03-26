#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Exercise1
{
public:
	void Execute()
	{
		int n;
		int m;

		cout << "Please enter the number of streets ";
		cin >> n;

		cout << "Please enter the number of crossroads ";
		cin >> m;

		int count = m;

		vector<vector<int>> streets;

		while (count != 0)
		{
			vector<int> street;

			int u, v, k;

			cout << "Please insert first crossroad ";
			cin >> u;

			cout << "Please insert second crossroad ";
			cin >> v;

			cout << "Please insert duration drive in minutes required through the street ";
			cin >> k;

			street.push_back(u);
			street.push_back(v);
			street.push_back(k);

			streets.push_back(street);

			cout << "Street was added";

			count--;
		}
	}

	vector<int> buses;

	void AddBuses()
	{
		static int c = 0;
		
		buses.push_back(c);
		c++;
		cout << "Bus " << c << " was added";
	}
};

