#include <stdio.h>
#include <cs50.h>

int bottles(int n);

int main(void)
{
    printf("Minutes: ");
    int minutes = get_int();
    printf("Bottles: %d\n", bottles(minutes));

}

int bottles(int n){
    int number_of_bottles = 12 * n;
    return number_of_bottles;
}

