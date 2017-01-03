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
    
    for (int k=0; k<n; k++)
    {
        printf("%d\n", values[k]);
    }
    
    int min = 0;
    int max = n - 1;
    
    printf("Initial min: %d\n", min);
    printf("Initial max: %d\n", max);
    
    while (max - 1 > min)
    {
        int guess = (max + min) / 2;
        printf("Guess index is now: %d\n", guess);
        if (values[guess] == value)
        {
            printf("FOUND IT!\n");
            return true;
        }
        else if (values[guess] < value)
        {
            printf("Guess value %d was less than %d\n", values[guess], value);
            min = guess ++;
            printf("New Min index: %d\n", min);
            printf("Max stays at index %d\n", max);
        }
        else if (values[guess] > value)
        {
            printf("Guess value %d was greater than %d\n", values[guess], value);
            max = guess --;
            printf("New Max index: %d\n", max);
            printf("Min stays at index %d\n", min);
        }
    }
    printf("COULD NOT FIND IT!\n");
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
