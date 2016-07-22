/***********************************************
*  vigenere.c
*
*  Divine Attipoe
*  divineattipoe@gmail.com
*
*  A solution to the vigenere cipher in pset 2
************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
  
int main(int argc, string argv[])
{
    string key_word = argv[1];
    bool valid_key = false;
    string message = "";
    int key_length = 0;
    int key_code;
   
    // used to check the command line argument and key validity
    do
    {
        if (argc != 2)
        {
            printf("Please check your input and re-run the program.\n");
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
        // to check if keyword is a string. remember isalpha = isupper + islower
        for (int i = 0, key_length = strlen(key_word); i < key_length; i++) 
        {
            if (!isalpha(argv[1][i]))
            {
                printf("A string is required as a keyword.\n");
                printf("Usage: ./vigenere becon\n");
                return 1;
             // for ( int i =0, key_lenght = strlen(key_word); i < key_lenght
             }
             
             else
                valid_key = true;
         }
         
     }while (!valid_key);
          
    // gets message at prompt and checks length of keyword
    message = GetString();
    key_length = strlen(key_word);
    
    /**
    * encryption begins here
    * it iterate through message and creats an array of both message and keyword
    * a reset is set in place for shorter keyword against message and  proceed
    * to encrypt the message, printing characters  whiles ignoring
    * non-alphabetical characters
    **/
    
    for(int i = 0, j = 0, message_len = strlen(message); i < message_len; i++, j++)
    {
    // resets key if shorter than message
        if (j >= strlen(key_word))
        {
            j = 0;
        }
        // creats an array of the keyword
        key_code = key_word[j];
        
        // skip keyword's[j] if message's[i] is not a letter.
        // Remember isalpha = islower and isupper
        if (!isalpha(message[i]))
        {
            j = (j - 1);
        } 
        
        // makes A = 0, Z = 25 for the uppercase letters 
        if ((key_code >= 'A') && (key_code <= 'Z'))
        {
            key_code = (key_code - 'A');
        }
 
        // makes a = 0, z = 25 for the lowercase letters
        if ((key_code >= 'a') && (key_code <= 'z'))
        {
            key_code = (key_code - 'a');
        }
        /* creats an error of encrypting each character thrice
         if(isalpha(message[i]))
         {
           printf("%c", (message[i] + key_code));
         }
        */
            // works on lower case letters
        if (islower(message[i]))
        {
            printf("%c", ((((message[i] - 'a') + key_code) % 26) + 'a'));
        }
            // works on upper case letters
        else if (isupper(message[i]))
        {
            printf("%c", ((((message[i] - 'A') + key_code) % 26) + 'A'));
        }
           
        
        else
        {
            printf("%c", message[i]);
            
        }
    }
    printf("\n");
    return 0; 
}
    
    
