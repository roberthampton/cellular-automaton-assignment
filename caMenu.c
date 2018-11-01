#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define gridSize 4
void menuRules();
void menuCA();
void rulePrint();
void decToBinary(int);

void initParent(int parent[], int currGen[], int genLength);
void generate(int);
void createNewGen(int parent[], int currGen[], int genLength);
int applyRules(int,int,int);
int chooseGenLength();
void writeGensToTextFile(int currGen[], int genLength);
void writeDescriptionToTextFile(int genLength, int genNumber);
int validateInput(int min, int max);


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

	rulePrint();
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
		printf("1.Random Rule\n" );
		printf("2.Select a Rule\n" );
    printf("3. Game of Life\n");
		printf("4.Exit\n" );
		printf("=========================\n" );
		choice = validateInput(1,4);


		switch(choice) {

   		case 1  :
      		r = rand() % 256;
      		decToBinary(r);
			menuCA();
      		break;

   		case 2  :

			printf("Enter a decimal number between 0 and 255\n");
   			scanf("%d",&num);
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

	}while(choice!=3);
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

int validateInput(int min, int max)
{
  int choice = 0;
  int accepted = 0;
      while(accepted == 0)
    {
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
        printf("%d\n", rule[i]);
    }

}

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
	do
	{
		printf("Enter option:\n" );
		printf("=========================\n" );
		printf("1.Create first generation\n" );
		printf("2.Start with pre-made generation \n" );
		printf("3.Return to previous menu \n" );
		printf("4.Exit\n" );
		printf("=========================\n" );
		choice = validateInput(1,4);

		switch(choice) {

   		case 1  :
                    generate(1);
      		break;

   		case 2  :
                    generate(2);
      		break;
        case 3  :
                    menuRules();
        break;

      	case 4  :
      	printf("Exiting program :) \n");
      	break;
   					default :
   					break;
				}

	}while(choice!=4);

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

//generates first gen with  the middle index = 1  and initializes everything else to 0
void initParent(int parent[], int currGen[], int genLength)
{
      for(int i=0; i<genLength; i++)
      {
        parent[i]=0;
        //I think parent is probably unneccessary -- could just do this with curr gen.
        currGen[i] = parent[i];
      }

      currGen[genLength/2]=1;
}

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

// starts generating 15 generations and printing them
// Should rename to something more meaningful probably.
void generate(int choice)
{
  /*prompts user for both length of gen and number of gens first. could add in some kind of flag system 
  where once this has run once it doesnt have to be done every time. 
  */
  int genLength = chooseGenLength();
  int genNumber = chooseNumberOfGens();

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

        int c;
        for(c=0; c<genLength; c++)
        {
          printf("%d", currGen[c]);

        }
        writeGensToTextFile(currGen, genLength);
      }

  printf("\n");
  printf("\n");
}

void writeDescriptionToTextFile(int genLength, int genNumber)
{
	FILE *f = fopen("file.txt", "a+");

	if (f == NULL)
	{
	   printf("Error opening file!\n");
	   exit(1);
	}

	fprintf(f, "\nThis is rule %d\n", ruleNum);
	fprintf(f, "There are %d cells in each generation, and there are %d generations in total\n\n", genLength, genNumber);

	fclose(f);
}

//writes each current gen array into a file
//Still needs some work, as currently it will write every rule to this file with no separation.
void writeGensToTextFile(int currGen[], int genLength)
{
  FILE *f = fopen("file.txt", "a+");

  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  for(int i = 0; i < genLength; i++)
  {
    fprintf(f, "%d", currGen[i]);
  }

  fprintf(f, "\n" );

  fclose(f);
}

// creates the next generation based on the rules
void createNewGen(int parent[], int currGen[], int genLength)
{
  int newGen[genLength];

  for(int i=0; i<genLength; i++)
  {
    newGen[i]= 0;
  }

  //Currently the first and last element in each generation are unchanged. Need to do this without going out of bounds
  int i;
  for( i= 0; i < genLength; i++)
  {
  	int left;
    int middle;
    int right;
  	
  	if(i == 0)
  	{
  		left = currGen[genLength-1];
    	middle = currGen[i];
    	right = currGen[i+1];
  	}

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

    newGen[i] = applyRules(left, middle, right);
  }
  int k;
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



