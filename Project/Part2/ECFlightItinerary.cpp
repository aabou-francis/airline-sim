//
//  ECFlightItinerary.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

ECFlightItinerary :: ECFlightItinerary() : price(0) {}

void ECFlightItinerary :: addSegments(const ECFlight& flight) {
    cout << "Adding flight to itinerary: " << flight.GetSource() << " -> " << flight.GetDest() << " at " << flight.GetDepartureTime() << endl;

    flightSegs.push_back(flight);
}

int ECFlightItinerary :: GetNumSegments() const {
    return flightSegs.size();
}

const ECFlight* ECFlightItinerary :: GetSegment(int segIndex) const {
    if (segIndex >= 0 && segIndex < flightSegs.size()) {
        return &(flightSegs[segIndex]);
    }

    return NULL;
}

double ECFlightItinerary :: GetTimeAllSegments() const {
    double total = 0;

    for (const auto& segment : flightSegs) {
        total += segment.GetFlightDuration();
    }

    return total;
}

double ECFlightItinerary :: GetFlightTime() const {
    if (flightSegs.empty()) return 0;

    return GetTimeAllSegments();
}

double ECFlightItinerary :: GetDepartTime() const {
    if (!flightSegs.empty()) {
        return flightSegs.front().GetDepartureTime();
    }

    return 0;
}

double ECFlightItinerary :: GetArrivalTime() const {
    if (!flightSegs.empty()) {
        return flightSegs.back().GetArrivalTime();
    }

    return 0;
}

double ECFlightItinerary :: GetPrice() const {
    return price;
}

void ECFlightItinerary :: SetPrice(double newPrice) {
    price = newPrice;
}

void ECFlightItinerary :: Dump() const {
    cout << "Itinerary details:\n";
    for (const auto& segment : flightSegs) { 
        segment.Dump();
    }
}