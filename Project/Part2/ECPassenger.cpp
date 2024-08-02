//
//  ECPassenger.cpp
//  
//
//  Created by Yufeng Wu on 5/15/23.
//

#include "ECPassenger.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlight.h"

#include <vector>
#include <iostream>
using namespace std;

ECPassenger :: ECPassenger(const string &srcAirportIn, const string &destAirportIn)
    : srcAirport(srcAirportIn), destAirport(destAirportIn), status(EC_PASSENGER_UNBOOKED) {}

ECPassenger :: ~ECPassenger() {}

bool ECPassenger :: Book(ECAirlineTicketing &airlineTicketing) {

    cout << "Generic booking for passenger from " << srcAirport << " to " << destAirport << endl;

    vector<ECFlightItinerary> itineraries = airlineTicketing.searchFlights(srcAirport, destAirport);

    if (itineraries.empty()) {
        cout << "No available itineraries from " << srcAirport << "to " << destAirport << endl;
        
        return false;
    }

    itin = itineraries[0];
    status = EC_PASSENGER_BOOKED;
    cout << "Booking successful for passenger from " << srcAirport << " to " << destAirport << "." << endl;
    return true;
}

void ECPassenger :: Dump() const {
    cout << "Passenger traveling from " << srcAirport << " to " << destAirport << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AddPassengerBudget :: AddPassengerBudget(const string &srcAirportIn, const string &destAirportIn, double budgetIn) : ECPassenger(srcAirportIn, destAirportIn), budget(budgetIn) {}

bool AddPassengerBudget :: Book(ECAirlineTicketing &airlineTicketing) {

    vector<ECFlightItinerary> itineraries = airlineTicketing.searchFlights(srcAirport, destAirport);
    sort(itineraries.begin(), itineraries.end(), 
        [](const ECFlightItinerary &a, const ECFlightItinerary &b) {
            return a.GetPrice() < b.GetPrice();
        });

    auto it = find_if(itineraries.begin(), itineraries.end(),
                      [this](const ECFlightItinerary &itinerary) {
                          return itinerary.GetPrice() <= budget;
                      });

    if (it == itineraries.end()) {
        cout << "No itineraries within budget from " << srcAirport << " to " << destAirport << "." << endl;
        return false;
    }

    itin = *it;
    status = EC_PASSENGER_BOOKED;
    return true;
}


void AddPassengerBudget :: Dump() const {
    cout << "Budget Passenger traveling from " << srcAirport << " to " << destAirport << ", Budget: " << budget << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AddPassengerBusiness :: AddPassengerBusiness(const string &srcAirportIn, const string &destAirportIn, double tmArrivalLatestIn)
    : ECPassenger(srcAirportIn, destAirportIn), tmArrivalLatest(tmArrivalLatestIn) {}

bool AddPassengerBusiness :: Book(ECAirlineTicketing &airlineTicketing) {

    vector<ECFlightItinerary> itineraries = airlineTicketing.searchFlights(srcAirport, destAirport);

    sort(itineraries.begin(), itineraries.end(), [this](const ECFlightItinerary &a, const ECFlightItinerary &b) { return a.GetArrivalTime() < b.GetArrivalTime(); });

    auto it = find_if(itineraries.begin(), itineraries.end(), [this](const ECFlightItinerary &itinerary) { return itinerary.GetArrivalTime() <= tmArrivalLatest; });

    if (it == itineraries.end()) {
        cout << "No itineraries meeting the business deadline from " << srcAirport << " to " << destAirport << "." << endl;
        return false;
    }

    itin = *it;
    status = EC_PASSENGER_BOOKED;
    return true;
}


void AddPassengerBusiness :: Dump() const {
    cout << "Business Passenger traveling from " << srcAirport << " to " << destAirport << ", Must arrive by: " << tmArrivalLatest << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AddPassengerComfort :: AddPassengerComfort(const string &srcAirportIn, const string &destAirportIn, double tmEarliestDepartIn, double maxFlightTimeIn, int maxSegmentsIn)
    : ECPassenger(srcAirportIn, destAirportIn), tmEarliestDepart(tmEarliestDepartIn), maxFlightTime(maxFlightTimeIn), maxSegments(maxSegmentsIn) {}

bool AddPassengerComfort :: Book(ECAirlineTicketing &airlineTicketing) {

    vector<ECFlightItinerary> itineraries = airlineTicketing.searchFlights(srcAirport, destAirport);

    sort(itineraries.begin(), itineraries.end(), [](const ECFlightItinerary &a, const ECFlightItinerary &b) {
            if (a.GetNumSegments() != b.GetNumSegments()) 
                return a.GetNumSegments() < b.GetNumSegments();
            if (a.GetFlightTime() != b.GetFlightTime()) 
                return a.GetFlightTime() < b.GetFlightTime();
            if (a.GetArrivalTime() != b.GetArrivalTime()) 
                return a.GetArrivalTime() < b.GetArrivalTime();
            return a.GetPrice() < b.GetPrice();
        });

    for (const auto& itinerary : itineraries) {
        if (itinerary.GetDepartTime() >= tmEarliestDepart && itinerary.GetFlightTime() <= maxFlightTime && itinerary.GetNumSegments() <= maxSegments) {
            itin = itinerary;
            status = EC_PASSENGER_BOOKED;
            cout << "Booking successful for comfort passenger from " << srcAirport << " to " << destAirport << "." << endl;
            return true;
        }
    }

    cout << "No suitable itineraries found for comfort passenger from " << srcAirport << " to " << destAirport << "." << endl;
    return false;
}


void AddPassengerComfort :: Dump() const {
    cout << "Comfort Passenger traveling from " << srcAirport << " to " << destAirport << ", Earliest Departure: " << tmEarliestDepart << ", Max Flight Time: " << maxFlightTime << ", Max Segments: " << maxSegments << endl;
}