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
  while(true) { // loop until the end of the input file
    bytesRead = read(fd_src, buffer, sizeof(buffer)); // read up to 2 bytes into the buffer    
    if(bytesRead == 0) break; // if no bytes read then break
    size_t bytesWritten = 0; // define a variable to store the number of bytes written   
    while(bytesWritten < bytesRead) { // looping untill all bytes are written     
        // Swap each pair of bytes in the buffer
        buf[0] = buffer[1]; 
        buf[1] = buffer[0]; 
        bytesWritten += write(fd_dst, buf, sizeof(buf)); // write the swapped bytes to the destination file
        buffer += sizeof(buf); // move the buffer pointer to the next pair of bytes
    }   
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
