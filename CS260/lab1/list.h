// make NO CHANGES to this file

#pragma once				// include this .h file file only once

#include <ostream>
#include "winery.h"

using namespace std;

class List
{
public:
	List(void);				// constructor
	virtual ~List(void);	// destructor

	// Print out the wineries in alphabetical order by name,
	// by calling winery's operator<< for each winery.
	void displayByName(ostream& out) const;

	// Print out the wineries from highest to lowest rating,
	// by calling winery's operator<< for each winery.
	void displayByRating(ostream& out) const;

	// Insert a winery into both the names and ratings threads.
	// The names thread should be in alphabetical order by name.
	// The ratings thread should be in order from highest rating
	// to lowest rating.
	void insert(const Winery& winery);

	// Return a const pointer to the winery instance it finds in
	// the list, or 0 if it didn't find a winery with that name.
	// Because the pointer is declared const, there is no danger
	// that find's caller will be able to use the returned pointer
	// to change the instance of winery.
	Winery * const find(const char * const name) const;

	// Remove the winery with the specified name from both the name
	// thread and the ratings thread. Returns true if it found and
	// removed the winery, false if it did not find the winery.
	bool remove(const char * const name);

private:
	// defines each node in the doubly-threaded linked list.
	struct Node
	{
		Node(const Winery& winery);		// constructor
		Winery item;					// an instance of winery
										// (NOT a pointer to an instance)
		Node *nextByName;				// next node in the name thread
		Node *nextByRating;				// next node in the rating thread
	};

	Node *headByName;					// first node in the name thread
	Node *headByRating;					// first node in the rating thread
};
