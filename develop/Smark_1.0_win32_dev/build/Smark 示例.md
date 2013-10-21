# Smark 测试

## 文本格式测试

下面的文字引用自 [Pandoc’s Markdown 语法中文翻译](http://pages.tzengyuxio.me/pandoc/)

 Markdown 是针对易于书写与阅读的目标而设计的，特别是在易于阅读这点上尤为重要：

 > 一份Markdown格式的文件应该要能以纯文字形式直接发表，并且一眼看过去不存在任何标记用的标签或格式指令。John Gruber 这项原则同样也是 pandoc 在制订表格、脚注以及其他扩充的语法时，所依循的规范。

 然而，pandoc 的目标与原始markdown 的最初目标有着方向性的不同。在markdown 原本的设计中，HTML 是其主要输出对象；然而pandoc 则是针对多种输出格式而设计。因此，虽然pandoc 同样也允许直接嵌入HTML 标签，但并不鼓励这样的作法，取而代之的是pandoc 提供了许多非HTML 的方式，来让使用者输入像是定义清单、表格、数学公式以及脚注等诸如此类的重要文件元素。

This ~~is deleted text.~~

H~2~O is a liquid.  2^10^ is 1024.

What is the difference between `>>=` and `>>`?

> 块段引用测试
>
>> Pandoc 本身是由 John MacFarlane 所開發的文件轉換工具，可以在 HTML, Markdown, PDF, TeX…等等格式之間進行轉換。有許多喜歡純文字編輯的人，利用 Pandoc 來進行論文的撰寫或投影片製作。但除了轉換的功能外，Pandoc 所定義的 Markdown 擴充語法也是這套工具的一大亮點，在 Pandoc 的官方使用說明文件中，光是其針對 Markdown 格式的擴充就佔了整整一半左右的篇幅。

下面是代码段测试

    <p align="center">
        <img src="../src/RS/LOGO.png" width="20%">
        <br>
        <small> Smark LOGO </small>
    </p>

## 列表测试

+ First
+ Second:
    - Fee
    - Fie
    - Foe
         1. 第一项
         2. 第二项
         3. 第三项
         4. 第四项

+ Third

## 表格测试

: 表格测试

+---------------+---------------+--------------------+
| Fruit         | Price         | Advantages         |
+===============+===============+====================+
| Bananas       | $1.34         | - built-in wrapper |
|               |               | - bright color     |
+---------------+---------------+--------------------+
| Oranges       | $2.10         | - cures scurvy     |
|               |               | - tasty            |
+---------------+---------------+--------------------+

## 图片与超链接测试

　下面是 Smark 的LOGO：

<p align="center">
    <img src="../src/RS/LOGO.png" width="20%">
    <br>
    <small> Smark LOGO </small>
</p>

　这里是[Pandoc’s Markdown 语法中文翻译](http://pages.tzengyuxio.me/pandoc/)的超链接

## 脚注测试

  下面是脚注测试：

Here is a footnote reference,[^1] and another.[^longnote]

[^1]: Here is the footnote.

[^longnote]: Here's one with multiple blocks.

    Subsequent paragraphs are indented to show that they
belong to the previous footnote.

        { some.code }

    The whole paragraph can be indented, or just the first
    line.  In this way, multi-paragraph footnotes work like
    multi-paragraph list items.

This paragraph won't be part of the note, because it
isn't indented.

 链接型脚注测试：

**NOTE:** You can find more information:

 - about **Markdown** syntax [here][2],
 - about **Markdown Extra** extension [here][3],
 - about **Prettify** syntax highlighting [here][4],
 - about **Latex** mathematical expressions [here][5].

  [1]: http://math.stackexchange.com/
  [2]: http://daringfireball.net/projects/markdown/syntax "Markdown"
  [3]: http://michelf.ca/projects/php-markdown/extra/ "Markdown Extra"
  [4]: https://code.google.com/p/google-code-prettify/
  [5]: http://en.wikibooks.org/wiki/LaTeX/Mathematics

## MathJax 数学公式测试

You can include **Latex** expressions to render mathematical formulas using [MathJax](math.stackexchange.com):

$$ \Gamma(z) = \int_0^\infty t^{z-1}e^{-t}dt\,. $$
$$ E = mc^2 $$
$$ e^{i\pi} - 1 = 0 $$

