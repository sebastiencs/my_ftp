/*
** send_reply.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 22:20:50 2015 chapui_s
** Last update Sat Mar 21 23:41:35 2015 chapui_s
*/

#include "server.h"

t_reply			g_reply[] =
{
  { 120, "%d Service ready in %s minutes.\r\n", 1 },
  { 125, "%d Data connection already open; transfer starting.\r\n", 0 },
  { 150, "%d File status okay; about to open data connection.\r\n", 0 },
  { 200, "%d Command okay.\r\n", 0 },
  { 220, "%d Service ready for new user.\r\n", 0 },
  { 221, "%d Service closing control connection.\r\n", 0 },
  { 226, "%d Closing data connection.\r\n", 0 },
  { 230, "%d User logged in, proceed.\r\n", 0 },
  { 250, "%d Requested file action okay, completed.\r\n", 0 },
  { 257, "%d \"%s\".\r\n", 1 },
  { 331, "%d User name okay, need password.\r\n", 0 },
  { 332, "%d Need account for login.\r\n", 0 },
  { 501, "%d Syntax error in parameters or arguments.\r\n", 0 },
  { 502, "%d Command not implemented.\r\n", 0 },
  { 215, "%d UNIX Type: L8\r\n", 0},
  { 530, "%d %s\r\n", 1 },
  { 227, "%d Entering Passive Mode (%s).\r\n", 1 },
  { 553, "%d Requested action not taken.\r\n", 0 },
  { 550, "%d Requested action not taken.\r\n", 0 },
  { 214, "%d %s\r\n", 1 },
  { 0, (char*)0, 0 }
};

static void		get_formatted_msg(char *buffer, int i, char *opt_msg)
{
  if (g_reply[i].complete_msg)
    snprintf(buffer,
	     SIZE_MAX_BUFFER - 1,
	     g_reply[i].msg,
	     g_reply[i].num, opt_msg);
  else
    snprintf(buffer,
	     SIZE_MAX_BUFFER - 1,
	     g_reply[i].msg,
	     g_reply[i].num);
}

int			send_reply(int fd, int num, char *opt_msg)
{
  char			buffer[SIZE_MAX_BUFFER];
  int			i;

  i = 0;
  memset(buffer, 0, SIZE_MAX_BUFFER);
  while (g_reply[i].num && g_reply[i].num != num)
    i += 1;
  if (!g_reply[i].num)
    return (-1);
  get_formatted_msg(buffer, i, opt_msg);
  if (write(fd, buffer, strlen(buffer)) == -1)
    return (derror("error: write"));
  return (0);
}
