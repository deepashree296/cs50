#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// program that implements vigenere cipher

int returnCipherIndex(int index, int key);

int main(int argc, string argv[])
{
    int k = 0;
    // accept command line arguments - all aphabetical
    if (argc == 2 )
    {
        // iterate over key elements
        while (k < strlen(argv[1]))
        {
            if ( isalpha(argv[1][k]) )
            {
                k++;
            }
            else
            {
                printf("Usage: ./caesar k(alphabets)");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar k(alphabets)");
        return 1;
    }

    // input string
    printf("plaintext: ");
    string plaintext = get_string();
    printf("ciphertext: ");

    // encipher
    // c =  ( p + k ) mod 26
    int plainIndex;
    int cipherIndex;
    //int key = atoi(argv[1]);

    // convert key alphabets to index
    string original_key = argv[1];
    int length_key = strlen( original_key );
    int key[length_key];

    for (int j = 0; j < length_key; j++ )
    {
        if ( islower(original_key[j]) )
        {
            key[j] = original_key[j] - 'a' ;
        }
        else if ( isupper(original_key[j]) )
        {
            key[j] = original_key[j] - 'A' ;
        }
    }


    // convert plaintext to ciphertext

    int j = -1;
    int length = strlen(plaintext);
    char cipherValue[length];

    for (int i = 0; i < length; i++ )
    {
        cipherValue[i] = plaintext[i];
    }


    for ( int i = 0; i < length; i++ )
    {

        // checking if letter is an alphabet
        if ( isalpha( plaintext[i]) )
        {
            j++;
            // preserve case of letters while calculating ciphervalue
            if ( islower( plaintext[i] ) )
            {
                if ( j == length_key )
                {
                    j = 0;
                }
                plainIndex = plaintext[i] - 'a';
                cipherIndex = returnCipherIndex(plainIndex, key[j]);
                cipherValue[i] = cipherIndex + 'a';

            }
            else if ( isupper( plaintext[i] ) )
            {
                if ( j == length_key )
                {
                    j = 0;
                }
                plainIndex = plaintext[i] - 'A';
                cipherIndex = returnCipherIndex(plainIndex, key[j]);
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






