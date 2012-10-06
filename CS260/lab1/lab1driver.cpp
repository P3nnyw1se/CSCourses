// make NO CHANGES to this file

#pragma warning(disable:4996)		// disable warnings about use of strcpy()

#include "memoryleakdetect.h"		// this must be the first #include in each of your .cpp files
#include <iostream>
#include "winery.h"
#include "list.h"

using namespace std;

static List		*wineries;

// Ask list to insert a winery into the doubly-threaded linked list.
// Note what this function does with memory, which has implications for
// how you will (and will not) be able to use the winery instance that's
// passed to wineries->insert.
static void insertWinery(char *name, char *location, int acres, int rating)
{
	Winery	*w;
	char	*nm = new char[strlen(name) + 1];
	char	*loc = new char[strlen(location) + 1];
	
	strcpy(nm, name);
	strcpy(loc, location);
	w = new Winery(nm, loc, acres, rating);
	wineries->insert(*w);
	delete[] nm;
	delete[] loc;
	delete w;
}

// Display all wineries in the list,
// first in order by name, then in order by rating.
static void displayWineries(ostream& out)
{
	out << "+++ list by name" << endl;
	wineries->displayByName(out);
	out << endl << "+++ list by rating" << endl;
	wineries->displayByRating(out);
}

int main(int argc, char **argv)
{
	Winery	*wPtr;

    cout << "CS260 - Lab1 - " << Winery::YOUR_NAME << endl << endl;

    wineries = new List();

	insertWinery("Lopez Island Vineyard", "San Juan Islands", 7, 95);
	insertWinery("Gallo", "Napa Valley", 200, 25);
	insertWinery("Cooper Mountain", "Willamette Valley", 100, 47);
	insertWinery("Duck Pond Cellars", "Willamette Valley", 845, 70);
	insertWinery("Del Rio", "Bear Creek Valley", 200, 37);
	insertWinery("Weisinger's of Ashland", "Bear Creek Valley", 6, 83);
	insertWinery("LongSword", "Applegate Valley", 16, 85);

	displayWineries(cout);

	cout << endl << ">>> removing Cooper Mountain" << endl <<  endl;
	wineries->remove("Cooper Mountain");

	displayWineries(cout);

	cout << endl << ">>> inserting San Juan Vineyards" << endl << endl;
	insertWinery("San Juan Vineyards", "San Juan Islands", 20, 90);

	displayWineries(cout);

	cout << endl << ">>> search for \"Gallo\"" << endl << endl;
	wPtr = wineries->find("Gallo");
	if (wPtr != 0)
		cout << wPtr;
	else
		cout << "not found" << endl;

	cout << endl << ">>> search for \"No Such\"" << endl << endl;
	wPtr = wineries->find("No Such");
	if (wPtr != 0)
		cout << wPtr;
	else
		cout << "not found" << endl;

	cout << endl;

	delete wineries;

	// report on memory leaks in the Output Window
	#ifdef _DEBUG
	if (argc == 2) {
		_CrtSetReportMode( _CRT_WARN , _CRTDBG_MODE_FILE );
		_CrtSetReportFile( _CRT_WARN , _CRTDBG_FILE_STDERR );
		}
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}
