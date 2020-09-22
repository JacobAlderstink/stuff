#include <iostream>
#include <math.h>
#define COUNT 30
using namespace std;
class node
{
public:
  bool term;           //if a node is a terminal
  double value;        //value stored in that node
  string operators;    //operator of that node
  bool variable;       //if true its x
  bool unary;          //if true its a unary operator (sqrt)
  ~node();             //deconstructor
public:
  node* right;         
  node* left;          
  double evaluate(double x);  //evaluates the tree
  node(char);                 //new random node
  node(bool,double,string, bool, bool); //copy node
};


class tree
{
public:
  int maxDepth;        //only for initialization purposes, holds initial max depth of tree
  node *head;          
  double fitness;      //fitnes value of the tree
  
public:
  string treeToString(node*,int);     //converts tree to "readable" equation
  int depthOfTree(node*);             //returns depth of tree
  node* randomNodeWithPar(node* start, node*&prev, bool& left, int);
  void mutate();                      //mutates tree
  node* randomNode(node*);            //returns random node
  int numberOfNodes(node* start);     //returns # of nodes in tree
  ~tree();             
  tree(node*);                        //deepcopy constructor  
  node* DeepCopy(node*);              //deepcopy tool function
  void print2D(node*);
  void print2DUtil(node*, int);
  double evaluateTree(double x);
  tree(string);
  tree(string,int);
  void FullR(node*, int depth);
  void GrowR(node*, int depth);
  void Grow();
  void Full();
};

