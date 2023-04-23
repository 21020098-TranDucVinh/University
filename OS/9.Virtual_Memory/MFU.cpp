#include <iostream>
#include <vector>
using namespace std;
int main()
{
    cout << "Nhap do dai cua chuoi: ";
    int l;
    cin >> l;
    cout << "Chuoi random: ";
    vector<int> page(l);
    for (int i = 0; i < l; i++)
    {
        page[i] = rand() % 10;
        cout << page[i] << " ";
    }
    cout << endl;
    int n = 1;
    while (n <= 7)
    {
        cout << "So luong frame hien tai: " << n << endl;

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
                    if (frame[j][i] == -1)
                    {
                        count[j] = n;
                    }
                    for (int k = i - 1; k >= 0; k--)
                    {
                        if (frame[j][i] == page[k])
                        {
                            count[j]++;
                        }
                    }
                }
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
                frame[indexMax][i] = page[i];
            }
        }

        cout << "frame";
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
        cout << "\nSo luong fage fault = " << pageFault << endl
             << endl;
        n++;
    }

    return 0;
}