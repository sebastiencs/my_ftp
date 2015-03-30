/*
** send_password.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar 21 23:24:22 2015 chapui_s
** Last update Sat Mar 21 23:30:57 2015 chapui_s
*/

#include "client.h"

int		send_password(t_client *client, char *true_cmd, char *param)
{
  char		buffer[1024];

  memset(buffer, 0, 1024);
  strncpy(buffer, true_cmd, strlen(true_cmd));
  buffer[strlen(true_cmd)] = ' ';
  strcat(buffer, param);
  if (send_request(client->fd, buffer) == -1)
    return (-1);
  if (get_reply(client) == -1)
    return (-1);
  return (0);
}
