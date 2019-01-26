# 第1章-计算机系统漫游

## 程序被其他程序翻译成不同的格式

- GCC编译器驱动程序读取源程序文件，并把它翻译成一个可执行目标文件。这个翻译过程可分为4个阶段（预处理阶段，编译阶段，汇编阶段，链接阶段）完成，这4个阶段的程序（预处理器，编译器，汇编器，链接器）一起构成了编译系统。
- 预处理阶段。预处理器（cpp）根据以字符`#`开头的命令，修改原始的C程序。经过预处理器处理的文件以`.i`作为文件扩展名。
  - 可以通过`gcc -E hello.c -o hello.i`获取预处理后的文件。
- 编译阶段。编译器（ccl）讲文本文件`hello.i`翻译成文本文件`hello.s`，包含一个汇编语言程序。
  - 可以通过`gcc -S hello.i -o hello.s`获取编译后的汇编文件。
- 汇编阶段。汇编器（as）将`hello.s`翻译成机器语言指令，把这些机器语言指令打包成一种==可重定位目标程序（relocatable object program）==的格式，并将结果保存到目标文件`hello.o`中`hello.o`文件是一个二进制文件。
  - 可以通过`gcc -c hello.s -o hello.o`获取汇编后的二进制文件。
- 链接阶段。链接器（ld）负责合并了将`printf.o`文件合并到`hello.o`程序中，结果得到了`hello`文件，它是一个==可执行目标文件==，可以被加载到内存中，由系统执行
  - 可以通过`gcc hello.o -o hello`获得链接后的可执行文件

## 处理器读并解释存储在内存的指令

### 系统的硬件组成

- 总线，它携带信息字节并负责在各个部件间传递。
  - 总线常常被设计为传送定长的字节块，也就是字（word）。字中的字节数（即字长）是一个基本的系统参数，各个系统都不尽相同。
  - 现在大多数机器字长要么是4个字节，要么是8个字节。
- I/O设备，是系统于外部时间联系的通道。
  - 每个I/O设备都通过一个控制器或适配器与I/O总线相连。
- 主存，它是一个临时存储设备。
  - 从物理上来说，主存是一个由一组动态随机存取存储器（DRAM）芯片组成的。
  - 从逻辑上来说，存储器是一个线性的字节数组，每个字节都有其唯一的地址（数组索引）。
- 处理器（中央处理单元），是解释存储在主存中指令的引擎，处理器的核心是一个大小为一个字的存储设备（或寄存器），称为程序计数器（PC）。
  - 任何时刻，PC都指向主存中的某条机器语言指令（即含有该条指令的地址）。
  - 寄存器文件是一个小的存储设备，由一些单个字长的寄存器组成，每个寄存器都有唯一的名字。逻辑单元（ALU）计算新的数据和地址值。
  - CPU在指令的要求下可能会执行下列操作
    - 加载：从主存复制一个字节或一个字到寄存器，以覆盖原来的内容。
    - 存储：从寄存器复制一个字节或者一个字到主存的某个位置，以覆盖这个位置上原来的内容。
    - 操作：把两个寄存器的内容复制到逻辑单元（ALU），ALU对这两个字做算术运算，并将结果放到一个寄存器中，以覆盖该寄存器中原来的内容。
    - 跳转：从指令本身中抽取一个字，并将这个字复制到程序计数器（PC）中，以覆盖PC中原来的值。

## 高速缓存至关重要

- 针对处理器与主存之间的差异，系统设计者采用了更小更快的存储设备，称为高速缓存存储器（cache memory），简称高速缓存。
- 位于处理器芯片上的L1高速缓存的容量可以达到数万字节，访问速度几乎和访问寄存器文件一样快。
- 一个容量为数十万到数百万字节的更大的L2高速缓存通过一条特殊的总线连接到处理器。进程通过访问L2高速缓存的时间要比访问L1高速缓存的时间长5倍，但这仍比访问主存的时间快5~10倍。
- L1和L2高速缓存是用一种叫做静态随机访问存储器（SRAM）的硬件技术实现的。

## 操作系统管理硬件

- 操作系统有两个基本功能
  - 防止硬件被失控的应用程序滥用。
  - 向应用程序提供简单一致的机制来控制复杂而又通常大不相同的低级硬件设备。
- 操作系统通过几个基本的抽象概念来实现这两个功能。
  - 进程：对处理器、主存和I/O设备的抽象表示。
  - 虚拟内存：对主存和磁盘I/O设备的抽象表示。
  - 文件：文件是对I/O设备的抽象表示。

### 进程

- 进程是操作系统对一个正在运行的程序的一种抽象。
- 一个系统上可以运行多个进程，而每个进程都好像在独占使用硬件。
- 并发运行，则是说一个进程的指令和另一个进程的指令是交错执行的。
- 无论是在单核还是多核系统中，一个CPU看上去都像是在并发地执行多个进程，这是处理器在进程间切换来实现的。
- 操作系统实现这种交错执行的机制称为==上下文切换==。
- 操作系统保持和跟踪==进程运行所需的所有状态信息==。这种状态，称为==上下文==。
- 在任何一个时刻，单处理器系统都只能执行一个进程的代码。
- 当操作系统决定要把控制权从当前进程转移到某个新进程时，就会进行==上下文切换==，即保存当前进程的上下文，恢复新进程的上下文，然后将控制权传递到新进程。
- 从一个进程到另一个进程的转换是由==操作系统的内核（kernel）==管理的。
- 内核是操作系统代码常驻主存的部分，当应用程序需要操作系统的某些操作时，比如读写文件，它就是执行一条特殊的系统调用（system call）指令，将控制权传递给内核，然后内核执行被请求的操作并返回应用程序。
- 内核不是一个独立的进程，它是系统管理全部进程所用代码和数据结构的集合。

### 线程

- 在现代操作系统中，一个进程实际上可以由多个称为线程的执行单元组成。
- 每个线程都运行在==进程的上下文==中，并==共享同样的代码和全局数据==。

### 虚拟内存

- 虚拟内存是一个抽象概念，它为每个进程提供了一个假象，即每个进程都在独占地使用主存。
- 每个进程看到的内存都是一致的，称为==虚拟 地址空间==。
- 进程的虚拟地址空间
  - 程序代码和数据。
  - 堆。
  - 共享库。
  - 栈，位于用户虚拟地址空间顶部是用户栈，编译器用它来实现函数调用。
  - 内核虚拟内存。地址空间顶部的区域是为内核保留的。不允许应用程序读写这个区域的内容或者直接调用内核代码定义的函数。

### 文件

- 文件就是字节序列。
- 每个I/O设备，包括磁盘，键盘，显示器甚至网络，都可以看成是文件。

## 重要主题

### Amdahl定律

- 对系统的某个部分加速时，其对系统整体性能的影响取决于==该部分的重要性和加速程度==。

- 若系统执行某应用程序所需时间为$T_{old}$。假设系统某部分所需执行时间与系统所需执行时间的比例为a，而该部分性能提升比例为k。即该部分初始所需执行时间为$aT_{old}$，系统其他部分所需执行时间为$(1-a)T_{old}$。该部分现在所需的时间为$aT_{old}/k$。因此，总的执行时间为
  $$
  T_new = (1 - a)T_{old} + (aT_{old}) / k = T_{old}[ (1 - a) + a/k ]
  $$

- 由此，计算加速比$S = T_{old} / T_{new}$为
  $$
  S = \frac{1}{(1 - a) + a/k}
  $$


### 并发和并行

- 并发（concurrency）指一个同时具有多个活动的系统。
- 并行（parallelism）指的是使用并发来使一个系统运行得更快。并行可以在计算机系统的多个抽象层次上使用。
- 多核处理器是将多个CPU（称为核）集成到一个集成电路芯片上。每个核都有自己的L1和L2高速缓存。
- 超线程，有时候称为多线程（simultaneous multi-threading）是一项允许一个CPU执行多个控制流的技术。
- 多核处理器的使用可以从两方面提高系统性能。
  - 它减少了在执行多个任务时模拟并发的需要。
  - 它可以使应用程序运行得更快，要求程序以多线程方式来书写。
- 在较低的抽象层次上，现代处理器可以同时执行多条指令的属性称为指令级并行。
- 如果处理器可以达到比一个周期一条指令更快的执行速率，就称之为超标量（super-scalar）处理器。
- 在最低层次上，许多现代处理器拥有特殊的硬件，允许一条指令产生多个可以并行执行的操作，这种方式称为单指令、多数据，即SIMD并行。

### 计算机系统中抽象的重要性

- 文件是对I/O设备的抽象。
- 虚拟内存是对程序存储器的抽象。
- 进程是对一个正在运行的程序的抽象。
- 虚拟机是对整个计算机的抽象，包括操作系统、处理器和程序。