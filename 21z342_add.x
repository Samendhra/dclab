/* Define a structure named 'numbers' with two integer members 'a' and 'b' */
struct numbers
{
    int a;
    int b;
};

/* Define an RPC program named 'ADD_PROG' with program number 0x4562877 */
program ADD_PROG
{
    /* Define a version named 'ADD_VERS' with version number 1 */
    version ADD_VERS
    {
        /* Define an RPC procedure named 'add' with procedure number 1 */
        int add(numbers) = 1;
    } = 1; /* End of version definition with version number 1 */
} = 0x4562877; /* End of program definition with program number 0x4562877 */

/*  sudo apt-get install rpcbind
    rpcinfo
    rpcgen  -a  -C add.x
    make  -f  Makefile.add
*/
