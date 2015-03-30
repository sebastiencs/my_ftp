/*
** send_request.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 01:02:40 2015 chapui_s
** Last update Sun Mar 22 01:03:03 2015 chapui_s
*/

#include "client.h"

int		send_request(int fd, char *s)
{
  char		buffer[1024];
  int		value;

  memset(buffer, 0, 1024);
  strncpy(buffer, s, 1023);
  strcat(buffer, "\r\n");
  signal(SIGPIPE, SIG_IGN);
  value = write(fd, buffer, strlen(buffer));
  return (value);
}
