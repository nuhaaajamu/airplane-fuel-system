// GENERAL GUIDELINES:
// The test file name must be mytest.cpp; the file name must be in lower case, a file name like myTest.cpp is not acceptable.
// The test file must contain the declaration and implementation of your Tester class and the main() function as well as all your test cases, i.e. calls to your test functions.
// You are responsible for adequately testing your work before submission. The following section presents a non-exhaustive list of tests to perform on your implementation.
// You must write a separate function for every test case.
// Every test function must return true/false depending on passing or failing the test. Visual outputs are not accepted as test results.
// The dump() function should not be called in the test functions. The dump() function is only provided to facilitate debugging.
// Tests cannot be interactive. The test file mytest.cpp must compile and run to completion.
//
//
// TESTING FUELSYS CLASS:
// Test whether addTank() works correctly for a normal case, i.e. inserting multiple tanks. We check whether the function returns true for every insertion. And we check whether all nodes are inserted.
// Test whether addTank() works correctly for an error case. For example, for the error case of insertion we check that the tank with an ID less than zero is not inserted and the function returns false. Another error case would be inserting a duplicate ID.
// Test whether removeTank() works correctly for a normal case. Create an object with a decent number of tanks and remove all, then check if all are removed correctly and at every removal the function returns true.
// Test whether removeTank() works correctly for an error case which the removal request is for a non-existing tank.
// Test whether findTank() works correctly for a normal case. Create an object with a decent number of tanks and search for them, then check if the found tank is the next node of the current node in the list and at every search operation the function returns true.
// Test whether findTank() works correctly for an error case which the tank does not exist in the list.
// Test whether totalFuel() works correctly for a normal case. It returns the correct value.
// Test whether totalFuel() works correctly for an error case. It returns zero where there is no tank in the system.
// Test whether addPump() works correctly for a normal case. It adds multiple pumps to some of the tanks.
// Test whether addPump() works correctly for an error case. It does not add a duplicate pump ID to a tank. Another error case would be adding a pump to a tank that does not exist.
// Test whether removePump() works correctly for a normal case. It removes multiple pumps from some of the tanks.
// Test whether removePump() works correctly for an error case. That is trying to remove a non-existent pump or trying to remove a pump from a non-existent tank.
// Test whether drain() works correctly. It transfers the fuel from the source tank to the target tank correctly where the requested fuel is less than the empty space of the target tank. Another case would be when the amount of fuel is more than the empty space of the target tank.
// Test whether drain() works correctly for the error cases. For example, the source tank or the pump or the destination tank does not exist in the system.
// Test the overloaded assignment operator.


#include "fuel.h"

class Tester {
public:
    // Tests for addTank()
    bool addTankEmpty();         // Tests if insertion is still successful even when the list is empty
    bool addMultipleTanks();     // Tests whether each tank is properly added to the end of the list
    bool validateInputError();   // Tests the error cases of the input passed in (ID, capacity, fuel), should not add a tank
    bool validateInputEdge();    // Tests the edge cases of the inputs passed in (ID, capacity, fuel), should add a tank


    // Tests for removeTank()
    bool removeAll();           // Tests whether all tanks are removed correctly.
    bool removeTankError();     // Tests if a non-existent tank can be removed (error case)


    // Tests for totalFuel()
    bool calculateFuelEmpty();  // Tests fuel amount for when no tank exists, should return zero (error case)
    bool calculateFuel();       // Tests if total is calculated accurately (normal case)


    // Tests for findTank()
    bool findTankNormal();     // Tests whether it works correctly for a normal case
    bool findTankError();      // Tests whether the function accounts for a tank that does not exist in the fuel system


    // Tests for addPump()
    bool addMultiplePumps();   // Tests whether the function works correctly when adding multiple pumps to a tank (normal case)
    bool addDuplicatePump();   // Tests whether the function guards against a pump with a duplicate pumpID (error case)
    bool addPumpInvalidTank(); // Tests how function handles adding a pump to a non-existent tank


    // Tests for removePump()
    bool removeMultiplePumps(); // Tests whether the function works correctly when removing multiple pumps from a tank (normal case)
    bool removePumpInvalid();   // Tests whether the function works correctly when there is a non-existent pump or non-existent tank (error case)


    // Tests for drain()
    bool drainNormal();         // Tests fuel transfer (normal case)
    bool drainError();          // Tests for non-existent tank, non-existent pump, no target (error case)

    // Tests for operator=
    bool assignmentOperator();  // Tests for deep copy
};

bool Tester::addTankEmpty(){
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

bool Tester::addMultipleTanks() {
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
    FuelSys obj;

    // Populate the fuel system with tanks 0-9
    for (int i = 0; i < 10; i++) {
        if (obj.addTank(i, 2000, 500) == false) {
            cout << "Error: Tank " << i << " was not added successfully" << endl;
            return false;
        }
    }

    // Remove every tanks 0-9
    for (int i = 0; i < 10; i++) {
        if (obj.removeTank(i) == false) {
            cout << "Error: Tank " << i << " was not successfully removed" << endl;
            return false;
        }
    }

    // After removing all tanks, m_current should be nullptr.
    if (obj.m_current != nullptr) {
        cout << "Error: m_current is not nullptr after removing all tanks" << endl;
        return false;
    }

    // Also, totalFuel should be 0 now.
    if (obj.totalFuel() != 0) {
        cout << "Error: totalFuel() is not zero after removing all tanks" << endl;
        return false;
    }

    cout << "Success: All tanks were removed successfully" << endl;
    return true;
}

bool Tester::calculateFuelEmpty() {
    FuelSys obj;
    int result = obj.totalFuel();

    if (result == 0) {
        cout << "Success: total fuel calculated for a non-existent tank is zero" << endl;
        return true;
    }

    cout << "Error: total fuel calculated for a non-existent tank is not zero" << endl;
    return false;
}


bool Tester::calculateFuel() {
    FuelSys obj;
    int expectedTotal = 600;

    obj.addTank(1, 2000, 100);
    obj.addTank(2, 2000, 200);
    obj.addTank(3, 2000, 300);

    int result = obj.totalFuel();

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

bool Tester::findTankError() {
    // Populate the list with tanks.
    FuelSys obj;
    for (int ID = 0; ID < 50; ID++) {
        obj.addTank(ID, 2000, 500);
    }

    // Observe to see if findTank() guards properly against searching for a tank that does not exist.
    if (obj.findTank(70) != false) {
        cout << "Error: False was not returned for a non-existent tank" << endl;
        return false;
    }

    cout << "Success: False was returned for a non-existent tank" << endl;
    return true;
}

bool Tester::addMultiplePumps() {
    // Populate the list with tanks.
    FuelSys obj;
    for (int tankID = 0; tankID < 60; tankID++) {
        obj.addTank(tankID, 2000, 500);
    }

    // Add pumps to each tank and evaluate whether they were successfully added for each addition.
    for (int tankID = 0; tankID < 3; tankID++) {
        for (int pumpID = 0, targetTank = 1; pumpID < 50; pumpID++, targetTank++) {
            if (obj.addPump(tankID, pumpID, targetTank) == false) {
                cout << "Error: Pump (" << pumpID << ") was not able to be added to tank (" << tankID << ")" << endl;
                return false;
            }

            // Check that the head of the list was updated to store the added pump.
            if (obj.m_current->m_next->m_pumps->m_pumpID != pumpID) {
                cout << "Error: The head of the list of pumps was not updated to point to the new pump" << endl;
                return false;
            }
        }

        // Check that the number of pumps in the tank reflects the number of pumps that were added.
        int count = 0;
        Pump * currentPump = obj.m_current->m_next->m_pumps;
        while (currentPump != nullptr) {
            count++;
            currentPump = currentPump->m_next;
        }
        if (count != 50) {
            cout << "Error: Only " << count << "/50 pumps were added to the tank" << endl;
            return false;
        }
    }

    cout << "Success: All pumps were successfully added to each tank" << endl;
    return true;
}

bool Tester::addDuplicatePump() {
    // Populate the list with tanks.
    FuelSys obj;
    for (int tankID = 0; tankID < 60; tankID++) {
        obj.addTank(tankID, 2000, 500);
    }

    // Add pumps to some of the tanks
    for (int tankID = 0; tankID < 3; tankID++) {
        for (int pumpID = 0, targetTank = 1; pumpID < 50; pumpID++, targetTank++) {
            obj.addPump(tankID, pumpID, targetTank);
        }
    }

    // Attempt to add a duplicate pumpID. We are adding a duplicate pump to the first tank in the list.
    int duplicatePump = 10;
    int tankID = 0;
    int targetTank = 10;

    if (obj.addPump(tankID, duplicatePump, targetTank) != false) {
        cout << "Error: A duplicate pump was added" << endl;
        return false;
    }

    cout << "Success: Duplicate pumps are not able to be added to a tank" << endl;
    return true;
}

bool Tester::addPumpInvalidTank() {
    FuelSys obj;
    int invalidTank = 70;  // A tank that does not exist within the fuel system
    int pumpID = 1; // Arbitrary value for pumpID used to create a pump
    int target = 10; // Arbitrary value for targetTank used to create a pump

    // Populate the list with tanks.
    for (int tankID = 0; tankID < 50; tankID++) {
        obj.addTank(tankID, 2000, 500);
    }

    // Check to see if a pump can be added to a tank that does not exist
    if (obj.addPump(invalidTank, pumpID, target) != false) {
        cout << "Error: A pump was added to a non-existent tank" << endl;
        return false;
    }

    cout << "Success: A pump was not added to a non-existent tank" << endl;
    return true;
}

bool Tester::removeMultiplePumps() {
    // Populate the list with tanks.
    FuelSys obj;
    for (int tankID = 0; tankID < 70; tankID++) {
        obj.addTank(tankID, 2000, 500);
    }

    // Add sixty pumps to each tank
    for (int tankID = 0; tankID < 70; tankID++) {
        for (int pumpID = 0, targetTank = 1; pumpID < 60; pumpID++, targetTank++) {
            obj.addPump(tankID, pumpID, targetTank);
        }
    }

    // Remove fifty pumps from some of the tanks and check the status after each removal.
    for (int tankID = 0; tankID < 50; tankID++) {
        for (int pumpID = 0; pumpID < 50; pumpID++) {
            if (obj.removePump(tankID, pumpID) == false) {
                cout << "Error: Pump (" << pumpID << ") removal failed for tank (" << tankID << ")" << endl;
                return false;
            }
        }
    }

    cout << "Success: Multiple pumps were removed successfully from multiple tanks" << endl;
    return true;
}

bool Tester::removePumpInvalid() {
    // Populate the list with tanks.
    FuelSys obj;
    for (int tankID = 0; tankID < 70; tankID++) {
        obj.addTank(tankID, 2000, 500);
    }

    // Add sixty pumps to each tank
    for (int tankID = 0; tankID < 70; tankID++) {
        for (int pumpID = 0, targetTank = 1; pumpID < 60; pumpID++, targetTank++) {
            obj.addPump(tankID, pumpID, targetTank);
        }
    }

    // Attempt to remove a pump that does not exist (valid tank, invalid pump).
    int invalidPump = 100;
    int validTank = 10;
    if (obj.removePump(validTank, invalidPump) == true) {
        cout << "Error: Function did not guard against a non-existent pump" << endl;
        return false;
    }

    // Attempt to remove a pump from a tank that does not exist.
    int invalidTank = 90;
    int validPump = 5;
    if (obj.removePump(invalidTank, validPump) == true) {
        cout << "Error: Function did not guard against a non-existent tank" << endl;
        return false;
    }

    cout << "Success: The function safely guarded against a non-existent pump and a non-existent tank" << endl;
    return true;
}

bool Tester::removeTankError() {
    FuelSys obj;

    // Populate the fuel system with tanks 0-9
    for (int i = 0; i < 10; i++) {
        obj.addTank(i, 2000, 500);
    }

    int expectedTotal = 10 * 500;

    // Try removing a tank that does not exist
    if (obj.removeTank(50) != false) {
        cout << "Error: removeTank() returned true for a non-existent tank" << endl;
        return false;
    }

    // Make sure nothing changed (a simple way is checking total fuel)
    if (obj.totalFuel() != expectedTotal) {
        cout << "Error: totalFuel() changed after trying to remove a non-existent tank" << endl;
        return false;
    }

    // Also ensure the system still has tanks
    if (obj.m_current == nullptr) {
        cout << "Error: m_current became nullptr after trying to remove a non-existent tank" << endl;
        return false;
    }

    cout << "Success: removeTank() safely guarded against removing a non-existent tank" << endl;
    return true;
}

bool Tester::drainNormal() {
    // Case 1: requested fuel is less than the empty space of the target tank
    {
        FuelSys obj;

        obj.addTank(1, 2000, 1000); // source
        obj.addTank(2, 2000, 0);    // target

        if (obj.addPump(1, 5, 2) == false) {
            cout << "Error: addPump() failed for drain normal case" << endl;
            return false;
        }

        if (obj.drain(1, 5, 400) == false) {
            cout << "Error: drain() failed when fuel should fit in target tank" << endl;
            return false;
        }

        // Check amounts after transfer
        obj.findTank(1);
        int sourceFuel = obj.m_current->m_next->m_tankFuel;

        obj.findTank(2);
        int targetFuel = obj.m_current->m_next->m_tankFuel;

        if (sourceFuel != 600 || targetFuel != 400) {
            cout << "Error: drain() transferred the wrong amount (fit case)" << endl;
            return false;
        }
    }

    // Case 2: requested fuel is more than the empty space of the target tank
    {
        FuelSys obj;

        obj.addTank(1, 2000, 1000); // source
        obj.addTank(2, 2000, 1900); // target (only 100 space left)

        if (obj.addPump(1, 7, 2) == false) {
            cout << "Error: addPump() failed for drain overflow case" << endl;
            return false;
        }

        if (obj.drain(1, 7, 500) == false) {
            cout << "Error: drain() failed when target should just fill up" << endl;
            return false;
        }

        obj.findTank(1);
        int sourceFuel = obj.m_current->m_next->m_tankFuel;

        obj.findTank(2);
        int targetFuel = obj.m_current->m_next->m_tankFuel;

        // Target should cap at 2000, and source should lose only 100
        if (sourceFuel != 900 || targetFuel != 2000) {
            cout << "Error: drain() transferred the wrong amount (overflow case)" << endl;
            return false;
        }
    }

    cout << "Success: drain() transferred fuel correctly for normal cases" << endl;
    return true;
}

bool Tester::drainError() {
    // Case 1: empty system
    {
        FuelSys obj;
        if (obj.drain(1, 1, 100) != false) {
            cout << "Error: drain() returned true for an empty system" << endl;
            return false;
        }
    }

    // Case 2: source tank does not exist
    {
        FuelSys obj;
        obj.addTank(2, 2000, 500);

        if (obj.drain(99, 1, 100) != false) {
            cout << "Error: drain() returned true for a non-existent source tank" << endl;
            return false;
        }
    }

    // Case 3: source tank exists but has no pumps
    {
        FuelSys obj;
        obj.addTank(1, 2000, 500);
        obj.addTank(2, 2000, 0);

        if (obj.drain(1, 3, 100) != false) {
            cout << "Error: drain() returned true even though no pumps exist" << endl;
            return false;
        }
    }

    // Case 4: pump does not exist in source tank
    {
        FuelSys obj;
        obj.addTank(1, 2000, 500);
        obj.addTank(2, 2000, 0);
        obj.addPump(1, 5, 2);

        if (obj.drain(1, 99, 100) != false) {
            cout << "Error: drain() returned true for a non-existent pump" << endl;
            return false;
        }
    }

    cout << "Success: drain() safely guarded against error cases" << endl;
    return true;
}

int main() {
    // 1. Test addTank function
    cout << "======= Testing addTank() =======" << endl;
    Tester test;
    // Ensure that a tank is added successfully to an empty list.
    cout << endl << "1. Inserting a tank in an empty list" << endl;
    test.addTankEmpty();
    // Ensure that multiple can be added in the intended order.
    cout << endl << "2. Inserting multiple tanks consecutively" << endl;
    test.addMultipleTanks();
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


    // 6. Testing addPump function
    cout << endl << "====== Testing addPump() ======" << endl;
    cout << "1. Adding multiple pumps to multiple tanks" << endl;
    test.addMultiplePumps();
    cout << "2. Adding a duplicate pump to a tank" << endl;
    test.addDuplicatePump();
    cout << "3. Attempting to add a pump to a non-existent tank" << endl;
    test.addPumpInvalidTank();


    // 7. Testing removePump function
    cout << endl << "====== Testing removePump() ======" << endl;
    cout << "1. Removing multiple pumps from tanks" << endl;
    test.removeMultiplePumps();
    cout << "2. Attempting to remove a non-existent pump from a non-existent tank" << endl;
    test.removePumpInvalid();
}