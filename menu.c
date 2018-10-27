#include<stdio.h>
#include<stdlib.h>


void menuRules();
void randomRule();
int selectRule();
void decToBinary(int); 
void menuCA();
void generate();
void initParent();
int applyRules();
void createNewGen();
void createFirstGen();
void selectMenu();

//Probably best to change later to pass from function, but need to figure out how to do that using pointers first
int ruleNum[8]; 
int parent[31] = { 0 };
int currGen[31];


int main()
{
  createFirstGen();
  //menuRules();
}

void menuRules()
{
  int choice = 0;
  
 
  do
  {
    printf("\nEnter option:\n" );
    printf("=========================\n" );
    printf("1.Random Rule\n" );
    printf("2.Select a Rule\n" );
    printf("3.Exit\n" );
    printf("=========================\n" );
    scanf("%d",&choice);

    switch(choice) {

      case 1  :
          randomRule();
      // ca menu  
          break; /* optional */
  
      case 2  :
          selectMenu();     
        //ca menu 
          break; /* optional */

        case 3  :
        printf("Exiting program :) \n");
        break; /* optional */
  
            /* you can have any number of case statements */
            default : /* Optional */
            break;
        }

  }while(choice!=3);
}

// function to convert decimal to binary 
void decToBinary(int n) 
{ 
    // array to store binary number 
    int reverseBinaryNum[8] = { 0 }; 
  
    // counter for binary array 
    int i = 0; 
    int d;
    while (n > 0) { 
  
        // storing remainder in binary array 
        reverseBinaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 

    for (i = 8 - 1, d = 0; i >= 0; i--, d++)
      ruleNum[d] = reverseBinaryNum[i];

}

void randomRule()
{
  int r = rand() % 256;
  printf("Rule %d \n", r);
  decToBinary(r);
  generate();
}

void initParent()
{
  parent[15] = 1;

  for(int i=0; i<31; i++)
  {
    currGen[i] = parent[i];
  }
  
}
void selectMenu() //user can select whether to generate whole array or just first generation
{
  int num;
  int input;

  printf("do you just want to create the first generation? \n");
  printf("1 = yes\n");
  printf("2 = no\n");
  scanf("%d", &input);

  if (input == 1)
  {
    createFirstGen();
  }
  else if (input == 2)
  {
    printf("Enter a decimal number between 0 and 255\n");
        scanf("%d",&num);
        decToBinary(num);
        generate();
  }
}
void createFirstGen() //This function will be implmented in Select a Rule
{
  int start;

  printf("select starting point\n");
  scanf("%d", &start);
  
  //This is just input validation
  if (start > 31 || start < 0)
  {
    printf("===================================\n");
    printf("Please pick value between 0 and 31!\n");
    printf("===================================\n");
    createFirstGen();
  }
  else
  {
    parent[start] = 1;

    for(int i=0; i<31; i++)
    {
      currGen[i] = parent[i];
    }
    
    for (int i = 0; i < 31; ++i)
    {
       printf("%d", currGen[i]);
    }
 }
 
  printf("\n");
  printf("\n");

 
}

void createNewGen()
{
  int newGen[31] = { 0 };

  //Currently the first and last element in each generation are unchanged. Need to do this without going out of bounds
  for(int i = 1; i<30; i++)
  {
    int left = currGen[i-1];
    int middle = currGen[i];
    int right = currGen[i+1];

    newGen[i] = applyRules(left, middle, right);
  }

  for(int i=0; i<31; i++)
  {
    currGen[i] = newGen[i];
  }

}

void generate()
{
  printf("\n");
  printf("\n");

  for(int i = 0; i < 15; i++)
  {
    if(i == 0)
    {
      putchar('\n');
      initParent();
    }

    else
    {
      putchar('\n');
      createNewGen();
    }
   
    for(int c=0; c<31; c++)
    {
      printf("%d", currGen[c]);
    }
  } 

  printf("\n");
  printf("\n");
}

int applyRules (int a, int b, int c) {
    if      (a == 1 && b == 1 && c == 1) return ruleNum[0];
    else if (a == 1 && b == 1 && c == 0) return ruleNum[1];
    else if (a == 1 && b == 0 && c == 1) return ruleNum[2];
    else if (a == 1 && b == 0 && c == 0) return ruleNum[3];
    else if (a == 0 && b == 1 && c == 1) return ruleNum[4];
    else if (a == 0 && b == 1 && c == 0) return ruleNum[5];
    else if (a == 0 && b == 0 && c == 1) return ruleNum[6];
    else if (a == 0 && b == 0 && c == 0) return ruleNum[7];
    return 0;
}