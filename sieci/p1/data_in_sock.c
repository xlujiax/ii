#include "data_in_sock.h"

int data_in_socket(unsigned int sockfd)
{
  fd_set fds;
  struct timeval timeout;
  int rc;

  timeout.tv_sec = 1;
  timeout.tv_usec = 0;

  FD_ZERO(&fds);
  FD_SET(sockfd, &fds);
  rc = select(sockfd+1, &fds, NULL, NULL, &timeout);

  if(rc == -1)
  {
    printf("select error\n");
    exit(1);
  }

  if (FD_ISSET(sockfd, &fds))
    return 1;

  return 0;
}
