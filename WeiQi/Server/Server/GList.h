#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

typedef struct soc_node
{
	SOCKET soc1;
	SOCKET soc2;
	soc_node* next;
}*psoc_node;

//////////////////////
void List_Init(soc_node* head);
void List_Add(soc_node* head,SOCKET soc);
void List_Del(soc_node* head,SOCKET soc);
void List_Rebuild(soc_node* head);
void List_Destroy(soc_node* head);
void List_GetVS(soc_node* head,SOCKET soc,SOCKET *socVS);
//////////////////////

void List_Init(soc_node *head)
{
	//head = new soc_node;
	head->next = NULL;
	head->soc1 = NULL;
	head->soc2 = NULL;
}

void List_Add(soc_node* head,SOCKET soc)
{
	soc_node* p = NULL;
	p = head;

	while(p->next)
	{
		p = p->next;
		if(p->soc1 != NULL && p->soc2 == NULL)
		{
			p->soc2 = soc;
			return;
		}
		else if(p->soc1 == NULL && p->soc2 != NULL)
		{
			p->soc1 = soc;
			return;
		}
	}

	psoc_node s = new soc_node;
	s->next = NULL;
	s->soc1 = soc;
	s->soc2 = NULL;

	p->next = s;
}

void List_Del(soc_node* head,SOCKET soc)
{
	psoc_node s = NULL;
	psoc_node p = NULL;

	p = head;
	while(p->next)
	{
		s = p;
		p = p->next;
		if(p->soc1 == soc)
		{
			if(p->soc2 == NULL)
			{
				s->next = p->next;
				delete p;
				return;
			}
			else
			{
				p->soc1 = NULL;
				return;
			}
		}
		else if(p->soc2 == soc)
		{
			if(p->soc1 == NULL)
			{
				s->next = p->next;
				delete p;
			}
			else
			{
				p->soc2 = NULL;
			}
			return;
		}
	}
}

void List_Rebuild(psoc_node head)
{
	psoc_node pBefore = NULL;
	psoc_node p = NULL;

	p = head;
	while(p->next)
	{
		p = p->next;
		if(p->soc1 == NULL || p->soc2 == NULL)
		{
			if(pBefore != NULL)
			{
				if(pBefore->soc1 == NULL)
				{
					if(p->soc1 == NULL)
					{
						pBefore->soc1 = p->soc2;
					}
					else
					{
						pBefore->soc1 = p->soc1;
					}
					pBefore = NULL;
				}
				else
				{
					if(p->soc1 == NULL)
					{
						pBefore->soc2 = p->soc2;
					}
					else
					{
						pBefore->soc2 = p->soc1;
					}
					pBefore = NULL;
				}
			}
			else 
			{
				pBefore = p;
			}
		}
	}
}

void List_Destroy(soc_node* head)
{
	psoc_node p = NULL;
	
	p = head;
	while(p->next)
	{
		p = p->next;
		delete head;
		head = p;
	}
}

void List_GetVS(soc_node* head,SOCKET soc,SOCKET *socVS)
{
	psoc_node p = NULL;

	p = head;
	while(p->next)
	{
		p = p->next;
		if(p->soc1 == soc)
		{
			*socVS = p->soc2;
			break;
		}
		else if(p->soc2 == soc)
		{
			*socVS = p->soc1;
			break;
		}
	}
}