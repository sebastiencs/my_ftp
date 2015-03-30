/*
** local_ls.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 22 15:56:18 2015 chapui_s
** Last update Sun Mar 22 15:59:31 2015 chapui_s
*/

#include "client.h"

char		*g_argv[] =
{
  "bidon",
  "-l",
  (char*)0,
};

int		local_ls(t_client *client, char *true_cmd, char *param)
{
  (void)client;
  (void)true_cmd;
  (void)param;
  mls(2, g_argv);
  return (0);
}
