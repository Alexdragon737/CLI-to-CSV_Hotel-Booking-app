#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<map>

namespace booking
{
    /** 
     * Depending on the software used for viewing CSV files (Excel, LibreOffice and others) the separator might be set to ';'.
     * 
     * The separator can be declared at the beginning of the CSV file in order to avoid changing settings and creating compatibility
     * problems with XLS, XLSX and other formats.
     */
    const char csvSeparator = ',';
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
            Room(int& peopleNumber, int& roomNumber, bool& preferAC);
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

            PaymentStatus(int roomPrice, int paidAmount);
    };

    class Period{
        public:
            std::tm* timeStart;
            std::tm* timeEnd;

            Period();

            Period(int& startDay, int& startMonth, int& startYear, int& startHour, int& startMinute,
                    int& daysToStay);
    };

    class BookingEntry{
        public:
            int entryID;
            Customer cust;
            Room room;
            PaymentStatus pay;
            Period period;

            // Construct a new BookingEntry object with default values.
            BookingEntry();

            BookingEntry(Customer& cust, Room& room, PaymentStatus& PaymentStatus, Period& period);
    };

};

// Operator<< overloading for BookingEntry objects. Avoid refactoring unless it's absolutely necessary.
std::ostream& operator<<(std::ostream& os, const booking::BookingEntry& entry);

// Check if the file is empty to determine if 'sep=(char)' line will be inserted. 
void emptyFileCheck(std::fstream& file);


void addBookingEntry();


void removeBookingEntry();