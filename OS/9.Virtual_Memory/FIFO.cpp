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
    int count = 0;
    vector<bool> checkPageFault(l, true);
    for (int i = 0; i < l; i++)
    {
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
            frame[count][i] = page[i];
            count = (count + 1) % n;
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
     for (int i = 0; i < l; i++){
        if(checkPageFault[i]){
            pageFault++;
        }
     }
    cout << "\nSo luong fage fault = " << pageFault;
    return 0;
}