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

    sort(values, n);

    for (int i=0; i<n; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int start = 0;
    while (start < n - 1)
    {
        for (int i=0; i < n-1; i ++)
        {
            int left = values[i];
            int right = values[i + 1];
            if (left > right)
            {
                values[i] = right;
                values[i+1] = left;
            }
            
        }
        start ++;
    }
}
