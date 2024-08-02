//
//  ECAirport.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECAirport_h
#define ECAirport_h

#include <string>
#include <set>
#include <map>
#include <utility>


// ****************************************************************************
// Airport: start/end point of a flight

class ECAirport 
{
public:
    // by default, airport is operating (except in default constructor)
    ECAirport(); 
    ECAirport(const std::string &nameAP, const std::string &codeIATA);
    ECAirport(const ECAirport &rhs);
    
    // Get the name of the airport
    std::string GetName() const;
    
    // Get IATA code
    std::string GetCode() const;
    
    // Operating status: is it operating normally?
    bool IsOperating();
    
    // Set operating status
    void SetOperating(bool f);
    
private:
    // your ocde
    std::string name;
    std::string code;

    bool operating;
};

// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

class ECAirportInfo
{
public:
    
    static ECAirportInfo& GetInstance();

    // Create a new airport in the system
    void CreateAirport(const std::string &name, const std::string &code);
    
    // Get airport by code
    // Throw exception (std::string) if there is no airport with the code
    ECAirport &GetAirport(const std::string &code) const;
    
    // Set distance (in miles) between airports
    void SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist);
    
    int GetDistanceBtw(const std::string &ap1code, const std::string &ap2Code) const;
    
private:
   // your code 
   static ECAirportInfo* instance;

   std::map< std::string, ECAirport > airports;
   std::map< std::pair< std::string, std::string >, int > distances;

   ECAirportInfo() {}
};

#endif /* ECAirport_h */