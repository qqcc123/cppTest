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

/*
https://oicebot.github.io/2020/03/20/c-compilers-explained.html (c++编译链接过程)
*/

/*
std::forward是C++标准库中的一个模板函数，它用于将参数按照原类型进行转发，主要在函数模板中使用。
它的实现主要使用模板特化和引用折叠特性，一般如下所示：
template <class T>
T&& forward(typename std::remove_reference<T>::type& param) noexcept {
    return static_cast<T&&>(param);
}

template <class T>
T&& forward(typename std::remove_reference<T>::type&& param) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward call");
    return static_cast<T&&>(param);
}

上述代码中，std::remove_reference<T>::type用于去掉类型T的引用，返回裸类型。这里的两个forward函数模板，根据不同的参数类型，进行模板特化。第一个版本用于处理左值引用，第二个版本用于处理右值引用。
两者都通过static_cast<T&&>实现类型的转换，并返回转换后的引用。

noexcept 是 C++11 引入的新特性，表示该函数保证不会抛出异常。static_assert 对编译期进行断言检查。
要理解std::forward的运作原理，需要理解引用折叠、类型萃取和模板特化等一些高级的C++特性。


实际上，std::forward中的这个函数的参数 std::remove_reference<T>::type&& param 并不是万能引用，但它确实与引用折叠和模板参数的类型推导有关。当你看到 T&& 的形式时，它有可能表示万能引用，也有可能表示右值引用，
关键在于 T 的类型是怎么确定的。如果 T 是模板参数，且这个类型是由编译器在模板实例化时推导得出的，那么 T&& 就是万能引用。而如果 T 的类型是明确指定的，那么 T&& 就表示右值引用。


比如我们看以下代码：
template<typename T> void foo(T&& param); // 此处的 T&& 是万能引用
int x = 27;
foo(x); // T 推导为 int&，然后 T&& 为 int& 的引用，根据引用折叠规则，此处 T&& 表示 int&

而针对 std::forward：
template<class T>
T&& forward(typename std::remove_reference<T>::type&& param) noexcept;

这里的 T 是之前已经确定的，是调用者指定的参数。本质上 std::remove_reference<T>::type&& param 是在保证输入的参数一律视为右值的情况下（type&&），再通过引用折叠（T&& forward(...) ）重新恢复其原本的性质（到底是左值还是右值）
，这样就能实现完美转发。所以，尽管 std::forward 中有 T&& 这样的形式，但它并不是万能引用，也没有发生类型的推导，而是利用了右值引用和引用折叠的规则。

*/


/*
你不能直接将一个左值传递给仅接受右值引用的函数，因为这是语言设计的结果，目的是防止使用者错误地修改他们原本没有意图修改的数据。但是，如果你确实有必要这样做，你可以通过std::move将左值显式转换为右值以传递给函数。这里是一个例子：


#include <utility> // for std::move

class MyClass {
public:
    void functionTakingRvalueRef(MyClass&& obj) {
        // your code here
    }
};

int main() {
    MyClass obj;
    MyClass instance;
    instance.functionTakingRvalueRef(std::move(obj));  // 我们将obj左值转成右值
    return 0;
}

std::move 的作用是将其参数强制转换（cast）为右值（具体来说是xvalue，一种特殊的右值），但必须注意，使用std::move后，原对象可能会处于不可预知的状态，因为其资源可能已经转移出去。因此，除非你明确知道自己在做什么，否则你应该避免这样做。


注意，上面这段代码中的 MyClass obj; 创建了一个名为 obj 的左值。但 std::move(obj); 将其转化为右值，使得我们可以将其传递给 functionTakingRvalueRef 方法。


然而，C++标准中并没有“重载右值引用符”的概念。你不能像重载操作符一样重载引用。这是因为引用自身并不是一个操作，而是一种数据类型。上述的 std::move 函数可以将左值“强制转换”为右值，但这并不算是“重载”
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEventLoop w;
    w.show();
    int code = a.exec();
    return code;
}
