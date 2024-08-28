#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


#define MIX_SIZE(a)    (a>1024?1024 : a)

int main(int argc ,char *argv[])
{
    int fd;
    FILE *p_file;
    ssize_t write_len;
    ssize_t read_len;
    unsigned char read_buff[1024];

    fd = open("/dev/linux_hello_drv",O_RDWR | O_SYNC);
    if(fd < 0)
    {
        fprintf(stderr,"Error open vangogh device: %s\n", strerror(errno));
		return -1; 

    }
    if(argc == 1)
    {
       write_len = write(fd,argv,strlen(argv[0]));
       if(write_len < 0 )
       {
            printf(" write error \n");

            return -1;
       }

    }
    if(argc == 2 )
    {
        write_len = write(fd , argv[1],strlen(argv[1]));
        if(write_len < 0)
        {
            printf("write error 2 \n");
            return -1;

        }

    }
    if(argc == 0)
    {
        read_len = read(fd , read_buff,MIX_SIZE(10));
        if(read_len < 0)
        {
            printf("read error \n");
            return -1;

        }
    }
    




    return 0;
}
