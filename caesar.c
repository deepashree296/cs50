#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/* get key in argument
convert to int
get input from user
convert input to ciphertext
iterate over all the characters of plaintext
check if it is alphabetical
check if it is lower
convert to index - pass 'char' - 'a'
if upper - pass char - A for index
p - k mod 26 -> this will give new index
convert index to ascii -> index + a or index + A */

int returnCipherIndex(int index, int key);

int main(int argc, string argv[])
{
    // condition to handle number of arguments
    if ( argc != 2 )
    {
        printf("Usage: ./caesar k");
        return 1;
    }
    // get user string
    printf("plaintext: ");
    string plaintext = get_string();
    printf("ciphertext: ");

    int key = atoi(argv[1]);
    int plainIndex;
    int cipherIndex;
    int length = strlen(plaintext);
    char cipherValue[length];

    for (int i = 0; i < length; i++ )
    {
        cipherValue[i] = plaintext[i];
    }

    // convert plaintext to ciphertext

    for ( int i = 0; i < length; i++ )
    {

        // checking if letter is an alphabet
        if ( isalpha( plaintext[i]) )
        {
            // preserve case of letters while calculating ciphervalue
            if ( islower( plaintext[i] ) )
            {
                plainIndex = plaintext[i] - 'a';
                cipherIndex = returnCipherIndex(plainIndex, key);
                cipherValue[i] = cipherIndex + 'a';

            }
            else if ( isupper( plaintext[i] ) )
            {
                plainIndex = plaintext[i] - 'A';
                cipherIndex = returnCipherIndex(plainIndex, key);
                cipherValue[i] = cipherIndex + 'A';
            }

        }
        printf("%c", cipherValue[i]);
    }

    printf("\n");

}

/*
method which returns alphabetical index of cipher character
*/
int returnCipherIndex(int index, int key)
{
    int cipherIndex = index + key;

// checking overflow of cipher index
    if ( cipherIndex > 26 )
    {
        cipherIndex = cipherIndex % 26;
    }

    return cipherIndex;
}


