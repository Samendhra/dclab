#include "21z342_add.h"
void add_prog_1(char *host, int x, int y) 
{
    CLIENT *clnt;
    int *result_1;
    numbers add_1_arg;

    // Create a client handle for the ADD_PROG program with ADD_VERS version using UDP
    clnt = clnt_create(host, ADD_PROG, ADD_VERS, "udp");

    // Check if client creation was successful
    if (clnt == NULL) 
    {
        clnt_pcreateerror(host); // Print error message if client creation fails
        exit(1);
    }

    // Set the values of the numbers structure
    add_1_arg.a = x;
    add_1_arg.b = y;

    // Make the remote procedure call to the "add" function in the server
    result_1 = add_1(&add_1_arg, clnt);

    // Check if the remote procedure call was successful
    if (result_1 == (int *)NULL) 
    {
        clnt_perror(clnt, "call failed"); // Print error message if the call fails
    } 
    else 
    {
        // Print the result obtained from the remote procedure call
        printf("Result: %d\n", *result_1);
    }

    // Destroy the client handle
    clnt_destroy(clnt);
}

int main(int argc, char *argv[]) 
{
    char *host;

    // Check if the correct number of command line arguments is provided
    if (argc < 4) 
    {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }

    // Extract the server host from the command line arguments
    host = argv[1];

    // Call the add_prog_1 function with the server host and two integer values
    add_prog_1(host, atoi(argv[2]), atoi(argv[3]));

    // Exit the program
    exit(0);
}
