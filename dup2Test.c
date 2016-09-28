/*
 * Author: Wen Chih Lo, NMSL
 * Date: 2016.9.27
 * Purpose: Try to test the my own dup2 function.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "hw2.h"

#define __DEBUG__ 666

#ifdef __DEBUG__
#define debug_printINT(x) printf("%s = %d\n", #x, (x)); 
#define debug_printSTR(x) printf("%s\n", #x);
#else
#define debug_printINT(x)
#define debug_printSTR(x)
#endif

int main(void) {
    int fd1, fd2, retn;
    char *str1 = "This is output from fd1.\n";
    char *str2 = "This is output from fd2.\n";

    fd1 = open("4test.txt", (O_RDWR|O_CREAT), 0644);
    
    fd2 = -666;
    debug_printSTR("Before dup2,");
    debug_printINT(fd1);
    debug_printINT(fd2);

    debug_printSTR("-------------------");

    fd2 = 87;
    retn = dup2_l(fd1, fd2);
    if( retn != -1 ) {
        debug_printSTR("After dup2,");
        debug_printINT(fd1);
        debug_printINT(fd2);
        debug_printINT(retn);
    }
    else
        fprintf(stderr, "Dup2 function failed, and retn = -1\n");
    
    if( write(fd1, str1, strlen(str1)) == -1 )
        fprintf(stderr, "Write failed.\n");

    if( write(fd2, str2, strlen(str2)) == -1 )
        fprintf(stderr, "Write failed.\n");

    return 0;
}
