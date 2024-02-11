#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

// Global variables
int list[MAX], n, c; // list array represents the status of processes, n is the number of processes, c is the coordinator

// Function to display the processes, their statuses, and the current coordinator
void display()
{
    int i;
    printf("\nProcesses-->");
    for (i = 1; i <= n; i++)
        printf("\t %d", i);
    printf("\nAlive-->");
    for (i = 1; i <= n; i++)
        printf("\t %d", list[i]);
    printf("\nCoordinator is::%d", c);
}

// Function to implement the Bully algorithm
void bully()
{
    int ch, crash, activate, i, gid, flag, subcdr;

    do
    {
        printf("\n1.Crash\n2.Activate\n3.Display\n4.Exit\nEnter Your choice::");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            // Crash a process
            printf("\nEnter Process no. to Crash::");
            scanf("%d", &crash);

            if (list[crash])
                list[crash] = 0; // Mark the process as crashed
            else
            {
                printf("\nProcess is already dead!!");
                break;
            }

            // Election process after a crash
            do
            {
                printf("\nEnter election generator id::");
                scanf("%d", &gid);

                if (gid == c)
                {
                    printf("\nEnter a valid generator id::");
                }
            } while (gid == crash);

            flag = 0;

            if (crash == c)
            {
                // If the crashed process was the coordinator
                for (i = gid + 1; i <= n; i++)
                {
                    printf("\nMessage is sent from %d to %d", gid, i);

                    if (list[i])
                    {
                        subcdr = i;
                        printf("\nResponse is sent from %d to %d", i, gid);
                        flag = 1;
                    }
                }

                if (flag == 1)
                {
                    c = subcdr; // Set the new coordinator
                }
                else
                {
                    c = gid; // Set the new coordinator
                }
            }

            display();
            break;

        case 2:
            // Activate a process
            printf("\nEnter Process no. to Activate::");
            scanf("%d", &activate);

            if (!list[activate])
                list[activate] = 1; // Mark the process as alive
            else
            {
                printf("\nProcess is already alive!!");
                break;
            }

            // Election process after an activation
            if (activate == n)
            {
                c = n; // If the activated process was the last one, set it as the coordinator
                break;
            }

            for (i = activate + 1; i <= n; i++)
            {
                printf("\nMessage is sent from %d to %d", activate, i);

                if (list[i])
                {
                    subcdr = i;
                    printf("\nResponse is sent from %d to %d", i, activate);
                    flag = 1;
                }
            }

            if (flag == 1)
            {
                c = subcdr; // Set the new coordinator
            }
            else
            {
                c = activate; // Set the new coordinator
            }

            display();
            break;

        case 3:
            display(); // Display the processes and coordinator
            break;

        case 4:
            break; // Exit the loop

        }
    } while (ch != 4);
}

int main()
{
    int i;

    printf("\nEnter no. of processes::");
    scanf("%d", &n);

    // Initialize processes and set the initial coordinator
    for (i = 1; i <= n; i++)
    {
        printf("\nEnter Process %d is Alive or not(0/1)::", i);
        scanf("%d", &list[i]);

        if (list[i])
            c = i; // Set the initial coordinator to the first alive process
    }

    display(); // Display the initial state

    bully(); // Run the Bully algorithm

    return 0;
}
