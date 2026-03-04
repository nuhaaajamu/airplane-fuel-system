#include "fuel.h"

FuelSys::FuelSys() : m_current(nullptr) {}

FuelSys::~FuelSys(){
    // First, ensure that a tank exists.
    if (m_current == nullptr) {
        return;
    }

    Tank * currentTank = m_current->m_next;
    m_current->m_next = nullptr; // Modify the list to become a forward list instead of circular. This allows us to use nullptr as indication of the end of the list.
    Tank * nextTank = nullptr;

    while (currentTank != nullptr){
        // The pumps need to be de-allocated before the tank is.
        Pump * currentPump = currentTank->m_pumps;

        // Only de-allocate pumps if at least one exists.
        if (currentPump != nullptr) {
            Pump * nextPump = nullptr;

            while (currentPump != nullptr) {
                nextPump = currentPump->m_next;
                delete currentPump;
                currentPump = nextPump;
            }
        }

        // After all pumps have been de-allocated, de-allocate the tank.
        nextTank = currentTank->m_next;
        delete currentTank;
        currentTank = nextTank;
    }

    m_current = nullptr;
}

bool FuelSys::addTank(int tankID, int tankCap, int tankFuel) {
    // Validate the fuel and capacity for the tank.
    if (tankCap < MINCAP || tankFuel > tankCap || tankID < 0) {
        return false;
    }

    // Validate that a unique ID is being used. This is only checked for non-empty lists.
    if (m_current != nullptr) {

        // Case 1: The list has only one tank, this means that the stored tank will point to itself.
        if (m_current == m_current->m_next) {
            if (tankID == m_current->m_tankID) {
                return false;
            }
        }

        // Case 2: The list contains two or more tanks. So, we must check the ID of each tank in the list.
        else {
            Tank * traverse = m_current->m_next;

            // Ensure that our ID is unique.
            do {
                if (tankID == traverse->m_tankID) {
                    return false;
                }
                traverse = traverse->m_next;

            }while (traverse != m_current->m_next);
        }

        // After ensuring that we have a unique ID, a tank is added.
        Tank * newTank = new Tank(tankID, tankCap, tankFuel);
        newTank->m_next = m_current->m_next;

        m_current->m_next = newTank;  // Former last tank should point to new tank.
        m_current = newTank;  // Now, update so that current stores the newly added node.
        return true;
    }

    // If the list is empty and a tank is being added, the first and last tank will be the same.
    else {
        Tank * newTank = new Tank(tankID, tankCap, tankFuel);
        m_current = newTank;
        m_current->m_next = newTank;
        return true;
    }
}

bool FuelSys::removeTank(int tankID){
    bool foundID = false; // Tracks whether a match is found.

    // If the list is empty, there is no tank to remove.
    if (m_current == nullptr) {
        return false;
    }

    Tank * traverse = m_current->m_next;
    Tank * beforeTarget = nullptr;

    // Find the target tank.
    do {
        if (traverse->m_next->m_tankID == tankID) {
            foundID = true;
            beforeTarget = traverse;
        }
        traverse = traverse->m_next;

    }while (traverse != m_current->m_next  && foundID == false);

    // Ensure that we have found a match before attempting to remove the tank.
    if (foundID == false || beforeTarget == nullptr) {
        return false;
    }

    // Remove the target tank. Since m_current tracks the last tank, only update if the last tank is affected.
    Tank * target = beforeTarget->m_next;

    if (m_current == target) {

        // If there is only one tank, then we simply just delete it.
        if (m_current->m_next == m_current) {

            // The pumps need to be de-allocated before the tank is.
            Pump * currentPump = target->m_pumps;
            while (currentPump != nullptr) {
                Pump * nextPump = currentPump->m_next;
                delete currentPump;
                currentPump = nextPump;
            }

            delete m_current;
            m_current = nullptr;
            return true;
        }

        m_current = beforeTarget;
    }

    // Disconnect target from the circular list.
    beforeTarget->m_next = target->m_next;

    // The pumps need to be de-allocated before the tank is.
    Pump * currentPump = target->m_pumps;
    while (currentPump != nullptr) {
        Pump * nextPump = currentPump->m_next;
        delete currentPump;
        currentPump = nextPump;
    }

    delete target;
    return true;
}

bool FuelSys::findTank(int tankID){
    bool foundTank = false; // Tracks whether a match is found.

    // If the list is empty, there is no tank to find.
    if (m_current == nullptr) {
        return false;
    }

    // Find the tank before the target tank.
    Tank * traverse = m_current->m_next;
    Tank * beforeTarget = nullptr;

    do {
        if (traverse->m_next->m_tankID == tankID) {
            foundTank = true;
            beforeTarget = traverse;
        }
        traverse = traverse->m_next;

    }while (traverse != m_current->m_next  && foundTank == false);

    // Ensure that we have found a match before updating m_current.
    if (foundTank == false || beforeTarget == nullptr) {
        return false;
    }

    // The tank before the target becomes the last node so that the target node becomes the first.
    m_current = beforeTarget;
    return true;
}

bool FuelSys::addPump(int tankID, int pumpID, int targetTank){
    // Ensure that the targetTank exists.
    if (findTank(targetTank) == false) {
        return false;
    }

    // Find the tank that we are adding a pump to and ensure that it exists.
    // This rotates the list so that the tank is the "first tank" in the list (m_current->m_next)
    if (findTank(tankID) == false) {
        return false;
    }

    // Check that the pumpID is valid.
    if (pumpID < 0) {
        return false;
    }

    // Ensure that the pumpID is unique.
    Pump * currentPump = m_current->m_next->m_pumps;
    while (currentPump != nullptr) {
        if (currentPump->m_pumpID == pumpID) {
            return false;
        }
        currentPump = currentPump->m_next;
    }

    // Add the pump to the tank.
    // The pump should be added to the head of the list.
    Pump * head = m_current->m_next->m_pumps;
    Pump * newPump = new Pump(pumpID, targetTank, head);

    // This is the part that actually attaches it to the tank's pump list.
    m_current->m_next->m_pumps = newPump;

    return true;
}

bool FuelSys::removePump(int tankID, int pumpID){
    // Ensure that the tank we are removing a pump from exists.
    if (findTank(tankID) == false) {
        return false;
    }

    // Check if the list is empty. If no pumps exist, there is nothing to remove.
    Pump * currentPump = m_current->m_next->m_pumps;
    if (currentPump == nullptr) {
        return false;
    }

    // Check if the pump we are looking for is the "head" of the list.
    if (currentPump->m_pumpID == pumpID) {
        Pump * nextPump = currentPump->m_next;
        delete currentPump;
        m_current->m_next->m_pumps = nextPump;
        return true;
    }

    // Now we remove from the middle/end.
    // The only thing we need to be careful about is that currentPump->m_next might be nullptr.
    bool foundPump = false;
    Pump * beforeTarget = currentPump;

    while (beforeTarget->m_next != nullptr && foundPump == false) {
        if (beforeTarget->m_next->m_pumpID == pumpID) {
            foundPump = true;
        } else {
            beforeTarget = beforeTarget->m_next;
        }
    }

    // A pumpID must be found as well as the pump before it in order to proceed.
    if (foundPump == false) {
        return false;
    }

    // Remove the pump.
    Pump * target = beforeTarget->m_next;
    beforeTarget->m_next = target->m_next;
    delete target;
    return true;
}

int FuelSys::totalFuel() const{
    int total = 0;

    // If fuel system does not contain any tanks, no fuel exists.
    if (m_current == nullptr) {
        return total;
    }

    // Calculate total amount of fuel for all tanks in the fuel system.
    Tank * first = m_current->m_next;
    do {
        total += first->m_tankFuel;
        first = first->m_next;

    }while (first != m_current->m_next);

    return total;
}

bool FuelSys::drain(int tankID, int pumpID, int fuel){
    // Determine if a pump exists and if so retrieve the ID of our target tank.

    // If there are no pumps, then there is no target tank.
    bool foundPump = false;
    Pump * currentPump = m_current->m_next->m_pumps;
    if (currentPump == nullptr) {
        return false;
    }

    // Check if the pump we are looking for is the head of the list.
    int targetTankID = 0;
    if (currentPump->m_pumpID == pumpID) {
        targetTankID = currentPump->m_target;
        foundPump = true;

    // Check all other pumps in the list.
    }else {
        while (currentPump != nullptr && foundPump == false) {
            if (currentPump->m_pumpID == pumpID) {
                targetTankID = currentPump->m_target;
                foundPump = true;
            }
            currentPump = currentPump->m_next;
        }
    }

    // Ensure that the target ID was found before adding fuel.
    if (foundPump != true) {
        return false;
    }

    // Rotate the list so that the first element is the target tank.
    if (findTank(targetTankID) != true) {
        return false;
    }

    // Store data about target tank before findTank() function call which will change m_current.
    Tank * targetTank = m_current->m_next;
    int targetFuel = targetTank->m_tankFuel; // Amount of fuel currently.
    int targetCapacity = targetTank->m_tankCapacity; // Maximum amount of fuel the tank can store.
    int leftToFill = targetCapacity - targetFuel; // How much fuel left to fill the tank.

    // Check that the source tank exists. findTank() rotates the list so that the first node is the source tank.
    if (findTank(tankID) == false) {
        return false;
    }

    // Fill the target tank.
    Tank * sourceTank = m_current->m_next;
    int sourceFuel = sourceTank->m_tankFuel;

    if (sourceFuel <= fuel) {
        // If the source tank is less than what the target tank can receive, the source is emptied out.
        if (sourceFuel <= leftToFill) {
            targetTank->m_tankFuel += sourceFuel;
            sourceTank->m_tankFuel = 0;
            return true;
        }

        // If the source tank contains more than what we can receive, the target tank reaches its maximum.
        if (sourceFuel > leftToFill) {
            targetTank->m_tankFuel = targetCapacity;
            sourceTank->m_tankFuel -= leftToFill;
            return true;
        }

    // Executes when the amount of fuel requested is less than the amount of fuel the source tank stores.
    }else {

        // If the amount of fuel requested is less than what we can receive, we simply just add the fuel to the target tank and the source tank is updated.
        if (fuel <= leftToFill) {
            targetTank->m_tankFuel += fuel;
            sourceTank->m_tankFuel -= fuel;
            return true;
        }

        // If the amount of fuel requested is more than what we can receive, the target tank reaches its maximum and the source tank is updated.
        if (fuel > leftToFill) {
            targetTank->m_tankFuel = targetCapacity;
            sourceTank->m_tankFuel -= leftToFill;
            return true;
        }
    }
}

bool FuelSys::fill(int tankID, int fuel){
    // Look for the tank we want to fill and ensure that it exists.
    // Rotate the list so that the tank is in the first position. (m_current->m_next)
    if (findTank(tankID) == false) {
        return false;
    }

    Tank * currentTank = m_current->m_next;
    int currentFuel = currentTank->m_tankFuel;
    int currentCapacity = currentTank->m_tankCapacity;
    int leftToFill = currentCapacity - currentFuel;

    // Fill the tank with fuel.
    if (fuel <= leftToFill) {
        currentTank->m_tankFuel += fuel;
        return true;
    }
    if (fuel > leftToFill) {
        currentTank->m_tankFuel = currentCapacity;
        return true;
    }

    // If something unexpected happens, just return false.
    return false;
}

const FuelSys & FuelSys::operator=(const FuelSys & rhs){
    // Check for self-assignment.
    if (this == &rhs) {
        return *this;
    }

    // If the lhs contains a tank, clear the object.
    if (m_current != nullptr) {
        Tank * currentTank = m_current->m_next;
        m_current->m_next = nullptr; // Modify the list to become a forward list instead of circular. This allows us to use nullptr as indication of the end of the list.
        Tank * nextTank = nullptr;

        while (currentTank != nullptr){
            // The pumps need to be de-allocated before the tank is.
            Pump * currentPump = currentTank->m_pumps;

            // Only de-allocate pumps if at least one exists.
            if (currentPump != nullptr) {
                Pump * nextPump = nullptr;

                while (currentPump != nullptr) {
                    nextPump = currentPump->m_next;
                    delete currentPump;
                    currentPump = nextPump;
                }
            }

            // After all pumps have been de-allocated, de-allocate the tank.
            nextTank = currentTank->m_next;
            delete currentTank;
            currentTank = nextTank;
        }

        m_current = nullptr;
    }

    // Now, make a deep copy of the tanks from the rhs to lhs.


    // Next, make a deep copy of all the pumps from the rhs to lhs.
}

void FuelSys::dumpSys() const{
    // This function prints out the list of tanks along with the amount of current fuel in the tank and the list of its pumps to the standard output.
    // The implementation of this function is provided for the debugging purposes.

    if (m_current != nullptr){
        Tank* tempTank = m_current->m_next;//we start at front item
        //we continue visting nodes until we reach the cursor
        while(m_current != nullptr && tempTank != m_current){
            cout << "Tank " << tempTank->m_tankID << "(" << tempTank->m_tankFuel << " kg)" << endl;
            // now dump the targets for all pumps in this tank
            // we need to traverse the list of pumps
            dumpPumps(tempTank->m_pumps);
            tempTank = tempTank->m_next;
        }
        //at the end we visit the cursor (current)
        //this also covers the case that there is only one item
        cout << "Tank " << m_current->m_tankID << "(" << m_current->m_tankFuel << " kg)" << endl;
        dumpPumps(tempTank->m_pumps);
        cout << "The current tank is " << m_current->m_tankID << endl;
    }
    else
        cout << "There is no tank in the system!\n\n";
}

void FuelSys::dumpPumps(Pump* pumps) const{
    // this traverses the linked list to the end
    Pump* tempPump = pumps;
    while (tempPump != nullptr){
        cout << " => pump " << tempPump->m_pumpID << "(To tank " << tempPump->m_target << ")" << endl;
        tempPump = tempPump->m_next;
    }
}
