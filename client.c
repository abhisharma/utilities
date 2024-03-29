#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define PORT 3490  /* well-known port */
#define MAXDATASIZE 5000 /* max number of bytes we can get at once */

int main (int argc, char* argv[]){
  int sockfd, numbytes;
  char buf[MAXDATASIZE + 1];
  struct hostent* he;
  struct sockaddr_in their_addr;
  /* connector’s address information */
  if (argc != 2) {
    fprintf (stderr, "usage: client hostname\n");
    exit (1);
  }
  if ((he = gethostbyname (argv[1])) == NULL) {
    /* get the host info */
    perror ("gethostbyname");
    exit (1);
  }

  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
    perror ("socket");
    exit (1);
  }
  their_addr.sin_family = AF_INET; /* interp’d by host */
  their_addr.sin_port = htons (PORT);
  their_addr.sin_addr = *((struct in_addr*)he->h_addr);
  bzero (&(their_addr.sin_zero), 8);
  /* zero rest of struct */
 
  if (connect (sockfd, (struct sockaddr*)&their_addr,
	       sizeof (struct sockaddr)) == -1) {
    perror ("connect");
    exit (1);
  }

  if ((numbytes = recv (sockfd, buf, MAXDATASIZE, 0))
      == -1) {
    perror ("recv");
    exit (1);
  }
  buf[numbytes] = '\0';
  printf ("Received: %s", buf);
  close (sockfd);
  return 0;

}
