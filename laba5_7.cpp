#include <iostream>
#include <memory>

using namespace std;

class Base {
public:
    Base() { 
        cout << "Base()\n"; 
    }
    virtual ~Base() { 
        std::cout << "~Base()\n"; 
    }

    void classname() const { 
        cout << "Base\n"; 
    }
};

// Функции для демонстрации
void takeUnique(unique_ptr<Base> ptr) {
    cout << "takeUnique получила ptr\n";
} // здесь ptr уничтожается, объект удаляется

void takeShared(shared_ptr<Base> ptr) {
    cout << "takeShared получила ptr, счетчик: " << ptr.use_count() << "\n";
}

int main() {
    cout << "\n=== UNIQUE_PTR ===\n\n";
    {
        cout << "Блок 1:\n";
        auto ptr1 = make_unique<Base>();
        cout << "ptr1: " << ptr1.get() << endl;
        // auto ptr2 = ptr1; // нельзя копировать
        auto ptr2 = move(ptr1); // можно перемещать
        cout << "ptr1: " << ptr1.get() << ", ptr2: " << ptr2.get() << "\n";
    } // ptr2 уничтожается, объект удален
    
    {
        cout << "\nБлок 2 (передача в функцию):\n";
        auto ptr = make_unique<Base>();
        takeUnique(move(ptr));  // владение уходит в функцию
        cout << "ptr после move: " << ptr.get() << "\n";
    }
    
    cout << "\n=== SHARED_PTR ===\n";
    {
        cout << "\nБлок 3:\n";
        auto ptr1 = make_shared<Base>();
        cout << "счетчик: " << ptr1.use_count() << "\n";
        
        auto ptr2 = ptr1;  // можно копировать
        cout << "после копирования: " << ptr1.use_count() << "\n";
        
        takeShared(ptr1);  // внутри функции счетчик увеличивается
        cout << "после функции: " << ptr1.use_count() << "\n";
    } // ptr1 и ptr2 уничтожены, объект удален
    
    return 0;
}