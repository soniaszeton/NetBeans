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
        bool isValid();
        int countLongestPath();
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
        void rbAddFixup(MovieNode *node); // called after insert to fix tree
        void leftRotate(MovieNode *tree, MovieNode *node);
        void rbDelete(MovieNode *z);
        void rightRotate(MovieNode *tree, MovieNode *node);
        void rbDeleteFixup(MovieNode *node);
        void replaceNode(MovieNode *tree, MovieNode *old_node, MovieNode *new_node);
        void rbTransplant(MovieNode *tree, MovieNode *u, MovieNode *v);
        int rbValid(MovieNode * node);
        int countLongestPath(MovieNode *node);
        MovieNode *nil; 
        MovieNode *root;
        //including the json_object in the class makes it global within the class, much easier to work with
        json_object *Assignment7Output;
        int operation_counter;
};


#endif	/* MOVIETREE_H */


TreeNode* minLeftNode(TreeNode* tree) {
    if (tree->left == NULL) {
        return tree;
    } else {
        return minLeftNode(tree->left);
    }
}

void deleteAndReplaceLeftMin(TreeNode *root, int key) {
    if (root != NULL) {

        if(key == root->key) {
            // Found the node to delete
            TreeNode *parent = root->parent;
            TreeNode *new_subtree = NULL;
    
            if (root->left != NULL || root->right != NULL) {
    
                if (root->right != NULL) {
                    // The new node is the right child (or nil)
                    root->right->parent = parent;
                    new_subtree = root->right;

                    if (root->left != NULL) {
                            TreeNode *minNode = minLeftNode(new_subtree);
                            minNode->left = root->left;
                            root->left->parent = minNode;
    
                } else {
                        root->left->parent = parent;
                        new_subtree = root->left;
                    }
                }
    
                if (parent != NULL) {
                    // Insert the new node into the parent
                    if (root == parent->left) {
                        parent->left = new_subtree;
                    } else {
                        parent->right = new_subtree;
                    }
                    if (new_subtree != NULL) {
                        new_subtree->parent = parent;
                    }
                }
    
                // Delete the old node
                delete root;
                // Assign the new subtree
                root = new_subtree;
            }
    
        } else if (key < root->key) {
            // The node to be deleted must be on the left side
            deleteAndReplaceLeftMin(root->left, key);
        } else {
            // The node to be deleted must be on the right side
            deleteAndReplaceLeftMin(root->right, key);
    
    } else {
        cout << "Movie not found." << endl;
    }
  }
}

