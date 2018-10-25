#include<stdio.h>
#include<stdlib.h>


void menuRules();
void menuCA();
void ruleZero();
void decToBinary(int);


char rule[7];

int main()
{
	menuRules();

	ruleZero();
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
			// ca menu
      		break;

   		case 2  :

			printf("Enter a decimal number between 0 and 255\n");
   			scanf("%d",&num);
    		decToBinary(num);
    		//ca menu
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

        // storing remainder in binary array
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

//menu to work with the cellular automation
void menuCA()
{


}
