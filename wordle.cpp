// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	std::set<std::string> returnSet;

	//Layer 1 helper function call
	floatPerm(in, floating, dict, returnSet);

	return returnSet;

}

// Define any helper functions here
void floatPerm(//Finds permutations of input string with floating letter in different locations
		const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
		std::set<std::string>& returnSet
){
	
	//make a copy of "in" to manipulate
	std::string inCpy = in;

	//Replace one dash per recursive iteration AS LONG as there are still floating letters
	//Call wordFinder on single instances first, then dupes, then trips, etc

	/*
	cases:
	1. no dashes in 'in' -> call word finder
	2. floating is empty (all letters have been used at least once) -> call word finder
	3. there are dashes and floating is not empty -> replace a dash with a letter from floating
		 and remove that letter for the next recursive call

	What about dupes and trips, etc?
	implemet: first try singles, then dupes, etc
	*/

	//Dash replacing repeats pseudo code
	/*
		outer loop - iterates from 1 to the number of dashes

		inner loop 1 - replaces dash, with floating letter and recursive call
	*/

	// unsigned int duplicates = dc - floating.length();//Max number of duplicate letters that can be in the word
	
	//if(duplicates <= 0){//All floating letters have been used so call wordFinder
	if(floating.empty()){//All floating letters have been used so call wordFinder


		//std::cout << "Call word finder on " << inCpy << std::endl;
		wordFinder(inCpy, dict, returnSet);
	//}

	}else{//There are still letters to place
		//Find the dashes

		for(unsigned i = 0; i < floating.length(); ++i){//Iterate thorugh all floating letters
			std::string s(1,floating[i]);

			//Place letter in each dash
			std::size_t found = inCpy.find("-");

			

			while(found != std::string::npos){
				//Replace the dash with a letter from the floating input string
				inCpy.replace(found, 1, s);

				//Degbug
				//std::cout << "Replaced a dash: " << inCpy << std::endl;

				//Remove letter from vector
				std::string temp = floating;
				temp.erase(i,1);

				//Recursive call with a dash replaced from the initial argument
				floatPerm(inCpy, temp, dict, returnSet);	

				//Undo change for next iteration
				inCpy.replace(found, 1, "-");

				//Find the next dash
				found = inCpy.find("-", found+1);	

			}			
		}
	}
}

void wordFinder(//Generate all permuations of a word with all letters in the alphabet and check if its in the dictionary
	std::string in,
	const std::set<std::string>& dict,
	std::set<std::string>& returnSet
){

	//create a vector for all letters in the alphabet
	std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	//find the remaining dashes
	std::size_t found = in.find("-");
  if (found!=std::string::npos){//If a dash was found

		//std::cout << in << " -> ";

		for (auto & letter : alphabet) {
			std::string s(1, letter);

			//Replace it with a letter in the alphabet
			in.replace(found,1,s);

			//Debug
			//std::cout << in << std::endl;

			//Recursive call
			wordFinder(in, dict, returnSet);
		}
		

	}else{//If there are none

		//Check if the string is in the dictionary
		std::set<std::string>::iterator it;

		it = dict.find(in);


		if(it != dict.end()){//If so, add it to the return set

			returnSet.insert(in);

		}else{//If not, return
			return;
		}

	}

}
