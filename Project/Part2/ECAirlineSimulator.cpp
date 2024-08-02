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
#include "ECPassenger.h"

#include <algorithm>

#include <iostream>
using namespace std;

ECAirlineSimulator :: ECAirlineSimulator() {
    pAirlineOp = new ECAirlineOperation();
    pAirlineFin = new ECAirlineFinancial(pAirlineOp);
    pAirlineTicket = new ECAirlineTicketing(*pAirlineOp);
}

ECAirlineSimulator :: ~ECAirlineSimulator() {
    delete pAirlineOp;
    delete pAirlineFin;
    delete pAirlineTicket;
}

void ECAirlineSimulator :: AddAirport(const string &name, const string &code) {
    cout << "Adding airport: Name = " << name << ", Code = " << code << endl;

    ECAirportInfo :: GetInstance().CreateAirport(name, code);
}

void ECAirlineSimulator :: SetDistBtwAirports(const string &srcAirport, const string &destAirport, int dist) {
    ECAirportInfo :: GetInstance().SetDistanceBtw(srcAirport, destAirport, dist);
}

void ECAirlineSimulator :: AddFlight(const string &srcAirport, const string &destAirport, double tmDepart, int maxPassengers, double cost) {
    cout << "Adding flight: Source = " << srcAirport << ", Destination = " << destAirport << ", Departure Time = " << tmDepart << endl;

    ECFlight newFlight(srcAirport, destAirport, tmDepart, maxPassengers);
    pAirlineOp->addFlight(newFlight);
}

void ECAirlineSimulator :: DoneFlightAdding() {}

void ECAirlineSimulator :: SearchForFlights(const string &src, const string &dest, vector<ECFlightItinerary> &listItineraries ) {
    listItineraries = pAirlineTicket->searchFlights(src, dest);

    for (auto &itinerary : listItineraries) {
        double price = pAirlineFin->priceItinerary(itinerary);
        itinerary.SetPrice(price);
    }

    SortItineraries(listItineraries);
}

void ECAirlineSimulator :: SortItineraries(vector< ECFlightItinerary >& itineraries) {
    sort(itineraries.begin(), itineraries.end(),
              [this](const ECFlightItinerary& a, const ECFlightItinerary& b) {
                  for (SortPreference pref : this->sortPreferences) {
                      switch (pref) {
                          case LowestPrice:
                              if (a.GetPrice() != b.GetPrice()) return a.GetPrice() < b.GetPrice();
                              break;
                          case EarliestArrival:
                              if (a.GetArrivalTime() != b.GetArrivalTime()) return a.GetArrivalTime() < b.GetArrivalTime();
                              break;
                          case ShortestFlight:
                              if (a.GetFlightTime() != b.GetFlightTime()) return a.GetFlightTime() < b.GetFlightTime();
                              break;
                          case FewestFlight:
                              if (a.GetNumSegments() != b.GetNumSegments()) return a.GetNumSegments() < b.GetNumSegments();
                              break;
                      }
                  }
                  
                  return false;
              });
}
