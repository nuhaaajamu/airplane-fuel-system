#include "fuel.h"
#include <vector>

class Tester {
public:
    // Tests for addTank function
    bool insertWhenEmpty(); // Evaluates if insertion is still successful even when the list is empty
    bool insertMultipleTanks();  // Evaluates whether each tank is properly added to the end of the list
    bool validateInputError(); // Handles the error cases of the input passed in (ID, capacity, fuel)
    bool validateInputEdge(); // Handles the edge cases of the inputs passed in (ID, capacity, fuel)

    // Tests for removeTank function
    bool removeAll(); // Tests whether all tanks are removed correctly.


    // Tests for totalFuel function
    bool calculateFuelEmpty(); // Evaluates fuel amount for when no tank exists (error case)
    bool calculateFuel(); // Evaluates if total is calculated accurately (normal case)


    // Test whether totalFuel() works correctly for a normal case. It returns the correct value.
    // Test whether totalFuel() works correctly for an error case. It returns zero where there is no tank in the system.


    // Tests for findTank() function
    bool findTankNormal(); // Tests whether it works correctly for a normal case.
    bool findTankError(); // Tests whether the function accounts for a tank that does not exist in the fuel system.
};

bool Tester::insertWhenEmpty(){
    // Ensure that a tank can be successfully added to an empty list.
    FuelSys obj;
    bool result = obj.addTank(5, 2500, 1000);
    if (result == false) {
        cout << "Error: The tank was unable to be added" << endl;
        return false;
    }

    // Now, check if current and m_current were properly updated. They should be pointing to one another.
    if (obj.m_current == nullptr) {
        cout << "Error: m_current points to nullptr" << endl;
        return false;
    }else if (obj.m_current != obj.m_current->m_next){
        cout << "Error: m_current and m_current->m_next do not store the same address" << endl;
        return false;
    }

    cout << "Success: A tank was successfully added to an empty list" << endl;
    return true;
}

bool Tester::insertMultipleTanks() {
    // Check that m_current is being updated properly as each tank is added by evaluating the ID.
    FuelSys obj;

    // Add first tank and evaluate.
    if (obj.addTank(10, 3000, 500) == false) {
        cout << "Error: First tank was not added successfully" << endl;
        return false;
    }else if (obj.m_current->m_tankID != 10) {
        cout << "Error: Incorrect data assigned to the first tank inserted" << endl;
        return false;
    }

    // Add second tank and evaluate.
    if (obj.addTank(20, 4000, 1000) == false) {
        cout << "Error: Second tank was not added successfully" << endl;
        return false;
    }else if (obj.m_current->m_tankID != 20) {
        cout << "Error: Incorrect data assigned to the second tank inserted" << endl;
        return false;
    }

    // Add third tank and evaulate.
    if (obj.addTank(30, 5000, 1500) == false) {
        cout << "Error: Third tank was not added successfully" << endl;
        return false;
    }else if (obj.m_current->m_tankID != 30) {
        cout << "Error: Incorrect data assigned to the third tank inserted" << endl;
        return false;
    }

    cout << "Success: Three tanks have been inserted successfully" << endl;
    return true;
}

bool Tester::validateInputError() {
    // 1. Pass in an invalid ID (less than zero) and evaluate if addTank() properly guards against it.
    FuelSys obj1;
    if (obj1.addTank(-1, 3000, 500) == true) {
        cout << "Error: An invalid ID was assigned" << endl;
        return false;
    }

    // 2. Pass in an invalid tank capacity (less than MIN_CAP) and evaluate if addTank() properly guards against it.
    FuelSys obj2;
    if (obj2.addTank(10, 1000, 500) == true) {
        cout << "Error: An invalid tank capacity was assigned" << endl;
        return false;
    }

    // 3. Pass in an invalid fuel capacity (fuel > capacity) and evaluate if addTank() properly guards against it.
    FuelSys obj3;
    if (obj3.addTank(10, 3000, 5000) == true) {
        cout << "Error: An invalid amount of tank fuel was assigned" << endl;
        return false;
    }

    cout << "Success: No valid input was assigned" << endl;
    return true;
}

bool Tester::validateInputEdge() {
    // 1. Pass in the edge case for ID and evaluate if addTank() tries to guard against it.
    //    tankID must be greater than or equal to zero, so the edge case is when they are equal.
    FuelSys obj1;
    if (obj1.addTank(0, 3000, 1000) == false) {
        cout << "Error: The function guarded against zero as a value for m_tankID" << endl;
        return false;
    }

    // 2. Pass in the edge case for tank capacity and evaluate if addTank() tries to guard against it.
    //    tankCapacity must be greater than or equal to MINCAP, so the edge case is when they are equal.
    FuelSys obj2;
    if (obj2.addTank(10, MINCAP, 1000) == false) {
        cout << "Error: The function guarded against the minimum capacity being a value for m_tankCapacity" << endl;
        return false;
    }


    // 3. Pass in the edge case for tank fuel and evaluate if addTank() tries to guard against it.
    //    tankFuel must be less than or equal to tankCapacity, so the edge case in when they are equal.
    FuelSys obj3;
    if (obj3.addTank(10, 3000, 3000) == false) {
        cout << "Error: The function guarded against m_tankFuel being equal to m_tankCapacity" << endl;
        return false;
    }

    cout << "Success: All edge cases for valid input were not guarded against. Values were assigned." << endl;
    return true;
}

bool Tester::removeAll() {
    FuelSys obj1;
    vector <int> objID{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Populate the fuel system.
    for (int i = 0; i < 10; i++) {
        obj1.addTank(i, 2000, 500);
    }

    // Remove tanks one by one.
    for (int j = 10; j >= 0; j--) {
        bool result = obj1.removeTank(j);
        objID.pop_back();

        // Test value of remove function
        if (result == false) {
            cout << "removeTank() returned false (tank " << j << ")" << endl;
            return false;
        }

        // Search for ID and see if it still exists.
        if (obj1.findTank(j) == true) {
            cout << "The tank ID still exists in the linked list (tank " << j << ")" << endl;
        }


        // Ensure that list order was preserved after removal
        Tank * traverse = obj1.m_current;
        for (int k = 0; k < 10; k++) {

        }

        do {
            if (j == traverse->m_tankID) {
                return false;
            }
            traverse = traverse->m_next;

        }while (traverse != obj1.m_current->m_next);


        // Update vector to reflect removal.


        // Check m_current for case in which we remove last tank.

    }

    if (obj1.removeTank(0) == false) {
        cout << "Tank 0 was not successfully removed." << endl;
        return false;
    }

    // Test value of remove function

    // Determine whether size of list decreased.

}

bool calculateFuelEmpty() {
    FuelSys obj;
    int result = obj.totalFuel();

    if (result == 0) {
        cout << "Success: total fuel calculated for a non-existent tank is zero" << endl;
        return true;
    }

    cout << "Error: total fuel calculated for a non-existent tank is not zero";
    return false;
}

bool calculateFuel() {
    FuelSys obj;
    int expectedTotal = 600;

    obj.addTank(1, 2000, 100);
    obj.addTank(2, 2000, 200);
    obj.addTank(3, 2000, 300);

    bool result = obj.totalFuel();

    if (result != expectedTotal) {
        cout << "Error: total fuel was calculated incorrectly" << endl;
        return false;
    }

    cout << "Success: total fuel was calculated correctly" << endl;
    return true;
}

bool Tester::findTankNormal() {
    // Populate the list with tanks.
    FuelSys obj;
    for (int ID = 0; ID < 50; ID++) {
        obj.addTank(ID, 2000, 500);
    }

    // Search for each tank and check to see if the found tank is the next node of the current node in the list.
    for (int ID = 0; ID < 50; ID++) {

        // Ensure that a tank was found.
        if (obj.findTank(ID) == false) {
            cout << "Error: findTank() returned false" << endl;
            return false;
        }

        // If a tank was found, check that m_current->m_next is properly updated to reflect this.
        if (obj.m_current->m_next->m_tankID != ID) {
            cout << "Error: The found tank is not the next node of the current node (ID: " << ID << ")" << endl;
            return false;
        }
    }

    cout << "Success: Each tank was successfully found" << endl;
    return true;
}

bool findTankError() {
    // Populate the list with tanks.
    FuelSys obj;
    for (int ID = 0; ID < 10; ID++) {
        obj.addTank(ID, 2000, 500);
    }

    // Observe to see if findTank() guards properly against searching for a tank that does not exist.
    if (obj.findTank(20) != false) {
        cout << "Error: False was not returned for a non-existent tank" << endl;
        return false;
    }

    cout << "Success: False was returned for a non-existent tank" << endl;
    return true;
}

int main() {
    // 1. Test addTank function
    cout << "======= Testing addTank() =======" << endl;
    Tester test;

    // Ensure that a tank is added successfully to an empty list.
    cout << endl << "1. Inserting a tank in an empty list" << endl;
    test.insertWhenEmpty();

    // Ensure that multiple can be added in the intended order.
    cout << endl << "2. Inserting multiple tanks consecutively" << endl;
    test.insertMultipleTanks();

    // Ensure that input passed in is validated properly.
    cout << endl << "3. Checking error cases for input" << endl;
    test.validateInputError();

    cout << endl << "4. Checking edge cases for valid input" << endl;
    test.validateInputEdge();


    // 2. Test removeTank function
    cout << endl << "====== Testing removeTank() ======" << endl;

    // Ensure that each tank in a list is removed properly. Should return true for each removal.
    cout << endl << "1. Removing all tanks from a fuel system containing ten tanks" << endl;
    test.removeAll();




    // 4. Test totalFuel function
    cout << endl << "====== Testing totalFuel() ======" << endl;

    cout << "1. Calculating total fuel for a non-existent tank" << endl;
    test.calculateFuelEmpty();

    cout << "2. Calculating total fuel for a fuel system containing three tanks" << endl;
    test.calculateFuel();


    // 5. Test findTank function
    cout << endl << "====== Testing findTank() ======" << endl;

    cout << "1. Adding fifty tanks to a fuel system and finding each of them" << endl;
    test.findTankNormal();

    cout << "2. Searching for a non-existent tank in a fuel system" << endl;
    test.findTankError();
}