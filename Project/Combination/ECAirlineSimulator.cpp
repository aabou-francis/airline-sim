//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

ECAirlineSimulator :: ECAirlineSimulator() {
    pAirlineOp = new ECAirlineOperation();
    pAirlineFin = new ECAirlineFinancial();
    pAirlineTicket = new ECAirlineTicketing(*pAirlineOp);
}

ECAirlineSimulator :: ~ECAirlineSimulator() {
    delete pAirlineOp;
    delete pAirlineFin;
    delete pAirlineTicket;
}

void ECAirlineSimulator :: AddAirport(const string &name, const string &code) {

    ECAirportInfo :: GetInstance().CreateAirport(name, code);
}

void ECAirlineSimulator :: SetDistBtwAirports(const string &srcAirport, const string &destAirport, int dist) {
    ECAirportInfo :: GetInstance().SetDistanceBtw(srcAirport, destAirport, dist);
}

void ECAirlineSimulator :: AddFlight(const string &srcAirport, const string &destAirport, double tmDepart, int maxPassengers, double cost) {
    
    ECFlight newFlight(srcAirport, destAirport, tmDepart, maxPassengers);
    pAirlineOp->addFlight(newFlight);
}

void ECAirlineSimulator :: DoneFlightAdding() {}

void ECAirlineSimulator :: SearchForFlights(const string &src, const string &dest, vector<ECFlightItinerary> &listItineraries ) const {
    listItineraries = pAirlineTicket->searchFlights(src, dest);

    for (auto &itinerary : listItineraries) {
        double price = pAirlineFin->priceItinerary(itinerary);
        itinerary.SetPrice(price);
    }
}
