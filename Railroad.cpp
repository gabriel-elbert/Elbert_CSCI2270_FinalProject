/*Gabriel Elbert
CSCI 2270
Final Project
Prof. Hoenigman*/

#include <iostream>
#include "Railroad.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
using namespace std;

Railroad::Railroad()
{
	buildRailroad(); //constructor calls buildRailroad
}

Railroad::~Railroad()
{
	
}

void Railroad::buildRailroad() //reads in file, builds linked list
{
	string file = "stations.csv";
	ifstream inFile;
	string line;
	inFile.open(file);
	vector<Station*> stations;
	while (getline(inFile, line))
	{
		Station *add = new Station;
		stringstream ss(line);
		string strName, strCode, strDistN, strDistS;
		int intDistN, intDistS;
		getline(getline(getline(getline(ss, strName, ','), strCode, ','), strDistN, ','), strDistS, ',');
		intDistN = stoi(strDistN);
		intDistS = stoi(strDistS);

		add->stationName = strName;
		add->code = strCode;
		add->distFromNorthEnd = intDistN;
		add->distFromSouthEnd = intDistS;
		stations.push_back(add);
	}
	Station *start;
	start = stations[0];
	start->south = NULL;
	start->north = NULL;
	Station *current = start;
	unsigned int i = 1;
	while (i < stations.size())
	{
		Station *tmp;
		tmp = stations[i];
		tmp->south = NULL;
		tmp->north = current;
		current->south = tmp;
		current = current->south;
		i++;
	}
	southEnd = current;
	current = start;
	northEnd = current;

	srand(time(NULL));
	int c = rand() % stations.size();
	Station *loc = stations[c];
	passenger.location = findStation(loc->code);

}

void Railroad::displayRailroad() //prints out all nodes in the list
{
	Station *current;
	current = northEnd;
	cout << "\nCODE	    STATION" << endl;
	cout << "========================================" << endl;
	cout << " ^^^ NORTH ^^^" << endl;
	while (current != NULL)
	{
		if (current->code != passenger.location->code)
		{
			cout << current->code << "  =|=|=  " <<
				current->stationName << endl;
			current = current->south;
		}
		else
		{
			cout << current->code << "  =|=|=  " <<
				current->stationName <<"	<--------------------- *YOU ARE HERE*"<< endl;
			current = current->south;
		}
		
	}
	cout << "======================================\n" << endl;
}

Station* Railroad::getLocation() //returns user location Station
{
	return passenger.location;
}

Station* Railroad::findStation(string id) //checks to see if requested station exists
{
	if (id.length() != 3)
	{
		cout << "Please enter the 3-letter Station Code and try again." << endl;
		return NULL;
	}
	else
	{
		Station* search;
		search = northEnd;
		while (search != NULL)
		{
			if (search->code.compare(id) == 0)
			{
				return search;
				break;
			}
			else
			{
				search = search->south;
			}
		}
		if (search == NULL)
		{
			cout << "That station was not found. Please try again." << endl;
			return search;
		}
		return search;
	}
}

void Railroad::buyTicket(Station* dest, string un) //allows user to buy a ticket, sets appropriate parameters of the passenger struct
{
	passenger.username = un;	
	passenger.destination = dest;
	cout << endl;
	if (dest->distFromNorthEnd - passenger.location->distFromNorthEnd > 0)
	{
		passenger.northBound = false;
		cout << "You are heading southbound to "<<dest->stationName<<"."<< endl;
	}
	else
	{
		passenger.northBound = true;
		cout << "You are heading northbound to "<< dest->stationName << "." << endl;
	}
	passenger.travelDistance = calcTotalDistance(passenger.location, dest);
    passenger.travelTime = calcTravelTime();
	passenger.ticketPrice = calcTicketPrice();
	passenger.hasTicket = true;
	cout << "Please enter 'C' to checkout." << endl;
	char enter;
	int run = 1;
	while (run == 1)
	{
		cin >> enter;
		switch (enter)
		{
		case 'C':
			cout << "Transaction completed successfully." << endl;
			run = 0;
			break;
		default:
			cout << "Please enter 'C' to checkout." << endl;
			break;
		}
	}
}

int Railroad::calcTotalDistance(Station *userLocation, Station *destination) //finds total distance between two nodes
{
	int dist;
	if (passenger.northBound == true)
	{
		dist = destination->distFromSouthEnd - userLocation->distFromSouthEnd;
		return dist;
	}
	else if(passenger.northBound == false)
	{
		dist = destination->distFromNorthEnd - userLocation->distFromNorthEnd;
		return dist;
	}
}

double Railroad::calcTravelTime() //calculates how long the travel time is between origin and destination of user (passenger)
{
	return (passenger.travelDistance / 38.5);
}

double Railroad::calcTicketPrice() //calculates final ticket price
{
	char choice;
	double price;
	double business;
	int bags;
	if (passenger.travelDistance <= 20)
	{
		price = 8.50;
	}
	else
	{
		price = 8.50 + (passenger.travelDistance-20)*0.25;
	}
	if (passenger.travelDistance <= 140)
	{
		business = 10.00;
	}
	else
	{
		business = 10.00 + (passenger.travelDistance - 140) % 20 * 0.75;
	}
	int run = 1;
	while (run == 1)
	{
		cout << "\nPlease choose from the following options:" << endl;
		cout << "ECONOMY (COACH)			BUSINESS CLASS" << endl;
		cout << "Option A: " <<"$"<< price << "		" <<"Option B: "<<"$"<<price+business << endl;
		cin >> choice;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (choice)
		{
			case 'A':
				price = price;
				run = 0;
				break;
			case 'B':
				price = price + business;
				passenger.businessClass = true;
				run = 0;
				break;
			default:
				cout << "Please choose Option A or B." << endl;
				break;
		}
	}
	cout << "\nPlease enter the number of bags will you be checking. \nEach bag is $15.00. Enter 0 for no bags." << endl;
	cin >> bags;
	price = price + 15.00*bags;
	passenger.bags = bags;
	char bike;
	run = 1;
	while (run == 1)
	{
		cout << "\nWill you be checking a bicycle? Bicycles are free. (Y/N)" << endl;
		cin >> bike;
		switch(bike)
		{
			case 'Y':
				passenger.hasBike = true;
				run = 0;
				break;
			case 'N':
				passenger.hasBike = false;
				run = 0;
				break;
			default:
				cout << "Please enter 'Y' for Yes, or 'N' for No." << endl;
				break;
		}
	}
	cout << "\nTOTAL: $" << price << endl;
	return price;
}

void Railroad::changeStation() //allows user to ride the train and change current station
{
	if (passenger.hasTicket == true)
	{
		cout << "ALL ABOARD!!!" << endl;
		Station *current;
		if (passenger.northBound == true)
		{
			current = passenger.location->north;
		}
		else
		{
			current = passenger.location->south;
		}
		cout << passenger.location->stationName << endl;
		while (current != passenger.destination)
		{
			cout << "=|=|=\n=|=|=\n=|=|=" << endl;
			cout << current->stationName << endl;
			if (passenger.northBound == true)
				current = current->north;
			else
				current = current->south;
		}
		cout << "=|=|=\n=|=|=\n=|=|=" << endl;
		cout << current->stationName << endl;
		cout << endl;
		if (passenger.travelTime < 1.00)
			cout << "Total travel time: " << passenger.travelTime*60 << " minutes" << endl;
		else
			cout << "Total travel time: " << passenger.travelTime << " hours" << endl;

		cout << "Total distance traveled: " << passenger.travelDistance << " miles" << endl;
		passenger.location = current;
		passenger.hasTicket = 0;
		passenger.northBound = false;
		passenger.destination = NULL;
	}
	else
	{
		cout << "\nYou may not ride the train without a ticket." << endl;
	}
}

void Railroad::printTicket() //prints all relevant information about the user
{
	if (passenger.hasTicket == true)
	{
		cout << "========================================================================================" << endl;
		cout << "			AMTRAK Pacific Surfliner" << endl;
		cout << "				BOARDING PASS" << endl;
		cout << endl;
		cout << "PASSENGER NAME:	" << passenger.username;
		if (passenger.businessClass == true)
			cout << "				BUSINESS CLASS" << endl;
		else
			cout << "				COACH" << endl;
		cout << endl;
		cout << "Origin: " << passenger.location->stationName << " (" << passenger.location->code << ") " << "		"
			<< "Destination: " << passenger.destination->stationName << " (" << passenger.destination->code << ") " << endl;
		cout << endl;
		cout << "Number of bags: " << passenger.bags;
		if (passenger.hasBike == true)
			cout << "				" << "BICYCLE: Yes" << endl;
		else
			cout << "				" << "BICYCLE: No" << endl;
		cout << endl;
		cout << "========================================================================================" << endl;
	}
	else
	{
		cout << "\nYou have not yet purchased a ticket" << endl;
	}
}