#include "memoryleakdetect.h"		// this must be the first #include in each of your .cpp files
#include <iostream>
#include "list.h"

List::List():headByName(NULL), headByRating(NULL)
{
}

List::~List()
{
	Node *deletionNode	= NULL;
	Node *transverse	= NULL;

	transverse			= headByRating->nextByRating;

	deletionNode		= headByRating;

	while (transverse->nextByRating != NULL)
	{
		delete deletionNode;
		deletionNode	= transverse;
		transverse		= transverse->nextByRating;
	}

	delete deletionNode;
	delete transverse;
	deletionNode		= NULL;
	transverse			= NULL;
}

List::Node::Node(const Winery& winery) : nextByName(NULL), nextByRating(NULL), item(winery.getName(), winery.getLocation(), winery.getAcres(), winery.getRating())
{

}


void List::displayByName(ostream& out) const
{
	Node *Temp = headByName;

	Temp->item.displayColumnHeadings(out);

	do
	{
		out << &Temp->item;

		Temp = Temp->nextByName;
	}while (Temp->nextByName != NULL);

	out << &Temp->item;
}

void List::displayByRating(ostream& out) const
{

	Node *Temp = headByRating;

	Temp->item.displayColumnHeadings(out);

	do
	{
		out << &Temp->item;

		Temp = Temp->nextByRating;
	}while (Temp->nextByRating != NULL);

	out << &Temp->item;
}

void List::insert(const Winery& winery)
{
	if (headByName == NULL)
	{
		headByName					= new Node(winery);
		headByRating				= headByName;
	}
	else
	{
		int maxCompareLen			= NULL;
		
		Node *insertionNode			= new Node(winery);
		Node *transversalByName		= NULL;
		Node *transversalByRating	= NULL;

		bool insertedByName			= false;
		bool insertedByRating		= false;

		//Test if it comes before the head.
		if (strlen(winery.getName()) >= strlen(headByName->item.getName()))
		{
			maxCompareLen = strlen(winery.getName());
		}
		else
		{
			maxCompareLen = strlen(headByName->item.getName());
		}

		if (strncmp(winery.getName(), headByName->item.getName(), maxCompareLen) < NULL)
		{
			insertionNode->nextByName	= headByName;
			headByName					= insertionNode;

			insertedByName = true;
		}
		if (winery.getRating() > headByRating->item.getRating())
		{
			insertionNode->nextByRating = headByRating;
			headByRating				= insertionNode;

			insertedByRating = true;
		}
		///////End head checking block.

		transversalByName	= headByName;
		transversalByRating	= headByRating;

		//Begin filtering through names if not sorted.
		if (!insertedByName)
		{
			while (transversalByName->nextByName != NULL)
			{
				if (strlen(insertionNode->item.getName()) <= strlen(transversalByName->nextByName->item.getName()))
				{
					maxCompareLen = strlen(insertionNode->item.getName());
				}
				else
				{
					maxCompareLen = strlen(transversalByName->nextByName->item.getName());
				}

				if ((strncmp(insertionNode->item.getName(), transversalByName->nextByName->item.getName(), maxCompareLen)) < NULL)
				{
					break;
				}
				else
				{
					transversalByName = transversalByName->nextByName;
				}
			}

			insertionNode->nextByName		= transversalByName->nextByName;
			transversalByName->nextByName	= insertionNode;
		}
		//endif

		if (!insertedByRating)
		{
			while (transversalByRating->nextByRating != NULL)
			{
				if (insertionNode->item.getRating() > transversalByRating->nextByRating->item.getRating())
				{
					break;
				}
				else
				{
					transversalByRating = transversalByRating->nextByRating;
				}
			}

			insertionNode->nextByRating			= transversalByRating->nextByRating;
			transversalByRating->nextByRating	= insertionNode;
		}
	}
}

Winery * const List::find(const char * const name) const
{
	if ((strncmp(name, headByName->item.getName(), strlen(name))) == NULL)
	{
		return &headByName->item;
	}
	else
	{
		Node *Temp = headByName->nextByName;

		do 
		{
			if ((strncmp(name, Temp->item.getName(), strlen(name))) == NULL)
			{
				return &Temp->item;
			}

			Temp = Temp->nextByName;

		} while (Temp->nextByName != NULL);

		if ((strncmp(name, Temp->item.getName(), strlen(name))) == NULL)
		{
			return &Temp->item;
		}
	}

	return 0;
}

bool List::remove(const char * const name)
{
	Node *deletionNode			= NULL;
	Node *transversalByName		= headByName;
	Node *transversalByRating	= headByRating;

	bool found					= false;

	//Check head first, then move onto the rest of the list.  Remember to check the last bit since the while loop won't include it.
	if ((strlen(name) == strlen(headByName->item.getName())) && (strncmp(name, headByName->item.getName(), strlen(name)) == NULL))
	{
		deletionNode	= headByName;
		headByName		= deletionNode->nextByName;

		found			= true;		
	}
	else if (!found)
	{
		while (transversalByName->nextByName != NULL)
		{
			if (strlen(name) <= strlen(transversalByName->nextByName->item.getName()))
			{
				if (strncmp(name, transversalByName->nextByName->item.getName(), strlen(name)) == NULL)
				{
					deletionNode = transversalByName->nextByName;
					found = true;

					break;
				}
			}
			else
			{
				transversalByName = transversalByName->nextByName;
			}
		}
		///end while.
	}

	if (found)
	{
		if (deletionNode == headByRating)
		{
			headByRating = deletionNode->nextByRating;
		}
		else
		{
			while (transversalByRating->nextByRating != deletionNode)
			{
				transversalByRating = transversalByRating->nextByRating;
			}

			transversalByRating->nextByRating = deletionNode->nextByRating;
		}

		delete deletionNode;
		deletionNode			= NULL;
		transversalByName		= NULL;
		transversalByRating		= NULL;

		return true;
	}

	return false;
}