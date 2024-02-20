#include <stdio.h>

// Global variables
int global_var = 10;

// Function declarations
void greet();
int add(int a, int b);

int main()
{
int result;

// Calling the greet function
greet();

// Using the add function
result = add(5, 7);
printf("Result of addition: %d\n", result);

return 0;
}

// Function definitions
void greet()
{
int banana;

printf("Hello, welcome to the C program!\n");
}

int add(int a, int b)
{
// adding the two int s
return a + b;
}
