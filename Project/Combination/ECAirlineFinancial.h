//
//  ECAirlineFinancial.h
//  
//
//  Created by Yufeng Wu on 5/16/23.
//

#ifndef ECAirlineFinancial_h
#define ECAirlineFinancial_h

#include "ECFlightItinerary.h"

// ****************************************************************************
// Airline finanical: budgetting, pricing and money bookkeeping


class ECAirlineFinancial {
public:
    double priceItinerary(const ECFlightItinerary& itinerary) const;

private:
    static constexpr double PRICE_PER_HOUR = 120.0;
};

#endif
