/* 
 * File:   CommunicationNetwork.cpp
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Created on February 7, 2015, 1:36 PM
 * Implements the function prototypes from the header file
 */

#include "CommunicationNetwork.h"
#include <iostream>

using namespace std;

string initial_cities[10] ={
    "Boston",
    "New York",
    "Washington, D.C.",
    "Atlanta",
    "Chicago",
    "St. Louis",
    "Dallas",
    "Denver",
    "Phoenix",
    "Los Angeles"

};

CommunicationNetwork::CommunicationNetwork(int size) {
    queueSize = size;
    arrayQueue = new string [queueSize];
    queueHead = 0;
    queueTail = 0;
    isFull = false;
}

CommunicationNetwork::~CommunicationNetwork() {
}

void CommunicationNetwork::enqueue(string word) {
    
    // If the queue is full the message is dequeued and sent off
    if (queueIsFull()) {
        while (!queueIsEmpty()) {
            dequeue();
        }
    }
    
    // Fill queue with words from message
    arrayQueue[queueTail++] = word;
    
    // If the tail reaches the end of the queue its reset to the beginning of the queue
    if (queueTail == queueSize) {
        queueTail = 0;
    }
    
    // When head = tail, the queue is either empty or full, must be full because enqueue
    if (queueHead == queueTail) {
        isFull = true;
    }
    cout << "E: " << word << endl;
    cout << "H: " << queueHead << endl;
    cout << "T: " << queueTail << endl;
}

void CommunicationNetwork::dequeue() {
    
    // Can't dequeue is the queue is already empty
    if (queueIsEmpty()) {
        cout << "Queue is empty." << endl;
    } 
    
    // word is the first word in the queue
    else {
        string word = arrayQueue[queueHead++];
        
        // if the end of the queue is reached, reset head to 0
        if (queueHead == queueSize) {
            queueHead = 0;
        }
        
        // If head = tail the queue must be empty because dequeue
        if (queueHead == queueTail) {
            isFull = false;
        }
        transmitMsg(word);
    }
}

bool CommunicationNetwork::queueIsFull() {
    return isFull;
}

bool CommunicationNetwork::queueIsEmpty() {
    return queueHead == queueTail && !isFull;
}

void CommunicationNetwork::transmitMsg(string word) {

    City *current_city = head;
    current_city->message = word;
    while (current_city != NULL) {
        
        cout << current_city->name << " received " << current_city->message << endl;
    
        if(current_city->next != NULL) {
                current_city->next->message = current_city->message;
            }
        current_city->message = "";        
        
        current_city = current_city->next;
    }
    
    // Sends the message back through the path
    current_city = tail;
    current_city->message = word;
    while (current_city != NULL) {
        cout << current_city->name << " received " << current_city->message << endl;
        if(current_city->previous != NULL) {
                current_city->previous->message = current_city->message;
            }
        current_city->message = "";        
        current_city = current_city->previous;
    }

}

void CommunicationNetwork::printQueue() {
    int counter = queueHead;
    while (counter != queueTail) {
        cout << counter << ": " << arrayQueue[counter] << endl;
        counter++;
        if (counter == queueSize) {
            counter = 0;
        }

    }
}

void CommunicationNetwork::buildNetwork() {
    for (int i = 0; i < 10; i++) {
        City *city = new City;
        city->name = initial_cities[i];
        city->message = "";
        city->next = head;
        if (head == NULL) {
            tail = city;
        } else {
            head->previous = city;
        }

        head = city;
    }
}

void CommunicationNetwork::printPath() {
    if(head == NULL) {
        buildNetwork();
    }
    City *current_city = head;
    cout << "===CURRENT PATH===" << endl;
    while (current_city != NULL) {
        cout << current_city->name << " -> ";
        current_city = current_city->next;
    }
    cout << "NULL" << endl;
    cout << "=================" << endl;

}

