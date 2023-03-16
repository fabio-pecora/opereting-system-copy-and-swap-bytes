// open function and flag definitions
#include <fcntl.h>
// print functions and std{in,out,err}
#include <stdio.h>
// create file mode definitions
#include <sys/stat.h>
// read, write, and close functions
#include <unistd.h>

void print_usage(char *program_name);

int main(int argc, char **argv) {
  if(argc < 3) {
    // Insufficient arguments
    print_usage(argv[0]);
    return -1;
  }
  int fd_src = open(argv[1], O_RDONLY);
  if(fd_src == -1) {
    // Failed to open source file
    perror("open SOURCE");
    print_usage(argv[0]);
    return -1;
  }
  // Truncate or create destination with permissions 644
  int fd_dst = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  if(fd_dst == -1) {
    // Failed to open/create destination file
    perror("open DEST");
    print_usage(argv[0]);
    return -1;
  }

  char buf[2];
  ssize_t nr;
  
  // we want the each pair of bytes swapped so I am reading two bytes from the source file at a time, untill there is no more data to read 
  while((nr = read(fd_src, buf, 2)) > 0) {
    // here I am swapping the first and second byte in the buffer
    char temporary = buf[0];
    buf[0] = buf[1];
    buf[1] = temporary;

    // after dwapping I am writing the swapped bytes to the destination file
    if(write(fd_dst, buf, 2) != 2) {
      // if there is an error writing in the destination file then print this error
      perror("write DEST");
      break;
    }
  }
  // If there was an error reading from the source file, print an error message
  if(nr == -1) {
    perror("read SOURCE");
  }


  }
  if(nr == -1) {
    perror("read SOURCE");
  }

  if(nr == -1) {
    perror("read SOURCE");
  }
  if(close(fd_src) == -1) {
    perror("close SOURCE");
  }
  if(close(fd_dst) == -1) {
    perror("close DEST");
  }
  return 0;
}

void print_usage(char *program_name) {
    fprintf(stderr, "usage: %s SOURCE DEST\n", program_name);
}