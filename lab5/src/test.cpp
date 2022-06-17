# include<iostream>
# include<math.h>
# include<windows.h>
# include<vector>
# include<algorithm>
# include<cstdlib>
# include<ctime>
# include<random>

using namespace std;

int main()
{
	vector<double> v(10,3);
	v[8] = 1;
	v[6] = 2;
	// print all the values of v
	printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	v.pop_back();
	printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	v.push_front(1212);
	printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	return 0;
}