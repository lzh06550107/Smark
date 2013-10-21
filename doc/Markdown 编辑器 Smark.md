# Markdown 编辑器 Smark 

## Smark 的设计

Smark 的界面分为阅读、编辑和预览三种模式：

 + `阅读模式` ：Smark 默认以阅读模式打开 Markdown 文件，该模式只显示一个只读 HTML 视图，不显示 Markdown 文件内容。

 + `编辑模式` ：该模式主要用于编辑 Markdown 内容，只显示 Smark 的 Markdown 编辑器，而不显示 HTML 视图，配合全屏的话就相当于 `Gtihub` 的 `ZenMode`，可以作为一个 “专心致志写作软件”。

 + `预览模式` ：该模式并列显示 HTML 视图和 Markdown 编辑器，用于实时预览 Markdown 内容的 HTML 显示。

可在 `视图` 菜单栏中方便切换这些显示模式，Smark 以阅读模式为基础模式，按 `Esc` 键可从任意模式回至阅读模式。Smark 尽可能的简化用户的操作，为此进行了许多细致的设计：

 + `自动调整布局` ：在预览模式下，Smark 经根据窗口的长宽比自动调整 HTML 视图和 Markdown 编辑器的布局（垂直布局和水平布局，包括 CSS 编辑器的布局）以达到最佳视觉效果；

 + `绝不乱弹窗` ：我非常烦在不同的窗口间换来换去，因此 Smark 中的 查找对话框 和 CSS 编辑器等都嵌在主窗口中，Smark 经根据用户的操作自动显示相应部件并切换焦点，当您想隐藏这些部件时，万能的 `Esc` 键永远可以满足你的要求；

 +  `HTML 视图和 Markdown 编辑器的垂直滚动` ：您只负责编辑内容，同步滚动这种事情交给 Smark 干就行了；

 + `完备的快捷键` ：我是一个键盘党，所以扔掉鼠标吧，键盘就行了；

 + `Markdown 语法高亮` ：这个正在整，在 Smark 1.1 版本中将正式实现

 + `自定义 CSS` ：虽然自认为 Smark 中默认的 CSS 已经够漂亮了，不过我相信您能创造出更漂亮的 CSS ；

## Smark 快捷键列表

 + 全局

        + `Esc`              : 隐藏 查找 / CSS 编辑 / Markdown 编辑部件
        + `Tab`              : 增加所选诸行的缩进（四个空格）
        + `Ctrl + Tab`       : 减小所选诸行的缩进（四个空格）

 + 文件菜单

        + `Ctrl + N`         : 新建 markdown 文件
        + `Ctrl + O`         : 打开 markdown 文件
        + `Ctrl + S`         : 保存当前 markdown 文件
        + `Ctrl + Shift + S` : 当前 markdown 文件另存为
        + `Ctrl + W`         : 关闭当前 markdown 文件
        + `Ctrl + Q`         : 退出 Smark 

 + 视图菜单

        + `F6`               : 预览模式视图
        + `F7`               : 阅读模式视图
        + `F8`               : 编辑模式视图
        + `F11`              : 进入 / 退出全屏显示


 + 编辑菜单

        + `F5`               : 刷新 HTML 显示
        + `Ctrl + C`         : 复制
        + `Ctrl + X`         : 剪切
        + `Ctrl + P`         : 粘贴
        + `Ctrl + F`         : 查找
        + `Ctrl + Z`         : 撤消
        + `Ctrl + Y`         : 重做
        + `Ctrl + G`         : 编辑 CSS

 + 插入菜单

        + `Ctrl + I`         : 插入图片
        + `Ctrl + L`         : 插入链接
        + `Ctrl + M`         : 插入数学公式

 + 格式菜单

        + `Ctrl + B`         : 加粗
        + `Ctrl + I`         : 倾斜
        + `Ctrl + U`         : 下划线
        + `Ctrl + ``         : 代码
        + `Ctrl + '`         : 引用
        + `Ctrl + Down`      : 下标
        + `Ctrl + Up`        : 上标
        + `Ctrl + ]`         : 加大字号
        + `Ctrl + [`         : 减小字号

## 运行截屏

<p align="center">
    <img src="./file/win7-readme-read-mode.png" width="90%">
    <p align="center">Win7 下阅读模式的 Smark 显示</p>
</p>

<p align="center">
    <img src="./file/ubuntu-readme-edit-mode.png" width="90%">
    <p align="center">Ubuntu 下编辑模式的 Smark 显示</p>
</p>

<p align="center">
    <img src="./file/win7-readme-preview-hor-mode.png" width="100%">
    <p align="center">Win7 下水平布局的预览模式的 Smark 显示</p>
</p>

<p align="center">
    <img src="./file/ubuntu-readme-preview-ver-mode.png" width="70%">
    <p align="center">Ubuntu  下垂直布局的预览模式的 Smark 显示</p>
</p>