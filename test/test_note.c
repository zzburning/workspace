Given the values of two nodes in a *binary search tree*, write a c program to find the lowest common ancestor. You may assume that both values already exist in the tree.

The function prototype is as follows: int FindLowestCommonAncestor(node* root,int value1,int value)
20
/ \
8 22
/ \
4 12
/ \
10 14
构筑函数： struct TreeNode * FindLowestCommonTreeNode(struct node *pNode,)

Struct TreeNode
{
int Data;
TreeNode *pLeft, *pRight;
}

FindLowestAncestor(Struct TreeNode *pRoot, Struct TreeNode *pNode1, Struct TreeNode *pNode2)
{
if (pRoot==NULL) 
return NULL;
if (pRoot==pNode1 && pRoot==pNode2) 
return pRoot;
Struct TreeNode *pTemp;
if (pTemp = FindLowestAncestor(pRoot->pLeft,pNode1,pNode2)) 
return pTemp;
if (pTemp = FindLowestAncestor(pRoot->pRight,pNode1,pNode2)) 
return pTemp;
if (FindLowestAncestor(pRoot,pNode1,pNode1) && FindLowestAncestor(pRoot,pNo
de2,pNode2)) return pRoot;

return NULL;
}


//线性链表的存储实现
struct LNODE{
ElemType data;
struct LNODE *next;
};
typedef struct LNODE LNode;
typedef struct LNODE * LinkList;

1初始化操作
Status Init_L(LinkList L){
if (L=(LinkList *)malloc(sizeof(LNode)))
{L->next=NULL;return 1;}
else return 0;
}
2插入操作
Status ListInsert_L(LinkList &L,int i,ElemType e){
p=L,j=0;
while(p&&j<i-1){p=p->next;++j;}
if(!p||j>i-1) return ERROR;
s=(LinkList)malloc(sizeof(LNode));
s->data=e;s->next=p->next;
p->next=s;
return OK;
}//ListInsert_L
 
3删除操作
Status ListDelete_L(LinkList &L,int i,ElemType &e){
p=L,j=0;
while(p&&j<i-1){p=p->next;++j;}
if(!p->next||j>i-1) return ERROR;
q=p->next;p->next=q->next;
e=q->data;free(q);
return OK;
}//ListDelete_L
 

4取某序号元素的操作
Status GetElem_L(LinkList &L,int i,ElemType &e){
p=L->next,j=1;
while(p&&j<i){p=p->next;++j;}
if(!p||j>i) return ERROR;
e=p->data;
return OK;
}//GetElem_L
5归并两个单链表的算法
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc){
//已知单链线性表La和Lb的元素按值非递减排列
//归并后得到新的单链线性表Lc,元素也按值非递减排列
pa=La->next;pb=Lb->next;
Lc=pc=La;
while(pa&&pb){
if(pa->data<=pb->data){
pc->next=pa;pc=pa;pa=pa->next;
}else{pc->next=pb;pc=pb;pb=pb->next;}
}
pc->next=pa?pa:pb;
free(Lb);
}//MergeList_L

全部用C语言完成：

1．自己定义数据结构，写出程序：在一个单向链表中，往I位置插入一个节点。
2．自己定义数据结构，写出程序：二叉树的前序遍历。
3．不允许使用系统时间，写出一个随机数生成函数。

%--  写一个在一个字符串(n)中寻找一个子串(m)第一个位置的函数。
KMP算法效率最好，时间复杂度是Ｏ(n+m)。

int findsubstr(const char *str,const char *substr)
{
	if(str==NULL || substr==NULL)
		return -1;
	const char *s=str;
	const char *p;
	while(p!=NULL)
	{
		p=substr;
		while(*s++!=*p)
		{
			if(s==NULL) goto NO;
		}
		
		while(*s++==*p++)
		{
			if(p==NULL)break;
			if(s==NULL)goto NO;
		}
	}
	return 0;
NO:
	return -1;
}






#--------------------------------------------------------------------------
%--  有哪几种情况只能用intialization list 而不能用assignment?
答案：当类中含有const、reference 成员变量；基类的构造函数都需要初始化表。


%--  比较C++中的4种类型转换方式？
请参考：http://blog.csdn.net/wfwd/archive/2006/05/30/7637%-- aspx，
重点是static_cast, dynamic_cast和reinterpret_cast的区别和应用。

%-- 进程间通信的方式有?
进程间通信的方式有 共享内存， 管道 ，Socket ，消息队列 , DDE等

对几种同步对象的总结
%-- Critical Section
A.速度快
B.不能用于不同进程
C.不能进行资源统计(每次只可以有一个线程对共享资源进行存取)
%-- Mutex
A.速度慢
B.可用于不同进程
C.不能进行资源统计
%-- Semaphore
A.速度慢
B.可用于不同进程
C.可进行资源统计(可以让一个或超过一个线程对共享资源进行存取)
%-- Event
A.速度慢
B.可用于不同进程
C.可进行资源统计

%-- 
const 符号常量；

(1)const char *p
(2)char const *p
(3)char * const p
(4)const char * const p

解析：const作用对象为距离最近的类型关键字，并最从向右原则。
(1)（const char） *p -------const修饰指针所指向的变量 *p，即*p为常量，p不是常量；
(2)char (const *)p	-------const修饰指针本身，即指针本身p是常量。
(3)char (* const) p	-----同上
(4)(const char) (* const) p	--------这种是地址及指向对象都不能修改。

//申请动态内存
//方法一：
#include <stdio.h>
char *GetMemory()
{
  char *p=(char *)malloc(100);
  return p;//-动态内存指针不能传回
}

int main(void)
{
  char *str=NULL;
  str=GetMemory();
  strcpy(str,"hello world");
  printf(str);
  
  return 0;
}

//方法二:
void GetMemory2(char **p, int num)
{
 *p = (char *)malloc(sizeof(char) * num);
}


#--------------------------------------------------------------------------
　　%--  将“引用”作为函数参数有哪些特点？
　　（1）传递引用给函数与传递指针的效果是一样的。这时，被调函数的形参就成为原来主调函数中的实参变量或对象的一个别名来使用，所以在被调函数中对形参变量的操作就是对其相应的目标对象（在主调函数中）的操作。
　　（2）使用引用传递函数的参数，在内存中并没有产生实参的副本，它是直接对实参操作；而使用一般变量传递函数的参数，当发生函数调用时，需要给形参分配存储单元，形参变量是实参变量的副本；如果传递的是对象，还将调用拷贝构造函数。因此，当参数传递的数据较大时，用引用比用一般变量传递参数的效率和所占空间都好。
　　（3）使用指针作为函数的参数虽然也能达到与使用引用的效果，但是，在被调函数中同样要给形参分配存储单元，且需要重复使用"*指针变量名"的形式进行运算，这很容易产生错误且程序的阅读性较差；另一方面，在主调函数的调用点处，必须用变量的地址作为实参。而引用更容易使用，更清晰。


　　%--  在什么时候需要使用“常引用”？
　　如果既要利用引用提高程序的效率，又要保护传递给函数的数据不在函数中被改变，就应使用常引用。常引用声明方式：const 类型标识符 &引用名=目标变量名；
　　引用型参数应该在能被定义为const的情况下，尽量定义为const 。


 　　%--  “引用”与多态的关系？
　　引用是除指针外另一个可以产生多态效果的手段。这意味着，一个基类的引用可以指向它的派生类实例。
　　
　  %--  什么时候需要“引用”？
　　流操作符<<和>>、赋值操作符=的返回值、拷贝构造函数的参数、赋值操作符=的参数、其它情况都推荐使用引用。
　　
	

#--------------------------------------------------------------------------
%-- 请简单描述Windows内存管理的方法。

内存管理是操作系统中的重要部分，两三句话恐怕谁也说不清楚吧～～

当程序运行时需要从内存中读出这段程序的代码。代码的位置必须在物理内存中才能被运行，由于现在的操作系统中有非常多的程序运行着，内存中不能够完全放下，所以引出了虚拟内存的概念。把哪些不常用的程序片断就放入虚拟内存，当需要用到它的时候再load入主存（物理内存）中。这个就是内存管理所要做的事。内存管理还有另外一件事需要做：计算程序片段在主存中的物理位置，以便CPU调度。

内存管理有块式管理，页式管理，段式和段页式管理。现在常用段页式管理

块式管理：把主存分为一大块、一大块的，当所需的程序片断不在主存时就分配一块主存空间，把程序片断load入主存，就算所需的程序片度只有几个字节也只能把这一块分配给它。这样会造成很大的浪费，平均浪费了50％的内存空间，但是易于管理。

页式管理：把主存分为一页一页的，每一页的空间要比一块一块的空间小很多，显然这种方法的空间利用率要比块式管理高很多。

段式管理：把主存分为一段一段的，每一段的空间又要比一页一页的空间小很多，这种方法在空间利用率上又比页式管理高很多，但是也有另外一个缺点。一个程序片断可能会被分为几十段，这样很多时间就会被浪费在计算每一段的物理地址上（计算机最耗时间的大家都知道是I/O吧）。

段页式管理：结合了段式管理和页式管理的优点。把主存分为若干页，每一页又分为若干段。好处就很明显，不用我多说了吧。




#--------------------------------------------------------------------------
　　%--  main 函数执行以前，还会执行什么代码？
　　答案：全局对象的构造函数会在main 函数之前执行。

　　%--  main 主函数执行完毕后，是否可能会再执行一段代码，给出说明？
　　答案：可以，可以用_onexit 注册一个函数，它会在main 之后执行int fn1(void), fn2(void), fn3(void), fn4 (void);

　　%--  描述内存分配方式以及它们的区别?
　　1） 从静态存储区域分配。内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在。例如全局变量，static 变量。
　　2） 在栈上创建。在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集。
　　3） 从堆上分配，亦称动态内存分配。程序在运行的时候用malloc 或new 申请任意多少的内存，程序员自己负责在何时用free 或delete 释放内存。 动态内存的生存期由程序员决定， 使用非常灵活， 但问题也最多。


#--------------------------------------------------------------------------
使用strcpy()需要小心 dest、res的长度，以及res的结束字符\0！！！即数组边界问题。
==数组越界
==strcpy拷贝的结束标志是查找字符串中的\0 因此如果字符串中没有遇到\0的话 会一直复制，直到遇到/0
==建议使用 strncpy 和 memcpy

printf并不是类型安全的，这就是为什么C++要引入cout的原因了。



　　5：什么是虚拟设备？为什么在操作系统中引入虚拟设备？（10分）
　　6：TCP为何采用三次握手来建立连接，若采用二次握手可以吗，请说明原因？（16分）
　　7：什么是分布式数据库？（12分）


/*
1.对数据库的一张表进行操作,同时要对另一张表进行操作,如何实现?? 
2.TCP/IP 建立连接的过程?(3-way shake) 
3.ICMP是什么协议,处于哪一层? 
4.触发器怎么工作的? 
5.winsock建立连接的主要实现步骤? 
6.动态连接库的两种方式? 
7.IP组播有那些好处? 
*/
1. 对数据库的一张表进行操作,同时要对另一张表进行操作,如何实现?? 
　　答案：将操作多个表的操作放入到事务中进行处理 

2. TCP/IP 建立连接的过程? ( 3 way shake) 
　　答案： 在TCP/IP协议中，TCP协议提供可靠的连接服务，采用三次握手建立一个连接。 
　　第一次握手：建立连接时，客户端发送syn包(syn=j)到服务器，并进入SYN_SEND状态，等待服务器确认； 
　　第二次握手：服务器收到syn包，必须确认客户的SYN（ack=j+1），同时自己也发送一个SYN包（syn=k），即SYN+ACK包，此时服务器进入SYN_RECV状态； 
　　第三次握手：客户端收到服务器的SYN＋ACK包，向服务器发送确认包ACK(ack=k+1)，此包发送完毕，客户端和服务器进入ESTABLISHED状态，完成三次握手。 
3. ICMP是什么协议,处于哪一层? 
　　答案：Internet控制报文协议，处于网络层（IP层） 
 4. 触发器怎么工作的? 
　　答案：触发器主要是通过事件进行触发而被执行的，当对某一表进行诸如UPDATE、 INSERT、 DELETE 这些操作时，数据库就会自动执行触发器所定义的SQL 语句，从而确保对数据的处理必须符合由这些SQL 语句所定义的规则。 
5. winsock建立连接的主要实现步骤? 
　　答案：服务器端：socker()建立套接字，绑定（bind）并监听（listen），用accept（）等待客户端连接。客户端：socker()建立套接字，连接（connect）服务器，连接上后使用send()和recv（），在套接字上写读数据，直至数据交换完毕，closesocket()关闭套接字。 
　　服务器端：accept（）发现有客户端连接，建立一个新的套接字，自身重新开始等待连接。该新产生的套接字使用send()和recv（）写读数据，直至数据交换完毕，closesocket()关闭套接字。 
6. 动态连接库的两种方式? 
　　答案：调用一个DLL中的函数有两种方法： 
　　1．载入时动态链接（load-time dynamic linking），模块非常明确调用某个导出函数，使得他们就像本地函数一样。这需要链接时链接那些函数所在DLL的导入库，导入库向系统提供了载入DLL时所需的信息及DLL函数定位。 
　　2．运行时动态链接（run-time dynamic linking），运行时可以通过LoadLibrary或LoadLibraryEx函数载入DLL。DLL载入后，模块可以通过调用GetProcAddress获取DLL函数的出口地址，然后就可以通过返回的函数指针调用DLL函数了。如此即可避免导入库文件了。 
7. IP组播有那些好处? 
　　答案：Internet上产生的许多新的应用，特别是高带宽的多媒体应用，带来了带宽的急剧消耗和网络拥挤问题。组播是一种允许一个或多个发送者（组播源）发送单一的数据包到多个接收者（一次的，同时的）的网络技术。组播可以大大的节省网络带宽，因为无论有多少个目标地址，在整个网络的任何一条链路上只传送单一的数据包。所以说组播技术的核心就是针对如何节约网络资源的前提下保证服务质量。 


1、 分数统计（15） 
要求： 
（1）输入某班级学生的姓名、分数； 
（2）对（1）的分数进行降幂排列并输出； 
（3）具有输入输出界面。 

2、 打字程序（15） 
要求： 
（1）随即产生一字符串，每次产生的字符串内容、长度都不同； 
（2）根据（1）的结果，输入字符串，判断输入是否正确，输出正确率； 
（3）具有输入输出界面。 

3、 文本编辑器（15） 
要求： 
（1）编辑文本； 
（2）保存、打开指定位置的文本文件； 
（3）具有输入输出界面。 

4、 加密（15） 
要求： 
（1）输入任意一段明文M，以及密钥K; 
（2）根据一下公式将其转换为密文C。 
Ci = mi + K ,其中i = 0,1,……n-1 , K 为密钥； 
（3）具有输入输出界面。 

5、进制转换器（15） 
要求： 
（1）可输入二进制、八进制、十进制、十六进制数； 
（2）将已输入的数转换成其余进制的数； 
（3）具有输入输出界面。


1。在字符串S中寻找最长的字符串x，条件是x存在于S中。即是如：abcabcdcd中的abc。 

2。求Fibonacci数列中第k个与前面所有数互质的数（除前面两个数 1，1 ）。 

3。有100个真币和一个假币，只知道真币与假币不等重，要求只称两次，得出是真币重还是假币重。 

　　1） C++中引用编译过的C代码为什么要用“extern c” 

　　2） 类与struct的区别 

　　3）数据库建表的SQL语句，注意主键与外键是如何建立的 

　　4）文件的外排序，考虑到CPU，内存，硬盘空间等。


 

1.请定义一个宏，比较两个数a、b的大小，不能使用大于、小于、if语句 
2.如何输出源文件的标题和目前执行行的行数 
3.两个数相乘，小数点后位数没有限制，请写一个高精度算法 
4.写一个病毒 
有A、B、C、D四个人，要在夜里过一座桥。他们通过这座桥分别需要耗时1、2、5、10分钟 
，只有一支手电，并且同时最多只能两个人一起过桥。请问，如何安排，能够在17分钟内 
这四个人都过桥？ 
 
3, printf("0x%x", (&0)[-1]); 请问打印了什么? 
4, 结构体内某项偏移地址 
5, 汇编,用ax,bx,cx,dx, 求1000*1000/30(四舍五入), 结果放在ax中. 
6, 1,2,3,4,5,6,7,8,9从栈里出来的可能性. 
7, 求一个struct的sizeof.(略) 
8, 编最优化Bubble(int *pIntArray,int L),要求:交换元素不能用临时变量,如果有序, 
需要最优. 

 

1，程序设计（可以用自然语言来描述，不编程）：C/C++源代码中，检查花括弧（是"（"与
"）"，"{"与"}"）是否匹配，若不匹配，则输出不匹配花括弧所在的行与列。


2，巧排数字，将1,2,...,19,20这20个数字排成一排，使得相邻的两个数字之和为一个素数，且
首尾两数字之和也为一个素数。编程打印出所有的排法。


3，打印一个N*N的方阵，N为每边字符的个数（ 3〈N〈20 ），要求最外层为"X"，第二层为"Y"，从第三层起每层依次打印数字0，1，2，3，...
例子：当N =5，打印出下面的图形：
X X X X X
X Y Y Y X
X Y 0 Y X
X Y Y Y X
X X X X X 
 

 要求15分钟完成。
　　1、简述ICQ或OICQ的工作原理。
　　2、WINDOWS下C++如何申请内存？
　　3、怎么使用VC++获得一个命令按钮的句柄？
　　4、JAVA和C++有什么区别？
　　5、LINUX的常见目录有什么？
　　6、有什么办法可以让一个程序一直运行并能够处理多个用户的login和logout操作？
　　7、
　　typedef struct{
　　 void (*ver)();
　　 int *p1;
　　}abc;
　　abc s={f1,&p1}, *s1;
　　int p1;
　　void f1(int *a){……}
　　Please use the pointer s1 reference(call) the function f1 and pass the parameter p1 to the function. The call syntax should not contain f1 and p1. 

嵌入式程序员应知道的0x10个基本问题

1.用预处理指令#define 声明一个常数，用以表明1年中有多少秒（忽略闰年问题）
#define SECONDS_PER_YEAR (60 * 60 * 24 * 365)UL

2 . 写一个"标准"宏MIN ，这个宏输入两个参数并返回较小的一个。
#define MIN(A,B) （（A） <= (B) ? (A) : (B)) 

3. 预处理器标识#error的目的是什么

4. 嵌入式系统中经常要用到无限循环，你怎么样用C编写死循环呢？
这个问题用几个解决方案。我首选的方案是：
while(1)
{;}

数据声明（Data declarations） 
5. 用变量a给出下面的定义
a) 一个整型数（An integer） 
b)一个指向整型数的指针（ A pointer to an integer） 
c)一个指向指针的的指针，它指向的指针是指向一个整型数（ A pointer to a pointer to an intege）r 
d)一个有10个整型数的数组（ An array of 10 integers） 
e) 一个有10个指针的数组，该指针是指向一个整型数的。（An array of 10 pointers to integers） 
f) 一个指向有10个整型数数组的指针（ A pointer to an array of 10 integers） 
g) 一个指向函数的指针，该函数有一个整型参数并返回一个整型数（A pointer to a function that takes an integer as an argument and returns an integer） 
h)一个有10个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数（ An array of ten pointers to functions that take an integer argument and return an integer ）
答案是： 
a) int a; // An integer 
b) int *a; // A pointer to an integer 
c) int **a; // A pointer to a pointer to an integer 
d) int a[10]; // An array of 10 integers 
e) int *a[10]; // An array of 10 pointers to integers 
f) int (*a)[10]; // A pointer to an array of 10 integers 
g) int (*a)(int); // A pointer to a function a that takes an integer argument and returns an integer 
h) int (*a[10])(int); // An array of 10 pointers to functions that take an integer argument and return an integer 

static
6. 关键字static的作用是什么？

const 
7．关键字const有什么含意？

volatile
8. 关键字volatile有什么含意?并给出三个不同的例子。
一个定义为volatile的变量是说这变量可能会被意想不到地改变，这样，编译器就不会去假设这个变量的值了。精确地说就是，优化器在用到这个变量时必须每次都小心地重新读取这个变量的值，而不是使用保存在寄存器里的备份。下面是volatile变量的几个例子：
; 并行设备的硬件寄存器（如：状态寄存器）
; 一个中断服务子程序中会访问到的非自动变量(Non-automatic variables)
; 多线程应用中被几个任务共享的变量

位操作（Bit manipulation） 
9. 嵌入式系统总是要用户对变量或寄存器进行位操作。

10. 嵌入式系统经常具有要求程序员去访问某特定的内存位置的特点。

中断（Interrupts） 
11. 中断是嵌入式系统中重要的组成部分，这导致了很多编译开发商提供一种扩展—让标准C支持中断。

代码例子（Code examples）
12 . 下面的代码输出是什么，为什么？
void foo(void)
{
unsigned int a = 6;
int b = -20;
(a+b > 6) ? puts("> 6") : puts("<= 6");
}

13. 评价下面的代码片断：
unsigned int zero = 0;
unsigned int compzero = 0xFFFF; 
/*1's complement of zero */

15 Typedef


考了几道网络、硬件，之后有三道编译题目。 
1、已知mac地址，如何得到ip地址。知道ip地址，如何得到mac地址。 
2、ping用了什么协议 
3、Tcp/ip的协议栈 
4、dhcp功能 
5、pc机bios有哪几个模块 
6、列出你用过的和知道的编译器和解释器 
7、编译器有哪几个模块 
8、列出你用过的单片机及其编译器 
9、硬盘的柱面、track、扇区的关系图 
13、根据程序列出变量a、b、c最可能分配的段。 stack段 data段 heap段 bss段 txt段 int a; int b = 3; 
main() 
{ 
int c; a = b; c =a; 
} 
14、写出程序的结果。 
int *pChar; int *pInt; int nValue[10]; 
void main() 
{ 
int i; 
for(i =0; i<10;i++) nValue[i] = i; 
pChar = (char *)nValue; pInt = (int *)nValue; pChar += 6; pInt += 6; printf("*pChar = %d\r\n", *pChar); 
printf("*pInt = %d\r\n", *pInt); } 
15、写出下面程序的结果 
class A { 
public: 
A() { m_pData = NULL; } 
A(LPSTR p) { int n = strlen(p); m_pData = new char[n+1]; memset(m_pData, 0, n+1); memcpy(m_pData, p, n); printf("Data=%d,Len =%d\n", m_pData, n); } ~A() { delete[] m_pData; } private: char * m_pData; } void main() { A* pObj1 = new A("ABC"); A* pObj2 = pObj1; A aObj1("DEF"); A aObj2=aObj1; delete pObj2; }


1．实现双向链表删除一个节点P，在节点P后插入一个节点，写出这两个函数。 

2．写一个函数，将其中的\t都转换成4个空格。 

3．Windows程序的入口是哪里？写出Windows消息机制的流程。 

4．如何定义和实现一个类的成员函数为回调函数？ 

5．C++里面是不是所有的动作都是main()引起的？如果不是，请举例。 

6．C++里面如何声明const void f(void)函数为C程序中的库函数？ 

7．下列哪两个是等同的 

int b; 

A const int* a = &b; 

B const* int a = &b; 

C const int* const a = &b; 

D int const* const a = &b; 

8．内联函数在编译时是否做参数类型检查？ 

void g(base & b){ 

b.play; 

} 

void main(){ 

son s; 

g(s); 

return; 

} 

1 写出程序把一个链表中的接点顺序倒排
typedef struct linknode
{
int data;
struct linknode *next;
}node;
//将一个链表逆置
node *reverse(node *head)
{
node *p,*q,*r;
p=head;
q=p->next;
while(q!=NULL)
{
r=q->next;
q->next=p;
p=q;
q=r;
}

head->next=NULL;
head=p;
return head;
}
2 写出程序删除链表中的所有接点
void del_all(node *head)
{
node *p;
while(head!=NULL)
{
p=head->next;
free(head);
head=p;
}
cout<<"释放空间成功!"<<endl;
}
3两个字符串，s,t;把t字符串插入到s字符串中，s字符串有足够的空间存放t字符串
void insert(char *s, char *t, int i)
{
char *q = t;
char *p =s;
if(q == NULL)return;
while(*p!='\0')
{
p++;
}
while(*q!=0)
{
*p=*q;
p++;
q++;
}
*p = '\0';
}


分析下面的代码：
char *a = "hello";
char *b = "hello";
if(a= =b)
printf("YES");
else
printf("NO");
这个简单的面试题目,我选输出 no(对比的应该是指针地址吧),可在VC是YES 在C是NO
lz的呢，是一个常量字符串。位于静态存储区，它在程序生命期内恒定不变。如果编译器优化的话，会有可能a和b同时指向同一个hello的。则地址相同。如果编译器没有优化，那么就是两个不同的地址，则不同

题目分成三个部分：软件、嵌入式、通信，前两部分任选一部分做答，通信为必答。 
软件部分1：定义class A、class B，内部各有一两个虚函数，值得慎重的是析构函 数也是虚函数。然后class C继承了A和B，程序中生成C的对象，考了一些虚函数方面的 东西。麻烦在于C对象析构时做了写什么事情？ 
2：考的是win32下的整型、字符、指针变量的大小。 
3：好像是要改什么错，可惜那个错误我实在拿不准，呵呵，不提了。 
4：win32下，写出用于线程/进程同步的三个内核对象。（一点也不会，空着） 
5：COM原理吧，好像是描述IUnknown的三个什么对象（？函数）的作用 
6：网络编程，socket绑定了缺省IP的8000端口，用netstat却看到绑定的是什么15346端口，解释原因？ 
嵌入式系统的不记得了，今天才算认识到嵌入式原来是这样di 
通信部分1：ISDN的Q.931对应OSI的哪一层？（偶答错了，应该是网络层，乱写成数据链路层了） 
2：举出三个TCP/IP应用层协议的例子（too naive！） 
3：描述TCP的窗口作用（too simple！） 
4：举出两种基本的复用方式，三种基本的调制方法（too old！呵呵，可惜我答的不是很准确） 
5：描述电路交换和分组交换的区别，以及虚电路技术的概念。 总体感觉，对C＋＋尤其是VC要求比较高，通信部分考的太业余了。


一、判断题（对的写T，错的写F并说明原因，每小题4分，共20分）

1、有数组定义int a[2][2]={,{2,3}};则a[0][1]的值为0。（ ）

2、int (*ptr) (),则ptr是一维数组的名字。（ ）

3、指针在任何情况下都可进行>,<,>=,<=,==运算。（ ）

4、switch(c) 语句中c可以是int ,long,char ,float ,unsigned int 类型。（ ）

5、#define print(x) printf(＂the no, ＂#x＂,is ＂)



二、填空题（共30分）

1、在windows下，写出运行结果，每空2分，共10分。

char str[ ]= ＂Hello＂;

char *p=str;

int n=10;

sizeof(str)=( )

sizeof(p)=( )

sizeof(n)=( )



void func(char str[100])

{ }

sizeof(str)=( )



2、void setmemory(char **p, int num)

{ *p=(char *) malloc(num);}

void test(void)

{ char *str=NULL;

getmemory(&str,100);

strcpy(str,＂hello＂);

printf(str);

}

运行test函数有什么结果？（ ）10分



3、设int arr[]={6,7,8,9,10};

int *ptr=arr;

*(ptr++)+=123;

printf(＂%d,%d＂,*ptr,*(++ptr));

( ) 10分



二、编程题（第一小题20，第二小题30分）

1、 不使用库函数，编写函数int strcmp(char *source, char *dest)

相等返回0，不等返回-1；



2、 写一函数int fun(char *p)判断一字符串是否为回文，是返回1，不是返回0，出错返回-1



　加拿大著名电信设备制造商北电网络公司始建于一个世纪以前，在通讯发展进步历程中始终处于领袖地位，广东北电通信设备有限公司成立于1995年3月，是北电在华投资的核心公司之一。

　　待遇：硕士7K，本科5.5K，很不错。一年13个月工资

　　1）笔试C++：考的比较难，一共4题，1个小时完成：

　　1.英译汉

　　做完花了15分钟，英语菜就一个字！

　　2.中序遍历一个二叉树，不能用递归 

　　地球上的人都知道要压栈，但平时根本就是在用递归解决。当时现场比划，花了近30分钟才勉强写到试卷上，汗颜！如果后序更麻烦。 

　　3.双向冒泡程序改错——3个错误

　　看来看去，只发现了2个错误。 

　　4.回答程序所完成的功能－共5问

　　题目有3页纸，都还没来的急看完，更别说写字了，收卷！

　　试卷一共13页纸，出来晕倒一大片！真不知道他在考什么。

　　以下是中大考试题目，要简单多了：

　　1.IS95标准，关于CDMA发展。汉译英

　　2.编程题

　　输入年月日格式yyyymmdd，判断是否是周末，只要求对2005年判断。

　　3.分析题：有关移动通信编码，位图什么的，好像是输入一串数据，根据题目比编码方法 ，写出编码后结果，好像没多少人会做 

　　2） 面试

　　1.多进程与多线程的区别与通信

　　2.测试方法

　　3.C++中的多态在C中如何实现 


Q1：请你分别划划OSI的七层网络结构图，和TCP/IP的五层结构图？ 

Q2：请你详细的解释一下IP协议的定义，在哪个层上面，主要有什么作用？ TCP与UDP呢？ 

Q3：请问交换机和路由器分别的实现原理是什么？分别在哪个层次上面实现的？ 

Q4:请问C++的类和C里面的struct有什么区别？ 



Q1 OSI的七层网络结构图——物理层/数据链路层/网络层/传输层/会话层/表示层/应用层
TCP/IP的五层网络结构图——应用层/传输层/网络层/链路层/物理层
Q2 IP协议的定义——因特网协议或网际协议（Internet Protocol）。对应于网络层，
它自身采用4层结构模型：应用层/传输层/网际层/网络接口层
作用在于规定了互连网上传输数据的确切格式及完成路由选择的功能，选择一个数据发送的路径。
TCP协议的主要是提供可靠的传输服务，而UDP（用户数据报协议）是定义用来在互连网络环境中
提供包交换的计算机通信的协议。此协议默认认为网路协议（IP）是其下层协议。此协议提供了
向另一用户程序发送信息的最简便的协议机制。
Q3 交换发生在网络的数据链路层，而路由则发生于网络层。数据链路层的转发即称为交换，而路径选
择即指路由，通常，路由器的性能比交换机要差一些，因为路由器是基于软件的查表转发，而交换
机可以实现硬件的直通式转发。
Q4 区别在于C里面的struct没有定义方法，而C++的类是将不同类型的数据和与这些数据相关的操作封
装在一起的集合体，包含了操作方法。 


第一部分 
Basics 应该是常识题 


考了一些 Threads,Memory Manager, HTTP 
session ,OSI&HTTP,Heap&Stack,BTree,Sorting Algorithm 等等
这部分我答的很菜 因为没有复习且荒于时间 估计要覆没了 
基本的内容还是操作系统和数据结构 

第二部分

Reasoning 和以前GRE的Analitical很像 有组题 也有单题 

做的还算比较爽

第三部分

Programming 

一道题 
一个单向链表 给出 链表头pHead 和 另一个链表中位置pStartNode
要把它转化为 以pStartNode为头的链表 但元素链接方向相反了

例如 
p1->p2->p3->p4->p5->null pHead=p1;pStartNode=p3
转换后 变成了 p3->p2->p1->p5->p4->null;

我也rush的写完了 

第四部分 

Design

给了一个Outlook2003 的图 
要求你给新的Outlook提建议和新的feature

第五部分 

Testing 

一个是要测试一个 一堆矩阵的重合区域的程序

找bug 并提供测试例子


另一个是给 字符串拷贝 strcpy找测试例子

微软笔试编程题(25分， 30分钟)
将一个链表按照规定的开始位置倒序排列，例如：
N1->N2->N3->N4->N5->NULL,给定的pHead = N1, pStartNode = N3,
倒序后变成：N3->N2->N1->N5->N4->NULL
N1->N2->N3->N4->N5->NULL,给定的pHead = N1, pStartNode = N1,
倒序后变成：N1->N5->N4->N3->N2->NULL
N1->N2->N3->N4->N5->NULL,给定的pHead = N1, pStartNode = N5,
倒序后变成：N5->N4->N3->N2->N1->NULL 


1）此题10分 
对任意输入的正整数N，编写C程序求N!的尾部连续0的个数，并指出计算复杂度。如：18！＝6402373705728000，尾部连续0的个数是3。 
（不用考虑数值超出计算机整数界限的问题） 

2）此题10分 
编写一个C语言函数，要求输入一个url，输出该url是首页、目录页或者其他url 
如下形式叫做首页： 
militia.info/ 
www.apcnc.com.cn/ 
http://www.cyjzs.comwww.greena888.com/ 
www.800cool.net/ 
http://hgh-products.my-age.net/ 
如下形式叫做目录页： 
thursdaythree.net/greenhouses--gas-global-green-house-warming/ 
http://www.mw.net.tw/user/tgk5ar1r/profile/ 
http://www.szeasy.com/food/yszt/chunjie/ 
www.fuckingjapanese.com/Reality/ 

请注意： 
a） url有可能带http头也有可能不带 
b）动态url（即含有"？"的url）的一律不算目录页，如： 
www.buddhismcity.net/utility/mailit.php?l=/activity/details/3135/ 
www.buddhismcity.net/utility/mailit.php?l=/activity/details/2449/ 

另：如果你会linux，请用linux下的grep命令实现第2题的功能（附加5分）。 

3）此题40分 
如果必须从网页中区分出一部分"重要网页"（例如在10亿中选8亿），比其他网页更值得展现给用户，请提出一种方案。 

4）此题40分 
假设有10亿网页已经被我们存下来，并提供如下信息：网页全文（即网页的源码）、全文长度、网页正文（即网页中提取的主体文字）、 
正文长度，以及其他网页提取物等，现在希望去掉其中的重复网页，请提出可行的方案，计算出每个网页对应的重复度，你可以自己 
对网页重复下定义，也可以提出需要哪些更多的网页提取物来实现更好的去重复方案 


 

1、请实现两棵树是否相等的比较，相等返回，否则返回其他值，并说明算法复杂度。
数据结构为：
typedef struct_TreeNode{
char c;
TreeNode *leftchild;
TreeNode *rightchild;
}TreeNode;
函数接口为：int CompTree(TreeNode* tree1,TreeNode* tree2);
注：A、B两棵树相等当且仅当Root->c==RootB-->c,而且A和B的左右子树相等或者左右互换相等。

2、写一段程序，找出数组中第k大小的数，输出数所在的位置。例如{2，4，3，4，7}中，第一大的数是7，位置在4。第二大、第三大的数都是4，位置在1、3随便输出哪一个均可。
函数接口为：int find_orderk(const int* narry,const int n,const int k)

2'、已知一个字串由GBK汉字和ansi编码的数字字母混合组成，编写c语言函数实现从中去掉所有ansi编码的字母和数字(包括大小写),要求在原字串上返回结果。
函数接口为：int filter_ansi(char* gbk_string)
注：汉字的GBK编码范围是0x8140-0xFEFE



百度笔试题（感谢网友lihan提供） 
shury 发表于 2005-12-5 17:05:00 

1）此题10分 
对任意输入的正整数N，编写C程序求N!的尾部连续0的个数，并指出计算复杂度。如：18！＝6402373705728000，尾部连续0的个数是3。 
（不用考虑数值超出计算机整数界限的问题） 

2）此题10分 
编写一个C语言函数，要求输入一个url，输出该url是首页、目录页或者其他url 
如下形式叫做首页： 
militia.info/ 
www.apcnc.com.cn/ 
http://www.cyjzs.comwww.greena888.com/ 
www.800cool.net/ 
http://hgh-products.my-age.net/ 
如下形式叫做目录页： 
thursdaythree.net/greenhouses--gas-global-green-house-warming/ 
http://www.mw.net.tw/user/tgk5ar1r/profile/ 
http://www.szeasy.com/food/yszt/chunjie/ 
www.fuckingjapanese.com/Reality/ 

请注意： 
a） url有可能带http头也有可能不带 
b）动态url（即含有"？"的url）的一律不算目录页，如： 
www.buddhismcity.net/utility/mailit.php?l=/activity/details/3135/ 
www.buddhismcity.net/utility/mailit.php?l=/activity/details/2449/ 

另：如果你会linux，请用linux下的grep命令实现第2题的功能（附加5分）。 

3）此题40分 
如果必须从网页中区分出一部分"重要网页"（例如在10亿中选8亿），比其他网页更值得展现给用户，请提出一种方案。 

4）此题40分 
假设有10亿网页已经被我们存下来，并提供如下信息：网页全文（即网页的源码）、全文长度、网页正文（即网页中提取的主体文字）、 
正文长度，以及其他网页提取物等，现在希望去掉其中的重复网页，请提出可行的方案，计算出每个网页对应的重复度，你可以自己 
对网页重复下定义，也可以提出需要哪些更多的网页提取物来实现更好的去重复方案 

 

 
1。简单介绍一下你做的项目
2。sturct和class的区别
3。虚函数和纯虚函数的区别，作用
4。有没有碰到过内存泄漏，怎么解决 
5。老师对你的评价
6。你认为哪个老师比较牛，为什么？
7。同学们怎么评价你的，你同学认为你哪方面比较牛？
8。平时有什么兴趣和爱好


两个字符串，s,t;把t字符串插入到s字符串中，s字符串有足够的空间存放t字符串
void insert(char *s, char *t, int i)
{
memcpy(&s[strlen(t)+i],&s[i],strlen(s)-i);
memcpy(&s[i],t,strlen(t));
s[strlen(s)+strlen(t)]='\0';
}

1。编写一个 C 函数，该函数在一个字符串中找到可能的最长的子字符串，且该字符串是由同一字符组成的。
char * search(char *cpSource, char ch)
{
char *cpTemp=NULL, *cpDest=NULL;
int iTemp, iCount=0;
while(*cpSource)
{
if(*cpSource == ch)
{
iTemp = 0;
cpTemp = cpSource;
while(*cpSource == ch) 
++iTemp, ++cpSource;
if(iTemp > iCount) 
iCount = iTemp, cpDest = cpTemp;
if(!*cpSource) 
break;
}
++cpSource;
}
return cpDest;
} 
2。请编写一个 C 函数，该函数在给定的内存区域搜索给定的字符，并返回该字符所在位置索引值。
int search(char *cpSource, int n, char ch)
{
int i;
for(i=0; i<n && *(cpSource+i) != ch; ++i);
return i;
}

一个单向链表，不知道头节点,一个指针指向其中的一个节点，问如何删除这个指针指向的节点？
将这个指针指向的next节点值copy到本节点，将next指向next->next,并随后删除原next指向的节点。


#include <stdio.h>
void foo(int m, int n)
{
printf("m=%d, n=%d\n", m, n);
}

int main()
{
int b = 3;
foo(b+=3, ++b);
printf("b=%d\n", b);
return 0;
}
输出：m=7,n=4,b=7(VC6.0)
这种方式和编译器中得函数调用关系相关即先后入栈顺序。不过不同
编译器得处理不同。也是因为C标准中对这种方式说明为未定义，所以
各个编译器厂商都有自己得理解，所以最后产生得结果完全不同。
因为这样，所以遇见这种函数，我们首先要考虑我们得编译器会如何处理
这样得函数，其次看函数得调用方式，不同得调用方式，可能产生不同得
结果。最后是看编译器优化。


2.写一函数，实现删除字符串str1中含有的字符串str2.
第二个就是利用一个KMP匹配算法找到str2然后删除（用链表实现的话，便捷于数组）


 

C++/C试题 
本试题仅用于考查C++/C程序员的基本编程技能。内容限于C++/C常用语法，不涉及数据结 
构、算法以及深奥的语法。考试成绩能反映出考生的编程质量以及对C++/C的理解程度，但 
不能反映考生的智力和软件开发能力。 
笔试时间90分钟。请考生认真答题，切勿轻视。 

一、请填写BOOL , float, 指针变量 与“零值”比较的 if 语句。（10分） 
提示：这里“零值”可以是0, 0.0 , FALSE或者“空指针”。例如 int 变量 n 与“零值 
”比较的 if 语句为： 
if ( n == 0 ) 
if ( n != 0 ) 
以此类推。 

请写出 BOOL flag 与“零值”比较的 if 语句： 
请写出 float x 与“零值”比较的 if 语句： 
请写出 char *p 与“零值”比较的 if 语句： 

二、以下为Windows NT下的32位C++程序，请计算sizeof的值（10分） 

char str[] = “Hello” ; char *p = str ;int n = 10;请计算sizeof (str ) 
= sizeof ( p ) = sizeof ( n ) = void Func ( 
char str[100]){请计算 sizeof( str ) = } 
void *p = malloc( 100 );请计算sizeof ( p ) = 

三、简答题（25分） 

1、头文件中的 ifndef/define/endif 干什么用？ 



2、#include 和 #include “filename.h” 有什么区别？ 



3、const 有什么用途？（请至少说明两种） 



4、在C++ 程序中调用被 C编译器编译后的函数，为什么要加 extern “C”声明？ 




5、请简述以下两个for循环的优缺点 

// 第一个for (i=0; i ing();} // 第二个if (condition){for (i=0; i for (i=0; i 优点：缺点： 优点：缺点： 

四、有关内存的思考题（20分） 

void GetMemory(char *p){p = (char *)malloc(100);}void Test(void) {char *str = 
NULL;GetMemory(str); strcpy(str, "hello world");printf(str);}请问运行Test函数会 
有什么样的结果？答： char *GetMemory(void){ char p[] = "hello world";return p; 
}void Test(void){char *str = NULL;str = GetMemory(); printf(str);}请问运行Test 
函数会有什么样的结果？答： 
Void GetMemory2(char **p, int num){*p = (char *)malloc(num);}void Test(void){c 
har *str = NULL;GetMemory(&str, 100);strcpy(str, "hello"); printf(str); }请问运 
行Test函数会有什么样的结果？答： void Test(void){char *str = (char *) malloc(1 
00); strcpy(str, “hello”); free(str); if(str != NULL) { strcpy(str, “ 
world”); printf(str);}}请问运行Test函数会有什么样的结果？答： 


五、编写strcpy函数（10分） 
已知strcpy函数的原型是 
char *strcpy(char *strDest, const char *strSrc); 
其中strDest是目的字符串，strSrc是源字符串。 

（1）不调用C++/C的字符串库函数，请编写函数 strcpy 







（2）strcpy能把strSrc的内容复制到strDest，为什么还要char * 类型的返回值？ 




六、编写类String的构造函数、析构函数和赋值函数（25分） 
已知类String的原型为： 
class String 
{ 
public: 
String(const char *str = NULL); // 普通构造函数 
String(const String &other); // 拷贝构造函数 
~ String(void); // 析构函数 
String & operate =(const String &other); // 赋值函数 
private: 
char *m_data; // 用于保存字符串 
}; 
请编写String的上述4个函数。 

 

 1:写出输出 

void fun(int i) { 
static int value=i++; 
cout<<value; 
} 

int main() { 
fun(0); 
fun(1); 
fun(2); 
} 


2:引用和指针之间有什么区别? 

3:比较全局变量和静态变量,试说明两者有何异同. 

4:分析代码,给出i,j,k的结果. 

int i,j,k; 
i=j=k=0; 
if(++i||j++||++k) {} 

5:说出如下const声明的含义: 
1.const char* p 
2.char const* p 
3.char* const p 
4.char A::fun() const; 

6:编译下面的代码,会有什么结果? 

1: 
void fun(char); 
void fun(char*); 
int main() 
{ 
fun(0); 
} 

2: 
void fun(int); 
void fun(int*); 
int main() 
{ 
fun(0); 
} 

7:请写出程序运行的结果 

class A{ 
public: 
A() { cout<<"A::A()"<<endl;} 
~A() { cout<<"A::~A()"<<endl;} 
}; 

class B{ 
public: 
B() {cout<<"B::B()"<<endl;} 
~B() {cout<<B::~B()"<<endl;} 
}; 

class C:public B{ 
A a; 
public: 
C() {cout<<"C::C()"<<endl;} 
~C() {cout<<"C::~C()"<<endl;} 
}; 

A a; 
int main() 
{ 
C c; 
} 


8:请写出程序运行的结果 

class A{ 
public: 
A() {cout<<"A::A()"<<endl;} 
~A() {cout<<"A::~A()"<<endl;} 
}; 

class B{ 
public: 
B(){cout<<"B::B()"<<endl;} 
~B(){cout<<"B::~B()"<<endl;} 
}; 

class C:public B{ 
public: 
C():a(A()),b(B()){} 
~C(){} 

private: 
B b; 
A a; 
}; 

int main() 
{ 
C c; 
} 

9:请写出程序运行的结果 

#include<iostream> 
using namespace std; 

class base{ 
public: 
virtual void print() const {cout<<"base::f()"<<endl;} 
}; 


class derived:public base { 
public: 
virtual void print() const {cout<<"derived::f()"<<endl;} 
}; 

void print(const base& obj) 
{ 
obj.print(); 
} 


int main() 
{ 
base* pb1=new derived(); 
print(*pb1); 

base* pb2=new base(*pb1); 
print(*pb2); 

base b=base(derived()); 
print(b); 

delete pb1; 
delete pb2; 

return 0; 
} 


10:什么是抽象类? 

11:什么时候需要使用虚拟析构函数? 

12:抽象基类的抽象虚析构函数一定要有函数体吗? 为什么? 

13:下面的代码是否有错误? 如果有错,请说明原因. 

char* const s="hello"; 
s[0]='a'; 

14:分析如下代码是否存在问题 

const char* hello() {return "hello world";} 

int main() 
{ 
const char* pc=hello(); 
cout<<pc; 
} 

15:分析下面代码,指出问题 

class obj{}; 

1. obj& fun() {obj o;return o;} 
2. obj* fun() {obj o;return &o;} 
3. obj fun() {obj o;return o;} 

16:什么是函数重载? 

17:面向对象有哪三个要素? 

18:什么是多态?C++如何实现多态? 

19:构造函数没有返回值,那么如何得知对象是否构造成功? 

20:编译一个C/C++程序通常有哪几个阶段? 

21:请指出下面代码存在的问题 

class CC{ 
int* m_pCount; 

public: 
void clear(){ if (m_pCount) delete m_pCount;} 
CC(){m_pCount=new int;} 
~CC() {clear();} 
}; 

22:请指出如下代码的问题所在 

void ex() { 
throw exception("exception"); 
} 

void fun() { 
char* buf=new char[64]; 
ex(); 
delete[] buf; 
} 

23:写出程序输出 

void ex() 
{ throw exception("exception");} 

void fun() 
{ 
try{ex();} 
catch(exception*) {cout<<"exception*"<<endl;} 
catch(exception&) { cout<<"exception&"<<endl"} 
catch(...) { cout<<"..."<<endl;} 
} 

 


1．完成下列程序
*
*.*.
*..*..*..
*...*...*...*...
*....*....*....*....*....
*.....*.....*.....*.....*.....*.....
*......*......*......*......*......*......*......
*.......*.......*.......*.......*.......*.......*.......*.......
#include
#define N 8
int main()
{
int i;
int j;
int k;
---------------------------------------------------------
│ │
│ │
│ │
---------------------------------------------------------
return 0;
}
答：

#define N 8
int main()
{
int i;
int j;
int k;

for(i=0;i<N;i++)
{
for(j=0;j<i+1;j++)
{
printf("*");
for(k=0;k<i;k++)
printf(".");
}
printf("\n");
}
return 0;
}

2．完成程序，实现对数组的降序排序
#include
void sort( );
int main()
{
int array[]={45,56,76,234,1,34,23,2,3}; //数字任意给出
sort( );
return 0;
}
void sort( )
{
---------------------------------------------------------
│ │
│ │
│ │
---------------------------------------------------------
}
答：使用选择排序法，我为sort函数多加了两个形参，至少第一个是必须的，否则无法传入待排序数组。不知道这样做是否符合题意。

void sort(int *array,int num)
{
int temp;
for(int i=0;i<num-1;i++)
for(int j=i+1;j<num;j++)
if (array[i]<array[j])
{
temp=array[i];
array[i]=array[j];
array[j]=temp;
}
}


3．费波那其数列，1，1，2，3，5……编写程序求第十项。可以用递归，也可以用其他方法，但要说明你选择的理由。
#include
int Pheponatch(int);
int main()
{
printf("The 10th is %d",Pheponatch(10));
return 0;
}
int Pheponatch(int N)
{
--------------------------------
│ │
│ │
--------------------------------
}
答：
使用递归，理由是递归编程简单,代码容易理解,但缺点是效率不高,而且有深度限制,如果深度太深,则堆栈会溢出。

int Pheponatch(int N)
{
if (N==3) 
return 2;
else if (N==2||N==1) 
return 1; 
else
return Pheponatch(N-1)+Pheponatch(N-2);
}

4．下列程序运行时会崩溃，请找出错误并改正，并且说明原因。

#include <stdio.h>
#include <malloc.h>
typedef struct TNode
{
TNode* left;
TNode* right;
int value;
}TNode;

TNode* root=NULL;
void append(int N);

int main()
{
append(63);
append(45);
append(32);
append(77);
append(96);
append(21);
append(17); // Again, 数字任意给出
return 0;
}

void append(int N)
{
TNode* NewNode=(TNode *)malloc(sizeof(TNode));
NewNode->value=N;
NewNode->left=NULL; //新增
NewNode->right=NULL; //新增
if(root==NULL)
{
root=NewNode;
return;
}
else
{
TNode* temp;
temp=root;
while((N>=temp->value && temp->left!=NULL)||(N<temp->value && temp->right!=NULL))
{
while(N>=temp->value && temp->left!=NULL)
temp=temp->left;
while(N<temp->value && temp->right!=NULL)
temp=temp->right;
}
if(N>=temp->value)
temp->left=NewNode;
else
temp->right=NewNode;
return; 
}
}
答：因为新节点的左右指针没有赋NULL值，至使下面的while循环不能正确结束而导致内存越界，最后崩溃（注意结束条件是temp->left!= NULL或temp->right!=NULL）。改正就是增加两条赋值语句，如上文红色部分字体就是新增的两条语句。 
 

 
 1、请用标准C语言实现一个双向循环链表的查找与删除。
typedef struct doublecyclelink{
int key;
struct doublecyclelink *prev;
struct doublecyclelink *next;
}DoubleCycleLinkT;
DoubleCycleLinkT *findKey(DoubleCycleLinkT *link,int key);
遍历整个双向循环链表，将第一个与key值相同的结点移出链表，并返回。
若没有找到则返回NULL。

答：
函数为

DoubleCycleLinkT *findKey(DoubleCycleLinkT *link,int key)
{
DoubleCycleLinkT *p;
p=link->next;
while (p->next!=link) // 链表结尾
{
if (p->key==key) // 查找到key值相同,删除该节点,并返回
{
p->prev->next=p->next;
p->next->prev=p->prev;
free(p);
return link;
}
else 
p=p->next; // 否则查找下一节点
}
if (p->next == link) return NULL; //没找到，返回NULL 

}

2、请用程序打印下列图型
*
* *
* * *
* * * *
* * * * *
void printTriangle(const unsigned char line);
输入行数，打印三角形。
答：
函数为

void printTriangle(const unsigned char line)
{
for(int i=1;i<=line;i++)
{
for(int j=0;j<(line*2-1);j++) // 5行每行需打印9个字符
{
if (i%2==1) // 奇数行
{
if (j%2==(line-1)%2 && j>=(line-1-i/2*2) && j<=(line-1+i/2*2)) 
printf("*");// 列从0计数
else
printf(" ");
}
else
if (j%2==(line)%2 && j>=(line-2-(i/2-1)*2) && j<=(line+(i/2-1)*2))
printf("*");
else
printf(" ");

}
printf("\n");
}
}

3、请用标准C语言实现下列标准库函数，设计中不得使用其他库函数。
char *strstr(char *str1,char *str2);
在字符串str1中，寻找字串str2，若找到返回找到的位置，否则返回NULL。
答：
函数为

char * strstr ( const char * str1, const char * str2 )
{
char *cp = (char *) str1;
char *s1, *s2;
if ( !*str2 )
return((char *)str1);
while (*cp)
{
s1 = cp;
s2 = (char *) str2;
while ( *s1 && *s2 && !(*s1-*s2) )
s1++, s2++;
if (!*s2)
return(cp);
cp++;
}
return(NULL);
}

4、请问这段代码循环多少次？

main()
{
char i=0;
while(i<10)
{
if(i<1)continue;
if(i==5)break;
i++;
}
......
}
答：是个死循环，无限次啊，无限次。


5、用预处理指令#define声明一个常数，用以表明1年中有多少秒（忽略闰年问题）
答： #define MIN (365*24*60*60)

6、请问运行main函数会有什么样的结果？

main()
{
int x=10,y=3;
printf("%d\n",y=x/y);
}
答：结果为3，考察强制类型转换

7、有以下程序

#define P 3
void F(int x)
{
return(P*x*x);
}
main()
{
printf("%d\n",F(3+5));
}
程序运行结果为：？
答：程序运行后的输出结果是129，此题为故意混淆概念，直接用F(8)计算得答案，而非计算3*3+5*3+5;

8、若int占2个字节，char占1个字节，float占4个字节，则定义如下：

struct stu
{
union{
char bj[5];
int bh[2];
}class;
char xm[8];
float cj;
}xc;
则sizeof(xc)的值为?
答：20，一道边界对齐的题目，很多地方有讲，此处注意下联合的内存大小取决于其中字节数最多的成员就可。

9、请问traceroute的工作原理
答：
主机先发出一个TTL（Time To Live，生存时间）为1的ICMP数据包。这个数据包到达一个路由器后，路由器将TTL减1到0，并将并送回一个「ICMP time exceeded」消息，以说明这个数据包不能继续向前传送，因为其TTL已经过期了。traceroute 收到这个消息后，便知道这个路由器存在于这个路径上，接着traceroute 再送出另一个TTL是2 的数据包，发现第2 个路由器......这个重复的动作一直持续到某个datagram 抵达目的地。 



 

基础部份:

1.下列程序在32位linux或unix中的结果是什么？ 
func(char *str)
{
printf("%d",sizeof(str));
printf("%d",strlen(str));
}

main()
{
char a[]="123456789";

printf("%d",sizeof(a));

func(a);
}

答: 10 4 9


网络/网络编程部份:

1、connect方法会阻塞，请问有什么方法可以避免其长时间阻塞？
答:最通常的方法最有效的是加定时器；也可以采用非阻塞模式。

2、网络中，如果客户端突然掉线或者重启，服务器端怎么样才能立刻知道？
答:若客户端掉线或者重新启动，服务器端会收到复位信号，每一种tcp/ip得实现不一样，控制机制也不一样。

3.在子网210.27.48.21/30种有多少个可用地址？分别是什么？
答:

简:
30表示的是网络号(network number)是30位，剩下2位中11是广播(broadcast)地址，00是multicast地址，只有01和10可以作为host address。

详:
210.27.48.21/30代表的子网的网络号是30位，即网络号是210.27.48.21 & 255.255.255.251=210.27.48.20，此子网的地址空间是2位，即可以有4个地址：210.27.48.20, 210.27.48.21, 210.27.48.22, 210.27.48.23。第一个地址的主机号(host number/id)是0，而主机号0代表的是multicast地址。最后一个地址的最后两位是11，主机号每一位都为1代表的是广播(broadcast)地址。所以只有中间两个地址可以给host使用。其实那个问题本身不准确，广播或multicast地止也是可以使用的地址，所以回答4也应该正确，当然问的人也可能是想要你回答2。我个人觉得最好的回答是一个广播地址，一个multicast地址，2个unicast地址。

4.TTL是什么？有什么用处，通常那些工具会用到它？（ping? traceroute? ifconfig? netstat?）
答:
简:TTL是Time To Live，一般是hup count，每经过一个路由就会被减去一，如果它变成0，包会被丢掉。它的主要目的是防止包在有回路的网络上死转，浪费网络资源。ping和traceroute用到它。

详:TTL是Time To Live，目前是hup count，当包每经过一个路由器它就会被减去一，如果它变成0，路由器就会把包丢掉。IP网络往往带有环(loop)，比如子网A和子网B有两个路由器相连，它就是一个loop。TTL的主要目的是防止包在有回路的网络上死转，因为包的TTL最终后变成0而使得此包从网上消失(此时往往路由器会送一个ICMP包回来，traceroute就是根据这个做的)。ping会送包出去，所以里面有它，但是ping不一定非要不可它。traceroute则是完全因为有它才能成的。ifconfig是用来配置网卡的，netstat -rn 是用来列路由表的，所以都用不着它

5.路由表示做什么用的？在linux环境中怎么来配置一条默认路由？
答:
简:路由表是用来决定如何将包从一个子网传送到另一个子网的，换局话说就是用来决定从一个网卡接收到的包应该送的哪一张网卡上的。在Linux上可以用“route add default gw <默认路由器IP>”来配置一条默认路由。

详:路由表是用来决定如何将包从一个子网传送到另一个子网的，换局话说就是用来决定从一个网卡接收到的包应该送的哪一张网卡上的。路由表的每一行至少有目标网络号、netmask、到这个子网应该使用的网卡。当路由器从一个网卡接收到一个包时，它扫描路由表的每一行，用里面的netmask和包里的目标IP地址做并逻辑运算(&)找出目标网络号，如果此网络号和这一行里的网络号相同就将这条路由保留下来做为备用路由，如果已经有备用路由了就在这两条路由里将网络号最长的留下来，另一条丢掉，如此接着扫描下一行直到结束。如果扫描结束任没有找到任何路由，就用默认路由。确定路由后，直接将包送到对应的网卡上去。在具体的实现中，路由表可能包含更多的信息为选路由算法的细节所用。题外话：路由算法其实效率很差，而且不scalable，解决办法是使用IP交换机，比如MPLS。
在Linux上可以用“route add default gw <默认路由器IP>”来配置一条默认路由。

6.在网络中有两台主机A和B，并通过路由器和其他交换设备连接起来，已经确认物理连接正确无误，怎么来测试这两台机器是否连通？如果不通，怎么来判断故障点？怎么排除故障？
答:测试这两台机器是否连通：从一台机器ping另一台机器
如果ping不通，用traceroute可以确定是哪个路由器不能连通，然后再找问题是在交换设备/hup/cable等。

7.网络编程中设计并发服务器，使用多进程 与 多线程 ，请问有什么区别？ 
答案一:
1，进程：子进程是父进程的复制品。子进程获得父进程数据空间、堆和栈的复制品。
2，线程：相对与进程而言，线程是一个更加接近与执行体的概念，它可以与同进程的其他线程共享数据，但拥有自己的栈空间，拥有独立的执行序列。
两者都可以提高程序的并发度，提高程序运行效率和响应时间。
线程和进程在使用上各有优缺点：线程执行开销小，但不利于资源管理和保护；而进程正相反。同时，线程适合于在SMP机器上运行，而进程则可以跨机器迁移。

答案二:
根本区别就一点：用多进程每个进程有自己的地址空间(address space)，线程则共享地址空间。所有其它区别都是由此而来的：
1。速度：线程产生的速度快，线程间的通讯快、切换快等，因为他们在同一个地址空间内。
2。资源利用率：线程的资源利用率比较好也是因为他们在同一个地址空间内。
3。同步问题：线程使用公共变量/内存时需要使用同步机制还是因为他们在同一个地址空间内。
等等
 

 
 
 1．改错

#include <stdio.h>
#include <String.h>
class CBuffer
{
char * m_pBuffer;
int m_size;
public:
CBuffer()
{
m_pBuffer=NULL;
}
~CBuffer()
{
Free();
}
void Allocte(int size) （3） {
m_size=size;
m_pBuffer= new char[size];
}
private:
void Free()
{ 
if(m_pBuffer!=NULL)
{
delete m_pBuffer;
m_pBuffer=NULL;
}
}
public:
void SaveString(const char* pText) const
{
strcpy(m_pBuffer, pText);
}
char* GetBuffer() const
{
return m_pBuffer;
}
};

void main (int argc, char* argv[])
{
CBuffer buffer1;
buffer1.SaveString("Microsoft");
printf(buffer1.GetBuffer());
}

答：改正后
主要改正SaveString函数
将
void SaveString(const char* pText) const
{
strcpy(m_pBuffer, pText);
}
改为
void SaveString(const char* pText) （1）
{
Allocte(strlen(pText)+1); （2）
strcpy(m_pBuffer, pText);
}
原因：
（1） const成员函数表示不会修改数据成员，而SaveString做不到，去掉const声明
（2） m_pBuffer指向NULL，必须用Allocte分配空间才能赋值。
（3） 另外需要将Allocte成员函数声明为私有成员函数更符合实际

2.下来程序想打印“Welcome MSR Asia”，改正错误

#include <stdio.h>
#include <string.h>
char * GetName (void)
{
//To return “MSR Asia” String
char name[]="MSR Asia";
return name;
}
void main(int argc, char* argv[])
{
char name[32];
//Fill in zeros into name
for(int i=0;i<=32;i++)
{
name[i]='\0';
}
//copy “Welcome” to name
name="Welcome";
//Append a blank char
name[8]=" ";
//Append string to name
strcat(name,GetName());
//print out
printf(name);
}

答：改正后为

#include <stdio.h>
#include <string.h>
char * GetName (void)
{
//To return “MSR Asia” String
//char name[]="MSR Asia"; （1） 
char *name=(char *)malloc(strlen("MSR Asia")+1); 
strcpy(name,"MSR Asia");
return name;
}
void main(int argc, char* argv[])
{
char name[32];
//Fill in zeros into name
for(int i=0;i<=32;i++)
{
name[i]='\0';
}
//copy “Welcome” to name
//name="Welcome"; （2）
strcat(name,"Welcome ");
//Append a blank char
// name[8]=' '; （3）
//Append string to name
char *p=GetName(); （4）
strcat(name,p);
free (p);
//print out
printf(name);
}
原因：（1）在函数内部定义的变量在函数结束时就清空了，必须动态分配内存
（2）字符串赋值语句错误，应该用strcat
（3）该语句无效，可去掉
（4）定义一个指针指向动态分配的内存，用完后需用free语句释放


3．写出下面程序的输出结果

#include <stdio.h>
class A
{
public:
void FuncA()
{
printf("FuncA called\n");
}
virtual void FuncB()
{
printf("FuncB called\n");
}
};

class B: public A
{
public:
void FuncA()
{
A::FuncA();
printf("FuncAB called\n");
}
virtual void FuncB()
{
printf("FuncBB called\n");
}
};

void main(void)
{
B b;
A *pa;
pa=&b;
A *pa2=new A;
b.FuncA(); （1）
b.FuncB(); （2） 
pa->FuncA(); （3）
pa->FuncB(); （4）
pa2->FuncA(); （5）
pa2->FuncB();
delete pa2;
}
答：
1．b.FuncA(); 输出
FuncA called
FuncAB called
2．b.FuncB();输出
FuncBB called
上两者好理解，直接调用类B的相应成员函数
3．pa->FuncA();输出
FuncA called 调用类A的FuncA()
4．pa->FuncB();输出
FuncBB called调用类B的FuncB()，原因是C++的动态决议机制，当基类函数声明为virtual时，指向派生类对象的基类指针来调用该函数会选择派生类的实现，除非派生类没有才调用基类的虚函数。还有一点注意的是：指向基类类型的指针可以指向基类对象也可以指向派生类对象，如pa=&b;
5. pa2->FuncA();
pa2->FuncB();输出
FuncA called
FuncB called
这也好理解，直接调用类A的相应成员函数

4．In the main() function, after ModifyString(text) is called, what’s the value of ‘text’?

#include <stdio.h>
#include <string.h>
int FindSubString(char* pch)
{
int count=0;
char* p1=pch;
while(*p1!='\0')
{
if(*p1==p1[1]-1)
{
p1++;
count++;
}
else
{
break;
}
}
int count2=count;
while(*p1!='\0')
{
if(*p1==p1[1]+1)
{
p1++;
count2--;
}
else
{
break;
}
}
if(count2==0)
return count;
return 0;
}

void ModifyString(char* pText)
{
char* p1=pText;
char* p2=p1;
while(*p1!='\0')
{
int count=FindSubString(p1);
if(count>0)
{
*p2++=*p1;
sprintf(p2, "%I", count);
while(*p2!= '\0')
{
p2++;
}
p1+=count+count+1;
}
else
{
*p2++=*p1++;
}
}
}
void main(void)
{
char text[32]="XYBCDCBABABA";
ModifyString(text);
printf(text);
}
答：我不知道这个结构混乱的程序到底想考察什么，只能将最后运行结果写出来是XYBCDCBAIBAAP 


 

1、现有1000个苹果，10个盒子，问各个盒子内应该分别放入多少个苹果，才能使得用户要买任意1至1000之间的一个苹果数，都可以给他（卖的时候是整个盒子卖，不能拆盒子的包装）。

2、请仔细阅读下面的资料：

1）材料一：CArray
template< class TYPE, class ARG_TYPE > class CArray : public CObject
Parameters:
TYPE
Template parameter specifying the type of objects stored in the array. 
TYPE is a parameter that is returned by CArray.
ARG_TYPE
Template parameter specifying the argument type used to access objects stored in the array. 
Often a reference to TYPE. ARG_TYPE is a parameter that is passed to CArray.
Remarks:
The CArray class supports arrays that are are similar to C arrays, but can dynamically shrink and grow as necessary. 
Array indexes always start at position 0. You can decide whether to fix the upper bound or allow the array to expand when you add elements past the current bound. Memory is allocated contiguously to the upper bound, even if some elements are null.

int CArray::Add (ARG_TYPE newElement);

Return Value:
The index of the added element.
Parameters:
ARG_TYPE
Template parameter specifying the type of arguments referencing elements in this array.
newElement
The element to be added to this array.

TYPE& CArray::operator [] (int nIndex);
Parameters:
TYPE
Template parameter specifying the type of elements in this array.
nIndex
Index of the element to be accessed.
Remarks:
Returns the array reference of element at the specified index.

2）材料二：CList
template<class TYPE, class ARG_TYPE>class CList : public CObject
Parameters:
TYPE
Type of object stored in the list.
ARG_TYPE
Type used to reference objects stored in the list. Can be a reference.
Remarks:
The CList class supports ordered lists of nonunique objects accessible sequentially or by value. 
CList lists behave like doubly-linked lists. 

void CList::AddTail(ARG_TYPE newElement);
Parameters:
ARG_TYPE
Template parameter specifying the type of the list element (can be a reference).
newElement
The element to be added to this list.
Remarks:
Adds a new element or list of elements to the tail of this list. The list can be empty before the operation.

3）材料三: realloc
realloc
Reallocate memory blocks.
void *realloc(void *memblock, size_t size);
Return Value:
The return value points to a storage space that is guaranteed to be suitably aligned for storage of any type of object. To get a pointer to a type other than void, use a type cast on the return value.
Remarks:
The size argument gives the new size of the block, in bytes. The contents of the block are unchanged up to the shorter of the new and old sizes, although the new block can be in a different location. Because the new block can be in a new memory location, the pointer returned by realloc is not guaranteed to be the pointer passed through the memblock argument.

4）请指出下面这段代码可能会出现的问题
CList<VARIANT*, VARIANT*> g_ValueList;
CArray<VARIANT, const VARIANT&> g_ValuePool;
void AddNewValue (const VARIANT& newValue)
{
g_ValueList.AddTail(&g_ValuePool[g_ValuePool.Add(newValue)]);
}

3、有一无符号整型数组，大小为10, 初始的数值随机，但在[0, 99]之间。请用C语言写一个过滤程序，令数组内的数据互不相等。
说明：
1.若数组内有相等的数据，可令某一数值加1或减1作出偏移，直至不等为止。
2.数组内的数据只能在[0, 99]之间。
3.保持数组内的数据位置不变，即对应下标不变。

4、 按要求编写以下函数。
功能：将给定缓冲区中的#字符移到字符串尾部
函数名称：ChangeToTail
入口参数：pSZ指向缓冲区的指针, nSize缓冲区长度
出口：pSZ所指缓冲区中的#字符被移到缓冲区尾部
返回值：在出口缓冲区中第一个#的位置,若缓冲区中无#字符则返回-1
说明：如传入#W#W#W#WW#， 10 则传出时应转换为WWWWW#####并且返回值为5
int ChangeToTail(BYTE* pSZ, UINT nSize)
{
// Todo：请在此加入您的代码
}

5、在金山，有一个非常经典有趣的游戏，称为杀人游戏。此游戏角色有：好人（m人）、坏人（n人）、村长（1人）、裁判（1人）。角色采用一定方式（如：抓阄）分配。村长、裁判两个角色是公开的，而好人、坏人两个角色则只要裁判和本人心知肚明。其玩法如下：
游戏开始了，裁判说：“天黑了”，这是所有其他角色都低头闭上眼睛（不准作弊！）。然后裁判说：“坏人开始活动”，此时坏人抬起头，并相互商议，杀死一个好人。然后裁判说：“天亮了”，此时所有人抬头，被杀死的那个好人宣布出局。剩下的人在村长的主持下，开始判断杀人凶手。每个人可以根据各人的表情反应，判断并提议杀死自己心目中的坏人。不过最终的裁决权属于村长，综合大家的意见杀死一人。此时裁判宣布此人出局。游戏进入下一轮，由天黑到天亮，再有2人出局，如此反复，直到最后好人先被全部杀死，则游戏结束，“邪恶”的一方战胜了“正义”的一方；而另一个结局则是在大家以及村长的英明决断下，坏人被全部杀死，则“正义”的一方战胜了“邪恶”的一方。
现在，我们的问题是，请写出你的思路，并编写一个C/C++语言程序，求出：在坏人有两个（n = 2）的情况下，需要多少个好人（m = ?），才能够使这个游戏比较公平，也就是说，从概率上说，“正义”的一方与“邪恶”的一方胜利的几率最接近于50%。
（此题与下面一题选做一道）
6、在以上的杀人游戏中，还有一个玩法，就是取消村长这个角色，“天亮”后剩余的人每个人投票列出自己心目中最怀疑的2个人，以此决定让谁出局。试问，在此玩法下，上面的问题又何解？
7.C++程序设计
1）.写出以下程序的运行结果：
#include <iostream>
class Base
{
public:
Base()
{
cout << "Base()" << endl;
}
Base(const Base &theBase)
{
cout << "Base(const Base &theBase)" << endl;
}
~Base()
{
cout << "~Base()" << endl;
}
void Open()
{
OnOpen();
}
private:
virtual void OnOpen() = 0;
};

class Derived : public Base
{
public:
Derived()
{
cout << "Derived()" << endl;
}
Derived(const Derived &theDerived)
{
cout << "Derived(const Derived &theDerived)" << endl;
}
~Derived()
{
cout << "~Derived()" << endl;
}
private:
virtual void OnOpen()
{
//这里可能抛出异常
}
};

Base *CreateInstance()
{
return new Derived();
}

int main()
{
Base *pBase = ::CreateInstance();
if (pBase)
{
pBase->Open();
delete pBase;
}
return 0;
}

2）.在1）中，类Base和类Derived的实现有没有问题？如果有，如何修改？

3）.说明1）中类Base的Open函数和OnOpen函数的设计目的和意义。

4）.使用STL技术修改main()函数中的代码，使之成为异常安全的。 
 
 

智力题 

1．每天中午从法国塞纳河畔的勒阿佛有一艘轮船驶往美国纽约，在同一时刻纽约也有一艘轮船驶往勒阿佛。已知横渡一次的时间是7天7夜，轮船匀速航行，在同一航线，轮船近距离可见。 
请问今天中午从勒阿佛开出的船会遇到几艘从纽约来的船？ 

2．巴拿赫病故于1945年8月31日。他的出生年份恰好是他在世时某年年龄的平方，问：他是哪年出生的？ 

答案： 

设他在世时某年年龄为x，则x的平方<1945，且x为自然数。其出生年份x的平方-x=x（x-1），他在世年龄1945-x（x-1）。1945的平方根=44.1，则x应为44或略小于此的数。而x=44时，x（x-1）=44×43=1892，算得其在世年龄为1945-1892=53；又x=43时，x（x-1）=43×42=1806，得其在世年龄为1945-1806=139；若x再取小，其在世年龄越大，显然不妥。故x=44，即他出生于1892年，终年53岁。 

笔试题目 

1．设计一个重采样系统，说明如何anti-alias。 

2．y1（n）=x（2n），y2（n）=x（n/2），问： 

如果y1为周期函数，那么x是否为周期函数？ 

如果x为周期函数，那么y1是否为周期函数？ 

如果y2为周期函数，那么x是否为周期函数？ 

如果x为周期函数，那么y2是否为周期函数？ 

3．如果模拟信号的带宽为5kHz，要用8k的采样率，怎么办。 

4．某个程序在一个嵌入式系统（200M的CPU，50M的SDRAM）中已经最优化了，换到另一个系统（300M的CPU，50M的SDRAM）中运行，还需要优化吗？ 

5．x^4+a*x^3+x^2+c*x+d最少需要做几次乘法。 

6．三个float:a,b,c 

问值： 

（a+b）+c==（b+a）+c 

（a+b）+c==（a+c）+b 

7．把一个链表反向填空。 

8．下面哪种排序法对12354最快？ 

A. quick sort 

B. buble sort 

C. merge sort 

9．哪种结构平均来讲获取一个值最快？ 

A. binary tree 
B. hash table 
C. stack 

10． 

#include 
“stdafx.h” 
#include <iostream.h> 
struct bit 
{ int a:3; 
int b:2; 
int c:3; 
}; 
int main(int argc, char* argv[]) 
{ 
bit s; 
char *c = (char*)&s; 
*c = 0x99; 
cout << 
s.a <<endl <<s.b<<endl<<s.c<<endl; 
return 0; 
} 

Output:? 

11． 

挑bug，在linux下运行： 
#include <stdio.h> 
char 
*reverse(char* str) 
{ 
int len=0, i=0; 
char *pstr=str, *ptemp,*pd; 
while(*++pstr) 
len++; 
pstr--; 
//ptemp=(char*)malloc(len+1); 
ptemp=(char*)malloc(len+1); 
pd=ptemp; 
while(len--){ 
*ptemp=*pstr; 
ptemp++; 
pstr--; 
i++; 
} 
*ptemp=*pstr; 
ptemp++; 
*ptemp=‘\0’; 
return pd; 
} 
main() 
{ 
char string[40]= “Hello World!”; 
char *pstr=string; 
printf(“%s”, pstr); 
printf(“%s”, reverse(pstr)); 
} 

实验室笔试题 
1．写出下列信号的奈亏斯特频率 

（1）f（t）=1+cos（2000pait）+sin（4000pait） 
（2）f（t）=sin（4000pait）/pait 
（3）f（t）=（sin（4000pait）的平方）/pait 

2．有两个线程 

void producer() 
{ 
while(1) 
{ 
GeneratePacket(); 
PutPacketIntoBuffer(); 
Signal(customer); 
} 
} 
void customer() 
{ 
while(1) 
{ 
WaitForSignal(); 
if(PacketInBuffer>10) 
{ 
ReadAllPackets(); 
ProcessPackets(); 
} 
} 
} 

（1）有没有其他方法可以提高程序的性能 

（2）可不可以不使用信号之类的机制来实现上述的功能 

3．优化下面的程序 

（0）sum=0 
（1）I=1 
（2）T1=4*I 
（3）T2=address(A)-4 
（4）T3=T2[T1] 
（5）T4=address(B)-4 
（6）T5=4*I 
（7）T6=T4[T5] 
（8）T7=T3*T5 
（9）sum=sum+T6 
（10）I=I+1 
（11）IF I<20 GOTO (2) 

来源：《你也能拿高薪》 

 
 

本人很弱，这几个题也搞不定，特来求救：
1）读文件file1.txt的内容（例如）：
12
34
56
输出到file2.txt：
56
34
12
（逆序）
2）输出和为一个给定整数的所有组合
例如n=5
5=1+4；5=2+3（相加的数不能重复）
则输出
1，4；2，3。
望高手赐教！！

第一题,注意可增长数组的应用.
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
int MAX = 10;
int *a = (int *)malloc(MAX * sizeof(int));
int *b;

FILE *fp1;
FILE *fp2;

fp1 = fopen("a.txt","r");
if(fp1 == NULL)
{printf("error1");
exit(-1);
}

fp2 = fopen("b.txt","w");
if(fp2 == NULL)
{printf("error2");
exit(-1);
}

int i = 0;
int j = 0;

while(fscanf(fp1,"%d",&a[i]) != EOF)
{
i++;
j++;
if(i >= MAX)
{
MAX = 2 * MAX;
b = (int*)realloc(a,MAX * sizeof(int));
if(b == NULL)
{
printf("error3");
exit(-1);
}
a = b;
}
}

for(;--j >= 0;)
fprintf(fp2,"%d\n",a[j]);

fclose(fp1);
fclose(fp2);

return 0;


}

第二题.
#include <stdio.h>

int main(void)
{
unsigned long int i,j,k;

printf("please input the number\n");
scanf("%d",&i);
if( i % 2 == 0)
j = i / 2;
else
j = i / 2 + 1;

printf("The result is \n");
for(k = 0; k < j; k++)
printf("%d = %d + %d\n",i,k,i - k);
return 0;
}

#include <stdio.h>
void main()
{
unsigned long int a,i=1;
scanf("%d",&a);
if(a%2==0)
{
for(i=1;i<a/2;i++)
printf("%d",a,a-i);
}
else
for(i=1;i<=a/2;i++)
printf(" %d, %d",i,a-i);
}

兄弟,这样的题目若是做不出来实在是有些不应该, 给你一个递规反向输出字符串的例子,可谓是反序的经典例程.

void inverse(char *p)
{
if( *p = = '\0' ) 
return;
inverse( p+1 );
printf( "%c", *p );
}

int main(int argc, char *argv[])
{
inverse("abc\0");

return 0;
}

借签了楼上的“递规反向输出”
#include <stdio.h>
void test(FILE *fread, FILE *fwrite)
{
char buf[1024] = {0};
if (!fgets(buf, sizeof(buf), fread))
return;
test( fread, fwrite );
fputs(buf, fwrite);
}
int main(int argc, char *argv[])
{
FILE *fr = NULL;
FILE *fw = NULL;
fr = fopen("data", "rb");
fw = fopen("dataout", "wb");
test(fr, fw);
fclose(fr);
fclose(fw);
return 0;
}

在对齐为4的情况下
struct BBB
{
long num；
char *name;
short int data;
char ha;
short ba[5];
}*p;
p=0x1000000;
p+0x200=____;
(Ulong)p+0x200=____;
(char*)p+0x200=____;
希望各位达人给出答案和原因，谢谢拉
解答：假设在32位CPU上，
sizeof(long) = 4 bytes
sizeof(char *) = 4 bytes
sizeof(short int) = sizeof(short) = 2 bytes
sizeof(char) = 1 bytes

由于是4字节对齐，
sizeof(struct BBB) = sizeof(*p) 
= 4 + 4 + 2 + 1 + 1/*补齐*/ + 2*5 + 2/*补齐*/ = 24 bytes (经Dev-C++验证)

p=0x1000000;
p+0x200=____;
= 0x1000000 + 0x200*24

(Ulong)p+0x200=____;
= 0x1000000 + 0x200

(char*)p+0x200=____;
= 0x1000000 + 0x200*4

你可以参考一下指针运算的细节


写一段程序，找出数组中第k大小的数，输出数所在的位置。例如{2，4，3，4，7}中，第一大的数是7，位置在4。第二大、第三大的数都是4，位置在1、3随便输出哪一个均可。函数接口为：int find_orderk(const int* narry,const int n,const int k) 
要求算法复杂度不能是O(n^2）
谢谢！
可以先用快速排序进行排序，其中用另外一个进行地址查找
代码如下，在VC++6.0运行通过。给分吧^-^

//快速排序

#include<iostream>

usingnamespacestd;

intPartition (int*L,intlow,int high)
{
inttemp = L[low];
intpt = L[low];

while (low < high)
{
while (low < high && L[high] >= pt)
--high;
L[low] = L[high];
while (low < high && L[low] <= pt)
++low;
L[low] = temp;
}
L[low] = temp;

returnlow;
}

voidQSort (int*L,intlow,int high)
{
if (low < high)
{
intpl = Partition (L,low,high);

QSort (L,low,pl - 1);
QSort (L,pl + 1,high);
}
}

intmain ()
{
intnarry[100],addr[100];
intsum = 1,t;

cout << "Input number:" << endl;
cin >> t;

while (t != -1)
{
narry[sum] = t;
addr[sum - 1] = t;
sum++;

cin >> t;
}

sum -= 1;
QSort (narry,1,sum);

for (int i = 1; i <= sum;i++)
cout << narry[i] << '\t';
cout << endl;

intk;
cout << "Please input place you want:" << endl;
cin >> k;

intaa = 1;
intkk = 0;
for (;;)
{
if (aa == k)
break;
if (narry[kk] != narry[kk + 1])
{
aa += 1;
kk++;
}

}

cout << "The NO." << k << "number is:" << narry[sum - kk] << endl;
cout << "And it's place is:" ;
for (i = 0;i < sum;i++)
{
if (addr[i] == narry[sum - kk])
cout << i << '\t';
}


return0;
}

1、找错
Void test1()
{
char string[10];
char* str1="0123456789";
strcpy(string, str1);// 溢出，应该包括一个存放'\0'的字符string[11]
}


Void test2()
{
char string[10], str1[10];
for(I=0; I<10;I++)
{
str1[i] ='a';
}
strcpy(string, str1);// I，i没有声明。
}

Void test3(char* str1)
{
char string[10];
if(strlen(str1)<=10)// 改成<10,字符溢出，将strlen改为sizeof也可以
{
strcpy(string, str1);
}
}

2.
void g(int**);
int main()
{
int line[10],i;
int *p=line; //p是地址的地址
for (i=0;i<10;i++)
{
*p=i;
g(&p);//数组对应的值加1
}
for(i=0;i<10;i++)
printf("%d\n",line[i]);
return 0;
}

void g(int**p)
{
(**p)++;
(*p)++;// 无效
}
输出：
1
2 
3 
4 
5 
6 
7 
8 
9 
10
3. 写出程序运行结果

int sum(int a)
{
auto int c=0;
static int b=3;
c+=1;
b+=2;
return(a+b+c);
}

void main()
{
int I;
int a=2;
for(I=0;I<5;I++)
{
printf("%d,", sum(a));
}
}
// static会保存上次结果，记住这一点，剩下的自己写
输出：8,10,12,14,16,


4.

int func(int a)
{
int b;
switch(a)
{
case 1: 30;
case 2: 20;
case 3: 16;
default: 0
}
return b;
}
则func(1)=?
// b定义后就没有赋值。

5:
int a[3];
a[0]=0; a[1]=1; a[2]=2;
int *p, *q;
p=a;
q=&a[2];
则a[q-p]=a[2]
解释：指针一次移动一个int但计数为1

今天早上的面试题9道，比较难，向牛人请教，国内的一牛公司，坐落在北京北四环某大厦：
1、线形表a、b为两个有序升序的线形表，编写一程序，使两个有序线形表合并成一个有序升序线形表h；
答案在 请化大学 严锐敏《数据结构第二版》第二章例题，数据结构当中，这个叫做：两路归并排序
Linklist *unio(Linklist *p,Linklist *q){
linklist *R,*pa,*qa,*ra;
pa=p;
qa=q;
R=ra=p;
while(pa->next!=NULL&&qa->next!=NULL){
if(pa->data>qa->data){
ra->next=qa;
qa=qa->next;
}
else{
ra->next=pa;
pa=pa->next;
}
}
if(pa->next!=NULL)
ra->next=pa;
if(qa->next!=NULL)
ra->next==qa;
return R;
}
2、运用四色定理，为N个局域举行配色，颜色为1、2、3、4四种，另有数组adj[][N]，如adj[i][j]=1则表示i区域与j区域相邻，数组color[N]，如color[i]=1,表示i区域的颜色为1号颜色。
四色填充
3、用递归算法判断数组a[N]是否为一个递增数组。
递归的方法，记录当前最大的，并且判断当前的是否比这个还大，大则继续，否则返回false结束：
bool fun( int a[], int n )
{
if( n= =1 )
return true;
if( n= =2 )
return a[n-1] >= a[n-2];
return fun( a,n-1) && ( a[n-1] >= a[n-2] );
}
4、编写算法，从10亿个浮点数当中，选出其中最大的10000个。
用外部排序，在《数据结构》书上有
《计算方法导论》在找到第n大的数的算法上加工
5、编写一unix程序，防止僵尸进程的出现.

 
写一个程序, 要求功能：求出用1，2，5这三个数不同个数组合的和为100的组合个数。
如：100个1是一个组合，5个1加19个5是一个组合。。。。 请用C++语言写。

答案：最容易想到的算法是：
设x是1的个数，y是2的个数，z是5的个数，number是组合数
注意到0<=x<=100，0<=y<=50，0<=z=20，所以可以编程为：


number=0;
for (x=0; x<=100; x++)
for (y=0; y<=50; y++)
for (z=0; z<=20; z++)
if ((x+2*y+5*z)==100)
number++;
cout<<number<<endl;


上面这个程序一共要循环100*50*20次，效率实在是太低了
事实上，这个题目是一道明显的数学问题，而不是单纯的编程问题。我的解法如下：
因为x+2y+5z=100
所以x+2y=100-5z，且z<=20 x<=100 y<=50
所以(x+2y)<=100，且(x+5z)是偶数
对z作循环，求x的可能值如下：

z=0, x=100, 98, 96, ... 0
z=1, x=95, 93, ..., 1
z=2, x=90, 88, ..., 0
z=3, x=85, 83, ..., 1
z=4, x=80, 78, ..., 0
......
z=19, x=5, 3, 1
z=20, x=0

因此，组合总数为100以内的偶数+95以内的奇数+90以内的偶数+...+5以内的奇数+1，
即为：
(51+48)+(46+43)+(41+38)+(36+33)+(31+28)+(26+23)+(21+18)+(16+13)+(11+8)+(6+3)+1


某个偶数m以内的偶数个数（包括0）可以表示为m/2+1=(m+2)/2
某个奇数m以内的奇数个数也可以表示为(m+2)/2

所以，求总的组合次数可以编程为：
number=0;
for (int m=0;m<=100;m+=5)
{
number+=(m+2)/2;
}
cout<<number<<endl;
这个程序,只需要循环21次, 两个变量，就可以得到答案,比上面的那个程序高效了许多
倍----只是因为作了一些简单的数学分析

这再一次证明了：计算机程序=数据结构+算法，而且算法是程序的灵魂，对任何工程问
题，当用软件来实现时，必须选取满足当前的资源限制，用户需求限制，开发时间限制等种
种限制条件下的最优算法。而绝不能一拿到手，就立刻用最容易想到的算法编出一个程序了
事——这不是一个专业的研发人员的行为。

那么，那种最容易想到的算法就完全没有用吗？不，这种算法正好可以用来验证新算法
的正确性，在调试阶段，这非常有用。在很多大公司，例如微软，都采用了这种方法：在调
试阶段，对一些重要的需要好的算法来实现的程序，而这种好的算法又比较复杂时，同时用
容易想到的算法来验证这段程序，如果两种算法得出的结果不一致（而最容易想到的算法保
证是正确的），那么说明优化的算法出了问题，需要修改。
可以举例表示为：
#ifdef DEBUG
int simple();
#end if
int optimize();
......
in a function:
{
result=optimize();
ASSERT(result==simple());
}
这样,在调试阶段,如果简单算法和优化算法的结果不一致,就会打出断言。同时，在程
序的发布版本，却不会包含笨重的simple()函数。——任何大型工程软件都需要预先设计良
好的调试手段，而这里提到的就是一种有用的方法。



一个学生的信息是：姓名，学号，性别，年龄等信息，用一个链表，把这些学生信息连在一起， 给出一个age, 在些链表中删除学生年龄等于age的学生信息。

#include "stdio.h"
#include "conio.h"

struct stu{
char name[20];
char sex;
int no;
int age;
struct stu * next;
}*linklist;
struct stu *creatlist(int n)
{
int i;
//h为头结点，p为前一结点，s为当前结点
struct stu *h,*p,*s;
h = (struct stu *)malloc(sizeof(struct stu));
h->next = NULL;
p=h;
for(i=0;i<n;i++)
{ 
s = (struct stu *)malloc(sizeof(struct stu));
p->next = s;
printf("Please input the information of the student: name sex no age \n");
scanf("%s %c %d %d",s->name,&s->sex,&s->no,&s->age);
s->next = NULL;
p = s;
}
printf("Create successful!");
return(h);
}
void deletelist(struct stu *s,int a)
{
struct stu *p;
while(s->age!=a)
{
p = s;
s = s->next;
}
if(s==NULL)
printf("The record is not exist.");
else
{
p->next = s->next;
printf("Delete successful!");
}
}
void display(struct stu *s)
{
s = s->next;
while(s!=NULL)
{
printf("%s %c %d %d\n",s->name,s->sex,s->no,s->age);
s = s->next;
}
}
int main()
{
struct stu *s;
int n,age;
printf("Please input the length of seqlist:\n");
scanf("%d",&n);
s = creatlist(n);
display(s);
printf("Please input the age:\n");
scanf("%d",&age);
deletelist(s,age);
display(s);
return 0;
}

2、实现一个函数，把一个字符串中的字符从小写转为大写。

#include "stdio.h"
#include "conio.h"

void uppers(char *s,char *us)
{
for(;*s!='\0';s++,us++)
{
if(*s>='a'&&*s<='z')
*us = *s-32;
else
*us = *s;
}
*us = '\0';
}
int main()
{
char *s,*us;
char ss[20];
printf("Please input a string:\n");
scanf("%s",ss);
s = ss;
uppers(s,us);
printf("The result is:\n%s\n",us);
getch();
}

随机输入一个数，判断它是不是对称数（回文数）（如3，121，12321，45254）。不能用字符串库函数 

/***************************************************************
1.
函数名称：Symmetry 
功能： 判断一个数时候为回文数(121,35653) 
输入： 长整型的数 
输出： 若为回文数返回值为1 esle 0 
******************************************************************/
unsigned char Symmetry (long n)
{
long i,temp;
i=n; temp=0;
while(i) //不用出现长度问题,将数按高低位掉换
{
temp=temp*10+i%10;
i/=10;
}
return(temp==n);
} 
方法一 
/* --------------------------------------------------------------------------- 
功能： 
判断字符串是否为回文数字 
实现： 
先将字符串转换为正整数，再将正整数逆序组合为新的正整数，两数相同则为回文数字 
输入： 
char *s：待判断的字符串 
输出： 
无 
返回： 
0：正确；1：待判断的字符串为空；2：待判断的字符串不为数字； 
3：字符串不为回文数字；4：待判断的字符串溢出 
---------------------------------------------------------------------------- */ 
unsigned IsSymmetry(char *s) 
{ 
char *p = s; 
long nNumber = 0; 
long n = 0; 
long nTemp = 0; 

/*判断输入是否为空*/ 
if (*s == \'\\0\') 
return 1; 

/*将字符串转换为正整数*/ 
while (*p != \'\\0\') 
{ 
/*判断字符是否为数字*/ 
if (*p<\'0\' || *p>\'9\') 
return 2; 

/*判断正整数是否溢出*/ 
if ((*p-\'0\') > (4294967295-(nNumber*10))) 
return 4; 

nNumber = (*p-\'0\') + (nNumber * 10); 

p++; 
} 

/*将数字逆序组合，直接抄楼上高手的代码，莫怪，呵呵*/ 
n = nNumber; 
while(n) 
{ 
/*判断正整数是否溢出*/ 
if ((n%10) > (4294967295-(nTemp*10))) 
return 3; 

nTemp = nTemp*10 + n%10; 
n /= 10; 
} 

/*比较逆序数和原序数是否相等*/ 
if (nNumber != nTemp) 
return 3; 

return 0; 
} 

方法二 
/* --------------------------------------------------------------------------- 
功能： 
判断字符串是否为回文数字 
实现： 
先得到字符串的长度，再依次比较字符串的对应位字符是否相同 
输入： 
char *s：待判断的字符串 
输出： 
无 
返回： 
0：正确；1：待判断的字符串为空；2：待判断的字符串不为数字； 
3：字符串不为回文数字 
---------------------------------------------------------------------------- */ 
unsigned IsSymmetry_2(char *s) 
{ 
char *p = s; 
int nLen = 0; 
int i = 0; 

/*判断输入是否为空*/ 
if (*s == \'\\0\') 
return 1; 

/*得到字符串长度*/ 
while (*p != \'\\0\') 
{ 
/*判断字符是否为数字*/ 
if (*p<\'0\' || *p>\'9\') 
return 2; 

nLen++; 
p++; 
} 

/*长度不为奇数，不为回文数字*/ 
if (nLen%2 == 0) 
return 4; 

/*长度为1，即为回文数字*/ 
if (nLen == 1) 
return 0; 

/*依次比较对应字符是否相同*/ 
p = s; 
i = nLen/2 - 1; 
while (i) 
{ 
if (*(p+i) != *(p+nLen-i-1)) 
return 3; 

i--; 
} 

return 0; 
} 

求2~2000的所有素数.有足够的内存,要求尽量快


答案：
int findvalue[2000]={2};
static int find=1;
bool adjust(int value)
{
assert(value>=2);
if(value==2) return true;
for(int i=0;i<=find;i++)
{
if(value%findvalue[i]==0)
return false;
}
findvalue[find++];
return true;
}
5、请简述以下两个for循环的优缺点(5分)

　　for (i=0; i＜N; i++)

　　{

　　if (condition)

　　DoSomething();

　　else

　　DoOtherthing();

　　}

　　if (condition)

　　{

　　for (i=0; i＜N; i++)

　　DoSomething();

　　}

　　else

　　{

　　for (i=0; i＜N; i++)

　　DoOtherthing();

　　}

　　优点：程序简洁

　　缺点：多执行了N-1次逻辑判断，并且打断了循环“流水线”作业，使得编译器不能

　　对循环进行优化处理，降低了效率。 优点：循环的效率高

　　缺点：程序不简洁

　　四、有关内存的思考题(每小题5分，共20分)

　　void GetMemory(char *p)

　　{

　　p = (char *)malloc(100);

　　}

　　void Test(void)

　　{

　　char *str = NULL;

　　GetMemory(str);

　　strcpy(str, "hello world");

　　printf(str);

　　}

　　请问运行Test函数会有什么样的结果？

　　答：程序崩溃。

　　因为GetMemory并不能传递动态内存，

　　Test函数中的 str一直都是 NULL。

　　strcpy(str, "hello world");将使程序崩溃。

　　char *GetMemory(void)

　　{

　　char p[] = "hello world";

　　return p;

　　}

　　void Test(void)

　　{

　　char *str = NULL;

　　str = GetMemory();

　　printf(str);

　　}

　　请问运行Test函数会有什么样的结果？

　　答：可能是乱码。

　　因为GetMemory返回的是指向“栈内存”的指针，该指针的地址不是 NULL，但其原现

　　的

　　内容已经被清除，新内容不可知。

　　void GetMemory2(char **p, int num)

　　{

　　*p = (char *)malloc(num);

　　}

　　void Test(void)

　　{

　　char *str = NULL;

　　GetMemory(&str, 100);

　　strcpy(str, "hello");

　　printf(str);

　　}

　　请问运行Test函数会有什么样的结果？

　　答：

　　(1)能够输出hello

　　(2)内存泄漏

　　void Test(void)

　　{

　　char *str = (char *) malloc(100);

　　strcpy(str, “hello”);

　　free(str);

　　if(str != NULL)

　　{

　　strcpy(str, “world”);

　　printf(str);

　　}

　　}

　　请问运行Test函数会有什么样的结果？

　　答：篡改动态内存区的内容，后果难以预料，非常危险。

　　因为free(str);之后，str成为野指针，

　　if(str != NULL)语句不起作用。

　　五、编写strcpy函数(10分)

　　已知strcpy函数的原型是

　　char *strcpy(char *strDest, const char *strSrc);

　　其中strDest是目的字符串，strSrc是源字符串。

　　(1)不调用C++/C的字符串库函数，请编写函数 strcpy

　　char *strcpy(char *strDest, const char *strSrc);

　　{

　　assert((strDest!=NULL) && (strSrc !=NULL)); // 2分

　　char *address = strDest; // 2分

　　while( (*strDest++ = * strSrc++) != ‘\0’ ) // 2分

　　NULL ;

　　return address ; // 2分

　　}

　　(2)strcpy能把strSrc的内容复制到strDest，为什么还要char * 类型的返回值？

　　答：为了实现链式表达式。 // 2分

　　例如 int length = strlen( strcpy( strDest, “hello world”) );

　　六、编写类String的构造函数、析构函数和赋值函数(25分)

　　已知类String的原型为：

　　class String

　　{

　　public:

　　String(const char *str = NULL); // 普通构造函数

　　String(const String &other); // 拷贝构造函数

　　~ String(void); // 析构函数

　　String & operate =(const String &other); // 赋值函数

　　private:

　　char *m_data; // 用于保存字符串

　　};

　　请编写String的上述4个函数。

　　标准答案：

　　// String的析构函数

　　String::~String(void) // 3分

　　{

　　delete [] m_data;

　　// 由于m_data是内部数据类型，也可以写成 delete m_data;

　　}

　　// String的普通构造函数

　　String::String(const char *str) // 6分

　　{

　　if(str==NULL)

　　{

　　m_data = new char[1]; // 若能加 NULL 判断则更好

　　*m_data = ‘\0’;

　　}

　　else

　　{

　　int length = strlen(str);

　　m_data = new char[length+1]; // 若能加 NULL 判断则更好

　　strcpy(m_data, str);

　　}

　　}

　　// 拷贝构造函数

　　String::String(const String &other) // 3分

　　{

　　int length = strlen(other.m_data);

　　m_data = new char[length+1]; // 若能加 NULL 判断则更好

　　strcpy(m_data, other.m_data);

　　}

　　// 赋值函数

　　String & String::operate =(const String &other) // 13分

　　{

　　// (1) 检查自赋值 // 4分

　　if(this == &other)

　　return *this;

　　// (2) 释放原有的内存资源 // 3分

　　delete [] m_data;

　　// (3)分配新的内存资源，并复制内容 // 3分

　　int length = strlen(other.m_data);

　　m_data = new char[length+1]; // 若能加 NULL 判断则更好

　　strcpy(m_data, other.m_data);

　　// (4)返回本对象的引用 // 3分 

 

1、估计一下广州有多少理发师，如果允许，你还需要那些调研工作？并给出你的推导过程。你认为你的 估算结果可信吗？

2、看过那些软件方面的书籍

3、什么是软件，软件开发包括那些步骤，并说出你对这些步骤的理解

4、OSI网络结构的七层模型分别是什么，并说出你认为划分为7层的理由。

5、软件过程中了解、使用过版本控制或建模工具吗？对你工作有什么帮助？

6、软件过程中你都写过什么文档？分别是什么目的及其对你的帮助？

7、我们知道，C++将内存划分为三个逻辑区域：堆、栈和静态存储，请说出它们的区别及你的理解。

8、字符串A是由n个小写英文字母（a ~ z）构成的，定义为char A[n]。你能用更少的空间表示这个字符串吗？请写出从char A[n]到你的新的储存格式的转换函数。（请用C/C++编程，不允许上机操作）

12、对现在的Stack（栈）数据结构进行改进，加一个min()功能，使之能在常数，即O(1)，时间内给出栈中的最小值。可对push()和pop()函数进行修改，但要求其时间复杂度都只能是O(1)。

9、C++构造函数为什么不能是虚函数？

10、C++中virtual与inline的含义分别是什么？虚函数的特点；内联函数的特点；一个函数能否即是虚函数又是内联函数？

12、请列出实现C++代码你认为需要注意的一些问题。

11、你在原来的项目中有没有遇到什么困难，又是如何解决的？


1 dll,lib处理实现 .lib文件中包含什么? dll在内存中被多个函数共享,有几个拷贝?
2 template,template等编译的时候作为几个类
3 struct ,class的区别,联系
4 MAcro,inline区别,实现.编译运行时
5 进程与线程区别
6 hdc-cdc区别联系
7 model dialog,modeless dialog,从创建到销毁全过程具体描述
8 各个线程new的内存,别的线程是否可以使用？
9 RUNTIME_CLASS, is what??


http://www.sinoprise.com/simple/index.php?t32.html

1. 堆和栈的区别？
栈区（stack）- 由编译器自动分配释放 ，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈。
堆区（heap） - 一般由程序员分配释放， 若程序员不释放，程序结束时可能由OS回收 。
2. 虚函数的本质和实现机制？
虚函数的本质就是通过基类访问派生类定义的函数。虚函数只能借助于指针或者引用来达到多态的效果。
3. C++中传递函数参数的方式及他们的优缺点？
4. static关键字的作用？
5. 引用和指针的区别？
6. 函数重载和覆盖的区别？
7. 深拷贝和浅拷贝的区别？
8. 数组a[4][3]的内存结构?并指出a[2][3]和a[3][2]在内存中的位置？
9. 包含和私有继承的区别？
10. 实现一个操作栈的模板（empty，push，pop，），并实现错误处理（对空栈的pop）
11. ANSI和Unicode的区别？并指出C RunTime Library 和 Win32 API对他们的支持。
12. 线程同步的四种方式的机制。
13. 虚拟内存。
14. DLL的实现机制和DLL的输出方式。
15. D3D的顶点着色。
16. 几种数据结构在游戏中的支持。
17. 游戏引擎


服务器程序员笔试题
C++
1.简述堆和栈的区别。
2.简述虚函数的本质和实现机制。
3.列举C++中向函数传递参数的各种方式，并比较它们之间的区别和优缺点。
4.static关键字有几种用途？请简述每种用途。
5.简述引用和指针的异同。
6.简述函数重载（overloading）和覆盖（overriding）的区别。
7.什么是深拷贝？什么是浅拷贝？
8.请画出二维数组char a[4][3]的内存结构图，并指出a[3][2]和a[2][3]在内存中的位置。
9.简述包含和私有继承的异同。
10.用模板实现一个通用的栈，要求实现empty, size, push, pop, top五个成员函数，并用异常机制来报告错误（比如在一个大小为0的栈上执行pop操作）。
标准库
11.用string类编写一个程序，它从标准输入接收一行输入，然后统计出其中单词的个数，单词的分隔符只有逗号、点号和空格三种。
12.简述STL的容器container、迭代器iterator、算法algorithm和函数器functor的作用以及它们之间的关系，举例说明。
13.下面的代码存在什么问题，如何修正？
list list1;

for (int i = 0; i < 8; i ++) {
list1.push_back(i);
}

for (list::iterator it = list1.begin(); it != list1.end(); ++it) {
if (*it % 2 == 0) {
list1.erase(it); 
}
}

Win32
14.比较ANSI和Unicode的区别，并说明C Runtime Library和Win32 API如何支持二者。
15.简述线程同步的四种机制。
16.简述虚拟内存机制，并描述在win95和winnt下内存空间的结构。
17.简述DLL的实现机制以及输出DLL中函数的两种方法。
网络
18.简述TCP和UDP之间的区别。
19.简述Winsock的六种主要IO处理模式。
20.描述一个你以前实现过的服务器的结构图，并分析其中可能存在的瓶颈。



16. 关联、聚合(Aggregation)以及组合(Composition)的区别？

涉及到UML中的一些概念：关联是表示两个类的一般性联系，比如“学生”和“老师”就是一种关联关系；聚合表示has-a的关系，是一种相对松散的关系，聚合类不需要对被聚合类负责，如下图所示，用空的菱形表示聚合关系：



从实现的角度讲，聚合可以表示为:

class A {...} class B { A* a; .....}

而组合表示contains-a的关系，关联性强于聚合：组合类与被组合类有相同的生命周期，组合类要对被组合类负责，采用实心的菱形表示组合关系：



实现的形式是:

class A{...} class B{ A a; ...}

参考文章：http://www.cnitblog.com/Lily/archive/2006/02/23/6860.html

http://www.vckbase.com/document/viewdoc/?id=422

17.面向对象的三个基本特征，并简单叙述之？

1. 封装：将客观事物抽象成类，每个类对自身的数据和方法实行protection(private, protected,public)

2. 继承：广义的继承有三种实现形式：实现继承（指使用基类的属性和方法而无需额外编码的能力）、可视继承（子窗体使用父窗体的外观和实现代码）、接口继承（仅使用属性和方法，实现滞后到子类实现）。前两种（类继承）和后一种（对象组合=>接口继承以及纯虚函数）构成了功能复用的两种方式。

3. 多态：是将父对象设置成为和一个或更多的他的子对象相等的技术，赋值之后，父对象就可以根据当前赋值给它的子对象的特性以不同的方式运作。简单的说，就是一句话：允许将子类类型的指针赋值给父类类型的指针。

18. 重载（overload)和重写(overried，有的书也叫做“覆盖”）的区别？

常考的题目。从定义上来说：

重载：是指允许存在多个同名函数，而这些函数的参数表不同（或许参数个数不同，或许参数类型不同，或许两者都不同）。

重写：是指子类重新定义复类虚函数的方法。

从实现原理上来说：

重载：编译器根据函数不同的参数表，对同名函数的名称做修饰，然后这些同名函数就成了不同的函数（至少对于编译器来说是这样的）。如，有两个同名函数：function func(p:integer):integer;和function func(p:string):integer;。那么编译器做过修饰后的函数名称可能是这样的：int_func、str_func。对于这两个函数的调用，在编译器间就已经确定了，是静态的。也就是说，它们的地址在编译期就绑定了（早绑定），因此，重载和多态无关！

重写：和多态真正相关。当子类重新定义了父类的虚函数后，父类指针根据赋给它的不同的子类指针，动态的调用属于子类的该函数，这样的函数调用在编译期间是无法确定的（调用的子类的虚函数的地址无法给出）。因此，这样的函数地址是在运行期绑定的（晚绑定）。

19. 多态的作用？

主要是两个：1. 隐藏实现细节，使得代码能够模块化；扩展代码模块，实现代码重用；2. 接口重用：为了类在继承和派生的时候，保证使用家族中任一类的实例的某一属性时的正确调用。

20. Ado与Ado.net的相同与不同？

除了“能够让应用程序处理存储于DBMS 中的数据“这一基本相似点外，两者没有太多共同之处。但是Ado使用OLE DB 接口并基于微软的COM 技术，而ADO.NET 拥有自己的ADO.NET 接口并且基于微软的.NET 体系架构。众所周知.NET 体系不同于COM 体系，ADO.NET 接口也就完全不同于ADO和OLE DB 接口，这也就是说ADO.NET 和ADO是两种数据访问方式。ADO.net 提供对XML 的支持。

21. New delete 与malloc free 的联系与区别?
答案：都是在堆(heap)上进行动态的内存操作。用malloc函数需要指定内存分配的字节数并且不能初始化对象，new 会自动调用对象的构造函数。delete 会调用对象的destructor，而free 不会调用对象的destructor.

22. #define DOUBLE(x) x+x ，i = 5*DOUBLE(5)； i 是多少？
答案：i 为30。

23. 有哪几种情况只能用intialization list 而不能用assignment? 

答案：当类中含有const、reference 成员变量；基类的构造函数都需要初始化表。

24. C++是不是类型安全的？
答案：不是。两个不同类型的指针之间可以强制转换（用reinterpret cast)。C#是类型安全的。

25. main 函数执行以前，还会执行什么代码？
答案：全局对象的构造函数会在main 函数之前执行。

26. 描述内存分配方式以及它们的区别?
1） 从静态存储区域分配。内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在。例如全局变量，static 变量。
2） 在栈上创建。在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集。
3） 从堆上分配，亦称动态内存分配。程序在运行的时候用malloc 或new 申请任意多少的内存，程序员自己负责在何时用free 或delete 释放内存。动态内存的生存期由程序员决定，使用非常灵活，但问题也最多。

27.struct 和 class 的区别

答案：struct 的成员默认是公有的，而类的成员默认是私有的。struct 和 class 在其他方面是功能相当的。 

从感情上讲，大多数的开发者感到类和结构有很大的差别。感觉上结构仅仅象一堆缺乏封装和功能的开放的内存位，而类就象活的并且可靠的社会成员，它有智能服务，有牢固的封装屏障和一个良好定义的接口。既然大多数人都这么认为，那么只有在你的类有很少的方法并且有公有数据（这种事情在良好设计的系统中是存在的!）时，你也许应该使用 struct 关键字，否则，你应该使用 class 关键字。 

28.当一个类A 中没有生命任何成员变量与成员函数,这时sizeof(A)的值是多少，如果不是零，请解释一下编译器为什么没有让它为零。（Autodesk）
答案：肯定不是零。举个反例，如果是零的话，声明一个class A[10]对象数组，而每一个对象占用的空间是零，这时就没办法区分A[0],A[1]…了。

29. 在8086 汇编下，逻辑地址和物理地址是怎样转换的？（Intel）
答案：通用寄存器给出的地址，是段内偏移地址，相应段寄存器地址*10H+通用寄存器内地址，就得到了真正要访问的地址。

30. 比较C++中的4种类型转换方式？ 

 

 
 一、问答
1、实模式与保护模式。为什么要设计这两种模式？好处在什么地方？分别写出各自寻址的过程。
答：
1. 实模式，又叫实地址模式，CPU完全按照8086的实际寻址方法访问从00000h--FFFFFh（1MB大小）的地址范围的内存，在这种模式下， CPU只能做单任务运行；寻址公式为：物理地址=左移4位的段地址+偏移地址，即：物理地址是由16位的段地址和16位的段内偏移地址组成的。
2. 保护模式，又叫内存保护模式，寻址采用32位段和偏移量，最大寻址空间4GB，在这种模式下，系统运行于多任务，设计这种模式的原因和好处是：保护模式增加了寻址空间，增加了对多任务的支持，增加了段页式寻址机制的内存管理（分段机制使得段具有访问权限和特权级，各应用程序和操作系统的代码和核心是被保护的，这也是多任务支持的实现关键和保护这个名字的由来）。寻址过程为：物理地址=由段地址查询全局描述符表中给出的段基址+偏移地址，即：物理地址由影像寄存器中的基址加上16位或者32位的偏移组成。

2、请阅读以下一段程序，并给出答案。

class A
{
public:
A(){ doSth(); }
virtual void doSth(){printf("I am A");}
};
class B:public A
{
public:
virtual void doSth(){ printf("I am B");}
};
B b;
执行结果是什么？为什么？
答：执行结果是I am A
因为b对象构造时调用基类A的构造函数A()，得此结果。

3、在STL的应用中 map这种key-value的应用很多，如果key的类型是GUID，该如何处理？
答：谁知道怎么处理补上吧。

4、一个内存变量a=5，有5个线程需要对其进行操作，其中3个对a进行加1操作，2个对a进行减1操作，为了保证能够得到正常结果6，需要使用什么方法？（列出越多越好）
答：即要求列出线程同步方法，具体答案可见下面一题。

5、描述并比较以下对象：事件，信标，临界区，互斥对象。
答：这些对象都是用于线程同步的对象。
临界区：一种保证在某一时刻只有一个线程能访问数据的简便办法。它只可以在同一进程内部使用。主要API函数有，产生临界区： InitializeCriticalSection，删除临界区：DeleteCriticalSection，进入临界区： EnterCriticalSection，退出临界区：LeaveCriticalSection。
互斥对象：互斥对象跟临界区相似，但它不仅仅能够在同一应用程序不同线程中实现资源的安全共享，而且可以在不同应用程序的线程之间实现对资源的安全共享，当然下面两者也有这个特点。主要API函数有，创建互斥量： CreateMutex，打开一个存在的互斥量： OpenMutex，释放互斥量的使用权：ReleaseMutex，关闭互斥量： CloseHandle。
信标：使用信号量（信标）最重要用途是：信号允许多个线程同时使用共享资源，它指出了同时访问共享资源的线程最大数目。它的API函数和使用方法都与互斥对象相似，如创建信号灯：CreateSemaphore，传入的参数可以指定信号灯的初始值。
事件：用来通知其他进程/线程某件操作已经完成。API函数有创建，打开事件对象等，特殊点的是可以用函数SetEvent人工设置事件为有无信号状态，因此创建事件对象时可以有两种方式，一种为自动重置，一种为人工重置。只有人工重置方式创建的事件对象才能正确使用函数SetEvent。
鉴于本套题考的是VC，有必要说明的是在MFC中对于各种同步对象都提供了相对应的类CCtiticalSection,CMutex,CSemaphore ,CEvent，另外为使用等待功能封装了两个类：CSingleLock和CMultiLock。这些类方便了使用这些同步对象。

6、cdecl、stdcall、fastcall是什么？哪种可以实现个数不定的入口参数，为什么？
答：三者都是函数调用的约定。
cdecl：c declare（C调用约定）的缩写，是C和C++程序的缺省调用方式，规则是，按从右至左的顺序压参数入栈，由调用者把参数弹出栈，对于传送参数的内存栈是由调用者来维护的，正因为如此，只有这种调用方式可实现个数不定的入口参数（可变参数）。
stdcall：是Pascal程序的缺省调用方式，规则是，按从右至左的顺序压参数入栈，被调用的函数在返回前清理传送参数的内存栈。
上两者的主要区别是前者由调用者清理栈，后者由被调用的函清理栈。当然函数名的修饰部分也是不同的。
fastcall：采用寄存器传递参数，特点就是快了。

二、程序设计（以下题目请写出实现代码）
1、有一段文本，统计其中的单词数。例如：
As a technology , "HailStorm" is so new that it is still only known by its
code name.
注意：单词间的间隔不一定是一个空格。
答：可执行程序代码如下，假设该文本已存入text这个数组里。

void main()
{
char text[1000]={"As a technology , 'HailStorm' is so new that it is still only known by its code name."};
int i=0,count=0;
bool flag=true;
while (text[i]&&i<1000) 
{
if (text[i]==' ') 
{
flag=true;
}
else if (flag==true && ((text[i]>='a'&&text[i]<='z')||(text[i]>='A'&&text[i]<='Z'))) 
{ // 前有空格，接着出现字母，表示出现一个单词。
count++;
flag=false;
}
i++;
}
cout<<count;
}


2、国际象棋有8×8格，每个格子可放一个棋子。皇后的规则是可以横、竖、斜移动。在一个棋盘放置8个皇后，并使它们互相无法威胁到彼此。
答：以下是可执行C代码，采用非递归解法，你如果想了解皇后问题的算法的详细过程可看下面网址：
http://www.cnjcw.cn/infoview/2005031720203563221270.html
不过下面的代码是以列优先进行试探的，不是上面网址介绍的那样以行优先的，当然本质是一样的。

#include <iostream.h>
#define QUEEN 8 //皇后数量
int queen[QUEEN] ; //下标代表所在列号,值代表所在行号，
//如queen[1]=2表示第1列第2行有个皇后
bool row_YN[QUEEN] ; //棋局的每一行是否有棋,有则为1,无为0 ;
bool passive_YN[2*QUEEN-1] ; //斜率为1的斜线方向上是否有棋,共有2*QUEEN-1个斜线
bool negative_YN[2*QUEEN-1] ; //斜率为负1的斜线方向上是否有棋
//用全局变量,因全局数组元素值自动为0
int main()
{ 
int row = 0 ;//游标,当前移动的棋子(以列计)
bool flag = false ; //当前棋子位置是否合法
queen[0] = -1 ; //第0列棋子准备,因一开始移动的就是第0列棋子
int count = 0 ; //一共有多少种解法的计数器 ;

while(row>=0 ) //跳出条件是回溯到无法回溯时 
{
queen[row]++ ; //row列上的皇后走到下一行试试
if(queen[row] >= QUEEN) //当前列全部走完
{ 
queen[row] = -1 ; //当前列棋子置于准备状态
row-- ; //回溯到上一列的棋子
if(row>=0) //回溯时要清理如下行，斜线的标志位 
{
row_YN[queen[row]] = false ; 
passive_YN[queen[row] + row] = false ;
negative_YN[QUEEN-1 + row - queen[row]] = false ;
} 
}
else
{ 
//先判断棋子所在行没有棋子
if(row_YN[queen[row]] == false) 
{
flag = true ; 
//以下检查当前棋子是否与之前的棋子斜线相交
if( passive_YN[queen[row] + row] == true || negative_YN[QUEEN-1 + row - queen[row]] == true) 
flag = false ;
else 
flag = true ;
if(flag) // flag为真表示位置合法
{ 
if(row == QUEEN-1) //列到达最后，即最后一个皇后也找到位置，输出解
{
count++ ; //解法的数目加一 ;
cout<<"***第"<<count<<"种解法***"<<endl ;
for(int i=0;i<QUEEN;i++)
cout<<"第"<<i<<"列皇后在第"<<queen[i]<<"行"<<endl;
}
row_YN[queen[row]] = true ;// 当前行设为有棋子
passive_YN[queen[row] + row] = true ;//当前行正斜率方向有棋子
negative_YN[QUEEN-1 + row - queen[row]] = true ; //当前行负斜率方向上也有棋子
row++ ;
if(row >= QUEEN) 
{ // 找到解后再次回溯找另外的解，这同上面无解回溯是一样的
row-- ;
row_YN[queen[row]] = false ; 
passive_YN[queen[row] + row] = false ;
negative_YN[QUEEN-1 + row - queen[row]] = false ;//原理同回溯
} 
flag = false ; 
}
}
}
}
cout<<QUEEN<<"皇后问题一共有"<<count<<"种解法"<<endl ;
return 0 ;
}

3、输入二个64位的十进制数，计算相乘之后的乘积。
答：以下代码为网上别人贴出的，输入任意位数十进制数（包括小数，负数）都可以得出正确结果。
思路是：将大数当作字符串进行处理，也就是将大数用10进制字符数组进行表示，然后模拟人们手工进行“竖式计算”的过程编写乘法。

#include <iostream.h>
#define MAX 100
int str_num(char str[]) //计算字符串的长度,等效于strlen(str);
{
int i=0,num_str=0;
while(str[i]!=0)
{num_str++;
i++;
}
return(num_str);
}
void place(int num_str,char str[]) //将字符串高低颠倒。
{
int temp=0,i=0,j=0;
for(i=0,j=num_str-1;i<j;i++,j--)
{temp=str[j];
str[j]=str[i];
str[i]=temp;
}
}
void transition(unsigned int a[],char str1[]) //数字字符转化为数字。
{
int i=0;
while(str1[i]!=0)
{a[i]=str1[i]-'0';
i++;
}
}
void multiply_int(unsigned int a[],unsigned int b[],unsigned int c[]) //大数相乘算法，入口为整形数组。
{
int i=0,j=0;
for(i=0;i<MAX;i++)
for(j=0;j<MAX;j++)
{
c[i+j]+=a[i]*b[j];
c[i+j+1]+=c[i+j]/10;
c[i+j]%=10;
}
}
void output(int sign,unsigned int c[],int quan) //数据输出。
{
int sign_temp=0,i=0;
cout<<"The result is: ";
if(sign==1)
cout<<"-";
for(i=MAX-1;i>-1;i--)
{
if(sign_temp==0)
{if(c[i]!=0)
sign_temp=1;
}
if(sign_temp==1)
{
if(i==quan-1)
cout<<".";
cout<<c[i];
c[i]=0;
}
}
cout<<endl;
}
void multiply_string(char str1[],char str2[],unsigned int c[]) //大数相乘，入口为字符串。
{
unsigned int a[MAX]={0},b[MAX]={0};
int sign=0;
transition(a,str1);
transition(b,str2);
multiply_int(a,b,c);
}
int sign_comp(char str1[],char str2[]) //符号判断，如果为负数将作相应处理。
{
int i=0,sign_num=0;
if(str1[0]==45)
{sign_num=!sign_num;
for(i=0;i<MAX-1;i++)
str1[i]=str1[i+1];
}
if(str2[0]==45)
{sign_num=!sign_num;
for(i=0;i<MAX-1;i++)
str2[i]=str2[i+1];
}
return (sign_num);
}
int format(char str[]) //将输入的字符串进行格式化。以得到字符的一些标志信息和相应格式的新数据串。
{
int point=0,quan=0,i=0,j,k=0,sign_point=0,num_str=0;
num_str=str_num(str);
while(str[i]!=0)
{
if(str[i]<'0'||str[i]>'9')
if(str[i]!='.')
{cout<<"data error"<<endl;
return(-1);
}
else
{point++;
sign_point=i;
}
if(point>1)
{cout<<"data error"<<endl;
return(-1);
}
i++;
}
if(point==1)
{
for(j=sign_point;j<num_str;j++)
str[j]=str[j+1];
num_str--;
quan=num_str-sign_point;
}
place(num_str,str);
return(quan);
}
void clear(char str[]) //清空函数。
{
int i;
for(i=0;i<MAX;i++)
{
str[i]=0;
}
}

void main(void) //主函数。
{
char str1[MAX]={0},str2[MAX]={0};
int quan1=0,quan2=0,sign=0;
unsigned int c[MAX*2+1]={0};
do
{
cout<<"Please input the first number:";
cin>>str1;
cout<<"Please input the second number:";
cin>>str2;
sign=sign_comp(str1,str2);
quan1=format(str1);
quan2=format(str2);
if(quan1==-1||quan2==-1)
{ 
clear(str1);
clear(str2);
}
}while(quan1==-1||quan2==-1||str1[0]==0||str2[0]==0);
multiply_string(str1,str2,c);
output(sign,c,quan1+quan2);
}

所有题目到此结束，说实话后面两题的算法我就是看别人的代码（呵呵，再次实话，后两题代码也不是我写的，只是对已有代码做了些修改，使结构更清晰，便于阅读）理解清楚也用了2个小时以上，所以我还真没有自信将答案发到那个邮箱呢。看白云黄鹤上别的学生的反响，让人怀疑这套题是否出得有点难了。 


已经n次倒在c语言面试的问题上，总结了一下，是由于基础知识不扎实。痛定思痛，决定好好努力！

1.引言

　　本文的写作目的并不在于提供C/C++程序员求职面试指导，而旨在从技术上分析面试题的内涵。文中的大多数面试题来自各大论坛，部分试题解答也参考了网友的意见。

　　许多面试题看似简单，却需要深厚的基本功才能给出完美的解答。企业要求面试者写一个最简单的strcpy函数都可看出面试者在技术上究竟达到了怎样的程度，我们能真正写好一个strcpy函数吗？我们都觉得自己能，可是我们写出的strcpy很可能只能拿到10分中的2分。读者可从本文看到strcpy 函数从2分到10分解答的例子，看看自己属于什么样的层次。此外，还有一些面试题考查面试者敏捷的思维能力。

　　分析这些面试题，本身包含很强的趣味性；而作为一名研发人员，通过对这些面试题的深入剖析则可进一步增强自身的内功。

2.找错题

　　试题1：

void test1()
{
　char string[10];
　char* str1 = "0123456789";
　strcpy( string, str1 );
}

　　试题2：

void test2()
{
　char string[10], str1[10];
　int i;
　for(i=0; i＜10; i++)
　{
　　str1[i] = 'a';
　}
　strcpy( string, str1 );
}

　　试题3：

void test3(char* str1)
{
　char string[10];
　if( strlen( str1 ) ＜= 10 )
　{
　　strcpy( string, str1 );
　}
}

　　解答：

　　试题1字符串str1需要11个字节才能存放下（包括末尾的’\0’），而string只有10个字节的空间，strcpy会导致数组越界；

　　对试题2，如果面试者指出字符数组str1不能在数组内结束可以给3分；如果面试者指出strcpy(string, str1)调用使得从str1内存起复制到string内存起所复制的字节数具有不确定性可以给7分，在此基础上指出库函数strcpy工作方式的给10 分；

　　对试题3，if(strlen(str1) ＜= 10)应改为if(strlen(str1) ＜ 10)，因为strlen的结果未统计’\0’所占用的1个字节。

　　剖析：

　　考查对基本功的掌握：

　　(1)字符串以’\0’结尾；

　　(2)对数组越界把握的敏感度；

　　(3)库函数strcpy的工作方式，如果编写一个标准strcpy函数的总分值为10，下面给出几个不同得分的答案：

　　2分

void strcpy( char *strDest, char *strSrc )
{
　 while( (*strDest++ = * strSrc++) != ‘\0’ );
}

　　4分

void strcpy( char *strDest, const char *strSrc )
//将源字符串加const，表明其为输入参数，加2分
{
　 while( (*strDest++ = * strSrc++) != ‘\0’ );
}

　　7分

void strcpy(char *strDest, const char *strSrc)
{
　//对源地址和目的地址加非0断言，加3分
　assert( (strDest != NULL) && (strSrc != NULL) );
　while( (*strDest++ = * strSrc++) != ‘\0’ );
}

　　10分

//为了实现链式操作，将目的地址返回，加3分！

char * strcpy( char *strDest, const char *strSrc )
{
　assert( (strDest != NULL) && (strSrc != NULL) );
　char *address = strDest;
　while( (*strDest++ = * strSrc++) != ‘\0’ );
　　return address;
}

　　从2分到10分的几个答案我们可以清楚的看到，小小的strcpy竟然暗藏着这么多玄机，真不是盖的！需要多么扎实的基本功才能写一个完美的strcpy啊！

　　(4)对strlen的掌握，它没有包括字符串末尾的'\0'。

　　读者看了不同分值的strcpy版本，应该也可以写出一个10分的strlen函数了，完美的版本为： 

int strlen( const char *str ) //输入参数const

{
　assert( strt != NULL ); //断言字符串地址非0
　int len;
　while( (*str++) != '\0' )
　{
　　len++;
　}
　return len;
}

　　试题4：

void GetMemory( char *p )
{
　p = (char *) malloc( 100 );
}

void Test( void )
{
　char *str = NULL;
　GetMemory( str );
　strcpy( str, "hello world" );
　printf( str );
}

　　试题5：

char *GetMemory( void )
{
　char p[] = "hello world";
　return p;
}

void Test( void )
{
　char *str = NULL;
　str = GetMemory();
　printf( str );
}

　　试题6：

void GetMemory( char **p, int num )
{
　*p = (char *) malloc( num );
}

void Test( void )
{
　char *str = NULL;
　GetMemory( &str, 100 );
　strcpy( str, "hello" );
　printf( str );
}

　　试题7：

void Test( void )
{
　char *str = (char *) malloc( 100 );
　strcpy( str, "hello" );
　free( str );
　... //省略的其它语句
}

　　解答：

　　试题4传入中GetMemory( char *p )函数的形参为字符串指针，在函数内部修改形参并不能真正的改变传入形参的值，执行完

char *str = NULL;
GetMemory( str );

　　后的str仍然为NULL；

　　试题5中

char p[] = "hello world";
return p;

　　的p[]数组为函数内的局部自动变量，在函数返回后，内存已经被释放。这是许多程序员常犯的错误，其根源在于不理解变量的生存期。

　　试题6的GetMemory避免了试题4的问题，传入GetMemory的参数为字符串指针的指针，但是在GetMemory中执行申请内存及赋值语句

*p = (char *) malloc( num );

　　后未判断内存是否申请成功，应加上：

if ( *p == NULL )
{
　...//进行申请内存失败处理
}

　　试题7存在与试题6同样的问题，在执行

char *str = (char *) malloc(100);

　　后未进行内存是否申请成功的判断；另外，在free(str)后未置str为空，导致可能变成一个“野”指针，应加上：

str = NULL;

　　试题6的Test函数中也未对malloc的内存进行释放。

　　剖析：

　　试题4～7考查面试者对内存操作的理解程度，基本功扎实的面试者一般都能正确的回答其中50~60的错误。但是要完全解答正确，却也绝非易事。

　　对内存操作的考查主要集中在：

　　（1）指针的理解；

　　（2）变量的生存期及作用范围；

　　（3）良好的动态内存申请和释放习惯。

　　再看看下面的一段程序有什么错误：

swap( int* p1,int* p2 )
{
　int *p;
　*p = *p1;
　*p1 = *p2;
　*p2 = *p;
}

　　在swap函数中，p是一个“野”指针，有可能指向系统区，导致程序运行的崩溃。在VC++中DEBUG运行时提示错误“Access Violation”。该程序应该改为：

swap( int* p1,int* p2 )
{
　int p;
　p = *p1;
　*p1 = *p2;
　*p2 = p;
}

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

3.内功题

　　试题1：分别给出BOOL，int，float，指针变量 与“零值”比较的 if 语句（假设变量名为var）

　　解答：

　　　BOOL型变量：if(!var)

　　　int型变量： if(var==0)

　　　float型变量：

　　　const float EPSINON = 0.00001;

　　　if ((x ＞= - EPSINON) && (x ＜= EPSINON)

　　　指针变量：　　if(var==NULL)

　　剖析：

　　考查对0值判断的“内功”，BOOL型变量的0判断完全可以写成if(var==0)，而int型变量也可以写成if(!var)，指针变量的判断也可以写成if(!var)，上述写法虽然程序都能正确运行，但是未能清晰地表达程序的意思。

　　一般的，如果想让if判断一个变量的“真”、“假”，应直接使用if(var)、if(!var)，表明其为“逻辑”判断；如果用if判断一个数值型变量(short、int、long等)，应该用if(var==0)，表明是与0进行“数值”上的比较；而判断指针则适宜用if(var==NULL)，这是一种很好的编程习惯。

　　浮点型变量并不精确，所以不可将float变量用“==”或“！=”与数字比较，应该设法转化成“＞=”或“＜=”形式。如果写成if (x == 0.0)，则判为错，得0分。

　　试题2：以下为Windows NT下的32位C++程序，请计算sizeof的值

void Func ( char str[100] )
{
　sizeof( str ) = ?
}

void *p = malloc( 100 );
sizeof ( p ) = ?

　　解答：

sizeof( str ) = 4
sizeof ( p ) = 4

　　剖析：

　　Func ( char str[100] )函数中数组名作为函数形参时，在函数体内，数组名失去了本身的内涵，仅仅只是一个指针；在失去其内涵的同时，它还失去了其常量特性，可以作自增、自减等操作，可以被修改。

　　数组名的本质如下：

　　（1）数组名指代一种数据结构，这种数据结构就是数组；

　　例如：

char str[10];
cout ＜＜ sizeof(str) ＜＜ endl;

　　输出结果为10，str指代数据结构char[10]。

　　（2）数组名可以转换为指向其指代实体的指针，而且是一个指针常量，不能作自增、自减等操作，不能被修改；

char str[10];
str++; //编译出错，提示str不是左值　

　　（3）数组名作为函数形参时，沦为普通指针。

　　Windows NT 32位平台下，指针的长度（占用内存的大小）为4字节，故sizeof( str ) 、sizeof ( p ) 都为4。

　　试题3：写一个“标准”宏MIN，这个宏输入两个参数并返回较小的一个。另外，当你写下面的代码时会发生什么事

least = MIN(*p++, b);

　　解答：

#define MIN(A,B) ((A) ＜= (B) ? (A) : (B))

　　MIN(*p++, b)会产生宏的副作用

　　剖析：

　　这个面试题主要考查面试者对宏定义的使用，宏定义可以实现类似于函数的功能，但是它终归不是函数，而宏定义中括弧中的“参数”也不是真的参数，在宏展开的时候对“参数”进行的是一对一的替换。

　　程序员对宏定义的使用要非常小心，特别要注意两个问题：

　　（1）谨慎地将宏定义中的“参数”和整个宏用用括弧括起来。所以，严格地讲，下述解答：

#define MIN(A,B) (A) ＜= (B) ? (A) : (B)
#define MIN(A,B) (A ＜= B ? A : B )

　　都应判0分；

　　（2）防止宏的副作用。

　　宏定义#define MIN(A,B) ((A) ＜= (B) ? (A) : (B))对MIN(*p++, b)的作用结果是：

((*p++) ＜= (b) ? (*p++) : (*p++))

　　这个表达式会产生副作用，指针p会作三次++自增操作。

　　除此之外，另一个应该判0分的解答是：

#define MIN(A,B) ((A) ＜= (B) ? (A) : (B));

　　这个解答在宏定义的后面加“;”，显示编写者对宏的概念模糊不清，只能被无情地判0分并被面试官淘汰。

　　试题4：为什么标准头文件都有类似以下的结构？

#ifndef __INCvxWorksh
#define __INCvxWorksh
#ifdef __cplusplus

extern "C" {
#endif
/*...*/
#ifdef __cplusplus
}

#endif
#endif /* __INCvxWorksh */

　　解答：

　　头文件中的编译宏

#ifndef　__INCvxWorksh
#define　__INCvxWorksh
#endif

　　的作用是防止被重复引用。

　　作为一种面向对象的语言，C++支持函数重载，而过程式语言C则不支持。函数被C++编译后在symbol库中的名字与C语言的不同。例如，假设某个函数的原型为：

void foo(int x, int y);

　　该函数被C编译器编译后在symbol库中的名字为_foo，而C++编译器则会产生像_foo_int_int之类的名字。_foo_int_int这样的名字包含了函数名和函数参数数量及类型信息，C++就是考这种机制来实现函数重载的。

　　为了实现C和C++的混合编程，C++提供了C连接交换指定符号extern "C"来解决名字匹配问题，函数声明前加上extern "C"后，则编译器就会按照C语言的方式将该函数编译为_foo，这样C语言中就可以调用C++的函数了。

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

　试题5：编写一个函数，作用是把一个char组成的字符串循环右移n个。比如原来是“abcdefghi”如果n=2，移位后应该是“hiabcdefgh”

　　函数头是这样的：

//pStr是指向以'\0'结尾的字符串的指针
//steps是要求移动的n

void LoopMove ( char * pStr, int steps )
{
　//请填充...
}

　　解答：

　　正确解答1：

void LoopMove ( char *pStr, int steps )
{
　int n = strlen( pStr ) - steps;
　char tmp[MAX_LEN];
　strcpy ( tmp, pStr + n );
　strcpy ( tmp + steps, pStr);
　*( tmp + strlen ( pStr ) ) = '\0';
　strcpy( pStr, tmp );
}

　　正确解答2：

void LoopMove ( char *pStr, int steps )
{
　int n = strlen( pStr ) - steps;
　char tmp[MAX_LEN];
　memcpy( tmp, pStr + n, steps );
　memcpy(pStr + steps, pStr, n );
　memcpy(pStr, tmp, steps );
}

　　剖析：

　　这个试题主要考查面试者对标准库函数的熟练程度，在需要的时候引用库函数可以很大程度上简化程序编写的工作量。

　　最频繁被使用的库函数包括：

　　（1） strcpy

　　（2） memcpy

　　（3） memset

　　试题6：已知WAV文件格式如下表，打开一个WAV文件，以适当的数据结构组织WAV文件头并解析WAV格式的各项信息。

　　WAVE文件格式说明表


1.给两个数组和他们的大小，还有一动态开辟的内存，求交集，把交集放到动态内存dongtai，并且返回交集个数
long jiaoji(long* a[],long b[],long* alength,long blength,long* dongtai[])
2.单连表的建立，把'a'--'z'26个字母插入到连表中，并且倒叙，还要打印！
方法1：
typedef struct val
{ int date_1;
struct val *next;
}*p;

void main(void)
{ char c;

for(c=122;c>=97;c--)
{ p.date=c;
p=p->next;
}

p.next=NULL;
} 
}
方法2：
node *p = NULL;
node *q = NULL;

node *head = (node*)malloc(sizeof(node));
head->data = ' ';head->next=NULL;

node *first = (node*)malloc(sizeof(node));
first->data = 'a';first->next=NULL;head->next = first;
p = first;

int longth = 'z' - 'b';
int i=0;
while ( i<=longth )
{
node *temp = (node*)malloc(sizeof(node));
temp->data = 'b'+i;temp->next=NULL;q=temp;

head->next = temp; temp->next=p;p=q;
i++;
}

print(head);

3.可怕的题目终于来了
象搜索的输入信息是一个字符串，统计300万输入信息中的最热门的前十条，我们每次输入的一个字符串为不超过255byte,内存使用只有1G,
请描述思想，写出算发（c语言），空间和时间复杂度，
4.国内的一些帖吧，如baidu,有几十万个主题，假设每一个主题都有上亿的跟帖子，怎么样设计这个系统速度最好，请描述思想，写出算发（c语言），空间和时间复杂度，


#include string.h
main(void)
{ char *src="hello,world";
char *dest=NULL;
dest=(char *)malloc(strlen(src));
int len=strlen(str);
char *d=dest;
char *s=src[len];
while(len--!=0)
d++=s--;
printf("%s",dest);
}
找出错误！！
#include "string.h"
#include "stdio.h"
#include "malloc.h"
main(void)
{ 
char *src="hello,world";
char *dest=NULL;
dest=(char *)malloc(sizeof(char)*(strlen(src)+1));
int len=strlen(src);
char *d=dest;
char *s=src+len-1;
while(len--!=0)
*d++=*s--;
*d='\0';
printf("%s",dest);
}

1. 简述一个Linux驱动程序的主要流程与功能。

2. 请列举一个软件中时间换空间或者空间换时间的例子。
void swap(int a,int b)
{
int c; c=a;a=b;b=a;
}
--->空优 
void swap(int a,int b)
{
a=a+b;b=a-b;a=a-b;
}
6. 请问一下程序将输出什么结果？
char *RetMenory(void)
{
char p[] = “hellow world”;
return p;
}
void Test(void)
{
char *str = NULL;
str = RetMemory();
printf(str);
}
RetMenory执行完毕，p资源被回收，指向未知地址。返回地址，str的内容应是不可预测的, 打印的应该是str的地址


写一个函数,它的原形是int continumax(char *outputstr,char *intputstr)
功能：
在字符串中找出连续最长的数字串，并把这个串的长度返回，并把这个最长数字串付给其中一个函数参数outputstr所指内存。例如："abcd12345ed125ss123456789"的首地址传给intputstr后，函数将返回
9，outputstr所指的值为123456789
int continumax(char *outputstr, char *inputstr)
{
char *in = inputstr, *out = outputstr, *temp, *final;
int count = 0, maxlen = 0;

while( *in != '\0' )
{
if( *in > 47 && *in < 58 )
{
for(temp = in; *in > 47 && *in < 58 ; in++ )
count++;
}
else
in++;

if( maxlen < count )
{
maxlen = count;
count = 0;
final = temp;
}
}
for(int i = 0; i < maxlen; i++)
{
*out = *final;
out++;
final++;
}
*out = '\0';
return maxlen;
}

不用库函数,用C语言实现将一整型数字转化为字符串
方法1：
int getlen(char *s){
int n;
for(n = 0; *s != '\0'; s++)
n++;
return n;
}
void reverse(char s[])
{
int c,i,j;
for(i = 0,j = getlen(s) - 1; i < j; i++,j--){
c = s[i];
s[i] = s[j];
s[j] = c;
}
}
void itoa(int n,char s[])
{
int i,sign;
if((sign = n) < 0)
n = -n;
i = 0;
do{/*以反序生成数字*/
s[i++] = n%10 + '0';/*get next number*/
}while((n /= 10) > 0);/*delete the number*/

if(sign < 0)
s[i++] = '-';

s[i] = '\0';
reverse(s);
}
方法2:
#include <iostream>
using namespace std;

void itochar(int num);

void itochar(int num)
{
int i = 0;
int j ;
char stra[10];
char strb[10];
while ( num )
{
stra[i++]=num%10+48;
num=num/10;
}
stra[i] = '\0';
for( j=0; j < i; j++)
{
strb[j] = stra[i-j-1];
}
strb[j] = '\0';
cout<<strb<<endl;

}
int main()
{
int num;
cin>>num;
itochar(num);
return 0;
}

前几天面试，有一题想不明白,请教大家！
typedef struct 
{ 
int a:2;
int b:2;
int c:1;
}test;

test t;
t.a = 1;
t.b = 3;
t.c = 1;

printf("%d",t.a);
printf("%d",t.b);
printf("%d",t.c);

谢谢!
t.a为01,输出就是1
t.b为11，输出就是－1
t.c为1，输出也是-1
3个都是有符号数int嘛。
这是位扩展问题 
01
11
1
编译器进行符号扩展


求组合数： 求n个数（1....n）中k个数的组合....
如：combination(5,3)
要求输出：543，542，541，532，531，521，432，431，421，321，
#include<stdio.h>

int pop(int *);
int push(int );
void combination(int ,int );

int stack[3]={0};
top=-1;

int main()
{
int n,m;
printf("Input two numbers:\n");
while( (2!=scanf("%d%*c%d",&n,&m)) )
{
fflush(stdin);
printf("Input error! Again:\n");
}
combination(n,m);
printf("\n");
}
void combination(int m,int n)
{
int temp=m;
push(temp);
while(1)
{
if(1==temp)
{
if(pop(&temp)&&stack[0]==n) //当栈底元素弹出&&为可能取的最小值，循环退出
break;
}
else if( push(--temp))
{
printf("%d%d%d ",stack[0],stack[1],stack[2]);//§ä¨ì¤@?
pop(&temp);
}
}
}
int push(int i)
{
stack[++top]=i;
if(top<2)
return 0;
else
return 1;
}
int pop(int *i)
{
*i=stack[top--];
if(top>=0)
return 0;
else
return 1;
}

1、用指针的方法，将字符串“ABCD1234efgh”前后对调显示
#include <stdio.h>
#include <string.h>
#include <dos.h>
int main()
{
char str[] = "ABCD1234efgh";
int length = strlen(str);
char * p1 = str;
char * p2 = str + length - 1;
while(p1 < p2)
{
char c = *p1;
*p1 = *p2;
*p2 = c;
++p1;
--p2;
}
printf("str now is %s\n",str);
system("pause");
return 0;
}
2、有一分数序列：1/2,1/4,1/6,1/8……，用函数调用的方法，求此数列前20项的和
#include <stdio.h>
double getValue()
{
double result = 0;
int i = 2;
while(i < 42)
{
result += 1.0 / i;//一定要使用1.0做除数，不能用1，否则结果将自动转化成整数，即0.000000
i += 2;
}
return result;
}
int main()
{
printf("result is %f\n", getValue());
system("pause");
return 0;
}
有一个数组a[1000]存放0--1000;要求每隔二个数删掉一个数，到末尾时循环至开头继续进行，求最后一个被删掉的数的原始下标位置。
以7个数为例：
{0,1,2,3,4,5,6,7} 0-->1-->2（删除）-->3-->4-->5(删除)-->6-->7-->0（删除），如此循环直到最后一个数被删除。
方法1：数组
#include <iostream>
using namespace std;
#define null 1000

int main()
{
int arr[1000];
for (int i=0;i<1000;++i)
arr[i]=i;
int j=0;
int count=0;
while(count<999)
{
while(arr[j%1000]==null)
j=(++j)%1000;
j=(++j)%1000;
while(arr[j%1000]==null)
j=(++j)%1000;
j=(++j)%1000;
while(arr[j%1000]==null)
j=(++j)%1000;
arr[j]=null;
++count;
}
while(arr[j]==null)
j=(++j)%1000;

cout<<j<<endl;
return 0;
}方法2：链表
#include<iostream>
using namespace std;
#define null 0
struct node
{
int data;
node* next;
};
int main()
{
node* head=new node;
head->data=0;
head->next=null;
node* p=head;
for(int i=1;i<1000;i++)
{
node* tmp=new node;
tmp->data=i;
tmp->next=null;
head->next=tmp;
head=head->next;
}
head->next=p;
while(p!=p->next)
{
p->next->next=p->next->next->next;
p=p->next->next;
}
cout<<p->data;
return 0;
}
方法3：通用算法
#include <stdio.h>
#define MAXLINE 1000 //元素个数
/*
MAXLINE 元素个数
a[] 元素数组
R[] 指针场
suffix 下标
index 返回最后的下标序号
values 返回最后的下标对应的值
start 从第几个开始
K 间隔
*/
int find_n(int a[],int R[],int K,int& index,int& values,int s=0) {
int suffix;
int front_node,current_node;
suffix=0;
if(s==0) {
current_node=0;
front_node=MAXLINE-1;
}
else {
current_node=s;
front_node=s-1;
}
while(R[front_node]!=front_node) {
printf("%d\n",a[current_node]);
R[front_node]=R[current_node];
if(K==1) {
current_node=R[front_node];
continue;
}
for(int i=0;i<K;i++){
front_node=R[front_node];
}
current_node=R[front_node];
}
index=front_node;
values=a[front_node];

return 0;
}
int main(void) {
int a[MAXLINE],R[MAXLINE],suffix,index,values,start,i,K;
suffix=index=values=start=0;
K=2;

for(i=0;i<MAXLINE;i++) {
a[i]=i;
R[i]=i+1;
}
R[i-1]=0;
find_n(a,R,K,index,values,2);
printf("the value is %d,%d\n",index,values);
return 0;
}

试题： 
void test2() 
{ 
char string[10], str1[10]; 
int i; 
for(i=0; i<10; i++) 
{ 
str1[i] = 'a'; 
} 
strcpy( string, str1 ); 
} 
解答：对试题2，如果面试者指出字符数组str1不能在数组内结束可以给3分；如果面试者指出strcpy(string, str1)调用使得从str1内存起复制到string内存起所复制的字节数具有不确定性可以给7分，在此基础上指出库函数strcpy工作方式的给10分；
str1不能在数组内结束:因为str1的存储为：{a,a,a,a,a,a,a,a,a,a},没有'\0'(字符串结束符)，所以不能结束
strcpy( char *s1,char *s2)他的工作原理是，扫描s2指向的内存，逐个字符付到s1所指向的内存，直到碰到'\0',因为str1结尾没有'\0'，所以具有不确定性，不知道他后面还会付什么东东。
正确应如下
void test2() 
{ 
char string[10], str1[10]; 
int i; 
for(i=0; i<9; i++) 
{ 
str1[i] = 'a'+i; //把abcdefghi赋值给字符数组
} 
str[i]='\0';//加上结束符
strcpy( string, str1 ); 
}

第二个code题是实现strcmp
int StrCmp(const char *str1, const char *str2)
做是做对了，没有抄搞，比较乱
int StrCmp(const char *str1, const char *str2)
{
assert(str1 && srt2);
while (*str1 && *str2 && *str1 == *str2) {
str1++, str2++;
}
if (*str1 && *str2)
return (*str1-*str2);
elseif (*str1 && *str2==0)
return 1;
elseif (*str1 = = 0 && *str2)
return -1;
else
return 0;
}

int StrCmp(const char *str1, const char *str2)
{
//省略判断空指针(自己保证)
while(*str1 && *str1++ = = *str2++);
return *str1-*str2; 
}
第三个code题是实现子串定位
int FindSubStr(const char *MainStr, const char *SubStr)
做是做对了，没有抄搞，比较乱
int MyStrstr(const char* MainStr, const char* SubStr)
{
const char *p;
const char *q;
const char * u = MainStr;

//assert((MainStr!=NULL)&&( SubStr!=NULL));//用断言对输入进行判断
while(*MainStr) //内部进行递增
{
p = MainStr;
q = SubStr;
while(*q && *p && *p++ == *q++);
if(!*q )
{
return MainStr - u +1 ;//MainStr指向当前起始位，u指向
}
MainStr ++;
}
return -1;
}

分析：
int arr[] = {6,7,8,9,10};
int *ptr = arr;
*(ptr++)+=123;
printf(“ %d %d ”, *ptr, *(++ptr));
输出：8 8
过程：对于*(ptr++)+=123;先做加法6+123，然后++，指针指向7；对于printf(“ %d %d ”, *ptr, *(++ptr));从后往前执行，指针先++，指向8，然后输出8，紧接着再输出8



C试题
类型：C试题 | 试题：55道试题（50道选择题，5道问答题） 
注意: 答题过程如果您不提交答案，或者关闭浏览器退出，我们将不再允许您再次答题。
谢谢！ 
试题 选项 
Question 1. (单选)
在顺序表(3,6,8,10,12,15,16,18,21,25,30)中,用二分法查找关键码值11,所需的关键码比
较次数为(3)

1. 2
2. 3
3. 4
4. 5

Question 2. (单选)
设散列表的存储空间大小为19,所用散列函数为h(key)=key mod 19,用开地址线性探查法解
决碰撞。散列表的当前

状态如下:0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 190 194 768 559 582 39
3 208.现要将关键码

值75插入到该散列表中,其地址应为 (1)

1. 1
2. 11
3. 5
4. 15

Question 3. (单选)
作业管理的主要任务包括作业输入、作业处理和作业输出。其中作业处理的工作是Ⅰ.作业
调度 Ⅱ.作业控制 Ⅲ.

作业后备 (3)

1. 只有Ⅰ
2. 只有Ⅱ
3. Ⅰ和Ⅱ
4. 都是

Question 4. (单选)
系统为了管理文件,设置了专门的数据结构----文件控制块(FC。FCB是在执行下列哪一个系
统调用时建立的? (1)

1. create
2. open
3. read
4. write

Question 5. (单选)
下面关于通道的叙述中,正确的是Ⅰ.通道相当于一个功能简单的处理机Ⅱ.通道完成数据输
入输出工作Ⅲ.通道与

CPU共用一个内存 (4)

1. Ⅰ和Ⅱ
2. Ⅰ和Ⅲ
3. Ⅱ和Ⅲ
4. 都是

Question 6. (单选)
互操作性是指在不同环境下的应用程序可以相互操作,交换信息。要使采用不同数据格式的
各种计算机之间能够相

互理解,这一功能是由下面哪一层来实现的? (2)

1. 应用层
2. 表示层
3. 会话层
4. 传输层

Question 7. (单选)
在UNIX的Shell程序中,可以使用位置变量。若要指明Shell引用的最近后台进程的号码,可
以使用位置变量 (2)

1. $$
2. $!
3. $#
4. $-

Question 8. (单选)
设二叉树根结点的层次为0，一棵深度(高度)为k的满二叉树和同样深度的完全二叉树各有
f个结点和c个结点，下列

关系式不正确的是： (2)

1. f>＝c
2. c>f
3. f=2k+1-1
4. C>2k-1

Question 9. (单选)
单链表的每个结点中包括一个指针link，它指向该结点的后继结点。现要将指针q指向的新
结点插入到指针p指向的

单链表结点之后，下面的操作序列中哪一个是正确的？ (3)

1. q:=p^.link; p^.link:=q^.link
2. p^.link:=q^.link; q:=P^.link
3. q^.link:=p^.link; p^.link:=q;
4. p^.link:=q; q^.link:=p^,link

Question 10. (单选)
某二叉树结点的对称序序列为A、B、C、D、E、F、G，后序序列为B、D、C、A、F、G、E。
该二叉树结点的前序序

列为 (2)

1. E、G、F、A、C、D、B
2. E、A、C、B、D、G、F
3. E、A、G、C、F、B、D
4. E、G、A、C、D、F、B

Question 11. (单选)
某二叉树结点的对称序序列为A、B、C、D、E、F、G，后序序列为B、D、C、A、F、G、E。
该二叉树对应的树林包

括多少棵树？ (2)

1. 1
2. 2
3. 3
4. 4

Question 12. (单选)
某二叉树结点的对称序序列为A、B、C、D、E、F、G，后序序列为B、D、C、A、F、G、E。
该二叉树对应的树林结

点的层次次序序列为 (1)

1. E、G、F、A、C、D、B
2. E、A、C、B、D、G、F
3. E、A、G、C、F、B、D
4. E、G、A、C、D、F、B

Question 13. (单选)
假设就绪队列中有10个进程，系统将时间片设为200ms， CPU进行进程切换要花费10ms。则
系统开销所占的比率约

为 (2)

1. 1%
2. 5%
3. 10%
4. 20%

yahoo在线笔试题（c语言）及部分答案
Question 14. (单选)
长度相同但格式不同的2种浮点数，假设前者阶码长、尾数短，后者阶码短、尾数长，其它
规定均相同，则它们可

表示的数的范围和精度为： (2)

1. 两者可表示的数的范围和精度相同
2. 前者可表示的数的范围大但精度低
3. 后者可表示的数的范围大且精度高
4. 前者可表示的数的范围大且精度高

Question 15. (单选)
所谓“变号操作”是指将一个整数变成绝对值相同但符号相反的另一个整数。假设使用补
码表示的8位整数

X=10010101，则经过变号操作后结果为：(4)

1. 1101010
2. 10101
3. 11101010
4. 1101011

Question 16. (单选)
设有一个用数组Q[1..m」表示的环形队列，约定f为当前队头元素在数组中的位置，r为队
尾元素的后一位置(按顺

时针方向)，若队列非空，则计算队列中元素个数的公式应为：(2)

1. r-f
2. (m+r-f) mod m
3. (m-r+f)mod m
4. (m-r-f) mod m

Question 17. (单选)
计算机最主要的工作特点是(2)

1. 存储程序与自动控制
2. 高速度与高精度
3. 可靠性与可用性
4. 有记忆能力

Question 18. (单选)
计算机中数据的表示形式是(3)

1. 八进制
2. 十进制
3. 二进制
4. 十六进制

Question 19. (单选)
下面列出的四种存储器中，易失性存储器是(1)

1. RAM
2. ROM
3. PROM
4. CD-ROM

Question 20. (单选)
I/O接口位于 (2)

1. 总线和设备之间
2. CPU和I/O设备之间
3. 主机和总线之间
4. CPU和主存储器之间

Question 21. (单选)
计算机硬件能直接识别和执行的只有(4)

1. 高级语言
2. 符号语言
3. 汇编语言
4. 机器语言

Question 22. (单选)
具有多媒体功能的微型计算机系统中，常用的CD-ROM是(2)

1. 只读型大容量软盘
2. 只读型光盘
3. 只读型硬盘
4. 半导体只读存储器

Question 23. (单选)
微机中1K字节表示的二进制位数是(4)

1. 1000
2. 8x1000
3. 1024
4. 8x1024

Question 24. (单选)
下列字符中，ASCII码值最小的是(2)

1. a
2. A
3. x
4. Y

Question 25. (单选)
OSI(开放系统互联)参考模型的最低层是(3)

1. 传输层
2. 网络层
3. 物理层
4. 应用层

Question 26. (单选)
在面向对象的系统中，系统责任的良好分配原则是(3)

1. 在类之间均匀分配
2. 集中分配在少数控制类中
3. 根据交互图的消息进行分配
4. 根据个人喜好进行分配

yahoo在线笔试题（c语言）及部分答案
Question 27. (单选)
在CMM模型中，对软件成熟度有以下5个级别，请从低到高排序
a 初始级:
软件过程的特点是无秩序的，偶尔甚至是混乱的。几乎没有什么过程是经过定义的,成功依
赖于个人的努力。

b 优化级:
利用来自过程和来自新思想、新技术的先导性试验的定量反馈信息，使持续过程改进成为
可能。

c 已定义级:
管理活动和工程活动两方面的软件过程均已文档化、标准化、并集成到组织的标准软件过
程。

d 已管理级:
已采集详细的有关软件过程和产品质量的度量,无论软件过程还是产品均得到定量了解和控
制。

e 可重复级:
已建立基本的项目管理过程去跟踪成本、进度和功能性。必要的过程纪律已经就位，使具
有类似应用的项目。能重

复以前的成功。
(3)

1. acdbe
2. adceb
3. aecdb
4. abcde

Question 28. (单选)
在下面所列举的逻辑测试覆盖中，测试覆盖最强的是(3)

1. 条件覆盖
2. 条件组合覆盖
3. 语句覆盖
4. 条件及判定覆盖

Question 29. (单选)
一般来说，在软件维护过程中，大部分工作是由什么引起的(3)

1. 适应新的软件环境
2. 适应新的硬件环境
3. 用户的需求改变
4. 程序的可靠性

Question 30. (单选)(2)
PSP是？

1. 团队软件过程
2. 个体软件过程
3. 过程改进过程
4. 质量管理过程

Question 31. (单选)
假定a和b为int型变量,则执行以下语句后b的值为 (4)
a=1; b=10; 
do { b-=a; a++; } while (b--<0); 

1. 9
2. -2
3. -1
4. 8

Question 32. (单选)
设有以下宏定义: 
#define N 3 
#define Y(n) ( (N+1)*n) 
则执行语句:z=2 * (N+Y(5+1));后,z的值为 (3)

1. 出错
2. 42
3. 48
4. 54

Question 33. (单选)
执行以下程序段后,m的值为 (1)
int a[2][3]={ {1,2,3},{4,5,6} }; 
int m,*p; 
p=&a[0][0]; 
m=(*p)*(*(p+2))*(*(p+4));

1. 15
2. 14
3. 13
4. 12

Question 34. (单选)
有以下程序 
main() 
{ char a[]=\"programming\", b[]=\"language\"; 
char *p1,*p2; 
int i; 
p1=a; p2=b; 
for(i=0;i<7;i++) 
if(*(p1+i)==*(p2+i)) printf(\"％c\",*(p1+i)); 
} 
输出结果是 (4)

1. gm
2. rg
3. or
4. ga

Question 35. (单选)
有以下程序 
int fun(int x,int y,int *cp,int *dp) 
{ *cp=x+y; *dp=x-y; } 
main() 
{ int a, b, c, d; 
a=30; b=50; 
fun(a,b,&c,&d); 
printf(\"%d,%d
\", c, d); 
} 
输出结果是 (3)

1. 50,30
2. 30,50
3. 80,-20
4. 80,20

Question 36. (单选)
下述标识符中, 合法的用户标识符是(4)

1. A#C
2. getch
3. void
4. sizeOf

yahoo在线笔试题（c语言）及部分答案
Question 37. (单选)
以下选项中合法的字符常量是(3)

1. A
2. \'10\'
3. 68
4. D

Question 38. (单选)
以下叙述正确的是 (3)

1. 在C程序中，main函数必须位于程序的最前面
2. C程序的每行中只能写一条语句
3. C语言本身没有输入输出语句
4. 在对一个C程序进行编译的过程中，可发现注释中的拼写错误

Question 39. (单选)
以下叙述中不正确的是 (4)

1. 在不同的函数中可以使用相同名字的变量
2. 函数中的形式参数是局部变量
3. 在一个函数内定义的变量只在本函数范围内有效
4. 在一个函数内的复合语句中定义的变量在本函数范围内有效

Question 40. (单选)
设int类型的数据长度为2个字节，则 unsigned int 类型数据的取值范围是 (2)

1. 0~255
2. 0~65535
3. -32768~32767
4. -256~255

Question 41. (单选)
某文件中定义的静态全局变量(或称静态外部变量)其作用域是 (2)

1. 只限某个函数
2. 本文件
3. 跨文件
4. 不限制作用域

Question 42. (单选)
语句:printf(\"%d
\"，12 & 012)；的输出结果是 (3)

1. 12
2. 012
3. 8
4. 6

Question 43. (单选)
设int x=4; 则执行以下语句: x+=x-=x-x;后,x的值为 (3)

1. 0
2. 4
3. 8
4. 12

Question 44. (单选)
while(!x)中的(!x)与下面条件等价。 (4)

1. x==1
2. x!=1
3. x!=0
4. x==0

Question 45. (单选)
已知int i,a;执行语句: i=(a=2*3,a*5),a+6;后,变量i的值是 (3)

1. 6
2. 12
3. 30
4. 36
Question 46. (单选)
整型变量x和y的值相等、且为非0值，则以下选项中，结果为零的表达式是 (4)

1. x || y
2. x | y
3. x & y
4. x ^ y

Question 47. (单选)
x、y、z被定义为int型变量，若从键盘给x、y、z输入数据，正确的输入语句是 (2)

1. INPUT x、y、z;
2. scanf(\"%d%d%d\",&x,&y,&z);
3. scanf(\"%d%d%d\",x,y,z);
4. read(\"%d%d%d\",x,y,z);

Question 48. (单选)
以下各选项企图说明一种新的类型名，其中正确的是 (2)

1. typedef v1 int;
2. typedef int v3;
3. typedef v4: int;
4. typedef v2=int;

Question 49. (单选)
char x=3,y=6,z;
z=x^y<<2;
则z的二进制值是 (2)

1. 10100
2. 11011
3. 11100
4. 11000

Question 50. (单选)
若有说明：int i, j=2，*p=&i;，则能完成i=j赋值功能的语句是 (2)

1. i=*p;
2. *p=*&j;
3. i=&j;
4. i=**p;

Question 51. (问答)
给定一个整型变量a，写两段代码，第一个设置a的bit 3，第二个清除a的bit 3。在以上两
个操作中，要保持其它

位不变。

a|=0x4;

int b=a&0x7;
a>>=4;
a=(a<<4)|b;

Question 52. (问答)
有双向循环链表结点定义为：
struct node
{ int data;
struct node *front,*next;
};
有两个双向循环链表A，B，知道其头指针为：pHeadA,pHeadB，请写一函数将两链表中dat
a值相同的结点删除

struct node
{ int data;
struct node *front,*next;
};
node* del(node *pHead){
if(pHead==pHead->next){
free(pHead);
return NULL;
}
node *p=pHead;
pHead->next->front=pHead->front;
pHead->front 


是申请intern的笔试题，刚刚做完笔试题回来... 

1.下面几个平台用什么传递参数 
IA32,IA64,ARM,EM64T 
2.RISC 机器的特性 
3.几种接口类型:FSB,PCI，ISA 
和33M,800M,8M配对...(记不清了，反正有compatiable这个词) 
4.算cache-hit ratio 
5.rtp/rtsp/rtcp的指什么？什么场合应用？ 
6.cpu取指时，指令不再cache中，也不再内存中，而在辅存中，问这整个过程中硬件和 
软件的行为是什么？ 
7.折半查找的复杂度，证明 
8.sizeof()和strlen()的使用. 
9.顺序存储结构的优点，散列法的思想是什么？ 
10.并发进程相关知识 
11.下面的程序能编译通过么？ 
#include <stdio.h> 
int main(void) 
{ 
unsigned long long a=0xAAAAAAAABBBBBBBB; 
unsigned int b=0xCCCCCCCC; 
printf("you have %d RMA ,right?\n"; 
printf("valuea :%lx,valueb :%lx\n",a,b); 
} 
12.汉罗塔算法，不能递归... 

13.插入一个usb设备描述驱动自动装载的过程。 
-- 

发信人: miser (大灰狼), 信区: job 
标 题: 去神州数码笔试随笔 
发信站: 饮水思源 (2004年12月22曰21:59:10 星期三) 


交大的ss，去神州数码可以乘855，终点站，再向西走100米左右吧，可以看到神州数码的 
大牌子了。 
我考的是软件研发，卷子分java和c/c++两部分，如果你只会其中的一部分，我建议你就不 
用去了，又累，还可能被bs。我只会做c/c++部分，考了些c++的一些基本概念，数据结构 
的基本题（都是选择题）。数据库考了SQL语言中的一些如select，update，join等。大题 
目主要考了三道：（1）为什么在编译时其它文件中的定义的函数要用extern c说明 
（2）看程序（求输入数的均值） 
（3）string类的构造函数，自引用函数，析构函数，重载赋值函数（实际 
上和类默认生成的几个函数差不多） 
题目还是比较简单的，祝好运。 

发信人: GlobalRainy (Dirichlet, Johann Peter Gustav Lejeune), 信区: C 
标 题: SAP试题（不完整），作为周末讨论话题吧 
发信站: 饮水思源 (2004年03月19曰23:30:13 星期五), 站内信件 

1.Below is usual way we find one element in an array: 

const int *find1(const int* array, int n, int x) 
{ 
const int* p = array; 
for(int i = 0; i < n; i++) 
{ 
if(*p == x) 
{ 
return p; 
} 
++p; 
} 
return 0; 
} 

In this case we have to bear the knowledge of value type "int", the size of 
array, even the existence of an array. Would you re-write it using template 
to eliminate all these dependencies? 

2. Assume you have a class like 

class erp 
{ 
HR* m_hr; 
FI* m_fi; 
public: 
erp() 
{ 
m_hr = new HR(); 
m_fi = new FI(); 
} 
~erp() 
{ 
} 
}; 

if "new FI()" failed in the constructor, how can you detect this problem and 
release the properly allocated member pointer m_hr? 

3. Check the class and variable definition below: 

#include <iostream> 
#include <complex> 
using namespace std; 
class Base 
{ 
public: 
Base() { cout<<"Base-ctor"<<endl; } 
~Base() { cout<<"Base-dtor"<<endl; } 
virtual void f(int) { cout<<"Base::f(int)"<<endl; } 
virtual void f(double) {cout<<"Base::f(double)"<<endl; } 
virtual void g(int i = 10) {cout<<"Base::g()"<<i<<endl; } 
}; 

class Derived: public Base 
{ 
public: 
Derived() { cout<<"Derived-ctor"<<endl; } 
~Derived() { cout<<"Derived-dtor"<<endl; } 
void f(complex<double> { cout<<"Derived::f(complex)"<<endl; } 
virtual void g(int i = 20) {cout<<"Derived::g()"<<i<<endl; } 
}; 

Base b; 
Derived d; 

Base* pb = new Derived; 
Select the correct one from the four choices: 
Cout<<sizeof(Base)<<endl; 
A. 4 B.32 C.20 D.Platform-dependent 
Cout<<sizeof(Base)<<endl; 
A. 4 B.8 C.36 D.Platform-dependent 
pb->f(1.0); 
A.Derived::f(complex) B.Base::f(double) 
pb->g(); 
A.Base::g() 10 B.Base::g() 20 
C.Derived::g() 10 D.Derived::g() 20 

4.Implement the simplest singleton pattern(initialize if necessary). 

5.Name three sort algorithms you are familiar with. Write out the correct 
order by the average time complexity. 

6.Write code to sort a duplex direction linklist. The node T has overridden 
the comparision operators. 

发信人: xiaokan (笑看风云), 信区: C 
标 题: Re: SAP试题（不完整），作为周末讨论话题吧 
发信站: 饮水思源 (2004年03月20曰11:51:48 星期六), 站内信件 

1、Use template function 
template <typename T, typename InputIter = const T*> 
InputIter find_imp (InputIter begin, InputIter end, const T& ct) 
{ 
InputIter iter = begin; 
while ((iter != end) && 
((*iter) != ct)) { iter++; } 
return iter; 
} 

2、2 methods can take. One is to use try catch idiom, the other 
is to use intelligent pointers, such as auto_ptr. I prefer 
auto_ptr. 

3、Have been discussed a lot. 

4、See GoF's <design pattern>. Another recommendable different 
implemented example, ACE_Singleton, u can look up ACE library 

5、Have been discussed a lot. 

6、Have been discussed a lot. 


【 在 GlobalRainy (Dirichlet, Johann Peter Gustav Lejeune) 的大作中提到: 】 
: 1.Below is usual way we find one element in an array: 
: const int *find1(const int* array, int n, int x) 
: { 
: const int* p = array; 
: for(int i = 0; i < n; i++) 
: { 
: if(*p == x) 
: { 
: return p; 
: } 
: .................（以下省略） 

发信人: cokio (慢慢长大), 信区: job 
标 题: synopsys CS笔试题 
发信站: 饮水思源 (2004年12月07曰20:55:54 星期二), 站内信件 

今天Synopsys笔试内容大致如下，有一题想不起来了，大家帮忙回忆： 
1。说出指针和引用的区别。 
2。说下深度优先遍历和广度优先遍历区别。 
3。C++语法错误判断。这题很有趣，我记下了，贴出来大家看看：） 

class base{ 
private: int i; 
public: base(int x){i=x;} 
}; 
class derived: public base{ 
private: int i; 
public: derived(int x, int y) {i=x;} 
void printTotal() {int total = i+base::i;} 
}; 
4。实现strcpy函数。 
5。编程判断字符串是否对称。如：ABCCBA对称，ABCDBA就不对称。 
6。1，2，5，10四个基数任意次数组合相加得到一个数N，求所有可能组合。 
7。二叉树前序遍历得到表达式。 
8。题目意思不是很明白，可能是推出产生式的意思吧。 
9。 
10。循环链表的节点对换和删除。 
11。hash表实现。 

发信人: dtbird (清谈), 信区: CPlusPlus 
标 题: 两个笔试题 
发信站: BBS 水木清华站 (Wed Oct 27 15:17:02 2004), 站内 

1. 定义一个类X使下面的语句可以通过编译 
X f() {return true;} 

2. 打印出1到1000的整数，不能使用流程控制语句（for，while，goto等）， 
也不能使用递归。 

发信人: withcloud (准备工作中), 信区: CPlusPlus 
标 题: 总结一下今年碰到的笔试和面试程序题目 
发信站: 南京大学小百合站 (Wed Nov 17 19:31:18 2004) 


我今年总共(到目前为止)参加了三场笔试,四次技术面试.我现在把在这过程中碰到的有关 
程序设计部分的题目大致总结一下,希望对在找和要找的 XDJMs 有所帮助. 

1.笔试: 
1)写一个内存拷贝函数,不用任何库函数.就是前些时候本版讨论的那个问题. 
2)将一个单链表逆序.(这个问题是个常规的数据结构问题.不过不小心时会损失效率) 
3)客房预定的问题.根据客户报的人数,客房等级来从预备的客房中选择出所有符合要求的 
客房号.客户没有要求等级时,只考虑人数因素就可以了.要考虑有些客房已经预定的情况. 
(写代码是要考虑好彼此的效率) 
4)对于一个无序序列进行二分查找 
5)将一个数字字符串转换为数字."1234" -->1234 
6)在文件(调用库函数创建的,不用考虑数据库的方式)中读入信息(包括职工号,职工产量) 
.根据输入的信息(包括职工号,职工产量)..检测是否有相同的职工号记录,如有,则增加其 
产量.如没有,则创建新的记录.最后的记录排序的依据是职工产量(降序),如果产量相同,则 
按职工号(升序). (具体的题目记不太清了,这个题目有点长.哪位也去笔试了.请修正一下 
子) 
. 
2.面试 
同一个地方.面试官的要求是一分钟给出求相似度的算法.)(幸好听老师讲过中文分词,要不 
然当场就挂了) 
2)写出二分查找的代码. 
3)将上述代码通用化.(在 C 的规范内.就是我前面所的那个问题) 
4)写出在母串中查找子串出现次数的代码.(不顾及效率时好说.当时一不留神把 KMP 说了 
出来,结果又让我描述整个过程.汗..只好从头又学了.不过没有冷场,边学边说.hoho) 
5)如何看待在函数中定义很多静态变量. 
6)写出quick_sort 
7)写出查找从一个集合中输出所有子集合的算法. 
8)有关于各种类型指针.各种数据类型的 sizeof 运算结果( 在 C 中) 

其他就跟程序写作关系不大了. 

发信人: griefjane (grief), 信区: C 
标 题: 夏尔笔试题 
发信站: 饮水思源 (2004年01月02曰18:31:53 星期五), 站内信件 

实现任意长度的整数相加功能。 
估计有多种方法可以实现，讨论一下吧，希望最后得到简洁、优雅的一个版本。 

发信人: lippman (lippman), 信区: C 
标 题: 10/28曰微创笔试题目公布！！！没有答案(ZZ) 
发信站: 饮水思源 (2004年10月29曰15:29:23 星期五), 站内信件 

下午3点左右接到一个电话，小姐称是微创软件公司，问我有没有空晚上6点去他们公司 
笔试，应聘软件工程师，我问了一下情况，就答应了，当作一次经历也不错的。于是乎 
，我骑着小电驴花了50分钟找到了延安东路222号外滩中心，大楼很PP，一幢非常高档的 
写字楼，进进出出都是白领，工作环境很不错，我看着自己穿的休闲服，还真不好意思 
进去，这楼还挺麻烦，要签名领牌子进去。终于上了21楼，看到了公司的门面，很气派 
，我喜欢的黄色系装潢，舒服的。不过接待的不是公司员工，是两个身穿制服的保安， 
递给我一份考卷，将我领进一间会议室，对我说90分钟后交卷。然后就走出去了。会议 
室里面有很多人，除了我和另外一个女生，其余都是男生，都在奋笔疾书！牛！我看了 
题目只有发傻~~~根本不是和我的岗位。唯一做的事情就是把题目摘录下来作为经验！不 
过我还是作了一部分的。嘻嘻 
http://cnwyy.yculblog.com/ 
下面把题目贴出来，没有答案，大家可以讨论：） 
Part A 
1）实现string toHex(int)把一个十进制转换成十六进制。（完全用算法实现） 
2）实现一个计算大位数（如100位以上）相乘结果的函数string 
multiply(sting,string)。（请完全用算法实现） 
3）一个数据库中有两个表，一张表为Customer，含字段ID,Name，一张表为Order，含字 
段ID,CustomerID（连向Customer中ID的外键）,Revenue；写出求每个Customer的Revenu 
e总和的SQL语句。 
4）一个学生成绩登记系统，其中学生和课程均是可添加的，请设计一个库表结构实现， 
尽量保证系统使用中库表结构不再改变。 
5）请简要描述出你最熟悉的技术架构，包括架构中的各种中间件。（建议用图的形式） 

Part B 
1）请简述Critical Section和Mutex的不同点。 
2）请描述下面函数声明中各个const的作用： const char* Test() const 
3）举3个以上ASP.Net与ASP相比的进步。 
4）ASP.Net中user control和custom control的区别。 
5）用一个C语言用来删除单链表的头元素的函数，请找出其中的问题并加以纠正。 
void RemoveHead(node* head) 
{ 
free(head) 
head=head->next 
} 


6）试编写函数判断计算机的字节存储顺序是开序(little endian)还是降序(bigendian) 

7）给定如下SQL数据库：Test(num INT(4)) 请用一条SQL语句返回num的最小值，但不许 
使用统计功能，如MIN，MAX等。 
8）输出下面程序结果。 

#include <iostream.h> 
using namespace std; 
class A 
{ 
public:virtual void print(void) 
{ 
cout<<"A::print()"<<endl; 
} 
}; 
class B:public A 
{ 
public:virtual void print(void) 
{ 
cout<<"B::print()"<<endl; 
} 
}; 
class C:public A 
{ 
public:void print(void) 
{ 
cout<<"C::print()"<<endl; 
} 
}; 
void print(A a) 
{ 
a.print(); 
} 
void main(void) 
{ 
A a, *pa,*pb,*pc; 
B b; 
C c; 

pa=&a; 
pb=&b; 
pc=&c; 

a.print(); 
b.print(); 
c.print(); 

pa->print(); 
pb->print(); 
pc->print(); 

print(a); 
print(b); 
print(c); 
} 

1. 以下三条输出语句分别输出什么？[C易] 
char str1[] = "abc"; 
char str2[] = "abc"; 
const char str3[] = "abc"; 
const char str4[] = "abc"; 
const char* str5 = "abc"; 
const char* str6 = "abc"; 
cout << boolalpha << ( str1==str2 ) << endl; // 输出什么？ 
cout << boolalpha << ( str3==str4 ) << endl; // 输出什么？ 
cout << boolalpha << ( str5==str6 ) << endl; // 输出什么？ 

13. 非C++内建型别 A 和 B，在哪几种情况下B能隐式转化为A？[C++中等] 
答： 
a. class B : public A { ……} // B公有继承自A，可以是间接继承的 
b. class B { operator A( ); } // B实现了隐式转化为A的转化 
c. class A { A( const B& ); } // A实现了non-explicit的参数为B（可以有其他带默认 
值的参数）构造函数 
d. A& operator= ( const A& ); // 赋值操作，虽不是正宗的隐式类型转换，但也可以勉 
强算一个 

12. 以下代码中的两个sizeof用法有问题吗？[C易] 
void UpperCase( char str[] ) // 将 str 中的小写字母转换成大写字母 
{ 
for( size_t i=0; i<sizeof(str)/sizeof(str[0]); ++i ) 
if( 'a'<=str && str<='z' ) 
str -= ('a'-'A' ); 
} 
char str[] = "aBcDe"; 
cout << "str字符长度为: " << sizeof(str)/sizeof(str[0]) << endl; 
UpperCase( str ); 
cout << str << endl; 

7. 以下代码有什么问题？[C难] 
void char2Hex( char c ) // 将字符以16进制表示 
{ 
char ch = c/0x10 + '0'; if( ch > '9' ) ch += ('A'-'9'-1); 
char cl = c%0x10 + '0'; if( cl > '9' ) cl += ('A'-'9'-1); 
cout << ch << cl << ' '; 
} 
char str[] = "I love 中国"; 
for( size_t i=0; i<strlen(str); ++i ) 
char2Hex( str ); 
cout << endl; 

4. 以下代码有什么问题？[C++易] 
struct Test 
{ 
Test( int ) {} 
Test() {} 
void fun() {} 
}; 
void main( void ) 
{ 
Test a(1); 
a.fun(); 
Test b(); 
b.fun(); 
} 

5. 以下代码有什么问题？[C++易] 
cout << (true?1:"1" << endl; 

8. 以下代码能够编译通过吗，为什么？[C++易] 
unsigned int const size1 = 2; 
char str1[ size1 ]; 
unsigned int temp = 0; 
cin >> temp; 
unsigned int const size2 = temp; 
char str2[ size2 ]; 

9. 以下代码中的输出语句输出0吗，为什么？[C++易] 
struct CLS 
{ 
int m_i; 
CLS( int i ) : m_i(i) {} 
CLS() 
{ 
CLS(0); 
} 
}; 
CLS obj; 
cout << obj.m_i << endl; 

10. C++中的空类，默认产生哪些类成员函数？[C++易] 
答： 
class Empty 
{ 
public: 
Empty(); // 缺省构造函数 
Empty( const Empty& ); // 拷贝构造函数 
~Empty(); // 析构函数 
Empty& operator=( const Empty& ); // 赋值运算符 
Empty* operator&(); // 取址运算符 
const Empty* operator&() const; // 取址运算符 const 
}; 

3. 以下两条输出语句分别输出什么？[C++难] 
float a = 1.0f; 
cout << (int)a << endl; 
cout << (int&a << endl; 
cout << boolalpha << ( (int)a == (int&a ) << endl; // 输出什么？ 
float b = 0.0f; 
cout << (int)b << endl; 
cout << (int&b << endl; 
cout << boolalpha << ( (int)b == (int&b ) << endl; // 输出什么？ 

2. 以下反向遍历array数组的方法有什么错误？[STL易] 
vector array; 
array.push_back( 1 ); 
array.push_back( 2 ); 
array.push_back( 3 ); 
for( vector::size_type i=array.size()-1; i>=0; --i ) // 反向遍历array数组 
{ 
cout << array << endl; 
} 

6. 以下代码有什么问题？[STL易] 
typedef vector IntArray; 
IntArray array; 
array.push_back( 1 ); 
array.push_back( 2 ); 
array.push_back( 2 ); 
array.push_back( 3 ); 
// 删除array数组中所有的2 
for( IntArray::iterator itor=array.begin(); itor!=array.end(); ++itor ) 
{ 
if( 2 == *itor ) array.erase( itor ); 
} 

11. 写一个函数，完成内存之间的拷贝。[考虑问题是否全面] 
答： 
void* mymemcpy( void *dest, const void *src, size_t count ) 
{ 
char* pdest = static_cast<char*>( dest ); 
const char* psrc = static_cast<const char*>( src ); 
if( pdest>psrc && pdest<psrc+cout ) 能考虑到这种情况就行了 
{ 
for( size_t i=count-1; i!=-1; --i ) 
pdest = psrc; 
} 
else 
{ 
for( size_t i=0; i<count; ++i ) 
pdest = psrc; 
} 
return dest; 
} 
int main( void ) 
{ 
char str[] = "0123456789"; 
mymemcpy( str+1, str+0, 9 ); 
cout << str << endl; 

system( "Pause" ); 
return 0; 



-------------------------------------------------------------------------------- 
发信人: stroller (混口饭吃不容易), 信区: Job 
标 题: 威盛笔试 
发信站: 曰月光华 (2004年11月06曰11:30:50 星期六), 站内信件 

calloc 和 malloc的区别 

4条线段连3*3的点 

3*3*3，2*2*2， 1*1*1的薄壁桶，每个桶里面只能倒一次水， 
怎么称出13个单位的水 

代码优化，主要思想就是把不变量的计算提到循环外 

x86种AND，OR，XOR有些什么用途 

#define导致计算结果诡异的一个题 

10个房间，每个房间里面有随机的金币，每个房间只能进一次， 
你获得最多金币的概率多大。 
一种策略是，先走4个房间，不拿，但是记下4个房间的金币最大值max， 
往后6个房间遇到比max大的就拿，如果没有遇到，那最后一个房间的金币。 
编程计算拿到最多金币的概率，给出文字说明； 
发信人: godiex (不知道), 信区: job 
标 题: Re: 威盛S3软件工程师3笔试 
发信站: 饮水思源 (2004年11月06曰14:01:25 星期六) 

补充一下全部的试题。 

1。看程序写运行结果 
m=5; 
If(m++>5) printf(“%d\n”, m); 
Else printf(“%d\n”, --m); 

2．简述 AND, XOR, OR的功能 
3．calloc和malloc的区别 
4．3x3九点，四条连线 
5．1x1x1, 2x2x2, 3x3x3的三个容器。每个容器只能灌一次，如何量出13ml的水。 
6．求sizeof(p) 
char *p=”hello!” 
char p[]=”hello!” 
void *p=malloc(100) 
void Func(char p[100]) 
7．一段很长的程序，要求写出程序的意图。基本上是把字节指针pData指向的一块内存数 
据复制到双字指针pwdData指向的内存区域。每次复制4字节，不足处补零。 
8． 
#define SQR(x) x*x 
int a=10; int k=2; int m=1; 
a/=SQR(k+m)/SQR(k+m); 
a=? 
9．一段程序找效率不高的地方。也是复制内存区域。 
10．10个房间里放着随机数量的金币。每个房间只能进入一次，并只能在一个房间中拿金 
币。一个人采取如下策略：前四个房间只看不拿。随后的房间只要看到比前四个房间都多 
的金币数，就拿。否则就拿最后一个房间的金币。 
a) 编程计算这种策略拿到最多金币的概率。 
b) 证明这是不是最优策略。 


补充一下全部的试题。 

1。看程序写运行结果 
m=5; 
If(m++>5) printf(“%d\n”, m); 
Else printf(“%d\n”, --m); 

打印结果 : 5 
程序会进入else所在的分支 

2．简述 AND, XOR, OR的功能 
跳过 

3．calloc和malloc的区别 
简单一点的说：1.参数不同，2.calloc还会初始化分配到的内存 

4．3x3九点，四条连线 
自己琢磨吧，有三条线都是从某一个角上的点开始的。 

5．1x1x1, 2x2x2, 3x3x3的三个容器。每个容器只能灌一次，如何量出13ml的水。 
方法一：三个容器套在一起，容器口都朝上，底部靠在一起，慢慢倒水，先倒满大容器 
(9-4)*2；水漫过2*2*2容器，直到快与1*1*1容器口齐3*1，10+3; 
方法二：3*3*3容器与2*2*2容器口朝上，口平齐，小容器在大容器内；往3*3*3容器倒 
水，3*3*3-2*2*2=19; 1*1*1容器与2*2*2容器口朝上，口平齐,小容器在大容器内；从 
3*3*3容器往2*2*2倒水,3*3*3容器剩12(19-(2*2*2-1*1*1)), 最后1*1*1容器满， 
12+1=13; 

6．求sizeof(p) 
1.char *p=”hello!” 
2.char p[]=”hello!” 
3.void *p=malloc(100); 
4.void Func(char p[100]){ 
sizeof(p)? 
} 

解答： 
1. sizeof(p) = 4; 怎么说也只是个指针而已 
2. sizeof(p) = 7; 最后要加一个'{post.content}' 
3. sizeof(p) = 4; 怎么说也只是个指针而已 
4. sizeof(p) = 4; 没有试过，感觉林锐的书上这样写的 

7．一段很长的程序，要求写出程序的意图。基本上是把字节指针pData指向的一块内存 
数据复制到双字指针pwdData指向的内存区域。每次复制4字节，不足处补零。 

8． 
#define SQR(x) x*x 
int a=10; int k=2; int m=1; 
a/=SQR(k+m)/SQR(k+m); 
a=? 
结果a = 1; 

解开后 a/=k+m*k+m/k+m*k+m 
a = 10 / (2+1*2+1/2+1*2+1) 
= 10 / 7.5 
整数取整，故a =1 ; 

9．一段程序找效率不高的地方。也是复制内存区域。 
解答L： 
1、计算首地址不必每次都用乘法来算， 
2、每行要复制的宽度是固定的，不必每个循环都算 

1、变乘为加，不必每次都计算的，只计算一次就可以了。 
2、特殊的图形内存块，如位图，可以考虑整块拷贝，不必分行拷贝。 

10．10个房间里放着随机数量的金币。每个房间只能进入一次，并只能在一个房间中拿 
金币。一个人采取如下策略：前四个房间只看不拿。随后的房间只要看到比前四个房间 
都多的金币数，就拿。否则就拿最后一个房间的金币。 

a) 编程计算这种策略拿到最多金币的概率。 
b) 证明这是不是最优策略。 

考官提示说不要用概率论的方法，我想无非是设一个长度为10的数组，编号1至10的数字 
放入其中，考虑10的位置。 
其他的自己考虑吧。 

发信人: realchichi (人淡如菊◎相交如水◎晶晶亮), 信区: Job_IT 
标 题: 威盛的Software test Engineer笔试题(转载) 
发信站: 武汉白云黄鹤站 (2004年11月18曰12:28:32 星期四), 站内信件 

【 以下文字转载自 Job 讨论区 】 
【 原文由 jjli 所发表 】 


1.What is OSI Model?Which layer is responsible for the information reliable 

delivery? 
2.List the differences of TCP and UDP 
3.Please list the differences between convertional C language and 
object-oriented language(OOL),sau C++? 
4.Please list the three major features and meanings of C++ 
5.Please list the program areas of the run time environment and give a brief 

explanation of the function of each area 
6.Write a piece of code(or macro)to convert the decimal number to hex format 

7.In a real time operating based embedded system,2 tasks will access the 
RS-232C port.Design a mutual exclusive mechanism for tasks sending command 

(Pseudo code is okay) 
8.A multi-task application is running on top of a real-time operating system, 

how many possbile states can a task have?Please draw a state transition 
diagram to explain. How the tasks communicate to each? 

发信人: realchichi (人淡如菊◎相交如水◎晶晶亮), 信区: Job_IT 
标 题: 威盛的Software tools Engineer笔试题(转载) 
发信站: 武汉白云黄鹤站 (2004年11月18曰12:28:36 星期四), 站内信件 

【 以下文字转载自 Job 讨论区 】 
【 原文由 jjli 所发表 】 


Software programming test on C++: 
1.How good do you see yours programming skills?Please circle your answers 
C: Fair/Good/Excellent 
C++: Fair/Good/Excellent 
2.Please estimate your programming experince: 
How many lines of code are your biggest C Program ever written excluding the 

standard linked library? 
How many lines of code are your biggest C++ program ever written excluding t 
he standard linked library? 
3.Please explain the following terms 
Data Encapsulation 
Inheritance 
Polymorphism 
4.What is a virtual base class?How do you declare such a class?How would you u 
se it in a design? 
5.What is a template or container class?How do you declare such a class? 
6.Which are the access control levels for C++ language? 
7.What is RTTI?How do you achieve RTTI in your design? 
8.What are the major differences between static and non-static member function 
s? 
9.How do you call a regular member function from a static member function? 
Please use psendo-code to provide your answer 
10.How do you declare/define a type of pointer to a class member function? 
Please use psendo-code to provide your answer 
11.Please explain the following tyoes: 
Here is a short lise of combinations and their meanings: 
1.Reference-Can change the referenced object 
2.Const-Reference 
3.Const-Pointer- 
4.Pointer-Const- 
5.Const-Pointer-Const- 
CFoo Instance 

CFoo &ReferenceToInstance=Instance; //1 
const CFoo &ConstReferenceToInstance=Instance; //2 
const CFoo *pConstPointer=&Instance; //3 
CFoo *const pPointerConst=&Instance; //4 
const CF00 *const pPointerConst=&Instance; //5 
12.What are top-down and bottom-up approach?How do you usually use them? 
13.Please use pseudo-code to design a set of stack operations with template 
14.Please use pseudo-code to design a set of double linked list operations wit 
h template 

Optional Questionsfor extra credits) 
15.Please write a unix makefile for Question13 
16.Please explain these common sections:text,data,bss 

发信人: guaibaogou (乖狗狗), 信区: job 
标 题: 微软笔试试题 
发信站: 雁塔晨钟 (Sat Oct 16 20:58:48 2004), 本站(bbs.xidian.edu.cn) 


今天笔试过后，11月还有一次笔试，那次的规模应该更大吧，星期五的微软报告说会有80% 
到90%的人会给予面 
试机会。所以我想把这次的试题写出来，可能对大家有一点帮助吧，当然，我大部分不 
记得了，因此希望参加 
了的同学可以一起来写。 

Part I.选择题70分钟) 
1.求函数返回值，输入x=9999; 
int func(x) 
{ 
int countx = 0; 
while(x) 
{ 
countx ++; 
x = x&(x-1); 
} 
return countx; 
} 

2.为什么返回局部变量的引用不好？ 
a,b,c,d不记得了，大概和内存，返回值等等有关。 

3.Stack R,from the top to bottom:{2,3,4,5,6},逐个取出放入Queue Q ，再从Q中逐 
个取出放入R中，问现在 

从上到下R中元素的排列？ 

4.在你自己定义的类中有什么是CLASSVIEW不会为你做的： 
(a) 析构器。 (b)拷贝构造函数 (c)构造函数 (不记得有没有这一项了) 
(d)（不记得了） 

5.写出程序的结果：___________ __________________ 
int funa(int *a) 
{ 
a[0] ++; 
} 

int funb(int b[]) 
{ 
b[1] += 5; 
} 

main() 
{ 
int a[5] = {2,3,4,5,6}; 
int b[5] = {2,3,4,5,6}; 
int *p; 
p = &a[0]; 
(*p)++; 
funb(p); 
for(int i = 0; i <5; i++) 
printf("%d,",a); 
p = &b[1]; 
funa(p);//(啊，现在写的时候才发现做错了，传的是b[1]的地址；只记得传地址给 
//指针了，考的时候以为 
//传的是b.主要是被第一次调用funb弄晕了～～呵呵) 
funb(p); 
for(i = 0; i < 5; i++) 
printf("%d,",b); 
} 

18.一道智力题或者说逻辑题，好多英文单词不认识，都没弄懂意思，所以也没做。有记 
得的写出来吧，最好翻译过来，我还打算做一下呢。虽然很有可能做不出。 

有一道好像是说编译器可以修改type error，的好处或不好。 
有一道是什么regular language和 text free language比较？（有没有人给我解释一下 
这两个是什么东东？） 
有一道是在编写代码是查找错误好还是用testing找好？ 

其他的都不记得了。 

Part II 编程（40分钟） 
1. 把一段汇编语言的程序写成一个C语言函数，不能有go to 和指针。因为那段汇编我 
没看懂，所以也记不得了。那个汇编是我们微原学的汇编，是另一个，不过它有解释关 
于它的语句命令。 

2.实现以下程序，以方便binary search. 
.要有处理错误语句 
.队列的分配的大小是固定的MAX_LEN,由第二个参数输入 
.不能复制队列 
insert (int *arr, //队列 
size_l len, // 队列大小 
size_l count, //队列元素的数目 
int varl //要处理的数据 
)返回插入数据的索引 
remove(int *arr,size_l len,size_l count,int varl)返回删除元素的索引 
search(int *arr,size_l len,size_l count,int varl)返回搜索道元素的索引 

Part III Design（20分钟） 
1.如果给你分配一个任务，做一个新版本的IE浏览器的一个功能，可能是搜索功能、用 
户界面，你将如何design,development,test 
2.不记得 

Part IV Testing（30分钟） 
1。给你一个函数，你如何测试它，函数是strcmp(char* str1,char* str2) 
2.给你一个DVD Play，你如何测试它？如果测有只有一定的时间，你首先测试哪一步？ 
为什么？ 

Part V. Writing（20分钟） 
在过去的这些年，你遇到了哪一个最大的困难，你是如何解决它的？你是单独做的还是 
和别人一起做的决定？为什么做这个决定？现在the output如何？ 

其他的大家来补充吧。 
总的感觉是对C\C++的编程内存、安全要求比较高，而不是仅仅编写一个程序，要求你知 
道为什么要这样编写，这样编写了对内存有什么影响，是否安全等等。都是很基础的东 
西，但大家平时也会不太注意。 

前天微软亚洲工程院全国第一轮笔试，西安考区的，安排在西电，人挺多，不过应 
该不到一千吧。 

15页考卷，分为AB卷，要求是三个小时考完，全部用铅笔答题。中途不允许去WC， 
PS：全英文考题。总体来说还是很基础的，算法与数据结构的比较多，还有一些推 
理题目，不过这次的不难（条件环节不够多）。当然少不了编程的题目不过这些题 
目主要是考你对程序的理解与习惯。 


都过了一夜睡了一觉,题目不记得多少了,就记得几个自己印象深刻点儿,遗憾才深 
刻.... 

I Basic 
这个部分有近二十道多项选择题和若干填空题,内容繁多零散,大部分是关于数据结 
构和c/c++语言,还有关于软件工程,测试方法,无状态网络的一些题目;填空题是读 
程序填结果,当然最后还有一道比较复杂的逻辑题目. 

1。regular expression不能描述的是? 
a)两个连续偶数 
b)两个连续奇数 
。。。。 

2 


int s(int v) 
{ 
int count=0; 
int x=v; 
while (x) 
{ 
count++; 
x=x&(x-1) 
} 
return count; 
} 

s(9999)=? 


3,关于堆排序的东西，插入新的元素以后的结果 

4,关于C语言中，.h文件和.c文件之间的关系 

5,如果数据扩大两倍，是向左，还是向右移动几位的问题 

6,对二叉排序数，以什么输出（前序，中序，还是后续）输出，是排列 

7,一个顺序为 1，2，3，4，5，6 的栈，依次进入一个队列，然后再进栈， 顺序 
是什么？ 

8 关于数组指针的的题目 

9 regular language 和context language之间的关系是什么. 
a)regular language more powerful than context free language 
(后面两个个选项记不清楚了,反正大意就是比较两个谁好.最后一个选项是两者不 
能进行这样的比较) 

10 在编写代码是查找错误好还是用testing找好？ 

11 好像是说编译器可以修改type error的好处或不好。 


逻辑推理部分 

一个线性车库,5排5辆车,一车最多坐两人. 
6个人.Tom,Jack, Gawen, Laurie, Mark, Paul. 

.Mark独享车且紧跟空车后 
.Tom不跟Gawen或Paul坐一辆车. 
.Laurie跟别人共享车. 
.Gawen在第三排或第四排. 

一共5道题目,显然通过4个条件不能确定车序.有的题目是问存在的可能,有的题目 
是附加条件后问车序. 


程序设计部分. 



1 Translate MIPS assembly code into a function in C/C++ 
* your code should be concise 
* no any GOTOs/pointers 

MIPS code: 


func: 
li $v0,0 
li $t0,0 
l1: 
add $t1,$a0,$a0 
lb $t2,0($t1) 
beq $t2,$zero,l3 
bne $t2,$a1,l2 
add $v0,$v0,1 
l2: 
add $t0,$t0,1 
j l1 
l3: 
jr $ra 


(caller register: $t0~$t9,$a0~$a3,$v0~$v1; callee $s0~$s7,$ra) 
然后列出了指令表,li是赋值,lb是将字段后第一个寄存器内容个字节的内容复制到 
第二个寄存器,beq是等值转移ben是不等值转移,j是无条件转移,jr转移至寄存器标 
示的内容. 

实现数组的插入,查找,删除操作. 

arr为指向数组的指针 
len为数组长度. 
count表示数组元素数目. 
出错返回-1 

int insert(int* arr, 
size_t len, 
size_t count, 
int val) 
返回插入的数组索引. 
插入后要求对数组排序. 
出错处理 

int search(int* arr, 
size_t len, 
size_t count, 

int val) 
要求返回所找到的元素 
出错处理 

int remove(int* arr, 
size_t len, 
size_t count, 
int val) 
要求返回删除的元素值 
出错处理 



测试部分. 

1.你被分配到Internet Explorer研发部,（从核心到界面什么都可以）.你如何设 
计,开发和测试它? 

2.给你个DVD,你应当如何测试它,如果你的时间极其有限,你会测试什么?为什么? 

3.给你一个字符比较函数strCmp(const char* string1, const char* string2)以 
及其返回值表明的意义,(>0, ==0, <0),设计测试case 

4.一段字符串复制程序,指出其存在的错误和潜在缺陷. 


最后是个论述题目,只有这个题目是要用英文作答的，上面的都可以用Chinese 

问的是你在过去一年里做出过什么样的重要决定,你为什么做出这样的决定,这个决 
定对你的影响,你达到你作决定时期望的目标了没.有什么收获. 

发信人: doggy (老三～差人※年复一年), 信区: Career_MS 
标 题: MS考经 
发信站: BBS 水木清华站 (Sat Nov 13 17:40:11 2004), 站内 

刚考完回来，趁热乎回忆一下题目吧。 
A组题 
1 选择填空题 
居然是多选，ft。似乎十几道，开始考基本概念。比如 
为什么要使用函数（结构化，可重用之类的） 
后来看程序输出或者找错，有一道比较难，我比较犹豫： 
struct S { 
int i; 
int * p; 
}; 
void main() 
{ 
S s; 
int * p = &s.i; 
p[0] = 4; 
p[1] = 3; 
s.p = p; 
s.p[1] = 1; 
s.p[0] = 2; 
} 
问程序会在哪一行死掉。 

还有一题考静态成员变量的，不过我看怎么着结果都一样 
int CalcMean(int i) 
{ static int s, c; 
s+=i; c++; 
return s/c; 
} 
求CalcMeas( CalcMeas(3) )＝？ 
再嵌套几次都一样。 

还有一个 
int calc(int a, int b) 
{ 
if(a >= b) 
return (a==b)?a:b; 
else 
return a+b+calc(++a, --b); 
} 
问calc(1, 5)等于？ 

还有那个IQ题：三个盒子有一个有宝石，先选一个， 
主持人打开一个问改不改的。常上iqdoor版肯定不会有问题 
还有一个 
abcdef*2=cdefab 
cdefab*2=efabcd 
每个字母代表一个数字 
abcdef＝？ 

2 编程题 
2。1 写一个CircularQueue() 
2。2 写一个Merge函数。把两个排序的链表合并。 
难点是两个链表一个从小到大排，另一个反向。 
我是先把反向的转过来再合并的。 

3 设计（可用中文） 
1 设计一个密码对话框。问如何设计，有什么规范，如何测试等 
2 Web搜索引擎测试。 

4 忘了，可用中文 

5 要用英文做答 
5。1 你有什么新奇的想法，最好是软件方面 
5。2 让一个员工开发一个功能，但是他不重视。如何搞定。 
英语是：我猜是这个意思吧。 
How would you convince a developer to add a feature 
that the developer does not view as importart? 

记性好差 

发信人: rebirth (肥得像猪一样的猫), 信区: C 
标 题: 微软笔试题目(ZZ) 
发信站: 饮水思源 (2004年01月01曰13:49:05 星期四), 站内信件 

MSRA Interview Written Exam（December 2003，Time：2.5 Hours） 


1写出下列算法的时间复杂度。 
(1)冒泡排序； 
(2)选择排序； 
(3)插入排序； 
(4)快速排序； 
(5)堆排序； 
(6)归并排序； 

2写出下列程序在X86上的运行结果。 

struct mybitfields 
{ 
unsigned short a : 4; 
unsigned short b : 5; 
unsigned short c : 7; 
}test 

void main(void) 
{ 
int i; 
test.a=2; 
test.b=3; 
test.c=0; 

i=*((short *)&test); 
printf("%d\n",i); 
} 

3写出下列程序的运行结果。 

unsigned int i=3; 
cout<<i * -1; 

4写出下列程序所有可能的运行结果。 

int a; 
int b; 
int c; 

void F1() 
{ 
b=a*2; 
a=b; 
} 

void F2() 
{ 
c=a+1; 
a=c; 
} 

main() 
{ 
a=5; 
//Start F1,F2 in parallel 
F1(); F2(); 
printf("a=%d\n",a); 
} 

5考察了一个CharPrev()函数的作用。 

6对 16 Bits colors的处理，要求： 
（1）Byte转换为RGB时，保留高5、6bits； 
（2）RGB转换为Byte时，第2、3位置零。 

7一个链表的操作，注意代码的健壮和安全性。要求： 
（1）增加一个元素； 
（2）获得头元素； 
（3）弹出头元素（获得值并删除）。 

8一个给定的数值由左边开始升位到右边第N位，如 
0010<<1 == 0100 
或者 
0001 0011<<4 == 0011 0000 
请用C或者C++或者其他X86上能运行的程序实现。 

附加题（只有在完成以上题目后，才获准回答） 
In C++, what does "explicit" mean? what does "protected" mean? 

31.分别写出BOOL,int,float,指针类型的变量a 与“零”的比较语句。
答案：
BOOL : if ( !a ) or if(a)
int : if ( a == 0)
float : const EXPRESSION EXP = 0.000001
if ( a < EXP && a >-EXP)
pointer : if ( a != NULL) or if(a == NULL) 



32.请说出const与#define 相比，有何优点？
答案：1） const 常量有数据类型，而宏常量没有数据类型。编译器可以对前者进行类型安全检查。而对后者只进行字符替换，没有类型安全检查，并且在字符替换可能会产生意料不到的错误。
2） 有些集成化的调试工具可以对const 常量进行调试，但是不能对宏常量进行调试。

33.简述数组与指针的区别？
数组要么在静态存储区被创建（如全局数组），要么在栈上被创建。指针可以随时指向任意类型的内存块。
(1)修改内容上的差别
char a[] = “hello”;
a[0] = ‘X’;
char *p = “world”; // 注意p 指向常量字符串
p[0] = ‘X’; // 编译器不能发现该错误，运行时错误
(2) 用运算符sizeof 可以计算出数组的容量（字节数）。sizeof(p),p 为指针得到的是一个指针变量的字节数，而不是p 所指的内存容量。C++/C 语言没有办法知道指针所指的内存容量，除非在申请内存时记住它。注意当数组作为函数的参数进行传递时，该数组自动退化为同类型的指针。
char a[] = "hello world";
char *p = a;
cout<< sizeof(a) << endl; // 12 字节
cout<< sizeof(p) << endl; // 4 字节
计算数组和指针的内存容量
void Func(char a[100])
{
cout<< sizeof(a) << endl; // 4 字节而不是100 字节
}

34.类成员函数的重载、覆盖和隐藏区别？
答案：
a.成员函数被重载的特征：
（1）相同的范围（在同一个类中）；
（2）函数名字相同；
（3）参数不同；
（4）virtual 关键字可有可无。
b.覆盖是指派生类函数覆盖基类函数，特征是：
（1）不同的范围（分别位于派生类与基类）；
（2）函数名字相同；
（3）参数相同；
（4）基类函数必须有virtual 关键字。
c.“隐藏”是指派生类的函数屏蔽了与其同名的基类函数，规则如下：
（1）如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆）。
（2）如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual 关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）

35. There are two int variables: a and b, don’t use “if”, “? :”, “switch”or other judgement statements, find out the biggest one of the two numbers.
答案：( ( a + b ) + abs( a - b ) ) / 2

36. 如何打印出当前源文件的文件名以及源文件的当前行号？
答案：
cout << __FILE__ ;
cout<<__LINE__ ;
__FILE__和__LINE__是系统预定义宏，这种宏并不是在某个文件中定义的，而是由编译器定义的。

37. main 主函数执行完毕后，是否可能会再执行一段代码，给出说明？
答案：可以，可以用_onexit 注册一个函数，它会在main 之后执行int fn1(void), fn2(void), fn3(void), fn4 (void);
void main( void )
{
String str("zhanglin");
_onexit( fn1 );
_onexit( fn2 );
_onexit( fn3 );
_onexit( fn4 );
printf( "This is executed first.\n" );
}
int fn1()
{
printf( "next.\n" );
return 0;
}
int fn2()
{
printf( "executed " );
return 0;
}
int fn3()
{
printf( "is " );
return 0;
}
int fn4()
{
printf( "This " );
return 0;
}
The _onexit function is passed the address of a function (func) to be called when the program terminates normally. Successive calls to _onexit create a register of functions that are executed in LIFO (last-in-first-out) order. The functions passed to _onexit cannot take parameters.


38. 如何判断一段程序是由C 编译程序还是由C++编译程序编译的？
答案：
#ifdef __cplusplus
cout<<"c++";
#else
cout<<"c";
#endif

39.文件中有一组整数，要求排序后输出到另一个文件中
答案：

＃i nclude

＃i nclude

using namespace std;


void Order(vector& data) //bubble sort
{
int count = data.size() ;
int tag = false ; // 设置是否需要继续冒泡的标志位
for ( int i = 0 ; i < count ; i++)
{
for ( int j = 0 ; j < count - i - 1 ; j++)
{
if ( data[j] > data[j+1])
{
tag = true ;
int temp = data[j] ;
data[j] = data[j+1] ;
data[j+1] = temp ;
}
}
if ( !tag )
break ;
}
}


void main( void )
{
vectordata;
ifstream in("c:\\data.txt");
if ( !in)
{
cout<<"file error!";
exit(1);
}
int temp;
while (!in.eof())
{
in>>temp;
data.push_back(temp);
}
in.close(); //关闭输入文件流
Order(data);
ofstream out("c:\\result.txt");
if ( !out)
{
cout<<"file error!";
exit(1);
}
for ( i = 0 ; i < data.size() ; i++)
out<40. 链表题：一个链表的结点结构
struct Node
{
int data ;
Node *next ;
};
typedef struct Node Node ;


(1)已知链表的头结点head,写一个函数把这个链表逆序 ( Intel)

Node * ReverseList(Node *head) //链表逆序
{
if ( head == NULL || head->next == NULL )
return head;
Node *p1 = head ;
Node *p2 = p1->next ;
Node *p3 = p2->next ;
p1->next = NULL ;
while ( p3 != NULL )
{
p2->next = p1 ;
p1 = p2 ;
p2 = p3 ;
p3 = p3->next ;
}
p2->next = p1 ;
head = p2 ;
return head ;
}
(2)已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序。(保留所有结点，即便大小相同）
Node * Merge(Node *head1 , Node *head2)
{
if ( head1 == NULL)
return head2 ;
if ( head2 == NULL)
return head1 ;
Node *head = NULL ;
Node *p1 = NULL;
Node *p2 = NULL;
if ( head1->data < head2->data )
{
head = head1 ;
p1 = head1->next;
p2 = head2 ;
}
else
{
head = head2 ;
p2 = head2->next ;
p1 = head1 ;
}
Node *pcurrent = head ;
while ( p1 != NULL && p2 != NULL)
{
if ( p1->data <= p2->data )
{
pcurrent->next = p1 ;
pcurrent = p1 ;
p1 = p1->next ;
}
else
{
pcurrent->next = p2 ;
pcurrent = p2 ;
p2 = p2->next ;
}
}
if ( p1 != NULL )
pcurrent->next = p1 ;
if ( p2 != NULL )
pcurrent->next = p2 ;
return head ;
}
(3)已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序，这次要求用递归方法进行。 (Autodesk)
答案：
Node * MergeRecursive(Node *head1 , Node *head2)
{
if ( head1 == NULL )
return head2 ;
if ( head2 == NULL)
return head1 ;
Node *head = NULL ;
if ( head1->data < head2->data )
{
head = head1 ;
head->next = MergeRecursive(head1->next,head2);
}
else
{
head = head2 ;
head->next = MergeRecursive(head1,head2->next);
}
return head ;
}




[C/C++] C/C++ 笔试、面试题目大汇总[41-45] 
bioeconomy 发表于 2006-3-22 20:28:00 


41. 分析一下这段程序的输出 (Autodesk)
class B
{
public:
B()
{
cout<<"default constructor"<}
~B()
{
cout<<"destructed"<}
B(int i):data(i) //B(int) works as a converter ( int -> instance of B)
{
cout<<"constructed by parameter " << data <}
private:
int data;
};


B Play( B b) 
{
return b ;
}

(1) results:
int main(int argc, char* argv[]) constructed by parameter 5
{ destructed B(5)形参析构
B t1 = Play(5); B t2 = Play(t1); 　 destructed t1形参析构
return 0;　　　　　　　　　　　　　　 destructed t2　注意顺序！
} destructed t1

(2) results:
int main(int argc, char* argv[]) constructed by parameter 5
{ destructed B(5)形参析构
B t1 = Play(5); B t2 = Play(10); 　 constructed by parameter 10
return 0;　　　　　　　　　　　　　　 destructed B(10)形参析构
} destructed t2　注意顺序！ 

destructed t1

42. 写一个函数找出一个整数数组中，第二大的数 （microsoft）
答案：
const int MINNUMBER = -32767 ;
int find_sec_max( int data[] , int count)
{
int maxnumber = data[0] ;
int sec_max = MINNUMBER ;
for ( int i = 1 ; i < count ; i++)
{
if ( data[i] > maxnumber )
{
sec_max = maxnumber ;
maxnumber = data[i] ;
}
else
{
if ( data[i] > sec_max )
sec_max = data[i] ;
}
}
return sec_max ;
}

43. 写一个在一个字符串(n)中寻找一个子串(m)第一个位置的函数。

KMP算法效率最好，时间复杂度是Ｏ(n+m),详见：http://www.zhanglihai.com/blog/c_335_kmp.html

44. 多重继承的内存分配问题：
比如有class A : public class B, public class C {}
那么A的内存结构大致是怎么样的？

这个是compiler-dependent的, 不同的实现其细节可能不同。
如果不考虑有虚函数、虚继承的话就相当简单；否则的话，相当复杂。
可以参考《深入探索C++对象模型》，或者：
http://blog.csdn.net/rainlight/archive/2006/03/03/614792.aspx
http://msdn.microsoft.com/archive/default.asp?url=/archive/en-us/dnarvc/html/jangrayhood.asp


45. 如何判断一个单链表是有环的？（注意不能用标志位，最多只能用两个额外指针）

struct node { char val; node* next;}

bool check(const node* head) {} //return false : 无环；true: 有环

一种O（n）的办法就是（搞两个指针，一个每次递增一步，一个每次递增两步，如果有环的话两者必然重合，反之亦然）：
bool check(const node* head)
{
if(head==NULL) return false;
node *low=head, *fast=head->next;
while(fast!=NULL && fast->next!=NULL)
{
low=low->next;
fast=fast->next->next;
if(low==fast) return true;
}
return false;
}



一、请填写BOOL , float, 指针变量 与“零值”比较的 if 语句。（10分）


提示：这里“零值”可以是0, 0.0 , FALSE或者“空指针”。例如 int 变量 n 与“零值”比较的 if 语句为：

if ( n == 0 )

if ( n != 0 )

以此类推。




请写出 BOOL flag 与“零值”比较的 if 语句：







请写出 float x 与“零值”比较的 if 语句：










请写出 char *p 与“零值”比较的 if 语句：












二、以下为Windows NT下的32位C++程序，请计算sizeof的值（10分）





char str[] = “Hello” ;

char *p = str ;

int n = 10;

请计算

sizeof (str ) = 



sizeof ( p ) = 



sizeof ( n ) =
void Func ( char str[100])

{

请计算

sizeof( str ) = 

}




void *p = malloc( 100 );

请计算

sizeof ( p ) =









三、简答题（25分）





1、头文件中的 ifndef/define/endif 干什么用？










2、#include 和 #include “filename.h” 有什么区别？










3、const 有什么用途？（请至少说明两种）










4、在C++ 程序中调用被 C编译器编译后的函数，为什么要加 extern “C”声明？













5、请简述以下两个for循环的优缺点



// 第一个


for (i=0; i

{


if (condition)


DoSomething();


else


DoOtherthing();


}

// 第二个


if (condition)


{


for (i=0; i

DoSomething();


}


else


{


for (i=0; i

DoOtherthing();


}


优点：






缺点：







优点：






缺点：











四、有关内存的思考题（20分）




void GetMemory(char *p)


{


p = (char *)malloc(100);


}


void Test(void) 

{

char *str = NULL;


GetMemory(str); 


strcpy(str, "hello world");


printf(str);


}




请问运行Test函数会有什么样的结果？


答：












char *GetMemory(void)


{ 


char p[] = "hello world";


return p;


}


void Test(void)


{


char *str = NULL;


str = GetMemory(); 


printf(str);


}




请问运行Test函数会有什么样的结果？


答：

Void GetMemory2(char **p, int num)


{


*p = (char *)malloc(num);


}

void Test(void)


{


char *str = NULL;


GetMemory(&str, 100);


strcpy(str, "hello"); 


printf(str); 


}

请问运行Test函数会有什么样的结果？


答：















void Test(void)


{


char *str = (char *) malloc(100);


strcpy(str, “hello”);


free(str); 


if(str != NULL)


{


strcpy(str, “world”); 


printf(str);


}


}

请问运行Test函数会有什么样的结果？


答：





















五、编写strcpy函数（10分）


已知strcpy函数的原型是

char *strcpy(char *strDest, const char *strSrc);

其中strDest是目的字符串，strSrc是源字符串。




（1）不调用C++/C的字符串库函数，请编写函数 strcpy






















（2）strcpy能把strSrc的内容复制到strDest，为什么还要char * 类型的返回值？













六、编写类String的构造函数、析构函数和赋值函数（25分）


已知类String的原型为：

class String


{


public:


String(const char *str = NULL); // 普通构造函数


String(const String &other); // 拷贝构造函数


~ String(void); // 析构函数


String & operate =(const String &other); // 赋值函数


private:


char *m_data; // 用于保存字符串


};


请编写String的上述4个函数。


以上题目摘自林锐博士的《高质量C++编程指南》。大家可以去看这本书作为参考

 

什么是预编译
何时需要预编译：
１、总是使用不经常改动的大型代码体。 
２、程序由多个模块组成，所有模块都使用一组标准的包含文件和相同的编译选项。在这种情况下，可以将所有包含文件预编译为一个预编译头。
char * const p;
char const * p
const char *p

上述三个有什么区别？
char * const p; //常量指针，p的值不可以修改
char const * p；//指向常量的指针，指向的常量值不可以改
const char *p； //和char const *p

char str1[] = "abc";
char str2[] = "abc";

const char str3[] = "abc";
const char str4[] = "abc";

const char *str5 = "abc";
const char *str6 = "abc";

char *str7 = "abc";
char *str8 = "abc";


cout << ( str1 == str2 ) << endl;
cout << ( str3 == str4 ) << endl;
cout << ( str5 == str6 ) << endl;
cout << ( str7 == str8 ) << endl;

结果是：0 0 1 1
解答：str1,str2,str3,str4是数组变量，它们有各自的内存空间；
而str5,str6,str7,str8是指针，它们指向相同的常量区域。


12. 以下代码中的两个sizeof用法有问题吗？[C易]
void UpperCase( char str[] ) // 将 str 中的小写字母转换成大写字母
{
for( size_t i=0; i<sizeof(str)/sizeof(str[0]); ++i )
if( 'a'<=str[i] && str[i]<='z' )
str[i] -= ('a'-'A' );
}
char str[] = "aBcDe";
cout << "str字符长度为: " << sizeof(str)/sizeof(str[0]) << endl;
UpperCase( str );
cout << str << endl;

答：函数内的sizeof有问题。根据语法，sizeof如用于数组，只能测出静态数组的大小，无法检测动态分配的或外部数组大小。函数外的str是一个静态定义的数组，因此其大小为6，函数内的str实际只是一个指向字符串的指针，没有任何额外的与数组相关的信息，因此sizeof作用于上只将其当指针看，一个指针为4个字节，因此返回4。

一个32位的机器,该机器的指针是多少位
指针是多少位只要看地址总线的位数就行了。80386以后的机子都是32的数据总线。所以指针的位数就是4个字节了。

main()
{
int a[5]={1,2,3,4,5};
int *ptr=(int *)(&a+1);

printf("%d,%d",*(a+1),*(ptr-1));
}
输出：2,5
*(a+1）就是a[1]，*(ptr-1)就是a[4],执行结果是2，5
&a+1不是首地址+1，系统会认为加一个a数组的偏移，是偏移了一个数组的大小（本例是5个int）
int *ptr=(int *)(&a+1); 
则ptr实际是&(a[5]),也就是a+5
原因如下：
&a是数组指针，其类型为 int (*)[5];
而指针加1要根据指针类型加上一定的值，
不同类型的指针+1之后增加的大小不同
a是长度为5的int数组指针，所以要加 5*sizeof(int)
所以ptr实际是a[5]
但是prt与(&a+1)类型是不一样的(这点很重要)
所以prt-1只会减去sizeof(int*)
a,&a的地址是一样的，但意思不一样，a是数组首地址，也就是a[0]的地址，&a是对象（数组）首地址，a+1是数组下一元素的地址，即a[1],&a+1是下一个对象的地址，即a[5].


1.请问以下代码有什么问题：
int main()
{
char a;
char *str=&a;
strcpy(str,"hello");
printf(str);
return 0;
}
没有为str分配内存空间，将会发生异常
问题出在将一个字符串复制进一个字符变量指针所指地址。虽然可以正确输出结果，但因为越界进行内在读写而导致程序崩溃。

char* s="AAA";
printf("%s",s);
s[0]='B';
printf("%s",s);
有什么错？
"AAA"是字符串常量。s是指针，指向这个字符串常量，所以声明s的时候就有问题。
cosnt char* s="AAA";
然后又因为是常量，所以对是s[0]的赋值操作是不合法的
1、写一个“标准”宏，这个宏输入两个参数并返回较小的一个。
.#define Min(X, Y) ((X)>(Y)?(Y):(X))//结尾没有;
2、嵌入式系统中经常要用到无限循环，你怎么用C编写死循环。
while(1){}或者for(;;)
3、关键字static的作用是什么？
定义静态变量
4、关键字const有什么含意？
表示常量不可以修改的变量。
5、关键字volatile有什么含意？并举出三个不同的例子？
提示编译器对象的值可能在编译器未监测到的情况下改变。


int (*s[10])(int) 表示的是什么啊
int (*s[10])(int) 函数指针数组，每个指针指向一个int func(int param)的函数。


1.有以下表达式：
int a=248; b=4;int const c=21;const int *d=&a;
int *const e=&b;int const *f const =&a;
请问下列表达式哪些会被编译器禁止？为什么？
*c=32;d=&b;*d=43;e=34;e=&a;f=0x321f;
*c 这是个什么东东，禁止
*d 说了是const， 禁止
e = &a 说了是const 禁止
const *f const =&a; 禁止
2.交换两个变量的值，不使用第三个变量。即a=3,b=5,交换之后a=5,b=3;
有两种解法, 一种用算术算法, 一种用^(异或)
a = a + b;
b = a - b;
a = a - b; 
or
a = a^b;// 只能对int,char..
b = a^b;
a = a^b;
or
a ^= b ^= a;
3.c和c++中的struct有什么不同？
c和c++中struct的主要区别是c中的struct不可以含有成员函数，而c++中的struct可以。c++中struct和class的主要区别在于默认的存取权限不同，struct默认为public，而class默认为private
4.#include <stdio.h>
#include <stdlib.h>
void getmemory(char *p)
{
p=(char *) malloc(100);
strcpy(p,"hello world");
}
int main( )
{
char *str=NULL;
getmemory(str);
printf("%s/n",str);
free(str);
return 0;
}
程序崩溃，getmemory中的malloc 不能返回动态内存， free（）对str操作很危险
5.char szstr[10];
strcpy(szstr,"0123456789");
产生什么结果？为什么？
长度不一样，会造成非法的OS
6.列举几种进程的同步机制，并比较其优缺点。
原子操作 
信号量机制
自旋锁
管程，会合，分布式系统

7.进程之间通信的途径
共享存储系统
消息传递系统
管道：以文件系统为基础
11.进程死锁的原因
资源竞争及进程推进顺序非法
12.死锁的4个必要条件
互斥、请求保持、不可剥夺、环路
13.死锁的处理
鸵鸟策略、预防策略、避免策略、检测与解除死锁
15. 操作系统中进程调度策略有哪几种？
FCFS(先来先服务)，优先级，时间片轮转，多级反馈
8.类的静态成员和非静态成员有何区别？
类的静态成员每个类只有一个，非静态成员每个对象一个
9.纯虚函数如何定义？使用时应注意什么？
virtual void f()=0;
是接口，子类必须要实现
10.数组和链表的区别
数组：数据顺序存储，固定大小
连表：数据可以随机存储，大小可动态改变

12.ISO的七层模型是什么？tcp/udp是属于哪一层？tcp/udp有何优缺点？
应用层
表示层
会话层
运输层
网络层
物理链路层
物理层
tcp /udp属于运输层
TCP 服务提供了数据流传输、可靠性、有效流控制、全双工操作和多路复用技术等。
与 TCP 不同， UDP 并不提供对 IP 协议的可靠机制、流控制以及错误恢复功能等。由于 UDP 比较简单， UDP 头包含很少的字节，比 TCP 负载消耗少。
tcp: 提供稳定的传输服务，有流量控制，缺点是包头大，冗余性不好
udp: 不提供稳定的服务，包头小，开销小 


1：(void *)ptr 和 (*(void**))ptr的结果是否相同？其中ptr为同一个指针
.(void *)ptr 和 (*(void**))ptr值是相同的
2：int main()
{
int x=3;
printf("%d",x);
return 1;

}
问函数既然不会被其它函数调用，为什么要返回1？
mian中，c标准认为0表示成功，非0表示错误。具体的值是某中具体出错信息


1，要对绝对地址0x100000赋值，我们可以用
(unsigned int*)0x100000 = 1234;
那么要是想让程序跳转到绝对地址是0x100000去执行，应该怎么做？
*((void (*)( ))0x100000 ) ( );
首先要将0x100000强制转换成函数指针,即:
(void (*)())0x100000
然后再调用它:
*((void (*)())0x100000)();
用typedef可以看得更直观些:
typedef void(*)() voidFuncPtr;
*((voidFuncPtr)0x100000)();
2，已知一个数组table，用一个宏定义，求出数据的元素个数
#define NTBL
#define NTBL (sizeof(table)/sizeof(table[0]))

面试题: 线程与进程的区别和联系? 线程是否具有相同的堆栈? dll是否有独立的堆栈?
进程是死的，只是一些资源的集合，真正的程序执行都是线程来完成的，程序启动的时候操作系统就帮你创建了一个主线程。

每个线程有自己的堆栈。
DLL中有没有独立的堆栈，这个问题不好回答，或者说这个问题本身是否有问题。因为DLL中的代码是被某些线程所执行，只有线程拥有堆栈，如果DLL中的代码是EXE中的线程所调用，那么这个时候是不是说这个DLL没有自己独立的堆栈？如果DLL中的代码是由DLL自己创建的线程所执行，那么是不是说DLL有独立的堆栈？

以上讲的是堆栈，如果对于堆来说，每个DLL有自己的堆，所以如果是从DLL中动态分配的内存，最好是从DLL中删除，如果你从DLL中分配内存，然后在EXE中，或者另外一个DLL中删除，很有可能导致程序崩溃


unsigned short A = 10;
printf("~A = %u\n", ~A);

char c=128; 
printf("c=%d\n",c);

输出多少？并分析过程
第一题，～A ＝0xfffffff5,int值 为－11，但输出的是uint。所以输出4294967285
第二题，c＝0x10,输出的是int，最高位为1，是负数，所以它的值就是0x00的补码就是128，所以输出－128。
这两道题都是在考察二进制向int或uint转换时的最高位处理。

分析下面的程序：
void GetMemory(char **p,int num)
{
*p=(char *)malloc(num);

} 
int main()
{
char *str=NULL;

GetMemory(&str,100);

strcpy(str,"hello");

free(str);

if(str!=NULL)
{
strcpy(str,"world");
} 

printf("\n str is %s",str);
getchar();
} 
问输出结果是什么？希望大家能说说原因，先谢谢了
输出str is world。
free 只是释放的str指向的内存空间,它本身的值还是存在的.
所以free之后，有一个好的习惯就是将str=NULL.
此时str指向空间的内存已被回收,如果输出语句之前还存在分配空间的操作的话,这段存储空间是可能被重新分配给其他变量的,
尽管这段程序确实是存在大大的问题（上面各位已经说得很清楚了），但是通常会打印出world来。
这是因为，进程中的内存管理一般不是由操作系统完成的，而是由库函数自己完成的。
当你malloc一块内存的时候，管理库向操作系统申请一块空间（可能会比你申请的大一些），然后在这块空间中记录一些管理信息（一般是在你申请的内存前面一点），并将可用内存的地址返回。但是释放内存的时候，管理库通常都不会将内存还给操作系统，因此你是可以继续访问这块地址的，只不过。。。。。。。。楼上都说过了，最好别这么干。

char a[10],strlen(a)为什么等于15？运行的结果

#include "stdio.h"
#include "string.h"

void main()
{

char aa[10];
printf("%d",strlen(aa));
}

sizeof()和初不初始化，没有关系；
strlen()和初始化有关。


char (*str)[20];/*str是一个数组指针，即指向数组的指针．*/
char *str[20];/*str是一个指针数组，其元素为指针型数据．*/

long a=0x801010;
a+5=?
0x801010用二进制表示为：“1000 0000 0001 0000 0001 0000”，十进制的值为8392720，再加上5就是8392725罗
1)给定结构struct A 
{
char t:4;
char k:4;
unsigned short i:8;
unsigned long m;
};问sizeof(A) = ?
给定结构struct A 
{
char t:4; 4位
char k:4; 4位
unsigned short i:8; 8位 
unsigned long m; // 偏移2字节保证4字节对齐
}; // 共8字节
2)下面的函数实现在一个数上加一个数，有什么错误？请改正。
int add_n ( int n )
{
static int i = 100;
i += n;
return i;
}
当你第二次调用时得不到正确的结果，难道你写个函数就是为了调用一次？问题就出在 static上？


// 帮忙分析一下
#include<iostream.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct AA
{
int b1:5;
int b2:2;
}AA;
void main()
{
AA aa;
char cc[100];
strcpy(cc,"0123456789abcdefghijklmnopqrstuvwxyz");
memcpy(&aa,cc,sizeof(AA));
cout << aa.b1 <<endl;
cout << aa.b2 <<endl;
}
答案是 -16和１
首先sizeof(AA)的大小为4,b1和b2分别占5bit和2bit.
经过strcpy和memcpy后,aa的4个字节所存放的值是:
0,1,2,3的ASC码，即00110000,00110001,00110010,00110011
所以，最后一步：显示的是这４个字节的前５位，和之后的２位
分别为：10000,和01
因为int是有正负之分　　所以：答案是-16和１

求函数返回值，输入x=9999; 
int func （ x ）
{ 
int countx = 0; 
while ( x ) 
{ 
countx ++; 
x = x&(x-1); 
} 
return countx; 
} 
结果呢？
知道了这是统计9999的二进制数值中有多少个1的函数，且有
9999＝9×1024＋512＋256＋15

9×1024中含有1的个数为2；
512中含有1的个数为1；
256中含有1的个数为1；
15中含有1的个数为4；
故共有1的个数为8，结果为8。
1000 - 1 = 0111，正好是原数取反。这就是原理。
用这种方法来求1的个数是很效率很高的。
不必去一个一个地移位。循环次数最少。

int a,b,c 请写函数实现C=a+b ,不可以改变数据类型,如将c改为long int,关键是如何处理溢出问题
bool add (int a, int b,int *c)
{
*c=a+b;
return (a>0 && b>0 &&(*c<a || *c<b) || (a<0 && b<0 &&(*c>a || *c>b)));
}


分析：
struct bit 
{ int a:3; 
int b:2; 
int c:3; 
}; 
int main() 
{ 
bit s; 
char *c=(char*)&s; 
cout<<sizeof(bit)<<endl;
*c=0x99;
cout << s.a <<endl <<s.b<<endl<<s.c<<endl; 
int a=-1;
printf("%x",a);
return 0; 
} 
输出为什么是
4
1
-1
-4
ffffffff
因为0x99在内存中表示为 100 11 001 , a = 001, b = 11, c = 100
当c为有符合数时, c = 100, 最高1为表示c为负数，负数在计算机用补码表示，所以c = -4;同理 
b = -1;
当c为有符合数时, c = 100,即 c = 4,同理 b = 3


位域 ： 
有些信息在存储时，并不需要占用一个完整的字节， 而只需占几个或一个二进制位。例如在存放一个开关量时，只有0和1 两种状态， 用一位二进位即可。为了节省存储空间，并使处理简便，Ｃ语言又提供了一种数据结构，称为“位域”或“位段”。所谓“位域”是把一个字节中的二进位划分为几个不同的区域， 并说明每个区域的位数。每个域有一个域名，允许在程序中按域名进行操作。 这样就可以把几个不同的对象用一个字节的二进制位域来表示。一、位域的定义和位域变量的说明位域定义与结构定义相仿，其形式为： 
struct 位域结构名 
{ 位域列表 }; 
其中位域列表的形式为： 类型说明符 位域名：位域长度 
例如： 
struct bs 
{ 
int a:8; 
int b:2; 
int c:6; 
}; 
位域变量的说明与结构变量说明的方式相同。 可采用先定义后说明，同时定义说明或者直接说明这三种方式。例如： 
struct bs 
{ 
int a:8; 
int b:2; 
int c:6; 
}data; 
说明data为bs变量，共占两个字节。其中位域a占8位，位域b占2位，位域c占6位。对于位域的定义尚有以下几点说明： 

1. 一个位域必须存储在同一个字节中，不能跨两个字节。如一个字节所剩空间不够存放另一位域时，应从下一单元起存放该位域。也可以有意使某位域从下一单元开始。例如： 
struct bs 
{ 
unsigned a:4 
unsigned :0 /*空域*/ 
unsigned b:4 /*从下一单元开始存放*/ 
unsigned c:4 
} 
在这个位域定义中，a占第一字节的4位，后4位填0表示不使用，b从第二字节开始，占用4位，c占用4位。 

2. 由于位域不允许跨两个字节，因此位域的长度不能大于一个字节的长度，也就是说不能超过8位二进位。 

3. 位域可以无位域名，这时它只用来作填充或调整位置。无名的位域是不能使用的。例如： 
struct k 
{ 
int a:1 
int :2 /*该2位不能使用*/ 
int b:3 
int c:2 
}; 
从以上分析可以看出，位域在本质上就是一种结构类型， 不过其成员是按二进位分配的。 

二、位域的使用位域的使用和结构成员的使用相同，其一般形式为： 位域变量名•位域名 位域允许用各种格式输出。 
main(){ 
struct bs 
{ 
unsigned a:1; 
unsigned b:3; 
unsigned c:4; 
} bit,*pbit; 
bit.a=1; 
bit.b=7; 
bit.c=15; 
pri

改错：
#include <stdio.h>

int main(void) {

int **p;
int arr[100];

p = &arr;

return 0;
}
解答：
搞错了,是指针类型不同,
int **p; //二级指针
&arr; //得到的是指向第一维为100的数组的指针
#include <stdio.h>
int main(void) {
int **p, *q;
int arr[100];
q = arr;
p = &q;
return 0;
}


下面这个程序执行后会有什么错误或者效果:
#define MAX 255
int main()
{
unsigned char A[MAX],i;//i被定义为unsigned char
for (i=0;i<=MAX;i++)
A[i]=i;
}
解答：死循环加数组越界访问（C/C++不进行数组越界检查）
MAX=255 
数组A的下标范围为:0..MAX-1,这是其一..
其二.当i循环到255时,循环内执行:
A[255]=255;
这句本身没有问题..但是返回for (i=0;i<=MAX;i++)语句时,
由于unsigned char的取值范围在(0..255),i++以后i又为0了..无限循环下去.

struct name1{
char str;
short x;
int num;
}

struct name2{
char str;
int num;
short x;
}

sizeof(struct name1)=8,sizeof(struct name2)=12
在第二个结构中，为保证num按四个字节对齐，char后必须留出3字节的空间；同时为保证整个结构的自然对齐（这里是4字节对齐），在x后还要补齐2个字节，这样就是12字节。

intel：
A.c 和B.c两个c文件中使用了两个相同名字的static变量,编译的时候会不会有问题?这两个static变量会保存到哪里（栈还是堆或者其他的）?
static的全局变量，表明这个变量仅在本模块中有意义，不会影响其他模块。
他们都放在数据区，但是编译器对他们的命名是不同的。
如果要使变量在其他模块也有意义的话，需要使用extern关键字。

struct s1
{
int i: 8;
int j: 4;
int a: 3;
double b;
};

struct s2
{
int i: 8;
int j: 4;
double b;
int a:3;
};

printf("sizeof(s1)= %d\n", sizeof(s1));
printf("sizeof(s2)= %d\n", sizeof(s2));
result: 16, 24
第一个struct s1
{
int i: 8;
int j: 4;
int a: 3;
double b;
};
理论上是这样的，首先是i在相对0的位置，占8位一个字节，然后，j就在相对一个字节的位置，由于一个位置的字节数是4位的倍数，因此不用对齐，就放在那里了，然后是a，要在3位的倍数关系的位置上，因此要移一位，在15位的位置上放下，目前总共是18位，折算过来是2字节2位的样子，由于double是8字节的，因此要在相对0要是8个字节的位置上放下，因此从18位开始到8个字节之间的位置被忽略，直接放在8字节的位置了，因此，总共是16字节。

第二个最后会对照是不是结构体内最大数据的倍数，不是的话，会补成是最大数据的倍数

 

 
给定字符串A和B,输出A和B中的最大公共子串。
比如A="aocdfe" B="pmcdfa" 则输出"cdf"
*/
//Author: azhen
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *commanstring(char shortstring[], char longstring[])
{
int i, j;

char *substring=malloc(256);

if(strstr(longstring, shortstring)!=NULL) //如果……，那么返回shortstring
return shortstring; 

for(i=strlen(shortstring)-1;i>0; i--) //否则，开始循环计算
{
for(j=0; j<=strlen(shortstring)-i; j++){
memcpy(substring, &shortstring[j], i);
substring[i]='\0';
if(strstr(longstring, substring)!=NULL)
return substring;
}
}
return NULL;
}


main()
{
char *str1=malloc(256);
char *str2=malloc(256);
char *comman=NULL;

gets(str1);
gets(str2);

if(strlen(str1)>strlen(str2)) //将短的字符串放前面
comman=commanstring(str2, str1);
else
comman=commanstring(str1, str2);

printf("the longest comman string is: %s\n", comman);
}


11.写一个函数比较两个字符串str1和str2的大小，若相等返回0，若str1大于
str2返回1，若str1小于str2返回－1
int strcmp ( const char * src,const char * dst)
{
int ret = 0 ;
while( ! (ret = *(unsigned char *)src - *(unsigned char *)dst) && *dst)
{
++src;
++dst;
}
if ( ret < 0 )
ret = -1 ;
else if ( ret > 0 )
ret = 1 ;
return( ret );
}
3,求1000！的未尾有几个0（用素数相乘的方法来做，如72=2*2*2*3*3）;
求出1->1000里,能被5整除的数的个数n1,能被25整除的数的个数n2,能被125整除的数的个数n3,
能被625整除的数的个数n4.
1000!末尾的零的个数=n1+n2+n3+n4;
#include<stdio.h>
#define NUM 1000

int find5(int num){
int ret=0;
while(num%5==0){
num/=5;
ret++;
}
return ret;
}
int main(){
int result=0;
int i;
for(i=5;i<=NUM;i+=5)
{
result+=find5(i);
}
printf(" the total zero number is %d\n",result);
return 0;
}




1. 有双向循环链表结点定义为： 
struct node 
{ int data; 
struct node *front,*next; 
}; 
有两个双向循环链表A，B，知道其头指针为：pHeadA,pHeadB，请写一函数将两链表中data值相同的结点删除 
BOOL DeteleNode(Node *pHeader, DataType Value)
{
if (pHeader == NULL) return;

BOOL bRet = FALSE;
Node *pNode = pHead;
while (pNode != NULL)
{
if (pNode->data == Value)
{
if (pNode->front == NULL)
{
pHeader = pNode->next;
pHeader->front = NULL;
}
else
{
if (pNode->next != NULL)
{
pNode->next->front = pNode->front;
}
pNode->front->next = pNode->next;
}

Node *pNextNode = pNode->next;
delete pNode;
pNode = pNextNode;

bRet = TRUE; 
//不要break或return, 删除所有
}
else
{
pNode = pNode->next;
}
}

return bRet;
}

void DE(Node *pHeadA, Node *pHeadB)
{
if (pHeadA == NULL || pHeadB == NULL)
{
return;
}

Node *pNode = pHeadA;
while (pNode != NULL)
{
if (DeteleNode(pHeadB, pNode->data))
{
if (pNode->front == NULL)
{
pHeadA = pNode->next;
pHeadA->front = NULL;
}
else
{
pNode->front->next = pNode->next;
if (pNode->next != NULL)
{
pNode->next->front = pNode->front;
}
}
Node *pNextNode = pNode->next;
delete pNode;
pNode = pNextNode;
}
else
{
pNode = pNode->next;
}
}
}
2. 编程实现：找出两个字符串中最大公共子字符串,如"abccade","dgcadde"的最大子串为"cad" 
int GetCommon(char *s1, char *s2, char **r1, char **r2)
{
int len1 = strlen(s1);
int len2 = strlen(s2);
int maxlen = 0;

for(int i = 0; i < len1; i++)
{
for(int j = 0; j < len2; j++)
{
if(s1[i] == s2[j])
{
int as = i, bs = j, count = 1;
while(as + 1 < len1 && bs + 1 < len2 && s1[++as] == s2[++bs])
count++;

if(count > maxlen)
{
maxlen = count;
*r1 = s1 + i;
*r2 = s2 + j;
}
}
}
}
3. 编程实现：把十进制数(long型)分别以二进制和十六进制形式输出，不能使用printf系列库函数
char* test3(long num) {
char* buffer = (char*)malloc(11);
buffer[0] = '0';
buffer[1] = 'x';
buffer[10] = '\0';

char* temp = buffer + 2;
for (int i=0; i < 8; i++) {
temp[i] = (char)(num<<4*i>>28);
temp[i] = temp[i] >= 0 ? temp[i] : temp[i] + 16;
temp[i] = temp[i] < 10 ? temp[i] + 48 : temp[i] + 55;
}
return buffer;
}




输入N, 打印 N*N 矩阵
比如 N = 3，打印：

1 2 3
8 9 4
7 6 5

N = 4，打印：

1 2 3 4
12 13 14 5
11 16 15 6
10 9 8 7
解答：
1 #define N 15
int s[N][N];
void main()
{
int k = 0, i = 0, j = 0;
int a = 1; 
for( ; k < (N+1)/2; k++ )
{
while( j < N-k ) s[i][j++] = a++; i++; j--;
while( i < N-k ) s[i++][j] = a++; i--; j--;
while( j > k-1 ) s[i][j--] = a++; i--; j++;
while( i > k ) s[i--][j] = a++; i++; j++; 
}
for( i = 0; i < N; i++ )
{
for( j = 0; j < N; j++ )
cout << s[i][j] << '\t';
cout << endl;
}
}
2 define MAX_N 100
int matrix[MAX_N][MAX_N];

/*
*（x,y）：第一个元素的坐标
* start：第一个元素的值
* n：矩阵的大小
*/
void SetMatrix(int x, int y, int start, int n) {
int i, j;

if (n <= 0) //递归结束条件
return;
if (n == 1) { //矩阵大小为1时
matrix[x][y] = start;
return;
}
for (i = x; i < x + n-1; i++) //矩阵上部
matrix[y][i] = start++;

for (j = y; j < y + n-1; j++) //右部
matrix[j][x+n-1] = start++;

for (i = x+n-1; i > x; i--) //底部
matrix[y+n-1][i] = start++;

for (j = y+n-1; j > y; j--) //左部
matrix[j][x] = start++;

SetMatrix(x+1, y+1, start, n-2); //递归
}

void main() {
int i, j;
int n;

scanf("%d", &n);
SetMatrix(0, 0, 1, n);

//打印螺旋矩阵
for(i = 0; i < n; i++) {
for (j = 0; j < n; j++)
printf("%4d", matrix[i][j]);
printf("\n");
}
}


斐波拉契数列递归实现的方法如下：
int Funct( int n )
{
if(n==0) return 1;
if(n==1) return 1;
retrurn Funct(n-1) + Funct(n-2);
}
请问，如何不使用递归，来实现上述函数？
请教各位高手！
解答：int Funct( int n ) // n 为非负整数
{
int a=0;
int b=1;
int c;
if(n==0) c=1;
else if(n==1) c=1;
else for(int i=2;i<=n;i++) //应该n从2开始算起
{
c=a+b;
a=b;
b=c;
}
return c;
}
解答：
现在大多数系统都是将低字位放在前面，而结构体中位域的申明一般是先声明高位。
100 的二进制是 001 100 100
低位在前 高位在后 
001----s3
100----s2
100----s1
所以结果应该是 1
如果先申明的在低位则：
001----s1
100----s2
100----s3
结果是 4
1、原题跟little-endian，big-endian没有关系
2、原题跟位域的存储空间分配有关，到底是从低字节分配还是从高字节分配，从Dev C++和VC7.1上看，都是从低字节开始分配，并且连续分配，中间不空，不像谭的书那样会留空位
3、原题跟编译器有关，编译器在未用堆栈空间的默认值分配上有所不同，Dev C++未用空间分配为
01110111b，VC7.1下为11001100b,所以在Dev C++下的结果为5，在VC7.1下为1。

注：PC一般采用little-endian，即高高低低，但在网络传输上，一般采用big-endian，即高低低高，华为是做网络的，所以可能考虑big-endian模式，这样输出结果可能为4



判断一个字符串是不是回文
int IsReverseStr(char *aStr)
{
int i,j;
int found=1;
if(aStr==NULL)
return -1;
j=strlen(aStr);
for(i=0;i<j/2;i++)
if(*(aStr+i)!=*(aStr+j-i-1))
{
found=0;
break;
}
return found;
}
Josephu 问题为：设编号为1，2，… n的n个人围坐一圈，约定编号为k（1<=k<=n）的人从1开始报数，数到m 的那个人出列，它的下一位又从1开始报数，数到m的那个人又出列，依次类推，直到所有人出列为止，由此产生一个出队编号的序列。

数组实现：
#include <stdio.h>
#include <malloc.h>
int Josephu(int n, int m)
{
int flag, i, j = 0;
int *arr = (int *)malloc(n * sizeof(int));
for (i = 0; i < n; ++i)
arr[i] = 1;
for (i = 1; i < n; ++i)
{
flag = 0;
while (flag < m)
{
if (j == n)
j = 0;
if (arr[j])
++flag;
++j;
}
arr[j - 1] = 0;
printf("第%4d个出局的人是：%4d号\n", i, j);
}
free(arr);
return j;
}
int main()
{
int n, m;
scanf("%d%d", &n, &m);
printf("最后胜利的是%d号！\n", Josephu(n, m));
system("pause");
return 0;
}
链表实现：
#include <stdio.h>
#include <malloc.h>
typedef struct Node
{
int index;
struct Node *next;
}JosephuNode;
int Josephu(int n, int m)
{
int i, j;
JosephuNode *head, *tail;
head = tail = (JosephuNode *)malloc(sizeof(JosephuNode));
for (i = 1; i < n; ++i)
{
tail->index = i;
tail->next = (JosephuNode *)malloc(sizeof(JosephuNode));
tail = tail->next;
}
tail->index = i;
tail->next = head;

for (i = 1; tail != head; ++i)
{
for (j = 1; j < m; ++j)
{
tail = head;
head = head->next;
}
tail->next = head->next;
printf("第%4d个出局的人是：%4d号\n", i, head->index);
free(head);
head = tail->next;
}
i = head->index;
free(head);
return i;
}
int main()
{
int n, m;
scanf("%d%d", &n, &m);
printf("最后胜利的是%d号！\n", Josephu(n, m));
system("pause");
return 0;
}

已知strcpy函数的原型是：
char * strcpy(char * strDest,const char * strSrc);
1.不调用库函数，实现strcpy函数。
2.解释为什么要返回char *。
解说：
1.strcpy的实现代码
char * strcpy(char * strDest,const char * strSrc)
{
if ((strDest==NULL)||(strSrc==NULL)) file://[/1]
throw "Invalid argument(s)"; //[2]
char * strDestCopy=strDest; file://[/3]
while ((*strDest++=*strSrc++)!='\0'); file://[/4]
return strDestCopy;
}
错误的做法：
[1]
(A)不检查指针的有效性，说明答题者不注重代码的健壮性。
(B)检查指针的有效性时使用((!strDest)||(!strSrc))或(!(strDest&&strSrc))，说明答题者对C语言中类型的隐式转换没有深刻认识。在本例中char *转换为bool即是类型隐式转换，这种功能虽然灵活，但更多的是导致出错概率增大和维护成本升高。所以C++专门增加了bool、true、false三个关键字以提供更安全的条件表达式。
(C)检查指针的有效性时使用((strDest==0)||(strSrc==0))，说明答题者不知道使用常量的好处。直接使用字面常量（如本例中的0）会减少程序的可维护性。0虽然简单，但程序中可能出现很多处对指针的检查，万一出现笔误，编译器不能发现，生成的程序内含逻辑错误，很难排除。而使用NULL代替0，如果出现拼写错误，编译器就会检查出来。
[2]
(A)return new string("Invalid argument(s)");，说明答题者根本不知道返回值的用途，并且他对内存泄漏也没有警惕心。从函数中返回函数体内分配的内存是十分危险的做法，他把释放内存的义务抛给不知情的调用者，绝大多数情况下，调用者不会释放内存，这导致内存泄漏。
(B)return 0;，说明答题者没有掌握异常机制。调用者有可能忘记检查返回值，调用者还可能无法检查返回值（见后面的链式表达式）。妄想让返回值肩负返回正确值和异常值的双重功能，其结果往往是两种功能都失效。应该以抛出异常来代替返回值，这样可以减轻调用者的负担、使错误不会被忽略、增强程序的可维护性。
[3]
(A)忘记保存原始的strDest值，说明答题者逻辑思维不严密。
[4]
(A)循环写成while (*strDest++=*strSrc++);，同[1](B)。
(B)循环写成while (*strSrc!='\0') *strDest++=*strSrc++;，说明答题者对边界条件的检查不力。循环体结束后，strDest字符串的末尾没有正确地加上'\0'。




 

4. static有什么用途？（请至少说明两种）
1.限制变量的作用域
2.设置变量的存储域
7. 引用与指针有什么区别？
1) 引用必须被初始化，指针不必。
2) 引用初始化以后不能被改变，指针可以改变所指的对象。
2) 不存在指向空值的引用，但是存在指向空值的指针。

8. 描述实时系统的基本特性
在特定时间内完成特定的任务，实时性与可靠性
9. 全局变量和局部变量在内存中是否有区别？如果有，是什么区别？
全局变量储存在静态数据库，局部变量在堆栈
10. 什么是平衡二叉树？
左右子树都是平衡二叉树 且左右子树的深度差值的绝对值不大于1
11. 堆栈溢出一般是由什么原因导致的？
没有回收垃圾资源
12. 什么函数不能声明为虚函数？
constructor
13. 冒泡排序算法的时间复杂度是什么？
O(n^2)
14. 写出float x 与“零值”比较的if语句。
if(x>0.000001&&x<-0.000001)
16. Internet采用哪种网络协议？该协议的主要层次结构？
tcp/ip 应用层/传输层/网络层/数据链路层/物理层
17. Internet物理地址和IP地址转换采用什么协议？
ARP (Address Resolution Protocol)（地址解析協議）
18.IP地址的编码分为哪俩部分？
IP地址由两部分组成，网络号和主机号。不过是要和“子网掩码”按位与上之后才能区分哪些是网络位哪些是主机位。


2.用户输入M,N值，从1至N开始顺序循环数数，每数到M输出该数值，直至全部输出。写出C程序。
循环链表，用取余操作做
3.不能做switch()的参数类型是：
switch的参数不能为实型。

華為
1、局部变量能否和全局变量重名？
答：能，局部会屏蔽全局。要用全局变量，需要使用"::"
局部变量可以与全局变量同名，在函数内引用这个变量时，会用到同名的局部变量，而不会用到全局变量。对于有些编译器而言，在同一个函数内可以定义多个同名的局部变量，比如在两个循环体内都定义一个同名的局部变量，而那个局部变量的作用域就在那个循环体内
2、如何引用一个已经定义过的全局变量？
答：extern
可以用引用头文件的方式，也可以用extern关键字，如果用引用头文件方式来引用某个在头文件中声明的全局变理，假定你将那个变写错了，那么在编译期间会报错，如果你用extern方式引用时，假定你犯了同样的错误，那么在编译期间不会报错，而在连接期间报错
3、全局变量可不可以定义在可被多个.C文件包含的头文件中？为什么？
答：可以，在不同的C文件中以static形式来声明同名全局变量。
可以在不同的C文件中声明同名的全局变量，前提是其中只能有一个C文件中对此变量赋初值，此时连接不会出错
4、语句for( ；1 ；)有什么问题？它是什么意思？
答：和while(1)相同。
5、do……while和while……do有什么区别？
答：前一个循环一遍再判断，后一个判断以后再循环
6、请写出下列代码的输出内容
#include<stdio.h>
main()
{
int a,b,c,d;
a=10;
b=a++;
c=++a;
d=10*a++;
printf("b，c，d：%d，%d，%d"，b，c，d）;
return 0;
} 
答：10，12，120

1、static全局变量与普通的全局变量有什么区别？static局部变量和普通局部变量有什么区别？static函数与普通函数有什么区别？
全局变量(外部变量)的说明之前再冠以static 就构成了静态的全局变量。全局变量本身就是静态存储方式， 静态全局变量当然也是静态存储方式。 这两者在存储方式上并无不同。这两者的区别虽在于非静态全局变量的作用域是整个源程序， 当一个源程序由多个源文件组成时，非静态的全局变量在各个源文件中都是有效的。 而静态全局变量则限制了其作用域， 即只在定义该变量的源文件内有效， 在同一源程序的其它源文件中不能使用它。由于静态全局变量的作用域局限于一个源文件内，只能为该源文件内的函数公用， 因此可以避免在其它源文件中引起错误。
从以上分析可以看出， 把局部变量改变为静态变量后是改变了它的存储方式即改变了它的生存期。把全局变量改变为静态变量后是改变了它的作用域， 限制了它的使用范围。
static函数与普通函数作用域不同。仅在本文件。只在当前源文件中使用的函数应该说明为内部函数(static)，内部函数应该在当前源文件中说明和定义。对于可在当前源文件以外使用的函数，应该在一个头文件中说明，要使用这些函数的源文件要包含这个头文件

static全局变量与普通的全局变量有什么区别：static全局变量只初使化一次，防止在其他文件单元中被引用;
static局部变量和普通局部变量有什么区别：static局部变量只被初始化一次，下一次依据上一次结果值；
static函数与普通函数有什么区别：static函数在内存中只有一份，普通函数在每个被调用中维持一份拷贝
2、程序的局部变量存在于（堆栈）中，全局变量存在于（静态区 ）中，动态申请数据存在于（ 堆）中。
3、设有以下说明和定义：
typedef union {long i; int k[5]; char c;} DATE;
struct data { int cat; DATE cow; double dog;} too;
DATE max;
则语句 printf("%d",sizeof(struct date)+sizeof(max));的执行结果是：___52____
答：DATE是一个union, 变量公用空间. 里面最大的变量类型是int[5], 占用20个字节. 所以它的大小是20
data是一个struct, 每个变量分开占用空间. 依次为int4 + DATE20 + double8 = 32.
所以结果是 20 + 32 = 52.
当然...在某些16位编辑器下, int可能是2字节,那么结果是 int2 + DATE10 + double8 = 20
4、队列和栈有什么区别？
队列先进先出，栈后进先出
5、写出下列代码的输出内容
#include<stdio.h>
int inc(int a)
{
return(++a);
}
int multi(int*a,int*b,int*c)
{
return(*c=*a**b);
}
typedef int(FUNC1)(int in);
typedef int(FUNC2) (int*,int*,int*);

void show(FUNC2 fun,int arg1, int*arg2)
{
INCp=&inc;
int temp =p(arg1);
fun(&temp,&arg1, arg2);
printf("%d\n",*arg2);
}

main()
{
int a;
show(multi,10,&a);
return 0;
}
答：110
7、请找出下面代码中的所以错误
说明：以下代码是把一个字符串倒序，如“abcd”倒序后变为“dcba”

1、#include"string.h"
2、main()
3、{
4、 char*src="hello,world";
5、 char* dest=NULL;
6、 int len=strlen(src);
7、 dest=(char*)malloc(len);
8、 char* d=dest;
9、 char* s=src[len];
10、 while(len--!=0) 
11、 d++=s--;
12、 printf("%s",dest);
13、 return 0;
14、} 
答：
方法1：
int main(){
char* src = "hello,world";
int len = strlen(src);
char* dest = (char*)malloc(len+1);//要为\0分配一个空间
char* d = dest;
char* s = &src[len-1];//指向最后一个字符
while( len-- != 0 )
*d++=*s--;
*d = 0;//尾部要加\0
printf("%s\n",dest);
free(dest);// 使用完，应当释放空间，以免造成内存汇泄露
return 0;
}
方法2：
#include <stdio.h>
#include <string.h>
main()
{
char str[]="hello,world";
int len=strlen(str);
char t;
for(int i=0; i<len/2; i++)
{
t=str[i]; 
str[i]=str[len-i-1]; str[len-i-1]=t;
}
printf("%s",str);
return 0;
}
1.-1,2,7,28,,126请问28和126中间那个数是什么？为什么？
第一题的答案应该是4^3-1=63
规律是n^3-1(当n为偶数0，2，4)
n^3+1(当n为奇数1，3，5)
答案：63
2.用两个栈实现一个队列的功能？要求给出算法和思路！
设2个栈为A,B, 一开始均为空.

入队:
将新元素push入栈A;

出队:
(1)判断栈B是否为空；
(2)如果不为空，则将栈A中所有元素依次pop出并push到栈B；
(3)将栈B的栈顶元素pop出；

这样实现的队列入队和出队的平摊复杂度都还是O(1), 比上面的几种方法要好。3.在c语言库函数中将一个字符转换成整型的函数是atool()吗，这个函数的原型是什么？
函数名: atol 
功 能: 把字符串转换成长整型数 
用 法: long atol(const char *nptr); 
程序例: 
#include <stdlib.h> 
#include <stdio.h> 
int main(void) 
{ 
long l; 
char *str = "98765432"; 

l = atol(lstr); 
printf("string = %s integer = %ld\n", str, l); 
return(0); 
}2.对于一个频繁使用的短小函数,在C语言中应用什么实现,在C++中应用什么实现?
c用宏定义，c++用inline
3.直接链接两个信令点的一组链路称作什么?
PPP点到点连接
4.接入网用的是什么接口?
5.voip都用了那些协议?
6.软件测试都有那些种类?
黑盒：针对系统功能的测试 白合：测试函数功能，各函数接口
7.确定模块的功能和模块的接口是在软件设计的那个队段完成的?
概要设计阶段
8.enum string
{
x1,
x2,
x3=10,
x4,
x5,
}x;
问x= 0x801005，0x8010f4 ;
9.unsigned char *p1;
unsigned long *p2;
p1=(unsigned char *)0x801000;
p2=(unsigned long *)0x810000;
请问p1+5= ;
p2+5= ;
三.选择题:
1.Ethternet链接到Internet用到以下那个协议?
A.HDLC;B.ARP;C.UDP;D.TCP;E.ID
2.属于网络层协议的是:
A.TCP;B.IP;C.ICMP;D.X.25
3.Windows消息调度机制是:
A.指令队列;B.指令堆栈;C.消息队列;D.消息堆栈;
4.unsigned short hash(unsigned short key)
{
return (key>>)%256
}
请问hash(16),hash(256)的值分别是:
A.1.16;B.8.32;C.4.16;D.1.32
四.找错题:
1.请问下面程序有什么错误?
int a[60][250][1000],i,j,k;
for(k=0;k<=1000;k++)
for(j=0;j<250;j++)
for(i=0;i<60;i++)
a[i][j][k]=0;
把循环语句内外换一下
2.#define Max_CB 500
void LmiQueryCSmd(Struct MSgCB * pmsg)
{
unsigned char ucCmdNum;
......

for(ucCmdNum=0;ucCmdNum<Max_CB;ucCmdNum++)
{
......;
}
死循环
3.以下是求一个数的平方的程序,请找出错误:
#define SQUARE(a)((a)*(a))
int a=5;
int b;
b=SQUARE(a++);
4.typedef unsigned char BYTE
int examply_fun(BYTE gt_len; BYTE *gt_code)
{ 
BYTE *gt_buf;
gt_buf=(BYTE *)MALLOC(Max_GT_Length);
......
if(gt_len>Max_GT_Length)
{
return GT_Length_ERROR; 
}
.......
}
五.问答题:
1.IP Phone的原理是什么?
IPV6
2.TCP/IP通信建立的过程怎样，端口有什么作用？
三次握手，确定是哪个应用程序使用该协议
3.1号信令和7号信令有什么区别，我国某前广泛使用的是那一种？
4.列举5种以上的电话新业务？

微软亚洲技术中心的面试题！！！
1．进程和线程的差别。
线程是指进程内的一个执行单元,也是进程内的可调度实体.
与进程的区别:
(1)调度：线程作为调度和分配的基本单位，进程作为拥有资源的基本单位
(2)并发性：不仅进程之间可以并发执行，同一个进程的多个线程之间也可并发执行
(3)拥有资源：进程是拥有资源的一个独立单位，线程不拥有系统资源，但可以访问隶属于进程的资源. 
(4)系统开销：在创建或撤消进程时，由于系统都要为之分配和回收资源，导致系统的开销明显大于创建或撤消线程时的开销。
2.测试方法 
人工测试：个人复查、抽查和会审
机器测试：黑盒测试和白盒测试

2．Heap与stack的差别。
Heap是堆，stack是栈。
Stack的空间由操作系统自动分配/释放，Heap上的空间手动分配/释放。
Stack空间有限，Heap是很大的自由存储区
C中的malloc函数分配的内存空间即在堆上,C++中对应的是new操作符。
程序在编译期对变量和函数分配内存都在栈上进行,且程序运行过程中函数调用时参数的传递也在栈上进行
3．Windows下的内存是如何管理的？
4．介绍.Net和.Net的安全性。
5．客户端如何访问.Net组件实现Web Service？
6．C/C++编译器中虚表是如何完成的？
7．谈谈COM的线程模型。然后讨论进程内/外组件的差别。
8．谈谈IA32下的分页机制
小页(4K)两级分页模式，大页(4M)一级
9．给两个变量，如何找出一个带环单链表中是什么地方出现环的？
一个递增一，一个递增二，他们指向同一个接点时就是环出现的地方
10．在IA32中一共有多少种办法从用户态跳到内核态？
通过调用门，从ring3到ring0，中断从ring3到ring0，进入vm86等等
11．如果只想让程序有一个实例运行，不能运行两个。像winamp一样，只能开一个窗口，怎样实现？
用内存映射或全局原子（互斥变量）、查找窗口句柄.. 
FindWindow，互斥，写标志到文件或注册表,共享内存。.　 
12．如何截取键盘的响应，让所有的‘a’变成‘b’？
键盘钩子SetWindowsHookEx
　13．Apartment在COM中有什么用？为什么要引入？
　14．存储过程是什么？有什么用？有什么优点？
我的理解就是一堆sql的集合，可以建立非常复杂的查询，编译运行，所以运行一次后，以后再运行速度比单独执行SQL快很多
　15．Template有什么特点？什么时候用？
16．谈谈Windows DNA结构的特点和优点。


网络编程中设计并发服务器，使用多进程 与 多线程 ，请问有什么区别？
1，进程：子进程是父进程的复制品。子进程获得父进程数据空间、堆和栈的复制品。
2，线程：相对与进程而言，线程是一个更加接近与执行体的概念，它可以与同进程的其他线程共享数据，但拥有自己的栈空间，拥有独立的执行序列。
两者都可以提高程序的并发度，提高程序运行效率和响应时间。
线程和进程在使用上各有优缺点：线程执行开销小，但不利于资源管理和保护；而进程正相反。同时，线程适合于在SMP机器上运行，而进程则可以跨机器迁移。

思科
1. 用宏定义写出swap（x，y）
#define swap(x, y)\
x = x + y;\
y = x - y;\
x = x - y;
2.数组a[N]，存放了1至N-1个数，其中某个数重复一次。写一个函数，找出被重复的数字.时间复杂度必须为o（N）函数原型：
int do_dup(int a[],int N)
3 一语句实现x是否为2的若干次幂的判断
int i = 512;
cout << boolalpha << ((i & (i - 1)) ? false : true) << endl;
4.unsigned int intvert(unsigned int x,int p,int n)实现对x的进行转换,p为起始转化位,n为需要转换的长度,假设起始点在右边.如x=0b0001 0001,p=4,n=3转换后x=0b0110 0001
unsigned int intvert(unsigned int x,int p,int n){
unsigned int _t = 0;
unsigned int _a = 1;
for(int i = 0; i < n; ++i){
_t |= _a;
_a = _a << 1;
}
_t = _t << p;
x ^= _t;
return x;
}
 
