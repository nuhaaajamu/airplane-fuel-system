#include "fuel.h"

class Tester {
public:
    // Tests addTank function
    bool insertWhenEmpty(); // Evaluates if insertion is still successful even when list is empty.
};

bool Tester::insertWhenEmpty(){
    // Ensure that a tank can be successfully added to an empty list.
    FuelSys obj1;
    bool result = obj1.addTank(5, 2500, 1000);
    if (result == false) {
        cout << "Error: a tank was unable to be added" << endl;
        return false;
    }

    // Now, check if current and m_current were properly updated. They should be pointing to one another.
    if (obj1.m_current == nullptr) {
        cout << "Error: m_current points to nullptr" << endl;
        return false;
    }else if (obj1.m_current != obj1.m_current->m_next){
        cout << "Error: m_current and m_current->m_next do not store the same address" << endl;
        return false;
    }

    cout << "Success: A tank was successfully added to an empty list" << endl;
    return true;
}


int main() {
    // Test addTank function

    // 1. Ensure that a tank is added successfully to an empty list.
    cout << "===== Testing addTank() =====" << endl;
    Tester test1;
    cout << "1. Inserting a tank in an empty list" << endl;
    test1.insertWhenEmpty();
}