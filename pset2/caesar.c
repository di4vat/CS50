/********************************************
*  caesar.c
*
*  Divine Attipoe
*  divineattipoe@gmail.com
*
*  A solution to the caesar cipher in pset 2
*********************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
  
int main(int argc, string argv[])
{
    // variable declaration
    string message = "";
    int m_length = 0;
    
    // handles lack of argv[1]
    if (argv[1] == 0)
    {
         printf("Please re-run the program\n");
            return 1;
    }
    
    /* key conversion from a string "string argv[]" to an int
    *  the key is the second command line argument and  atoi does the conversion
    */
    int key = atoi(argv[1]);

    /* if conmmand line argument is not valid the 
     *  user is prompted and the program exits
     *  argc is the number of command line argument
     */
    if (argc != 2)
    {
        printf("Usage: ./caesar 13\n");
        return 1;
    }
        
    // handles lack of argv[1]
    if (argv[1] == 0)
    {
        printf("Please re-run the program\n");
        return 1;
    }
    
        
    if (key <= 0)
    {  
        printf("Please submit a valid encryption key\n");
        printf("Key must be a non-negative integer.\n");
        return 1;
    }
 
   
    // prints a new line and procced to get message 
    message = GetString();
    m_length = strlen(message);
    
    // for iterating through the message
    for(int i = 0; i < m_length; i++)
    {
        // Process characters
        if (isalpha(message[i]))
        {
            // works on lower case letters
            if (islower(message[i]))
            {
                printf("%c", ((((message[i] - 97) + key) % 26) + 97));
            }
            // works on upper case letters
            else
            {
                printf("%c", ((((message[i] - 65) + key) % 26) + 65));
            }
        }
        
        else
        {
            printf("%c", message[i]);
            
        }
       
    }
    printf("\n");
    return 0;    


}


