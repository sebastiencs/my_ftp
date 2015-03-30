/*
** common.h for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 07:45:21 2015 chapui_s
** Last update Sun Mar 22 16:00:13 2015 chapui_s
*/

#ifndef COMMON_H_
# define COMMON_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "my_ls.h"

int		derror(const char *);
int		derrorn(const char *);
char		*get_next_line(const int fd);
int		is_nb(char *s);
int		mls(int argc, char **argv);

#endif /* !COMMON_H_ */
