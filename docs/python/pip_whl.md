# pip & wheel

* [pip](https://pip.pypa.io/en/stable/): The PyPA recommended tool for installing Python packages

* [wheel](https://wheel.readthedocs.io/en/latest/) is the reference implementation of the Python wheel packaging standard

  - [Python Wheels](https://pythonwheels.com/)

---

[TOC]

## pip

* 配置 国内源

  ```ini title="~/.pip/pip.conf"
  [global]
  trusted-host =  pypi.douban.com
  index-url = http://pypi.douban.com/simple
  ```

* install
  ```sh
  pip install -i https://pypi.tuna.tsinghua.edu.cn/simple <package-name>
  ```

## wheel

