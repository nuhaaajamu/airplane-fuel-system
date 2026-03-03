#include "fuel.h"


FuelSys::FuelSys() : m_current(nullptr) {}


FuelSys::~FuelSys(){

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
            delete m_current;
            m_current = nullptr;
            return true;
        }

        m_current = beforeTarget;
    }

    beforeTarget->m_next = target->m_next;
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

    // Find the tank that we are adding a pump to and ensure that it exists. This rotates the list so that the tank is the "first tank" in the list.
    if (findTank(tankID) == false) {
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
    Pump * head = m_current->m_next->m_pumps;
    Pump * newPump = new Pump(tankID, targetTank, head);
    head = newPump;
    return true;
}


bool FuelSys::removePump(int tankID, int pumpID){
    // Ensure that the tank we are removing a pump from exists.
    if (findTank(tankID) == false) {
        return false;
    }

    // 1. Check if the list is empty. If no pumps exist, there is nothing to remove.
    Pump * currentPump = m_current->m_next->m_pumps;
    if (currentPump == nullptr) {
        cout << "Error: No pumps have been added to the tank" << endl;
        return false;
    }

    // 2. Check if the pump we are looking for is the "head" of the list.
    Pump * nextPump = currentPump->m_next;
    if (currentPump->m_pumpID == pumpID) {
        delete currentPump;
        m_current->m_next->m_pumps = nextPump;
        return true;
    }

    // 3. Ensure that pumpID exists.
    bool foundPump = false;
    Pump * beforeTarget = nullptr;
    while (currentPump != nullptr && foundPump == false) {
        if (pumpID == currentPump->m_next->m_pumpID) {
            foundPump = true;
            beforeTarget = currentPump;
        }
        currentPump = currentPump->m_next;
    }

    // A pumpID must be found as well as the node before it in order to proceed in removing the target pump.
    if (foundPump == false || beforeTarget == nullptr) {
        return false;
    }

    // 4. Remove the pump.
    Pump * target = beforeTarget->m_next; // This is the pump we are removing.
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
    // This function transfers the fuel from tankID to the targetID specified in the pumpID.
    // If the amount of requested transfer is more than the current empty space in the target tank, the function fills the target tank and returns true.
    // If the amount of requested transfer is less than the empty space of the target tank the function transfers all and returns true.
    // If the amount of requested transfer is greater than the current fuel in the source tank, the function performs the transfer and makes the source tank empty.
    // In a case of failure that either tank or the pump does not exist the function returns false.
}


bool FuelSys::fill(int tankID, int fuel){
    // This function fills up the tankID with the amount of fuel.
    // If the empty space of the tank is less than fuel the function still fills up the tank up to its capacity and returns true.
    // If the tank does not exist the function returns false.


}


const FuelSys & FuelSys::operator=(const FuelSys & rhs){

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
