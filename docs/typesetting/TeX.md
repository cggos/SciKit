# TeX

* [TeX Users Group (TUG)](http://www.tug.org/)
* [The Com­pre­hen­sive TEX Archive Net­work (CTAN)](https://ctan.org/)
* [LaTeX科技排版工作室](http://www.latexstudio.net/)

* [LaTeX Community](https://latex.org/forum/)
* [LaTeX Tutorial](https://www.latex-tutorial.com)
* [LaTex from WiKiBooks](https://en.wikibooks.org/wiki/LaTeX)
* [LaTeX-materials](https://github.com/BIT-thesis/LaTeX-materials)
* [mathtextutorial (forkosh)](http://www.forkosh.com/mathtextutorial.html): LaTeX Practice Box
* [Overleaf LaTeX Documentation](https://www.overleaf.com/learn/latex/Main_Page)

* LaTeX Algorithms
    - [LaTeX/Algorithms(wikibook)](https://en.wikibooks.org/wiki/LaTeX/Algorithms)
    - [How to write algorithm in Latex](http://shantoroy.com/latex/how-to-write-algorithm-in-latex/)

---

## TeX Editor

### Online Tools

* [Tables Generator](https://www.tablesgenerator.com/): Create LaTeX tables online

* [Upmath](https://upmath.me/): Markdown & LaTeX Online Editor

* [Online LaTeX Equation Editor - LaTeX4technics](https://www.latex4technics.com/)

* [CodeCogs Equation Editor](http://latex.codecogs.com/)


### IDE

* [TeXworks](http://www.tug.org/texworks/)
* [TeXstudio](https://www.texstudio.org/)
* [TeXMaker](http://www.xm1math.net/texmaker/): Free cross-platform LaTeX editor since 2003
* [LyX](https://www.lyx.org/): The Document Processor
* [Overleaf](https://www.overleaf.com/)
* [ShareLaTeX, Online TeX Editor](https://www.sharelatex.com/)
* [Visual Studio Code LaTeX Workshop Extension](https://github.com/James-Yu/LaTeX-Workshop)

### Convertor

* [Mathpix](https://mathpix.com/): Convert images to LaTeX

* [KLatexFormula](https://klatexformula.sourceforge.io/): an easy-to-use graphical application for generating images (that you can drag and drop, copy and paste or save to disk) from LaTeX equations


## TeX发行版

* [各个操作系统下的TeX发行版(清华大学开源软件镜像站)](https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/)

* [TeX Live](http://www.tug.org/texlive/)
* [MiKTeX](https://miktex.org/)
* [Chinese TeX](http://www.ctex.org/HomePage)


## TeX Templates

* [TeXample.net](http://www.texample.net/)

* [LaTeX Templates](http://www.latextemplates.com/)

* [北京理工大学硕士（博士）学位论文LaTeX模板](https://github.com/BIT-thesis/LaTeX-template)


## TeX on ubuntu

* [Ubuntu下部署Latex编译环境](http://ptbsare.org/2014/05/12/ubuntu%E4%B8%8B%E9%83%A8%E7%BD%B2latex%E7%BC%96%E8%AF%91%E7%8E%AF%E5%A2%83/#1_-从源里面安装)

```sh
sudo apt install texlive-full

# optional
# 安装中文字体包，字体包中包含bsmi，bkai，gkai，gbsn四种中文字体
# bsmi和bkai是Big5编码的宋体和楷体字；后两者gkai和gbsn分别处理简体中文楷体字和宋体字
sudo apt install latex-cjk-all
```

* ubuntu 16.04下的latex的section没有编号的问题
    - 从 https://www.ctan.org/tex-archive/macros/latex/contrib/titlesec 下载解压到 `/usr/share/texlive/texmf-dist/tex/latex`

* tlmgr
  ```sh
  sudo mktexlsr

  tlmgr init-usertree
  tlmgr update --list # sudo apt install xzdec
  tlmgr --gui # sudo apt install perl-tk

  # 永久更改镜像源
  tlmgr option repository https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/texlive/tlnet

  # 临时切换镜像源
  tlmgr update --all --repository \
    https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/texlive/tlnet
  ```


## TeX with Make

example: [jlblancoc/tutorial-se3-manifold](https://github.com/jlblancoc/tutorial-se3-manifold)

Prerequisites in Ubuntu:

```sh
sudo apt install latexmk texlive texlive-science
```

Build PDF with:

```sh
make
```

```makefile title="Makefile"
# From: http://tex.stackexchange.com/questions/40738/how-to-properly-make-a-latex-project
# You want latexmk to *always* run, because make does not have all the info.
.PHONY: out.pdf

# First rule should always be the default "all" rule, so both "make all" and
# "make" will invoke it.
all: out.pdf

# MAIN LATEXMK RULE

# -pdf tells latexmk to generate PDF directly (instead of DVI).
# -pdflatex="" tells latexmk to call a specific backend with specific options.
# -use-make tells latexmk to call make for generating missing files.

# -interactive=nonstopmode keeps the pdflatex backend from stopping at a
# missing file reference and interactively asking you for an alternative.

out.pdf: in.tex
	latexmk -pdf -pdflatex="pdflatex -interactive=nonstopmode" -bibtex -use-make in.tex

clean:
	latexmk -CA
```

## TeX with Math Graphics

* [jPicEdt](http://jpicedt.sourceforge.net/site/index.php)
* [The Ipe extensible drawing editor](http://ipe.otfried.org/)
* [MetaPost (TUG)](https://tug.org/metapost.html)

### TikZ & PGF

* [Latex--TikZ和PGF--高级文本绘图，思维绘图，想到--得到！](https://www.cnblogs.com/tsingke/p/6649800.html)

* [TikZ and PGF](http://www.texample.net/tikz/) are TeX packages for creating graphics programmatically

* [TikzEdt](http://www.tikzedt.org/) is a combined WYSIWYG/text editor designed for editing Tikz code

* [matlab2tikz/matlab2tikz](https://github.com/matlab2tikz/matlab2tikz): converts MATLAB®/Octave figures to TikZ/pgfplots figures for smooth integration into LaTeX

* [tikz-bayesnet](https://github.com/jluttine/tikz-bayesnet): TikZ library for drawing Bayesian networks, graphical models and (directed) factor graphs in LaTeX.

* with **Inkscape**
    - [svg2tikz](https://github.com/kjellmf/svg2tikz): a set of tools for converting SVG graphics to TikZ/PGF code
    - [TexText](https://textext.github.io/textext/): Re-editable LaTeX graphics for Inkscape


## Apps

### Beamer Slides with LaTeX

* [Urinx/LaTeX-PPT-Template](https://github.com/Urinx/LaTeX-PPT-Template): Seven awesome latex ppt templates for researchers or students
* [beamer-theme-matrix](https://hartwork.org/beamer-theme-matrix/)
* [slides](https://github.com/wzpan/wzpan.github.io/wiki/slides)

### Curriculum Vitæ with TeX

* [Writing the curriculum vitæ with LaTeX](http://tug.org/pracjourn/2007-4/mori/)
* [moderncv 的笔记](https://www.xiangsun.org/tex/notes-on-moderncv)
