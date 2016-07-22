/**
*  mario.c
*
*  Divine Attipoe
*  divineattipoe@gmail.com
*
*  A solution to mario pyramid from pset1
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = 0;
    
    /**
    *  asks user for input between 1 and 23 inlusive 
    *  checks if within bounds, if not user is prompted again
    */
    do
    {
        printf("Height: ");
        height = GetInt();
	    
        if (height == 0)
        {
            return 0;
        }
    }
    while (height < 1 || height > 23);

    /**
    *  this function takes care of the height of the pyramid,spaces and hashs
    *  the first function deals with the height of the pyramid 
    *  whiles the inner most functions prints the spaces
    */
    for (int row = 0; row < height; row++) 
    {
        for (int spaces = 0; spaces < height - row - 1; spaces++) 
        {
            printf("%s", " ");
        }
        
        // Print the '#' character
        for (int hash = 0; hash < row + 2; hash++) 
        {
            printf("#");
		}
		 
        printf("\n");
	}	
	
    return 0;
}
