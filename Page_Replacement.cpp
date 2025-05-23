#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>
#define ll long long
using namespace std;

#define LENGTH  13
#define MAX_PAGE_NUMBER  7
#define FRAME_NUMBER  3
int pages[LENGTH] = { 1 , 2 , 3 , 1 , 4 , 5 , 2 , 1 , 2 , 6 , 7 , 3 , 2 };
int frames[FRAME_NUMBER];

void FIFO(void)
{
	cout << "\n FIFO \n";
	int k, c, current_page, counter = 0;
	for (k = 0; k < FRAME_NUMBER; k++) {
		frames[k] = -1;
	}
	int victim = 0;
	for (int page_no = 0; page_no < LENGTH; page_no++)
	{
		int done = 0, exist = 0;
		current_page = pages[page_no];
		for (k = 0; k < FRAME_NUMBER; k++)
			if (frames[k] == current_page)
			{
				exist = 1;
				cout << "\n" << page_no << "\t" << current_page;
				break;
			}
		if (exist == 0)
		{
			for (k = 0; k < FRAME_NUMBER; k++)
				if (frames[k] == -1)
				{
					done = 1;
					frames[k] = current_page;
					cout << "\n" << page_no << "\t" << current_page << "\t\t";
					for (c = 0; c < FRAME_NUMBER; c++) {
						cout << frames[c] << "\t";
					}
					counter++;
					break;
				}
		}
		if ((exist == 0) && (done == 0))
		{
			frames[victim] = current_page;
			victim = (victim + 1) % FRAME_NUMBER;
			cout << "\n" << page_no << "\t" << current_page << "\t\t";
			for (c = 0; c < FRAME_NUMBER; c++) {
				cout << frames[c] << "\t";
			}
			counter++;
		}
	}
	cout << "\nNumber of page fault = " << counter << "\n";
}

void optimal(void)
{
	cout << "\n Optimal \n";
	int k, c, current_page, counter = 0;
	for (k = 0; k < FRAME_NUMBER; k++)			frames[k] = -1;
	for (int page_no = 0; page_no < LENGTH; page_no++)
	{
		int done = 0, exist = 0;
		current_page = pages[page_no];
		for (k = 0; k < FRAME_NUMBER; k++)
			if (frames[k] == current_page)
			{
				exist = 1;
				cout << "\n" << page_no << "\t" << current_page;
				break;
			}
		if (exist == 0)
		{
			for (k = 0; k < FRAME_NUMBER; k++)
				if (frames[k] == -1)
				{
					done = 1;
					frames[k] = current_page;
					cout << "\n" << page_no << "\t" << current_page << "\t\t";
					for (c = 0; c < FRAME_NUMBER; c++)			cout << frames[c] << "\t";
					counter++;
					break;
				}
		}
		if ((exist == 0) && (done == 0))
		{
			int next_use[FRAME_NUMBER];
			for (k = 0; k < FRAME_NUMBER; k++)		next_use[k] = LENGTH + 1;

			for (k = 0; k < FRAME_NUMBER; k++)
			{
				for (c = page_no; c < LENGTH; c++)
					if (pages[c] == frames[k]) { next_use[k] = c; break; }
			}
			int victim = 0;
			for (k = 1; k < FRAME_NUMBER; k++)
				if (next_use[k] > next_use[victim]) { victim = k; }

			frames[victim] = current_page;
			cout << "\n" << page_no << "\t" << current_page << "\t\t";
			for (c = 0; c < FRAME_NUMBER; c++)			cout << frames[c] << "\t";
			counter++;
		}
	}
	cout << "\nNumber of page fault = " << counter << "\n";
}

void LRU(void)
{
	cout << "\n LRU \n";
	int k, c, current_page, counter = 0;
	for (k = 0; k < FRAME_NUMBER; k++)			frames[k] = -1;
	for (int page_no = 0; page_no < LENGTH; page_no++)
	{
		int done = 0, exist = 0;
		current_page = pages[page_no];
		for (k = 0; k < FRAME_NUMBER; k++)
			if (frames[k] == current_page)
			{
				exist = 1;
				cout << "\n" << page_no << "\t" << current_page;
				break;
			}
		if (exist == 0)
		{
			for (k = 0; k < FRAME_NUMBER; k++)
				if (frames[k] == -1)
				{
					done = 1;
					frames[k] = current_page;
					cout << "\n" << page_no << "\t" << current_page << "\t\t";
					for (c = 0; c < FRAME_NUMBER; c++)			cout << frames[c] << "\t";
					counter++;
					break;
				}
		}
		if ((exist == 0) && (done == 0))
		{
			int prev_use[FRAME_NUMBER];
			for (k = 0; k < FRAME_NUMBER; k++)		prev_use[k] = -1;

			for (k = 0; k < FRAME_NUMBER; k++)
			{
				for (c = page_no; c >= 0; c--)
					if (pages[c] == frames[k]) { prev_use[k] = c; break; }
			}
			int victim = 0;
			for (k = 1; k < FRAME_NUMBER; k++)
				if (prev_use[k] < prev_use[victim]) { victim = k; }

			frames[victim] = current_page;
			cout << "\n" << page_no << "\t" << current_page << "\t\t";
			for (c = 0; c < FRAME_NUMBER; c++)			cout << frames[c] << "\t";
			counter++;
		}
	}
	cout << "\nNumber of page fault = " << counter << "\n";
}

void LFU(void)
{
	cout << "\n LFU \n";
	int k, c, current_page, counter = 0;
	for (k = 0; k < FRAME_NUMBER; k++) frames[k] = -1;
	int number_of_use[MAX_PAGE_NUMBER + 1];
	for (k = 0; k <= MAX_PAGE_NUMBER; k++)		number_of_use[k] = 0;

	for (int page_no = 0; page_no < LENGTH; page_no++)
	{
		int done = 0, exist = 0;
		current_page = pages[page_no];
		for (k = 0; k < FRAME_NUMBER; k++)
			if (frames[k] == current_page)
			{
				exist = 1;
				cout << "\n" << page_no << "\t" << current_page;
				break;
			}
		if (exist == 0)
		{
			for (k = 0; k < FRAME_NUMBER; k++)
				if (frames[k] == -1)
				{
					done = 1;
					frames[k] = current_page;
					cout << "\n" << page_no << "\t" << current_page << "\t\t";
					for (c = 0; c < FRAME_NUMBER; c++)			cout << frames[c] << "\t";
					counter++;
					break;
				}
		}
		if ((exist == 0) && (done == 0))
		{
			int victim = 0;
			for (k = 1; k < FRAME_NUMBER; k++)
				if (number_of_use[frames[k]] < number_of_use[frames[victim]])
				{
					victim = k;
				}
			frames[victim] = current_page;
			cout << "\n" << page_no << "\t" << current_page << "\t" << number_of_use[current_page] << "\t";
			for (c = 0; c < FRAME_NUMBER; c++)			cout << frames[c] << "\t";
			counter++;
		}
		number_of_use[current_page]++;
	}
	cout << "\nNumber of page fault = " << counter << "\n";
}

void main(void)
{
	FIFO();
	optimal();
	LRU();
	LFU();
}
