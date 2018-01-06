# Objective-C 环境搭建

## 安装

听说安装 GNUstep 即可。
但是 GNUstep 以来于　build-essential，gobjc，gobjc++，gnustep-devel。
然后使用　sudo apt-get install gnustep\*　可以自动把所有需要的以来都安装。

## 配置

在　~/.bashrc 文件的最后加入下面四行

```
#set GNUstep
GNUSTEP_MAKEFILES=/usr/share/GNUstep.sh
export GNUSTEP_MAKEFILES
source /usr/share/GNUstep/Makefiles/GNUstep.sh
```

然后执行　source ~/.bashrc 命令。




## 测试 hello word

直接把 C 程序的　hello word 保存为　.m 后缀的就可以了。
但是这不能表现出 Objective-C 来。


```
#import <Foundation/Foundation.h>

int main(int argc, const char *argv[]) {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"Hello world\n");
    [pool drain];
    return 0;
}
```

## 编译


我们直接使用　gcc 编译是有问题的。
我们需要使用　makefile 来编译。


创建 GNUmakefile 文件，写入下面内容

```
include $(GNUSTEP_MAKEFILES)/common.make

TOOL_NAME = LogTest
LogTest_OBJC_FILES = source.m

include $(GNUSTEP_MAKEFILES)/tool.make
```

然后执行　make 即可。

可执行程序在有一个　obj 目录，里面有生成的可执行程序。

