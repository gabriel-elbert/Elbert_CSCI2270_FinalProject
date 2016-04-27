#ifndef RAILROAD_H
#define RAILROAD_H
#include <iostream>
#include <vector>
#include <string>

struct Station
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

struct user
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
	public:
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
		user passenger;
};
#endif // !RAILROAD_H