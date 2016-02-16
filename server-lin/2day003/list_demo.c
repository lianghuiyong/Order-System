#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct kool_list
{

	struct list_head list;
	
    /*Ҫά�������� */
	int from;
	int to;
};

int main (int argc, char **argv)
{

	struct kool_list *tmp;
	struct list_head *pos, *q;
	unsigned int i;

   //-----0.����һ���ṹ�����
	struct kool_list mylist;
	
    // ------1.��ʼ������
	INIT_LIST_HEAD (&mylist.list);	/*��ʼ������ͷ */

	/* ��mylist����Ԫ�� */
	for (i = 5; i != 0; --i) {
		tmp = (struct kool_list *) malloc (sizeof (struct kool_list));

		/* ����INIT_LIST_HEAD(&tmp->list); */
		printf ("enter to and from:");
		scanf ("%d %d", &tmp->to, &tmp->from);
		
      //-----2.����Ԫ��
		list_add (&(tmp->list), &(mylist.list));
		/* Ҳ������list_add_tail() �ڱ�β����Ԫ�� */
	}
	printf ("\n");

	printf ("traversing the list using list_for_each()\n");

	/* ��Ӧ��Χ:  ����ı�����������Ӧ���м��б�ɾ����������� */
	list_for_each (pos, &mylist.list) {

		/* ������ pos->next ָ��next �ڵ�, pos->prevָ��ǰһ���ڵ�.����Ľڵ���
		   struct kool_list����. ���ǣ�������Ҫ���ʽڵ㱾��

		   �����ǽڵ��е�list�ֶΣ���list_entry()����Ϊ��Ŀ�ġ� */

		tmp = list_entry (pos, struct kool_list, list);

		printf ("to= %d from= %d\n", tmp->to, tmp->from);

	}
	printf ("\n");
	/* ��Ϊ����ѭ������Ҳ�������෴��˳���������
	 *Ϊ�ˣ�ֻ��Ҫ��'list_for_each_prev'����'list_for_each'��

	 * Ҳ���Ե���list_for_each_entry() �Ը������͵Ľڵ���б�����
	 * ����:
	 */
	printf ("traversing the list using list_for_each_entry()\n");
	list_for_each_entry (tmp, &mylist.list, list)
		printf ("to= %d from= %d\n", tmp->to, tmp->from);
	printf ("\n");

	/*���ڣ����ǿ����ͷ� kool_list�ڵ���.���Ǳ����Ե��� list_del()ɾ���ڵ�Ԫ�أ�

	 * ��Ϊ�˱����������Ĺ�����ɾ��Ԫ�س�����˵�����һ�����Ӱ�ȫ�ĺ� list_for_each_safe()��

	 * ����ԭ�������ķ���*/

	printf ("deleting the list using list_for_each_safe()\n");

#if 0  /* ���´���ǰ����ʵ�ֹ����Ŵ˴�ֻ��Ϊ���Ķ�����ı�����ɾ�����뷽��*/

	struct kool_list *tmp;
	struct list_head *pos, *q;  /*��ʱ���ں�������õ�ָ�룬�����Լ�����ʱ��ʹ�� */


   //-----0.����һ���ṹ�����
	struct kool_list mylist;
	
    // ------1.��ʼ������
	INIT_LIST_HEAD (&mylist.list);	/*��ʼ������ͷ */

#endif

	  //-----3.��������Ԫ��

    /* �Ƽ��ı�������ķ���������Ӧ�ڲ����Ƿ��м�����б�ɾ����������� */
	list_for_each_safe (pos, q, &mylist.list) {
		tmp = list_entry (pos, struct kool_list, list); //tmpָ���������ĳһ��ṹ������
		
		printf ("freeing item to= %d from= %d\n", tmp->to, tmp->from);
		  //-----4.ɾ������Ԫ��
		list_del (pos);
		free (tmp);
	}

	return 0;
}
