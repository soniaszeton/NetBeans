/* 
 * File:   CommunicationNetwork.h
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Created on February 7, 2015, 1:36 PM
 * Header file for CommunicationNetwork 
 */

#ifndef COMMUNICATIONNETWORK_H
#define	COMMUNICATIONNETWORK_H
#include<string>

class CommunicationNetwork
{
    public:
        CommunicationNetwork(int);
        virtual ~CommunicationNetwork();
        //circular queue methods
        void enqueue(std::string);
        void dequeue(); //should send through network, call transmit msg
        void printQueue();
        void buildNetwork();
        void printPath();
        bool queueIsFull(); //send when full
        bool queueIsEmpty();
        void transmitMsg(std::string);
        
    protected:
    private:
        int queueSize;
        int queueHead;
        int queueTail;
        std::string *arrayQueue;
        bool isFull;
        std::string *message;
        
        struct City
        {
            std::string name;
            std::string message;
            City *next;
            City *previous;
        };

        City *head;
        City *tail;


};

#endif	/* COMMUNICATIONNETWORK_H */

