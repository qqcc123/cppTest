#include "QtEventLoop.h"
#include <QtWidgets/QApplication>

/*
Qmake是Qt开发环境中的一个重要工具，主要用于自动处理构建过程。其主要工作是自动生成 Makefile 文件，这些文件描述了源代码文件之间的依赖关系以及如何生成可执行文件。
在使用Qmake时，你会创建一个项目文件（.pro）文件，里面描述了你的项目的各种信息，例如项目中包含哪些源文件、头文件、UI文件、资源文件等，还可以包括一些特殊的构建和配置选项。
当你运行 Qmake 时，它会读取你的 .pro 文件，然后生成对应平台（比如Unix, Windows, macOS等）和编译器的 Makefile 文件。然后，这些 Makefile 文件可以被 make 命令或其他构建工具
使用，来进行编译和链接，生成最终的可执行文件或库文件。总的来说，Qmake 是一个构建工具，也可以看作是构建系统的管理工具，它的主要工作就是处理和管理构建过程中的各种任务，帮助
开发者更方便的编译和构建他们的 Qt 项目。

MOC 预处理：当你的 Qt 项目构建时，qmake 会生成 makefile，并且 qmake 会检测到含有 Q_OBJECT 宏的头文件，为其产生 moc 指令，然后 make(或 cmake 等等) 执行 makefile 这一步时，
会调用 MOC 对含有 Q_OBJECT 的类进行预处理，为其生成一个 moc 文件，这个文件包含了 MyClass 类的元对象信息。编译链接：然后再编译这个生成的 moc 文件和其他源文件，进行链接，
生成最终的可执行文件。在最终的可执行文件中，你的类（例如 MyClass）就具有了 Qt 所需要的元对象特性，例如信号和槽等等。
*/

/*
静态加载和动态加载 DLL，导入的地址是可以不一样的。对于静态加载的 DLL，当程序启动时，Windows 操作系统会自动加载 DLL，并进行地址绑定，将程序中的函数和变量引用链接到 DLL 的实际内存地址。
这个地址是由操作系统的内存管理模块在程序启动时确定的，并且在程序的整个生命周期内保持不变。对于动态加载的 DLL，当调用 LoadLibrary 函数加载 DLL 时，Windows 操作系统会找到一个适合的内存
区域来加载 DLL，并返回 DLL 的基址。然后，当调用 GetProcAddress 函数获取函数地址时，这个地址实际上是 DLL 基址加上函数在 DLL 中的偏移。这个地址在每次调用 LoadLibrary 和 FreeLibrary 时
可能会改变，因为每次加载 DLL 可能使用不同的内存区域。
因此，静态加载和动态加载 DLL 的地址可能并不相同，具体取决于操作系统的内存管理策略和程序的调用情况。
*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEventLoop w;
    w.show();
    int code = a.exec();
    return code;
}
