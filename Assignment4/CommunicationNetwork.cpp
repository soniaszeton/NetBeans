/* 
 * File:   CommunicationNetwork.cpp
 * Author: Sonia
 * 
 * Created on February 7, 2015, 1:36 PM
 */

#include "CommunicationNetwork.h"


CommunicationNetwork::CommunicationNetwork(int size) {
    queueSize = size;
    arrayQueue = new std::string [queueSize];
    queueHead = 0;
    queueTail = 0;
    isFull = false;
}

CommunicationNetwork::~CommunicationNetwork() {
}
void CommunicationNetwork::enqueue(std::string word) {
    arrayQueue[tail++] = word;
    if(tail == queueSize)
    {
        tail = 0;
    }
    if(head == tail) {
        isFull = true;
    }
}
std::string CommunicationNetwork::dequeue() {
    return arrayQueue[head++];
    if(head == queueSize) {
        head = 0;
    }
    if(head == tail) {
        isFull = false;
    }
}
bool CommunicationNetwork::queueIsFull() {
    return isFull;
}

