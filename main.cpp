/*
Jacob Alderink 
October 10th 2018

The goal of this program is to recreate the math equation (x^4 + 3x + 32/ 36) to the best of the programs abilities. It does this by using a genetic program which utilizes trees to make equations. And then evolving these equations to find better results

It goes through 10000 iterations (ignore the variable named "generationCount") and our tree population is 100.

2 children are created with each iteration off of 2 parents.

Currently the mutation rate is 100% on both those children.

Mutation chooses any random node terminal or non-term and has a 90-10 chance of converting it to a non-term/term respectively.

The functions the tree is allowed to choose from is sqrt/ power/ + / - / * /divide/.

Closure is handled by for division by checking the denominator first for 0, and if it is then just have the denominator part = 1.

                      for the sqrt function by checking the operand first for negative values and if it is, it just sets it to 0.

final output of this algorithm is the best and average fitness for each iteration.
*/
  

//#include "../opennn/openn.h"
#include "TreeAndNode.h"
#include <unistd.h>

const int populationSize = 100;            //
tree* TreePop[populationSize];             //our population
const int generationCount = 10000;           //number of iterations the population will go through(yes I know the word generation is misleading considering its a steady-state model
const int MAXDEPTH = 6;                    //Max depth of trees before fitness penalty


int partition(int low, int high);          //These three functions are your typical quick sort function
void quickSort(int low, int high);
void qSort();
void Crossover(tree *&Tree1, tree *&Tree2);//DONE Chooses two parents. crosses over the children then mutates the children
void Initialize();                         //Initializes all the trees. The first 50 given the grow funtcion. The other 50 given the full function
void RunGen();                             //controls the iteration process by holding the loop that controls how many iterations the code will go through
void Mutate(tree *&child);                 //Mutates a given tree by changing a single chosen node into either a terminal or non-terminal
void Fitness(tree *&child1);               //Evaluates the fitness of a tree using the evaluate and the real evalute function. currently tests on 100 data points and uses the RMSE method plus an additional method that hurts fitness based on length of a tree
int Merge(tree *&child);                   //Finds the worst fitness in the population currently, and then replaces it with the new child if that worst fitness indvidual is worse then the one being replaced
tree* ChooseParent();                      //Chooses a parent based on fitness by choosing 5 random individuals in the population and then returning the one with the best fitness of those
void FitnessPop();                         //calls the fitness function on the entire population
double RealEvaluate(double x);             //this is the base function that our trees are trying to evaluate
void storeFitness();                       //Currently not in use //stores the fitnesses at a given iteration
double calculateAverageFitness();          //calculates the average fitness in a population
void printFitnesses();                     //prints out the average and best fitness over the generations
double calculateBestFitness();             //calculates the best fitness in the population

double fitnessValues[populationSize];      //stores current fitness values /*currently not in use*/
double averageFitness[generationCount];    //stores the average fitness values
double bestFitness[generationCount];       //stores the best fitness values

int main()
{
  srand(time(NULL));                       //randomizes the random values of rand(); 
  Initialize();                            
  RunGen();
  //PrintResults
}

double calculateAverageFitness()
{
  double sum = 0;
  for(int i = 0; i < populationSize; i++)
    sum+=TreePop[i]->fitness;
  return sum/populationSize;
}

double calculateBestFitness()
{
  
  return TreePop[0]->fitness;
}

void storeFitness()             //currently not in use. was for testing purposes
{
  for(int i = 0; i < populationSize; i++)
    {
      fitnessValues[i] = TreePop[i]->fitness;
      cout << i << ": " << fitnessValues[i] << endl;
    }
    TreePop[0]->print2D(TreePop[0]->head);
}

void printFitnesses()
{
  for(int i = 0; i < generationCount; i++) 
    {
      cout << averageFitness[i] << "\t";
      cout << bestFitness[i] << endl;
    }
}

void Initialize()              
{
  for(int i = 0; i < populationSize; i++)
    {
      if(i >= 50)
	TreePop[i] = new tree("full");  //first 50 are full trees
      else
	TreePop[i] = new tree("grow");  //second 50 are grow trees
    }
}

string finalstring()
{
  return TreePop[0]->treeToString(TreePop[0]->head,0);   //converts the tree equation to a "readable"(hard without subscript and superscripting characters) form
  
}

double RealEvaluate(double x)
{
  return (pow(x,4)+(3*x)+7)/36;    //currently trying to make the in function with just polynomial functions :) :)
}


void Fitness(tree *&child1)
{
  double recieved[30];
  double actual[30];
  int counter = 0;
  for(double i = -7.5; counter < 30; counter++, i += 0.5)
    {
      recieved[counter] = child1->evaluateTree(i);
      actual[counter] = RealEvaluate(i);
    }
  double fitTemp = 0;
  for(int i = 0; i < 30; i++)
    {
      fitTemp += pow(recieved[i]-actual[i],2);
    }
  //if(isnan(fitTemp/30.0))
  // fitTemp = 10000;
  child1->fitness = sqrt(fitTemp/100.0);
  int depth = child1->depthOfTree(child1->head);
  //cout << depth;
  if(MAXDEPTH < depth)
    {
      int diff = depth - MAXDEPTH;
      double hurtMultiplier = 1;
      for(int i = 0; i < diff; i++)
	{
	hurtMultiplier += 0.1;
	child1->fitness += 10; //(gives a fitness of + 10 for every size too large plus the multiplier)
	}
      child1->fitness *= hurtMultiplier;
    }
  if(isnan(child1->fitness))   //checks if fitness if nan then sets it to 1000 fitness so itll 99.999% of the time be replaced or not put in the population to begin with
    child1->fitness = 1000;
}


void FitnessPop()
{
  for(int i = 0; i < populationSize; i++)
    {
      Fitness(TreePop[i]);
    }
}



void RunGen()
{
  FitnessPop();
  qSort();
  for(int gen = 0; gen < generationCount; gen++)
    {
      tree* child1;
      tree* child2;
      Crossover(child1,child2);           //creates children
      if(child1 == NULL || child2 == NULL)
      	{
      	  cout << "error parent NULL1" << endl;
      	  exit(1);
      	}
      Mutate(child1);  //mutates
      Mutate(child2);
      Fitness(child1);
      Fitness(child2);
      if(Merge(child1))   //merge returns 1 if it wasnt placed in the pop.
	{
	  delete(child1);  //therefore it is deleted if it wasnt placed in the pop.
	}
      if(Merge(child2))
	{
	  delete(child2);
	}
      qSort();
      averageFitness[gen] = calculateAverageFitness();
      bestFitness[gen] = calculateBestFitness();
    }
  //  storeFitness();
  printFitnesses();
  //  TreePop[0]->print2D(TreePop[0]->head);
  cout << finalstring() << endl;
}


void Crossover(tree *&Tree1, tree *&Tree2)
{
  tree* parent1 = ChooseParent();
  tree* parent2 = ChooseParent();
  if(parent1 == NULL)
    {
      cout << "error parent NULL" << endl;
      exit(1);
    }
  if(parent2 == NULL)
    {
      cout << "error parent NULL" << endl;
      exit(1);
    }
  Tree1 = new tree(parent1->head);    
  Tree2 = new tree(parent2->head);    //this calls the deepcopy function that creates a whole new copy of a tree for the child here
  //   cout << "Tree1 before crossover" << endl;
  // Tree1->print2D(Tree1->head);
  // cout << "\n\n\n\n\nTree2 before crossover" << endl;
  // Tree2->print2D(Tree2->head);
  if(Tree1 == NULL)
    {
      cout << "error parent NULL" << endl;
      exit(1);
    }
  if(Tree2 == NULL)
    {
      cout << "error parent NULL" << endl;
      exit(1);
    }  
  bool left1 = true;
  bool left2 = true;
  node* parentnode1 = Tree1->head;
  node* parentnode2 = Tree2->head;
  node* partition1 = Tree1->randomNodeWithPar(Tree1->head, parentnode1, left1, 0);  //if left1 is true that means the node that points to the chosen node is on the left
  node* partition2 = Tree2->randomNodeWithPar(Tree2->head, parentnode2, left2, 0);  //parentnode1 (or 2) points is the head pointer to the chosen randomnode. with it either being its left or right node
  // cout << "Partition 1" << endl;         
  // Tree1->print2D(partition1);
  // cout << "Partition 2" << endl;
  // Tree1->print2D(partition2);  
  if(left2 == true)
    {
      parentnode2->left = partition1;
    }
  else
    {
      parentnode2->right = partition1;
    }
  if(left1 == true)
    {
      parentnode1->left = partition2;
    }
  else
    {
      parentnode1->right = partition2;
    }
  // cout << "\n\n\n\n\n\nTree1 after crossover" << endl;
  // Tree1->print2D(Tree1->head);
  // cout << "\n\n\n\n\n\nTree2 after crossover" << endl;
  // Tree2->print2D(Tree2->head);
}


void Mutate(tree *&child)
{
  if(child == NULL)
    {
      cout << "error parent NULL" << endl;
      exit(1);
    }
  //  cout << "Child before MUtation" << endl;
  //  child->print2D(child->head);
  child->mutate();
  //  cout << "Child after MUtation" << endl;
  //  child->print2D(child->head);
}



tree* ChooseParent()
{
  int index[5];
  for(int i = 0; i < 5; i++)
    {
     index[i] = rand() % populationSize;
    }
  int bestindex = index[0];  
  for(int i = 0; i < 5; i++)
    {
      if(TreePop[index[i]]->fitness < TreePop[bestindex]->fitness)
	{
	  bestindex = index[i];
	}
    }
  return TreePop[bestindex];
}



void qSort()
{ 
  quickSort(0,populationSize-1);  
}



void quickSort(int low, int high)
{
  if(low < high)
    {
      int pi = partition(low,high);
      quickSort(low,pi-1);
      quickSort(pi+1,high);
    }
}



int partition(int low, int high)
{
  double pivot = TreePop[high]->fitness;
  int i = low-1;
  for(int j = low; j <= high -1; j++)
    {
      if(TreePop[j]->fitness <= pivot)
	{
	  i++;
	  swap(TreePop[i],TreePop[j]);
	}
    }
  swap(TreePop[i+1],TreePop[high]);
  return i+1;
}


int Merge(tree *&child)
{
  int index = 0;
  for(int i = index; i < populationSize; i++)
    {
      if(TreePop[i]->fitness > TreePop[index]->fitness)
	{
	  index = i;
	}
    }  
  if(TreePop[index]->fitness < child->fitness)
    {
      return 1;
    }
  else
    {
      delete(TreePop[index]); //deletes the tree being replaced by calling the deconstructor for our trees
      TreePop[index] = child;  
    }
  return 0;
}
