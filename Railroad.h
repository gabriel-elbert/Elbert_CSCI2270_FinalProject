/*Gabriel Elbert
CSCI 2270
Final Project
Prof. Hoenigman*/

#ifndef RAILROAD_H
#define RAILROAD_H
#include <iostream>
#include <vector>
#include <string>

struct Station //framework for a statin struct
{
	std::string stationName;
	std::string code;
	Station *south;
	Station *north;
	int distFromSouthEnd;
	int distFromNorthEnd;
	Station() {};
	Station(std::string initName, std::string initCode,
		Station *initNext, Station *initPrev, int distSouth, int distNorth)
		{
			stationName = initName;
			code = initCode;
			south = initNext;
			north = initPrev;
			distFromSouthEnd = distSouth;
			distFromNorthEnd = distNorth;
		}
};

struct user //framework for a user struct
{
	std::string username;
	Station *destination;
	Station *location;
	double ticketPrice;
	double travelTime;
	int travelDistance;
	int bags;
	bool northBound;
	bool hasTicket;
	bool businessClass;
	bool hasBike;
	
	user() {};
};

class Railroad
{
	public:				//functions of Railroad
		Railroad();
		~Railroad();
		void buildRailroad();
		double calcTravelTime();
		void changeStation();
		void printTicket();
		double calcTicketPrice();
		//void viewInfo();
		void buyTicket(Station* dest, std::string un);
		int calcTotalDistance(Station *origin, Station *dest);
		void displayRailroad();
		Station * getLocation();
		Station * findStation(std::string id);
	protected:
	private:
		Station *northEnd;
		Station *southEnd;
		user passenger; //creating a user 
};
#endif // !RAILROAD_H