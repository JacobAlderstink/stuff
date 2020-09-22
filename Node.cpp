#include "TreeAndNode.h"

// void node::deepDelete(node* pointer)
// {
//   if(pointer ->right != NULL)
//     deepDelete(pointer->right);
//   if(pointer ->left != NULL)
//     deepDelete(pointer->left);
//   if(this != NULL)
//     delete(pointer);  
// }


node::~node()
{
  if(right != NULL)
    delete(right);
  if(left != NULL)
    delete(left);  
}


node::node(bool termT, double valueT, string operationT, bool variableT, bool unaryT)
{

  //essentially a copy function that copies all values of a node
  term = termT;
  value = valueT;
  operators = operationT;
  unary = false;
  if(operationT == "s")
    unary = true;
  //unary = unaryT
  variable = variableT;
  right = NULL;
  left = NULL;
}


node::node(char type)
{  
  //creates a random new node of type either 'n' or 't'; 'n' being non-terminal, 't' being terminal
  if(type == 'n')
    {
      //cout << "here 2" << endl;
      term = false;
    }
  if(type == 't')
    {
      //cout << "here 3" << endl;
      term = true;
    }
  left = NULL;
  right = NULL;
  variable = false;
  int ValOrVar = rand() % 100;
  if(ValOrVar > 70)
    variable = true; //a terminal node has a ~30% chance of being x
  double x[] = {0, 1, -1, 10, 2, M_PI, M_E, sqrt(2), (1+sqrt(5))/2}; //other wise its one of these values 
  int index = rand() % 9;
  value = x[index];
  unary = false;
  if(!term)
    {
      unary = false;
      int y = rand() % 6;
      switch(y)
	{
	case 0:
	  operators = "+";
	  break;
	case 1:
	  operators = "-";
	  break;
	case 2:
	  operators = "/";
	  break;
	case 3:
	  operators = "*";
	  break;
	case 4:
	  operators = "s";	  
	  unary = true;
	  break;
	case 5:
	  operators = "sq";
	  break;
	default:
	  operators = "+";
	}
    }
}



double node::evaluate(double x)
{
  //most of this code just is error checking for left and right pointers being NULL or not NULL
  
  tree* s; //just a pointer that allows us to call our tree fucntions but doesnt actually point to an existing tree. 
  //in order traversal
  if(term == true)
    {
      if(variable == true)
	{
	  return x;
	}
      else
	return value;
    }
  else if(operators == "+")
    {
      if(left == NULL)
	{
	  cout << " left was NULL at \' + \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      if(right == NULL)
	{
	  cout << " right was NULL at \' + \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      return left->evaluate(x) + right->evaluate(x);
    }
  else if(operators == "-")
    {
      if(left == NULL)
	{
	  cout << " left was NULL at \' - \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      if(right == NULL)
	{
	  cout << " right was NULL at \' - \'" << endl;
	  s->print2D(this);
	  exit(1);
	}      
      return left->evaluate(x) - right->evaluate(x);
    }
  else if(operators == "/")
    {
      if(left == NULL)
	{
	  cout << " left was NULL at \' / \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      if(right == NULL)
	{
	  cout << " right was NULL at \' / \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      double rightside = right->evaluate(x);   //closure for the divide function
      if(rightside == 0)
	rightside = 1;
      return left->evaluate(x) / rightside;
    }
  else if(operators == "*")
    {
      if(left == NULL)
	{
	  cout << " left was NULL at \' * \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      if(right == NULL)
	{
	  cout << " right was NULL at \' * \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      return left->evaluate(x) * right->evaluate(x);
    }
  else if(operators == "s")
    {
      if(right == NULL)
	{
	  cout << " right was NULL at \' s \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      if(left != NULL)
	{
	  cout << " left wasnt NULL at \' s \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      double rightside = right->evaluate(x);
      if(rightside < 0)                      //closure for the sqrt function
	rightside = 0; 
    return sqrt(rightside);
    }
  else if(operators == "sq")
    {
      if(left == NULL)
	{
	  cout << " left was NULL at \' sq \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      if(right == NULL)
	{
	  cout << " right was NULL at \' sq \'" << endl;
	  s->print2D(this);
	  exit(1);
	}
      return pow(left->evaluate(x),right->evaluate(x));
    }
  else
    cout << "error operator uninitialized" << endl;  
  return 0;
}

