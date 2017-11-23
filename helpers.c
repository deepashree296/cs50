/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm: assuming array is sorted in increasing order
    int start_index = 0;
    int end_index = n - 1;
    int middle_index = n / 2;
    int size = n;

    // repeat this till sub array size reduces to zero

    while ( size > 0 )
    {

        if ( value == values[middle_index] )
        {
            return true;
        }
        else if ( value < values[middle_index] )
        {
            // shift end index to middle index decreased by 1
            // calculate new middle_index
            end_index = middle_index - 1;

        }
        else
        {
            // shift start index to middle index increased by 1
            start_index = middle_index + 1;
        }

        // calculate new middle index
        middle_index = ( start_index + end_index ) / 2;
        // calculate size of sub array

        size = ( end_index - start_index ) + 1;
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm : bubble sort, increasing order
    int counter = -1;
    int unsorted_array = n - 1;
    // repeat till there are no swaps
    while ( counter != 0 )
    {
        // reset counter variable before for walking through array starts
        counter = 0;
        unsorted_array = unsorted_array - 1;

        for ( int i = 0; i <= unsorted_array; i++)
        {
            // compare adjacent pairs
            if ( values[i] > values[i + 1] )
            {
                counter++;
                // swap the values
                values[i] = values[i] + values[i + 1];
                values[i + 1] = values[i] - values[i + 1];
                values[i] = values[i] - values[i + 1];
            }

        }

    }

    return;
}
