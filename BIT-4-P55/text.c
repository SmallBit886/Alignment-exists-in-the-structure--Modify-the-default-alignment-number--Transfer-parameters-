#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <assert.h>

//特别热门的考点： 结构体内存对齐
//1.6 结构体内存对齐
//struct S1
//{
//	char c1;
//	int i;
//	char c2;
//};
//struct S2
//{
//	char c1;
//	char c2;
//	int i;
//};
//int main()
//{
//	//大小不匹配 : 已将“unsigned __int64”作为 _Param_(2) 传递，但需要使用“int”来调用“printf”
//	struct S1 s1 = { 0 };
//	printf("%d\n",(int)(sizeof(s1)));//12
//	struct S2 s2 = { 0 };
//	printf("%d\n", (int)sizeof(s2));//8
//	return 0;
//}

//练习-结构体嵌套问题
//struct S3
//{
//	double d;//8字节
//	char c;//1字节
//	int i;//偏移3字节 ，放4字节 ，一共16字节 ，是最大对齐数大小8字节的倍数
//};
//
//struct S4
//{
//	char c1;//1字节
//	struct S3 s3;//偏移7字节 ，放16字节
//	double d;//放8字节 ，一个32字节 ，是最大对齐数大小8字节的倍数
//};
//int main()
//{
//	printf("%d\n", sizeof(struct S3));//16字节
//	printf("%d\n", sizeof(struct S4));//32字节
//	return 0;
//}
/*
首先得掌握结构体的对齐规则:
1. 第一个成员在与结构体变量偏移量为0的地址处。
2. 其他成员变量要对齐到某个数字（对齐数）的整数倍的地址处。
对齐数 = 编译器默认的一个对齐数 与 该成员大小的较小值。
////////// VS中默认的值为8
/////////  gcc没有默认对齐数
Linux中没有默认对齐数，对齐数就是成员自身的大小
3. 结构体总大小为最大对齐数（每个成员变量都有一个对齐数）的整数倍
4. 如果嵌套了结构体的情况，嵌套的结构体对齐到自己的最大对齐数的整数倍处，结构体的整
体大小就是所有最大对齐数（含嵌套结构体的对齐数）的整数倍。
*/
/*
为什么存在内存对齐?
1. 平台原因(移植原因)：
不是所有的硬件平台都能访问任意地址上的任意数据的；
某些硬件平台只能在某些地址处取某些特定类型的数据，否则抛出硬件异常。
2. 性能原因：
数据结构(尤其是栈)应该尽可能地在自然边界上对齐。
原因在于，为了访问未对齐的内存，处理器需要作两次内存访问；而对齐的内存访问仅需要一次访问。

总体来说：
结构体的内存对齐是拿空间来换取时间的做法
*/

//在设计结构体的时候，我们既要满足对齐，又要节省空间
//让占用空间小的成员尽量集中在一起

//例如：
//struct S1//12字节
//{
//	char c1;
//	int i;
//	char c2;
//};
//struct S2//8字节
//{
//	char c1;
//	char c2;
//	int i;
//};
//S1和S2类型的成员一模一样，但是S1和S2所占空间的大小有了一些区别

//1.7 修改默认对齐数
// #pragma 这个预处理指令，可以改变我们的默认对齐数
//#pragma pack(4)//设置默认对齐数 为 4字节
//struct S
//{
//	char c1;//1字节
//	//3字节
//	double d;//8字节  默认对齐数为4  一共12字节  是4的倍数
//};
//
//#pragma pack(1)//设置默认对齐数为1
//struct S2
//{
//	char c1;
//	int i;
//	char c2;
//};
//#pragma pack()//取消设置的默认对齐数，还原为默认
//
//int main()
//{
//	struct S s;
//	printf("%d\n", sizeof(s));//12字节   //默认对齐数下为16字节
//	return 0;
//}

//百度笔试题：写一个宏，计算结构体中某变量相对于首地址的偏移，并给出说明
//考察： size_t offsetof(structName , memberName); 宏的实现 
//#include <stddef.h>
//struct s
//{
//	char c;
//	int i;
//	double d;
//};
//
//int main()
//{
//	//offsetof();
//	printf("%d\n", offsetof(struct s, c));//0
//	return 0;
//}


//1.8 结构体传参
struct S
{
	int data[1000];
	int num;
};
void Init(struct S* ps)
{
	*(ps->data) =1;
	ps->num = 10;
}
//结构体传参
void print1(struct S s)
{
	printf("%d\n", s.num);
}
//结构体地址传参
void print2(struct S* ps)
{
	printf("%d\n", ps->num);
}
int main()
{
	struct S s;
	Init(&s);
	print1(s); //传结构体
	print2(&s); //传地址
	return 0;
}
//结论：
//结构体传参的时候，要传结构体的地址。