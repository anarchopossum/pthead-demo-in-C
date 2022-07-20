#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/*
 * For the child function, I didn't do any drastic changes except making it into an infinite Loop.
 *
 * 2. Explain why the sleeping thread can print its periodic messages while
 * the main thread is waiting for keyboard input.
 * ANS:
 * This is basically a thread that is working by itself doing a certain task,
 * we create a thread and that can have its own function to work on
 * simultaneously with other threads doing their tasks under the same process.
 */
_Noreturn static void *child(void *ignored) {
    while (1 != 0) { // Here is the added infinite loop
        sleep(3); // The program halts for 3 seconds
        printf("Child is done sleeping 3 seconds.\n");
    }
    //return NULL;
}


int main(int argc, char *argv[]) {
    pthread_t child_thread, parent_thread; // Declare both child and parent thread.
    int code;
    code = pthread_create(&child_thread, NULL, child, NULL); // creates a child thread and assigns it to 'code'.
    printf("\nPress enter to kill process.\n");
    char ch = getchar(); // gets the user Input for the If command to operate


    /*
     * Here we made an infinite while loop. this keeps generating the parent_thread and is waiting for the user to
     * Hit the enter Key. Once the user hits the enter key the process will wait 5 seconds until the thread gets killed
     * from there a message to the user saying that the thread was terminated.
     *
     * 1. Explain what `pthread` is doing in this program. Be specific.
     * ANS:
     * Pthread is allowing the possibility to multithreading (or multitask operations). this program is simple as in
     * reality these threads are not doing much. But if this program was a desktop client for a messaging service,
     * We can have a thread that fetches incoming messages, that may also start another threaded process to notify the
     * user with an icon and audio tone. But in this case we are just placing the thread to sleep and printing a message
     * from one end, and waiting input on the main function to finally complete the programs intention. threads work
     * under a process, one thread gets killed, the whole process dies.
     */
    while (1 != 0) {
        pthread_create(&parent_thread, NULL, child, NULL); // creates the parent thread
        if (ch == '\n') { // this looks for the users input to equal the 'enterKey'.
            sleep(5);  // Parent goes to Sleep.
            printf("Parent is done sleeping 5 seconds.\n");
            pthread_cancel(parent_thread);  // Kills the parent Thread
            printf("Parent Thread Killed :(");
            break;
        }
    }


    if (code) {
        fprintf(stderr, "pthread_create failed with code %d\n", code);
    }
    //sleep(5);
    //printf("Parent is done sleeping 5 seconds.\n");
    return 0;
    // test
}
