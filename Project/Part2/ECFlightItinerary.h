//
//  ECFlightItinerary.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlightItinerary_h
#define ECFlightItinerary_h

#include <vector>
#include <string>

class ECFlight;
class ECAirlineFinancial;

// ****************************************************************************
// Flight itineary: consisting segments of flights so to go from one airport to another airport

class ECFlightItinerary
{
public:
    ECFlightItinerary();
    
    // access/edit segments
    void addSegments(const ECFlight& flight);

    // Return the number of segments of the itineary
    int GetNumSegments() const;
    
    // Return a segment
    const ECFlight* GetSegment(int segIndex) const;
    
    // Get flight time: from departure to arrival
    double GetFlightTime() const;
    
    // Get segment time: add the time of all segments
    double GetTimeAllSegments() const;
    
    // Get departure time
    double GetDepartTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Price 
    double GetPrice() const;
    
    void SetPrice(double newPrice);

    void Dump() const;


    
private:
    // your code
    std::vector< ECFlight > flightSegs;

    double price;

};

#endif /* ECFlightItinerary_h */
