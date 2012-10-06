#include "memoryleakdetect.h"		// this must be the first #include in each of your .cpp files
#include "winery.h"
#include <iostream>
#include <iomanip>

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	Winery::YOUR_NAME[] = "Vikrum Ojha";

Winery::Winery(const char * const name, const char * const location, const int acres, const int rating): name(NULL), location(NULL), acres(NULL), rating(NULL)
{
	setName(name);
	setLocation(location);
	setAcres(acres);
	setRating(rating);
}

Winery::~Winery()
{
	ReleaseArray(name);
	ReleaseArray(location);
}

void Winery::setName(const char *name)
{
	ReleaseArray(this->name);

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Winery::setLocation(const char *location)
{
	ReleaseArray(this->location);

	this->location = new char[strlen(location) + 1];
	strcpy(this->location, location);
}

void Winery::setAcres(const int acres)
{
	this->acres = acres;
}

void Winery::setRating(const int rating)
{
	this->rating = rating;
}

void Winery::displayColumnHeadings(ostream& out)
{
	// print out column headings for lists of wineries, as specified by lab1output.txt
	//name		location		acres	rating
	//____		________		_____	______
	
	out << setw(25) << left << "name"
		<< setw(20) << "location"
		<< setw(10) << "acres"
					<< "rating\n"
					
		<< setw(25) << left << "____"
		<< setw(20)	<< "________"
		<< setw(10) << "_____"
					<< "______\n";
}

ostream& operator<<(ostream& out, Winery *w)
{
	out << setw(25) << left << w->getName()
		<< setw(20) << w->getLocation()
		<< setw(10) << w->getAcres()
					<< w->getRating()
					<< endl;

	return out;
}
