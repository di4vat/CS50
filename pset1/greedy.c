/**
*  greedy.c
*    
*  Divine Attipoe
*  divineattipoe@gmail.com
*
*  Solution to the greedy algorithm problem from pset1 
*   
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define QUARTER 25;
#define DIME 10;
#define NICKEL 5;

int main(void)
{
    // Variable declarations
    float given_amount = 0;
    int cent = 0;
    int quarter_count = 0;
    int dime_count = 0;
    int nickel_count = 0;
    int leftover = 0;
    int coin_count = 0;
    
    // Input handling
    do 
    {
        printf("You gave me: ");
        given_amount = GetFloat();
        
        // If given amount is zero or less then zero checked
        if (given_amount == 0 || given_amount <= 0)
            printf("Amount Should be greater then Zero\n:");
    }
    while(given_amount <= 0);

    // Given amount is convert to cents
    cent = (int) round(given_amount * 100);

    // Quarters
    quarter_count = cent / QUARTER;
    leftover = cent % QUARTER;
    
    // Dimes
    dime_count = leftover / DIME;
    leftover = leftover % DIME;
    
    // Nickels
    nickel_count = leftover / NICKEL;
    leftover = leftover % NICKEL;
    
    // Leftover at this stage is pennies
    coin_count = quarter_count + dime_count + nickel_count + leftover;
    
   
    // Prints out total coins count
    printf("%d\n", coin_count);
    
    return 0;
}
