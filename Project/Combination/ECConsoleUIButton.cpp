//
//  ECConsoleUIButton.cpp
//  
//
//  Created by Yufeng Wu on 3/6/24.
//

#include <string>
#include "ECConsoleUIButton.h"
#include "ECAirlineSimulator.h"
#include <ostream>
#include <sstream>
#include <iomanip>

using namespace std;

//*****************************************************************************
// Console UI button: 

// specifiy the portion of the view for this list box
ECConsoleUIButton :: ECConsoleUIButton(int xUL, int yUL, int xLR, int yLR, const std::string &strButIn, ECConsoleUIListBox* depart, ECConsoleUIListBox* arrive, ECConsoleUIListBox* i, ECAirlineSimulator& s, ECConsoleUIView& view) 
    : ECConsoleUIItem(xUL, yUL, xLR, yLR), strButton(strButIn), departureList(depart), arrivalList(arrive), itin(i), simulator(s), view(view)
{
}

// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUIButton :: GetTextAtRow(int r) const
{
    // there is only one line
    std::string str;
    int rconv = r - GetYUL();

    if( rconv <0 || /*rconv >= 1 ||*/ rconv >= GetHeight() )
    {
        return str;
    }

    // add a row of '----' right above/below
    if( rconv == 1 || rconv == GetHeight()-2 )
    {
        str += '+';
        for( int i=1 ; i<GetWidth() - 1; ++i)
        {
            str += '-';
        }
        str += '+';
    }
    else
    {
        // begin with a '|'
        //str += '|';

        // align to the center
        if( strButton.size() < GetWidth())
        {
            str += '|';
            for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
        }

        str += strButton;
        for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
            str += ' ';

        // end with a '|'
        str += '|';
    }

    // ensure the str is not too long
    str = str.substr(0, GetWidth());
    return str;
}

// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUIButton :: GetHighlightPosition(int &xLeft, int &xRight) const
{
    return -1;
}

// Handle enter key
void ECConsoleUIButton :: HdlKeyEnter() {   
    string source = departureList->getAirport();
    string dest = arrivalList->getAirport();

    vector<ECFlightItinerary> itineraries;

    simulator.SearchForFlights(source, dest, itineraries);
    
    itin->clear();

    for (const auto& itinerary : itineraries) {        
        string result = dump(itinerary);
        itin->AddChoice(result);
    }
    
    if (itineraries.empty()){
        string result = "No Itineraries Found";
        itin->AddChoice(result);
    }

    view.Refresh();
}

string ECConsoleUIButton :: dump(const ECFlightItinerary& itinerary) {
    if (itinerary.GetNumSegments() == 0) {
        return "No Itineraries Found";
    }
    
    int dhour = static_cast<int>(itinerary.GetDepartTime());
    int dmin = static_cast<int>((itinerary.GetDepartTime() - dhour) * 60);

    int ahour = static_cast<int>(itinerary.GetArrivalTime());
    int amin = static_cast<int>((itinerary.GetArrivalTime() - ahour) * 60);

    std::stringstream pricestr;
    pricestr << fixed << setprecision(2) << itinerary.GetPrice();
    string str = pricestr.str();

    string res = "Leaving at " + to_string(dhour) + ":" + (dmin < 10 ? "0" : "") + to_string(dmin) + ", arriving at " + to_string(ahour) + ":" + (amin < 10 ? "0" : "") + to_string(amin) + " for $" + str;
    
    return res;
}
