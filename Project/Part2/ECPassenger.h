//
//  ECPassenger.h
//  
//
//  Created by Yufeng Wu on 5/15/23.
//  Airline passenger of differen types

#ifndef ECPassenger_h
#define ECPassenger_h

#include <string>

#include "ECObserver.h"
#include "ECFlightItinerary.h"

class ECAirlineTicketing;

//****************************************************************************
typedef enum
{
    EC_PASSENGER_UNBOOKED = 0,
    EC_PASSENGER_BOOKED = 1
} EC_PASSENGER_STATUS;

//****************************************************************************
// Passenger: generic
class ECPassenger
{
public:
    ECPassenger(const std::string &srcAirportIn, const std::string &destAirportIn);
    virtual ~ECPassenger();
    
    // Book with the airline; return true if booked; false otherwise
    // Template method pattern
    bool Book(ECAirlineTicketing &airlineTicketing);
    
    // Get current itinerary
    const ECFlightItinerary &GetItinerary() const { return this->itin; }
    
    // Get status
    EC_PASSENGER_STATUS GetStatus() const { return this->status; }
    
    // Dump out info
    void Dump() const;

protected:
    std::string srcAirport;
    std::string destAirport;
    ECFlightItinerary itin;
    EC_PASSENGER_STATUS status;
};

// Passenger: budget (with a fixed upper limit on budget)
class AddPassengerBudget : public ECPassenger
{
public:
    AddPassengerBudget(const std::string &srcAirportIn, const std::string &destAirportIn, double budgetIn);
    
    bool Book(ECAirlineTicketing &airlineTicketing);
    void Dump() const;

private:
    std::string srcAirport;
    std::string destAirport;
    double budget;
};

// Passenger: business (with a deadline to arrive on time; i.e., must arrive by certain time)
class AddPassengerBusiness : public ECPassenger
{
public:
    AddPassengerBusiness(const std::string &srcAirportIn, const std::string &destAirportIn, double tmArrivalLatestIn);

    virtual bool Book(ECAirlineTicketing &airlineTicketing);
    virtual void Dump() const;

private:
    std::string srcAirport;
    std::string destAirport;
    double tmArrivalLatest;
};

// Passenger: comfort (with upper bounds on departure time, flight time and number of segments)
class AddPassengerComfort : public ECPassenger
{
public:
    AddPassengerComfort(const std::string &srcAirportIn, const std::string &destAirportIn, double tmEarliestDepartIn, double maxFlightTimeIn, int maxSegmentsIn);

    virtual bool Book(ECAirlineTicketing &airlineTicketing);
    virtual void Dump() const;

private:
    std::string srcAirport;
    std::string destAirport;
    double tmEarliestDepart;
    double maxFlightTime;

    int maxSegments;
};

#endif /* ECPassenger_h */
