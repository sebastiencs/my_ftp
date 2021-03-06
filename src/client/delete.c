/*
** delete.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 19:57:04 2015 chapui_s
** Last update Thu Mar 19 20:02:07 2015 chapui_s
*/

#include "client.h"

int		delete_file(t_client *client, char *true_cmd, char *param)
{
  char		buffer[1024];

  memset(buffer, 0, 1024);
  if (!client->tab_cmd[1])
  {
    puts("Please give a file to remove");
    return (0);
  }
  sprintf(buffer, "%s %s", true_cmd, param);
  if (send_request(client->fd, buffer) == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 250)
    return (-1);
  return (0);
}
