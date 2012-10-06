// make NO CHANGES to this file

#pragma once				// include this .h file file only once

//Macro for releasing char arrays.
#define ReleaseArray(x) if(x != NULL){delete [] x; x = NULL;}
#define Release(x) if(x != NULL){delete x; x = NULL;}

#include <ostream>

class Winery
{
public:
	static const char	YOUR_NAME[];	// used for printing out programmer's name

	Winery(const char * const name, const char * const location, const int acres, const int rating);
	virtual ~Winery(void);

	// adding in my own set functions.
	void setName(const char *name);
	void setLocation(const char *location);
	void setAcres(const int acres);
	void setRating(const int rating);

	// complete implementations for the following 4 functions, nothing needed in the .cpp file
	const char * const getName() const { return name; }
	const char * const getLocation() const { return location; }
	const int getAcres() const { return acres; }
	const int getRating() const { return rating; }

	// print out column headings for lists of wineries, as specified by lab1output.txt
	static void displayColumnHeadings(std::ostream& out);

	// print out a winery, as specified by lab1output.txt
	friend std::ostream& operator<<(std::ostream& out, Winery *w);

private:
	char	*name;
	char	*location;
	int		acres;
	int		rating;
};
