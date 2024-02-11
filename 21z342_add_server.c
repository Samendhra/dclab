#include "21z342_add.h"

// Implementation of the server-side RPC function add_1
int *add_1_svc(numbers *argp, struct svc_req *rqstp) 
{
    static int result; // Static variable to store the result

    // Print a message indicating that the add function is called with the provided arguments
    printf("add(%d, %d) is called\n", argp->a, argp->b);

    // Calculate the result by adding the two numbers from the 'numbers' structure
    result = argp->a + argp->b;

    // Return a pointer to the static result variable
    return &result;
}
