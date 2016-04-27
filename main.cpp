#include <iostream>
#include <fstream>
#include <sstream>
#include "Railroad.h"
using namespace std;

int main()
{
	Railroad RR;
	int run = 1;
	bool station = false;
	string username;
	string dest;
	Station *start;
	Station *end;
	cout << "Welcome to the AMTRAK Pacific Surfliner\nTicketing and Information System.\n" << endl;
	cout << "Please enter your first and last name:" << endl;
	getline(cin, username);
	cout << "\nWelcome, " << username <<"."<< endl;
	cout << "Your current location is:\n" << RR.getLocation()->stationName << " (" << RR.getLocation()->code << ")" << endl;
	while (run == 1)
	{
		int choice;
		cout << "---------------------------------------" << endl;
		cout << "Please make a selection from\nthe following options:\n" << endl;
		cout << "1. Stations - Full Route Map" << endl;
		cout << "2. Book a Ticket" << endl;
		cout << "3. View Itinerary / Print Ticket" << endl;
		cout << "4. Ride the Surfliner" << endl;
		cout << "5. Finish" << endl;
		cin >> choice;
		cin.clear();
		cin.ignore(10000, '\n');
		switch(choice)
		{
		case 1:
			RR.displayRailroad();
			break;
		case 2:
			while (username != "")
			{
				cout << "Please enter the Station Code of your destination:" << endl;
				getline(cin, dest);
				Station *d = RR.findStation(dest);
				if (d != NULL && d->code != RR.getLocation()->code)
				{
					RR.buyTicket(d, username);
					break;
				}
				else if (dest == RR.getLocation()->code)
				{
					cout << "Your destination cannot be the same as your departure point." << endl;
				}
			}
			break;
		case 3:
			RR.printTicket();
			break;
		case 4:
			RR.changeStation();
			break;
		case 5:
			cout << "Thank you for riding the AMTRAK Pacific Surfliner." << endl;
			exit(EXIT_SUCCESS);
		default:
			break;

		}

		
	}
}