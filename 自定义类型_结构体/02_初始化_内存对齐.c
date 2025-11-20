#define _CRT_SECURE_NO_WARNINGS

// 自定义类型:结构体,枚举,联合

// 结构体:
// 结构体类型的声明
// 结构体的自引用
// 结构体变量的定义和初始化
// 结构体内存对齐
// 结构体的传参
// 结构体实现位段(位段的填充&可移植性)

// #####################################################################
// (3):结构体变量的定义和初始化
// #####################################################################

// 方式1：声明结构体的同时定义结构体变量
struct Point
{
	int x;
	int y;
} p1; // 声明结构体的同时定义结构体变量p1（未初始化）

struct Point p2; // 定义结构体变量p2（未初始化）

// 方式2：声明结构体的同时定义并初始化变量
struct Point2
{
	int x;
	int y;
} p3 = {2, 3}; // 声明结构体的同时定义结构体变量p1，并初始化
// struct Point2{ int x; int y; } p3 = {2,3};
// struct Point2{ int x; int y; } 就相当于一个新的数据类型

// 单独定义结构体类型
struct Student
{
	char name[20];
	int age;
	float score;
};

// 在函数中定义和初始化结构体变量
int main1()
{
	struct Point p4 = {4, 5};				 // 定义结构体变量p4，并初始化
	struct Student s1 = {"张三", 20, 99.5f}; // 定义结构体变量s1，并初始化
	return 0;
}

#include <stdio.h>

// 结构体嵌套示例
// 结构体也是可以嵌套的
struct score
{
	int math;
	int chinese;
	int english;
};

struct Student2
{
	char name[20];
	int age;
	struct score sc; // 结构体嵌套
};

int main2()
{
	struct Student2 s1 = {"张三", 20, {100, 100, 100}}; // 定义结构体变量s1，并初始化嵌套结构体
	printf("%s %d %d %d %d\n", s1.name, s1.age, s1.sc.math, s1.sc.chinese, s1.sc.english);
	return 0;
}

/*
结构体变量定义和初始化要点：
1. 可以在声明结构体时直接定义变量（全局或局部）
2. 可以在声明时直接初始化，也可以在后续代码中初始化
3. 使用花括号{}进行初始化，按成员声明顺序赋值
4. 支持结构体嵌套初始化，使用多层花括号
5. 字符串等数组类型成员可以直接用字符串字面量初始化
6. 未初始化的结构体变量包含随机值（全局变量初始化为0）
*/

// #####################################################################
// (4):结构体内存对齐
// #####################################################################

// 结构体的对齐规则:
// 1. 第一个成员在与结构体变量偏移量为0的地址处
// 2. 其他成员变量要对齐到某个数字(对齐数)的整数倍的地址处
//    对齐数 = 编译器默认的第一个对齐数 与 该成员大小的较小值
//    VS默认的对齐数是8字节
// 3. 结构体的总大小为最大对齐数(每一个成员变量都有一个对齐数)的整数倍
// 4. 如果嵌套了结构体的情况,嵌套的结构体对齐到自己的最大对齐数的整数倍处,
//    结构体的整数大小就是所有最大对齐数(含嵌套结构体的对齐数)的整数倍

// gcc编译器没有默认的对齐数,
// 所以对齐数就是:所有成员变量按照自己的大小对齐

// 内存对齐的原因:
// 1. 提高内存访问的效率
// 2. 有些CPU架构要求数据必须对齐访问,否则会产生异常
// 3. 方便硬件设计
// 4. 编译器的实现方式

// 结构体内存对齐的验证方法:offsetof宏
// 结构体的内存对齐是拿空间换时间的一种手段

// 那么我们如何减少结构体的内存对齐带来的空间浪费呢?
// 1. 调整结构体成员的顺序,让大的数据类型放在前面
// 2. 让占用空间小的数据类型放在一起
// 3. 使用#pragma pack指令改变默认的对齐数(不推荐使用,影响全局,可能导致性能下降)

#include <stdio.h>
#include <stddef.h> // offsetof宏所在的头文件

struct s1
{
	char c1; // 1字节
	int i;	 // 4字节
	char c2; // 1字节
};

struct s2
{
	char c1; // 1字节
	char c2; // 1字节
	int i;	 // 4字节
};

struct s3
{
	double d; // 8字节
	char c;
	int i;
};

// 结构体嵌套的内存对齐
struct s4
{
	char c1;
	struct s3 s;
	double d;
};

int main1()
{
	printf("struct s1 大小: %zu\n", sizeof(struct s1)); // 12
	// 验证各成员偏移量
	printf("s1.c1 偏移量: %zu\n", offsetof(struct s1, c1)); // 0
	printf("s1.i  偏移量: %zu\n", offsetof(struct s1, i));	// 4
	printf("s1.c2 偏移量: %zu\n", offsetof(struct s1, c2)); // 8

	printf("-----\n");
	printf("struct s2 大小: %zu\n", sizeof(struct s2));		// 8
	printf("s2.c1 偏移量: %zu\n", offsetof(struct s2, c1)); // 0
	printf("s2.c2 偏移量: %zu\n", offsetof(struct s2, c2)); // 1
	printf("s2.i  偏移量: %zu\n", offsetof(struct s2, i));	// 4

	printf("-----\n");
	printf("struct s3 大小: %zu\n", sizeof(struct s3));	   // 16
	printf("s3.d  偏移量: %zu\n", offsetof(struct s3, d)); // 0
	printf("s3.c  偏移量: %zu\n", offsetof(struct s3, c)); // 8
	printf("s3.i  偏移量: %zu\n", offsetof(struct s3, i)); // 12

	printf("-----\n");
	printf("struct s4 大小: %zu\n", sizeof(struct s4));		// 32
	printf("s4.c1 偏移量: %zu\n", offsetof(struct s4, c1)); // 0
	printf("s4.s  偏移量: %zu\n", offsetof(struct s4, s));	// 8
	printf("s4.d  偏移量: %zu\n", offsetof(struct s4, d));	// 24

	return 0;
}

// 修改默认对齐数
// #pragma pack(n)
#include <stdio.h>
#pragma pack(4) // 修改默认对齐数为4字节
// 一般不建议修改默认对齐数,可能会影响性能,也可能导致某些数据类型无法正确访问
// 修改的时候一般用的是2的倍数,比如2,4,8等
struct s5
{
	int i;	  // 4字节
	double f; // 8字节
};

int main2()
{
	printf("struct s5 大小: %zu\n", sizeof(struct s5)); // 12
	return 0;
}

// #pragma once
// 在头文件中使用,防止头文件被多次使用

/*
内存对齐要点总结:
1. 内存对齐是为了提高CPU访问效率
2. 不同编译器可能有不同的默认对齐数
3. 合理安排成员顺序可以优化内存使用
4. offsetof宏可以验证成员偏移量
5. #pragma pack可以修改对齐数但不推荐使用
6. 嵌套结构体需要按照其最大对齐数对齐
*/
