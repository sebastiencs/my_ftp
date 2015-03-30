/*
** get_reply.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 00:59:45 2015 chapui_s
** Last update Sun Mar 22 01:00:52 2015 chapui_s
*/

#include "client.h"

int		get_reply(t_client *client)
{
  char		buffer[1024];
  ssize_t	size;

  memset(buffer, 0, 1024);
  size = read(client->fd, buffer, 1023);
  if (size == 0)
    return (derrorn("Server Disconnect"));
  else if (size == -1)
    return (derror("error: read"));
  client->code_reply = atoi(buffer);
  if (client->debug || client->code_reply == 220)
    my_putstr(buffer);
  memset(client->buffer, 0, 1024);
  strncpy(client->buffer, buffer, 1023);
  return (0);
}
