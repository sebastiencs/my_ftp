/*
** help.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 20:10:37 2015 chapui_s
** Last update Fri Mar 20 03:13:38 2015 chapui_s
*/

#include "client.h"

int		help(t_client *client, char *true_cmd, char *param)
{
  char		buffer[1024];

  memset(buffer, 0, 1024);
  if (client->tab_cmd[1])
    sprintf(buffer, "%s %s", true_cmd, param);
  else
    sprintf(buffer, "%s", true_cmd);
  if (send_request(client->fd, buffer) == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 214)
    return (-1);
  if (!client->debug)
    puts(client->buffer);
  return (0);
}
