#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>
#define ll long long
using namespace std;

#define PN 5   
#define RN 3	

int alloc[PN][RN] = { {0,2,0} , {2,0,0} , {3,0,2} , {2,1,1} , {0,0,2} };
int maximum[PN][RN] = { {7,5,3} , {3,2,2} , {9,0,2} , {2,2,2} , {4,3,3} };
int available[RN] = { 3,2,2 };
int need[PN][RN];
int request[RN + 1] = { 0 , 0, 0 , 2 };
int test[PN + 1][RN + 1];
int p, r;

void calculate_need(void)
{
	cout << "The need matrix: \n \t";
	for (r = 0; r < RN; r++)
		cout << "R" << r << "\t";
	cout << "\n";

	for (p = 0; p < PN; p++)
	{
		cout << "P" << p << "\t";
		for (r = 0; r < RN; r++)
		{
			need[p][r] = maximum[p][r] - alloc[p][r];
			cout << need[p][r] << "\t";
		}
		cout << "\n";
	}
}

bool is_safe(void)
{
	int flag;
	int counter = 0;
	int finish[PN] = { };
	int tempavail[RN];
	for (r = 0; r < RN; r++)
		tempavail[r] = available[r];
	do {
		flag = 0;
		for (p = 0; p < PN; p++) {
			if (finish[p] == 0) {
				for (r = 0; r < RN; r++) {
					if (need[p][r] > tempavail[r]) {
						break;
					}
				}
				if (r == RN) {
					finish[p] = 1;
					cout << "\nP" << p << "\t";
					for (r = 0; r < RN; r++)
					{
						tempavail[r] += alloc[p][r];
						cout << tempavail[r] << "\t";
					}
					flag = 1;
					counter++;
				}
			}
		}
	} while (flag == 1);
	if (counter == PN) {
		cout << "\n System is safe \n";
		return 1;
	}
	else {
		cout << "\n System is unsafe \n";
		return 0;
	}
}

bool test_safe(void)
{
	int tempneed[RN], tempalloc[RN], tempavail[RN], tp, save;
	tp = request[0];
	for (r = 0; r < RN; r++)
	{
		tempneed[r] = need[tp][r];
		tempalloc[r] = alloc[tp][r];
		tempavail[r] = available[r];
		need[tp][r] = need[tp][r] - request[r + 1];
		alloc[tp][r] = alloc[tp][r] + request[r + 1];
		available[r] = available[r] - request[r + 1];
	}
	if (is_safe() == true) { cout << "\nThe request is accepted because the system will still safe\n";  return true; }
	else
	{
		cout << "\nThe request is rejected because the system will be unsafe\n";
		for (r = 0; r < RN; r++)
		{
			need[tp][r] = tempneed[r];
			alloc[tp][r] = tempalloc[r];
			available[r] = tempavail[r];
		}
		return false;
	}
}


void main(void)
{
	calculate_need();
	is_safe();
	test_safe();
}


