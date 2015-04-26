/* MovieTree.cpp implements functions in the header file
 * Assignment 5
 * Sonia Szeton
 * Mentor: Derk Norton
 * 2/23/15
 */

#include "MovieTree.h"
#include <iostream>
#include <string>
using namespace std;

MovieTree::MovieTree() {
    nil = new MovieNode;
    nil->parent = nil;
    nil->leftChild = nil;
    nil->rightChild = nil;
    nil->isRed = false;
    root = nil;
    initJson();
}

MovieTree::~MovieTree() {
    deleteAll(root);
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment7Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("add");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_parameter = json_object_new_string(title.c_str());
    json_object_object_add(j_operation, "parameter", operation_parameter);
    json_object *operation_output = json_object_new_array();
    json_object_object_add(j_operation, "output", operation_output);
    MovieNode *new_node = new MovieNode;
    new_node->ranking = ranking;
    new_node->title = title;
    new_node->year = releaseYear;
    new_node->quantity = quantity;
    new_node->leftChild = nil;
    new_node->rightChild = nil;
    new_node->parent = nil;
    new_node->isRed = true;
    if (root != nil) {
        insert(new_node, root, operation_output);
    } else {
        root = new_node;
        root->isRed = false;
    }

    rbAddFixup(new_node);

}

void MovieTree::findMovie(string title) {
    MovieNode* found_movie = MovieTree::searchMovieTree(root, title, NULL);
    if (found_movie != nil) {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << found_movie->ranking << endl;
        cout << "Title:" << found_movie->title << endl;
        cout << "Year:" << found_movie->year << endl;
        cout << "Quantity:" << found_movie->quantity << endl;
    } else {
        cout << "Movie not found." << endl;
    }
}

void MovieTree::deleteAll(MovieNode* tree) {
    if (tree != nil) {
        deleteAll(tree->leftChild);
        deleteAll(tree->rightChild);
        delete tree;
    }
}

void MovieTree::printMovieInventory() {
    printMovieInventory(root);
}

void MovieTree::printMovieInventory(MovieNode* tree) {
    if (tree != nil) {
        printMovieInventory(tree->leftChild);
        cout << "Movie: " << tree->title << endl;
        printMovieInventory(tree->rightChild);
    }
}

void MovieTree::rentMovie(string title) {
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment7Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("rent");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_parameter = json_object_new_string(title.c_str());
    json_object_object_add(j_operation, "parameter", operation_parameter);
    json_object *operation_output = json_object_new_array();
    json_object_object_add(j_operation, "output", operation_output);

    MovieNode *wanted_movie = searchMovieTree(root, title, operation_output);
    if (wanted_movie != nil) {
        if (wanted_movie->quantity > 0) {
            cout << "Movie has been rented." << endl;
            wanted_movie->quantity--;
            if(wanted_movie->quantity == 0) {
                rbDelete(wanted_movie);
            }
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << wanted_movie->ranking << endl;
            cout << "Title:" << wanted_movie->title << endl;
            cout << "Year:" << wanted_movie->year << endl;
            cout << "Quantity:" << wanted_movie->quantity << endl;

        } else {
            cout << "Movie out of stock." << endl;
        }
    } else {
        cout << "Movie not found." << endl;
    }
}

int MovieTree::countMovieNodes() {
    int num_movies = countMovieNodes(root);
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment7Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("count");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_output = json_object_new_int(num_movies);
    json_object_object_add(j_operation, "output", operation_output);
    return num_movies;
}

int MovieTree::countMovieNodes(MovieNode *tree) {
    int num_movies = 0;
    if (tree != nil) {
        num_movies += countMovieNodes(tree->leftChild);
        num_movies += 1;
        num_movies += countMovieNodes(tree->rightChild);
    }
    return num_movies;

}

void MovieTree::initJson() {
    Assignment7Output = json_object_new_object();
    operation_counter = 1;
}

void MovieTree::deleteMovieNode(string title) {
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment7Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("delete");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_parameter = json_object_new_string(title.c_str());
    json_object_object_add(j_operation, "parameter", operation_parameter);
    json_object *operation_output = json_object_new_array();
    json_object_object_add(j_operation, "output", operation_output);
    MovieNode *unwanted_movie = searchMovieTree(root, title, operation_output);
    rbDelete(unwanted_movie);

}

MovieNode* MovieTree::deleteNode(MovieNode* tree, string title, json_object * traverseLog) {
    if (tree != nil) {
        if (traverseLog != NULL) {
            json_object *j_title = json_object_new_string(tree->title.c_str());
            json_object_array_add(traverseLog, j_title);
        }

        if (title == tree->title) {
            // Found the node to delete
            MovieNode *parent = tree->parent;
            MovieNode *new_subtree = nil;

            if (tree->leftChild != nil || tree->rightChild != nil) {

                if (tree->rightChild != nil) {
                    // The new node is the right child (or nil)
                    tree->rightChild->parent = parent;
                    new_subtree = tree->rightChild;

                    if (tree->leftChild != nil) {
                        MovieNode *minNode = minLeftNode(new_subtree);
                        minNode->leftChild = tree->leftChild;
                        tree->leftChild->parent = minNode;

                    }
                } else {
                    tree->leftChild->parent = parent;
                    new_subtree = tree->leftChild;
                }
            }

            if (parent != nil) {
                // Insert the new node into the parent
                if (tree == parent->leftChild) {
                    parent->leftChild = new_subtree;
                } else {
                    parent->rightChild = new_subtree;
                }
                if (new_subtree != nil) {
                    new_subtree->parent = parent;
                }
            }

            // Delete the old node
            delete tree;
            // Assign the new subtree
            tree = new_subtree;

        } else if (title < tree->title) {
            // The node to be deleted must be on the left side
            tree->leftChild = deleteNode(tree->leftChild, title, traverseLog);
        } else {
            // The node to be deleted must be on the right side
            tree->rightChild = deleteNode(tree->rightChild, title, traverseLog);
        }
    } else {
        cout << "Movie not found." << endl;
    }

    // return the new subtree
    rbDeleteFixup(tree);
    return tree;
}

MovieNode* MovieTree::minLeftNode(MovieNode* tree) {
    if (tree->leftChild == nil) {
        return tree;
    } else {
        return minLeftNode(tree->leftChild);
    }
}

MovieNode* MovieTree::minRightNode(MovieNode* tree) {
    if (tree->rightChild == nil) {
        return tree;
    } else {
        return minRightNode(tree->rightChild);
    }
}

json_object* MovieTree::getJsonObject() {
    return Assignment7Output;
}

MovieNode* MovieTree::searchMovieTree(MovieNode* tree, string title, json_object * traverseLog) {
    if (tree != nil) {
        if (traverseLog != NULL) {
            json_object *j_title = json_object_new_string(tree->title.c_str());
            json_object_array_add(traverseLog, j_title);
        }
        if (title == tree->title)
            return tree;
        if (title < tree->title)
            return searchMovieTree(tree->leftChild, title, traverseLog);
        else
            return searchMovieTree(tree->rightChild, title, traverseLog);
    } else
        return nil;
}

void MovieTree::insert(MovieNode *new_node, MovieNode *tree, json_object * traverseLog) {
    string title = new_node->title;
    if (traverseLog != NULL) {
        json_object *j_title = json_object_new_string(tree->title.c_str());
        json_object_array_add(traverseLog, j_title);
    }
    if (title < tree->title) {
        if (tree->leftChild != nil) {
            insert(new_node, tree->leftChild, traverseLog);
        } else {
            tree->leftChild = new_node;
            new_node->parent = tree;
        }
    } else if (title >= tree->title) {
        if (tree->rightChild != nil) {
            insert(new_node, tree->rightChild, traverseLog);
        } else {
            tree->rightChild = new_node;
            new_node->parent = tree;
        }
    }
}

bool MovieTree::isValid() {
    int result = rbValid(root);
    return result > 0;
}

// Returns 0 if the tree is invalid, otherwise returns the black node height. 

int MovieTree::rbValid(MovieNode * node) {
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1;

    else {
        // First check for consecutive red links. 
        if (node->isRed) {
            if (node->leftChild->isRed || node->rightChild->isRed) {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }

        // Check for valid binary search tree. 
        if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0)) {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }

        // Determine the height of let and right children. 
        lh = rbValid(node->leftChild);
        rh = rbValid(node->rightChild);

        // black height mismatch 
        if (lh != 0 && rh != 0 && lh != rh) {
            cout << "This tree contains a black height violation" << endl;
            return 0;
        }

        // If neither height is zero, incrament if it if black. 
        if (lh != 0 && rh != 0) {
            if (node->isRed)
                return lh;
            else
                return lh + 1;
        } else
            return 0;

    }
}

// node is the top of the subtree that just got changed

void MovieTree::rbAddFixup(MovieNode *node) {
    MovieNode * uncle = NULL;

    // Set the left/right nodes to the sentinal
    node->leftChild = nil;
    node->rightChild = nil;

    // Now we restore the red-black properties. 
    while ((node != root) && (node->parent->isRed)) {
        // If our parent is a a left child.  
        if (node->parent == node->parent->parent->leftChild) {
            // If node's parent is a left, y is x's right uncle. 
            uncle = node->parent->parent->rightChild;

            // Case 1, red uncle node 
            if (uncle->isRed) {
                // Change colors of parent,uncle,grandparent
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                // Move node up the tree. 
                node = node->parent->parent;
            }// Case 2/3 , black uncle node 
            else {
                // right child of left child 
                if (node == node->parent->rightChild) {
                    // Rotate the parent around node. 
                    node = node->parent;
                    leftRotate(root, node);
                }
                // Case 3 left child of left child
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                rightRotate(root, node->parent->parent);
            }
        }// Else if the parent is a right child. 
        else {
            // If node's parent is a left, y is x's right uncle. 
            uncle = node->parent->parent->leftChild;
            // Case 1, red uncle node 
            if (uncle->isRed == true) {
                // Change colors of parent,uncle,grandparent
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                // Move node up the tree. 
                node = node->parent->parent;
            }// Case 2/3 , black uncle node 
            else {
                // left child of left child 
                if (node == node->parent->leftChild) {
                    // Rotate the parent around node. 
                    node = node->parent;
                    rightRotate(root, node);
                }
                // Case 3 left child of left child
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                leftRotate(root, node->parent->parent);
            }
        }
    }

    // Ensure the root is still black. 
    root->isRed = false;

    return;

}

void MovieTree::replaceNode(MovieNode *tree, MovieNode *old_node, MovieNode *new_node) {
    if (old_node->parent == nil) {
        tree = new_node;
    } else {
        if (old_node == old_node->parent->leftChild) {
            old_node->parent->leftChild = new_node;
        } else {
            old_node->parent->rightChild = new_node;
        }
    }
    if (new_node != nil) {
        new_node->parent = old_node->parent;
    }
}

void MovieTree::leftRotate(MovieNode *tree, MovieNode *node) {
    MovieNode* r = new MovieNode;
    r = node->rightChild;
    replaceNode(tree, node, r);
    node->rightChild = r->leftChild;
    if (r->leftChild != nil) {
        r->leftChild->parent = node;
    }
    r->leftChild = node;
    node->parent = r;
}

void MovieTree::rbDelete(MovieNode *z) {
    MovieNode * y = z;
    MovieNode * x = nil;
    bool yOrigColor = y->isRed;

    if (z->leftChild == nil) {
        x = z->rightChild;
        rbTransplant(root, z, z->rightChild);
    } else if (z->rightChild == nil) {
        x = z->leftChild;
        rbTransplant(root, z, z->leftChild);
    } else {
        // y = tree min of right
        y = z->rightChild;
        while (y->leftChild != nil) {
            y = y->leftChild;
        }

        yOrigColor = y->isRed;
        x = y->rightChild;

        if (y->parent == z)
            x->parent = y;

        else {
            rbTransplant(root, y, y->rightChild);
            y->rightChild = z->rightChild;
            y->rightChild->parent = y;
        }
        rbTransplant(root, z, y);
        y->leftChild = z->leftChild;
        y->leftChild->parent = y;
        y->isRed = z->isRed;
    }

    // Actually the node. 
    delete z;

    // Check if we need to now fix the tree. 
    if (yOrigColor == false)
        rbDeleteFixup(x);
}

void MovieTree::rightRotate(MovieNode *tree, MovieNode *node) {
    MovieNode* L = new MovieNode;
    L = node->leftChild;
    replaceNode(tree, node, L);
    node->leftChild = L->rightChild;
    if (L->rightChild != nil) {
        L->rightChild->parent = node;
    }
    L->rightChild = node;
    node->parent = L;

}

void MovieTree::rbDeleteFixup(MovieNode *node) {
    MovieNode * w = NULL;

    // Now we restore the red-black properties. 
    while ((node != root) && (node->isRed == false)) {
        // If we are a left child  
        if (node == node->parent->leftChild) {
            w = node->parent->rightChild;

            // If helper is red 
            if (w->isRed) {
                w->isRed = false;
                node->parent->isRed = true;
                leftRotate(root, node->parent);
                w = node->parent->rightChild;
            }

            // If helper's children are both black 
            if (w->leftChild->isRed == false && w->rightChild->isRed == false) {
                w->isRed = true;
                node = node->parent;
            } else {
                if (w->rightChild->isRed == false) {
                    // case 3
                    w->leftChild->isRed = false;
                    w->isRed = true;
                    rightRotate(root, w);
                    w = node->parent->rightChild;
                }
                // case 4
                w->isRed = node->parent->isRed;
                node->parent->isRed = false;
                w->rightChild->isRed = false;
                leftRotate(root, node->parent);
                node = root;
            }
        }// If we are a right child 
        else {

            // helper is the left child 
            w = node->parent->leftChild;
            // If helper is red 
            if (w->isRed) {
                w->isRed = false;
                node->parent->isRed = true;
                rightRotate(root, node->parent);
                w = node->parent->leftChild;
            }

            // If helper's children are both black 
            if (w->leftChild->isRed == false && w->rightChild->isRed == false) {
                w->isRed = true;
                node = node->parent;
            } else {
                if (w->leftChild->isRed == false) {
                    // case 3
                    w->rightChild->isRed = false;
                    w->isRed = true;
                    leftRotate(root, w);
                    w = node->parent->leftChild;
                }

                // case 4
                w->isRed = node->parent->isRed;
                node->parent->isRed = false;
                w->leftChild->isRed = false;
                rightRotate(root, node->parent);
                node = root;
            }
        }

    }

    node->isRed = false;
    return;

}

void MovieTree::rbTransplant(MovieNode *tree, MovieNode *u, MovieNode *v) {
    if (u->parent == nil) {
        tree = v;
    } else if (u == u->parent->leftChild) {
        u->parent->leftChild = v;
    } else {
        u->parent->rightChild = v;
    }
    v->parent = u->parent;
}

// ALL FROM http://ideone.com/mr7juv

int MovieTree::countLongestPath(MovieNode *node) {
    // If we hit the end, just return the count;
    if (node == nil)
        return 0;
    // Return the largest path from this point. 
    return max(countLongestPath(node->rightChild), countLongestPath(node->leftChild)) + 1;
}
// FROM http://cslibrary.stanford.edu/110/BinaryTrees.html

int MovieTree::countLongestPath() {
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    int height = countLongestPath(root);


    // Update our json object
    json_object *jsonOperation = json_object_new_string("height");
    json_object_object_add(newJSON, "operation", jsonOperation);
    json_object *jsonOutput = json_object_new_string(to_string(height).c_str());
    json_object_object_add(newJSON, "output", jsonOutput);
    json_object_object_add(Assignment7Output, to_string(operation_counter).c_str(), newJSON);
    operation_counter++;

    return height;
}




