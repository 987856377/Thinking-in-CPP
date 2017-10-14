/*
1 malloc函数
	extern void* malloc(unsigned int num_bytes)
	函数的功能是分配长度是num_bytes字节的内存块，如果分配成功则返回指向
	分配内存的指针，如果分配失败返回空指针
	malloc只管分配内存，并不能对所得的内存进行初始化，所以得到的一片新内存中，其值将是随机的。

2 calloc函数
	void* calloc(unsigned n,unsigned size)
	函数功能：在内存的动态存储区中分配n个长度为size的连续空间，函数返回
	一个指向分配起始地址的指针，如果分配不成功，返回NULL。
	跟malloc的区别：calloc在动态分配完内存后，自动初始化分配空间为零，
	而malloc不初始化，里面的数据是随机的垃圾数据。

3 realloc函数
	extern void* realloc(void* mem_address,unsigned int newsize)
	函数功能：先按照newsize指定的大小分配空间，将原有数据从头到尾拷贝到
	新分配的内存区域，而后释放原来的mem_address所指内存区域，同时返回新
	分配的内存区域的首地址
	如果重新分配成功则返回指向被分配的内存指针，否则返回空指针NULL
	1.realloc失败的时候，返回NULL
	2.realloc失败的时候，原来的内存不改变，不会释放也不会移动
	3.假如原来的内存后面还有足够多剩余内存的话，realloc的内存=原来的内
		存+剩余内存,realloc还是返回原来内存的地址;假如原来的内存后面没有足
		够多剩余内存的话，realloc将申请新的内存，然后把原来的内存数据拷贝
		到新内存里，原来的内存将被free掉,realloc返回新内存的地址
	4.如果size为0，效果等同于free()。这里需要注意的是只对指针本身进行
		释放，例如对二维指针**a，对a调用realloc时只会释放一维，使用时谨防内存泄露。
	5.传递给realloc的指针必须是先前通过malloc(),calloc(),或realloc()分配的
	6.传递给realloc的指针可以为空，等同于malloc。
	
注意:
	如果不再使用的内存可以使用free函数释放掉
	C,C++规定，void*类型可以强制转换为任何其它类型的指针
	void*表示未确定类型的指针，更明确的说是指申请内存空间时还不知道用户是
	用这段空间来存储什么类型的数据。
	
                    有了malloc/free为什么还要new/delete？

malloc与free是C++/C语言的标准库函数，new/delete是C++的运算符。它们都可用于申请动态内存和释放内存。

对于非内部数据类型的对象而言，光用 maloc/free 无法满足动态对象的要求。
	对象在创建的同时要自动执行构造函数，对象在消亡之前要自动执行析构函数。
	由于malloc/free是库函数而不是运算符，不在编译器控制权限之内，
	不能够把执行构造函数和析构函数的任务强加于 malloc/free。

C++语言需要运算符 new 完成动态内存分配和初始化工作，运算符 delete 能完成清理与释放内存工作的。

*/
#include<iostream>
#include<cstdlib>
using namespace std;

int main(){
	
	//malloc
	int *p1 = (int*)malloc(sizeof(int)*10);		//分配存储十个整型数据的内存 
	if(!p1){
		cout<<"Malloc Memery Error!!!"<<endl;
		exit(1);
	}
	for(int i=0;i<10;++i){
		p1[i]=i;
	}
	for(int i=0;i<10;++i){
		cout<<p1[i]<<" ";
	}
	cout<<"\n首个元素的内存地址："<<&p1[0]<<endl;
	cout<<"最后元素的内存地址："<<&p1[9]<<endl;
	free(p1);
	
	//calloc
	int *p2 = (int*)calloc(10,sizeof(int));
	if(!p2){
		cout<<"Malloc Memery Error!!!"<<endl;
		exit(1);
	}
	for(int i=0;i<10;++i){
		p2[i]=i;
	}
	for(int i=0;i<10;++i){
		cout<<p2[i]<<" ";
	}
	cout<<"\n首个元素的内存地址："<<&p2[0]<<endl;
	cout<<"最后元素的内存地址："<<&p2[9]<<endl;	
	
	//realloc
	int *p3 = (int*)realloc(p2,20);
	if(!p3){
		cout<<"Malloc Memery Error!!!"<<endl;
		exit(1);
	}
	for(int i=10;i<20;++i){
		p3[i] = i;
	}
	for(int i=0;i<20;++i){
		cout<<p3[i]<<" ";
	}
	cout<<"\n首个元素的内存地址："<<&p3[0]<<endl;
	cout<<"最后元素的内存地址："<<&p3[19]<<endl;
	free(p2);
	free(p3);
	
	return 0;
}
/*

1 、内存分配方式

　　内存分配方式有三种：
　　（1）从静态存储区域分配。
        内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在。
		例如全局变量，static变量。

　　（2）在栈上创建。
		在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。
		栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限。

　　（3）从堆上分配，亦称动态内存分配。
		程序在运行的时候用malloc或new申请任意多少的内存，程序员自己负责在何时用free或delete释放内存。
		动态内存的生存期由我们决定，使用非常灵活，但问题也最多。

2、常见的内存错误及其对策

	发生内存错误是件非常麻烦的事情。编译器不能自动发现这些错误，通常是在程序运行时才能捕捉到。
		而这些错误大多没有明显的症状，时隐时现，增加了改错的难度。
		有时用户怒气冲冲地把你找来，程序却没有发生任何问题，你一走，错误又发作了。
		
常见的内存错误及其对策如下：

* 内存分配未成功，却使用了它。
　　编程新手常犯这种错误，因为他们没有意识到内存分配会不成功。
	常用解决办法是，在使用内存之前检查指针是否为NULL。
	如果指针p是函数的参数，那么在函数的入口处用assert(p!=NULL)进行检查。
	如果是用malloc或new来申请内存，应该用if(p==NULL)或if(p!=NULL)进行防错处理。

* 内存分配虽然成功，但是尚未初始化就引用它。

　　犯这种错误主要有两个起因：
		一是没有初始化的观念；
		二是误以为内存的缺省初值全为零，导致引用初值错误（例如数组）。
			内存的缺省初值究竟是什么并没有统一的标准，尽管有些时候为零值，我们宁可信其无不可信其有。
			所以无论用何种方式创建数组，都别忘了赋初值，即便是赋零值也不可省略，不要嫌麻烦。

* 内存分配成功并且已经初始化，但操作越过了内存的边界。

　　例如在使用数组时经常发生下标“多1”或者“少1”的操作。
	特别是在for循环语句中，循环次数很容易搞错，导致数组操作越界。

* 忘记了释放内存，造成内存泄露。

　　含有这种错误的函数每被调用一次就丢失一块内存。
	刚开始时系统的内存充足，你看不到错误。终有一次程序突然死掉，系统出现提示：内存耗尽。

　　动态内存的申请与释放必须配对，程序中malloc与free的使用次数一定要相同，否则肯定有错误（new/delete同理）。

* 释放了内存却继续使用它。

　　有三种情况：

　　（1）程序中的对象调用关系过于复杂，实在难以搞清楚某个对象究竟是否已经释放了内存，
		此时应该重新设计数据结构，从根本上解决对象管理的混乱局面。

　　（2）函数的return语句写错了，注意不要返回指向“栈内存”的“指针”或者“引用”，
		因为该内存在函数体结束时被自动销毁。

　　（3）使用free或delete释放了内存后，没有将指针设置为NULL。导致产生“野指针”。

　　【规则1】用malloc或new申请内存之后，应该立即检查指针值是否为NULL。防止使用指针值为NULL的内存。

　　【规则2】不要忘记为数组和动态内存赋初值。防止将未被初始化的内存作为右值使用。

　　【规则3】避免数组或指针的下标越界，特别要当心发生“多1”或者“少1”操作。

　　【规则4】动态内存的申请与释放必须配对，防止内存泄漏。

　　【规则5】用free或delete释放了内存之后，立即将指针设置为NULL，防止产生“野指针”。

3、指针与数组的对比

C++/C程序中，指针和数组在不少地方可以相互替换着用，让人产生一种错觉，以为两者是等价的。

　　数组要么在静态存储区被创建（如全局数组），要么在栈上被创建。
	数组名对应着（而不是指向）一块内存，其地址与容量在生命期内保持不变，只有数组的内容可以改变。

　　指针可以随时指向任意类型的内存块，它的特征是“可变”，所以我们常用指针来操作动态内存。
		指针远比数组灵活，但也更危险。

5 、杜绝 “ 野指针 ”
 
“野指针”不是NULL指针，是指向“垃圾”内存的指针。
	人们一般不会错用NULL指针，因为用if语句很容易判断。但是“野指针”是很危险的，if语句对它不起作用。
	
“野指针”的成因主要有两种：

　　（1）指针变量没有被初始化。任何指针变量刚被创建时不会自动成为NULL指针，它的缺省值是随机的，它会乱指一气。
		所以，指针变量在创建的同时应当被初始化，要么将指针设置为NULL，要么让它指向合法的内存。
	
	（2）指针p被free或者delete之后，没有置为NULL，让人误以为p是个合法的指针。

　　（3）指针操作超越了变量的作用范围。

7 、内存耗尽怎么办？
如果在申请动态内存时找不到足够大的内存块，malloc和new将返回NULL指针，宣告内存申请失败。

通常有三种方式处理“内存耗尽”:
 
（1）判断指针是否为NULL，如果是则马上用return语句终止本函数。

（2）判断指针是否为NULL，如果是则马上用exit(1)终止整个程序的运行。
 
（3）为new和malloc设置异常处理函数。
	例如Visual C++可以用_set_new_hander函数为new设置用户自己定义的异常处理函数，
	也可以让malloc享用与new相同的异常处理函数。

既然new/delete的功能完全覆盖了malloc/free，为什么C++不把malloc/free淘汰出局呢？
	这是因为C++程序经常要调用C函数，而C程序只能用malloc/free管理动态内存。
	如果用free释放“new创建的动态对象”，那么该对象因无法执行析构函数而可能导致程序出错。
	如果用delete释放“malloc申请的动态内存”，理论上讲程序不会出错，但是该程序的可读性很差。
	
所以new/delete必须配对使用，malloc/free也一样。
*/ 

