# MyLinearAlgebra

_——简单易用的 C++ 线性代数库_

![](https://img.shields.io/badge/version-1.0-blue.svg)

### 1. 基本属性

- 名称：MyLinearAlgebra，缩写为 MLA。
- 语言：采用标准 C++ 语言编写，最低兼容版本：ISO C++17 。
- 目标：实现一个简单易用的 C++ 线性代数库。
- 模块：Vector, Matrix.
- 风格：大部分遵循 [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) ，小部分基于项目规模和源码简洁性的考虑采用自己的风格。
- 测试：使用 [GoogleTest](https://github.com/google/googletest) 进行了测试，确保测试全部通过。
- 安全：使用 [Dr. Memory](https://drmemory.org/) 进行了检查，确保没有安全问题。
- 文档：使用 [Doxygen](https://www.doxygen.nl/) 生成文档。

### 2. 使用说明

使用非常方便：直接拷贝整个 Sources 目录到工程目录下然后直接`#include "mla.h"`就可以了。

一些简单的例子：

```cpp
using namespace mla;

// 向量点积
dot(Vector({1, 2, 3}), Vector({4, 5, 6})) // 32
// 向量叉积
cross(Vector({1, 2, 3}), Vector({4, 5, 6})) // [-3 6 -3]
// 向量哈达玛积
Vector({1, 2, 3}) * Vector({4, 5, 6}) // [4 10 18]
// 向量标量积
Vector({1, 2}) * 2 * 0.4 // [0.8 1.6]
// 向量单位化
Vector({1, 1}).unitize() // [0.7071067811865475 0.7071067811865475]

// 矩阵求秩
Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}).rank() // 2
// 矩阵求行列式
Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}).det() // 27
// 矩阵求逆
Matrix({{1, 2}, {3, 4}}).inv() // [-2.0 1.0; 1.5 -0.5]
// 矩阵行/列拓展
Matrix({{1, 2}, {3, 4}}).append_col(Matrix(2, 2, 0)) // [1 2 0 0; 3 4 0 0]
// 矩阵化阶梯形
Matrix({{1, 2, 3}, {4, 5, 6}}).transform_row_echelon() // [1 2 3; 0 -3 -6]
// 矩阵元素映射
Matrix(2, 2, 0).map([](int r, int c, double& e) { e = r + c; }) // [0 1; 1 2]
// 矩阵行/列拆分
Matrix({{1, 2}, {3, 4}, {5, 6}}).split_col(1).first // [1; 3; 5]
// 矩阵加法
Matrix(2, 3, 1) + Matrix(2, 3, 2) // [3 3 3; 3 3 3]
// 矩阵减法
Matrix(2, 3, 1) - Matrix(2, 3, 2) // [-1 -1 -1; -1 -1 -1]
// 矩阵Hadamard乘法
Matrix(2, 3, 1) * Matrix(2, 3, 2) // [2 2 2; 2 2 2]
// 矩阵标量乘法
Matrix(2, 3, 1) * 2 // [2 2 2; 2 2 2]
// 矩阵点乘
dot(Matrix(2, 2, 1), Matrix(2, 2, 2)) // [4 4; 4 4]
```

### 3. 开发历史

这个项目最初是 2021 年底开始写的，当时想了三个方向：符号计算（最开始想的），数值计算（此项目基于此分支重构），快速计算（后期计划）。

这是当初的 README.md：

"""
学考研数学时萌发了写一个计算矩阵的程序，然后就一发不可收拾了。

因为普通的浮点数有误差，我想实现精确运算，就自己设计了分数类。

后来在单位化的时候引入了无理数。想用大数库但是不行，因为无法进行分数幂次运算，它本质上还是数值运算。

要同时实现精确运算和精确表示，只能是符号计算。符号计算就是我之前最开始写的那个，比如输入 $\sqrt{12}$ ，输出 $2\sqrt{3}$ ，不是数字，就是 2 倍根号 3 的数学表示。事实上我已经写完了，而且不仅仅是开根号，而是任意分数次幂的数（比如 $4^{-\frac{3}{2}}$ ）都可以进行计算，并且保证每次运算后都是最简形式。

我完全是自己想的，因为网上根本没有，至少中文互联网上我没找到。各种二级指针各种引用各种 const ，各种拷贝构造、移动构造还有类型转换都要考虑，要把这些基础类做得像内置基本类型一样好用，我把每一个类的运算符重载都写了几十个，整个项目光是运算符重载我就写了几百个。但是两个不同幂次的无理数加起来本质上是一个多项式，就比较复杂，我还计划用降幂排序，当时开发到这里就停滞了，转去练手了。

符号计算和精确计算不一样，精确计算本质还是数值计算，比如 $\sqrt{2}$ 乘以 $\sqrt{3}$ 符号计算就直接显示 $\sqrt{6}$ ，精确计算在有无限小数位的情况下必须需要用户给出有效数字位数然后算到那一位，会用到 Qt 的精确小数计算相关的库。高性能计算就用内置的基本类型，比如 double 就是 IEEE754 的 64 位浮点数，1 位符号位，11 位指数位，52 位尾数位，精确到 52 位 2 进制位。也就是说，精确到 log(2^52)/log(10) = 15.6535597 位 10 进制位。之后会参考 BLAS 写高性能计算。

我打算三个方向选一到两个。后续计划符号计算版本还可以给出计算步骤，比如把一个矩阵化解到阶梯形式或者是行简化行每一个步骤，高斯消元法是怎么做的，都可以给出来，求平方求逆的步骤都可以显示出来，而且是用类似于 LaTeX 那样的公式显示出来，打算用 QWT Text Mathml 那些库。符号计算，全世界好像只有 Mathematica 是老大。快速计算， MATLAB 是老大。这个简单版本既不是符号计算也不是快速计算，只是简单练练手。快速计算需要很多高级算法和计算机底层架构的知识，比如矩阵乘法用 Strassen 算法，以及嵌入汇编 CPU 流水线优化， GPU 加速计算，安全并行计算等等，还要考虑 IEEE754 的 double 精度和上下限问题。

做完一部分之后我特地在网上仔细的找了找，中文互联网上还真没有找到比我这个还完善的。外网上有，但是我最近暂时没时间弄这个项目，以后有空再继续。

目前中国缺少符号计算的软件，我想这个完成之后或许可以填补一些这个空白。比速度我没法比， MATLAB 那是在硬件层面比如 CPU 和多级内存缓存命中以及算法层面进行了大量的、专家级别的、几十年的持续优化，所以速度这个没法比。符号计算也比不过 Mathematica ，也就是 Wolfram Alpha 的后端计算引擎。这些都是有巨大商业价值的国际通用的工业软件。虽然我比不了那些工业软件，但是我也没有想去比较，我只是想写着玩玩，应该很有趣。

里面有一些我值得骄傲的代码。比如无理数精确运算及化简（居然把辗转相除法拓展到了无理数上）以及符号表示（设计符号表示的数据结构真有趣），比如对角化快速计算矩阵幂次和高斯消元法加前导零（居然用到了 STM32 的新特性计算前导零 CLZ ）快速排序化上三角，接着就可以用上三角矩阵计算行列式和秩了。时间复杂度比直接硬算要好很多。

快乐并进步着，我觉得，这才叫劳动嘛！
"""
