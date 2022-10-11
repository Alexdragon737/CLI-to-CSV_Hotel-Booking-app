#include "../include/hotelBooking.h"

using namespace booking;

int main()
{
    // Open the file in append mode so that the CSV file is not rewritten at the start of the program.
    std::fstream file("..\\assets\\bookings.csv",std::ios::app);

    emptyFileRoutine(file);

    //std::map<std::string, int> options;
    // Don't forget to close the file when done to avoid memory leaks.
    file.close();

    addBookingEntry();

    return 0;   
}