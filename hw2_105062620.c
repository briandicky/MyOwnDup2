/*
 * Author: Wen Chih Lo
 * Date: 2016.9.22
 * Purpose:
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define __DEBUG__ 666

#ifdef __DEBUG__
#define debug_printINT(x) printf("%s = %d\n", #x, (x)); 
#define debug_printSTR(x) printf("%s\n", #x);
#else
#define debug_printINT(x)
#define debug_printSTR(x)
#endif

int dup2_l( int oldfd, int newfd );

int main(void) {
    int fd1, fd2, retn;
    char *str1 = "This is output from fd1.\n";
    char *str2 = "This is output from fd2.\n";

    fd1 = open("4test.txt", (O_RDWR|O_CREAT), 0644);
    
    fd2 = -1;
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
        fprintf(stderr, "retn = -1\n");
    
    if( write(fd1, str1, strlen(str1)) == -1 )
        fprintf(stderr, "Invalid write.\n");

    if( write(fd2, str2, strlen(str2)) == -1 )
        fprintf(stderr, "Invalid write.\n");

    return 0;
}

int dup2_l( int oldfd, int newfd ) {

    int fd[256];
    int i;
    memset(fd, 0, sizeof(fd));

    /* If the file descriptor is overflow, then return -1.*/
    if( newfd >= 256 || newfd < 0 )
        return -1;

    /* If the oldfd is invalid, then print the error message and return -1.
     * Do not use the read() or write() function, because they may change the files.*/
    if( lseek(oldfd, 0, SEEK_CUR) == -1 && errno == EBADF ) {
        fprintf(stderr, "Invalid file descriptor %d.\n", oldfd);
        return -1;
    }

    /*If newfd is equal to oldfd, then just return the newfd.*/
    if( newfd == oldfd )
        return newfd;

    /* Whether newfd is null or not, just close it at first.*/
    close(newfd);

    /* Try to find the target file descriptor*/
    for( i = 0 ; i < 256 ; i++) {
        if( ( fd[i] = dup(oldfd) ) < 0 ) {
            printf( "dup: %s\n", strerror(errno) );

            while( --i > 0 )
                close(fd[i]);

            return -1;
        }

        if( fd[i] == newfd )
            break;
    }

    /* Close all the useless and redundant file descriptors.*/
    while( --i >= 0 )
        close(fd[i]);
    
    return newfd;
}
