/*
** get_port.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 06:39:57 2015 chapui_s
** Last update Thu Mar 19 16:02:54 2015 chapui_s
*/

#include "server.h"

int		get_port(t_server *server, char *port)
{
  if (!port || is_nb(port) == -1)
    return (usage());
  server->port = atoi(port);
  return (0);
}
