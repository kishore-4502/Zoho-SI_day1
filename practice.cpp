#include <iostream>
using namespace std;

// TODO 1.Create a class for vehicle which contains vehicleType (petrol, diesel ,ev ,…), brand , model, color, mileage, price.
class Vehicle
{
public:
    string vehicleType;
    string brand;
    string model;
    string color;
    int mileage;
    int price;
    // TODO 5.Create a abstract method getNoOfWheels in vehicles which has to be overridden in derive class
    virtual int getNoOfWheels() = 0;
    Vehicle(string vehicleType, string brand, string model, string color, int mileage, int price)
    {
        this->vehicleType = vehicleType;
        this->brand = brand;
        this->model = model;
        this->color = color;
        this->mileage = mileage;
        this->price = price;
    }
};

// TODO 2.Derive car and bike from vehicle
// TODO 3.Car should have attributes no of persons, carType(suv, sedan, etc),

class Car : public Vehicle
{
public:
    int noOfPersons;
    string carType;
    Car(string vehicleType, string brand, string model, string color, int mileage, int price, int noOfPersons, string carType)
        : Vehicle(vehicleType, brand, model, color, mileage, price)
    {
        this->noOfPersons = noOfPersons;
        this->carType = carType;
    }
    int getNoOfWheels()
    {
        return 4;
    }
    string getBrand()
    {
        return brand;
    }
};

// TODO 4.Bike should have attributes weight, bikeType(scooter, motorbikes, etc)
class Bike : public Vehicle
{
public:
    int weight;
    string bikeType;
    Bike(string vehicleType, string brand, string model, string color, int mileage, int price, int weight, string bikeType)
        : Vehicle(vehicleType, brand, model, color, mileage, price)
    {
        this->weight = weight;
        this->bikeType = bikeType;
    }
    int getNoOfWheels()
    {
        return 2;
    }
    string getBrand()
    {
        return brand;
    }
};

// TODO 6.Using operator overloading (<<) to display, brand, model, type, color, price.
ostream &operator<<(ostream &COUT, Car c1)
{
    COUT << "VehicleType : " << c1.vehicleType << endl;
    COUT << "Brand : " << c1.brand << endl;
    COUT << "Model : " << c1.model << endl;
    COUT << "type : " << c1.carType << endl;
    COUT << "Color : " << c1.color << endl;
    COUT << "Price : " << c1.price << endl;
    COUT << "No_Of_Persons : " << c1.noOfPersons << endl;
    COUT << "Mileage : " << c1.mileage << endl;
    return COUT;
}

ostream &operator<<(ostream &COUT, Bike b1)
{
    COUT << "VehicleType : " << b1.vehicleType << endl;
    COUT << "Brand : " << b1.brand << endl;
    COUT << "Model : " << b1.model << endl;
    COUT << "type : " << b1.bikeType << endl;
    COUT << "Color : " << b1.color << endl;
    COUT << "Price : " << b1.price << endl;
    COUT << "Weight : " << b1.weight << endl;
    COUT << "Mileage : " << b1.mileage << endl;
    return COUT;
}

// TODO 7.Using operator overloading (< (less than) or > (greater than) ) two vehicles can be compared, return true or false based on price of the vehicle.
bool operator<(Car &c1, Bike &b1)
{
    return c1.price < b1.price;
}
bool operator>(Car &c1, Bike &b1)
{
    return c1.price > b1.price;
}
bool operator<(Bike &b1, Car &c1)
{
    return b1.price < c1.price;
}
bool operator>(Bike &b1, Car &c1)
{
    return b1.price > c1.price;
}

// TODO 8.In main function , create some objects for car and bike , print the noofWheels , compare two vehicles.
int main()
{
    cout.setf(ios::boolalpha);
    Car car1 = Car("Diesel", "b1", "m1", "black", 15, 1500000, 6, "suv");
    Bike bike1 = Bike("Petrol", "b2", "m2", "blue", 20, 200000, 250, "motorbike");
    // cout << car1;
    // cout << "\n";
    // cout << bike1;
    // cout << "\n";
    // TODO Print Operation:
    cout << car1 << bike1 << endl;

    // TODO No of Wheels:
    cout << (car1.getNoOfWheels()) << endl;
    cout << (bike1.getNoOfWheels()) << endl;

    // TODO Compare Operations:
    cout << (car1 > bike1) << endl;
    cout << (car1 < bike1) << endl;
    cout << (bike1 > car1) << endl;
    cout << (bike1 < car1) << endl;

    return 0;
}