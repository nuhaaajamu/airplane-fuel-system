// UMBC - CMSC 341 - Spring 2026 - Proj1
#include "fuel.h"


FuelSys::FuelSys(){

}


FuelSys::~FuelSys(){

}


bool FuelSys::addTank(int tankID, int tankCap, int tankFuel = 0) {
    // This function creates and inserts a new Tank object after the current location of the list and makes the node the current location.
    // If the insertion is successful the function returns true, otherwise it returns false.
    // Since the tank IDs must be unique in the list this function will not insert the tank if it already exists. In such a failure case the function returns false.
    // The tankCap cannot be less than the min capacity. The amount of fuel cannot exceed the tank capacity.
}


bool FuelSys::removeTank(int tankID){
    // This function removes the tank with tankID from the list. If the requested tank is removed the function returns true otherwise it returns false, i.e. if tankID does not exists the function returns false.
    // Note, if the tank has pumps the list of pumps must be removed too.
}


bool FuelSys::findTank(int tankID){
    // This function searches the list for tankID.
    // If the ID is found the function makes it the next of current location and it returns true.
    // If the ID is not found the function returns false.

}


bool FuelSys::addPump(int tankID, int pumpID, int targetTank){
    // This function finds the tankID and adds a pump with pumpID to the tank's pump list.
    // The targetTank is the tank ID that will receive fuel from the parent of the pump in the case of transfer requests.
    // Both tankID and targetID must exist in the list in order to add the pump.
    // In the case of success the function returns true, otherwise it returns false.
    // The pump must be added to the head of the pump list.
}


bool FuelSys::removePump(int tankID, int pumpID){
    // This function removes the pumpID from the tankID.
    // If the remove operation is successful the function returns true.
    // If either tankID or pumpID does not exist it is a failure and the function returns false.
}


int FuelSys::totalFuel() const{
    // This function calculates and returns the total amount of current fuel in the airplane.
    // The total amount of fuel is the sum of fuel in all tanks.
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
