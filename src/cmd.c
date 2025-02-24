/*
** EPITECH PROJECT, 2022
** edzfev
** File description:
** ezfed
*/

#include "myftp.h"

void PWD(int fd, list *tmp)
{
    chdir(tmp->str);
    char *str = get_path();
    write(fd, "257 ", 4);
    write(fd, str, strlen(str));
    write(fd, "\r\n", 2);
    free(str);
}

void CDUP(int fd, list *tmp)
{
    struct passwd *pw = getpwuid(getuid());
    write(fd, "200 ", 4);
    chdir(pw->pw_dir);
    memset(tmp->str, '\0', sizeof(tmp->str));
    strcpy(tmp->str, pw->pw_dir);
    write(fd, "Directory successfully changed\r\n", 32);
}

void DELE(int fd, char *str)
{
    char v[1024];
    char w[1024];
    strcpy(v, &str[5]);
    strncpy(w, v, strlen(v) - 1);
    if (remove(w) == 0)
    {
        write(fd, "250 File deleted\r\n", 18);
    }
    else
    {
        write(fd, "550 File not found\r\n", 20);
    }
}

void NOOP(int fd)
{
    write(fd, "200 NOOP\r\n", 10);
}

void QUIT(list *lst)
{
    write(lst->fds, "221 Goodbye\r\n", 13);
    close(lst->fds);
    lst->fds = 0;
    lst->auth = false;
    lst->inter = false;
    lst->link = false;
    lst->pass = false;
    memset(lst->str, '\0', strlen(lst->str));
}
