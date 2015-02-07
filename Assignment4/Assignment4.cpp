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

using namespace std;

// Declare struct to hold information about each city in path
struct City
{
    string name;
    string message;
    City *next;
    City *previous;
};

City *head = NULL;
City *tail = NULL;

string initial_cities[10]=
{
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


// Will build the original path
void buildNetwork()
{
    for(int i = 0; i < 10; i++)
    {
        City *city = new City;
        city->name = initial_cities[i];
        city->message = "";
        city->next = head;
        if(head == NULL)
        {
            tail = city;
        }
        else 
        {
            head->previous = city;
        }
        
        head = city;
    }
}

// Opens the file holding the message and transmits it between the cities word by word
void transmitMsg()
{
    ifstream file;
    file.open("messageIn.txt");
    if(!file.is_open())
    {
        cout << "File not found." << endl;
    }
    
    // Pulls out a word from the message sends it through each city then gets the next word
    string word;
    while(file >> word)
    {
        City *current_city = head;
        while(current_city != NULL)
        {
            cout << current_city->name << " received " << word << endl;
            current_city = current_city->next;
        }
    }

}

// Start at the head and print the name of each city in the path
void printPath()
{
    City *current_city = head;
    cout << "===CURRENT PATH===" << endl;
    while(current_city != NULL)
    {
        cout << current_city->name << " -> ";
        current_city = current_city->next;
    }
    cout << "NULL" << endl;
    cout << "=================" << endl;
    
}

int main(int argc, char** argv) {

    string user_command;
    string desired_city;
    string previous_city;
    string unwanted_city;

    while(true)
    {
        cout << "======Main Menu=====" << endl;
        cout << "1. Build Network" << endl;
        cout << "2. Print Network Path" << endl;
        cout << "3. Transmit Message Coast-To-Coast" << endl;
        cout << "4. Add City" << endl;
        cout << "5. Delete City" << endl;
        cout << "6. Clear Network" << endl;
        cout << "7. Quit" << endl;
        getline(cin, user_command);

        switch (stoi(user_command)) 
        {
            case 1:
            {
                buildNetwork();
                break;
            }
            case 2:
            {
                printPath();
                break;
            }
            case 3:
            {
                transmitMsg();
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
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

