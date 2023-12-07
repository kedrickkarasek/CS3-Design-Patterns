//Example Observer Design Pattern and Registry Design Pattern
//Created by Kedrick Karasek

/*
****************************************Important Information about Observer Design Pattern*****************************************************
1. Elaborated type specifier: allows to state foward declaration class right in the place of variable declaration
	- You must repeat for every variable declaration
	- It makes forward declaration easier to read
	ex. B(class A *p) : p_(p) {}
2. Motivation: objects (observers) need to synchronize behavior with some other object (subject): observe changing subject's state
3. In observer, observers subscribe to change state notifications, while subjects publish changes by notifying observers or sending them messages
4. Another name for this pattern is publish/subsribe
5. abstract overser/subject: implement registation/notification functionality
6. concrete observer/subject: implement subject state and state acquisition by observer
7. Observer is a behavioral pattern
8. there may be a registry of subjects for observers to subscribe to 
9.Communication methods: Push and Pull
	- push: state change is in a message itself and may require large message, not all concrete observers need all the data subject may push a reference to itself
	- pull: observer quieries the state of subject after receiving notification, the observer needs to keep reference to subject and the subject needs to implement getters
*********************************************************************************************************************************************
*/

/*
****************************************Important Information about Registry Design Pattern*****************************************************
1. Registry is non-canonical design pattern
2. Resistry is a well-know object that other objects use to find common objects and services
3. Resistry is implemented by it usually being a global object,
	it may be implemented as a singleton,
	objects to be looked up register with the registry,
	object lookup is performed by key,
	key-ed map is often used as implementation,
	may be used to pass information to objects without lookup
3. Evaluation
	- global object: creates external dependencies
	-may be prefferred to passing them around as parameters
*********************************************************************************************************************************************
*/

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using std::cout; using std::endl;
using std::map; using std::set;
using std::string;

//Forward Class Delcarations
class Observer;
class Subject;

//Registry, We make everything static because we only want one registry
class EventRegistry {
public:
	static void registerObserver(Subject*, Observer*);
	static void deregisterObserver(Subject*, Observer*);
	static void handleMessage(Subject*);

private:
	static map<Subject*, set<Observer*>> observerMap_;
};

//Initializing the static map
map < Subject*, set<Observer*>> EventRegistry::observerMap_;

//Observer Class
class Observer {
public:
	//Defualt Constructor
	Observer(const string& name) : name_(name) {}

	//Method
	string getName() const { return name_; }

	//Need for observer pattern
	void subscribe(Subject* s) { EventRegistry::registerObserver(s, this); }
	void unsubscribe(Subject* s) { EventRegistry::deregisterObserver(s, this); }
	void handleMessage(Subject*);
private:
	string name_;
};

//Subject Class
class Subject {
public:
	//Default Constructor
	Subject(const string& name) : name_(name) {}

	//Method
	string getName() const { return name_; }

	//Need for Observer Pattern in subject
	void generateMessage() {
		cout << name_ << " send a message" << endl;
		EventRegistry::handleMessage(this);
	}
private:
	string name_;
};

//Out of line definition for registerObserver
void EventRegistry::registerObserver(Subject* s, Observer* o) {
	observerMap_[s].insert(o);
	cout << o->getName() << " subscribed to " << s->getName() << endl;
}
//Out of line definition for deregisterObserver
void EventRegistry::deregisterObserver(Subject* s, Observer* o) {
	observerMap_[s].erase(o);
	cout << o->getName() << " unsubscribed from " << s->getName() << endl;
}
//Out of line definition for handleMessage for EventRegistry
void EventRegistry::handleMessage(Subject* s) {
	for (auto e : observerMap_[s]) {
		e->handleMessage(s);
	}
}
//Out of line definition for handleMessage for Observer
void Observer::handleMessage(Subject* s) {
	cout << name_ << " received message from " << s->getName() << endl;
}

int main() {
	//Creating two Subjects
	Subject sue("Subject Sue"), steve("Subject Steve");
	//Creating two Observers
	Observer olaf("Observer Olaf"), olga("Observer Olga");

	//olaf subscribes to sue and steeve
	olaf.subscribe(&sue);
	olaf.subscribe(&steve);
	//olga subscribes to sue
	olga.subscribe(&sue);

	cout << endl;

	//sue and steve generate messages
	sue.generateMessage();
	steve.generateMessage();
	cout << endl;

	//olga unsubscribes from sue
	olga.unsubscribe(&sue);
	//sue generates messages
	sue.generateMessage();
}
