//
//  ECAirport.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirport.h"
#include <utility>
#include <stdexcept>

using namespace std;

ECAirportInfo* ECAirportInfo :: instance = NULL;

ECAirport :: ECAirport() : operating(false) {}

ECAirport :: ECAirport(const string &nameAP, const string &codeIATA) : name(nameAP), code(codeIATA), operating(true) {}

ECAirport :: ECAirport(const ECAirport &rhs) : name(rhs.name), code(rhs.code), operating(rhs.operating) {}

string ECAirport :: GetName() const { return name; }

string ECAirport :: GetCode() const { return code; }

bool ECAirport :: IsOperating() { return operating; }

void ECAirport :: SetOperating(bool f) { operating = f; }

ECAirportInfo& ECAirportInfo :: GetInstance() {
    if ( instance == NULL ) {
        instance = new ECAirportInfo();
    }

    return *instance;
}

void ECAirportInfo :: CreateAirport(const string &name, const string &code) {
    airports[code] = ECAirport(name, code);
}

ECAirport& ECAirportInfo :: GetAirport(const string &code) const {
    auto port = airports.find(code);
    if (port == airports.end()) {
        throw string("This is not a valid code.");
    }

    return const_cast< ECAirport& >(port->second);
}

void ECAirportInfo :: SetDistanceBtw(const string &ap1Code, const string &ap2Code, int dist) {
    distances[make_pair(ap1Code, ap2Code)] = dist;
    distances[make_pair(ap2Code, ap1Code)] = dist;
}

int ECAirportInfo :: GetDistanceBtw(const string &ap1Code, const string &ap2Code) const {
    auto key = make_pair(ap1Code, ap2Code);

    if (distances.find(key) != distances.end()) {
        return distances.at(key);
    }

    throw string("Distance not found");
}