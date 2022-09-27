#include "../include/hotelBooking.h"

using namespace booking;

BookingEntry::BookingEntry()
{
    srand(time(NULL));
    entryID = rand()%1000000;
    cust = Customer();
    room = Room();
    pay = PaymentStatus();
    period = Period();
}

BookingEntry::BookingEntry(Customer& cust, Room& room, PaymentStatus& pay, Period& period)
{
    std::fstream currentIDfile("../assets/currentID.txt");
    currentIDfile >> entryID;
    currentIDfile << entryID++;

    this->cust = Customer(cust.name, cust.address, cust.phoneNumber);
    this->room = Room(room.peopleNumber, room.roomNumber, room.preferAC);
    this->pay = PaymentStatus(room.price, pay.paidAmount);
    this->period = Period();
}

Customer::Customer()
{
    name = "N/A";
    address = "N/A";
    phoneNumber = "N/A";
}

Customer::Customer(std::string& name, std::string& address, std::string& phoneNumber)
{
    this->name = name;
    this->address = address;
    this->phoneNumber = phoneNumber;
}

Room::Room()
{
    peopleNumber = 0;
    roomNumber = 0;
    price = 0;
    preferAC = false;
}

Room::Room(int& peopleNumber, int& roomNumber, bool& preferAC)
{
    this->peopleNumber = peopleNumber;
    this->roomNumber = roomNumber;
    this->preferAC = preferAC;
}

PaymentStatus::PaymentStatus()
{
    fullyPaid = false;
    paidAmount = 0;
    leftAmount= 0;
}

PaymentStatus::PaymentStatus(int price, int paidAmount)
{
    if(price == paidAmount)
    {
        leftAmount = 0;
        fullyPaid = true;
    }    
    else
    {
        leftAmount = price-paidAmount;
        fullyPaid = false;
    } 
}

Period::Period()
{
    time_t now = std::time(0);
    timeStart = std::localtime(&now);
    timeEnd = std::localtime(&now);
}

Period::Period(int& startDay, int& startMonth, int& startYear, int& startHour, int& startMinute, int& daysToStay)
{
    this->timeStart->tm_mday = startDay;
    this->timeStart->tm_mon = startMonth;
    this->timeStart->tm_year = startYear;
    this->timeStart->tm_hour = startHour;
    this->timeStart->tm_min = startMinute;

    if(timeStart->tm_mday + daysToStay > 31)
    {
        timeEnd->tm_mday = timeStart->tm_mday + daysToStay - 31;
        timeEnd->tm_mon++;
        if(timeEnd->tm_mon > 12)
            timeEnd->tm_year++;
        timeEnd->tm_hour = startHour;
        timeEnd->tm_min = startMinute;
    }

}

std::ostream& operator<<(std::ostream& os, const booking::BookingEntry& entry)
{
    // Push the entryID
    os << entry.entryID << csvSeparator;

    // Push the Customer components
    os << '"' << "Name: " << entry.cust.name << newLineOp << "Address: "<< entry.cust.address << newLineOp << "Phone number: " << entry.cust.phoneNumber << '"' << csvSeparator;

    // Push the Room components and handle the booleans
    os << '"' << "Room number: "<<entry.room.roomNumber << newLineOp << "People number: " <<entry.room.peopleNumber << newLineOp << "Prefer AC: ";
    if(entry.room.preferAC == true)
        os << "Yes";
    else os << "No";
    os << newLineOp << "Price: " << entry.room.price <<'"' << csvSeparator;

    // Push the PaymentStatus components and handle the booleans
    os << '"' << "Fully paid: ";
    if(entry.pay.fullyPaid == true)
        os << "Yes";
    else os << "No";
    os << newLineOp << "Paid amount: " <<entry.pay.paidAmount << newLineOp << "Left amount: " <<entry.pay.leftAmount << '"' << csvSeparator;


    os << '"';

    // Check-in date & time 
    os << "From: " << entry.period.timeStart->tm_mday << '/' << entry.period.timeStart->tm_mon << '/' << entry.period.timeStart->tm_year 
    << ' ' << entry.period.timeStart->tm_hour << ':' << entry.period.timeStart->tm_min;

    // Check-out date & time
    os << newLineOp << "To: " << entry.period.timeEnd->tm_mday << '/' << entry.period.timeEnd->tm_mon << '/' << entry.period.timeEnd->tm_year << ' '
    << entry.period.timeEnd->tm_hour << ':' << entry.period.timeEnd->tm_min;

    os << '"' << csvSeparator << newLineOp;
    return os;
};

void emptyFileCheck(std::fstream& file)
{
    file.seekg(0,std::ios::end);
    if(file.tellg() == 0)
    {
       file << "sep=" << csvSeparator << newLineOp;
       file << "ID"  << csvSeparator << "Customer information" << csvSeparator << "Room details" << csvSeparator << "Payment status" << csvSeparator << "Time to stay" << newLineOp;
    }    
}

void addBookingEntry()
{
    
}