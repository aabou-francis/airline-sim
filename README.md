# Airline Simulator with Booking UI

Welcome to the Airline Simulator project! This application is a flight booking simulator that allows users to search for and book flights between different airports. The project is built using C++ and follows object-oriented design principles. It features a simple, user-friendly interface that makes the booking process straightforward and intuitive.

## Features

- **Flight Search Algorithm:** Efficiently searches and filters available flights based on user-selected departure and arrival airports and times.
- **User-Friendly Interface:** A simple and intuitive UI that allows users to easily navigate through the flight booking process.

## Technologies Used

- **Programming Language:** C++
- **Development Tools:** Visual Studio Code
- **Design:** Object-Oriented Design principles

## Installation

To run this project locally, follow these steps:

1. **Clone the repository:**

   `git clone` [https://github.com/aabou-francis/airline-sim.git](https://github.com/aabou-francis/airline-sim.git)
   
   `cd Combination`

3. **Build the project:**
   
   `g++ ECConsoleUITextLabel.cpp ECTextViewImp.cpp ECConsoleUIView.cpp  ECConsole.cpp ECConsoleUIListBox.cpp ECConsoleUITextField.cpp ECObserver.h ECAirlineSimulator.cpp ECAirlineOperation.cpp ECAirlineTicketing.cpp ECAirlineFinancial.cpp ECFlight.cpp ECFlightItinerary.cpp ECAirport.cpp ECConsoleUIButton.cpp -o test`

4. **Run the application:**

   After building, run `./test` to launch the application

5. **Using the application:**

    When the application opens up, use `CTRL A` to navigate between UI features (i.e. scroll boxes and search button)

## Usage

1. **Launch the Application:**
   Start the application from the terminal

2. **Search for Flights:**
   Edit the files with airports and times your liking.
   
   Select your desired departure and arrival airports then hit search. The application will display available flights and their times.

## Challenges

During the development of this project, several challenges were encountered, including:

- **UI Design:** Iterating on the UI to make it as intuitive and user-friendly as possible.
- **Algorithm Optimization:** Ensuring the flight search algorithm was optimized for speed and accuracy.

## Future Enhancements

Potential improvements and features to add:

- **Advanced Pricing Models:** Implement more complex pricing algorithms based on demand, time, and other factors.
- **Expand Booking Process** Allow users to select flights and reserve seats
- **Database Integration:** Replace CSV files with a database for better scalability and performance.
- **Enhanced UI:** Add more features to the UI, such as sorting and filtering options for flights.
