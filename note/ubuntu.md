# 1 snap

包管理工具

在Ubuntu系统中，snapd 的 seed 信息通常存储在 /var/lib/snapd/seed 目录下。

# 2 tar压缩和解压

- tar -cjvf filename.tar.bz2 -C 创建临时目录 具体要压缩的目录
- tar -xjvf filename.tar.bz2

- tar -czvf filename.tar.gz -C 创建临时目录 具体要压缩的目录
- tar -xzvf filename.tar.gz


# 3 在Ubuntu上访问另一个台Ubuntu系统

- sudo apt-get install cifs-utils 安装工具cifs，便于共享windows文件夹和samba共享的文件夹
- sudo mkdir -p /mnt/remote_share 在mnt下创建一个临时的挂载文件夹remote_share
- sudo mount -t cifs -o username=chris,password=password //server-ip/share /mnt/remote_share 挂载共享目录
- sudo mount -t cifs -o username=chris,password=PeitianX //10.20.210.90/share /mnt/remote_share 挂载共享目录

# 4 创建用户

ubuntu下如何创建ae用于，并拥有root权限？

- `sudo adduser ae` ： 创建一个名为 ae 的用户
- `sudo usermod -aG sudo ae` ： 将用户添加到 sudo 组
  - `-aG`: 将用户添加到指定的组而不从其他组中移除。
- `su - ae`：切换到ae用户 
  - `-`： 这个选项表示切换到新用户的主目录，并加载其环境变量。
  - `ae`: 是你想要切换到的用户名。


# 5 snap包瘦身

- gnome-shell --version