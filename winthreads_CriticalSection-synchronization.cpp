//https://www.codeproject.com/Articles/438/Introduction-to-Multi-threaded-Code
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <time.h>


CRITICAL_SECTION cs;
int a[ 5 ];

void Thread( void* pParams )
{

    srand (time(NULL));
    while ( TRUE )
    {
        printf("Update variable with random numbers :: ");
        EnterCriticalSection( &cs );
        a[0] = rand() % 100 + 1;
        a[1] = rand() % 100 + 1;
        a[2] = rand() % 100 + 1;
        a[3] = rand() % 100 + 1;
        a[4] = rand() % 100 + 1;
        printf("a[0]=%d;a[1]=%d;a[2]=%d;a[3]=%d;a[4]=%d \n",a[0],a[1],a[2],a[3],a[4]);
        LeaveCriticalSection( &cs );
        Sleep(1000);
    }
}

int main( void )
{
    InitializeCriticalSection( &cs );
    _beginthread( Thread, 0, NULL );

    while( TRUE )
    {
        printf("!!!!!\nRead variable \n");
        EnterCriticalSection( &cs );
        printf("a[0]=%d;a[1]=%d;a[2]=%d;a[3]=%d;a[4]=%d \n",a[0],a[1],a[2],a[3],a[4]);
        LeaveCriticalSection( &cs );
        printf("!!!!! \n");
        Sleep(3000);
    }
    return 0;
}

