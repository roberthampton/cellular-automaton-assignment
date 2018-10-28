#include<stdio.h>
#include<stdlib.h>


void menuRules();
void menuCA();
void rulePrint();
void decToBinary(int);

void initParent();
void generate(int);
void createNewGen();
int applyRules(int,int,int);


//holds rule for the program
char rule[7];

int parent[31] = { 0 };

int currGen[31];


int main()
{
	menuRules();

	rulePrint();
}


//Menu to choose a rule for the program
void menuRules()
{
	int choice = 0;
	int r;
	int num;
	do
	{
		printf("Enter option:\n" );
		printf("=========================\n" );
		printf("1.Random Rule\n" );
		printf("2.Select a Rule\n" );
		printf("3.Exit\n" );
		printf("=========================\n" );
		scanf("%d",&choice);

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
    // counter for binary array
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array in reverse order (first index in array is last number)
        rule[i]=n % 2;
        n = n / 2;
        i++;
    }

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
    int choice = 0;

	do
	{
		printf("Enter option:\n" );
		printf("=========================\n" );
		printf("1.Create first generation\n" );
		printf("2.Start with pre-made generation \n" );
		printf("3.Return to previous menu \n" );
		printf("4.Exit\n" );
		printf("=========================\n" );
		scanf("%d",&choice);

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

	}while(choice!=3);

}

//generates first gen with index 15 = 1  and initializes everything else to 0
void initParent()
{
  parent[15] = 1;
        int i;
      for(i=0; i<31; i++)
      {
        currGen[i] = parent[i];
      }
}

void createFirstGen() //lets the user create first generation
{
           int start;

           do//This is just input validation
           {
            printf("===================================\n");
            printf("Please pick value between 0 and 31!\n");
            printf("===================================\n");
            printf("select starting point\n");
            scanf("%d", &start);
           }while (start > 31 || start < 0);

            parent[start] = 1;
            int i;
            for(i =0; i<31; i++)
            {
              currGen[i] = parent[i];
            }

         }

// starts generating 15 generations and printing them
void generate(int choice)
{
  printf("\n");
  printf("\n");
    int i;
      for( i= 0; i < 15; i++)
      {

        if(i == 0)
        {
            printf("\n");

            if(choice==1)
            {
                createFirstGen();
            }else if(choice==2)
            {
                initParent();
            }

        }

        else
        {
          printf("\n");
          createNewGen();
        }

            int c;
        for(c=0; c<31; c++)
        {
          printf("%d", currGen[c]);
        }
      }

  printf("\n");
  printf("\n");
}

// creates the next generation based on the rules
void createNewGen()
{
  int newGen[31] = { 0 };

  //Currently the first and last element in each generation are unchanged. Need to do this without going out of bounds
  int i;
  for( i= 1; i<30; i++)
  {
    int left = currGen[i-1];
    int middle = currGen[i];
    int right = currGen[i+1];

    newGen[i] = applyRules(left, middle, right);
  }
int k;
  for(k=0; k<31; k++)
  {
    currGen[k] = newGen[k];
  }

}



