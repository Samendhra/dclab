#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

// Global variables
int list[MAX], n, c;

// Function to display the state of processes and coordinator
void display() {
    int i;
    printf("\nProcesses-->");
    for (i = 1; i <= n; i++)
        printf("\t %d", i);
    printf("\nAlive-->");
    for (i = 1; i <= n; i++)
        printf("\t %d", list[i]);
    printf("\nCoordinator is::%d", c);
}

// Function implementing the Ring algorithm for leader election
void ring() {
    int k, i;
    int ch, crash, activate, gid[MAX], flag, subcdr;

    do {
        printf("\n1.Crash\n2.Activate\n3.Display\n4.Exit\nEnter Your choice::");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                // Crash a process
                printf("\nEnter Process no. to Crash::");
                scanf("%d", &crash);

                if (list[crash])
                    list[crash] = 0;
                else {
                    printf("\nProcess is already dead!!");
                    break;
                }

                // Election process after a crash
                printf("\nEnter number of election generator ids::");
                int num_generators;
                scanf("%d", &num_generators);

                printf("\nEnter election generator ids::");
                for (i = 0; i < num_generators; i++) {
                    scanf("%d", &gid[i]);
                    if (gid[i] == crash) {
                        printf("\nProcess is already dead!!");
                        return;
                    }
                }

                for (i = 0; i < n; i++) {
                    if (i != 0)
                        gid[i] = 0; // Mark other election generator ids as 0
                }

                flag = 0;
                k = 1;

                if (crash == c) {
                    for (i = (gid[0] + 1) % n; i != gid[0]; i = (i + 1) % n) {
                        if (list[i]) {
                            printf("\nMessage is sent to %d ", i);
                        }
                    }

                    subcdr = 0;
                    for (i = 1; i < k; i++) {
                        printf("\nMessage::%d\n", gid[0]);
                        if (subcdr < gid[0]) {
                            subcdr = gid[0];
                        }
                    }
                    c = subcdr;
                }
                display();
                break;

            case 2:
                // Activate a process
                printf("\nEnter Process no. to Activate::");
                scanf("%d", &activate);

                if (!list[activate])
                    list[activate] = 1;
                else {
                    printf("\nProcess is already alive!!");
                    break;
                }

                // Election process after activation
                if (activate == n) {
                    c = n;
                    break;
                }

                for (i = activate + 1; i <= n; i++) {
                    printf("\nMessage is sent from %d to %d", activate, i);
                    if (list[i]) {
                        subcdr = i;
                        printf("\nResponse is sent from %d to %d", i, activate);
                        flag = 1;
                    }
                }

                if (flag == 1) {
                    c = subcdr;
                } else {
                    c = activate;
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

int main() {
    int i;

    printf("\nEnter no. of processes::");
    scanf("%d", &n);

    // Initialize processes
    for (i = 1; i <= n; i++) {
        printf("\nEnter Process %d is Alive or not(0/1)::", i);
        scanf("%d", &list[i]);
        if (list[i])
            c = i; // Set the initial coordinator to the first alive process
    }

    display(); // Display the initial state
    ring(); // Run the Ring algorithm

    return 0;
}
