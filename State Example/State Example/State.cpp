//Example State Design Pattern
//Created by Kedrick Karasek

/*
****************************************Important Information about State Design Pattern*****************************************************
1. State Design Pattern: provides exentsivility and cleaner interface to state transitions
2. State has a Context Class: "concentrator" class whose objects actually have states, passes operations to the state class.
3. Abstract State Class: an abstract class representing state with the set of abstract operations on states
4. Concrete State Class: implements the abstract operations, including changing of the state.
	- This is usually implemented as singletons - The object may be in only one state.
5. State is a behavior design pattern meaning it prescribes behavior between objects.
*********************************************************************************************************************************************
*/

#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl; using std::string;

//Forward Class Declaration
class State;

// Context Class
class Character {
public: 
	//Default constructor (defined later)
	Character();

	//Behaviors
	void skipLunch();
	void eat();
	string report();

	//part of implemtation of state pattern
	void changeState(State* state) { state_ = state; }

private:
	State* state_;
};

//Abstract State Class
class State {
public:

	//Abstract Methods
	//Provides default implementation
	virtual void skipLunch(Character*) {}
	//Provides default implementation
	virtual void eat(Character*) {}
	virtual string report() = 0;

	void changeState(Character* c, State* s) {
		c->changeState(s);
	}
};

//Concrete State Class
class Full : public State {
public:
	//SingleTon
	static State* instance() {
		static State* onlyInstance = new Full;
		return onlyInstance;
	}

	void skipLunch(Character* c) override;
	void eat(Character* c) override;
	string report() override { return "full"; }

private:
	//Privated constructors and assignment operator
	Full(){}
	Full(const Full&) {}
	Full& operator=(const Full&) {}
};

//Concrete State Class
class Hungry : public State {
public:
	//SingleTon
	static State* instance() {
		static State* onlyInstance = new Hungry;
		return onlyInstance;
	}

	void skipLunch(Character*) override;
	void eat(Character*) override;
	string report() override {return "Hungry";}

private:
	//Privated constructors and assignment operator
	Hungry() {}
	Hungry(const Hungry&) {}
	Hungry& operator=(const Hungry&) {}
};

//Concrete State Class
class Dead : public State {
public:
	//SingleTon
	static State* instance() {
		static State* onlyInstance = new Dead;
		return onlyInstance;
	}
	string report() override { return "Dead"; }

private:
	//Privated constructors and assignment operator
	Dead() {}
	Dead(const Dead&) {}
	Dead& operator=(const Dead&) {}
};

//Full State Transistion Methods implemented
void Full::skipLunch(Character* c) { changeState(c, Hungry::instance()); }
void Full::eat(Character* c) { changeState(c, Dead::instance()); }

//Hungry State Transistion Methods implemented
void Hungry::skipLunch(Character* c) { changeState(c, Dead::instance()); }
void Hungry::eat(Character* c) { changeState(c, Full::instance()); }

//Character Default Constructor Defined
Character::Character() { state_ = Hungry::instance(); }

// handles/behaviors implementation for character class
void Character::skipLunch() { state_->skipLunch(this); }
void Character::eat() { state_->eat(this); }
string Character::report() { return state_->report(); }

int main() {
	Character Zork;
	
	cout << "Zorkulus is " << Zork.report() << endl;

	while (Zork.report() != "Dead") {
		cout << "What would you like Zorkulus to do? bulk or Skip the bulk? [b/s]";
		char action; cin >> action;
		if (action == 'b') {
			Zork.eat();
		}
		else {
			Zork.skipLunch();
		}
		cout << "Zorkulus is " << Zork.report() << endl;
	}

	//demonstrating that two Characters may be in different states

	Character Kedrick;
	cout << "Zorkulus is " << Zork.report() << " while " << "Kedrick is " << Kedrick.report() << endl;
}