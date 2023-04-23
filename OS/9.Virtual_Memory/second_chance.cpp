#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
using ll = long long;

int main() {
    #ifndef ONLINE_JUDGE
    #define ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int max_frames, max_pages, pageFaults = 0;
    max_frames = 5;
    int frames[max_frames];
    bool second_change[max_frames];
    int pages[] = {7, 2, 3, 1, 2, 5, 3, 4 ,6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1};
    max_pages = sizeof(pages) / sizeof(pages[0]);
    list<pair<int, int>> leastRecent;
    unordered_map<int, list<pair<int, int>>::iterator> usedPage;
    vector<vector<int>> answer;
    for(int i = 0; i < max_frames; i++) {
        frames[i] = -1;
        second_change[i] = false;
    }
    // for(int i = 0; i < max_pages; i++) cin >> pages[i];
    int count = 0;
    for(int i = 0; i < max_pages; i++) {
        if(usedPage.find(pages[i]) == usedPage.end()) {
            ++pageFaults; 
            int index = count++;
            auto it = --leastRecent.end();
            if(usedPage.size() >= max_frames) {
                while(second_change[it->second]) {
                    second_change[it->second] = false;
                    if(it == leastRecent.begin()) it = --leastRecent.end();
                    else --it;
                }
                index = it->second;
                usedPage.erase(it->first);
                leastRecent.erase(it);
            } 
            leastRecent.push_front({pages[i], index});
            frames[index] = pages[i];
            usedPage[pages[i]] = leastRecent.begin();
            answer.push_back(vector<int>(frames, frames + max_frames));
        }
        else {
            second_change[usedPage[pages[i]]->second] = true;
            answer.push_back(vector<int>(max_frames, -1));
        }
    }
    for(int i = 0; i < max_pages; i++) {
        cout << setw(3) << left << pages[i];
    }
    cout << endl;
    for(int i = 0; i < max_pages; i++) {
        cout << setw(3) << left << '-';
    }
    cout << endl;
    for(int j = 0; j < answer[0].size(); j++) {
        for(int i = 0; i < answer.size(); i++) {
            std::cout << setw(3) << left;
            if(answer[i][j] != -1) cout << answer[i][j];
            else cout << ' ';
        }
        std::cout << endl;
    }
    std::cout << "Page Faults: " << pageFaults << endl;

    return 0;
}