#include "fuel.h"

class Tester {
public:
    // Tests addTank function
    bool insertWhenEmpty(); // Evaluates if insertion is still successful even when list is empty.
    bool insertMultipleTanks();  // Evaluates whether the tank is properly added to the end of the list.
};

bool Tester::insertWhenEmpty(){
    // Ensure that a tank can be successfully added to an empty list.
    FuelSys obj1;
    bool result = obj1.addTank(5, 2500, 1000);
    if (result == false) {
        cout << "Error: The tank was unable to be added" << endl;
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

bool Tester::insertMultipleTanks() {
    // Check that m_current is being updated properly as each tank is added by evaluating the ID.
    FuelSys obj1;

    // Add first tank and evaluate.
    if (obj1.addTank(10, 3000, 500) == false) {
        cout << "Error: First tank was not added successfully" << endl;
        return false;
    }else if (obj1.m_current->m_tankID != 10) {
        cout << "Error: Incorrect data assigned to the first tank inserted" << endl;
        return false;
    }

    // Add second tank and evaluate.
    if (obj1.addTank(20, 4000, 1000) == false) {
        cout << "Error: Second tank was not added successfully" << endl;
        return false;
    }else if (obj1.m_current->m_tankID != 20) {
        cout << "Error: Incorrect data assigned to the second tank inserted" << endl;
        return false;
    }

    // Add third tank and evaulate.
    if (obj1.addTank(30, 5000, 1500) == false) {
        cout << "Error: Third tank was not added successfully" << endl;
        return false;
    }else if (obj1.m_current->m_tankID != 30) {
        cout << "Error: Incorrect data assigned to the third tank inserted" << endl;
        return false;
    }

    cout << "Success: Three tanks have been inserted successfully" << endl;
    return true;
}

int main() {
    // Test addTank function

    // 1. Ensure that a tank is added successfully to an empty list.
    cout << "===== Testing addTank() =====" << endl;
    Tester test;

    cout << endl << "1. Inserting a tank in an empty list" << endl;
    test.insertWhenEmpty();

    cout << endl << "2. Inserting multiple tanks consecutively" << endl;
    test.insertMultipleTanks();

}