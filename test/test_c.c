#include <stdio.h>
#include <stdlib.h>

struct Foo {
    int n;
    double d[2];
    char *p_c;
}foo1, foo2;

int struct_copy()
{
    char *c = (char *) malloc (4*sizeof(char));
    c[0] = 'a'; c[1] = 'b'; c[2] = 'c'; c[3] = '\0';

    foo1.n = 1;
    foo1.d[0] = 2; 
	foo1.d[1] = 3;
    foo1.p_c = c;

    foo2 = foo1;     //assign foo1 to foo2

    printf("%d %lf %lf %s\n", foo2.n, foo2.d[0], foo2.d[1], foo2.p_c);

	foo1.d[0] = 4;
	foo1.p_c[0] = 'd';

    printf("%d %lf %lf %s\n", foo1.n, foo1.d[0], foo1.d[1], foo1.p_c);
    printf("%d %lf %lf %s\n", foo2.n, foo2.d[0], foo2.d[1], foo2.p_c);

    return 0;
}

/*
 * 嵌套宏
 * 首先，在C语言的宏中是容许嵌套的，其嵌套后，一般的展开规律像函数的参数一样,先展开参数，再分析函数，所以展开顺序是由内而外，
 * 但是当宏中有#则不再展开参数了；如果宏中有##，则先展开函数，再展开里面的参数。
如下面的例子：
它的输出结果为：
"ADDPARAM( 1 )"
PARAM( ADDPARAM( 1 ) )
对于宏TO_STRING，它的定义中没有#，所以先展开里面的“PARAM( ADDPARAM( 1 ) )”，由于PARAM中有#，
所以里面展开的结果为ADDPARAM( 1 )，然后外面再展开，其结果为"ADDPARAM( 1 )"
而对于TO_STRING2，其定义中有#，所以直接展开，其结果为PARAM( ADDPARAM( 1 ) )

 */
#define TO_STRING( x ) TO_STRING1( x )
#define TO_STRING1( x ) #x
#define TO_STRING2( x ) #x
#define PARAM( x ) #x
#define ADDPARAM( x ) INT_##x

int main()
{
    const char * str = TO_STRING(PARAM( ADDPARAM( 1 ) ) );
    printf("%s\n",str);
    str = TO_STRING2(PARAM( ADDPARAM( 1 ) ) );
    printf("%s\n",str);

    return 1;
}
