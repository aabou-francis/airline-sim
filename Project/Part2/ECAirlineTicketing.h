//
//  ECAirlineTicketing.h
//  
//
//  Created by Yufeng Wu on 5/12/23.
//

#ifndef ECAirlineTicketing_h
#define ECAirlineTicketing_h

#include "ECFlightItinerary.h"
#include "ECAirlineOperation.h"
#include <vector>
#include <string>

// ****************************************************************************
// Airline ticketing: search for flights, issue tickets, etc

class ECAirlineTicketing {
public:
    ECAirlineTicketing(const ECAirlineOperation& operation);

    std::vector< ECFlightItinerary > searchFlights(const std::string& source, const std::string& dest);

    void bookFlight(const ECFlightItinerary& itinerary);


private:
    std::vector< ECFlightItinerary > itineraries;
    
    void SearchForFlightsRecursive(const std::string &currentAirport, const std::string &finalDestination, ECFlightItinerary &currentItinerary, std::vector<ECFlightItinerary> &allItineraries, std::set<std::string> &visitedAirports);
                    
    const ECAirlineOperation& operation;

};

#endif /* ECAirlineTicketing_h */
