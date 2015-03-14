/* 
 * Assignment 5
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Created on February 23, 2015, 3:43 PM
 */

#ifndef MOVIETREE_H
#define	MOVIETREE_H
#include <string>
#include <json.h>

struct MovieNode {
    int ranking;
    std::string title;
    int year;
    int quantity;
    bool isRed;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        isRed = true;
    }

};

class MovieTree
{
    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void initJson();
        //bool isValid();
        //int countLongestPath();
        //use this to return the json object from the class when you are ready to write it to a file
        json_object* getJsonObject();
        
    protected:
    private:
        void deleteAll(MovieNode * node);
        void printMovieInventory(MovieNode * node);
        void insert(MovieNode *node, MovieNode *tree, json_object * traverseLog);
        MovieNode* deleteNode(MovieNode* tree, std::string title, json_object * traverseLog);
        MovieNode* searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog);
        int countMovieNodes(MovieNode *node);
        MovieNode* minLeftNode(MovieNode* tree);
        MovieNode* minRightNode(MovieNode* tree);
        /* void rbAddFixup(MovieNode * node); // called after insert to fix tree
        void leftRotate(MovieNode * x);
        void rbDelete(MovieNode * z);
        void rightRotate(MovieNode * x);
        void rbDeleteFixup(MovieNode * node);
        void rbTransplant(MovieNode * u, MovieNode * v);
        int rbValid(MovieNode * node);
        int countLongestPath(MovieNode *node);
        MovieNode *nil; */
        MovieNode *root;
        //including the json_object in the class makes it global within the class, much easier to work with
        json_object *Assignment6Output;
        int operation_counter;
};


#endif	/* MOVIETREE_H */

