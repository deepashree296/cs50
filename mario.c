#include <stdio.h>
#include <cs50.h>

void print_spaces(int n);
void print_hash(int n);

int main(void)
{
    int height = 0;
    int row_number = 1;
    bool is_valid = false;

    // prompt and validate user input
    do
    {
        printf("Height: ");
        height = get_int();
        if (height >= 0 && height <= 23)
        {
            is_valid = true;
        }
        else
        {
            is_valid = false;
        }
    }
    while (!is_valid);

    // draw the half pyramid

// checking base condition
    if (height == 0)
    {
        printf("");
    }
    else
    {
        while   (row_number <= height)
        {
            // calling print_spaces and print_hash depending on row
            print_spaces(height - row_number);
            print_hash(row_number + 1);
            printf("\n");
            row_number++;
        }
    }


}

// prints n number of spaces
void print_spaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// prints n number of hashes
void print_hash(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

