# 安装

sudo ./bjam "-sTOOLS=gcc" "--includedir=/usr/include" "--libdir=/usr/local/lib" install

你提供的命令是使用 bjam 工具来构建和安装软件的命令。bjam 是 Boost.Build 的构建工具，用于构建 C++ 项目。以下是对命令中各个部分的解释：

命令解释
- sudo：

使用 sudo 是为了以管理员权限运行命令，通常是因为安装过程需要写入系统目录（如 /usr/local/lib）。
- ./bjam：

bjam 是 Boost.Build 的构建工具，用于根据项目的构建脚本（通常是 Jamfile 或 Jamroot 文件）来编译和安装软件。
"-sTOOLS=gcc"：

- -s 是设置变量的选项。这里设置 TOOLS 变量为 gcc，表示使用 GCC 编译器来编译项目。
这个选项告诉 bjam 使用 GCC 作为编译工具链。
"--includedir=/usr/include"：

- --includedir 是指定头文件安装目录的选项。这里指定头文件将被安装到 /usr/include 目录。
这个选项告诉 bjam 在安装过程中将头文件复制到指定的目录。
"--libdir=/usr/local/lib"：

- --libdir 是指定库文件安装目录的选项。这里指定库文件将被安装到 /usr/local/lib 目录。
这个选项告诉 bjam 在安装过程中将库文件复制到指定的目录。
install：

- install 是 bjam 的一个目标，表示执行安装操作。它会根据项目的构建脚本将编译后的文件安装到指定的目录。