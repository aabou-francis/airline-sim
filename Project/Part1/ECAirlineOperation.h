//
//  ECAirlineOperation.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//  About operation of an airline: especially flights management

#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h

#include "ECFlight.h"
#include "ECAirport.h"
#include <vector>
#include <string>

// put your code about airline operation here...

class ECAirlineOperation {
public:
    void addFlight(const ECFlight& flight);

    void removeFlight(const std::string& source, const std::string& destination);

    const ECFlight* getFlight(const std::string& source, const std::string& destination) const;

    std::vector< ECFlight > flights;

    std::vector<ECFlight> GetFlightsFromAirport(const std::string& airportCode) const;

};

#endif