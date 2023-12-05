//Example Abstract Factory
//Created by Kedrick Karasek

/*
*************************Important Information about Abstract Factory Design Pattern*******************************************************************
1. Abstract Class: an abstract class provides a list of abstract functions (virtual functions) to be used by the pattern                              *
2. Concrete Class: a contrete class proivides implementation for the abstract functions                                                               *
3. Factory       : a factory is an object for creating other objects called products (contains a method for object creation)                          *
4. Factory Method: Implements the actual object creation, it usually returns a pointer to the created object,                                         *
				   it also specifies the interface to be implemented (overriden) by the subclass, this is hence known as a virtual constructor.       *
5. Abstract Factory is a creational pattern                                                                                                           *
6. Abstract Factory Design Pattern: it seperates interface and implementation                                                                         *
	1. Abstract Factory: specifies creational interface                                                                                               *
	2. Abstract Product: specifies profuct interface to be maniplated by abstract factory                                                             *
	3. Abstract Factory Method: is the product creation interface                                                                                     *
	4. Concrete factory, product, method: is the implementation of respective interfaces                                                              *
7. The benifit of the abstract factory pattern is the client may not need to know (concrete) implementations to operate objects                       *
8. Abstract Factory is often designed as a singleton pattern                                                                                          *
9. A factory may be part abstract and part concrete                                                                                                   *
*******************************************************************************************************************************************************
*/

#include <iostream>

//Abstract Product (Abstract Engine)
class AbstractEngine {
public:
	//Abstract factory methods for creating an engine
	virtual void start() const = 0;
	virtual void stop() const = 0;

	//destructor
	virtual ~AbstractEngine() {
		std::cout << "AbstractEngine Destructor Called." << std::endl;
	}
};

//Concrete Product (Concrete Engine)
class CarEngine : public AbstractEngine {
public:
	//concrete methods for car Engine
	void start() const override {
		std::cout << "Car Engine Started!" << std::endl;
	}

	void stop() const override {
		std::cout << "Car Engine Stopped!" << std::endl;
	}

	~CarEngine() {
		std::cout << "CarEngine Destructor Called." << std::endl;
	}
};

//Abstract Product (Abstract Chassis)
class AbstractChassis {
public:
	//Abstract factory methods for creating a chassis
	virtual void assemble() const = 0;
	virtual ~AbstractChassis() {
		std::cout << "AbstractChassis Destructor Called." << std::endl;
	}
};

//Concrete Product (Concrete Chassis)
class CarChassis : public AbstractChassis {
public: 
	//Concrete Methods for car chassis
	void assemble() const override {
		std::cout << "Car Chassos Assembled" << std::endl;
	}
	
	//Destructor
	~CarChassis() {
		std::cout << "CarChassis Destructor Called." << std::endl;
	}
};

//Abstract Factory
class AbstractCarFactory {
public: 
	virtual ~AbstractCarFactory() {
		std::cout << "AbstractCarFactory Destructor Called." << std::endl;
	}

protected: 
	//Abstract Factory methods for creating the engine and chassis
	AbstractEngine* createEngine() const {
		return new CarEngine();
	}

	AbstractChassis* createChassis() const {
		return new CarChassis();
	}
};

//Concrete Factory
class CarFactory : public AbstractCarFactory {
public:
	//Constructor
	CarFactory(const std::string& model, int productionYear) : model_(model), productionYear_(productionYear) {}

	//public method to create a car
	void createCar() const {
		std::cout << "Creating a " << productionYear_ << " " << model_ << " car:" << std::endl;

		//Using abstract factory methods to create the engine and chassis
		AbstractEngine* engine = createEngine();
		AbstractChassis* chassis = createChassis();

		//Assembling the car
		engine->start();
		chassis->assemble();
		engine->stop();

		//Cleaning up the created objects
		delete engine;
		delete chassis;
	}

	~CarFactory() {
		std::cout << "CarFactory Destructor Called." << std::endl;
	}

private:
	//variables specific to car model
	std::string model_;
	int productionYear_;
};

int main() {
	//creating carFactory for a 2023 sedan
	CarFactory carFactory("Sedan", 2023);
	//creating car (2023 sedan)
	carFactory.createCar();

	return 0;
}