//
//  ECAirlineFinancial.cpp
//  
//
//  Created by Yufeng Wu on 5/16/23.
//

#include "ECAirlineFinancial.h"
#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"

#include <string>
#include <iostream>
using namespace std;

double ECAirlineFinancial :: priceItinerary(const ECFlightItinerary& itinerary) const {
    double totalFlightTime = itinerary.GetTimeAllSegments();
    return totalFlightTime * PRICE_PER_HOUR;
}