#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define gridSize 4
void menuRules();
void menuCA();
void rulePrint();
void decToBinary(int);

void initParent(int parent[], int currGen[], int genLength);
void generateCellularAutomaton(int);
void createNewGen(int parent[], int currGen[], int genLength);
int applyRules(int,int,int);
int chooseGenLength();
void writeGensToTextFile(int currGen[], int genLength);
void writeDescriptionToTextFile(int genLength, int genNumber);
int validateInput(int min, int max);
int generateRandomNumber();


//holds rule for the program
char rule[7];
int ruleNum;


//array for game of life blinker 
 int arr[gridSize][gridSize];  /* = { {0,1,0},
                  {0,1,0},
                  {0,1,0} };*/
 int arrGen[gridSize][gridSize];
 //functions for game of life
void gameOfLife();
void printArray();
void cellLives();



int main()
{
	menuRules();
  return 0;
}


//Menu to choose a rule for the program
void menuRules()
{
	int choice;
	int r;
	int num;
    
	do
	{
		printf("Enter option:\n" );
		printf("=========================\n" );
		printf("=========================\n" );
    printf("1.Random Rule\n" );
    printf("2.Select a Rule\n" );
    printf("3. Game of Life\n");
    printf("4.Exit\n" );
		printf("=========================\n" );
		choice = validateInput(1,4);


		switch(choice) {

   		case 1  :
      		r = generateRandomNumber();
      		decToBinary(r);
			menuCA();
      		break;

   		case 2  :

			printf("Enter a decimal number between 0 and 255\n");
   			num = validateInput(0,255);
    		decToBinary(num);
    		menuCA();
      		break;
        case 3  : 
          gameOfLife();
        break;
        case 4  :
        printf("Exiting program :) \n");
        break;
            default :
            break;
				}

	}while(choice!=4);
}

int generateRandomNumber()
{
  int r = rand() % 256;
  return r;
}

// function to convert decimal to binary
void decToBinary(int n)
{
    ruleNum = n;
    // counter for binary array
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array in reverse order (first index in array is last number)
        rule[i]=n % 2;
        n = n / 2;
        i++;
    }

}

/*
Takes the minimum and maximum possible value for an input, and ensures it is 
within the range and is an integer, then returns the integer
*/
int validateInput(int min, int max)
{
  int choice = 0;
  int accepted = 0;
      while(accepted == 0)
    {
      //Creates a string to hold the usersInput for checking
      char userInput[64];
      fgets(userInput, 63, stdin);
      if(sscanf(userInput, "%d", &choice)!= 1)
      {
        printf("This is not a valid integer. Please try again. \n");
        continue;
      }

      else
      {
        if((choice<min) ||(choice>max))
          printf("This is not an option. Please try again. \n");
        else
          accepted = 1;
      } 
    }

    return choice;
}

//print rule
void rulePrint()
{
int i;
    for(i = 0; i<=7;i++)
    {
        printf("%d", rule[i]);
    }

    printf("\n");

}

/*
Takes the the cell to be checked and its left and right neighbours and then uses 
this combination to return the appropriate bit from the rule array. 
*/
int applyRules (int a, int b, int c) {
    if      (a == 1 && b == 1 && c == 1) return rule[7];
    else if (a == 1 && b == 1 && c == 0) return rule[6];
    else if (a == 1 && b == 0 && c == 1) return rule[5];
    else if (a == 1 && b == 0 && c == 0) return rule[4];
    else if (a == 0 && b == 1 && c == 1) return rule[3];
    else if (a == 0 && b == 1 && c == 0) return rule[2];
    else if (a == 0 && b == 0 && c == 1) return rule[1];
    else if (a == 0 && b == 0 && c == 0) return rule[0];
    return 0;
}


//menu to work with the cellular automation
void menuCA()
{
  int choice;
  int exitMenu = 0;
	do
	{
		printf("Enter option:\n" );
		printf("=========================\n" );
		printf("1.Create first generation\n" );
		printf("2.Start with pre-made generation (middle cell is 1) \n" );
		printf("3.Return to previous menu \n" );
		printf("4.Exit\n" );
		printf("=========================\n" );
		choice = validateInput(1,4);

		switch(choice) {

   		case 1  :
                    generateCellularAutomaton(1);
                    exitMenu = 1;
      		break;

   		case 2  :
                    generateCellularAutomaton(2);
                    exitMenu = 1;
      		break;
        case 3  :
                    exitMenu = 1;
        break;

      	case 4  :
      	printf("Exiting program :) \n");
        exit(-1);
      	break;
   					default :
   					break;
				}

	}while(exitMenu == 0);

}

//Function to allow user to choose the length of each generation
int chooseGenLength()
{ 
  printf("\n Please enter how many cells you would like in each generation: ");
  int genLength = validateInput(3,120);

    return genLength;
}

//Fucntion to allow user to choose how many generations they would like to see.
int chooseNumberOfGens()
{
  printf("\n Please enter how many generations you would like in total: ");
  int genNumber = validateInput(2,120);

  return genNumber;
}

//generate first gen with  the middle index = 1  and initializes everything else to 0
void initParent(int parent[], int currGen[], int genLength)
{
      for(int i=0; i<genLength; i++)
      {
        parent[i]=0;
        currGen[i] = parent[i];
      }

      currGen[genLength/2]=1;
}

//Allows the user to select where the one is in the first generation.
void createFirstGen(int parent[], int currGen[], int genLength) //lets the user create first generation
{
            printf("===================================\n");
            printf("Please pick value between 0 and %d!\n", genLength);
            printf("===================================\n");
            printf("select starting point\n");
            int start = validateInput(0,genLength);
          
            for(int i =0; i<genLength; i++)
            {
              parent[i] = 0;
              currGen[i] = parent[i];
            }

            currGen[start-1] = 1;

         }

/*
Starts generating 15 generations and printing them. 
Takes an integer from the menu that determines whether or not the user will create their own parent generation.
*/
void generateCellularAutomaton(int choice)
{
  //prompts user for both length of each generation and number of generations first. 
  int genLength = chooseGenLength();
  int genNumber = chooseNumberOfGens();

  //Creates empty arrays of the size that is enetered by the user for the initial 'parent' generation and the current generation.
  int parent[genLength];
  int currGen[genLength];

  writeDescriptionToTextFile(genLength, genNumber);
  printf("\n");
  printf("\n");
    int i;
      for( i= 0; i < genNumber; i++)
      {

        if(i == 0)
        {
            printf("\n");

            if(choice==1)
            {
                createFirstGen(parent, currGen, genLength);
            }else if(choice==2)
            {
                initParent(parent, currGen, genLength);
            }
        }

        else
        {
          printf("\n");
          createNewGen(parent, currGen, genLength);
        }

        if(i == 0)
        {
          printf("This is rule number %d which in binary is: ", ruleNum);
          rulePrint();
        }

        int c;
        for(c=0; c<genLength; c++)
        {
          //printf("%d", currGen[c]);
          if(currGen[c] == 1)
            printf(".");
          else
            printf("O");

        }
        writeGensToTextFile(currGen, genLength);
      }

  printf("\n");
  printf("\n");
}

/*
Writes a description to the text file including the rule number, the number of cells in each generation 
and the total number of generations. 
*/
void writeDescriptionToTextFile(int genLength, int genNumber)
{
  //opens the file if it exists and otherwise creates it. 
  //It ignores whatever is already in it and continues from the next new line
	FILE *f = fopen("savedrules.txt", "a+");

  //Error message if the file cannot be opened. Will also terminate the program.
	if (f == NULL)
	{
	   printf("Error opening file!\n");
	   exit(1);
	}

  //Writes the appropriate information to the file.
	fprintf(f, "\nThis is rule %d\n", ruleNum);
	fprintf(f, "There are %d cells in each generation, and there are %d generations in total\n\n", genLength, genNumber);

  //Closes the file.
	fclose(f);
}

//writes each current generation array into a file after the description.
void writeGensToTextFile(int currGen[], int genLength)
{
  //opens the file if it exists and otherwise creates it. 
  //It ignores whatever is already in it and continues from the next new line
  FILE *f = fopen("savedrules.txt", "a+");

   //Error message if the file cannot be opened. Will also terminate the program.
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  //Writes each element from the currentGen array into the file to form the whole generation.
  for(int i = 0; i < genLength; i++)
  {
    fprintf(f, "%d", currGen[i]);
  }
  //Writes a new line to the file so that when the next generation is written in its on a new line.
  fprintf(f, "\n" );

  //Closes the file.
  fclose(f);
}

// creates the next generation based on the rules
void createNewGen(int parent[], int currGen[], int genLength)
{
  //Declares an array to hold the next generation.
  int newGen[genLength];

  for(int i=0; i<genLength; i++)
  {
    newGen[i]= 0;
  }

  //Currently the first and last element in each generation are unchanged. Need to do this without going out of bounds
  int i;
  for( i= 0; i < genLength; i++)
  {
    //Variables to store the bit from the current position and the left and right neighbours.
  	int left;
    int middle;
    int right;

  	/*
    For the left most cell, the rules are applied using the right most cell as the left neighbour.
    genLength is the size of the array so this is taken into consideration and the last cell is accessed by using the 
    index genLength-1 
    */
  	if(i == 0)
  	{
  		left = currGen[genLength-1];
    	middle = currGen[i];
    	right = currGen[i+1];
  	}

    //For the right most cell, the rules are applied using the left most cell as the right neighbour.
  	else if(i == (genLength-1))
  	{
  		left = currGen[genLength-2];
    	middle = currGen[genLength-1];
    	right = currGen[0];
  	}

  	else{
  		left = currGen[i-1];
    	middle = currGen[i];
    	right = currGen[i+1];
  	}
    // uses the rules to assign the new value to each element of the new generation.
    newGen[i] = applyRules(left, middle, right);
  }
  int k;
  //Sets the current gen to the new generation.
  for(k=0; k<genLength; k++)
  {
    currGen[k] = newGen[k];
  }
}


//runs the game of Life with a blinker 
void gameOfLife()
{
  //initialize array 
   for(int i = 0; i<gridSize; i++)
  {
    for(int k = 0; k<gridSize; k++)
    {
      arr[i][k] = rand() % 2;
    }
   }
  
   printf("This is the initial state of the blinker:\n");
  printArray();
   int answer; 
   do
  {
      cellLives();
       printf("This is next generationn \n");
      printArray();
      printf("To continue press '1' and '2' to stop  \n");
      answer = validateInput(1,2);
  }while(answer!=2);
 }
 //prints out current state of the array 
void printArray()
{
  for(int i = 0; i<gridSize; i++)
  {
      for(int k = 0; k<gridSize; k++)
      {
         printf("%d ", arr[i][k]);
      }
              printf("\n");
    }
}
 void cellLives()
{
  int N;
   for(int i = 0; i<gridSize; i++)
  {
      for(int k = 0; k<gridSize; k++)
      {
            N=0;
             //check left and right 
            
                if(arr[i][k-1]==1)
              {
                N++;
              } 
            
            
            
              if(arr[i][k+1]==1)
              {
                N++;
              } 
          
             
              if(arr[i-1][k]==1)
              {
                N++;
              } 
          
          
            if(arr[i+1][k]==1)
            {
              N++;
            } 
          
            
             //check diagonals 
          
            if(arr[i-1][k-1]==1)
            {
              N++;
            } 
          
            
          
            if(arr[i+1][k+1]==1)
            {
              N++;
            } 
          
            
          
            if(arr[i-1][k+1]==1)
            {
              N++;
            } 
          
            
          
             if(arr[i+1][k-1]==1)
            {
              N++;
            } 
          
             //Test correct neighbours display 
              /*
              printf("Array:");
              printf("%d ", arr[i][k]);
              printf("Neighbours:");
              printf("%d ", N);
              printf(" \n");*/
             switch(N)
            {
               case 0  :
                    if(arr[i][k]==1)
                    {
                      arrGen[i][k]=0;
                    } 
                    else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                    break;
               case 1  :
                     if(arr[i][k]==1)
                     {
                      arrGen[i][k]=0;
                     } 
                      else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                    break;
                     case 2:
                    arrGen[i][k] = arr[i][k];
                    break;
               case 3:
                    if(arr[i][k]==0)
                    {
                      arrGen[i][k]=1;
                    } 
                     else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                break;
                 case 4:
                    if(arr[i][k]==1)
                    {
                      arrGen[i][k]=0;
                    } 
                     else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                    break;
                 case 5:
                    if(arr[i][k]==1)
                    {
                      arrGen[i][k]=0;
                    } 
                     else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                    break;
                 case 6: 
                    if(arr[i][k]==1)
                    {
                      arrGen[i][k]=0;
                    } 
                     else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                    break;
                 case 7:
                    if(arr[i][k]==1)
                    {
                      arr[i][k]=0;
                    }
                     else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                    
                    break;
                  case 8:
                    if(arr[i][k]==1)
                    {
                      arr[i][k]=0;
                    } 
                     else
                    {
                      arrGen[i][k] = arr[i][k];
                    }
                    break;
                         default :
                        break;
            }
       }
     }
     for(int i = 0; i<gridSize; i++)
    {
        for(int k = 0; k<gridSize; k++)
        {
           arr[i][k] = arrGen[i][k];
        }
     }
 }




