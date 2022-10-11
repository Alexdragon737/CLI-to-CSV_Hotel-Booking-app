#include "../include/hotelBooking.h"


std::ostream& operator<<(std::ostream& os, const booking::Customer& cust)
{
    os << '"' << "Name: " << cust.name << booking::newLineOp << "Address: " << cust.address << booking::newLineOp << "Phone number: " << cust.phoneNumber << booking::newLineOp << '"' << booking::csvSeparator;
    return os;
}

std::ostream& operator<<(std::ostream& os, const booking::Room& room)
{
    os << '"' << "Number of people: " <<room.peopleNumber << booking::newLineOp << "Prefer AC:";
    if(room.preferAC == true)
        os << "Yes";
    else os << "No";
    os << booking::newLineOp << "Room price: " <<room.price << booking::newLineOp << "Room number: " <<room.roomNumber << '"' << booking::csvSeparator;
    return os;
}

std::ostream& operator<<(std::ostream& os, const booking::PaymentStatus& pay)
{
    os << '"';
    if(pay.fullyPaid == true)
        os << "Yes";
    else os << "No";
    os << "Paid amount: " << pay.paidAmount << booking::newLineOp << "Left amount: " << pay.leftAmount << booking::newLineOp << '"' << booking::csvSeparator;
    return os;
}

std::ostream& operator<<(std::ostream& os, const booking::Period& period)
{
    os << '"' << "From: " << period.startDate << booking::newLineOp;
    os << "To: " << period.endDate << '"' << booking::csvSeparator;
    return os;
}

booking::Customer::Customer()
{
    name = "N/A";
    address = "N/A";
    phoneNumber = "N/A";
}

booking::Customer::Customer(std::string& name, std::string& address, std::string& phoneNumber)
{
    this->name = name;
    this->address = address;
    this->phoneNumber = phoneNumber;
}

booking::Room::Room()
{
    peopleNumber = 0;
    roomNumber = 0;
    price = 0;
    preferAC = false;
}

booking::Room::Room(int& peopleNumber, bool& preferAC)
{
    this->peopleNumber = peopleNumber;
    this->roomNumber = rand()%250+1;
    this->preferAC = preferAC;
    this->price = 100*peopleNumber + 50*(int)preferAC;
}

booking::PaymentStatus::PaymentStatus()
{
    fullyPaid = false;
    paidAmount = 0;
    leftAmount= 0;
}

booking::PaymentStatus::PaymentStatus(int& price, int& paidAmount)
{
    this->paidAmount = paidAmount;
    this->leftAmount = price - this->paidAmount;
    if(this->leftAmount != 0)
        this->fullyPaid = false;
    else this->fullyPaid = true;
}

booking::Period::Period()
{
    this->startDate = "1/1/1970";
    this->endDate = "2/1/1970";
}

booking::Period::Period(std::string& startDate, int& daysToStay)
{
    this->startDate = startDate;
    char dateSeparator;
    int day, month, year;
    std::stringstream ss(startDate);
    ss >> day >> dateSeparator >> month >> dateSeparator >> year;
    day += daysToStay;
    if(day > 31)
    {
        day -= 31;
        month++;
        if(month > 12)
        {
            month -= 12;
            year++;
        }
    }
    this->endDate = std::to_string(day) + dateSeparator + std::to_string(month) + dateSeparator + std::to_string(year); 
}

void booking::emptyFileRoutine(std::fstream& file)
{
    // Go to the end of the file
    file.seekg(0,std::ios::end);
    
    // If after reaching the end we are still at the position 0 in input sequence then do what needs to be done.
    if(file.tellg() == 0)
    {
        std::cout << "File is empty, information needs to be written into it. \n Writing the separator line and headers." << std::endl;
        file << "sep=" << booking::csvSeparator << booking::newLineOp;
        file << "ID"  << booking::csvSeparator << "Customer information" << booking::csvSeparator << "Room details" << booking::csvSeparator << "Payment status" << booking::csvSeparator << "Time to stay" << booking::newLineOp;
        std::ofstream idValue("../assets/currentID.txt");
        idValue << 1;
    }
}

void booking::addBookingEntry()
{
    std::fstream paramFile("..\\assets\\bookings.csv",std::ios::app);
    int entriesNumber;
    
    int id = initID();

    try
    {
        std::cout << "Please input how many entries you want to add: " << std::endl;
        std::cin >> entriesNumber;
        // This is used in order to remove the stray '\n' that is inserted after reading input and messes with the further input
        std::cin.ignore(1,'\n');
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
        clearScreen();
        addBookingEntry();
    }
    
    for(int i=0;i<entriesNumber;i++)
    {
        // Initialize objects
        booking::Customer cust;
        booking::Room room; 
        booking::PaymentStatus pay;
        booking::Period time;

        std::cout << "Current entry: " << i+1 << std::endl;
        std::cout << "Input the name, address and phone number of the customer number " << i+1 << std::endl;
        std::vector<std::string> custAttrib;

        // Do this for 3 strings
        for(int j=0;j<3;j++)
        {
            std::string value;
            std::getline(std::cin, value);
            custAttrib.push_back(value);
        }

        cust = booking::Customer(custAttrib[0],custAttrib[1],custAttrib[2]);

        // People
        int people;
        bool preferAC;
        std::cout << "Input the number of people in the room. Inputs need to be numeric. " << std::endl;
        std::cin >> people;

        std::cout << "Input the preference for using the AC. Accepted inputs are 1 for \"true\" or 0 for \"false\"." << std::endl;
        std::cin >> preferAC;
        room = booking::Room(people,preferAC);

        // Payment status
        int price = room.price;
        int paidAmount;
        std::cout << "Please input the amount that the customer number " << i+1 << " has paid. Input needs to be numeric. " << std::endl;
        std::cin >> paidAmount;

        pay = booking::PaymentStatus(price, paidAmount);
        
        // Period
        int startDay, startMonth, startYear, daysToStay;
        std::string startingDate;
        char dateSeparator; 
        std::cout << "Input the starting date. The formats needs to be d/m/yyyy (example: 1/1/1970" << std::endl;
        std::cin >> startingDate;


        std::cout << "Input how many days does the client number " << i+1 << " want to stay." << std::endl;
        std::cin >> daysToStay;
        time = booking::Period(startingDate, daysToStay);

        std::cin.ignore(1,'\n');
        updateID();

        paramFile << id << booking::csvSeparator;
        paramFile << cust << room << pay << time << booking::newLineOp;

        std::cout << "Entry number " << i+1 << " added" << std::endl;
    }
    paramFile.close();
    std::cout << "All entries added" << std::endl;
}

void booking::removeBookingEntry(std::fstream& file, int& lineToRemove)
{
    std::string container;
    file.open("..\\assets\\bookings.csv", std::ios::app);
    
}

int booking::initID()
{
    int id;
    std::ifstream file;
    file.open("..\\assets\\currentID.txt");
    file >> id;
    file.close();
    return id;
}

void booking::updateID()
{
    int id;
    std::fstream oldFile("..\\assets\\currentID.txt", std::ios::in);
    oldFile >> id;
    oldFile.close();
    id++;
    std::fstream newFile("..\\assets\\currentID.txt",std::ios::out);
    newFile << id;
    newFile.close();
}

void clearScreen()
{
    std::cout << std::string(100,'\n');
}