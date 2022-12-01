#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool isSingleShift( std::vector<Worker_T> vec, Worker_T w ){//Ensure worker is scheduled once for the week

	for(unsigned i = 0; i < vec.size()-1; i++){//Compare w with every other worker scheduled for that day to make sure they are not double booked
		if(w == vec[i]){//If a previous entry has the same worker ID, the worker has been double booked
			return false;
		}
		//Note: we don't look at the last item in the vector because it is the newly added item
	}
	return true;
}

bool isUnderMax( size_t maxShifts, DailySchedule& sched, Worker_T w ){//Ensure worker has not reached max number of shifts for the period

	//Go through schedule to make sure worker has not reached max schedulings for the period
	size_t bookings = 0;//Track bookings for the worker for the period
	for(auto& day: sched) {//Take each vector in sched
		bookings += count( day.begin(), day.end(), w );//Count the number of occurences of worker w in the vector (should be 1 each time since there should be no double bookings)
		if(bookings > maxShifts){//If the bookings of the worker exceed the maxshifts, we must undo the scheduling
			return false;
		}
	}
	return true;//If we make it here than it is ok for the worker to be booked

}

bool schedHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched) {  

	//BC - Fully finished schedule
  if( sched.size() == avail.size() ){//Sched has the same number of rows as avail (n)
		if( sched[sched.size()-1].size() == dailyNeed ){//Sched's final row is the same size as avail's final row (d)
    	return true;//The final placement is valid [n][d] and the solution has been achieved
		}
  }

	//BC - Fully finished row in sched
  if(sched[sched.size()-1].size() == dailyNeed){//The last row of sched is the same size as any row of avail
 
		//Add another row to sched
		std::vector<Worker_T> temp;//Creating a new vector of Workers
		sched.push_back(temp);//Adding empty vector to sched
    return schedHelper(avail, dailyNeed, maxShifts, sched);//recursive call
  }

  //Iterate through each worker's availablity for the day we're scheduling for (the row)
	for(unsigned i = 0; i < avail[0].size() /* =k */; i++){//Tries all workers by thier index
		
		//Create a Worker_T variable from the index (worker's ID)
		Worker_T temp = i;

		//Add to the end of the current (last) row of sched
		sched[sched.size()-1].push_back(temp);
										//Last row, Last element in last row
		if( isSingleShift(sched[sched.size()-1], i ) && isUnderMax( maxShifts, sched, i ) && (avail[sched.size()-1][i]) ){//Check if this is a valid value for the cell
			bool status = schedHelper(avail, dailyNeed, maxShifts, sched);//recursive call with next cell in sequence
			if( status ){
				return true;//final arrangement returns true
			}   
		}

		sched[sched.size()-1].pop_back();//Remove worker from sched before trying next worker configuration      
  }

	//If you have exhausted all values for the cell, try a different number in the previous cell
	//But if the previous cell is in a different row, delete the current row/vector
	if(sched[sched.size()-1].empty()){
		sched.pop_back();
	}

  return false;
  
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	if(avail.size() == 0U){
			return false;
	}
	sched.clear();
	// Add your code below

	//Add the first row to sched
	std::vector<Worker_T> temp;
	sched.push_back(temp);

	return schedHelper(avail, dailyNeed, maxShifts, sched);
}

