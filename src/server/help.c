/*
** help.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 12:00:04 2015 chapui_s
** Last update Sat Mar 21 23:43:17 2015 chapui_s
*/

#include "server.h"

t_help		g_help[] =
{
  { "user", "Login to an account" },
  { "pass", "Specify the user password" },
  { "cwd", "Change working directory" },
  { "cd", "Change working directory" },
  { "list", "List working directory" },
  { "ls", "List working directory" },
  { "pasv", "Enable passive mode" },
  { "cdup", "Change to parent directory" },
  { "quit", "Logout and close connections" },
  { "close", "Logout and close connections" },
  { "dele", "Delete file" },
  { "rm", "Delete file" },
  { "help", "help ?" },
  { "syst", "Display server system" },
  { "noop", "Waste of time" },
  { "retr", "Get file from server" },
  { "get", "Get file from server" },
  { "stor", "Store file from client" },
  { "put", "Store file from client" },
  { (char*)0, (char*)0 }
};

int		help(t_user *user, char *param)
{
  int		i;

  if (!param || !strlen(param))
    send_reply(user->fd, 214, "help [command]");
  else
  {
    i = 0;
    while (g_help[i].name && strcasecmp(g_help[i].name, param))
      i += 1;
    if (g_help[i].name)
      send_reply(user->fd, 214, g_help[i].msg);
    else
      send_reply(user->fd, 214, "What ? I don't know");
  }
  return (0);
}
