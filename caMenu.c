#include<stdio.h>
#include<stdlib.h>


void menuRules();
int randomRule();
int selectRule();
void decToBinary(int); 
void menuCA();

int main()
{
	menuRules();
}

void menuRules()
{
	int choice = 0;

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
      		int r = rand() % 256;
			// ca menu  
      		break; /* optional */
	
   		case 2  :
      		int num;
			printf("Enter a decimal number between 0 and 255\n");
   			scanf("%d",&num);
    		decToBinary(num);
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
    int binaryNum[1000]; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
  
    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) 
        printf("%d\n", binaryNum[j]); 
} 
