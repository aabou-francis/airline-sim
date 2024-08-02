//
//  ECAirlineTicketing.cpp
//  
//
//  Created by Yufeng Wu on 5/12/23.
//

#include "ECAirlineTicketing.h"
#include <iostream>

using namespace std;

ECAirlineTicketing :: ECAirlineTicketing(const ECAirlineOperation& operation) : operation(operation) {}

void ECAirlineTicketing :: SearchForFlightsRecursive(const string &currentAirport, const string &finalDestination, ECFlightItinerary &currentItinerary, vector<ECFlightItinerary> &allItineraries, set<string> &visitedAirports) {

    cout << "Visiting: " << currentAirport << " with goal: " << finalDestination << endl;

    if (currentAirport == finalDestination) {
        cout << "Destination reached. Adding itinerary." << endl;

        allItineraries.push_back(currentItinerary);
        return;
    }

    if (visitedAirports.find(currentAirport) != visitedAirports.end()) {
        cout << "Already visited " << currentAirport << ". Skipping to avoid cycle." << endl;

        return;
    }

    visitedAirports.insert(currentAirport);

    auto departingFlights = operation.GetFlightsFromAirport(currentAirport);

    for (const auto& flight : departingFlights) {
        if (visitedAirports.find(flight.GetDest()) == visitedAirports.end()) {
            cout << "Considering flight: " << flight.GetSource() << " to " << flight.GetDest() << endl;

            bool canAddFlight = currentItinerary.GetNumSegments() == 0 || flight.GetDepartureTime() >= currentItinerary.GetSegment(currentItinerary.GetNumSegments() - 1)->GetArrivalTime();
                
            if (canAddFlight) {
                ECFlightItinerary newItinerary = currentItinerary;
                newItinerary.addSegments(flight);

                SearchForFlightsRecursive(flight.GetDest(), finalDestination, newItinerary, allItineraries, visitedAirports);
            }
        }
    }

    visitedAirports.erase(currentAirport);
}

vector<ECFlightItinerary> ECAirlineTicketing :: searchFlights(const string& src, const string& dest) {

    cout << "Starting search for flights from " << src << " to " << dest << endl;

    vector<ECFlightItinerary> allItineraries;
    ECFlightItinerary currentItinerary;
    set<string> visitedAirports;

    SearchForFlightsRecursive(src, dest, currentItinerary, allItineraries, visitedAirports);

    return allItineraries;
}


void ECAirlineTicketing :: bookFlight(const ECFlightItinerary& itinerary) {}
