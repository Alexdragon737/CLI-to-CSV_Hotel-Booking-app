#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<map>
#include<vector>
#include<sstream>

namespace booking
{
    /** 
     * Depending on the software used for viewing CSV files (Excel, LibreOffice and others) the separator might be set to ';'.
     * 
     * The separator can be declared at the beginning of the CSV file in order to avoid changing settings
     * and creating compatibility problems with XLS, XLSX and other formats.
     */
    const char csvSeparator = ',';

    // Expands to "\n"
    const char newLineOp = '\n';

    class Customer{
        public:
            std::string name, address, phoneNumber;

            // Construct a new Customer object with default values.
            Customer();

            /**
             * @brief Construct a new Customer object
             * 
             * @param name The name of the Customer.
             * @param address The address of the Customer.
             * @param phoneNumber The phone nunber of the Customer.
             */
            Customer(std::string& name, std::string& address, std::string& phoneNumber);

    };

    class Room{
        public:
            int peopleNumber, roomNumber, price;
            bool preferAC;

            /**
             * @brief Construct a new Room object with default values.
             * 
             */
            Room();

            /**
             * @brief Construct a new Room object
             * 
             * @param peopleNumber 
             * @param roomNumber 
             * @param preferAC 

             */
            Room(int& peopleNumber, bool& preferAC);
    };

    class PaymentStatus
    {
        public:
            bool fullyPaid;
            int paidAmount, leftAmount;

            /**
             * @brief Construct a new Payment Status object with default values.
             * 
             */
            PaymentStatus();

            PaymentStatus(int& roomPrice, int& paidAmount);
    };

    class Period{
        public:
            std::string startDate, endDate;

            Period();

            Period(std::string& startDate, int& daysToStay);
    };
    /**
    * @brief Check if the file is empty. If true, then the separator line is appended to the file and reset the currentID.
    * 
    * @param file The file that is checked.
    * 
    */
    void emptyFileRoutine(std::fstream& file);
    
    // Add one or more entries to the Bookings CSV file.
    void addBookingEntry();
    
    // Remove one or more entries from the Bookings CSV file.
    void removeBookingEntry(std::fstream& file, int& lineToRemove);
    
    // Explicitly initialize the ID by reading it from the currentID.txt file.
    int initID();
    
    // Update the ID when necessary by rewriting the currentID.txt file.
    void updateID();
    
};

// Operator<< overloading for Customer objects
std::ostream& operator<<(std::ostream& os, const booking::Customer& cust);

// Operator<< overloading for Room objects
std::ostream& operator<<(std::ostream& os, const booking::Room& room);

// Operator<< overloading for PaymentStatus objects
std::ostream& operator<<(std::ostream& os, const booking::PaymentStatus& pay);

// Operator<< overloading for Period objects
std::ostream& operator<<(std::ostream& os, const booking::Period& period);

/*
    "Clear" the screen by inserting 100 lines of '\\n'.

    Even though it's not the most elegant solution, clearing the actual console is a challenge
    considering that most methods are either deprecated (e.g. clrscr() from conio.h) or unsafe
    (e.g. system("cls") from stdlib.h).
*/
void clearScreen();