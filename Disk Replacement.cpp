#include <bits/stdc++.h>
using namespace std;

void FCFS(int val[], int n, int head) {
    int tot = 0;
    cout << head << " ";
    for (int i = 0; i < n; ++i) {
        tot += abs(val[i] - head);
        head = val[i];
        cout << head << " ";
    }
    cout << "total: " << tot << "\n";
}

void SSTF(int val[], int n, int head) {
    int tot = 0, current = head, steps[n - 1], temp[n];
    for (int i = 0; i < n; ++i) {
        temp[i] = val[i];
    }
    cout << head << " ";
    for (int i = 0; i < n; ++i) {
        int mini = 1e9, ind = -1;
        for (int j = 0; j < n; ++j) {
            if (temp[j] != -1) {
                int dist = abs(temp[j] - current);
                if (dist < mini) {
                    mini = dist;
                    ind = j;
                }
            }
        }
        tot += mini;
        head = temp[ind];
        cout << head << " ";
        temp[ind] = -1;
    }
    cout << "total: " << tot << "\n";
}

void SCAN(int val[], int n, int head, int maxi) {
    int left[n + 1], right[n + 1];
    int l = 0, r = 0, tot = 0;
    right[r++] = maxi;
    for (int i = 0; i < n; i++) {
        if (val[i] <= head)
            left[l++] = val[i];
        else
            right[r++] = val[i];
    }
    
    sort(left, left + l);
    sort(right, right + r);

    cout << head << " ";
    for (int i = 0; i < r; i++) {
        int move = abs(head - right[i]);
        head = right[i];
        cout << head << " ";
        tot += move;
    }
    tot += abs(maxi - left[0]);
    for (int i = l - 1; i >= 0; i--) {
        int move = abs(head - left[i]);
        head = left[i];
        cout << head << " ";
        tot += move;
    }
    cout << "total: " << tot << "\n";
}

void CSCAN(int val[], int n, int head, int maxi) {
    int left[n + 1], right[n + 1];
    int l = 0, r = 0;
    int tot = 0;
    left[l++] = 0;
    right[r++] = maxi;
    for (int i = 0; i < n; i++) {
        if (val[i] <= head)
            left[l++] = val[i];
        else
            right[r++] = val[i];
    }

    sort(left, left + l);
    sort(right, right + r);
    tot += maxi;
    cout << head << " ";
    for (int i = 0; i < r; i++) {
        int move = abs(head - right[i]);
        tot += move;
        head = right[i];
        cout << head << " ";
        }

    for (int i = 0; i < l; i++) {
        int move = abs(head - left[i]);
        tot += move;
        head = left[i];
        cout << head << " ";
    }
    cout << "total: " << tot << "\n";
}



void CLOOK(int val[], int n, int head) {
    int left[n + 1], right[n + 1];
    int l = 0, r = 0;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        if (val[i] <= head)
            left[l++] = val[i];
        else
            right[r++] = val[i];
    }

    sort(left, left + l);
    sort(right, right + r);

    cout << head << " ";
    for (int i = 0; i < r; i++) {
        int move = abs(head - right[i]);
        tot += move;
        head = right[i];
        cout << head << " ";
        }

    for (int i = 0; i < l; i++) {
        int move = abs(head - left[i]);
        tot += move;
        head = left[i];
        cout << head << " ";
    }
    cout << "total: " << tot << "\n";
}


int main() {
    const int MAX_SIZE = 100;
    int val[MAX_SIZE];
    int value;
    int n = 0;

    int head;
    cout << "Enter the Head value :";
    cin >> head;

    //FCFS(val, n, head);
    SSTF(val, n, head);
    //SCAN(val, n, head, 199);
    //CSCAN(val, n, head, 199);
    //CLOOK(val, n, head);
    return 0;
}
