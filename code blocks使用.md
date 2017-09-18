# code blocks使用介绍
- 下载

[点此进入官网下载](http://www.codeblocks.org/downloads/26)

下载这个：codeblocks-16.01mingw_fortran-setup.exe

- 安装

无脑next，第一次进入可能要选择默认编译器，选第一个就行

- 使用

新建项目
file->new->project->Console project

即新建一个控制台程序，中间的过程按提示操作即可。


- 与C-free的区别
编译器自带的库中没有 iostream.h 和 iomanip.h，可以使用

iostream 和 iomanip,然后加一句 using namespace std;

```
# include <iostream>
# include <iomanip>
using namespace std;
```

- 汉化

