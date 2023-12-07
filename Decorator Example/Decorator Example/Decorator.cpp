//Example Decorator Design Pattern
//Created by Kedrick Karasek

/*
****************************************Important Information about Decorator Design Pattern*****************************************************
1. Decorator needs run-time extension (decoration) of functionality of an object (component)
2. Approch: subclass decorator and then reference the original component,
			Decorator invokeds the original component methods optionallt decorating it before or after invocation.
3. Decorator is a structural pattern
4. Decorators/Components can be abstract and concrete
*********************************************************************************************************************************************
*/

//Example exam problem answer

#include<iostream>
#include<string>

using std::string; using std::cout; using std::endl;

//Abstract Decorator
class ChristmasTree {
public:
    ChristmasTree() : tree_("_\|/_") {} // initializes the tree
    virtual string show() const { return tree_; }
private:
    string tree_;
};

// First decorator
class TinselDecorator : public ChristmasTree {
public:
    TinselDecorator(const ChristmasTree* tree) : tree_(tree) {}
    string show() const override {
        return decorateWithTinsel(tree_->show());
    }
private:
    string decorateWithTinsel(const string& original) const {
        return original + " ~";
    }
    const ChristmasTree* tree_;
};

// Second decorator
class LightsDecorator : public ChristmasTree {
public:
    LightsDecorator(const ChristmasTree* tree) : tree_(tree) {}
    string show() const override {
        return decorateWithLights(tree_->show());
    }
private:
    string decorateWithLights(const string& original) const {
        return original + " *";
    }
    const ChristmasTree* tree_;
};

int main() {
    // Create a simple Christmas tree
    ChristmasTree simpleTree;

    // Decorate the tree with tinsel and lights
    TinselDecorator tinselTree(&simpleTree);
    LightsDecorator decoratedTree(&tinselTree);

    // Print out the decorated tree
    cout << "Simple Tree: " << simpleTree.show() << endl;
    cout << "Decorated Tree: " << decoratedTree.show() << endl;

    return 0;
}
