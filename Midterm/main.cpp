/* 
 * File:   main.cpp
 * Author: Sonia
 *
 * Created on February 19, 2015, 9:23 AM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

struct node

{

    int value;

    node *next;

};



class Queue

{

    public:

        Queue(node *, node *);

        virtual ~Queue();

        node* dequeue(); 

        void displayQueue();

    protected:

    private:

        node *head;

        node *tail;

};
node* Queue::dequeue() {
    node *current_node = head;
    if(current_node != NULL) {
        head = current_node->next;
    }
    return current_node;
}

int main(int argc, char** argv) {
    
}