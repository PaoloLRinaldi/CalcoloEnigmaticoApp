#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "fast_input.h"

void rmEcho() {
	
	struct termios t;
	int fd=0;
		tcgetattr(fd, &t);
		t.c_lflag |= ~ECHO;
		tcsetattr(fd, TCSANOW, &t);
	
	return;
}

/************************/

void setEcho() {
	
	struct termios t;
	int fd=0;
		tcgetattr(fd, &t);
		t.c_lflag &= ECHO;
		tcsetattr(fd, TCSANOW, &t);
	
	return;
}

/**************************************************/


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

/**************************************************/


int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/**************************************************/


int getls (file_info** list, const char *dir)
{
  DIR *dp;
  struct dirent *ep;  
  char *precise;   
  int i=0;
  
  (*list) = (file_info*) calloc (1, sizeof (file_info));
  precise = (char*) calloc (1000, sizeof(char));
  sprintf (precise, "./%s", dir);
  
  dp = opendir (precise);
  if (dp != NULL)
  {
    while ((ep = readdir (dp))) {
      (*list) = (file_info*) realloc ((*list), (++i)*sizeof(file_info));
      (*list)[i-1].name = (char*) calloc (100, sizeof(char));
      sprintf ((*list)[i-1].name, ep->d_name);
      if (ep->d_type == DT_REG)
        (*list)[i - 1].is_dir = false;
      else if (ep->d_type == DT_DIR)
        (*list)[i - 1].is_dir = true;
      else
        perror ("Unknown file type");
    }

    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");
  
  free(precise);

  return i;
}

/**************************************************/


void free_str_ltrl_array(file_info *list, int size) {
  int i;
  
  for (i = 0; i != size; ++i)
    free(list[i].name);
    
  free(list);
  
  return;
}