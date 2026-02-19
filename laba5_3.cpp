#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    virtual string classname() {
        return "Base";
    }

    virtual bool isA(const string& name) {
        return name == "Base";
    }
};

class Derived : public Base {
public:
    string classname() override {
        return "Derived";
    }

    bool isA(const string& name) override {
        return name == "Derived" || Base::isA(name);
    }
};

class SuperDerived : public Derived {
public:
    string classname() override {
        return "SuperDerived";
    }

    bool isA(const string& name) override {
        return name == "SuperDerived" || Derived::isA(name);
    }
};

int main() {
    Base* obj = new SuperDerived();

    cout << endl << "obj classname() = " << obj->classname() << endl;
    cout << boolalpha; // для вывода true или false вместо 1/0

    cout << endl << "=== Проверка через classname() ===" << endl;
    cout << "obj является SuperDerived? " << (obj->classname() == "SuperDerived") << endl; // да - верно
    cout << "obj является Derived? " << (obj->classname() == "Derived") << endl; // нет - неверно, является объектомDerived
    cout << "obj является Base? " << (obj->classname() == "Base") << endl; // нет - неверно, является объектом Base

    cout << endl << "Проверка через isA():" << endl;
    cout << "obj является SuperDerived? " << obj->isA("SuperDerived") << endl; // да - верно
    cout << "obj является Derived? " << obj->isA("Derived") << endl; // да - верно
    cout << "obj является Base? " << obj->isA("Base") << endl; // да - верно
}