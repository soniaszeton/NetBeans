/* 
 * File:   CommunicationNetwork.cpp
 * Author: Sonia
 * 
 * Created on February 7, 2015, 1:36 PM
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
    arrayQueue[queueTail++] = word;
    if (queueTail == queueSize) {
        queueTail = 0;
    }
    if (queueHead == queueTail) {
        isFull = true;
    }
    cout << "E: " << word << endl;
    cout << "H: " << queueHead << endl;
    cout << "T: " << queueTail << endl;
}

string CommunicationNetwork::dequeue() {
    string word = arrayQueue[queueHead++];
    if (queueHead == queueSize) {
        queueHead = 0;
    }
    if (queueHead == queueTail) {
        isFull = false;
    }
    return word;
}

bool CommunicationNetwork::queueIsFull() {
    return isFull;
}

bool CommunicationNetwork::queueIsEmpty() {
    return queueHead == queueTail && !isFull;
}

void CommunicationNetwork::transmitMsg(string word) {

    City *current_city = head;
    while (current_city != NULL) {
        cout << current_city->name << " received " << word << endl;
        current_city = current_city->next;
    }
    current_city = tail;
    while (current_city != NULL) {
        cout << current_city->name << " received " << word << endl;
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
    City *current_city = head;
    cout << "===CURRENT PATH===" << endl;
    while (current_city != NULL) {
        cout << current_city->name << " -> ";
        current_city = current_city->next;
    }
    cout << "NULL" << endl;
    cout << "=================" << endl;

}

