#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int main()
{
  cout << "Capacity: ";
  int capacity;
  cin >> capacity;

  int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
  int n = sizeof(pages) / sizeof(pages[0]);

  int frame[capacity][n] = {-1};
  bool checkPageFault[n] = {true};

  int page_faults = 0;

  unordered_map<int, int> indexes;

  for (int i = 0; i < n; i++)
  {
    vector<int> count(n, 0);

    if (i != 0)
    {
      for (int j = 0; j < capacity; j++)
      {
        frame[j][i] = frame[j][i - 1];
        if (frame[j][i] == pages[i])
        {
          checkPageFault[i] = false;
        }
      }
    }
    if (checkPageFault[i])
    {
      indexes[pages[i]] = i;

      int indexMax = 0;
      for (int j = 0; j < n; j++)
      {
        if (count[j] > count[indexMax])
        {
          indexMax = j;
        }
        else if (count[j] == count[indexMax])
        {
          for (int k = i; k >= 0; k--)
          {
            if (frame[j][k] != frame[j][i] || frame[indexMax][k] == -1)
            {
              break;
            }
            if (frame[indexMax][k] != frame[indexMax][i])
            {
              indexMax = j;
              break;
            }
          }
        }
      }
      frame[indexMax][i] = pages[i];
    }
  }

  cout << "\nTable";
  for (int i = 0; i < n; i++)
  {
    cout << "   " << pages[i];
  }
  for (int i = 0; i < capacity; i++)
  {
    cout << "\n  " << i << "  ";
    for (int j = 0; j < n; j++)
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
  cout << "\nSo luong page fault = " << page_faults;
  return 0;
}