/*
** get_info_client.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 00:58:40 2015 chapui_s
** Last update Sun Mar 22 00:59:40 2015 chapui_s
*/

#include "client.h"

int		get_info_client(t_client *client, int argc, char **argv)
{
  if (argc < 3 || is_nb(argv[2]) == -1)
    return (usage());
  client->machine = argv[1];
  client->port = atoi(argv[2]);
  return (0);
}
