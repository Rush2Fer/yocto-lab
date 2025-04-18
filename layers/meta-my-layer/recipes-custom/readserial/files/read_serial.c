#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main() {
    int fd;
    struct termios tty;

    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    tcgetattr(fd, &tty);

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag = IGNPAR | ICRNL; 

    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 0;

    tcsetattr(fd, TCSANOW, &tty);

    FILE *fp = fdopen(fd, "r");
    if (!fp) {
        perror("fdopen");
        close(fd);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf(">> %s", line); 
    }

    fclose(fp);
    return 0;
}