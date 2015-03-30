/*
** pwd.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 20:02:50 2015 chapui_s
** Last update Fri Mar 20 03:13:36 2015 chapui_s
*/

#include "client.h"

int		get_cur_dir(t_client *client, char *true_cmd, char *param)
{
  (void)true_cmd;
  (void)param;
  if (send_request(client->fd, "PWD") == -1)
    return (-1);
  if (get_reply(client) == -1 || client->code_reply != 227)
    return (-1);
  if (!client->debug)
    puts(client->buffer);
  return (0);
}
