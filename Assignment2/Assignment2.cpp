/* 
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * 1/26/15
 * Assignment 2
 * Professor Hoenigman
 * This program goes through an entire book and keeps track of how often words
 * are used. It will print out a list of the most used words excluding the top 
 * 50 most used words as well as the number of unique words and total words.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;


// Creates the struct to hold the information for a word
struct Word
{
    string word;
    int count;
};

// Creates an array of pointers to words as well as counters
int array_size = 100;
Word** word_array = new Word*[array_size];
int word_count = 0;
int times_doubled = 0;


// Algorithm from Wikipedia 
void bubbleSort(Word** array, int length)
{
    bool swapped = true;
    do
   {
       swapped = false;
       for(int i = 1; i < length; i++)
       {
           if(array[i-1]->count < array[i]->count)
           {
               Word* word = array[i-1];
               array[i-1] = array[i];
               array[i] = word;
               swapped = true;
           }
       }
   }while(swapped);
}

// Array of the 50 most common words
string common_words[50] = {
    "the",
    "be",
    "to",
    "of",
    "and",
    "a",
    "in",
    "that",
    "have",
    "i",
    "it",
    "for",
    "not",
    "on",
    "with",
    "he",
    "as",
    "you",
    "do",
    "at",
    "this",
    "but",
    "his",
    "by",
    "from",
    "they",
    "we",
    "say",
    "her",
    "she",
    "or",
    "an",
    "will",
    "my",
    "one",
    "all",
    "would",
    "there",
    "their",
    "what",
    "so",
    "up",
    "out",
    "if",
    "about",
    "who",
    "get",
    "which",
    "go",
    "me"
};

// Checks to see if a word is one of the 50 most common words
bool isCommon(string word)
{
    // Check to see if its a common word
    for(int i = 0; i < 50; i++)
    {
        if(common_words[i] == word)
        {
            // Is a common word, no need to keep checking
            return true;
        }
    }
    return false;
}

// Goes through the array to see if the word is already there
bool isExistingWord(string word)
{
    for(int i = 0; word_array[i] != NULL; i++)
    {
        Word* possible_match = word_array[i];

        // The word is in the array already so bump up the count
        if(possible_match->word == word)
        {
            possible_match->count++;
            return true;
        }
    }
    return false;
}

// Adds the new word to the array and doubles the array as necessary
void insertNewWord(string word)
{
    if(word_count == array_size-1)
    {

        // Create new array twice the size of the original
        Word** new_word_array = new Word*[array_size*2];

        // Copying all the pointers from the old array into the new array
        for(int k = 0; k < array_size; k++)
        {
            new_word_array[k] = word_array[k];
        }
        // delete old array to avoid memory leak, reset pointer and size
        delete [] word_array;
        word_array = new_word_array;
        array_size *= 2;
        times_doubled++;
    
    }
    // Allocate space on the heap for the new item
    Word* the_word = new Word;
    the_word->word = word;
    the_word->count = 1;
    word_array[word_count++] = the_word;
    
}


int main(int argc, char** argv) {
    
    // Opens the file from the command line argument
    string data_filename = argv[1]; 
    int top_word_count = stoi(argv[2]);
    ifstream file;
    file.open(data_filename);
    if(!file.is_open())
    {
        cout << "File not found." << endl;
        return 0;
    }
    
    // Reads each line parses it into words, either finds in the array and ups count or adds to the array
    string word;
    int total_word_count = 0;
    while(file >> word)
    {
        if(!isCommon(word))
        {
            if(!isExistingWord(word))
            {
                insertNewWord(word);
            }
            total_word_count++;
        }
    }
    
    file.close();
    
    // Sort the array by largest word count
    bubbleSort(word_array, word_count);
    
    // Prints out the most used uncommon words in order
    for(int i = 0; i < top_word_count; i++)
    {
        cout << word_array[i]->count << " - " << word_array[i]->word << endl;
    }
    cout << "#" << endl;
    cout << "Array doubled: " << times_doubled << endl;
    cout << "#" << endl;
    cout << "Unique non-common words: " << word_count << endl;
    cout << "#" << endl;
    cout << "Total non-common words: " << total_word_count << endl;
    
    return 0;
}

