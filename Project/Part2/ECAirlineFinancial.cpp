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

#include "ECAirlineFinancial.h"

ECAirlineFinancial :: ECAirlineFinancial(ECAirlineOperation *pOperateIn) : pOperate(pOperateIn), balance(0) {}

ECAirlineFinancial :: ~ECAirlineFinancial() {
    for(auto *passenger : listPassengers) {
        delete passenger;
    }

    listPassengers.clear();
}

void ECAirlineFinancial :: RegisterPassenger(ECPassenger *pPassenger) {
    listPassengers.push_back(pPassenger);
}


double ECAirlineFinancial :: Quote(const ECFlightItinerary &itin) const {
    return itin.GetFlightTime() * PRICE_PER_HOUR;
}


double ECAirlineFinancial :: GetBalance() const {
    return balance;
}

void ECAirlineFinancial :: Paid(double amt) {
    balance += amt;
}

void ECAirlineFinancial :: Charged(double amt) {
    balance -= amt;
}

void ECAirlineFinancial :: Dump() const {
    std::cout << "Current Balance: $" << balance << std::endl;
}

double ECAirlineFinancial :: priceItinerary(const ECFlightItinerary& itinerary) const {
    double totalFlightTime = itinerary.GetTimeAllSegments();
    return totalFlightTime * PRICE_PER_HOUR;
}