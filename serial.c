#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <linux/ip.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/stat.h>
#include <time.h>
#include <assert.h>
#include <fcntl.h>
 
#define BAUDRATE B38400
#define SERIALDEVICE "/dev/ttyS0"
unsigned char buf[255];

int main(void){
    int fd, res, k;
    struct termios oldtio, newtio;

    bzero(&buf, sizeof(buf));    
    fd = open(SERIALDEVICE, O_RDWR | O_NOCTTY, O_NONBLOCK);
    if(fd<0){
        perror(SERIALDEVICE);
        exit(-1);
    }    
    tcgetattr(fd, &oldtio); 

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR | ICRNL;
 
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);
    fflush(stdin);
    fflush(stdout);
     
    for(k=0; k<255; k++){
        buf[k] = 0x00;
    }
    tcflush(fd, TCIFLUSH);
    tcflush(fd, TCIFLUSH);
    tcflush(fd, TCIFLUSH);
         
    while(1)
    {
    fflush(stdin);
        fflush(stdout);
        res = read(fd, buf, 255);
    for (k=0 ; k<res; k++){
        printf("%X\t", buf[k]);   
    }        
    } //while end
    tcsetattr(fd,TCSANOW, &oldtio);    
    return 0;
}