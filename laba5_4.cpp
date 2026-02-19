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

    void derivedMethod() {
        cout << "Метод только класса Derived" << endl;
    }
};

class Other : public Base {
public:
    std::string classname() override {
        return "Other";
    }

    bool isA(const std::string& name) override {
        return name == "Other" || Base::isA(name);
    }
};

int main() {
    Base* basePtr = new Derived();  // указатель на Base, но объект Derived
    Base* otherPtr = new Other();   // указатель на Base, но объект Other

    cout << "=== Опасное приведение === " << endl << endl;
    Derived* obj1 = static_cast<Derived*>(basePtr); // скомпилируется правильно
    Derived* obj2 = static_cast<Derived*>(otherPtr); // скомпилируется, но неправильно

    cout << "obj1: " << endl;
    obj1->derivedMethod();

    cout << "obj2: " << endl;
    // dangerous2->derivedMethod();  // непредсказуемое поведение 
    cout << "static_cast Other к Derived - объект не того типа" << endl;

    cout << endl << "=== Безопасное приведение через isA() ===" << endl << endl;
    if (otherPtr->isA("Derived")) {
        Derived* safe = static_cast<Derived*>(otherPtr);
        safe->derivedMethod();
    } else {
        cout << "otherPtr не является Derived, приведение невозможно" << endl;
    }
    
    if (basePtr->isA("Derived")) {
        Derived* safe = static_cast<Derived*>(basePtr);
        cout << "basePtr является Derived, можно привести: " << endl;
        safe->derivedMethod();
    }

    cout << endl << "=== Безопасное приведение с помощью dynamic_cast ===" << endl << endl;
    
    // dynamic_cast возвращает nullptr если приведение невозможно
    Derived* dc1 = dynamic_cast<Derived*>(basePtr);
    if (dc1) {
        cout << "basePtr -> Derived успешно: " << endl;
        dc1->derivedMethod();
    }
    
    Derived* dc2 = dynamic_cast<Derived*>(otherPtr);
    if (dc2) {
        cout << "otherPtr -> Derived успешно" << endl;
    } else {
        cout << "otherPtr -> Derived: невозможно - dynamic_cast вернул nullptr" << endl;
    }
}