#include "../include/hotelBooking.h"

using namespace booking;

int main()
{
    bool programExecuting = true;
    while(programExecuting)
    {
        int choice;
        std::cout << "Welcome to the HotelEntry++ program. Simplifying the process of adding hotel booking entries since 2022" << std::endl;
        std::cout << "Please input your desired choice" << std::endl;
        std::cout << "1. Add entry" << std::endl;
        std::cout << "2. Quit program" << std::endl;
        std::cin >> choice;
        switch(choice)
        {
            case 1:
                {
                    // Open the file in append mode so that the CSV file is not rewritten at the start of the program.
                    std::fstream file("..\\assets\\bookings.csv",std::ios::app);

                    emptyFileRoutine(file);

                    //std::map<std::string, int> options;
                    // Don't forget to close the file when done to avoid memory leaks.
                    file.close();

                    addBookingEntry();
                }
                break;
            case 2:
                std::cout << "Thank you for using our solutions. See you next time!" << std::endl;
                programExecuting = false;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
                break;
        }
    };
    return 0;   
}