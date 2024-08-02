//
//  ECFlight.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlight_h
#define ECFlight_h

#include <string>


// ****************************************************************************
// Flight: service between two airports at a specific time;

class ECFlight 
{
public:
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn);
    
    virtual ~ECFlight();
    
    // Get departure time
    double GetDepartureTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Set max passenger for this flight
    void SetMaxNumPassengers(int m);
    
    // Get src airport code
    std::string GetSource() const;
    
    // Get destination code
    std::string GetDest() const;

    // more to add...    

    double GetFlightDuration() const;

    void bookFlight();

    void Dump() const;

private:
    // your code
    int maxPass;

    std::string source;
    std::string dest;

    double departure;
    double arrival;

    bool booked;
};

#endif /* ECFlight_h */
