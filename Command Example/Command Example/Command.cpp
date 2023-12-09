//Example Command Design Pattern
//Created by Kedrick Karasek

/*
*************************Important Information about Command Design Pattern*******************************************************************
1. Command Design Pattern: allows to make request to receiver by turning request itself into an object called command
2. We Use This if you need
	- specify, keep, queue, execute requests at different time, the command encapsulates the request
	- support undo and command history
	- support logging/rollback/recovery, these are know and log commands
	- support transaction processing systems (ticket vooking, backing, ...)
	- When you need to issue request (command) on an object from a place that does not know about the action or the object (receiver) of the request
3. Terms:
	1. Command: delcares an interface for executing the operation, declares execute()
	2. Concrete Command: implements execute(), acts on receiver
	3. Client: creates the concrete command object and sets up its reveiver
	4. Reveiver: object on which operations (commands) are performed
	5. Invoker: asks to execute the command 
 *******************************************************************************************************************************************************
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

//Recevier Object
class Document {
public:

	Document(const vector <string>& lines = {}) : lines_(lines) {}

	// actions
	void insert(int line, const string& str) {
		const int index = line - 1;
		if (index <= lines_.size())
			lines_.insert(lines_.begin() + index, str);
		else
			cout << "line out of range" << endl;
	}

	const string remove(int line) {
		const int index = line - 1;
		string deletedLine = "";
		if (index < lines_.size()) {
			// deletedLine = lines_[index];
			deletedLine = *(lines_.begin() + index); // same thing but with iterator arithmetic
			lines_.erase(lines_.begin() + index);
		}
		else
			cout << "line out of range" << endl;
		return deletedLine;
	}

	void show() {
		for (int i = 0; i < lines_.size(); ++i)
			cout << i + 1 << ". " << lines_[i] << endl;
	}

private:
	vector<string> lines_;
};

//Abstract Command
class Command {
public:
	//Default Constructor
	Command(Document* doc) : doc_(doc) {}
	
	//Abstract Methods
	virtual void execute() = 0;
	virtual void unexecute() = 0;

	//Abstract Destructor
	virtual ~Command(){}
protected:
	Document* doc_;
};

//Concrete Command
class InsertCommand : public Command {
public:
	InsertCommand(Document* doc, int line, const string& str) : Command(doc), line_(line), str_(str) {}
	void execute() override { doc_->insert(line_, str_); }
	void unexecute() override { doc_->remove(line_); }
private:
	int line_;
	string str_;
};

//Concrete Command
class EraseCommand : public Command {
public:
	EraseCommand(Document* doc, int line) : Command(doc), line_(line), str_("") {}
	void execute() override { doc_->remove(line_); }
	void unexecute() override { doc_->insert(line_, str_); }
private:
	int line_;
	string str_;
};

//Client Class
class DocumentWithHistory {
public:
	DocumentWithHistory(const vector<string>& text = {}) : doc_(text) {}

	void insert(int line, string str) {
		Command* com = new InsertCommand(&doc_, line, str);
		com->execute();
		doneCommands_.push(com);
	}

	void erase(int line) {
		Command* com = new EraseCommand(&doc_, line);
		com->execute();
		doneCommands_.push(com);
	}

	void undo() {
		if (doneCommands_.size() != 0) {
			Command* com = doneCommands_.top();
			doneCommands_.pop();
			com->unexecute();
			delete com; // don't forget to delete command
		}
		else
			cout << "no commands to undo" << endl;
	}

	void show() { doc_.show(); }

private:
	Document doc_;
	std::stack<Command*> doneCommands_;
};

// invoker
int main() {
	DocumentWithHistory his({
	  "Lorem Ipsum is simply dummy text of the printing and typesetting",
	  "industry. Lorem Ipsum has been the industry's standard dummy text",
	  "ever since the 1500s, when an unknown printer took a galley of",
	  "type and scrambled it to make a type specimen book. It has",
	  "survived five centuries." });

	char option;
	do {
		his.show();
		cout << endl;

		cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command: ";
		cin >> option;

		int line; string str;
		switch (option) {
		case 'i':
			cout << "line number to insert: ";
			cin >> line;
			cout << "line to insert: ";
			cin.get(); // removes end-of-line character so getline() works correctly
			getline(cin, str);
			his.insert(line, str);
			break;

		case 'e':
			cout << "line number to remove: ";
			cin >> line;
			his.erase(line);
			break;

		case 'u':
			his.undo();
			break;
		}

	} while (option == 'i' || option == 'e' || option == 'u');
}
