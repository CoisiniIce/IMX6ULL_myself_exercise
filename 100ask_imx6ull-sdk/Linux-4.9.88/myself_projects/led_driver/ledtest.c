#include <stdio.h>

int main(int argc,char *argv[]){
    if(argc != 3){
        printf("Usage: %s <dev> <on | off>\r\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd;
    char status;

    fd = open(argv[1],O_RDWR);
    if(fd == -1){
        perror("Can't open file %s\r\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    if(strcmp(argv[2],"on") == 0){
        status = 1;
        write(fd,&status,1);
    }else{
        status = 0;
        write(fd,&status,1);
    }
    close(fd);
    return 0;
}