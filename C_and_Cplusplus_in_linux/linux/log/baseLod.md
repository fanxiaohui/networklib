
# log file 的含义


## /var/log/messages

 Contains global system messages, including the messages that are logged during system startup. There are several things that are logged in /var/log/messages including mail, cron, daemon, kern, auth, etc.

包含全局系统消息，包括在系统启动过程中记录的信息。但是也有一些记录在/ var/ log / messages中几件事情，包括邮件，cron里，守护进程，克恩，身份验证等。


## /var/log/dmesg 

Contains kernel ring buffer information. When the system boots up, it prints number of messages on the screen that displays information about the hardware devices that the kernel detects during boot process. These messages are available in kernel ring buffer and whenever the new message comes the old message gets overwritten. You can also view the content of this file using the dmesg command.

包含内核环形缓冲区的信息。当系统启动时，它打印出显示有关该内核在启动过程中检测到的硬件设备的信息在屏幕上的消息数量。这些信息可在内核环形缓冲区，每当新的消息出现在旧消息被覆盖。您还可以查看使用dmesg命令这个文件的内容。

## /var/log/auth.log 

Contains system authorization information, including user logins and authentication machinsm that were used.

包含系统授权信息，包括用户登录和所使用的身份验证machinsm。

## /var/log/boot.log 

Contains information that are logged when the system boots 

包含了被记录在系统开机时的信息


## /var/log/daemon.log 

 Contains information logged by the various background daemons that runs on the system 

包含该系统上运行的各种后台守护进程记录的信息

## /var/log/dpkg.log 

Contains information that are logged when a package is installed or removed using dpkg command 

包含一个包安装或移除使用dpkg命令时所记录的信息

## /var/log/kern.log

Contains information logged by the kernel. Helpful for you to troubleshoot a custom-built kernel.

包含记录的内核信息。有助于你解决一个定制的内核。


## /var/log/lastlog

Displays the recent login information for all the users. This is not an ascii file. You should use lastlog command to view the content of this file.

显示最近的登录信息的所有用户。这不是一个ascii文件。您应该使用lastlog的命令来查看该文件的内容。

## /var/log/maillog /var/log/mail.log 

Contains the log information from the mail server that is running on the system. For example, sendmail logs information about all the sent items to this file

包含从正在该系统上运行的邮件服务器的日志信息。例如，sendmail的记录有关的所有已发送的邮件信息到这个文件


## /var/log/user.log 

Contains information about all user level logs

包含所有用户级别的日志信息

## /var/log/Xorg.x.log 

Log messages from the X

从X日志消息

## /var/log/alternatives.log 

Information by the update-alternatives are logged into this log file. On Ubuntu, update-alternatives maintains symbolic links determining default commands.

通过update-alternatives的信息被记录到该日志文件。在Ubuntu上，update-alternatives来保持符号链接确定默认的命令。

## /var/log/btmp 

This file contains information about failed login attemps. Use the last command to view the btmp file. For example, “last -f /var/log/btmp | more”

此文件包含有关失败的登录attemps信息。使用last命令查看BTMP文件。例如, “last -f /var/log/btmp | more”

## /var/log/cups 

All printer and printing related log messages

所有的打印机和打印相关的日志信息

## /var/log/anaconda.log

When you install Linux, all installation related messages are stored in this log file

When you install Linux, all installation related messages are stored in this log file

## /var/log/yum.log 

Contains information that are logged when a package is installed using yum

包含在一个包使用yum安装的记录信息

## /var/log/cron 

Whenever cron daemon (or anacron) starts a cron job, it logs the information about the cron job in this file

每当cron守护进程（或anacron的）启动一个cron作业，它记录在此文件中关于cron作业的信息

## /var/log/secure 

Contains information related to authentication and authorization privileges. For example, sshd logs all the messages here, including unsuccessful login.

包含与身份验证和授权权限的信息。例如，sshd的日志，这里所有的信息，包括登录失败。

## /var/log/wtmp or /var/log/utmp 

Contains login records. Using wtmp you can find out who is logged into the system. who command uses this file to display the information.


包含登录记录。使用wtmp文件你可以找出谁登录到系统中。谁命令使用此文件来显示信息。

## /var/log/faillog 

Contains user failed login attemps. Use faillog command to display the content of this file.


包含用户登录失败attemps。使用登录失败命令可以显示该文件的内容。







