#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct kool_list
{

	struct list_head list;
	
    /*要维护的数据 */
	int from;
	int to;
};

int main (int argc, char **argv)
{

	struct kool_list *tmp;
	struct list_head *pos, *q;
	unsigned int i;

   //-----0.定义一个结构体变量
	struct kool_list mylist;
	
    // ------1.初始化链表
	INIT_LIST_HEAD (&mylist.list);	/*初始化链表头 */

	/* 给mylist增加元素 */
	for (i = 5; i != 0; --i) {
		tmp = (struct kool_list *) malloc (sizeof (struct kool_list));

		/* 或者INIT_LIST_HEAD(&tmp->list); */
		printf ("enter to and from:");
		scanf ("%d %d", &tmp->to, &tmp->from);
		
      //-----2.增加元素
		list_add (&(tmp->list), &(mylist.list));
		/* 也可以用list_add_tail() 在表尾增加元素 */
	}
	printf ("\n");

	printf ("traversing the list using list_for_each()\n");

	/* 适应范围:  下面的遍历方法不适应于中间有被删除过项的链表 */
	list_for_each (pos, &mylist.list) {

		/* 在这里 pos->next 指向next 节点, pos->prev指向前一个节点.这里的节点是
		   struct kool_list类型. 但是，我们需要访问节点本身，

		   而不是节点中的list字段，宏list_entry()正是为此目的。 */

		tmp = list_entry (pos, struct kool_list, list);

		printf ("to= %d from= %d\n", tmp->to, tmp->from);

	}
	printf ("\n");
	/* 因为这是循环链表，也可以以相反的顺序遍历它，
	 *为此，只需要用'list_for_each_prev'代替'list_for_each'，

	 * 也可以调用list_for_each_entry() 对给定类型的节点进行遍历。
	 * 例如:
	 */
	printf ("traversing the list using list_for_each_entry()\n");
	list_for_each_entry (tmp, &mylist.list, list)
		printf ("to= %d from= %d\n", tmp->to, tmp->from);
	printf ("\n");

	/*现在，我们可以释放 kool_list节点了.我们本可以调用 list_del()删除节点元素，

	 * 但为了避免遍历链表的过程中删除元素出错，因此调用另一个更加安全的宏 list_for_each_safe()，

	 * 具体原因见后面的分析*/

	printf ("deleting the list using list_for_each_safe()\n");

#if 0  /* 以下代码前面有实现过，放此处只是为了阅读下面的遍历和删除代码方便*/

	struct kool_list *tmp;
	struct list_head *pos, *q;  /*临时被内核链表借用的指针，我们自己遍历时不使用 */


   //-----0.定义一个结构体变量
	struct kool_list mylist;
	
    // ------1.初始化链表
	INIT_LIST_HEAD (&mylist.list);	/*初始化链表头 */

#endif

	  //-----3.遍历链表元素

    /* 推荐的遍历链表的方法，它适应于不管是否中间过程有被删除过项的链表 */
	list_for_each_safe (pos, q, &mylist.list) {
		tmp = list_entry (pos, struct kool_list, list); //tmp指向遍历到的某一项结构体数据
		
		printf ("freeing item to= %d from= %d\n", tmp->to, tmp->from);
		  //-----4.删除链表元素
		list_del (pos);
		free (tmp);
	}

	return 0;
}
