[1 如何拉取docker](#-1-如何拉取docker)  
[5 如何使用Vscode远程打开docker容器中的工程](#-5-如何使用Vscode远程打开docker容器中的工程)

# 1 如何拉取docker

- `/etc/docker`
- `sudo vim daemon.json`

      {
          "registry-mirrors":["https://hub.xdark.top", "https://hub.littlediary.cn", "https://dockerpull.org", "https://hub.crdz.gq", "http://docker.1panel.live", "https://docker.unsee.tech", "https://docker.udayun.com", "https://docker.kejilion.pro", "https://registry.dokcermirror.com", "https://docker.rainbond.cc", "https://hub.geekery.cn", "https://docker.1panelproxy.com", "https://docker.linkedbus.com", "https://docker.nastool.de"]
      }

    
- `systemctl daemon-reload`
- `systemctl restart docker`
- `docker pull httpd`: 执行命令拉取apache容器，拉取成功，这个就叫**专业**


- 更新源：若以上的源都失败了，可以打开如下链接

  - `https://www.coderjia.cn/archives/dba3f94c-a021-468a-8ac6-e840f85867ea`

# 2 使用docker的命令

image就像是光盘，container就是一个已安装的系统

- `sudo docker run hello-world`：
- `sudo docker pull jupyter/base-notebook`:
- `sudo docker images`: 查看docker所拉取的镜像
- `docker ps -a --size` or `docker ps --all --size`： 如何查看docker中容器占有的大小

- 启动停止的容器并进入容器
  - `sudo docker ps -a`: 查看历史的所有容器
  - `docker start container_name_or_id`: 启动容器
  - `docker exec -it container_name /bin/bash`: 启动容器之后，以交互的方式进入容器
- 停止容器
  - `docker stop container_name_or_id`: 停止容器 



# 3 使用docker创建jupyter容器

从而可以运行`jupyter Notebook`

- `sudo docker run -d -p 8888:8888 jupyter/base-notebook`: 将本地的8888端口映射到容器的8888端口
- `sudo docker ps`: 查看容器已经运行

- `127.0.0.1:8888`: 在本地浏览器中输入该地址,需要token，输入以下内容
- `sudo docker logs [容器id]`: 就可以看到如下信息中的token

  http://d1f8a81a60b6:8888/lab?token=d6930a45306b949b3cba33f43885721db0efa0b419cfcba1
  http://127.0.0.1:8888/lab?token=d6930a45306b949b3cba33f43885721db0efa0b419cfcba1

  推出来之后，在下方添加密码，如Hello123456,这样每次进入，只要输入密码就可以，而不需要每次都用token了

- `Shift Enter`: 快捷键运行程序

## 3.1 markdown基本功能

### 3.1.1 在markdown中输入表格的形式：

|syntax     |description|
|------     |-----------|
|Header     |Title      |
|Paragraph  | Text      |

### 3.1.2 添加图片

![](https://images.cpolar.com/img/202401181550696.jpeg)

### 3.1.3 直接安装github插件

还可以修改github中的代码

- `Settings/Extension Manager/勾选Disclaimed Status`：右边出现插件图标
- 点击该图标，并输入github，安装`jupyterlab-github`
- 登出再重新进入，左侧就会有github logo
- 可以输入想查找的项目，如`seaside-play`,就可以直接看到了

### 3.1.4 Cpolar内网穿透工具

内网穿透工具，在公网上远程访问Jupyter Notebook，就可以大大提高了学习和工作效率。

- `一键脚本安装命令`：

    curl -L https://www.cpolar.com/static/downloads/install-release-cpolar.sh | sudo bash

...

### 3.1.5 如何删除docker中的image和容器

- `sudo docker ps -a` ： 查看所有正在运行的容器
- `sudo docker stop ${CONTAINER ID}` : 停止容器
- `docker rm ${CONTAINER ID}`: 删除容器
- `sudo docker rmi ${IMAGE ID}` : 删除镜像


# 4 64位Ubuntu通过Docker安装32位的Ubuntu16.04

在Docker中运行32位的Ubuntu 16.04系统有一些挑战，因为Docker通常在64位系统上运行，并且默认支持64位容器。然而，如果你确实需要运行32位的Ubuntu 16.04容器，你可以尝试以下方法：

## 4.1 方法1：使用Multiarch支持
从Docker 17.05版本开始，Docker支持多架构（Multiarch），这意味着你可以下载和运行不同架构的Docker镜像。要运行32位的Ubuntu 16.04容器，你需要确保你的Docker版本支持多架构，并且安装了相应的工具。

### 4.1.1 安装binfmt-support：
这个包允许你的64位系统支持运行32位的二进制文件。

sh
- sudo apt-get update
- sudo apt-get install binfmt-support

### 4.1.2 添加32位架构支持：
使用dpkg添加i386架构支持。

sh
- sudo dpkg --add-architecture i386
- sudo apt-get update

### 4.1.3 拉取32位的Ubuntu 16.04镜像：
你可以尝试拉取一个32位的Ubuntu 16.04镜像。由于官方Docker Hub上可能没有直接提供32位的Ubuntu 16.04镜像，你可能需要查找社区提供的镜像或者自己构建一个。

sh
- sudo docker pull i386/ubuntu:16.04
如果官方镜像库中没有32位的Ubuntu 16.04镜像，你可能需要查找其他社区提供的镜像，或者自己构建一个32位的Ubuntu 16.04 Docker镜像。

## 4.2 方法2：自定义构建32位Ubuntu 16.04镜像
如果你找不到现成的32位Ubuntu 16.04镜像，你可以考虑自己构建一个。以下是一个基本的Dockerfile示例，用于创建32位的Ubuntu 16.04镜像：

### 4.2 1 dockerfile

    # 使用32位的Ubuntu 16.04基础镜像

    FROM i386/ubuntu:16.04

    # 设置环境变量
    ENV DEBIAN_FRONTEND noninteractive

    # 更新包列表并安装基本软件包
    RUN apt-get update && apt-get install -y \
        vim \
        wget \
        && apt-get clean

    # 设置工作目录
    WORKDIR /root

    # 启动bash shell
    CMD ["/bin/bash"]

将上述内容保存为Dockerfile。

### 4.2.2 在包含Dockerfile的目录中，运行以下命令来构建镜像：

sh
- sudo docker build -t my-ubuntu-16.04-i386 .
运行构建的32位Ubuntu 16.04容器：

sh
- sudo docker run -it my-ubuntu-16.04-i386


## 4.3 运行Ubuntu16.04

- sudo docker run -it [IMAGE ID]

    -i 或 --interactive：保持标准输入（STDIN）打开，即使不附加到容器终端。
    -t 或 --tty：分配一个伪终端。

- 修改容器名字
  - 在运行容器时指定名称： `sudo docker run -it --name my-ubuntu ubuntu`
  - 为已运行的容器重命名: 
    - `sudo docker ps`
    - `sudo docker rename old-container-name new-container-name`
## 4.4 如何将文件复制到docker中的ubuntu中？

### 4.4.1 方法1：使用 docker cp 命令
  - 从宿主机复制到容器：`docker cp /path/to/local/file container_name:/path/to/container/destination`
  - 从容器复制到宿主机：`docker cp container_name:/path/to/container/file /path/to/local/destination`
### 4.4.2 使用Dockerfile和构建镜像

如果你经常需要将文件复制到容器中，可以考虑在构建Docker镜像时将文件添加到镜像中。

- 创建Dockerfile：

  在Dockerfile中使用 COPY 指令将文件添加到镜像中
  dockerfile
  
  FROM ubuntu
  COPY /path/to/local/file /path/to/container/destination

- `docker build -t my-image-name .`: 构建Docker镜像：
- `docker run -it my-image-name /bin/bash`: 使用构建的镜像运行容器

# 5 如何在ubuntu中使用VSCode访问容器中的C++工程

## 5.1 使用VS Code访问容器中C++代码的推荐方式

remote-development 是最适合用于连接Docker容器进行C++开发的扩展。它提供了以下优势：

- 直接连接容器： 可以直接连接到运行中的Docker容器，无需额外的配置。
- 丰富的功能： 支持远程调试、代码补全、Git集成等功能。
- 自定义配置： 可以通过.devcontainer.json文件自定义开发环境。
- 跨平台： 支持Windows、macOS和Linux。

## 5.2 具体操作步骤

- 安装如下扩展 
  - Remote Development: 
  - Dev Containers :
