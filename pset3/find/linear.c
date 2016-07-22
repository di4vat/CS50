/**
*  linear.c
*
*  A linear search program for sorting 
*  my first implementation of search in pset3( in file helpers.c)
*/


bool search(int value, int values[], int n)
{   // TODO: implemets a linear searching algorithm
    if (n <= 0)
    {
        return false;
    }
    
    for (int i = 0; i < n; i++)
    {
        if (value == values[i])
            {
                return true;
            }
        
    }    
    return false;
}
