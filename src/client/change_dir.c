/*
** change_dir.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 19:26:20 2015 chapui_s
** Last update Fri Mar 20 03:13:39 2015 chapui_s
*/

#include "client.h"

int		change_dir(t_client *client, char *true_cmd, char *param)
{
  char		buffer[1024];

  memset(buffer, 0, 1024);
  if (client->tab_cmd[1])
    sprintf(buffer, "%s %s", true_cmd, param);
  else
    sprintf(buffer, "%s", true_cmd);
  if (send_request(client->fd, buffer) == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 250)
    return (-1);
  return (0);
}

int		change_dir_up(t_client *client, char *true_cmd, char *param)
{
  (void)param;
  return (change_dir(client, true_cmd, ".."));
}
