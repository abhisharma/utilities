#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define PORT 3490  /* well-known port */
#define BACKLOG 10  /* how many pending connections queue  will hold */

/* This routine returns the size of the file it is called with. */

static unsigned
get_file_size (const char * file_name)
{
    struct stat sb;
    if (stat (file_name, & sb) != 0) {
        fprintf (stderr, "'stat' failed for '%s': %s.\n",
                 file_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    return sb.st_size;
}

/* This routine reads the entire file into memory. */

static unsigned char *
read_whole_file (const char * file_name)
{
    unsigned s;
    unsigned char * contents;
    FILE * f;
    size_t bytes_read;
    int status;

    s = get_file_size (file_name);
    contents = malloc (s + 1);
    if (! contents) {
        fprintf (stderr, "Not enough memory.\n");
        exit (EXIT_FAILURE);
    }

    f = fopen (file_name, "r");
    if (! f) {
        fprintf (stderr, "Could not open '%s': %s.\n", file_name,
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    bytes_read = fread (contents, sizeof (unsigned char), s, f);
    if (bytes_read != s) {
        fprintf (stderr, "Short read of '%s': expected %d bytes "
                 "but got %d: %s.\n", file_name, s, bytes_read,
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    status = fclose (f);
    if (status != 0) {
        fprintf (stderr, "Error closing '%s': %s.\n", file_name,
                 strerror (errno));
        exit (EXIT_FAILURE);
    }

    return contents;
}

main()
{
  int sockfd, new_fd; /* listen on sock_fd, new connection on new_fd */
  struct sockaddr_in my_addr;  /* my address */
  struct sockaddr_in their_addr; /* connector addr */
  int sin_size;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1){
    perror("socket");
    exit(1);
  }

  bzero(&my_addr, sizeof(struct sockaddr));
  /* zero the struct */
  my_addr.sin_family = AF_INET; /* host byte order */
  my_addr.sin_port = htons(PORT); /* short, network byte order */
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sockfd, (struct sockaddr *)&my_addr,
	   sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }
  perror("Server started");

  while(1) {
    sin_size = sizeof(struct sockaddr_in);
    
    if ((new_fd = accept(sockfd, (struct sockaddr*)
			 &their_addr,&sin_size)) == -1)
    {
	perror("accept");
	continue;
    }
    perror("Accepted connection");

    if (!fork()) { /* this is the child process */
      unsigned char *file_contents;
      unsigned s;

      s = get_file_size ("server.c");
      file_contents = read_whole_file ("server.c");
      
      if (send(new_fd,file_contents, s, 0)
	  == -1)
	perror("send");
      close(new_fd);
      free (file_contents);
      exit(0);
    }
    close(new_fd); /* parent doesn't need this */
    /* clean up all child processes */
    while(waitpid(-1,NULL,WNOHANG) > 0);

  }
}
