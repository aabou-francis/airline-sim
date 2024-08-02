//
//  ECFlight.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

ECFlight::ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn) :
    source(srcIn), dest(destIn), departure(tmDepartIn), maxPass(maxPassengersIn) 
{
    int distance = ECAirportInfo::GetInstance().GetDistanceBtw(source, dest);
    
    double duration = static_cast< double >(distance) / 500;
    
    arrival = departure + duration;
}

ECFlight :: ~ECFlight() {}

double ECFlight :: GetDepartureTime() const { return departure; }

double ECFlight :: GetArrivalTime() const { return arrival; }

void ECFlight :: SetMaxNumPassengers(int m) { maxPass = m;}

string ECFlight :: GetSource() const { return source; }

string ECFlight :: GetDest() const { return dest; }

double ECFlight :: GetFlightDuration() const { return GetArrivalTime() - GetDepartureTime(); }

void ECFlight :: bookFlight() { booked = true; }

void ECFlight :: Dump() const { cout << "Flight: Source = " << GetSource()  << ", Destination = " << GetDest() << endl; }