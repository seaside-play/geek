# 1 如何在Ubuntu24.04上安装git server

- sudo apt-get update

- sudo apt-get install git
- sudo apt install git-daemon-sysvinit： 在Ubuntu24.04上通常安装`git-daemon-sysvinit`软件包来提供git服务

- sudo mkdir -p /src/git
- sudo adduser git
- sudo chown -R git:git /srv/git # 设置权限，让git用户可以访问目录

- sudo systemctl start git-daemon.service：启动Git服务

- sudo systemctl enable git-daemon.service: 配置Gt服务为开机启动（可选）

- sudo systemctl status git-daemon.service：检查Git服务状态

- sudo ufw allow 9418/tcp: 。如果系统启用了防火墙，并且我希望外部用户可以访问 Git 服务，我可能需要开放 Git 服务使用的端口。Git 服务默认使用 9418 端口，可以使用以上命令开放该端口。

- 测试git服务
  
    # 创建一个测试仓库
    cd /srv/git
    sudo git init --bare test.git

    # 尝试从本地克隆该仓库
    git clone git://localhost/srv/git/test.git

- 需要更高级的功能，如基于 SSH 的 Git 访问
  - sudo apt install openssh-server： 安装 OpenSSH 服务器

# 2 排查

## 2.1 问题1
运行`git clone git://localhost/srv/git/test.git`，出现如下错误

    chris@x:~/workspace/test_git$ git clone git://localhost/srv/git/test.git
    正克隆到 'test'...
    fatal: 无法连接到 localhost：
    localhost[0: 127.0.0.1]: errno=连接被拒绝

解决方案

- 检查服务是否开启：sudo systemctl status git-daemon.service
  - 若是没有开启，使用如下命令开启：sudo systemctl start git-daemon.service
- 检查 Git 服务端的配置
  - 确保 Git 服务端的配置文件正确，通常 Git 服务端使用 git-daemon 运行时，它会监听默认的 9418 端口。可以检查 /etc/sv/git-daemon/run 或 /etc/default/git-daemon 文件，确保配置正确。内容如下所示：


        # Defaults for git-daemon initscript
        # sourced by /etc/init.d/git-daemon

        # start Git daemon?
        GIT_DAEMON_START=false

        # user to run it as
        GIT_DAEMON_USER=git

        # where to store the pid file
        GIT_DAEMON_PIDFILE=/var/run/git-daemon.pid

        # where to find repositories to export
        GIT_DAEMON_DIRECTORY=/srv/git

        # what port to listen on
        GIT_DAEMON_PORT=9418

        # what extra args to pass to git daemon
        GIT_DAEMON_ARGS="--syslog --inetd --export-all --base-path=/srv/git"

可以使用 sudo nano /etc/default/git-daemon 编辑该文件，确保配置符合上述示例，特别是 GIT_DAEMON_START=true 来确保服务启动，修改内容如下：

      # Defaults for git-daemon initscript
      # sourced by /etc/init.d/git-daemon
      # installed at /etc/default/git-daemon by the maintainer scripts

      #
      # This is a POSIX shell fragment
      #

      #2025014. Chaojiang Wu 修改配置
      #GIT_DAEMON_ENABLE=false
      GIT_DAEMON_ENABLE=true
      GIT_DAEMON_START=true
      #GIT_DAEMON_USER=gitdaemon
      GIT_DAEMON_USER=git
      GIT_DAEMON_BASE_PATH=/var/lib
      #GIT_DAEMON_DIRECTORY=/var/lib/git
      GIT_DAEMON_DIRECTORY=/srv/git



      # Additional options that are passed to the Daemon.
      GIT_DAEMON_OPTIONS=""

## 2.2 问题2

    chris@x:~/workspace/test_git$ git clone git://localhost/srv/git/test.git
    正克隆到 'test'...
    fatal: 远程错误：access denied or repository not exported: /srv/git/test.git


### 2.2.1 错误分析

当你执行 git clone git://localhost/srv/git/test.git 时，收到 fatal: 远程错误：access denied or repository not exported: /srv/git/test.git 的错误信息，这表明存在访问权限问题或 Git 仓库没有正确导出。

- 可能的原因包括：

Git 服务端的配置没有允许对 /srv/git/test.git 这个仓库的访问。
权限设置问题，例如 Git 服务端进程没有足够的权限访问或导出该仓库。
- 解决步骤
  - 检查 Git 服务端的配置：
  - 确保 Git 服务端的配置文件正确，通常 Git 服务端使用 git-daemon 运行时，其配置文件 /etc/default/git-daemon 应该包含以下内容或类似内容：


          # Defaults for git-daemon initscript
          # sourced by /etc/init.d/git-daemon

          # start Git daemon?
          GIT_DAEMON_START=true

          # user to run it as
          GIT_DAEMON_USER=git

          # where to store the pid file
          GIT_DAEMON_PIDFILE=/var/run/git-daemon.pid

          # where to find repositories to export
          GIT_DAEMON_DIRECTORY=/srv/git

          # what port to listen on
          GIT_DAEMON_PORT=9418

          # what extra args to pass to git daemon
          GIT_DAEMON_ARGS="--syslog --inetd --export-all --base-path=/srv/git"

你可以使用 `sudo nano /etc/default/git-daemon` 编辑该文件，确保 `GIT_DAEMON_START=true` 和 `GIT_DAEMON_ARGS` 中包含 `--export-all` 选项，这样可以确保服务端导出 `/srv/git` 目录下的所有仓库。
如果你只想导出 `test.git` 仓库，可以将 `--export-all` 替换为 `--export=/srv/git/test.git`，但使用 `--export-all` 更方便管理多个仓库。
- 保存修改后，重新启动 Git 服务端：

  - `sudo systemctl restart git-daemon.service`

- 检查权限设置：
确保 Git 服务端进程可以访问 `/srv/git/test.git` 仓库，通常 Git 服务端使用 git 用户运行。你可以使用以下命令检查权限：

bash
  - `sudo chown -R git:git /srv/git/test.git`

确保目录和文件的权限允许 Git 服务端进程访问，你可以使用以下命令设置权限：

  - `sudo chmod -R 755 /srv/git/test.git`


## 2.3 结合2.1和2.2最终的配置内容


      # Defaults for git-daemon initscript
      # sourced by /etc/init.d/git-daemon
      # installed at /etc/default/git-daemon by the maintainer scripts

      #
      # This is a POSIX shell fragment
      #

      #2025014. Chaojiang Wu 修改配置
      #GIT_DAEMON_ENABLE=false
      GIT_DAEMON_ENABLE=true

      GIT_DAEMON_START=true

      #GIT_DAEMON_USER=gitdaemon
      GIT_DAEMON_USER=git

      # where to store the pid file
      GIT_DAEMON_PIDFILE=/srv/run/git-daemon.pid

      #GIT_DAEMON_BASE_PATH=/var/lib
      GIT_DAEMON_BASE_PATH=/srv/git

      #GIT_DAEMON_DIRECTORY=/var/lib/git
      GIT_DAEMON_DIRECTORY=/srv/git

      # what port to listen on 
      GIT_DAEMON_PORT=9418

      # what extra args to pass to git daemon
      GIT_DAMEON_ARGS="--syslog --inetd --export-all"

      #20250114. Chaojiang Wu End


      # Additional options that are passed to the Daemon.
      GIT_DAEMON_OPTIONS=""


# 3 如何让别的电脑也可以访问

1. 需要在同一个局域网内，目前通过有线网接入，ip地址为`10.20.210.154`
2. 可提供的git服务端的ip地址为：`git clone git://10.20.210.154/srv/git/test.git`
3. 密码为`HelloGit`
