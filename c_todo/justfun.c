// C++ program to illustrate Pointer Arithmetic 
// in C/C++ 
#include <stdio.h> 

// Driver program 
int main() 
{ 
	// Declare an array 
	int v[3][4] = {{100, 100, 200,300},{500,600,700,800},{900,1000,1100,1200}}; 

	// Declare pointer variable 
	int *ptr; 

	// Assign the address of v[0] to ptr 
	ptr = v; 

	for (int i = 0; i < 3; i++) 
	{ 
		for(int j=0;j<4;j++){
		printf("Value of *ptr = %d\n", *(ptr+i*j*4)); 
		//printf("Value of ptr = %p\n\n", ptr); 

		// Increment pointer ptr by 1 
		//ptr++; 
		}
	} 
} 

/**
 * C program to access two dimensional array using pointer.
 */
/*
#include <stdio.h>

#define ROWS 3
#define COLS 3

// Function declaration to input and print two dimensional array 
void inputMatrix(int matrix[][COLS], int rows, int cols);
void printMatrix(int matrix[][COLS], int rows, int cols);



int main()
{
    int matrix[ROWS][COLS];
    int i, j;

    // Input elements in matrix 
    printf("Enter elements in %dx%d matrix.\n", ROWS, COLS);
    inputMatrix(matrix, ROWS, COLS);


    // Print elements in matrix 
    printf("Elements of %dx%d matrix.\n", ROWS, COLS);
    printMatrix(matrix, ROWS, COLS);


    return 0;
}




//
 * Function to take input in two dimensional array (matrix)
 * from user.
 *
 * @matrix  2D array to store input.
 * @rows    Total rows in 2D matrix.
 * @cols    Total columns in 2D matrix.
 *
void inputMatrix(int matrix[][COLS], int rows, int cols)
{
    int i, j;


    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            // (*(matrix + i) + j is equivalent to &matrix[i][j]
            scanf("%d", (*(matrix + i) + j));
        }
    }
}




 * Function to display elements of two dimensional array (matrix)
 * on console.
 *
 * @matrix  2D array to display as output.
 * @rows    Total rows in 2D matrix.
 * @cols    Total columns in 2D matrix.
 
void printMatrix(int (*matrix)[COLS], int rows, int cols)
{
    int i, j;


    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            // *(*(matrix + i) + j) is equivalent to matrix[i][j]
            printf("%d ", *(*(matrix + i) + j));
        }

        printf("\n");
    }
}
*/
