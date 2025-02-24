/*
** EPITECH PROJECT, 2022
** ezdfe
** File description:
** ezrfed
*/

#include "myftp.h"

void CWD(int fd, char *str, list *tmp)
{
    char v[1024];
    char w[1024];
    if (strlen(str) == 4) {
        write(fd, "550 Failled too change directory\r\n", 34);
        return;
    }
    if (strcasecmp(str,"CWD \r") == 0) {
        write(fd, "550 Failled too change directory\r\n", 34);
        return;
    }
    strcpy(v, &str[4]);
    strncpy(w, v, strlen(v) - 1);
    int x = chdir(w);
    if (x < 0)
    {
        write(fd, "550 Failled to change directory\r\n", 33);
    }
    else
    {
        memset(tmp->str, '\0', sizeof(tmp->str));
        strcpy(tmp->str, get_path());
        write(fd, "250 Directory change successfully\r\n", 35);
    }
}


void HELP(int fd)
{
    write(fd, "214 HELP\r\n", 10);
}

void handle_com(char *str, list *tmp)
{
    if (valid_cmd(str, "USER") == 1)
    {
        if (strncmp(&str[5], "Anonymous", 9) == 0)
        {
            tmp->auth = true;
            write(tmp->fds, "331 Please specify the password\r\n", 33);
        }
        else
        {
            tmp->inter = true;
            write(tmp->fds, "331 Please specify the password\r\n", 33);
        }
    }
    else if (valid_cmd(str, "PASS") == 1)
    {
        if (tmp->pass == true) write(tmp->fds, "230 Already logged in\r\n", 23);
        else
        {
            if (tmp->auth == true)
            {
                write(tmp->fds, "230 Login successful\r\n", 22);
                tmp->pass = true;
            }
            else if (tmp->inter == true && tmp->auth == false)
            {
                tmp->auth = false;
                tmp->pass = false;
                tmp->inter = false;
                write(tmp->fds, "530 Login incorrect\r\n", 21);
            }
            else write(tmp->fds, "503 Login with USER first\r\n", 27);
        }
    }
    else
    {
        if (check_cmd(str) == 1)
        {
            if (tmp->auth == false && tmp->pass == false)
                write(tmp->fds, "530 Please login with USER and PASS\r\n", 37);
            else
            {
                valid_cmd(str, "PWD") == 1 ? PWD(tmp->fds, tmp) : 0;
                valid_cmd(str, "CDUP") == 1 ? CDUP(tmp->fds, tmp) : 0;
                valid_cmd(str, "CWD") == 1 ? CWD(tmp->fds, str, tmp) : 0;
                valid_cmd(str, "DELE") == 1 ? DELE(tmp->fds, str) : 0;
                valid_cmd(str, "NOOP") == 1 ? NOOP(tmp->fds) : 0;
                valid_cmd(str, "QUIT") == 1 ? QUIT(tmp) : 0;
                valid_cmd(str, "HELP") == 1 ? HELP(tmp->fds) : 0;
            }
        }
        else
            write(tmp->fds, "500 Unknow command\r\n", 20);
    }
}

int enter_dir(char **curr_dir, char **av)
{
    if (strcmp(av[2], ".") == 0)
    {
        *curr_dir = get_path();
    }
    else
    {
        *curr_dir = malloc(sizeof(char) * PATH_MAX);
        strcpy(*curr_dir, av[2]);
    }
    if (chdir(*curr_dir) < 0)
        return 84;
    else
        return 0;
}

int valid_cmd(char *str, char *c)
{
    int e = strncasecmp(str, c, strlen(c)) == 0 ? 1 : 0;
}