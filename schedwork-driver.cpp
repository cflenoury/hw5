// main() program to test your schedule function.
// Feel free to modify this program in any way you need for testing.
// It will not be graded. 
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"

using namespace std;

void printSchedule(const DailySchedule& sched);

int main()
{
    // Replace the matrix below with your test case
    AvailabilityMatrix avail = { 
        {1, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 0, 1},
				{1, 0, 0, 1}
    };
		
		// cout << "Printing size of availablity matrix: " << avail.size()<< endl;
		// int temp = avail[0].size();
		// cout << "Printing size of the first row of availablity matrix: " << temp << endl;
    
		DailySchedule sched;
    bool solutionFound = schedule(avail, 2, 2, sched);
    if(solutionFound)
    {
        printSchedule(sched);
    }
    else
    {
        cout << "No solution found!" << endl;
    }
    return 0;
}

void printSchedule(const DailySchedule& sched)
{
    int day = 0;
    for(auto s : sched)
    {
        cout << "Day " << day << ": ";
        for(auto nurse : s)
        {
            cout << nurse << " ";
        }
        cout << endl;
        day++;
    }
}
