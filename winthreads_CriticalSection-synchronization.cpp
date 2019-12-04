/*
 *   Author:  Michael McGuire
 *  Purpose:  in multi-threaded code their may arise a need to update variables exclusively in one thread while blocking other threads from accessing these variables during the update
 * Language:  c++
 */

// headers
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <time.h>

// global variables
// a Critical Section lock
CRITICAL_SECTION cs;
// the shared object
int a[ 5 ];


// 2nd thread that will access a[] concurrently
void Thread( void* pParams )
{
    // srand randomizes rand, to generate random number based on system clock
    srand (time(NULL));
    // a never ending loop
    while ( TRUE )
    {
        printf("Update variable with random numbers :: ");
        // CRITICAL_SECTION cs lock
        EnterCriticalSection( &cs );
        a[0] = rand() % 100 + 1;
        a[1] = rand() % 100 + 1;
        a[2] = rand() % 100 + 1;
        a[3] = rand() % 100 + 1;
        a[4] = rand() % 100 + 1;
        printf("a[0]=%d;a[1]=%d;a[2]=%d;a[3]=%d;a[4]=%d \n",a[0],a[1],a[2],a[3],a[4]);
        LeaveCriticalSection( &cs );
        // CRITICAL_SECTION cs unlock
        Sleep(1000);
    }
}

int main( void )
{
    // initialize CRITICAL_SECTION lock
    InitializeCriticalSection( &cs );
    // startup 2nd thread
    _beginthread( Thread, 0, NULL );

    // forever running loop
    while( TRUE )
    {
        printf("!!!!!\nRead variable \n");

        // CRITICAL_SECTION cs lock
        EnterCriticalSection( &cs );
        printf("a[0]=%d;a[1]=%d;a[2]=%d;a[3]=%d;a[4]=%d \n",a[0],a[1],a[2],a[3],a[4]);
        LeaveCriticalSection( &cs );
        // CRITICAL_SECTION cs unlock

        printf("!!!!! \n");
        Sleep(3000);
    }

    // exit main
    return 0;
}

