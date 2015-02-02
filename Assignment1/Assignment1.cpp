/* 
 * Assignment 1
 * Sonia Szeton
 * January 19, 2015
 * Professor Hoenigman
 * 
 * This program reads in a list similar to craigslist and finds matches of 
 * wanted and for sale items.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// This struct holds the information of each item
struct Item
    {
        string type;
        bool isWanted;
        int price;
    };
 

int main(int argc, char** argv) 
{
    // This section reads in the filename from the command line and opens the file
    string data_filename = argv[1]; 
    ifstream file;
    file.open(data_filename);
    if(!file.is_open())
    {
        cout << "File not found." << endl;
        return 0;
    }
    
    // Creating an array of pointers to items and declaring various counters
    Item* message_board[100]; 
    int number_unsold = 0;
    int number_operations = 0;
    string line;
    
    // reads one line at a time, either finds a match or adds to the array
    while(getline(file, line))
    {
        // Parsing each line to get type, intent, and price of each item
        int first_index = line.find(",");
        string type = line.substr(0, first_index);
        int second_index = line.find(",", first_index+2);
        string intent = line.substr(first_index+2, second_index - first_index-2);
        bool isWanted = intent.length() == 6;
        int price = stoi(line.substr(second_index+2));
        number_operations++; // finished 1 operation
        
        // looking through the array for a match (wanted matched to for sale)
        bool found = false;
        for(int i = 0; message_board[i] != NULL; i++)
        {
            number_operations++;
            
            // Checking to see if the current item matches this item in the message board
            Item* test_item = message_board[i];
            if(test_item->type == type && test_item->isWanted != isWanted)
            {
                //  Make sure the wanted price is greater or equal than the for sale price (asking price)
                int asking_price;
                if(test_item->isWanted && test_item->price >= price)
                {
                    asking_price = price;
                }
                else if(!test_item->isWanted && test_item->price <= price)
                {
                    asking_price = test_item->price;
                }
                else
                {
                    // The sale price is greater than the wanted price so no match
                    continue; // start at the top of the loop
                }
                // Found a match. Deleting the item from the message board
                message_board[i] = NULL;
                delete test_item;
                
                // Shift all the items in the array up one to fill the NULL space
                for(int j = i+1; message_board[j] != NULL; j++)
                {
                    message_board[j-1] = message_board[j];
                    number_operations++;
                }
                found = true;
                number_unsold--;
                
                // Print the sold item
                cout << test_item->type << " " << asking_price << endl;
                
                // No need to keep looking (otherwise take more than 1 item out of array)
                break; // exit out of the loop
            }
            
        }
        
        // If there is no match the item is added to the array
        if(!found)
        {
            // Allocate space on the heap for the new item
            Item* item = new Item;
            item->type = type;
            item->isWanted = isWanted;
            item->price = price;
            message_board[number_unsold++] = item;
        }
 
    }
    
    // Done reading, close file
    file.close();
    cout << "#" << endl;
    
    // Printing out the items that are still on the message board
    for(int k = 0; message_board[k] != NULL; k++)
    {
        cout << message_board[k]->type << ", " << (message_board[k]->isWanted ? "wanted, " : "for sale, ") << message_board[k]->price << endl;
    }
    cout << "#" << endl;
    
    // Print out the count of the number of operations performed
    cout << "operations:" << number_operations << endl; 
    
    return 0;
}

