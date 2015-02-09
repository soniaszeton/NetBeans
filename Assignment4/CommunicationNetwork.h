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

