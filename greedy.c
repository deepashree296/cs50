#include <stdio.h>
#include <cs50.h>
#include <math.h>

int no_of_coins(int den, int tot);

int main(void)
{

    int coin;
    int count;
    int rem;
    double change;

    do
    {
        printf("O hai! How much change is owed?");
        change = get_double();
    }
    while (!(change >= 0.00));

// convert to cents
    double cents = 100 * change;
    int cent = (int)round(cents);

// minimum no of quarter

    coin = no_of_coins(25, cent);
    count = coin;
    rem = cent - (coin * 25);

// minimum no of dime
    coin = no_of_coins(10, rem);
    count = count + coin;
    rem = rem - (coin * 10);

// minimum no of nickel
    coin = no_of_coins(5, rem);
    count = count + coin;
    rem = rem - (coin * 5);

// minimum no of penny
    count = count + rem;

    printf("%d\n", count);
}
// calculate no of coins of a particular denomination

int no_of_coins(int denomination, int total)
{
    int no_of_coin = total / denomination;
    return no_of_coin;
}
