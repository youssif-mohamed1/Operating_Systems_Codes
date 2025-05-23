#include <iostream>
using namespace std;

void FCFS(int values[], int size, int head) {
    int totalSteps = 0;
    cout << "-----FCFS-----\n";
    cout << "Access Steps:\n";
    cout << head << " -> ";
    totalSteps += abs(values[0] - head);

    for (int i = 0; i < size - 1; ++i) {
        cout << values[i] << " -> ";
        totalSteps += abs(values[i + 1] - values[i]);
    }
    cout << values[size - 1] << "\n";

    cout << "Movement of each step:\n";
    cout << "0";
    for (int i = 0; i < size; ++i) {
        int movement = abs(values[i] - head);
        cout << " + " << movement;
        head = values[i];
    }
    cout << " = " << totalSteps << "\n";
}

void SSTF(int values[], int size, int head) {
    cout << "-----SSTF-----\n";
    cout << "Access Steps:\n";

    int totalSteps = 0;
    int current = head;
    int steps[size - 1];

    int valuesCopy[size];
    for (int i = 0; i < size; ++i) {
        valuesCopy[i] = values[i];
    }

    for (int i = 0; i < size; ++i) {
        int minDistance = 99999999;
        int index = -1;

        for (int j = 0; j < size; ++j) {
            if (valuesCopy[j] != -1) {
                int distance = abs(valuesCopy[j] - current);
                if (distance < minDistance) {
                    minDistance = distance;
                    index = j;
                }
            }
        }

        totalSteps += minDistance;
        steps[i] = minDistance;
        cout << current << " -> ";
        current = valuesCopy[index];
        valuesCopy[index] = -1;
    }
    cout << current << "\n";

    cout << "Movement of each step:\n";
    cout << "0";
    for (int i = 0; i < size - 1; ++i) {
        cout << " + " << steps[i];
    }
    cout << " = " << totalSteps << "\n";
}

void SCAN(int values[], int size, int head, int maxTrack) {
    int left[size + 1], right[size + 1], result[size + 2];
    int lc = 0, rc = 0, resc = 0;
    int totalSteps = 0, curr;
    int steps[size + 2];

    result[resc] = head;
    steps[resc++] = 0;

    right[rc++] = maxTrack;

    for (int i = 0; i < size; i++) {
        if (values[i] < head)
            left[lc++] = values[i];
        else
            right[rc++] = values[i];
    }

    sort(left, left + lc);
    sort(right, right + rc);

    int phead = head;

    for (int i = 0; i < rc; i++) {
        curr = right[i];
        result[resc] = curr;
        steps[resc] = abs(curr - phead);
        totalSteps += steps[resc];
        phead = curr;
        resc++;
    }

    for (int i = lc - 1; i >= 0; i--) {
        curr = left[i];
        result[resc] = curr;
        steps[resc] = abs(curr - phead);
        totalSteps += steps[resc];
        phead = curr;
        resc++;
    }

    cout << "-----SCAN-----\n";
    cout << "Access Steps:\n";
    cout << result[0];
    for (int i = 1; i < resc; i++) {
        cout << " -> " << result[i];
    }
    cout << "\nMovement of each step:\n";
    cout << steps[0];
    for (int i = 1; i < resc; i++) {
        cout << " + " << steps[i];
    }
    cout << " = " << totalSteps << "\n";
}

void CSCAN(int values[], int size, int head, int maxTrack) {
    int left[size + 1], right[size + 1], result[size + 2];
    int lc = 0, rc = 0, resc = 0;
    int totalSteps = 0, curr;
    int steps[size + 2];

    result[resc] = head;
    steps[resc++] = 0;

    left[lc++] = 0;
    right[rc++] = maxTrack;

    for (int i = 0; i < size; i++) {
        if (values[i] < head)
            left[lc++] = values[i];
        else
            right[rc++] = values[i];
    }

    sort(left, left + lc);
    sort(right, right + rc);

    int phead = head;

    for (int i = 0; i < rc; i++) {
        curr = right[i];
        result[resc] = curr;
        steps[resc] = abs(curr - phead);
        totalSteps += steps[resc];
        phead = curr;
        resc++;
    }

    for (int i = 0; i < lc; i++) {
        curr = left[i];
        result[resc] = curr;
        steps[resc] = abs(curr - phead);
        totalSteps += steps[resc];
        phead = curr;
        resc++;
    }

    cout << "-----C-SCAN-----\n";
    cout << "Access Steps:\n";
    cout << result[0];
    for (int i = 1; i < resc; i++) {
        cout << " -> " << result[i];
    }
    cout << "\nMovement of each step:\n";
    cout << steps[0];
    for (int i = 1; i < resc; i++) {
        cout << " + " << steps[i];
    }
    cout << " = " << totalSteps << "\n";
}



void CLOOK(int values[], int size, int head) {
    int left[size + 1], right[size + 1], result[size + 2];
    int lc = 0, rc = 0, resc = 0;
    int totalSteps = 0, curr;
    int steps[size + 2];

    result[resc] = head;
    steps[resc++] = 0;

    for (int i = 0; i < size; i++) {
        if (values[i] < head)
            left[lc++] = values[i];
        else
            right[rc++] = values[i];
    }

    sort(left, left + lc);
    sort(right, right + rc);

    int phead = head;

    for (int i = 0; i < rc; i++) {
        curr = right[i];
        result[resc] = curr;
        steps[resc] = abs(curr - phead);
        totalSteps += steps[resc];
        phead = curr;
        resc++;
    }

    for (int i = 0; i < lc; i++) {
        curr = left[i];
        result[resc] = curr;
        steps[resc] = abs(curr - phead);
        totalSteps += steps[resc];
        phead = curr;
        resc++;
    }

    cout << "-----C-LOOK-----\n";
    cout << "Access Steps:\n";
    cout << result[0];
    for (int i = 1; i < resc; i++) {
        cout << " -> " << result[i];
    }
    cout << "\nMovement of each step:\n";
    cout << steps[0];
    for (int i = 1; i < resc; i++) {
        cout << " + " << steps[i];
    }
    cout << " = " << totalSteps << "\n";
}


int main() {
    ifstream file("mydata.txt");

    if (!file.is_open()) {
        cout << "Failed to open the file: " << strerror(errno) << endl;
        return 1;
    }

    const int MAX_SIZE = 100;
    int values[MAX_SIZE];
    int value;
    int size = 0;

    while (file >> value && size < MAX_SIZE) {
        values[size] = value;
        size++;
    }

    file.close();

    int head;
    cout << "Enter the Head value :";
    cin >> head;

    //FCFS(values, size, head);
    SSTF(values, size, head);
    //SCAN(values, size, head, 199);
    //CSCAN(values, size, head, 199);
    //CLOOK(values, size, head);
    return 0;
}
