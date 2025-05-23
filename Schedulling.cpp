#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>
#define ll long long
using namespace std;

struct process
{
	int num, arv, bur, pri;
};

#define SIZE 5
void sort_process(process*, int);
int FCFS(struct process*, int, int*);
int SJF_NP(struct process*, int, int*);
int SJF_P(struct process*, int, int*);
int Priority_NP(struct process*, int, int*);
int Priority_P(struct process*, int, int*);
int RR(struct process*, int, int, int*);

void main(void)
{
	struct process list1[SIZE] = { {1,0,1,3},{2,3,8,4},{3,4,5,2},{4,5,2,2},{5,8,4,1} };
	sort_process(list1, SIZE);
	int wait_time[SIZE] = { }, total_wait_time;
	cout << "\n FCFS\n";
	total_wait_time = FCFS(list1, SIZE, wait_time);
	cout << "\n SJF_NP\n";
	total_wait_time = SJF_NP(list1, SIZE, wait_time);
	cout << "\n SJF_P\n";
	total_wait_time = SJF_P(list1, SIZE, wait_time);
	cout << "\n Priority_NP\n";
	total_wait_time = Priority_NP(list1, SIZE, wait_time);
	cout << "\n Priority_P\n";
	total_wait_time = Priority_P(list1, SIZE, wait_time);
	cout << "\n RR\n";
	total_wait_time = RR(list1, SIZE, 3, wait_time);
}
class queue
{
private:
	int front, rear, counter, size;
	int* que;
public:
	queue(int ss)
	{
		size = ss;
		que = new int[size];
		front = rear = counter = 0;
	}
	void enqueue(int data)
	{
		que[rear] = data;
		rear = (rear + 1) % size;
		counter++;
	}
	int dequeue(void)
	{
		int temp;
		temp = que[front];
		front = (front + 1) % size;
		counter--;
		return temp;
	}
	bool is_full(void) { return counter == size; }
	bool is_empty(void) { return counter == 0; }
};


void sort_process(process* ptr, int n)
{
	int a, b;
	struct process temp;
	for (a = 0; a < n; a++)
	{
		for (b = a + 1; b < n; b++)
			if (ptr[a].arv > ptr[b].arv)
			{
				temp = ptr[a]; ptr[a] = ptr[b]; ptr[b] = temp;
			}
		cout << ptr[a].num << "\t" << ptr[a].arv << "\t" << ptr[a].bur << "\t" << ptr[a].pri << "\n";
	}
}
int FCFS(struct process* prs, int n, int* wt)
{
	struct process* list = new process[n];
	for (int a = 0; a < n; a++)		list[a] = prs[a];

	int twt = 0;
	int t = 0;
	for (int a = 0; a < n; a++)
	{
		while (list[a].bur > 0)
		{
			if (t >= list[a].arv)
			{
				cout << t << " ~ " << t + 1 << "\t\t" << list[a].num << "\n";
				list[a].bur--;
			}
			else		cout << t << " ~ " << t + 1 << "\t\t" << "NULL\n";
			t++;
		}
		wt[a] = t - prs[a].arv - prs[a].bur;   twt = twt + wt[a];
	}
	cout << "\n Waiting times = \n";
	for (int a = 0; a < n; a++)	cout << "P" << list[a].num << "\t" << wt[a] << "\n";
	cout << "Total waiting time = " << twt << "\n";
	return twt;
}

int SJF_NP(struct process* prs, int n, int* wt)
{
	struct process* list = new process[n];
	for (int a = 0; a < n; a++)		list[a] = prs[a];

	int twt = 0;
	int t = 0;
	int index_min, min_bur, still;
	still = 1;
	while (still == 1)
	{
		index_min = -1;
		min_bur = 1000;
		for (int a = 0; a < n; a++)
			if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].bur < min_bur))
			{
				min_bur = list[a].bur;  index_min = a;
			}

		//		cout << "min_index = " << index_min << "\t burst = " << min_bur << "\n";		
		if (index_min != -1)
		{
			while (list[index_min].bur > 0)
			{
				cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
				t++;
				list[index_min].bur--;
			}
			wt[index_min] = t - prs[index_min].arv - prs[index_min].bur;
			twt = twt + wt[index_min];
		}
		else
		{
			still = 0;
			for (int a = 0; a < n; a++)
				if (list[a].bur > 0)
				{
					still = 1;
					cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
					t++;
					break;
				}
		}
	}
	cout << "\n Waiting times = \n";
	for (int a = 0; a < n; a++)	cout << "P" << list[a].num << "\t" << wt[a] << "\n";
	cout << "Total waiting time = " << twt << "\n";
	return twt;
}

int Priority_NP(struct process* prs, int n, int* wt)
{
	struct process* list = new process[n];
	for (int a = 0; a < n; a++)		list[a] = prs[a];
	int twt = 0;

	int t = 0;
	int index_min, min_pri, still;
	still = 1;
	while (still == 1)
	{
		index_min = -1;
		min_pri = 1000;
		for (int a = 0; a < n; a++)
			if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].pri < min_pri))
			{
				min_pri = list[a].pri;  index_min = a;
			}

		if (index_min != -1)
		{
			while (list[index_min].bur > 0)
			{
				cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
				t++;
				list[index_min].bur--;
			}
			wt[index_min] = t - prs[index_min].arv - prs[index_min].bur;
			twt = twt + wt[index_min];
		}
		else
		{
			still = 0;
			for (int a = 0; a < n; a++)
				if (list[a].bur > 0)
				{
					still = 1;
					cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
					t++;
					break;
				}
		}
	}
	cout << "\n Waiting times = \n";
	for (int a = 0; a < n; a++)	cout << "P" << list[a].num << "\t" << wt[a] << "\n";
	cout << "Total waiting time = " << twt << "\n";
	return twt;
}

int SJF_P(struct process* prs, int n, int* wt)
{
	struct process* list = new process[n];
	for (int a = 0; a < n; a++)		list[a] = prs[a];

	int twt = 0;
	int t = 0;
	int index_min, min_bur, still;
	still = 1;
	while (still == 1)
	{
		index_min = -1;
		min_bur = 1000;
		for (int a = 0; a < n; a++)
			if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].bur < min_bur))
			{
				min_bur = list[a].bur;  index_min = a;
			}

		if (index_min != -1)
		{
			cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
			t++;
			list[index_min].bur--;
			if (list[index_min].bur == 0)
			{
				wt[index_min] = t - prs[index_min].arv - prs[index_min].bur;   twt = twt + wt[index_min];
			}
		}
		else
		{
			still = 0;
			for (int a = 0; a < n; a++)
				if (list[a].bur > 0)
				{
					still = 1;
					cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
					t++;
					break;
				}
		}
	}
	cout << "\n Waiting times = \n";
	for (int a = 0; a < n; a++)	cout << "P" << list[a].num << "\t" << wt[a] << "\n";
	cout << "Total waiting time = " << twt << "\n";
	return twt;
}

int Priority_P(struct process* prs, int n, int* wt)
{
	struct process* list = new process[n];
	for (int a = 0; a < n; a++)		list[a] = prs[a];

	int twt = 0;
	int t = 0;
	int index_min, min_pri, still;
	still = 1;
	while (still == 1)
	{
		index_min = -1;
		min_pri = 1000;
		for (int a = 0; a < n; a++)
			if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].pri < min_pri))
			{
				min_pri = list[a].pri;  index_min = a;
			}

		if (index_min != -1)
		{
			cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
			t++;
			list[index_min].bur--;
			if (list[index_min].bur == 0)
			{
				wt[index_min] = t - prs[index_min].arv - prs[index_min].bur;   twt = twt + wt[index_min];
			}
		}
		else
		{
			still = 0;
			for (int a = 0; a < n; a++)
				if (list[a].bur > 0)
				{
					still = 1;
					cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
					t++;
					break;
				}
		}
	}
	cout << "\n Waiting times = \n";
	for (int a = 0; a < n; a++)	cout << "P" << list[a].num << "\t" << wt[a] << "\n";
	cout << "Total waiting time = " << twt << "\n";
	return twt;
}

int RR(struct process* prs, int n, int quantum, int* wt)
{
	struct process* list = new process[n];
	for (int a = 0; a < n; a++)		list[a] = prs[a];

	int twt = 0;
	queue myque(n);
	int t = 0, still = 1, index = 0;
	int current;
	for (int k = index; k < n; k++)
		if (list[k].arv == 0) { myque.enqueue(k);  index++; }
	while ((index < n) || (myque.is_empty() == false))
	{
		if (myque.is_empty() == true)
		{
			cout << t << " ~ " << t + 1 << "\t\t" << "IDLE \n";
			t++;
		}
		else
		{
			current = myque.dequeue();
			for (int k = 1; k <= quantum; k++)
			{
				if (list[current].bur > 0)
				{
					cout << t << " ~ " << t + 1 << "\t\t" << list[current].num << "\n";
					t++;
					list[current].bur--;
				}
				else
				{
					wt[current] = t - prs[current].arv - prs[current].bur;
					twt = twt + wt[current];  break;
				}
			}
		}
		for (int k = index; k < n; k++)
			if (list[k].arv <= t) { myque.enqueue(k);  index++; }
		if (list[current].bur > 0)			myque.enqueue(current);
	}
	cout << "\n Waiting times = \n";
	for (int a = 0; a < n; a++)	cout << "P" << list[a].num << "\t" << wt[a] << "\n";
	cout << "Total waiting time = " << twt << "\n";
	return twt;
}

