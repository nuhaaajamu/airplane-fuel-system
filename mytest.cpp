#include "fuel.h"

class Tester {
public:
    // Tests for addTank()
    bool addTankEmpty();         // Tests if insertion is still successful even when the list is empty
    bool addMultipleTanks();     // Tests whether each tank is properly added to the end of the list
    bool validateInputError();   // Tests the error cases of the input passed in (ID, capacity, fuel), should not add a tank
    bool validateInputEdge();    // Tests the edge cases of the inputs passed in (ID, capacity, fuel), should add a tank


    // Tests for removeTank()
    bool removeAll();            // Tests whether all tanks are removed correctly (normal case)
    bool removeTankError();      // Tests if a non-existent tank can be removed (error case)


    // Tests for totalFuel()
    bool calculateFuelEmpty();   // Tests fuel amount for when no tank exists, should return zero (error case)
    bool calculateFuel();        // Tests if total is calculated accurately (normal case)


    // Tests for findTank()
    bool findTankNormal();      // Tests whether it works correctly for a normal case
    bool findTankError();       // Tests whether the function accounts for a tank that does not exist in the fuel system


    // Tests for addPump()
    bool addMultiplePumps();    // Tests whether the function works correctly when adding multiple pumps to a tank (normal case)
    bool addDuplicatePump();    // Tests whether the function guards against a pump with a duplicate pumpID (error case)
    bool addPumpInvalidTank();  // Tests how function handles adding a pump to a non-existent tank


    // Tests for removePump()
    bool removeMultiplePumps(); // Tests whether the function works correctly when removing multiple pumps from a tank (normal case)
    bool removePumpInvalid();   // Tests whether the function works correctly when there is a non-existent pump or non-existent tank (error case)


    // Tests for drain()
    bool drainNormal();         // Tests fuel transfer (normal case)
    bool drainError();          // Tests for non-existent tank, non-existent pump, no target (error case)

    // Test for operator=
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
        cout << "Error: Incorrect data assigned to tank (0)" << endl;
        return false;
    }

    // Add second tank and evaluate.
    if (obj.addTank(20, 4000, 1000) == false) {
        cout << "Error: Second tank was not added successfully" << endl;
        return false;
    }else if (obj.m_current->m_tankID != 20) {
        cout << "Error: Incorrect data assigned to tank (1)" << endl;
        return false;
    }

    // Add third tank and evaluate.
    if (obj.addTank(30, 5000, 1500) == false) {
        cout << "Error: Third tank was not added successfully" << endl;
        return false;
    }else if (obj.m_current->m_tankID != 30) {
        cout << "Error: Incorrect data assigned to tank (2)" << endl;
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
    //    tankCapacity must be greater than or equal to MIN_CAP, so the edge case is when they are equal.
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
            cout << "Error: Tank (" << i << ") was not added successfully" << endl;
            return false;
        }
    }

    // Remove every tank 0-9
    for (int i = 0; i < 10; i++) {
        if (obj.removeTank(i) == false) {
            cout << "Error: Tank (" << i << ") was not successfully removed" << endl;
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

    // If the object does not contain any tanks, there is no fuel.
    if (result == 0) {
        cout << "Success: total fuel calculated for a non-existent tank is zero" << endl;
        return true;
    }

    cout << "Error: total fuel calculated for a non-existent tank is not zero" << endl;
    return false;
}


bool Tester::calculateFuel() {
    // Test whether arithmetic calculations for fuel are accurate.
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

    // Search for each tank and check to see if the found tank is the m_next of the current tank in the list.
    for (int ID = 0; ID < 50; ID++) {

        // Ensure that a tank was found.
        if (obj.findTank(ID) == false) {
            cout << "Error: findTank() returned false" << endl;
            return false;
        }

        // If a tank was found, check that m_current->m_next is properly updated to reflect this.
        if (obj.m_current->m_next->m_tankID != ID) {
            cout << "Error: The found tank is not m_current->m_next (tankID: " << ID << ")" << endl;
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

            // Ensure we are positioned at the correct tank before checking the head.
            obj.findTank(tankID);

            // Check that the head of the list was updated to store the added pump.
            if (obj.m_current->m_next->m_pumps->m_pumpID != pumpID) {
                cout << "Error: The head of the list m_pumps was not updated to point to the new pump" << endl;
                return false;
            }
        }

        // Make sure we are positioned at the correct tank before counting.
        obj.findTank(tankID);

        // Check that the number of pumps in the tank reflects the number of pumps that were added.
        int count = 0;
        Pump * currentPump = obj.m_current->m_next->m_pumps;

        while (currentPump != nullptr) {
            count++;
            currentPump = currentPump->m_next;
        }

        if (count != 50) {
            cout << "Error: Not all pumps were added. Only " << count << "/50 pumps exist within tank ("<< tankID << ")" <<  endl;
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

    // Add pumps to some of the tanks.
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
        cout << "Error: A duplicate pump was added to the tank" << endl;
        return false;
    }

    cout << "Success: Duplicate pumps were not able to be added to the tank" << endl;
    return true;
}

bool Tester::addPumpInvalidTank() {
    FuelSys obj;
    int invalidTank = 70;  // A tank that does not exist within the fuel system
    int pumpID = 1;        // Arbitrary value for pumpID used to create a pump
    int target = 10;       // Arbitrary value for targetTank used to create a pump

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

    // Add sixty pumps to each tank.
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

    // Add sixty pumps to each tank.
    for (int tankID = 0; tankID < 70; tankID++) {
        for (int pumpID = 0, targetTank = 1; pumpID < 60; pumpID++, targetTank++) {
            obj.addPump(tankID, pumpID, targetTank);
        }
    }

    // Attempt to remove a pump that does not exist (valid tank, invalid pump).
    int invalidPump = 100;
    int validTank = 10;
    if (obj.removePump(validTank, invalidPump) == true) {
        cout << "Error: Removal of a non-existent pump was not guarded against" << endl;
        return false;
    }

    // Attempt to remove a pump from a tank that does not exist (invalid tank, valid pump).
    int invalidTank = 90;
    int validPump = 5;
    if (obj.removePump(invalidTank, validPump) == true) {
        cout << "Error: Removal from a non-existent tank was not guarded against" << endl;
        return false;
    }

    cout << "Success: Removal using a non-existent pump or a non-existent tank were safely guarded against" << endl;
    return true;
}

bool Tester::removeTankError() {
    FuelSys obj;

    // Populate the fuel system with tanks.
    for (int i = 0; i < 10; i++) {
        obj.addTank(i, 2000, 500);
    }

    int expectedTotal = 10 * 500;

    // Try removing a tank that does not exist.
    if (obj.removeTank(50) != false) {
        cout << "Error: removeTank() returned true for a non-existent tank" << endl;
        return false;
    }

    // Make sure nothing changed.
    if (obj.totalFuel() != expectedTotal) {
        cout << "Error: totalFuel() changed after trying to remove a non-existent tank" << endl;
        return false;
    }

    // Also ensure the fuel system still has tanks.
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
            cout << "Error: drain() transferred the wrong amount" << endl;
            return false;
        }
    }

    // Case 2: requested fuel is more than the empty space of the target tank
    {
        FuelSys obj;

        obj.addTank(1, 2000, 1000); // source tank
        obj.addTank(2, 2000, 1900); // target tank (only 100 kg space left)

        if (obj.addPump(1, 7, 2) == false) {
            cout << "Error: addPump() failed" << endl;
            return false;
        }

        if (obj.drain(1, 7, 500) == false) {
            cout << "Error: drain() failed when target tank should fill up" << endl;
            return false;
        }

        obj.findTank(1);
        int sourceFuel = obj.m_current->m_next->m_tankFuel;

        obj.findTank(2);
        int targetFuel = obj.m_current->m_next->m_tankFuel;

        // Target tank should cap at 2000 kg, and source tank should lose only 100 kg.
        if (sourceFuel != 900 || targetFuel != 2000) {
            cout << "Error: drain() transferred the wrong amount" << endl;
            return false;
        }
    }

    cout << "Success: drain() transferred fuel correctly for normal cases" << endl;
    return true;
}

bool Tester::drainError() {
    // Case 1: empty fuel system
    {
        FuelSys obj;
        if (obj.drain(1, 1, 100) != false) {
            cout << "Error: drain() returned true for an empty fuel system" << endl;
            return false;
        }
    }

    // Case 2: destination tank does not exist
    {
        FuelSys obj;
        obj.addTank(1, 2000, 500);   // source tank exists

        // Temporarily create the target tank just so addPump() is allowed to succeed.
        if (obj.addTank(99, 2000, 0) == false) {
            cout << "Error: setup failed (could not add temporary target tank)" << endl;
            return false;
        }

        if (obj.addPump(1, 5, 99) == false) {
            cout << "Error: setup failed (could not add pump that points to temporary target tank)" << endl;
            return false;
        }

        if (obj.removeTank(99) == false) {
            cout << "Error: setup failed (could not remove temporary target tank)" << endl;
            return false;
        }

        if (obj.drain(1, 5, 100) != false) {
            cout << "Error: drain() returned true for a non-existent tank" << endl;
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

bool Tester::assignmentOperator() {
    FuelSys rhs;
    rhs.addTank(1, 2000, 500);
    rhs.addTank(2, 2000, 0);
    rhs.addPump(1, 5, 2);

    FuelSys lhs;
    lhs.addTank(10, 2000, 100);
    lhs.addTank(11, 2000, 200);

    // Perform assignment.
    lhs = rhs;

    // Ensure that totals match.
    if (lhs.totalFuel() != rhs.totalFuel()) {
        cout << "Error: totalFuel() does not match after assignment" << endl;
        return false;
    }

    // Now mutate rhs and make sure lhs does not change (check that a deep copy was made).
    // Remove pump from rhs, then rhs should fail drain but lhs should still succeed.
    if (rhs.removePump(1, 5) == false) {
        cout << "Error: removePump() failed on rhs during assignment test" << endl;
        return false;
    }

    if (rhs.drain(1, 5, 100) != false) {
        cout << "Error: rhs drain() succeeded even though pump was removed" << endl;
        return false;
    }

    if (lhs.drain(1, 5, 100) == false) {
        cout << "Error: lhs drain() failed after rhs pump removal (deep copy failed)" << endl;
        return false;
    }

    cout << "Success: a deep copy was made" << endl;
    return true;
}

int main() {
    Tester test;
    int passed = 0;
    int failed = 0;
    bool result = false;

    // Test addTank()
    cout << "======= Testing addTank() =======" << endl;

    cout << "1. Inserting a tank in an empty list" << endl;
    result = test.addTankEmpty();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "2. Inserting multiple tanks consecutively" << endl;
    result = test.addMultipleTanks();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "3. Checking error cases for input" << endl;
    result = test.validateInputError();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "4. Checking edge cases for valid input" << endl;
    result = test.validateInputEdge();
    if (result == true)
        passed++;
    else
        failed++;


    // Test removeTank()
    cout << endl << "====== Testing removeTank() ======" << endl;

    cout << "1. Removing all tanks from a fuel system containing ten tanks" << endl;
    result = test.removeAll();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "2. Attempting to remove a non-existent tank" << endl;
    result = test.removeTankError();
    if (result == true)
        passed++;
    else
        failed++;


    // Test findTank()
    cout << endl << "====== Testing findTank() ======" << endl;

    cout << "1. Adding fifty tanks to a fuel system and finding each of them" << endl;
    result = test.findTankNormal();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "2. Searching for a non-existent tank in a fuel system" << endl;
    result = test.findTankError();
    if (result == true)
        passed++;
    else
        failed++;


    // Test addPump()
    cout << endl << "====== Testing addPump() ======" << endl;

    cout << "1. Adding multiple pumps to multiple tanks" << endl;
    result = test.addMultiplePumps();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "2. Adding a duplicate pump to a tank" << endl;
    result = test.addDuplicatePump();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "3. Attempting to add a pump to a non-existent tank" << endl;
    result = test.addPumpInvalidTank();
    if (result == true)
        passed++;
    else
        failed++;


    // Test removePump()
    cout << endl << "====== Testing removePump() ======" << endl;

    cout << "1. Removing multiple pumps from tanks" << endl;
    result = test.removeMultiplePumps();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "2. Attempting to remove a non-existent pump and a non-existent tank" << endl;
    result = test.removePumpInvalid();
    if (result == true)
        passed++;
    else
        failed++;


    // Test totalFuel()
    cout << endl << "====== Testing totalFuel() ======" << endl;

    cout << "1. Calculating total fuel for an empty fuel system" << endl;
    result = test.calculateFuelEmpty();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "2. Calculating total fuel for a fuel system containing three tanks" << endl;
    result = test.calculateFuel();
    if (result == true)
        passed++;
    else
        failed++;


    // Test drain()
    cout << endl << "====== Testing drain() ======" << endl;

    cout << "1. Testing for normal cases" << endl;
    result = test.drainNormal();
    if (result == true)
        passed++;
    else
        failed++;

    cout << "2. Testing for error cases" << endl;
    result = test.drainError();
    if (result == true)
        passed++;
    else
        failed++;


    // Test overloaded assignment operator
    cout << endl << "====== Testing operator= ======" << endl;

    cout << "1. Determining if the assignment operator makes a deep or shallow copy" << endl;
    result = test.assignmentOperator();
    if (result == true)
        passed++;
    else
        failed++;


    cout << endl;
    cout << "======= TEST SUMMARY =======" << endl;
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    return 0;
}