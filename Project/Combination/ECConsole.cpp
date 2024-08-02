// Test code for console UI
#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUITextField.h"
#include "ECConsoleUIButton.h"
#include "ECAirlineSimulator.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace  std;

// construct a simple UI
static void Test1(ECConsoleUIView &viewTest, const vector<string>& departures, const vector<string>& arrivals, ECAirlineSimulator& simulator)
{
    // create several labels
    ECConsoleUITextLabel *pl1 = new ECConsoleUITextLabel(30, 1, "Soup Airline");
    pl1->SetHighlight(true);
    viewTest.AddUIItem(pl1);
    ECConsoleUITextLabel *pl2 = new ECConsoleUITextLabel(30, 13, "Itineraries");
    viewTest.AddUIItem(pl2);
    // Create a border (well, not very pretty)
    string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i)
    {
        horizBar += '-';
    }

    
    ECConsoleUITextLabel *pl4 = new ECConsoleUITextLabel(0, 0, horizBar);
    viewTest.AddUIItem(pl4);
    ECConsoleUITextLabel *pl5 = new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar);
    viewTest.AddUIItem(pl5);

    // YOU NEED TO IMPLEMENT THE FOLLOWING TO MAKE IT WORK
    
    // Add list box
    ECConsoleUITextLabel *pl6 = new ECConsoleUITextLabel(15, 5, "Departing Airport");
    viewTest.AddUIItem(pl6);

    ECConsoleUIListBox *px2 = new ECConsoleUIListBox(18, 7, 33, 9);
    for (const string& airport : departures) {
        px2->AddChoice(airport);
    }

    px2->Choose(0);
    viewTest.AddUIItem(px2);
    
    // Add a third list box
    ECConsoleUITextLabel *pl7 = new ECConsoleUITextLabel(40, 5, "Arrival Airport");
    viewTest.AddUIItem(pl7);

    ECConsoleUIListBox *px3 = new ECConsoleUIListBox(43, 7, 58, 9);
    for (const string& airport : arrivals) {
        px3->AddChoice(airport);
    }

    px3->Choose(0);
    viewTest.AddUIItem(px3);
    

    // Add list box
    ECConsoleUIListBox *itin = new ECConsoleUIListBox(15, 15, 65, 17 );
    viewTest.AddUIItem(itin);
    itin->Choose(0);

    // Add button
    ECConsoleUIButton *b1 = new ECConsoleUIButton(66, 15, 86, 17, "Search", px2, px3, itin, simulator, viewTest);
    viewTest.AddUIItem(b1);
}

void airports(const string& filename, vector<string>& departures, vector<string>& arrivals, ECAirlineSimulator& simulator) {
    ifstream file(filename);

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        stringstream ss(line);
        int type;
        ss >> type;

        switch (type) {
            case 1: {
                string code, name;
                ss >> code;
                getline(ss, name);
                if (name.size() > 0 && name[0] == ' ') {
                    name = name.substr(1);
                }

                departures.push_back(code);
                arrivals.push_back(code);
                simulator.AddAirport(name, code);
                break;
            }

            case 2: {
                string source, dest;
                int dist;
                ss >> source >> dest >> dist;
                simulator.SetDistBtwAirports(source, dest, dist);
                break;
            }

            case 3: {
                string source, dest;
                double time;
                int maxPassengers;
                double cost;
                ss >> source >> dest >> time >> maxPassengers >> cost;
                simulator.AddFlight(source, dest, time, maxPassengers, cost);
                break;
            }
        }
    }

    file.close();
}


int main(int argc, char *argv[])
{
    //
    ECTextViewImp wndTest;

    // add a status bar
    wndTest.AddStatusRow("Final Project", "For 3150 Final", true);
    
    // Create a console UI view
    ECConsoleUIView viewUI(&wndTest);


    ECAirlineSimulator simulator;
    vector<string> departures, arrivals;

    airports("airports.txt", departures, arrivals, simulator);
    
    // Add a few UI items
    Test1(viewUI, departures, arrivals, simulator);
    
    // Display it
    viewUI.Refresh();
    
    // Show the window
    try {
        wndTest.Show();
    }
    catch(std::string ex)
    {
        cout << "Exception: " << ex << endl;
    }
    return 0;
}
