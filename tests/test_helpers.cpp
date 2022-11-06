#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/MovieTree.hpp"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}


traceNode *traceHead = NULL;
bool verbose = false;
int numAllocs = 0;

string test_showMovieCollection(string* name,int* ranking, int* year, float* rating, int len)
{
     MovieTree* tree = new MovieTree();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<ranking[i]<<", "<<name[i]<<", "<<year[i]<<", "<<rating[i] <<")"<< endl;
        tree->insertMovie(ranking[i],name[i],year[i],rating[i]);
    }
    cout<<"[GRADER] Printing movie inventory:"<<endl;
    tree->showMovieCollection();
    
     // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_InsertMovieCollection(string* name,int* ranking, int* year, float* rating, int len, char parent, char child)
{
     MovieTree* tree = new MovieTree();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<ranking[i]<<", "<<name[i]<<", "<<year[i]<<", "<<rating[i] <<")"<< endl;
        tree->insertMovie(ranking[i],name[i],year[i],rating[i]);
    }
    cout<<"[GRADER] Printing movie inventory:"<<endl;
    tree->showMovieCollection();
    
    if(parent!='\0' &&child!='\0')
    {
        TreeNode* pNode = tree->searchCharNode(parent);
        TreeNode* cNode = tree->searchCharNode(child);
        //cout<<pNode
        if(!pNode || !cNode)
        {
            cout<< "ERROR: parent of " <<child<< "is not correct. Set the child's parent accordingly"<<endl;
        }
        else if(cNode->parent!=pNode)
        {
            cout<< "ERROR: parent of " <<child<< "is not correct. Set the child's parent accordingly"<<endl;
        }
    }
    else if(parent=='\0' &&child!='\0')
    {
        TreeNode* pNode = NULL;
        TreeNode* cNode = tree->searchCharNode(child);
        if(!cNode)
        {
            cout<< "ERROR: parent of " <<child<< "is not correct. Set the child's parent accordingly"<<endl;
        }
        else if(cNode->parent!=pNode)
        {
            cout<< "ERROR: parent of " <<child<< "is not correct. Set the child's parent accordingly"<<endl;
        }
    }
     // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_RemoveMovieNode(string* name,int* ranking, int* year, float* rating, int len, string del, bool isEmptyHead)
{
    MovieTree* tree = new MovieTree();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<ranking[i]<<", "<<name[i]<<", "<<year[i]<<", "<<rating[i] <<")"<< endl;
        tree->insertMovie(ranking[i],name[i],year[i],rating[i]);
    }
    
    cout << "[GRADER] Deleting: "<<del<< endl;    
    tree->removeMovieRecord(del);
    cout<<"[GRADER] Printing movie inventory:"<<endl;
    tree->showMovieCollection();
    if(isEmptyHead)
    {
        TreeNode* tNode = tree->searchCharNode(del[0]);
        if(tNode->head!= NULL)
        {
               cout<<"ERROR: "<< tNode->titleChar << " inventory should be empty and isn't."<<endl;
        }
    }
    
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_GetSuccessor(string* name,int* ranking, int* year, float* rating, int len, char del, bool isEmptyHead){
    MovieTree* tree = new MovieTree();
    testing::internal::CaptureStdout();

    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<ranking[i]<<", "<<name[i]<<", "<<year[i]<<", "<<rating[i] <<")"<< endl;
        tree->insertMovie(ranking[i],name[i],year[i],rating[i]);
    }
    
    cout << "[GRADER] Getting successor of node "<<del<< endl; 
    TreeNode* rightSubtree = tree->searchCharNode(del);
    if(rightSubtree){
        TreeNode* movie = tree->getSuccessor(rightSubtree->rightChild);
        cout<<"[GRADER] Successor is : " << movie->titleChar <<endl;
    }
   
    
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}



string test_RemoveBSTNode(string* name,int* ranking, int* year, float* rating, int len, char del, bool isEmptyHead)
{
    MovieTree* tree = new MovieTree();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<ranking[i]<<", "<<name[i]<<", "<<year[i]<<", "<<rating[i] <<")"<< endl;
        tree->insertMovie(ranking[i],name[i],year[i],rating[i]);
    }
    
    cout << "[GRADER] Deleting BST node with title: "<<del<< endl;    
    tree->removeBSTNode(del);
    cout<<"[GRADER] Printing movie inventory:"<<endl;
    tree->showMovieCollection();
    if(isEmptyHead)
    {
        TreeNode* tNode = tree->searchCharNode(del);
        if(tNode != NULL)
        {
               cout<<"ERROR: "<< tNode->titleChar << " inventory should be empty and isn't."<<endl;
        }
    }
    
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_RightRotation(string* name,int* ranking, int* year, float* rating, int len, char r)
{
    MovieTree* tree = new MovieTree();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<ranking[i]<<", "<<name[i]<<", "<<year[i]<<", "<<rating[i] <<")"<< endl;
        tree->insertMovie(ranking[i],name[i],year[i],rating[i]);
    }
    
    TreeNode* curr = tree->searchCharNode(r);
    

    if(curr)
    {
        TreeNode* oldParent = curr->parent;
        TreeNode* left = curr->leftChild;
        TreeNode* oldright = left->rightChild;
        tree->rightRotation(curr);
        if( curr->leftChild != oldright || left->rightChild!= curr)
            cout<< "failed rotation"<<endl;
        else if(oldParent != left->parent || curr->parent!=left)
            cout<< "Parent pointer not set. failed rotation"<<endl;
        else
            cout<< "Rotation successful"<<endl;
    }
    tree->showMovieCollection();
    
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}