/**************************************************************************
*  initials.c
*
*  Divine Attipoe
*  divineattipoe@gmail.com
*
*  Prompts a user for their name and prints out their initials with no space
*****************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // it sets the initial lenght of the string to 0
    int input_length = 0;   
     
    // prompt for user's name and uses strlen to get the length of the name
    string name = GetString();
    input_length = strlen(name);
    
    // capitalizes and prints the first letter of the name 
    printf("%c", toupper(name[0]));
    
    
    if (name != NULL)
    {
        // ignores the space and moves to the next name
        for(int i = 0; i < input_length; i++)
        { 
            if (name[i - 1] == ' ') 
            {
                printf("%c", toupper(name[i]));
		    }
	    }
       
           
    }
    printf("\n");
}
