// (一).字符指针
// (二).指针数组
// (三).数组指针
// (四).数组参数和指针参数
// (五).函数指针
// (六).函数指针数组
// (七).指向函数指针数组的指针
// (八).回调函数
// (九).指针和数组面试题目的解析

// ##########################################################
// (六).函数指针数组
// ##########################################################

// 函数指针数组:一个数组,其中的每个元素都是函数指针
// 用途:用于实现回调函数表、状态机、命令模式等

// 我们首先模拟一个计算器的程序:

// ----------------------------------------------------------
// 原始版本:使用switch-case,代码重复
// ----------------------------------------------------------

#include <stdio.h>

// 计算器菜单函数 - 显示操作选项
void menu1()
{
    printf("***********************************\n");
    printf("***********************************\n");
    printf("*********** 1.add  2.sub **********\n");
    printf("*********** 3.mul  4.div **********\n");
    printf("*********** 0.exit      ***********\n");
    printf("***********************************\n");
    printf("***********************************\n");
}

// 四个算术运算函数定义
int add1(int x, int y)
{
    return x + y;
}
int sub1(int x, int y)
{
    return x - y;
}
int mul1(int x, int y)
{
    return x * y;
}
int div1(int x, int y)
{
    return x / y;
}

// 原始版本的计算器 - 使用switch case
// 缺点:代码重复,每个case中都有相似的输入输出逻辑
int main1()
{
    int input = 0;
    int x = 0;
    int y = 0;
    int res = 0;

    // 使用do-while循环实现持续计算直到用户选择退出
    do
    {
        menu1(); // 显示菜单
        printf("请选择:>");
        scanf("%d", &input);

        // 根据用户选择执行相应的算术运算
        switch (input)
        {
        case 1: // 加法
            printf("请输入两个操作数:>");
            scanf("%d %d", &x, &y);
            res = add1(x, y);
            printf("两个整数相加的结果:%d\n", res);
            break;
        case 2: // 减法
            printf("请输入两个操作数:>");
            scanf("%d %d", &x, &y);
            res = sub1(x, y);
            printf("两个整数相减的结果:%d\n", res);
            break;
        case 3: // 乘法
            printf("请输入两个操作数:>");
            scanf("%d %d", &x, &y);
            res = mul1(x, y);
            printf("两个整数相乘的结果:%d\n", res);
            break;
        case 4: // 除法
            printf("请输入两个操作数:>");
            scanf("%d %d", &x, &y);
            res = div1(x, y);
            printf("两个整数相除的结果:%d\n", res);
            break;
        case 0: // 退出
            printf("退出计算器\n");
            break;
        default: // 错误输入
            printf("选择错误\n");
            break;
        }
    } while (input); // 当input不为0时继续循环
    return 0;
}

// 上面的计算器代码有很多重复的代码,我们可以使用函数指针来改进一下;
// 改进思路:将重复的输入输出逻辑提取到通用函数中,通过函数指针调用具体的运算函数

// ----------------------------------------------------------
// 第一次改进:使用函数指针,消除重复输入输出代码
// ----------------------------------------------------------

// 使用函数指针改进上面的计算器代码;

#include <stdio.h>

// 菜单函数
void menu2()
{
    printf("***********************************\n");
    printf("***********************************\n");
    printf("*********** 1.add  2.sub **********\n");
    printf("*********** 3.mul  4.div **********\n");
    printf("*********** 0.exit      ***********\n");
    printf("***********************************\n");
    printf("***********************************\n");
}

// 四个算术运算函数
int add2(int x, int y)
{
    return x + y;
}
int sub2(int x, int y)
{
    return x - y;
}
int mul2(int x, int y)
{
    return x * y;
}
int div2(int x, int y)
{
    return x / y;
}

// 通用的计算函数,接收函数指针作为参数
// pf是一个函数指针,指向一个接收两个int参数并返回int的函数
void calc(int (*pf)(int, int))
{
    int x = 0;
    int y = 0;
    int res = 0;
    printf("请输入两个操作数:>");
    scanf("%d %d", &x, &y);
    res = pf(x, y); // 通过函数指针调用对应的运算函数
    printf("结果:%d\n", res);
}

// 使用函数指针的改进版本计算器
// 优点:消除了重复的输入输出代码,逻辑更清晰
int main2()
{
    int input = 0;
    do
    {
        menu2();
        printf("请选择:>");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            calc(add2); // 传递add2函数的地址
            break;
        case 2:
            calc(sub2); // 传递sub2函数的地址
            break;
        case 3:
            calc(mul2); // 传递mul2函数的地址
            break;
        case 4:
            calc(div2); // 传递div2函数的地址
            break;
        case 0:
            printf("退出计算器\n");
            break;
        default:
            printf("选择错误\n");
            break;
        }
    } while (input);
    return 0;
}

// ##########################################################
// (六).函数指针数组
// ##########################################################

// 指针数组 : int* arr1[10];  // 包含10个int指针的数组
//           char* arr2[10]; // 包含10个char指针的数组

// 函数指针数组: 存放函数指针的数组;
// 函数指针也是指针,把函数指针放在数组中,就是函数指针数组;
// 语法:返回值类型 (*数组名[数组大小])(参数列表)

#include <stdio.h>

// 四个算术运算函数
int add4(int x, int y)
{
    return x + y;
}
int sub4(int x, int y)
{
    return x - y;
}
int mul4(int x, int y)
{
    return x * y;
}
int div4(int x, int y)
{
    return x / y;
}

// 演示函数指针数组的基本用法
int main4()
{
    // 声明一个函数指针pf,指向add4函数
    int (*pf)(int, int) = add4; // pf是一个函数指针;

    // 函数指针数组:包含4个函数指针的数组
    // 每个元素都是指向函数的指针，该函数接收两个int参数并返回int
    int (*arr[4])(int, int) = {add4, sub4, mul4, div4};

    // 通过函数指针数组调用各个函数
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        int res = arr[i](8, 4); // 通过函数指针数组调用函数
        printf("arr[%d](8,4) = %d\n", i, res);
    }
    return 0;
}

// ----------------------------------------------------------
// 第二次改进:使用函数指针数组,完全消除switch-case
// ----------------------------------------------------------

// (2):使用函数指针数组对上面的计算器代码进一步简化;

#include <stdio.h>

// 菜单函数
void menu3()
{
    printf("***********************************\n");
    printf("***********************************\n");
    printf("*********** 1.add  2.sub **********\n");
    printf("*********** 3.mul  4.div **********\n");
    printf("*********** 0.exit       **********\n");
    printf("***********************************\n");
    printf("***********************************\n");
}

// 四个算术运算函数
int add3(int x, int y)
{
    return x + y;
}
int sub3(int x, int y)
{
    return x - y;
}
int mul3(int x, int y)
{
    return x * y;
}
int div3(int x, int y)
{
    return x / y;
}

// 使用函数指针数组的简化版本计算器
// 优点:完全消除了switch-case,代码更加简洁
int main()
{
    int input = 0;
    int x = 0;
    int y = 0;
    int res = 0;

    // 函数指针数组 ---- 转移表(dispatch table)
    // 索引0位置放0(NULL),这样输入1-4可以直接对应数组索引
    // pfArr[0] = 0 (不使用)
    // pfArr[1] = add3
    // pfArr[2] = sub3
    // pfArr[3] = mul3
    // pfArr[4] = div3
    int (*pfArr[5])(int, int) = {0, add3, sub3, mul3, div3};

    do
    {
        menu3();
        printf("请选择:>");
        scanf("%d", &input);

        if (input == 0)
        {
            printf("退出计算器\n");
        }
        else if (input >= 1 && input <= 4)
        {
            printf("请输入两个操作数:>");
            scanf("%d %d", &x, &y);
            res = pfArr[input](x, y); // 通过函数指针数组直接调用对应函数
            printf("结果:%d\n", res);
        }
        else
        {
            printf("选择错误;\n");
        }
    } while (input);
    return 0;
}

// 总结:
// 1. 原始版本:使用switch-case,代码重复
// 2. 第一次改进:使用函数指针,消除重复输入输出代码
// 3. 第二次改进:使用函数指针数组,完全消除switch-case
// 函数指针数组的优点:代码简洁,易于扩展,适合实现命令模式、状态机等
