//Example Mediator Design Pattern
//Created by Kedrick Karasek

/*
*************************Important Information about Mediator Design Pattern*******************************************************************
1. God Object: is a class that has too many resposibilities, and too many functions.
	- the other objects in the program rely on god object for information and interactions
	- the code is tightly coupled, coe maintenance becomes difficult
2. Anti-Pattern: a commonly used technique, although initally apealing, it has more bad consequences than good ones, there is a more effective solution
3. A God Object is and Anti-Pattern
4. Mediator is when you define objects that encasulate how other objects interact and prevenets objects from reffering to each other. 
5. terms:
	1. Abstract Medator: defines interface communicating between colleague objects
	2. Concrete mediator: implements and coordinates communication between colleagues
	3. Colleague Classes: each colleague knows mediator and each colleague communicates with mediator to reach other colleagues
6. may use push and pull method communication
7. If mediator is abused it may turn into a God Object
 *******************************************************************************************************************************************************
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
#include <set>
#include <vector>

using std::cout; using std::cin; using std::endl;
using std::string;

//Abstract Mediator
class Controller {
public:
	virtual void join(class Flight*) = 0;
	virtual void leave(class Flight*) = 0;
	virtual void broadcast() = 0;
	virtual void observe() = 0;
};

//Concrete Mediator
class Tower : public Controller {
public:
	void join(class Flight*) override;
	void leave(class Flight*) override;
	void broadcast() override;
	void observe() override;
private:
	std::set<class Flight*> waiting_;
};

// abstract colleague
class Flight {
public:
	Flight(Controller* controller) :controller_(controller), status_(Status::waiting) {
		task_ = rand() % 2 ? Task::taxiing : Task::approaching;
		controller_->join(this);
	}
	void receive(const string& msg) {
		if (msg.find(flightNo_) != string::npos || msg.find("all") != string::npos) {
			if (msg.find("clear") != string::npos) {
				cout << flightNo_ << " roger that, ";
				cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
				status_ = Status::cleared;
			}
			else if (msg.find("status") != string::npos) {
				cout << flightNo_
					<< (status_ == Status::waiting ? " waiting to " : " cleared to ")
					<< (task_ == Task::taxiing ? "take off" : "land") << endl;
			}
			else
				cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
		}
	}
	bool isCleared() const { return status_ == Status::cleared; }
	void proceed() {
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1)); // wait a while    
		cout << flightNo_
			<< (task_ == Task::taxiing ? " took off" : " landed")
			<< ". Have a good day!" << endl;
		controller_->leave(this);
	}

protected:
	string flightNo_;
	Controller* controller_;
	enum class Task { taxiing, approaching };  Task task_;
	enum class Status { waiting, cleared };    Status status_;
};

//Concrete collegue
class Airbus : public Flight {
public:
	Airbus(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "AirFrance", "KLM", "Aeroflot", "Lufthansa" };
		flightNo_ = companies[rand() % companies.size()] +
			std::to_string(rand() % 1000);
		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};

//Concrete collegue
class Boeing : public Flight {
public:
	Boeing(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "Delta", "United", "JetBlue" };
		flightNo_ = companies[rand() % companies.size()] +
			std::to_string(rand() % 1000);
		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};


// member functions for Tower
void Tower::broadcast() {
	cout << "Tower: ";
	string msg;
	getline(cin, msg);
	if (!msg.empty())
		for (auto f : waiting_) f->receive(msg);
}


void Tower::observe() {
	auto findCleared = [](Flight* f) {return f->isCleared(); };

	auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);

	while (toProceed != waiting_.end()) { // found a cleared flight
		(*toProceed)->proceed();
		toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
		if (toProceed != waiting_.end())
			cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single flight cleared
	}
}


void Tower::join(Flight* f) {
	waiting_.insert(f);
}


void Tower::leave(Flight* f) {
	waiting_.erase(f);
	delete f;
}

int main() {
	srand(time(nullptr));
	Tower jfk;

	new Boeing(&jfk);
	new Airbus(&jfk);
	new Boeing(&jfk);
	new Airbus(&jfk);

	while (true) {
		jfk.broadcast();
		jfk.observe();
		if (rand() % 2) {
			if (rand() % 2)
				new Boeing(&jfk);
			else
				new Airbus(&jfk);
		}
	}
}