/*
** get_command.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 01:04:38 2015 chapui_s
** Last update Sun Mar 22 01:05:16 2015 chapui_s
*/

#include "client.h"

int		get_command(t_client *client, char *buffer)
{
  ssize_t	size;

  memset(buffer, 0, 1024);
  if ((size = read(0, buffer, 1023)) == -1)
    return (derror("error: read"));
  if (size > 0)
    buffer[size - 1] = 0;
  else
    puts("");
  if ((client->tab_cmd = my_str_to_wordtab(buffer)) == (char**)0)
    return (-1);
  return (0);
}
