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
// (八).回调函数
// ##########################################################

// 回调函数:
// 回调函数就是一个通过函数指针调用的函数.如果你把函数的指针(地址)作为参数传递给另一个函数，
// 当这个指针被用来调用其所指向的函数时,我们就说这是回调函数.回调函数不是由该函数的实现方直接调用,
// 而是在特定的事件或条件发生时由另外的一方调用的,用于对该事件或条件进行响应.

// ----------------------------------------------------------
// 1.冒泡排序实现排序int类型
// ----------------------------------------------------------

// (1):回顾冒泡排序,这个函数只能够实现排序int类型的:
#include <stdio.h>

/**
 * @brief 基础冒泡排序 - 只能排序int类型数组
 * @param arr 待排序的整型数组
 * @param len 数组长度
 */
void bubble_sort1(int arr[], int len)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    // 进行len-1趟冒泡排序
    for (i = 0; i < len - 1; i++)
    {
        // 相邻两个元素比较
        for (j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief 优化版冒泡排序 - 添加提前结束优化
 * @param arr 待排序的整型数组
 * @param len 数组长度
 * @note 当检测到数组已经有序时会提前结束排序
 */
void bubble_sort2(int arr[], int len)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    for (i = 0; i < len - 1; i++)
    {
        int flag = 1; // 有序标志:1表示假设数组已有序
        for (j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = 0; // 发生交换,数组尚未有序
            }
        }
        if (flag == 1)
            break; // 提前结束:整轮无交换说明已排序完成
    }
}

int main1()
{
    int arr[] = {45, 58, 6, 7485, 25, 64, 50, 94, 257, 615, 88};
    int len = sizeof(arr) / sizeof(arr[0]); // 计算数组长度
    bubble_sort2(arr, len);                 // 使用优化版冒泡排序
    int i = 0;
    printf("冒泡排序结果：");
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

// ----------------------------------------------------------
// 2.void*指针
// ----------------------------------------------------------

// (2):了解void*指针的用法
#include <stdio.h>

/**
 * @brief 演示void*指针的用法
 * @note void*可以接收任意类型地址,但不能直接解引用
 * @note void*是无具体类型的指针,所以不能够解引用操作,也不能+-整数;
 */
int main2()
{
    int a = 10;
    float b = 3.14f;
    char c = 'X';

    // char* p1 = &a; // 错误:类型不兼容
    void *p2 = &a; // 正确:void*可以接收int*
    void *p3 = &b; // 正确:void*可以接收float*
    void *p4 = &c; // 正确:void*可以接收char*

    // void*不能直接解引用,需要先类型转换
    printf("a = %d\n", *(int *)p2);
    printf("b = %.2f\n", *(float *)p3);
    printf("c = %c\n", *(char *)p4);

    return 0;
}

// ----------------------------------------------------------
// 3.qsort函数排序int类型的数据
// ----------------------------------------------------------

/**
 * @brief qsort函数 - 标准库快速排序函数
 *
 * 函数原型:void qsort(void* base, size_t nmemb, size_t size,
 *                     int (*compar)(const void*, const void*));
 *
 * 功能:使用快速排序算法对任意类型的数据进行排序
 *
 * 参数说明:
 * @param base   - 指向要排序数组的起始位置的指针(void* 类型,可接受任意数据类型)
 * @param nmemb  - 数组中元素的个数
 * @param size   - 每个元素的大小(以字节为单位)
 * @param compar - 函数指针,指向比较函数,用于定义排序规则
 *
 * 比较函数原型:int compar(const void* e1, const void* e2);
 *
 * 比较函数返回值规则:
 * - 如果 e1 > e2，返回 > 0 的数(正数)
 * - 如果 e1 = e2，返回 0
 * - 如果 e1 < e2，返回 < 0 的数(负数)
 *
 * 头文件：#include <stdlib.h>
 *
 * 特点:
 * - 通用性强:可排序任意数据类型
 * - 效率高:基于快速排序算法
 * - 灵活:通过比较函数自定义排序规则
 */

// (4):使用qsort函数实现排序整型数据
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 整型比较函数 - 详细判断版本
 * @param e1 指向第一个元素的void指针
 * @param e2 指向第二个元素的void指针
 * @return 正数(e1>e2), 0(e1=e2), 负数(e1<e2)
 */
int cmp_int1(const void *e1, const void *e2)
{
    // 升序排列：
    if (*(int *)e1 > *(int *)e2)
        return 1; // e1大于e2返回正数
    else if (*(int *)e1 == *(int *)e2)
        return 0; // e1等于e2返回0
    else
        return -1; // e1小于e2返回负数
}

/**
 * @brief 整型比较函数 - 简洁版本
 * @param e1 指向第一个元素的void指针
 * @param e2 指向第二个元素的void指针
 * @return e1-e2(升序) 或 e2-e1(降序)
 */
int cmp_int_pro(const void *e1, const void *e2)
{
    return (*(int *)e1 - *(int *)e2); // 升序排列
    // return (*(int*)e2 - *(int*)e1); // 降序排列
}

int main3()
{
    int arr[] = {45, 58, 6, 7485, 25, 64, 50, 94, 257, 615, 88};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("排序前:");
    int i = 0;
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    qsort(arr, len, sizeof(arr[0]), cmp_int_pro); // 使用qsort排序

    printf("排序后：");
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

// ----------------------------------------------------------
// 4.使用qsort排序结构体数据
// ----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // 使用qsort函数
#include <string.h> // 引入头文件,使用strcmp函数

// 定义人员结构体
struct person
{
    char name[20];
    int age;
};

/**
 * @brief 按姓名比较的回调函数
 * @param e1 指向第一个结构体的void指针
 * @param e2 指向第二个结构体的void指针
 * @return 字符串比较结果
 */
int cmp_by_name1(const void *e1, const void *e2)
{
    // 将void*转换为struct person*类型,然后比较name字段
    // strcmp函数比较两个字符串,返回>0(=0,<0)的数字
    return strcmp(((struct person *)e1)->name, ((struct person *)e2)->name);
}

/**
 * @brief 按年龄比较的回调函数
 * @param e1 指向第一个结构体的void指针
 * @param e2 指向第二个结构体的void指针
 * @return 年龄差值
 */
int cmp_by_age1(const void *e1, const void *e2)
{
    // 将void*转换为struct person*类型,然后比较age字段
    return ((struct person *)e1)->age - ((struct person *)e2)->age;
}

int main4()
{
    // 测试使用qsort来排序结构体数据
    struct person ss[] = {{"zhangsan", 15}, {"lisi", 80}, {"wangwu", 25}};
    int len = sizeof(ss) / sizeof(ss[0]);

    printf("按年龄排序前:\n");
    int i = 0;
    for (i = 0; i < len; i++)
    {
        printf("姓名：%s, 年龄：%d\n", ss[i].name, ss[i].age);
    }

    qsort(ss, len, sizeof(ss[0]), cmp_by_age1); // 按年龄排序

    printf("\n按年龄排序后:\n");
    for (i = 0; i < len; i++)
    {
        printf("姓名：%s, 年龄：%d\n", ss[i].name, ss[i].age);
    }

    return 0;
}

// ##########################################################
// 冒泡排序Pro_MAX版本
// ##########################################################
// (6):把我们的冒泡排序改进一下,让他什么都可以排序
#include <stdio.h>
#include <string.h> // 添加strcmp头文件

// 定义学生结构体
struct Student
{
    char name[20];
    int age;
};

/**
 * @brief 通用交换函数 - 按字节交换两个内存区域的内容
 * @param a 指向第一个元素的字节指针
 * @param b 指向第二个元素的字节指针
 * @param size 每个元素的大小(字节数)
 */
void swap(char *a, char *b, int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        char temp = *a;
        *a = *b;
        *b = temp;
        a++;
        b++;
    }
}

/**
 * @brief 整型比较函数
 * @param e1 指向第一个元素的void指针
 * @param e2 指向第二个元素的void指针
 * @return 整型比较结果
 */
int cmp_by_int(const void *e1, const void *e2)
{
    return (*(int *)e1 - *(int *)e2); // 升序排列
}

/**
 * @brief 按姓名比较函数
 * @param e1 指向第一个结构体的void指针
 * @param e2 指向第二个结构体的void指针
 * @return 字符串比较结果
 */
int cmp_by_name(const void *e1, const void *e2)
{
    return strcmp(((struct Student *)e1)->name, ((struct Student *)e2)->name);
}

/**
 * @brief 按年龄比较函数
 * @param e1 指向第一个结构体的void指针
 * @param e2 指向第二个结构体的void指针
 * @return 年龄差值
 */
int cmp_by_age(const void *e1, const void *e2)
{
    return ((struct Student *)e1)->age - ((struct Student *)e2)->age;
}

/**
 * @brief 通用冒泡排序函数 - 可以排序任意类型的数据
 * @param arr 待排序数组的首地址
 * @param len 数组元素个数
 * @param size 每个元素的大小(字节数)
 * @param cmp 比较函数的指针
 * @note 使用回调函数机制实现通用性
 */
void bubble_sort(void *arr, int len, int size, int (*cmp)(const void *e1, const void *e2))
{
    int i = 0;
    int j = 0;
    for (i = 0; i < len - 1; i++)
    {
        int flag = 1; // 优化标志位，假设已经有序
        for (j = 0; j < len - i - 1; j++)
        {
            // 计算两个相邻元素的地址:
            // (char*)arr + j * size     -> 第j个元素的地址
            // (char*)arr + (j + 1) * size -> 第j+1个元素的地址
            if (cmp((char *)arr + j * size, (char *)arr + (j + 1) * size) > 0)
            {
                // 调换两个元素的位置
                swap((char *)arr + j * size, (char *)arr + (j + 1) * size, size);
                flag = 0; // 发生了交换说明还不是有序
            }
        }
        if (flag == 1)
            break; // 如果一趟排序中没有交换,提前结束
    }
}

/**
 * @brief 主函数 - 测试通用冒泡排序
 */
int main()
{
    printf("=== 测试通用冒泡排序 ===\n\n");

    // 测试1:排序整型数组
    printf("1. 整型数组排序:\n");
    int arr[] = {45, 58, 6, 7485, 25, 64, 50, 94, 257, 615, 88};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("排序前:");
    int i = 0;
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubble_sort(arr, len, sizeof(arr[0]), cmp_by_int);

    printf("排序后:");
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // 测试2:排序结构体数组(按年龄)
    printf("2. 结构体数组按年龄排序:\n");
    struct Student ss[] = {{"zhangsan", 15}, {"lisi", 80}, {"wangwu", 25}};
    int len2 = sizeof(ss) / sizeof(ss[0]);

    printf("排序前:\n");
    for (i = 0; i < len2; i++)
    {
        printf("姓名:%s, 年龄:%d\n", ss[i].name, ss[i].age);
    }

    bubble_sort(ss, len2, sizeof(ss[0]), cmp_by_age);

    printf("按年龄排序后:\n");
    for (i = 0; i < len2; i++)
    {
        printf("姓名:%s, 年龄:%d\n", ss[i].name, ss[i].age);
    }
    printf("\n");

    // 测试3:排序结构体数组(按姓名)
    printf("3. 结构体数组按姓名排序：\n");
    struct Student ss2[] = {{"zhangsan", 15}, {"lisi", 80}, {"wangwu", 25}};
    int len3 = sizeof(ss2) / sizeof(ss2[0]);

    printf("排序前:\n");
    for (i = 0; i < len3; i++)
    {
        printf("姓名:%s, 年龄:%d\n", ss2[i].name, ss2[i].age);
    }

    bubble_sort(ss2, len3, sizeof(ss2[0]), cmp_by_name);

    printf("按姓名排序后:\n");
    for (i = 0; i < len3; i++)
    {
        printf("姓名:%s, 年龄:%d\n", ss2[i].name, ss2[i].age);
    }

    return 0;
}
