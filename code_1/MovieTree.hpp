#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;


struct LLMovieNode
{
  int ranking;
  std::string title;
  int year;
  float rating;
  struct LLMovieNode* next;

  void *operator new(std::size_t bytes);
  void operator delete(void *);
};

struct TreeNode
{
  LLMovieNode* head = NULL;
  char titleChar;
  TreeNode *parent = NULL;
  TreeNode *leftChild = NULL;
  TreeNode *rightChild = NULL;

  void *operator new(std::size_t bytes);
  void operator delete(void *);
};

class MovieTree
{
    public:
  // Check writeup for detailed function descriptions
    MovieTree();
    ~MovieTree();
    void showMovieCollection();
    void preorderTraversal();
    void insertMovie(int ranking, std::string title, int year, float rating);
    void removeMovieRecord(std::string title);
    void removeBSTNode(char titleFirstLetter);
    TreeNode* searchCharNode(char key);
    void rightRotation(TreeNode* curr);
    TreeNode* getSuccessor(TreeNode* node);

  private:
    TreeNode *root;
    void rdelete(TreeNode *node);
    void printMovieInventoryHelper(TreeNode* node);
    TreeNode* addHelper(TreeNode *root, TreeNode* parentpointer, int _ranking, string _title, int _year, float _rating);
    void removeLLnodes(TreeNode* node);
    TreeNode* removeBSTNodeHelper(TreeNode* node, TreeNode* parent, char titleFirstLetter);
};


struct traceNode
{
  std::string pType;
  void *ptr;
  traceNode *next = nullptr;
  traceNode(){}
  traceNode(std::string t, void *p, traceNode *n) : pType(t), ptr(p), next(n) {}
};

extern traceNode *traceHead;
extern bool verbose;
extern int numAllocs;

inline traceNode * addTraceNode(std::string pType, void *ptr, traceNode *traceHead)
{
  traceNode *nn = new traceNode(pType, ptr, traceHead);
  return nn;
}

inline traceNode * removeTraceNode(traceNode *traceHead, void *ptr)
{

  if (traceHead == nullptr){
    std::cerr << "[ERROR] Attempted to delete a node that was never allocated." << std::endl;
    exit(1);
  }
  else if (traceHead->ptr == ptr){
    traceNode *tmp = traceHead->next;
    delete traceHead;
    return tmp;
  }
  else{
    traceHead->next = removeTraceNode(traceHead->next, ptr);
    return traceHead;
  }
}

//------------------Overloads LL nodes---------------------------------
inline void* LLMovieNode::operator new(std::size_t bytes)
{
  numAllocs += 1;
  void * buf = malloc(bytes);
  memset(buf, 0x0, bytes);

  if(verbose){
    std::cout << "[GRADER] Created LLMovieNode with address: " << buf << std::endl;
  }

  traceHead = addTraceNode("LL", buf, traceHead);

  return buf;
}

inline void LLMovieNode::operator delete(void *ptr)
{
  numAllocs -= 1;

  if (verbose){
      std::cout << "[GRADER] Deleted LLMovieNode with address: " << ptr << std::endl;
  }

  traceHead = removeTraceNode(traceHead, ptr);

  free(ptr);
}

//----------------------Overloads tree nodes---------------------------
inline void* TreeNode::operator new(std::size_t bytes)
{
  numAllocs += 1;
  void * buf = malloc(bytes);
  memset(buf, 0x0, bytes);

  if(verbose){
    std::cout << "[GRADER] Created TreeNode with address: " << buf << std::endl;
  }

  traceHead = addTraceNode("BST", buf, traceHead);

  return buf;
}

inline void TreeNode::operator delete(void *ptr)
{
  numAllocs -= 1;

  if (verbose){
      std::cout << "[GRADER] Deleted TreeNode with address: " << ptr << std::endl;
  }

  traceHead = removeTraceNode(traceHead, ptr);

  free(ptr);
}

//----------------------------------------------------
inline void printNode(traceNode * n)
{
  if(n->pType=="BST"){
    TreeNode *tn = (TreeNode*) n->ptr;
    cout << "    TreeNode <" << tn->titleChar << ">" << endl;
  }
  else if(n->pType=="LL"){
    LLMovieNode *ln = (LLMovieNode*) n->ptr;
    cout << "    LLMovieNode [" << ln->title << "]" << endl;
  }
}
