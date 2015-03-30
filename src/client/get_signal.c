/*
** get_signal.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 17:54:18 2015 chapui_s
** Last update Sun Mar 22 17:55:12 2015 chapui_s
*/

#include "client.h"

void			manage_sigint(t_client* ptr)
{
  static t_client	*client;

  if (ptr)
  {
    client = ptr;
  }
  else
  {
    quit_client(client, (char*)0, (char*)0);
    exit(0);
  }
}

void		catch_sigint(int sig)
{
  (void)sig;
  manage_sigint((t_client*)0);
}
