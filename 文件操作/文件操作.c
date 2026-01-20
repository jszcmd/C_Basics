#define _CRT_SECURE_NO_WARNINGS 

// 1.为什么使用文件

// 文件用于持久化存储数据，使得数据在程序结束后仍然存在，便于后续访问和处理。

// 2.什么是文件
// 硬盘上的文件是文件
// 但是在程序设计中,我们一般谈及的文件有两种:程序文件和数据文件(从文件功能的角度来分类)

// 2.1 程序文件
// 包括源文件(后缀为.c),头文件(后缀为.h),目标文件(后缀为.obj或.o),可执行文件(后缀为.exe或.out)

// 2.2 数据文件
// 文件的内容不一定是程序,而是程序运行时需要处理的数据,读写的数据,比如程序运行需要从中读取数据的文件,
// 或者是输出内容的文件

// 写(输出):把内存中的数据写入到文件中
// 读(输入):把文件中的数据读取到内存中


// 2.3 文件名
// 一个文件要有一个唯一的文件标识,以便用户识别和引用
// 文件名包括部分: 文件路径 + 文件主干名 + 文件后缀
// 列如: C:\code\hello.c
// 路径: C:\code\
// 主干名: hello
// 后缀: .c


// 文件的操作:  打开文件 -> 读写文件(操作文件) -> 关闭文件

// 3.文件的打开与关闭

// 3.1 文件指针

// 缓冲文件系统中,关键的概念是"文件类型指针",简称"文件指针"
// 每一个使用的文件都在内存中开辟了一个相应的文件信息区,用来存放文件的相关信息(如文件的名字,文件状态,以及文件当前的位置等).
// 这些信息将保存在一个结构变量中的,该结构体类型是系统声明的,取名为FILE
// #include <stdio.h>
// 每当打开一个文件的时候,系统会根据文件的情况自动创建一个FILE结构的变量,并填充其中的信息,使用者不必关心这个结构体的具体内容.

// 一般都是通过一个FILE的指针来维护这个FILE结构的变量,这样使用起来更加方便


// 3.2 文件的打开和关闭

// 文件的读写之前,必须先打开文件,打开文件的函数是fopen
// FILE * fopen ( const char * filename, const char * mode );
// 第一个参数: filename,要打开的文件名,字符串
// 第二个参数: mode,文件的打开方式(读,写,追加,二进制等)
// 返回值: 成功返回文件指针,失败返回NULL

// 打开方式:
// "r"(只读)         为了输入数据,打开一个已存在的文本文件        指定的文件不存在,会出错
// "w"(只写)         为了输出数据,打开一个文本文件               指定的文件不存在,创建一个新的文件;指定的文件存在,则清空文件内容
// "a"(追加)         向文本末尾添加数据                        指定的文件不存在,创建一个新的文件;指定的文件存在,则在文件末尾追加内容
// "rb"(二进制只读)   为了输入数据,打开一个已存在的二进制文件      指定的文件不存在,会出错
// "wb"(二进制只写)   为了输出数据,打开一个二进制文件             指定的文件不存在,创建一个新的文件;指定的文件存在,则清空文件内容
// "ab"(二进制追加)   向二进制文件末尾添加数据                   指定的文件不存在,创建一个新的文件;指定的文件存在,则在文件末尾追加内容
// "r+"(读写)        为了输入和输出数据,打开一个已存在的文本文件   指定的文件不存在,会出错
// "w+"(读写)        为了输入和输出数据,打开一个文本文件          指定的文件不存在,创建一个新的文件;指定的文件存在,则清空文件内容
// "a+"(读写)        为了输入和输出数据,打开一个文本文件          指定的文件不存在,创建一个新的文件;指定的文件存在,则在文件末尾追加内容
// "rb+"(二进制读写)  为了输入和输出数据,打开一个已存在的二进制文件  指定的文件不存在,会出错
// "wb+"(二进制读写)  为了输入和输出数据,打开一个二进制文件         指定的文件不存在,创建一个新的文件;指定的文件存在,则清空文件内容
// "ab+"(二进制读写)  为了输入和输出数据,打开一个二进制文件         指定的文件不存在,创建一个新的文件;指定的文件存在,则在文件末尾追加内容



//#include <stdio.h> // 使用 fopen 和 fclose 函数需要包含该头文件
//#include <string.h> // 使用 strerrno 函数需要包含该头文件
//#include <errno.h>  // 使用 errno 变量需要包含该头文件
//
//int main() {
//	// 以只读方式打开当前目录下的 test.txt 文件
//	FILE* pf = fopen("test.txt", "r"); 
//
//	// 使用绝对路径打开文件,打开桌面上的 test.txt 文件
//	FILE * pf2 = fopen("C:\\Users\\13033\\Desktop\\test.txt", "r");
//	if (pf == NULL) {
//		printf("%s\n", strerror(errno)); // 打印不成功的原因
//		return -1;
//	}
//	// 文件不存在: No such file or directory
//
//	// 读写文件
//	
//	// 关闭文件: 非常类似free函数
//	fclose(pf); 
//	pf == NULL;
//	return 0;
//}


// 4.文件的顺序读写

// fgetc    字符输入函数   适用于所有输入流
// fputc    字符输出函数   适用于所有输出流
// fgets    文本行输入函数 适用于所有输入流
// fputs    文本行输出函数 适用于所有输出流
// fscanf   格式化输入函数 适用于所有输入流
// fprintf  格式化输出函数 适用于所有输出流
// fread    块输入函数    适用于文件
// fwrite   块输出函数    适用于文件


#include <stdio.h> // 使用 fopen 和 fclose 函数需要包含该头文件
#include <string.h> // 使用 strerrno 函数需要包含该头文件
#include <errno.h>  // 使用 errno 变量需要包含该头文件

//int main() {
//	FILE* pf = fopen("test.txt", "w");  // 以只写方式打开当前目录下的 test.txt 文件
//	if (pf == NULL) {
//		printf("%s\n", strerror(errno)); // 打印不成功的原因
//		return -1;
//	}
//
//	// 写文件
//	char i = 0;
//	for (i = 'a'; i <= 'z'; i++) {
//		fputc(i, pf); // 写入单个字符
//	} // fputc,第一个参数是int类型的
//	
//	// 关闭文件: 非常类似free函数
//	fclose(pf); 
//	pf == NULL;
//	// 一个程序能打开的文件数量是有限的,所以用完文件后,一定要关闭文件
//	// 如果不关闭文件,还可能会丢失数据
//	return 0;
//}


//int main() {
//	FILE* pf = fopen("test.txt", "r");  // 以只读方式打开当前目录下的 test.txt 文件
//	if (pf == NULL) {
//		printf("%s\n", strerror(errno)); // 打印不成功的原因
//		return -1;
//	}
//
//	// 读文件
//	// int fgetc ( FILE * stream )
//	// 参数(FILE *): stream,文件指针
//	// 返回值(int): 读取到的字符,失败返回EOF
//
//	// 一次读取一个字符
//	//int ch = fgetc(pf);
//	//printf("ch = %c\n", ch); // 以字符形式打印读取到的字符
//
//	// 一次读取文件里面的所有字符
//	int ch = 0;
//	while ((ch = fgetc(pf)) != EOF) {
//		printf("%c ", ch); // 以字符形式打印读取到的字符
//	}
//
//	// 关闭文件: 非常类似free函数
//	fclose(pf);
//	pf == NULL;
//	// 一个程序能打开的文件数量是有限的,所以用完文件后,一定要关闭文件
//	// 如果不关闭文件,还可能会丢失数据
//	return 0;
//}



// 写一行数据
//int main() {
//	FILE* pf = fopen("test.txt", "w");  // 以只写方式打开当前目录下的 test.txt 文件
//	if (pf == NULL) {
//		printf("%s\n", strerror(errno)); // 打印不成功的原因
//		return -1;
//	}
//
//	// 写一行数据
//
//	// int fputs ( const char * str, FILE * stream );
//	// 参数(const char *): str,要写入的字符串
//	// 参数(FILE *): stream,文件指针
//	// 返回值(int): 成功返回非负值,失败返回EOF
//
//	fputs("Hello, World!\n", pf);
//	fputs("Hello, World!\n", pf);
//	// fputs不会自动添加换行符,需要手动添加
//	// 由于我们打开文件使用的是"w"模式,所以每次运行程序,都会覆盖原有内容
//	// 如果想要保留原有内容,可以使用"a"模式
//	
//	// 关闭文件: 非常类似free函数
//	fclose(pf); 
//	pf == NULL;
//	// 一个程序能打开的文件数量是有限的,所以用完文件后,一定要关闭文件
//	// 如果不关闭文件,还可能会丢失数据
//	return 0;
//}


// 读一行数据
//int main() {
//	FILE* pf = fopen("test1.txt", "r");  // 以只读方式打开当前目录下的 test.txt 文件
//	if (pf == NULL) {
//		// printf("%s\n", strerror(errno)); // 打印不成功的原因
//		perror("fopen error"); // 等价于上面一行
//		return -1;
//	}
//
//	// 读一行数据
//	// char * fgets ( char * str, int num, FILE * stream );
//	// 参数(char *): str,用于存放读取到的数据的缓冲区
//	// 参数(int): num,要读取的最大字符数,包括结尾的'\0'
//	// 参数(FILE *): stream,文件指针
//	// 返回值(char *): 成功返回str,失败返回NULL
//
//	char arr[20];
//	fgets(arr, 5, pf); // 一次读取最多4个字符,第5个位置存放'\0'
//	printf("%s\n", arr); // 打印读取到的数据
//
//	// 关闭文件: 非常类似free函数
//	fclose(pf);
//	pf == NULL;
//	// 一个程序能打开的文件数量是有限的,所以用完文件后,一定要关闭文件
//	// 如果不关闭文件,还可能会丢失数据
//	return 0;
//}


// 定义一个结构体数据
struct Student {
	char name[20];
	int age;
	float score;
};

// 把结构体数据格式化到文件
//int main() {
//	struct Student s = { "zhangsan",25,50.f };
//	FILE* pf = fopen("test.txt", "w");  // 以只写方式打开当前目录下的 test.txt 文件
//	if (pf == NULL) {
//		perror("fopen error");
//		return -1;
//	}
//
//	printf("%s %d %f", s.name, s.age, s.score); // 在控制台打印结构体数据
//	fprintf(pf, "%s %d %f", s.name, s.age, s.score); // 将结构体数据格式化写入文件
//
//	fclose(pf);
//	pf == NULL;
//	return 0;
//}


// 从文件中格式化读取数据
//int main() {
//	struct Student s = { 0 };
//	FILE* pf = fopen("test.txt", "r");  // 以读方式打开当前目录下的 test.txt 文件
//	if (pf == NULL) {
//		perror("fopen error");
//		return -1;
//	}
//	// 从文件中格式化读取数据
//	fscanf(pf, "%s %d %f", s.name, &s.age, &s.score); // 将文件中的格式化数据读到结构体中
//
//	printf("%s %d %f", s.name, s.age, s.score); // 打印
//
//	fclose(pf);
//	pf == NULL;
//	return 0;
//}




// 流: ---> 就是输入输出缓冲区的抽象概念
// 打开文件的时候就会返回一个FILE*的指针,这个指针就可以成为一个文件流
// 我打开一个文件,返回一个FILE*的指针,打开一个文件就会有一个文件流

// 任何一个C程序,只要运行,就会至少有三个流存在
// FILE* stdin   标准输入流    键盘
// FILE* stdout  标准输出流    屏幕
// FILE* stderr  标准错误流    屏幕
// 它们的类型都是FILE*


// fprintf()也可以把数据写到标准输出流(stdout)中,把数据打印到屏幕上
//int main() {
//	struct Student s = { 0 };
//	FILE* pf = fopen("test.txt", "r");  // 以读方式打开当前目录下的 test.txt 文件
//	if (pf == NULL) {
//		perror("fopen error");
//		return -1;
//	}
//	// 从文件中格式化读取数据
//	fscanf(pf, "%s %d %f", s.name, &s.age, &s.score); // 将文件中的格式化数据读到结构体中
//
//	fprintf(stdout, "%s %d %f", s.name, s.age, s.score); // 把数据写到标准输出流(stdout)中,把数据打印到屏幕上
//
//	fclose(pf);
//	pf == NULL;
//	return 0;
//}


// 二进制文件的输入和输出

// 把结构体数据以二进制形式写入文件
//int main() {
//	struct Student s = { "zhangsan",25,50.f };
//
//	// 把结构体数据以二进制形式写入文件
//
//	FILE* pf = fopen("test.txt", "wb");  // 以二进制只写方式打开当前目录下的 test.bin 文件
//	if (pf == NULL) {
//		perror("fopen error");
//		return -1;
//	}
//	// 二进制的方式写入数据
//	// size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
//	// 参数(const void *): ptr,指向要写入数据的缓冲区
//	// 参数(size_t): size,每个数据元素的大小(字节数)
//	// 参数(size_t): count,要写入的数据元素的个数
//	// 参数(FILE *): stream,文件指针
//	// 返回值(size_t): 成功写入的元素个数
//
//	fwrite(&s, sizeof(struct Student), 1, pf); // 把结构体数据以二进制形式写入文件
//
//	fclose(pf);
//	pf == NULL;
//	return 0;
//}


// 以二进制形式读取结构体数据
//int main() {
//	struct Student s = { 0 };
//
//	FILE* pf = fopen("test.txt", "rb");  // 以二进制只写方式打开当前目录下的 test.bin 文件
//	if (pf == NULL) {
//		perror("fopen error");
//		return -1;
//	}
//
//	// size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
//	// 参数(void *): ptr,指向用于存放读取数据的缓冲区
//	// 参数(size_t): size,每个数据元素的大小(字节数)
//	// 参数(size_t): count,要读取的数据元素的个数
//	// 参数(FILE *): stream,文件指针
//	// 返回值(size_t): 成功读取的元素个数
//	fread(&s, sizeof(struct Student), 1, pf); // 以二进制形式读取结构体数据
//	printf("%s %d %f", s.name, s.age, s.score); // 打印读取到的结构体数据
//	
//	fclose(pf);
//	pf == NULL;
//	return 0;
//}


// 4.1 对比一组函数:
// scanf 和 fprintf 和 sscanf
// printf 和 fscanf 和 sprintf

// scanf: 是针对标准输入的格式化输入语句
// printf: 是针对标准输出的格式化输出语句

// fprintf: 是针对任意输出流的格式化输出语句
// fscanf: 是针对任意输入流的格式化输入语句

// sscanf  :从字符串中读取格式化数据


// sprintf :将格式化数据写入字符串
// 把一个格式化的数据写到字符串中,本质是把一个格式化的数据转换成字符串
// sprintf是把一个格式化数据转换成字符串
//int main() {
//	struct Student s = { "zhangsan",25,50.f };
//	char buf[100] = { 0 };
//
//	// 把s中的格式化数据转换成字符串,放到buf中.
//	sprintf(buf, "%s %d %f\n", s.name, s.age, s.score);
//	printf("%s", buf); // 打印字符串
//	// "zhangsan 25 50.000000"
//
//	return 0;
//}


// sscanf从一个字符串中转换出一个格式化的数据.
int main() {
	struct Student temp = { 0 };
	char buf[] = "lisi 30 85.5";
	// 从字符串buf中获取一个格式化的数据到temp中
	sscanf(buf, "%s %d %f\n", temp.name, &(temp.age), &(temp.score));
	printf("%s %d %f\n", temp.name, temp.age, temp.score);

	// 如果字符串没有空格,那么sscanf就不能读出来了.

	return 0;
}

