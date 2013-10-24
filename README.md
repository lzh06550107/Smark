# Smark -- A Simple Markdown Editor

<p><img align="right" src="./doc/file/logo.png" width="150"></p>

## What's Smark ?

只是为了方便使用，没什么新奇的东西。我使用 [pandoc](http://johnmacfarlane.net/pandoc/) 来转化 `markdown`，但是我不想在修改文件时总是在编辑器、文字终端和浏览器间换来换去，因此我写了一个简单的编辑器，它在后台调用 `pandoc` 将当前编辑的 `markdown` 内容转化为 `HTML`，而后将 `HTML` 在 `smark` 中的浏览器中显示出来。并为常见的格式编辑等提供了方便的快捷键等（从 [项目 wiki](https://github.com/elerao/Smark/wiki) 中了解更多），就遵循 [LGPL](http://www.gnu.org/copyleft/gpl.html) 罢了，只是个小工具而已。

## Dependent packages

 + [`pandoc`](http://johnmacfarlane.net/pandoc/)
 + [`Qt 4.8`](http://qt-project.org/)
  
## Links

 + 主页 : [https://github.com/elerao/Smark](https://github.com/elerao/Smark)
 + Wiki : [https://github.com/elerao/Smark/wiki](https://github.com/elerao/Smark/wiki)
 + 联系 : [elerao.ao@gmail.com](elerao.ao@gmail.com)

## Install Smark

### For Windows

 1. 下载 `[./install]` 路径下的 [pandoc-1.11.1.msi](./pandoc-1.11.1.msi) 和 [smark_1.0_win32_portable.zip](./smark_1.0_win32_portable.zip);
 2. 运行 [pandoc-1.11.1.msi](./pandoc-1.11.1.msi) 安装 `pandoc`;
 2. 解压 [smark_1.0_win32_portable.zip](./smark_1.0_win32_portable.zip) 到你想安装的路径下;
 3. 运行 `smark.exe`，自己设置相关文件的打开方式!

### For Anywhere

 1. 安装依赖的程序包:

        $ sudo apt-get install qtsdk
        $ sudo apt-get install pandoc

    如果你不使用 `apt-get` 作为软件包管理器，自己谷歌搜索如何安装这两个程序包

 2. 下载 `[./develop]` 路径下的源码，解压并编译源码:

        $ qmake -project
        $ qmake
        $ make

 3. 把 `[./build]` 路径下的 `smark-dev` 移动到你的 `[bin]` 路径下即可

## 运行截屏

<p align="center">
    <img src="https://raw.github.com/elerao/Smark/master/doc/file/win7-readme-read-mode.png" width="80%">
    <p align="center">Win7 下阅读模式的 Smark 显示</p>
</p>

<p align="center">
    <img src="https://raw.github.com/elerao/Smark/master/doc/file/ubuntu-readme-preview-ver-mode.png" width="80%">
    <p align="center">Ubuntu  下垂直布局的预览模式的 Smark 显示</p>
</p>
 
