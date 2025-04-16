#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]){
    if(argc != 3){
        printf("Usage: %s <dev> <on | off>\r\n",argv[0]);
        return -1;
    }

    int fd;
    unsigned int status;

    fd = open(argv[1],O_RDWR);
    if(fd == -1){
        printf("Usage: %s <dev> <on | off>\r\n",argv[1]);
        return -1;
    }
    if(strcmp(argv[2],"on") == 0){
        status = 0;
        write(fd,&status,sizeof(status));
    }else{
        status = 1;
        write(fd,&status,sizeof(status));
    }
    close(fd);
    return 0;
}