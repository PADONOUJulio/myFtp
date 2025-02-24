# myFtp

This program is a FTP (file transfer protocol) server made in C language.
Supported commands are RFC 959 compliant.

Supported commands
PORT
PASV
RETR
PASS
USER
QUIT
CWD
CDUP
PWD
DELE
STOR
HELP
NOOP
LIST

# How to use it?
Clone the project and run this command to compile the program:

$> make
After that, you can run the server with this command:

$> ./myftp <SERVER PORT> <SERVER ROOT LOCATION>
Exemple:

$> ./myftp 4242 .
The default username is "Anonymous".
The default password is "".
