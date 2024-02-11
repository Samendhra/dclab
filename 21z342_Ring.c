#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
    int msg[20], k, i;
    int ch, crash, activate, gid, flag, subcdr;

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
                do {
                    printf("\nEnter election generator id::");
                    scanf("%d", &gid);
                    if (gid == c) {
                        printf("\nEnter a valid generator id::");
                    }
                } while (gid == crash);

                flag = 0;
                k = 1;

                if (crash == c) {
                    msg[k++] = gid;
                    for (i = (gid + 1) % n; i != gid; i = (i + 1) % n) {
                        if (list[i]) {
                            printf("\nMessage is sent to %d k = %d", i, k);
                            msg[k++] = i;
                        }
                    }

                    subcdr = 0;
                    for (i = 1; i < k; i++) {
                        printf("\nMessage::%d\n", msg[i]);
                        if (subcdr < msg[i]) {
                            subcdr = msg[i];
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
