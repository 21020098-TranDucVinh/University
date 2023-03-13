#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Nhập số lượng tiến trình và tài nguyên
    int n, m;
    cout << "Nhap so luong tien trinh: ";
    cin >> n;
    cout << "Nhap so luong tai nguyen: ";
    cin >> m;
    
    // Khai báo các mảng cần thiết
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> request(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);
    vector<int> safe_sequence;
    vector<bool> finished(n, false);

    // Nhập phân bố tài nguyên hiện tại của các tiến trình
    cout << "Nhap phan bo tai nguyen hien tai cua tung tien trinh: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    // Nhập yêu cầu của các tiến trình
    cout << "Nhap yeu cau cua tung tien trinh: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> request[i][j];
        }
    }

    // Nhập số lượng tài nguyên có sẵn
    cout << "Nhap so luong tai nguyen co san: " << endl;
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool safe = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > available[j]) {
                        safe = false;
                        break;
                    }
                }
                if (safe) {
                    for (int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }
                    safe_sequence.push_back(i);
                    finished[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    // Kiểm tra nếu có chuỗi an toàn
    if (count == n) {
        cout << "Chuoi an toan: ";
        for (int i = 0; i < safe_sequence.size(); i++) {
            cout << "P" << safe_sequence[i];
            if (i != safe_sequence.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "Deadlock!" << endl;
    }

    return 0;
}
