#include <iostream>
#include <vector>
using namespace std;
int main()
{
	cout << "Nhap so luong frame: ";
	int n;
	cin >> n;

	cout << "Nhap do dai cua chuoi: ";
	int l;
	cin >> l;

	cout << "Nhap chuoi: ";
	vector<int> page(l);
	for (int i = 0; i < l; i++)
	{
		cin >> page[i];
	}

	vector<vector<int>> frame(n, vector<int>(l, -1));
	vector<bool> checkPageFault(l, true);
	for (int i = 0; i < l; i++)
	{
		vector<int> count(n, 0);
		if (i != 0)
		{
			for (int j = 0; j < n; j++)
			{
				frame[j][i] = frame[j][i - 1];
				if (frame[j][i] == page[i])
				{
					checkPageFault[i] = false;
				}
			}
		}
		if (checkPageFault[i])
		{
			for (int j = 0; j < n; j++)
			{
				// if (frame[j][i] == -1)
				// {
				//     count[i] = l;
				// }
				for (int k = i - 1; k >= 0; k--)
				{
					if (frame[j][i] == page[k])
					{
						count[j]++;
					}
				}
			}
			int indexMin = 0;
			for (int j = 0; j < n; j++)
			{
				if (count[j] < count[indexMin])
				{
					indexMin = j;
				}
				else if (count[j] == count[indexMin])
				{
					for (int k = i; k >= 0; k--)
					{
						if (frame[j][k] != frame[j][i] || frame[indexMin][k] == -1)
						{
							break;
						}
						if (frame[indexMin][k] != frame[indexMin][i])
						{
							indexMin = j;
							break;
						}
					}
				}
			}
			frame[indexMin][i] = page[i];
		}
	}

	cout << "\nframe";
	for (int i = 0; i < l; i++)
	{
		cout << "   " << page[i];
	}
	for (int i = 0; i < n; i++)
	{
		cout << "\n  " << i << "  ";
		for (int j = 0; j < l; j++)
		{
			if (frame[i][j] != -1 && checkPageFault[j])
			{
				cout << "   " << frame[i][j];
			}
			else
			{
				cout << "    ";
			}
		}
	}
	int pageFault = 0;
	for (int i = 0; i < l; i++)
	{
		if (checkPageFault[i])
		{
			pageFault++;
		}
	}
	cout << "\nSo luong fage fault = " << pageFault;
	return 0;
}