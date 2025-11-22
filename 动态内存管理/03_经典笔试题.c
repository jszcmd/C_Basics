// #########################################################################
// 4.几个经典的动态内存笔试题
// #########################################################################

// -------------------------------------------------------------------------
// 题目1：传值调用导致的内存泄漏问题
// -------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 错误版本:传值调用,无法修改外部指针
void GetMemory_1(char *p)
{
    p = (char *)malloc(100);
    // 问题分析：
    // 1. 这里p是外部指针的临时拷贝
    // 2. malloc返回的地址只保存在临时拷贝中
    // 3. 函数返回后,临时拷贝消失,堆内存无法访问
    // 4. 导致内存泄漏:申请了空间但找不到地址释放
}

void Test_1(void)
{
    char *str = NULL;
    GetMemory_1(str);           // 按值传递,传递的是str的一份临时拷贝
    strcpy(str, "hello world"); // str仍然是NULL,对空指针解引用会导致程序崩溃
    printf(str);
}

// 解决方法1：使用二级指针（传址调用）
void GetMemory1(char **p)
{
    *p = (char *)malloc(100); // 通过二级指针修改外部指针的值
}

void Test1(void)
{
    char *str = NULL;
    GetMemory1(&str);           // 传递指针的地址，这个函数结束以后str就是开辟的100个字节的首地址
    strcpy(str, "hello world"); // 现在str指向有效的堆内存
    printf(str);
    free(str);  // 正确释放内存
    str = NULL; // 避免野指针
}

// 解决方法2：返回指针
char *GetMemory2(void)
{
    char *p = (char *)malloc(100);
    return p; // 返回堆内存地址
}

void Test2(void)
{
    char *str = NULL;
    str = GetMemory2(); // str存放的就是动态开辟的100字节的地址
    strcpy(str, "hello world");
    printf(str);
    free(str);  // 正确释放内存
    str = NULL; // 避免野指针
}

int main1()
{
    // Test();  // 这个会崩溃,不要运行

    printf("=== 解决方法1测试 ===\n");
    Test1();

    printf("\n=== 解决方法2测试 ===\n");
    Test2();

    printf("\n=== printf格式说明 ===\n");
    printf("Hello World!!!\n");
    char *p = "Hello World!!!\n";
    printf(p); // 传递给printf不是字符串而是字符串的首地址
    // 指定格式,%s
    printf("%s\n", p);

    return 0;
}

// 野指针问题示例
// 问题1:返回局部变量的地址
int *f1(void)
{
    int x = 10;  // 局部变量,在栈上分配
    return (&x); // 错误:返回栈内存地址,函数返回后x被销毁
}

// 问题2:使用未初始化的指针
int *f2(void)
{
    int *ptr;   // 未初始化的指针,值是随机的
    *ptr = 10;  // 危险:向随机地址写入数据
    return ptr; // 返回野指针
}

// -------------------------------------------------------------------------
// 题目2：返回栈区空间地址的问题
// -------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 错误：返回栈区数组的地址
char *GetMemory_2(void)
{
    char p[] = "hello world"; // 栈区数组,函数返回后自动销毁
    return p;                 // 错误:返回局部数组地址
}

void Test_2(void)
{
    char *str = NULL;
    str = GetMemory_2(); // str成为野指针,指向已释放的栈内存
    printf(str);         // 未定义行为:可能输出乱码或崩溃
}

int main2()
{
    printf("=== 题目2测试 ===\n");
    Test_2(); // 未定义行为
    return 0;
}

// 类似的栈区地址返回问题
int *test()
{
    // 返回栈区空间的地址的问题
    int a = 10; // 栈区变量
    return &a;  // 错误：返回局部变量地址
}

int test_main()
{
    int *p = test();    // p成为野指针
    printf("%d\n", *p); // 未定义行为
    return 0;
}

// -------------------------------------------------------------------------
// 题目3:正确的动态内存使用(但需要完善)
// -------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GetMemory(char **p, int num)
{
    *p = (char *)malloc(num); // 正确：通过二级指针分配内存
}

void Test(void)
{
    char *str = NULL;
    GetMemory(&str, 100); // 正确：传递指针的地址
    strcpy(str, "hello world");
    printf(str);
    free(str);  // 正确：记得释放空间
    str = NULL; // 正确：释放后置空
}

int main()
{
    printf("\n=== 题目3测试 ===\n");
    Test();
    return 0;
}

// -------------------------------------------------------------------------
// 题目4:使用已释放内存(野指针问题)
// -------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 错误版本:使用已释放的内存
void Test_4(void)
{
    char *str = (char *)malloc(100);
    strcpy(str, "hello ");
    free(str); // 已经把这一块空间释放了

    // 后面再使用str, str就是野指针了
    if (str != NULL)
    {                         // 这个检查无效，因为free不会自动置空指针
        strcpy(str, "world"); // 危险：向已释放内存写入
        printf(str);          // 未定义行为
    }
}

// 改正版本：释放后立即置空
void Test_correct(void)
{
    char *str = (char *)malloc(100);
    strcpy(str, "hello ");
    free(str);  // 释放内存
    str = NULL; // 关键:立即置为空指针

    if (str != NULL)
    { // 现在这个检查有效了
        strcpy(str, "world");
        printf(str);
    }
    else
    {
        printf("指针已置空,安全跳过操作\n");
    }
}

int main()
{
    printf("\n=== 题目4测试 ===\n");
    printf("错误版本（注释掉避免崩溃）:\n");
    // Test();  // 这个会导致未定义行为，注释掉

    printf("正确版本:\n");
    Test_correct();
    return 0;
}

// -------------------------------------------------------------------------
// 内存布局说明
// -------------------------------------------------------------------------

/*
内存空间分布（从高地址到低地址）：

1. 内核空间: 用户代码不能读写
   - 操作系统内核使用

2. 栈区: 局部变量, 函数参数等
   - 栈区向下增长（向低地址扩展）
   - 自动分配和释放

3. 内存映射段:
   - 文件映射、动态库加载等

4. 堆区: malloc, calloc, realloc, free操作的内存
   - 堆区向上增长（向高地址扩展）
   - 手动分配和释放

5. 数据段: 全局变量、静态变量
6. 代码段: 程序代码、字符串常量
*/

// 总结：
// 1. 动态内存分配后必须检查返回值
// 2. 使用完毕后必须及时释放
// 3. 释放后指针要置NULL
// 4. 不要返回栈区地址
// 5. 不要使用未初始化的指针
// 6. 不要使用已释放的内存
