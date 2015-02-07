/* 
 * File:   CommunicationNetwork.h
 * Author: Sonia
 *
 * Created on February 7, 2015, 1:36 PM
 */

#ifndef COMMUNICATIONNETWORK_H
#define	COMMUNICATIONNETWORK_H
#include<string>

/*struct City{

    std::string name;
    std::string message; //intended to hold one word
    City *next;
    City *previous;

}; */

class CommunicationNetwork
{
    public:
        CommunicationNetwork(int);
        virtual ~CommunicationNetwork();
        //circular queue methods
        void enqueue(std::string);
        std::string dequeue(); //should send through network, call transmit msg
        void printQueue();
        void buildNetwork();
        void printPath();
        bool queueIsFull(); //send when full
        void transmitMsg(std::string);

    protected:
    private:
        // City *head;
        // City *tail;
        int queueSize;
        int queueHead;
        int queueTail;
        std::string *arrayQueue;
        bool isFull;

};

#endif	/* COMMUNICATIONNETWORK_H */

