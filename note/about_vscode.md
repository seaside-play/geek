# 1 launch.json和tasks.json的区别是什么在vscode中？

在Visual Studio Code（VSCode）中，launch.json和tasks.json文件都用于配置开发和调试任务，但它们的用途和功能有所不同：

## 1.1 launch.json
- 用途：用于配置调试任务。
- 功能：
  - 定义调试会话的启动配置，例如选择调试器、设置启动参数、环境变量等。
  - 可以配置多个调试配置，允许用户在不同的调试场景下快速切换。
  - 支持各种语言和框架的调试器配置，如C++、Python、JavaScript等。
  - 可以与tasks.json中的任务结合使用，例如在启动调试之前先运行构建任务。
## 1.2 tasks.json
- 用途：用于配置构建和运行任务。
- 功能：
  - 定义在VSCode中执行的自定义任务，例如编译代码、运行脚本、执行测试等。
  - 可以配置任务的名称、命令、参数、工作目录等。
  - 支持任务的依赖关系，允许一个任务在另一个任务完成后自动执行。
  - 可以配置任务的触发方式，例如在保存文件时自动运行或通过快捷键触发。
## 1.3 总结
- launch.json主要关注调试过程中的配置，如启动调试器、设置断点等。
- tasks.json主要关注构建和运行过程中的配置，如编译代码、执行脚本等。

在实际开发中，通常会将两者结合使用，例如先通过tasks.json配置编译任务，然后在launch.json中配置调试任务，并在调试配置中引用编译任务，以实现“编译-调试”一体化的工作流程。  

# 2 Ubuntu版本和GCC版本

- `cat /etc/issue`: 查看Ubuntu版本
- `g++ --version`: 查看G++版本，目前的Ubuntu24.04是 13.02
- `g++ 13.02支持的C++`：
  - `C++98`：完全支持
  - `C++11`：完全支持
  - `C++14`：完全支持
  - `C++17`：完全支持，并且是 GCC 11 到 13 版本的默认模式
  - `C++20`：支持大部分特性
  - `C++23`：支持一些特性，但标准仍在开发中
# 3 使用clangd进行代码补全

在Ubuntu 24.04中，在VSCode中实现clangd的步骤如下：

- `sudo apt install clangd`:安装clangd服务器
- `clangd`：打开VSCode，安装插件clangd
- `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`:在`CMakeLists.txt`添加该变量，生成 `compile_commands.json`文件
- `--compile-commands-dir=${workspaceFolder}/build`:打开VSCode的设置（Settings），搜索“clangd: arguments”。

        "clangd.arguments": [
          "--background-index",
          "--log=error",
          "--header-insertion=never",
          "--clang-tidy",
          "--cross-file-rename=true",
          "--compile-commands-dir=${workspaceFolder}/build"
        ],

- 打开您的C/C++项目目录，clangd将自动读取compile_commands.json文件并提供代码补全、错误检测等功能。如果您遇到任何问题，可以检查clangd的日志以获取更多信息