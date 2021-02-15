# Linux Notes

> Time: 2019.11.30 21:53 Saturday

> Author: Sears Saint Tian

## 版本

**Linux发行版** => 应用程序 -> 系统调用 -> **Linux 内核**：稳定版、开发版 => 硬件

Linux发行版本：Ubuntu, Debian, Redhat, CentOS, Fedora, openSUSE, Mageia, Manjaro, Arch, Linux Mint 

==Linux没有盘符的概念，从根目录"/"开始==

==一切皆文件==

## 文件命令

学习终端命令的技巧：不需要死记硬背，对于常用命令（10多个），用的多了，自然就记住了；对于不常用的，临时遇到找度娘

`Ctrl + Shift + =` 放大终端窗口字体	`Ctrl + -` 缩小终端字体

格式：command [-options] [parameter]

+ ls = list 查看目录内容

  ls -a -l -h 所有 长格式 人类可读 

+ pwd = print wrok directory 查看当前工作目录

+ cd [path]= change directory 切换目录

  cd 或 cd ~ 切换到家目录

  cd . 切换到当前目录

  cd .. 切换到上级目录

  cd - 在最近两次目录间切换

+ touch file （不存在则）创建文件

+ mkdir dir = make directory 创建目录

  mkdir -p a1/b1/c1 递归创建

+ rm [file_name] = rmove 删除文件/目录

  rm -rf 递归 强制删除

+ tree 树状图显示文件目录结构

  tree -d 只显示目录

+ cp src dst = copy 复制

  cp src dst -f -i -r 强制 覆盖提示 递归目录

+ mv src dst = move 移动/重命名

+ cat file = concatenate 查看/创建/合并/追加文件内容 

  cat -b -n file 对非空 对所有 （ 输出行编号）

  cat -n file <=> nl

+ more 分屏显示文件内容

  操作：space 下一屏，Enter 下一行，b 回滚一屏， f 前滚一屏，q 退出

+ find [path] -name "text" 查找文件名

+ grep text 查找文件内容

  grep -n -v -i text 行号 取反 忽略大小写

+ ln -s srcfile linkfile 软链接文件（=>Windows的快捷方式）

  *源文件使用绝对路径，方便移动连接文件后仍然可以正常使用*

  ln srcfile linkfile 硬链接文件（两个文件占用相同大小的硬盘空间）

  ==在Linux中，**文件名**和**文件数据**是分开存储的==

  只有文件的 `硬链接数==0`才会被删除

  ```mermaid
  graph LR
  SB[文件名] --> SA[文件数据]
  SC[软链接文件数据] --> SB
  SD[软链接文件名] --> SC
  ```

  ```mermaid
  graph LR
  HB[文件名] --> HA[文件数据]
  HC[硬链接] --> HA[文件数据]
  ```

+ tar 打包/解包，gzip 压缩/解压缩

  **.tar.gz** <= tar + gzip

  tar -zcvf file.tar.gz files/dirs 打包压缩文件 压缩 创建 显示进度 文件名

  tar -zxvf file.tar.gz -C dir 解包解压缩文件 压缩(gzip) 解开(extract) 显示进度(verbose) 文件名(file) 目标目录(Change to dir)

  **.tar.bz2** <= tar + bzip2

  tar -jcvf file.tar.bz2 files/dirs 

  tar -jxvf file.tar.bz2 -C dir 

  打包压缩：Windows -> rar, Mac -> zip, Linux -> tar.gz

+ echo

+ \> 输出，会覆盖 >> 追加 重定向

+ | 管道

+ clear 清屏

## 远程命令

+ shutdown option time 关机/重启

  shutdown -r now 重启 立刻

  shutdown -c 取消

+ ifconfig = network interface configure 查看网卡配置信息

  类比：电脑 => 电话，网卡 => SIM卡，IP地址 => 电话号码

  物理网卡命名 ensXX，一台计算机可能会有一个物理网卡和多个虚拟网卡

+ ping ip_address 检测连接

+ ssh [-p port] user@remote(ip/domain/alias) = Secure Shell 远程连接

  数据传输加密，防止信息泄露；数据传输压缩，提高传输速度

  默认端口22

  > 免密码登录：
  >
  > **ssh-keygen** -> id_rsa, id_rda.pub
  >
  > **ssh-copy-id -p port user@remot_ip**
  >
  > 非对称加密算法：
  >
  > 本地使用私钥加密/解密，服务器使用公钥解密/加密

  > 别名登录：
  >
  > cd ~/.ssh | touch config :
  >
  > ```txt
  > Host myserver
  > 	HostName 172.16.146.1
  > 	User itheima
  > 	Port 22
  > ```
  >
  > ssh myserver

+ scp [-P port] user@remote_ip:file_path = Secure Copy 远程复制文件

  scp -r ... 目录

  FileZilla传输文件，FTP服务，端口号21

## 用户命令

ls -l : info

-rw-rw-r--   1 sky  sky     1512 7月  24 22:47 my.txt

-rwxrwxr-x   1 sky  sky     9320 7月  16 16:14 server

drwxrwxr-x   2 sky  sky     4096 7月  22 21:56 test

权限，硬链接数，拥有者，组，大小，时间，名称



> 硬链接数：有多少种方式可以访问到当前文件/目录，子目录越多数值越大
>
> - cd /home/Documents/aaa
> - cd .
> - cd ..
> - ...

+ sudo = substitude user 超级用户

  代替其他用户，预设身份为root，输入密码，5分钟有效期限

+ groupadd group 添加组

  需要sudo权限，组信息文件 /etc/group :

  最后一列表示用户的附加权限

+ groupdel group 删除组

+ useradd user 添加用户

  useradd **-m** -g group user 自动建立家目录 指定用户组

  用户信息文件 /etc/passwd :

  用户名; 密码(x=加密); UID(用户标识); GID(组标识); 用户全名/本地帐号; 家目录; 登录的Shell(ubuntu, remote=dash，Terminal=/bin/bash)

  修改用户密码的程序 /usr/bin/passwd

+ passwd user 设置用户密码

+ userdel user 删除用户

  userdel **-r**  user 自动删除家目录

+ usermod 修改用户的主组/附加组和登录Shell

  usermod -g/-G group user 修改用户的主组/附加组

  usermod -s /bin/bash user 修改登录Shell

  usermod -G sudo user 将用户添加到sudo附加组

  *设置了默认组后，需要重新登录才能生效！*

+ chown -R user file|dir = change owner 递归修改文件/目录的拥有者

+ chgrp -R group file|dir = change group 递归修改文件/目录的所属组

+ chmod -R +/-rwx file|dir = change mode 递归修改文件/目录的权限 

  对于目录，r 为读取目录内容，w 为修改目录内容，x 为执行终端命令

  chmod -R num file|dir 递归修改文件权限 num=拥有者+所属组+其他

+ id [user] 查看用户UID和GID信息

+ who 查看当前所有登录的用户列表

+ whoami 查看当前登录的用户名

+ which command 查看执行命令所在位置

  /bin (binary) 具体应用的二进制执行文件目录

  /sbin (sytem binary) 用于系统管理

  /usr/bin (user commands for applications) 后期安装的软件

  /usr/sbin (super user commands for application) 超级用户的管理程序

  *cd 命令内置在系统内核中，没有独立的文件，用which无法查找*

+ su - user 切换用户

+ exit 退出当前用户/登录

## 系统命令

+ date 查看系统时间

+ cal = calendar 查看日历

  cal -y 查看一年的日历

+ df -h = disk free 显示磁盘剩余空间 人性化显示

+ du -h [dir] = disk usage 显示目录下的文件大小 人性化显示

+ ps = process status 查看进程的状况 （默认只显示当前用户终端程序）

  ps aux 所有 详细  没有控制终端

+ top 动态显示运行中的进程并排序

  退出输入`q`

+ kill [-9] process_id 终止指定代号的进程 强行终止

  *最好只终止由当前用户开启的进程*

## 安装命令

软件源：主服务器

镜像源：所有服务器的内容是相同的

+ sudo apt = Advanced Packaging Tool 安装包管理工具

  sudo apt install/remove/upgrade package 安装/卸载/更新

## 文本编辑

vi = Visual interface 

vim = vi improved “编辑器之神”

vi --> vim (软链接)

vi file +row 文件名 定位行号

vi中的**文本缓冲区**和系统的**剪贴板**不是同一个

> 工作模式：Esc切换

- **命令模式**

   ←h  j↓  k↑  l→ 移动选择，0 行首，^ 行首非空，$ 行尾

  b 向前移动一个单词，w 向后移动一个单词

  gg 文件顶部，go/G 文件末尾，`n`gg/`n`G/:`n`数字行数 

  Ctrl+b 向上翻页，Ctrl+f 向下翻页，

  H 屏幕顶部(Head)，M 屏幕中间(Middle)，L屏幕底部(Low)

  { 上一段，} 下一段 (使用空行区分段)，% 括号匹配切换

  mx 添加标记(mark, x=[a-zA-Z])，'x 定位到x所在位置

  v **可视模式**，V **可视行模式**(水平行)，Ctrl+v 可视块模式(垂直块)

  u 撤销(undo)，Ctrl+r 恢复(redo)

  x 删除光标字符或选中文字(cut)，d(move) 删除移动命令内容(delete)，

  dd 删除光标行，`n`dd 删除多行，D 删除至行尾

  y(move) 复制(copy)，yy 复制行，`n`yy 复制多行，p 粘贴(paste)

  r 替换字符(replace)，R 替换行光标后的字符 **替换模式**

  \>> 向右增加缩进 (4个空格)， << 向左减少缩进，. 重复上次命令

  /str 查找str，n 查找下一个，N 查找上一个

  \* 向后查找当前光标所在单词，# 向前查找当前光标所在单词

  `nx` 重复次数 命名模式：`n -> 编辑模式：`x` -> Esc

  `n#`多行注释 命令模式：0 -> Ctrl+v 可视块模式 -> I 插入模式：'# ' -> Esc

- **编辑模式** :a/i/0 进入编辑(insert)

- **末行模式** 

  :wq! 保存(write) 退出(quit) 强制，:x 保存退出，

  :n file 新建文件(new)，:w file 另存为，:e . 打开内置文件浏览器(edit)

  V -> :s/`'old'`/`new`/g 可视区域替换，:%s/`'old'`/`new`/gc 全局确认替换： 

  *y=yes 替换, n=no 不替换, a=all替换所有, q=quit退出, l=last最后一个,*

  *^E向下滚屏, ^Y向上滚屏*

  ​            **O**                   o 行后插入空行，O 行前插入空行

  **I	     i  a      A**       i 当前字符插入文本(insert)，I 行首插入，

  "Hello ==W==orld"         a 当前字符后添加文本(append)，A 行末添加，

  ​            **o**

  :sp [file] 横向增加分屏(split)，:vsp[file] 纵向增加分屏(vertical split)

  切换分屏窗口 Ctrl + w + 

  ​    w 切换下一个窗(window)口，r 互换窗口(reverse)，

  ​    c 关闭窗口除最后一个(close)，q 退出窗口最后一个则关闭(close)，

  ​    o 关闭其它窗口(other)