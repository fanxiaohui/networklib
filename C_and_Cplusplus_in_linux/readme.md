
## 安装相关库


想要使得 c/c++ 连接mysql,需要安装 libmysqld-dev。

于是我们可以安装 libmysqld-dev

````
tiankonguse@tiankonguse-PC:~$ sudo apt-get install libmysqld-dev
````

结果提示

````
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Some packages could not be installed. This may mean that you have
requested an impossible situation or if you are using the unstable
distribution that some required packages have not yet been created
or been moved out of Incoming.
The following information may help to resolve the situation:

The following packages have unmet dependencies:
 libmysqld-dev : Depends: libmysqlclient-dev (>= 5.5.35-0ubuntu0.12.04.2)
E: Unable to correct problems, you have held broken packages.
````

那就先安装 libmysqlclient-dev 吧。

````
tiankonguse@tiankonguse-PC:~$  sudo apt-get install libmysqlclient-dev
````

但是又提示

````
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Some packages could not be installed. This may mean that you have
requested an impossible situation or if you are using the unstable
distribution that some required packages have not yet been created
or been moved out of Incoming.
The following information may help to resolve the situation:

The following packages have unmet dependencies:
 libmysqlclient-dev : Depends: libmysqlclient18 (= 5.5.35-0ubuntu0.12.04.2) but 10.0.9+maria-1~precise is to be installed
E: Unable to correct problems, you have held broken packages.
tiankonguse@tiankonguse-PC:~$ 
````

原来问题在于我的数据库不是 musql ,而是 maria 的原因吧。

那尝试安装 libmariadb 吧。

````
tiankonguse@tiankonguse-PC:~$ sudo apt-get install libmariadb
libmariadbclient18    libmariadbclient-dev  libmariadbd-dev
````
刚好出现了上面 mysql 类似的三个包。安装它们试试吧。

````
tiankonguse@tiankonguse-PC:~$ sudo apt-get install libmariadb\*
````

## 编译

如果自己使用命令行编译，加上-lmysqlclient选项。
如果使用IDE，将连接库设为mysqlclient。

## 头文件

一般头文件在 mysql/mysql.h 中。


## 使用


### 用CAPI连接MySQL数据库有两个步骤

#### 初始化一个连接句柄

````
MYSQL \*mysql\_init(MYSQL \*connection);
````

#### 建立连接

````
MYSQL \*mysql\_real\_connect(MYSQL \*connection,   
                          const char \*server\_host,      
                          const char \*sql\_user\_name,  
                          const char \*sql\_password,   
                          const char \*db\_name,   
                          unsigned int port\_number,   
                          const char \*unix\_socket\_name,   
                          unsigned int flags);  //建立连接
//成功返回MySQL结构指针，失败返回NULL
````

### MySQL连接工作完成之后，需要对MySQL的连接进行释放

````
void mysql\_close(MYSQL \*connection); //关闭连接
//参数connection被清空，指针变为无效
````

### mysql_options用于设置额外选项，并影响连接行为，但是它只能在mysql_init和mysql_real_connect之间调用


````
int mysql\_options(MYSQL \*connection, enum mysql\_option option, const char \*argument); //设置连接选项  
````

option的值为下列四个值之一：

````
MYSQL\_INIT\_COMMAND       //连接到MySQL服务器时将执行的命令，再次连接时将自动再次执行。
MYSQL\_OPT\_CONNECT\_TIMEOUT    //连接超时前的等待秒数
MYSQL\_OPT\_COMPRESS           //网络连接中使用压缩机制
MYSQL\_OPT\_PROTOCOL       //要使用的协议类型，影视mysql.h中定义的mysql\_protocol\_type枚举值之一
````

### 以下两个函数来处理错误信息

````
unsigned int mysql\_errno(MYSQL \*connection);    //返回错误代码(0表示为出现错误)  
char \*mysql\_error(MYSQL \*connection);           //返回错误信息，是以NULL作为终结的字符串 
````

### 执行SQL语句

````
int mysql\_query(MYSQL \*connection, const char \*query);
````

## 样例

[test.cpp](test.cpp)


