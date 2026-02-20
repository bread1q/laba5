#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    // Конструктор по умолчанию
    Base() {
        cout << "Base() конструктор" << endl;
    }
    
    // Конструктор от указателя
    Base(Base* obj) {
        cout << "Base(Base*) конструктор" << endl;
    }
    
    // Конструктор копирования
    Base(const Base& obj) {
        cout << "Base(Base&) конструктор копирования" << endl;
    }
    
    virtual ~Base() {
        cout << "~Base() деструктор" << endl;
    }
    
    virtual void classname() {
        cout << "Base" << endl;
    }
};

Base out1() {
    cout << "\n--- Создаем локальный Base ---" << endl;
    Base obj;
    cout << "Возвращаем obj (по значению)" << std::endl;
    return obj;  // Возвращается копия
}

Base* out2() {
    cout << "\n--- Создаем локальный Base ---" << endl;
    Base obj;
    cout << "Возвращаем &obj (указатель на локальный объект)" << std::endl;
    return &obj;  // Указатель на локальный объект - опасно
}

Base& out3() {
    cout << "\n--- Создаем локальный Base ---" << endl;
    Base obj;
    cout << "Возвращаем obj (ссылку на локальный объект)" << endl;
    return obj; // Ссылка на локальный объекты - опасно
}

Base out4() {
    cout << "\n--- Создаем динамический Base ---" << endl;
    Base* ptr = new Base();
    cout << "Возвращаем *ptr (по значению)" << endl;
    return *ptr; // возвращается копия, а оригинал в ptr не удаляется - утечка
}

Base* out5() {
    cout << "\n--- Создаем динамический Base ---" << endl;
    Base* ptr = new Base();
    cout << "Возвращаем ptr (указатель)" << endl;
    return ptr; // возвращается указатель
}

Base& out6() {
    cout << "\n--- Создаем динамический Base ---" << endl;
    Base *ptr = new Base();
    cout << "Возвращаем *ptr (ссылку)" << endl;
    return *ptr; // возвращается ссылка
}

int main() {
    cout << endl << "=== Возврат локальных объектов === " << endl << endl;

    cout << "1. out1() - возврат по значению" << endl;
    {
        Base result = out1();
        result.classname();
    }

    cout << "\n2. out2() - возврат указателя на локальный объект" << endl;
    {
        Base* result = out2(); // получаем указатель на уже уничтоженный объект
        // result->classname() - непредсказуемо, так как объект уничтожен
    }

    cout << "\n3. out3() - возврат ссылки на локальный объект" << endl;
    {
        Base& result = out3(); // получаем ссылку на уже уничтоженный объект
        // result.classname() - непредсказуемо, объект уничтожен
    }

    cout << endl << "=== Возврат динамических объектов ===" << endl << endl;

    cout << "\n4. out4() - возврат по значению" << endl;
    {
        Base result = out4(); // создается копия, оригинал не удален
        result.classname();
    } // result уничтожен, но объект Base все еще в памяти

    cout << "\n5. out5() - возврат указателя" << endl;
    {
        Base* result = out5(); // получаем указатель на объект
        result->classname();
        delete result; // удаляем вручную
    }

    cout << "\n6. out6() - возврат ссылки" << endl;
    {
        Base& result = out6(); // получаем ссылку на объект
        result.classname();
        delete &result; // удаляем объект через ссылку 
    }

    return 0;
}