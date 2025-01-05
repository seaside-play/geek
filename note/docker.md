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