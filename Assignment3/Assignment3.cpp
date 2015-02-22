/*
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Assignment 3
 * 2/3/15
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
};

City *head = NULL;

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
        head = city;
    }
}

// Insert a city into the path
void addCity(string previous_name, string city_name)
{
    City *new_city = new City;
    new_city->name = city_name;
    new_city->message = "";
    if(previous_name == "First")
    {
        new_city->next = head;
        head = new_city;
    }
    else
    {
        City *current_city = head;
        while(current_city != NULL)
        {
            if(current_city->name == previous_name)
            {
                new_city->next = current_city->next;
                current_city->next = new_city;
                break;
            }
            current_city = current_city->next;
        }
    }
}

// Delete a city from the path
void deleteCity(string city_name)
{
    City *previous_city = NULL;
    City *current_city = head;
    while(current_city != NULL)
    {
        if(current_city->name == city_name)
        {
            if(previous_city != NULL)
            {
                previous_city->next = current_city->next;
            }
            else
            {
                head = current_city->next;
            }
            delete current_city;
            return;
        }
        previous_city = current_city;
        current_city = current_city->next;
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
        current_city->message = word;
        
        while(current_city != NULL)
        {
            cout << current_city->name << " received " << current_city->message << endl;
            
            if(current_city->next != NULL) {
                current_city->next->message = current_city->message;
            }
            current_city->message = "";
            current_city = current_city->next;
            
        }
    }

}

// Starts at the head and deletes each city
void deleteEntireNetwork()
{
    City *current_city = head;
    while(current_city != NULL)
    {
        current_city = current_city->next;
        delete current_city;
    }
    head = NULL;
    
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
    cout << " NULL" << endl;
    cout << "=================" << endl;
    
}

int main(int argc, char** argv) {

    string user_command;
    string desired_city;
    string previous_city;
    string unwanted_city;

    //buildNetwork();
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
                cout << "Enter a city name:" << endl;
                getline(cin, desired_city);
                cout << "Enter a previous city name:" << endl;
                getline(cin, previous_city);
                addCity(previous_city, desired_city);
                break;
            }
            case 5:
            {
                cout << "Enter a city name:" << endl;
                getline(cin, unwanted_city);
                deleteCity(unwanted_city);
                break;
            }
            case 6:
            {
                deleteEntireNetwork();
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

