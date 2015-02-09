/*
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Assignment 4
 * 2/7/15
 * This program transmits a message word by word through a path the user chooses
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "CommunicationNetwork.h"

using namespace std;

int main(int argc, char** argv) {

    ifstream file;
    file.open("messageIn.txt");
    if (!file.is_open()) {
        cout << "File not found." << endl;
    }

    // Pulls out a word from the message sends it through each city then gets the next word
    string word;
    string *message = new string [35];
    int word_count = 0;

    while (file >> word) {
        message[word_count++] = word;

    }


    CommunicationNetwork *network = new CommunicationNetwork(10);
    string user_command;
    int word_index = 0;

    while (true) {
        cout << "======Main Menu=====" << endl;
        cout << "1. Build Network" << endl;
        cout << "2. Print Network Path" << endl;
        cout << "3. Enqueue" << endl;
        cout << "4. Dequeue" << endl;
        cout << "5. Print Queue" << endl;
        cout << "6. Send Entire Message" << endl;
        cout << "7. Quit" << endl;
        getline(cin, user_command);

        switch (stoi(user_command)) {
            case 1:
            {
                network->buildNetwork();
                break;
            }
            case 2:
            {
                network->printPath();
                break;
            }
            case 3:
            {
                if (network->queueIsFull()) {
                    while (!network->queueIsEmpty()) {
                        word = network->dequeue();
                        network->transmitMsg(word);
                    }
                }
                network->enqueue(message[word_index++]);
                if (word_index == 32) {
                    word_index = 0;
                }
                break;
            }
            case 4:
            {
                if (network->queueIsEmpty()) {
                    cout << "Queue is empty." << endl;
                } else {
                    word = network->dequeue();
                    network->transmitMsg(word);
                }
                break;
            }
            case 5:
            {
                network->printQueue();
                break;
            }
            case 6:
            {
                // Send anything already in the queue 
                while (!network->queueIsEmpty()) {
                    word = network->dequeue();
                    network->transmitMsg(word);
                }

                // Putting the entire message in the queue
                word_index = 0;
                while (word_index < 32) {
                    if (network->queueIsFull()) {
                        while (!network->queueIsEmpty()) {
                            word = network->dequeue();
                            network->transmitMsg(word);
                        }
                    }
                    network->enqueue(message[word_index++]);
                    if (word_index == 32) {
                        word_index = 0;
                    }
                }
                
                // Sending the entire message
                while (!network->queueIsEmpty()) {
                    word = network->dequeue();
                    network->transmitMsg(word);
                }
                break;
            }
            case 7:
            {
                cout << "Goodbye!" << endl;
                return 0; // All done
            }
            default:
            {
                cout << "Pick a value from the above list" << endl;
            }

        }

    }
    return 0;
}

