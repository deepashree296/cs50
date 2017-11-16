#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // get name as input from user
    string name = get_string();

    // check if user input something
    if ( name != NULL )

    {
        printf( "%c", toupper( name[0]) );
        int i = 1;
        // to check end of string
        while ( name[i] != '\0' )
        {
            // to check end of one name in the string
            if ( name[i] == ' ')
            {
                i++;
                printf( "%c", toupper( name[i]) );
            }
            else
            {
                i++;
            }
        }
        printf( "\n" );

    }
}