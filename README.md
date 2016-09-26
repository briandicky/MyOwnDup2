#MyOwnDup2
This is a implement of my own dup2 function that behaves the same way as the dup2 function.
- Dup2 can duplicate the descriptor correctly.
- Copy the file descriptor oldfd and use the newfd as the target fd.
- After calling dup2 function, the oldfd and the newfd point to the same file.
- If oldfd equals to newfd, dup2 will return the newfd.
- If newfd is an opened file descriptor, it will close the newfd first.
- The return file descriptor is the new newfd that points to the file table of oldfd.
- If newfd is not closed, it will close the newfd before you copy the fds.
- This dup2 will handle invalid file descriptors and others error status. 
And this program is compiled and run on Ubuntu 16.04 LTS.

##How to compile & run this program
This program is written in Linux environment, GUN make, and GCC(Gnu compiler collection.)
Just type the commands (in BASH shell),
```
make help
```

or

```
make clean dep all
```
It will automatically compile all the necessary files/codes, then generate the execution file.
Then type this,
```
./EXENAME
```

In the end, it will work successfully.

###2016 Advance UNIX Programmin HW2
