#include "MovieTree.hpp"
#include <iostream>
#include <fstream>


using namespace std;
/* ------------------------Starter Code function---------- */
LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}

void preorderTraversalHelper(TreeNode * root) {
	if (root == NULL) 
    {
		return;
	}
    cout << root->titleChar << " ";
    preorderTraversalHelper(root->leftChild);
    preorderTraversalHelper(root->rightChild);
}

void MovieTree::preorderTraversal() {
	preorderTraversalHelper(root);
	cout << endl;
}

TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

/* --------------------------Constructor---------------------------- */
MovieTree::MovieTree()
{
    root = nullptr;
}

/* --------------------------Destructor---------------------------- */

void MovieTree:: rdelete(TreeNode *node)
{
	//TODO
    if(node==nullptr){
        return;
    }
    LLMovieNode* temp;
    while(node->head!=nullptr){
        temp = node->head;
        node->head = node->head->next;
        delete temp;
    }
    rdelete(node->leftChild);
    rdelete(node->rightChild);
    delete node;
}

MovieTree::~MovieTree()
{
    rdelete(root);
}

/* -------------------------showMovieCollection----------------------------- */
void MovieTree::printMovieInventoryHelper(TreeNode* node)
{
    TreeNode * t = node;
    // for every non-empty TreeNode (t) in the tree 
    if(t != nullptr){
        printMovieInventoryHelper(t->leftChild);

        if(t->head != nullptr){
            cout << "Movies starting with letter: " << t->titleChar << endl;
        }

        LLMovieNode * m = t->head;

        // for every LLMovieNode (m) attached to t

        while(m != nullptr){
            cout << " >> " << m->title << " " << m->rating << endl;
            m = m->next;
        }

        printMovieInventoryHelper(t->rightChild);
    
    }
}

void MovieTree::showMovieCollection()
{
    TreeNode* m = root;
    if(m==nullptr){
        return;
    }
    printMovieInventoryHelper(m);
}

/* --------------------------insertMovie---------------------------- */
TreeNode* MovieTree::addHelper(TreeNode *root, TreeNode* parentpointer, int _ranking, string _title, int _year, float _rating)
{
    if(root == nullptr){                    // root is empty

        // create new movie node
    	LLMovieNode * n = new LLMovieNode;
        n->ranking = _ranking;
        n->title = _title;
        n->year = _year;
        n->rating = _rating;

        TreeNode * e = new TreeNode;    // create new treenode
        e->titleChar = n->title[0];     // set first letter of title to Title Char
        e->head = n;                    // set the head of the linked list to our MovieNode n
        e->parent = parentpointer;             
        return e;
    }

    if(_title[0] > root->titleChar){
        root->rightChild = addHelper(root->rightChild, root, _ranking, _title, _year, _rating);
    }
    else if(_title[0] < root->titleChar){
        root->leftChild = addHelper(root->leftChild, root, _ranking, _title, _year, _rating);
    }
    else if(_title[0] == root->titleChar){  
        // create new movie node
    	LLMovieNode * n = new LLMovieNode;
        n->ranking = _ranking;
        n->title = _title;
        n->year = _year;
        n->rating = _rating;

        LLMovieNode *temp = root->head; 
        LLMovieNode *prev;
        if(n->title < temp->title){
            n->next = temp;
            root->head = n;
        }
        else{
            while(n->title > temp->title){    
                if(temp->next == nullptr){
                    temp->next = n;
                    n->next = nullptr;
                    return root;
                }
                prev = temp;
                temp = temp->next;
            }
            prev->next = n;
            n->next = temp;
        }
    }
    return root;
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating)
{
    if(root==nullptr){
        root = addHelper(root, nullptr, ranking, title, year, rating);
    }
    else{
        root = addHelper(root, root->parent, ranking, title, year, rating);
    }
}

/* ------------------------removeMovieRecord------------------------------ */
void MovieTree::removeMovieRecord(std::string title)
{
    TreeNode * tempTN = root;       
    bool found = false;
    if(root==nullptr){
        cout << "Movie not found." << endl;
        return;
    }
    
    while(!found){
        while(title[0] < tempTN->titleChar){
            if(tempTN->leftChild == nullptr){
                cout << "Movie not found." << endl;
                return;
            }
            tempTN = tempTN->leftChild;
        }
        while(title[0] > tempTN->titleChar){
            if(tempTN->rightChild == nullptr){
                cout << "Movie not found." << endl;
                return;
            }
            tempTN = tempTN->rightChild;
        }
        if(title[0]==tempTN->titleChar){
            LLMovieNode * tempLL = tempTN->head;
            LLMovieNode * prev;
            while(tempLL!=nullptr){
                if(tempTN->head->title == title){       // EDGE CASE: head node contains title
                    tempTN->head = tempLL->next;
                    delete tempLL;
                    return;                            
                }
                else if(tempLL->title == title){        // Otherwise check if node exists in LL
                    prev->next = tempLL->next;
                    delete tempLL;
                    return;
                }
                prev = tempLL;
                tempLL = tempLL->next;
            }
            cout << "Movie not found." << endl;         // if we get to this point, movie was not in LL
            return;
        }      
    }
}

/* ------------------------removeBSTNode------------------------------ */
void MovieTree::removeLLnodes(TreeNode* node){
    LLMovieNode * temp;
    while(node->head != nullptr){
        temp = node->head;
        node->head = node->head->next;
        delete temp;
    }
}

// takes in node->rightChild to find successor of node;
TreeNode* MovieTree::getSuccessor(TreeNode* node){

    if(node == nullptr){
        return node;                       // node has no successor, return null
    }
    while(node->leftChild != nullptr){
        node = node->leftChild;           // get leftmost node or node->rightChild
    }
    return node;
}

TreeNode* MovieTree::removeBSTNodeHelper(TreeNode* node, TreeNode* parent, char titleFirstLetter){

    TreeNode * r = node;
    if(node==nullptr){
        return nullptr;
    }
    if(node->titleChar > titleFirstLetter){
        node->leftChild = removeBSTNodeHelper(node->leftChild, node, titleFirstLetter);
    }
    else if(node->titleChar < titleFirstLetter){
        node->rightChild = removeBSTNodeHelper(node->rightChild, node, titleFirstLetter);
    }
    else if(node->titleChar == titleFirstLetter){   // its equal
        removeLLnodes(node);

        if(node->leftChild != nullptr && node->rightChild != nullptr){          // has both right and left children

            TreeNode *success = getSuccessor(node->rightChild);                 // get successor to node -> this takes place of node

            if(success->rightChild != nullptr && success != node->rightChild){
                success->rightChild->parent = success->parent;
                success->parent->leftChild = success->rightChild;
            }

            success->parent = parent;
            success->leftChild = node->leftChild;
            success->leftChild->parent = success;
            if(success != node->rightChild){
                success->rightChild = node->rightChild;
                success->rightChild->parent = success;
            }
            r = success; 
        }    
        else if(node->leftChild == nullptr){                                    // node only having right child
            node->rightChild->parent = node->parent;
            r = node->rightChild;
        }
        else if(node->rightChild == nullptr){                                    // node only having left child
            node->leftChild->parent = node->parent;
            r = node->leftChild;
        }
        // else node is a leaf
        else{                             
            r = nullptr;
        }
        delete node;
    }
    return r;
}

void MovieTree::removeBSTNode(char titleFirstLetter){
    root = removeBSTNodeHelper(root, nullptr, titleFirstLetter);
}


/* --------------------------rightRotation---------------------------- */
void MovieTree::rightRotation(TreeNode* curr)
{
    TreeNode * l = curr->leftChild;                    // y is curr

    if(l==nullptr){                 // check if current has no left child
        return;
    }

    if(curr->parent != nullptr){
        if(curr->parent->rightChild == curr){
            curr->parent->rightChild = l;
        }
        else{
            curr->parent->leftChild = l;
        }
    }
    else{
        root = l;
    }

    l->parent = curr->parent;
    curr->parent = l;

    curr->leftChild = l->rightChild;
    l->rightChild = curr;

}
