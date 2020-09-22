#include "TreeAndNode.h"
tree::~tree()
{
  if(head != NULL)
    delete(head);
  //calls delete function for node which will delete every node in the tree
}



tree::tree(string x)
{
  // gives the trees a set maxDepth of 3 for their initilization
  maxDepth = 3;
  if(x == "grow")
    Grow();
  if(x == "full")
    Full();
}

tree::tree(string x, int y)
{ //gives the trees a set maxDepth of y for their initilization
  maxDepth = y;
  if(x == "grow")
    Grow();
  if(x == "full")
    Full(); 
}

string tree::treeToString(node* start, int x)
{
  //function converts the tree into a "readable" equation
  static string y = "";
  
  if(start->term)
    if(start->variable)
      {
	y += "x";
      }
    else
      {
	y += to_string(start->value); 
      }
  else if(start->operators == "+")
    {
      treeToString(start->left,1);
      y+="+";
      treeToString(start->right,1);
    }
  else if(start->operators == "-")
    {
      treeToString(start->left,1);
      y+="-";
      treeToString(start->right,1);
    }
  else if(start->operators == "/")
    {
      y+="\\frac{";
      treeToString(start->left,1);
      y+="}{";
      treeToString(start->right,1);
      y+="}";
}
  else if(start->operators == "*")
    {
      treeToString(start->left,1);
      y+="\\cdot{";
      treeToString(start->right,1);
      y+="}";
    }
  else if(start->operators == "s")
    {
      //treeToString(left,1);
      y+="\\sqrt{";
      treeToString(start->right,1);
      y+="}";
    }
  else if(start->operators == "sq")
    {
      treeToString(start->left,1);
      y+="^{";
      treeToString(start->right,1);
      y+="}";
    }
  return y;
}


void tree::mutate()
{
  bool IsLeft = false;
  node* previous = head;
  node* mutator = randomNodeWithPar(head, previous, IsLeft, 0);  //returns a random node witha pointer to its previous node

  int x = rand() % 100;
  if(mutator->term == false)    // Currently A NonTerminal
    {
      //______________Convert To a Terminal_____________________________
      if(x >90)
	{
	  delete(mutator);
	  if(IsLeft)
	    {
	      previous->left = new node('t');
	    }
	  else
	    {
	      previous->right = new node('t');
	    }
	}
      else //______________Convert to a nonterminal________________________
	{
	  if(mutator->unary == true)
	    mutator->left = new node('t');
	  mutator->unary = false;
	  int y = rand() % 6;
	  switch(y)
	    {
	    case 0:
	      mutator->operators = "+";
	      break;
	    case 1:
	      mutator->operators = "-";
	      break;
	    case 2:
	      mutator->operators = "/";
	      break;
	    case 3:
	      mutator->operators = "*";
	      break;
	    case 4:
	      mutator->operators = "s";
	      delete(mutator->left);
	      mutator->unary = true;
	      mutator->left = NULL;         //DONT GET RID OF THIS LINE. CAUSED SEGFAULT FOR LIKE 2 DAYS AND WAS IMPOSSIBLE TO FIGURE OUT
	      break;
	    case 5:
	      mutator->operators = "sq";
	      break;
	    default:
	      mutator->operators = "+";
	      break;
	    }
	}
    }
  else               //Current A Terminal
    {
      //______________Convert To a Terminal_____________________________
      if(x > 90)
	{
	  delete(mutator);
	  if(IsLeft)
	    {
	      previous->left = new node('t');
	    }
	  else
	    {
	      previous->right = new node('t');
	    }
	}
      else //______________Convert to a nonterminal________________________
	{
	  delete(mutator);
	  if(IsLeft)
	    {
	      previous->left = new node('n');
	      mutator = previous->left;
	    }
	  else
	    {
	      previous->right = new node('n');
	      mutator = previous->right;
	    }
	  if(mutator->unary)
	    {
	      mutator->right = new node('t');
	    }
	  else
	    {
	      mutator->right = new node('t');
	      mutator->left = new node('t');
	    }
	}
    }
}

tree::tree(node* star)  // makes a deepCopy Tree with the node passed 
{
  head = new node(star->term,star->value,star->operators, star->variable, star->unary); 
  if(star->right != NULL)
    head->right = DeepCopy(star->right);
  if(star->left != NULL)
    head->left = DeepCopy(star->left);
}


node* tree::DeepCopy(node* curr)   //reccursive deep copy of a tree
{
  node* retNode = new node(curr->term, curr->value, curr->operators, curr->variable, curr->unary);
  if(curr->right != NULL)
    retNode->right = DeepCopy(curr->right);
  if(curr->left != NULL)
    retNode->left = DeepCopy(curr->left);
  return retNode;
}



void tree::print2DUtil(node *root, int space) //NOT MINE just a function that prints the tree out in a graphical manner
{ 
  if (root == NULL) 
    return;    
  space += COUNT; 
  print2DUtil(root->right, space); 
  printf("\n"); 
  for (int i = COUNT; i < space; i++) 
    printf(" ");
  if(root->term == true)
    {
      if(root -> variable == true)
	cout << "x" << endl;
      else
	cout<< root->value << endl; 
    }
  else
    cout << root->operators << endl;
  print2DUtil(root->left, space); 
} 



void tree::print2D(node *root) //interface for the print function
{ 
  print2DUtil(root, 0); 
}



void tree::Grow()   
{
  head = new node('n');
  GrowR(head, 0);
}



void tree::GrowR(node* Curr, int depth)  //grows the tree until it reaches max depth or all the new nodes are terminals
{  
  int chance1 = rand() % 100;
  int chance2 = rand() % 100;
  if(Curr->term)
    {
      return;
    }
  else if(depth == maxDepth)
    {
      if(Curr->unary)
	Curr->right = new node('t');
      else
	{
	  Curr->right = new node('t');
	  Curr->left = new node('t');
	}
    }
  else if(Curr->unary && chance1 > 89)
    {
      Curr->right = new node('t');
    }
  else if(Curr -> unary && chance1 <= 89)
    {
      Curr->right = new node('n');
      GrowR(Curr->right, depth+1);
    }
  else if(chance1 > 89)
    {
      if(chance2 > 89)
	{
	  Curr->right = new node('t');
	  Curr->left = new node('t');
	}
      else
	{
	  Curr->right = new node('t');
	  Curr->left = new node('n');
	  GrowR(Curr->left, depth+1);
	}
    }
  else if(chance1 <= 89)
    {
      if(chance2 > 89)
	{
	  Curr->right = new node('n');
	  Curr->left = new node('t');
	  GrowR(Curr->right, depth+1);
	}
      else
	{
	  Curr->right = new node('n');
	  Curr->left = new node('n');
	  GrowR(Curr->left, depth+1);
	  GrowR(Curr->right, depth+1);
	}
    }
}




void tree::Full()
{
  head = new node('n');
  FullR(head, 0);
}



void tree::FullR(node* Curr, int depth)  //makes all new nodes into non-terminals until max-depth is reached
{
  if(depth == maxDepth)
    {
      if(Curr->unary)
	Curr->right = new node('t');
      else
	{
	  Curr->right = new node('t');
	  Curr->left = new node('t');
	}
    }
  else if(Curr -> unary)
    {
      Curr->right = new node('n');
      FullR(Curr->right, depth+1);
    }
  else
    {
      Curr->right = new node('n');
      Curr->left = new node('n');
      FullR(Curr->right, depth+1);
      FullR(Curr->left, depth+1);
    }
}



double tree::evaluateTree(double x)   //evaluates the tree given a value for x
{
  return head->evaluate(x);
}



node* tree::randomNode(node* start)  //returns a random node in a tree
{
  if(start == NULL)
    return NULL;
  int totalSize = numberOfNodes(start);
  int leftSize = numberOfNodes(start->left);
  //int rightSize = numberOfNodes(start->right);
  int index = rand() % totalSize;
  if(index < leftSize)
    {
      return randomNode(start->left);
    }
  else if(index == leftSize)
    {
      return start;
    }
  else
    {
      return randomNode(start->right);
    }  
}


node* tree::randomNodeWithPar(node* start, node*& prev, bool& left, int count)  //returns a random node in a tree with a pointer to the head of the node of that tree. also a bool value for whether the node was left or right of the head of that node
{
  if(count == 0)
    {
      if(start->right == NULL && start->left == NULL)
	{
	  return start;
	}
      else if (start->right == NULL)
	{
	  prev = start;
	  left = true;
	  return randomNodeWithPar(start->left, prev, left, 1);
	}
      else if (start->left == NULL)
	{
	  prev = start;
	  left = false;
	  return randomNodeWithPar(start->right, prev, left, 1);
	}
      int leftOr = rand() %2;
      if(leftOr == 0)
	{
	  prev = start;
	  left = true;
	  return randomNodeWithPar(start->left, prev, left, 1);
	}
      else 
	{
	  prev = start;
	  left = false;
	  return randomNodeWithPar(start->right, prev, left, 1);
	}      
    }
  if(start == NULL)
    return NULL;
  int totalSize = numberOfNodes(start);
  //  cout << totalSize << endl << flush;
  int leftSize = numberOfNodes(start->left);
  //int rightSize = numberOfNodes(start->right);
  int index = rand() % totalSize;
  if(index < leftSize)
    {
      prev = start;
      left = true;
      return randomNodeWithPar(start->left, prev, left , count);
    }
  else if(index == leftSize)
    {
      return start;
    }
  else
    {
      prev = start;
      left = false;
      return randomNodeWithPar(start->right, prev, left, count);
    }  
}


int tree::numberOfNodes(node* start)  //returns the number of nodes in a tree
{
  if(start == NULL)
    return 0;
  else if(start->right == NULL)
    return  numberOfNodes(start->left) + 1;
  else if(start->left == NULL)
    return numberOfNodes(start->right) + 1;
  else if(start->left == NULL && start->right == NULL)
    return 1;
  else
    return numberOfNodes(start->right) + numberOfNodes(start->left) + 1;
  //  return 0;
}

int tree::depthOfTree(node* start)  //returns the current depth of a tree
{
  if(start == NULL)
    {
      return 0;
    }
  else 
    { 
      int lDepth = depthOfTree(start->left); 
      int rDepth = depthOfTree(start->right); 
      if (lDepth > rDepth)  
	return(lDepth+1); 
      else return(rDepth+1); 
    } 
}  
  

