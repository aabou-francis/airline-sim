//
//  ECAirlineOperation.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"
#include "ECAirlineFinancial.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void ECAirlineOperation :: addFlight(const ECFlight& flight) {
    flights.push_back(flight);
}

void ECAirlineOperation :: removeFlight(const std::string& source, const std::string& destination) {
    flights.erase(remove_if(flights.begin(), flights.end(), [&source, &destination](const ECFlight& flight) { 
                                      return flight.GetSource() == source && flight.GetDest() == destination; }), flights.end());
}

const ECFlight* ECAirlineOperation :: getFlight(const std::string& source, const std::string& destination) const {
    for (auto& flight : flights) {
        if (flight.GetSource() == source && flight.GetDest() == destination) {
            return &flight;
        }
    }

    return NULL;
}

vector< ECFlight > ECAirlineOperation :: GetFlightsFromAirport(const string& airportCode) const {
    vector<ECFlight> departingFlights;
    
    for (const auto& flight : flights) {
        if (flight.GetSource() == airportCode) {
            departingFlights.push_back(flight);
        }
    }
    
    return departingFlights;
}