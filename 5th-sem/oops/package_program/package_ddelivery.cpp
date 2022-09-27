#include <bits/stdc++.h>
using namespace std;

// Package Delivery Services
// create an inheritance hierarchy for package delivery services
// base class: Package
// derived classes: TwoDayPackage, OvernightPackage

class Package
{
private:
    string senderName;
    string senderAddress;
    string senderCity;
    string senderState;
    string senderZip;
    string recipientName;
    string recipientAddress;
    string recipientCity;
    string recipientState;
    string recipientZip;
    double weight;
    double costPerOunce;

public:
    Package(string, string, string, string, string, string, string, string, string, string, double, double);
    void setSenderName(string);
    string getSenderName();
    void setSenderAddress(string);
    string getSenderAddress();
    void setSenderCity(string);
    string getSenderCity();
    void setSenderState(string);
    string getSenderState();
    void setSenderZip(string);
    string getSenderZip();
    void setRecipientName(string);
    string getRecipientName();
    void setRecipientAddress(string);
    string getRecipientAddress();
    void setRecipientCity(string);
    string getRecipientCity();
    void setRecipientState(string);
    string getRecipientState();
    void setRecipientZip(string);
    string getRecipientZip();
    void setWeight(double);
    double getWeight();
    void setCostPerOunce(double);
    double getCostPerOunce();
    double calculateCost();
    void print();
};

Package::Package(string sName, string sAddress, string sCity, string sState, string sZip, string rName, string rAddress, string rCity, string rState, string rZip, double w, double cpo)
{
    senderName = sName;
    senderAddress = sAddress;
    senderCity = sCity;
    senderState = sState;
    senderZip = sZip;
    recipientName = rName;
    recipientAddress = rAddress;
    recipientCity = rCity;
    recipientState = rState;
    recipientZip = rZip;
    weight = w;
    costPerOunce = cpo;
}

void Package::setSenderName(string sName)
{
    senderName = sName;
}

string Package::getSenderName()
{
    return senderName;
}

void Package::setSenderAddress(string sAddress)
{
    senderAddress = sAddress;
}

string Package::getSenderAddress()
{
    return senderAddress;
}

void Package::setSenderCity(string sCity)
{
    senderCity = sCity;
}

string Package::getSenderCity()
{
    return senderCity;
}

void Package::setSenderState(string sState)
{
    senderState = sState;
}

string Package::getSenderState()
{
    return senderState;
}

void Package::setSenderZip(string sZip)
{
    senderZip = sZip;
}

string Package::getSenderZip()
{
    return senderZip;
}

void Package::setRecipientName(string rName)
{
    recipientName = rName;
}

string Package::getRecipientName()
{
    return recipientName;
}

void Package::setRecipientAddress(string rAddress)
{
    recipientAddress = rAddress;
}

string Package::getRecipientAddress()
{
    return recipientAddress;
}

void Package::setRecipientCity(string rCity)
{
    recipientCity = rCity;
}

string Package::getRecipientCity()
{
    return recipientCity;
}

void Package::setRecipientState(string rState)
{
    recipientState = rState;
}

string Package::getRecipientState()
{
    return recipientState;
}

void Package::setRecipientZip(string rZip)
{
    recipientZip = rZip;
}

string Package::getRecipientZip()
{
    return recipientZip;
}

void Package::setWeight(double w)
{
    weight = w;
}

double Package::getWeight()
{
    return weight;
}

void Package::setCostPerOunce(double cpo)
{
    costPerOunce = cpo;
}

double Package::getCostPerOunce()
{
    return costPerOunce;
}

double Package::calculateCost()
{
    return weight * costPerOunce;
}

void Package::print()
{
    cout << "Sender Name: " << senderName << endl;
    cout << "Sender Address: " << senderAddress << endl;
    cout << "Sender City: " << senderCity << endl;
    cout << "Sender State: " << senderState << endl;
    cout << "Sender Zip: " << senderZip << endl;
    cout << "Recipient Name: " << recipientName << endl;
    cout << "Recipient Address: " << recipientAddress << endl;
    cout << "Recipient City: " << recipientCity << endl;
    cout << "Recipient State: " << recipientState << endl;
    cout << "Recipient Zip: " << recipientZip << endl;
    cout << "Weight: " << weight << endl;
    cout << "Cost Per Ounce: " << costPerOunce << endl;
    cout << "Total Cost: " << calculateCost() << endl;

    // print in a table format
    // cout << left << setw(20) << senderName << setw(20) << senderAddress << setw(20) << senderCity << setw(20) << senderState << setw(20) << senderZip << setw(20) << recipientName << setw(20) << recipientAddress << setw(20) << recipientCity << setw(20) << recipientState << setw(20) << recipientZip << setw(20) << weight << setw(20) << costPerOunce << setw(20) << calculateCost() << endl;
}

class TwoDayPackage : public Package
{
private:
    double flatFee;

public:
    TwoDayPackage(string, string, string, string, string, string, string, string, string, string, double, double, double);
    void setFlatFee(double);
    double getFlatFee();
    double calculateCost();
    void print();
};

TwoDayPackage::TwoDayPackage(string sName, string sAddress, string sCity, string sState, string sZip, string rName, string rAddress, string rCity, string rState, string rZip, double w, double cpo, double ff) : Package(sName, sAddress, sCity, sState, sZip, rName, rAddress, rCity, rState, rZip, w, cpo)
{
    flatFee = ff;
}

void TwoDayPackage::setFlatFee(double ff)
{
    flatFee = ff;
}

double TwoDayPackage::getFlatFee()
{
    return flatFee;
}

double TwoDayPackage::calculateCost()
{
    return Package::calculateCost() + flatFee;
}

void TwoDayPackage::print()
{
    Package::print();
    cout << "Flat Fee: " << flatFee << endl;
    cout << "Total Cost: " << calculateCost() << endl;
}

class OvernightPackage : public Package
{
private:
    double extraFee;

public:
    OvernightPackage(string, string, string, string, string, string, string, string, string, string, double, double, double);
    void setExtraFee(double);
    double getExtraFee();
    double calculateCost();
    void print();
};

OvernightPackage::OvernightPackage(string sName, string sAddress, string sCity, string sState, string sZip, string rName, string rAddress, string rCity, string rState, string rZip, double w, double cpo, double ef) : Package(sName, sAddress, sCity, sState, sZip, rName, rAddress, rCity, rState, rZip, w, cpo)
{
    extraFee = ef;
}

void OvernightPackage::setExtraFee(double ef)
{
    extraFee = ef;
}

double OvernightPackage::getExtraFee()
{
    return extraFee;
}

double OvernightPackage::calculateCost()
{
    return Package::calculateCost() + (extraFee * Package::getWeight());
}

void OvernightPackage::print()
{
    // print in cool format
    Package::print();
    cout << "Extra Fee: " << extraFee << endl;
    cout << "Total Cost: " << calculateCost() << endl;
}

int main()
{
    Package package1("John Smith", "123 Main St", "Anytown", "NY", "12345", "Jane Doe", "456 Elm St", "Anytown", "NY", "12345", 5, 2.5);
    TwoDayPackage package2("John Smith", "123 Main St", "Anytown", "NY", "12345", "Jane Doe", "456 Elm St", "Anytown", "NY", "12345", 5, 2.5, 5);
    OvernightPackage package3("John Smith", "123 Main St", "Anytown", "NY", "12345", "Jane Doe", "456 Elm St", "Anytown", "NY", "12345", 5, 2.5, 1);

    // take user input for package all packages
    string sName, sAddress, sCity, sState, sZip, rName, rAddress, rCity, rState, rZip;
    double w, cpo, ff, ef;

    cout << "Enter the sender's name: ";
    getline(cin, sName);
    cout << "Enter the sender's address: ";
    getline(cin, sAddress);
    cout << "Enter the sender's city: ";
    getline(cin, sCity);
    cout << "Enter the sender's state: ";
    getline(cin, sState);
    cout << "Enter the sender's zip: ";
    getline(cin, sZip);
    cout << "Enter the recipient's name: ";
    getline(cin, rName);
    cout << "Enter the recipient's address: ";
    getline(cin, rAddress);
    cout << "Enter the recipient's city: ";
    getline(cin, rCity);
    cout << "Enter the recipient's state: ";
    getline(cin, rState);
    cout << "Enter the recipient's zip: ";
    getline(cin, rZip);
    cout << "Enter the weight of the package: ";
    cin >> w;
    cout << "Enter the cost per ounce: ";
    cin >> cpo;
    cout << "Enter the flat fee: ";
    cin >> ff;
    cout << "Enter the extra fee: ";
    cin >> ef;

    Package package4(sName, sAddress, sCity, sState, sZip, rName, rAddress, rCity, rState, rZip, w, cpo);
    TwoDayPackage package5(sName, sAddress, sCity, sState, sZip, rName, rAddress, rCity, rState, rZip, w, cpo, ff);
    OvernightPackage package6(sName, sAddress, sCity, sState, sZip, rName, rAddress, rCity, rState, rZip, w, cpo, ef);

    // print all packages
    cout << "Package 1" << endl;
    package1.print();
    cout << endl;
    cout << "Package 2" << endl;
    package2.print();
    cout << endl;
    cout << "Package 3" << endl;
    package3.print();
    cout << endl;
    cout << "Package 4" << endl;
    package4.print();
    cout << endl;
    cout << "Package 5" << endl;
    package5.print();
    cout << endl;
    cout << "Package 6" << endl;
    package6.print();
    cout << endl;
    return 0;
}
