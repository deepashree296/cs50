// Helper functions for music

#include <cs50.h>

#include "helpers.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int read_letter(string note);
int read_octave(int value);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
        return (8 / atoi(&fraction[2])) * atoi(&fraction[0]) ;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int no_of_semitones = 0;
    no_of_semitones = read_letter(note);

    // read second character to check if it is numeric
    if( isdigit(note[1]) )
    {
        no_of_semitones = no_of_semitones + read_octave(atoi(&note[1]));
    }
    else
    {
        if( note[1] == '#' )
        {
            no_of_semitones = no_of_semitones + 1;
        }
        else if( note[1] == 'b')
        {
            no_of_semitones = no_of_semitones - 1;
        }
        no_of_semitones = no_of_semitones + read_octave(atoi(&note[2]));
    }

    // calculate frequency

    double freq = (pow(2, (double)no_of_semitones / 12)) * 440;
    return roundl(freq);

}

int read_letter(string note)
{
    int n ;
    switch ( note[0] )
    {
        case 'A':
        n = 0;
        break;
        case 'B':
        n = 2;
        break;
        case 'C':
        n = -9;
        break;
        case 'D':
        n = -7;
        break;
        case 'E':
        n = -5;
        break;
        case 'F':
        n = -4;
        break;
        case 'G':
        n = -2;
        break;
        default:
        n = 0;
    }
     return n;
}

int read_octave(int octave)
{

    int n = 0;
    int diff = octave - 4;
    n =  diff * 12 ;
    return n;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO

    if (s != NULL && strcmp(s, "") == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
