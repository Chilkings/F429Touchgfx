#ifndef __MALLOC_H
#define __MALLOC_H
/* USER CODE BEGIN PTD */
#include "stm32f4xx_it.h"
#include "stdint.h"

//#include "sys.h"
#ifndef NULL
#define NULL 0
#endif

#define MEM_BLOCK_SIZE			  32  	  					          //�ڴ���СΪ32�ֽ�
#define MEM_MAX_SIZE			    16*2048  						        //�������ڴ� 2K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE //�ڴ���С
		 
//�ڴ���������
struct _m_mallco_dev
{
	void (*init)(void);					//��ʼ��
	uint8_t   (*perused)(void);		  	    	//�ڴ�ʹ����
	uint8_t 	  *membase;					//�ڴ��
	uint16_t   *memmap; 					//�ڴ����״̬��
	uint8_t     memrdy; 						//�ڴ�����Ƿ����
};

extern struct _m_mallco_dev mallco_dev;	 //��mallco.c���涨��

void mymemset(void *s,uint8_t c,uint32_t count);	 //�����ڴ�
void mymemcpy(void *des,void *src,uint32_t n);//�����ڴ� 

void mem_init(void);					 			//�ڴ�����ʼ������
uint32_t mem_malloc(uint32_t size);		 				//�ڴ����
uint8_t mem_free(uint32_t offset);		 				//�ڴ��ͷ�
uint8_t mem_perused(void);				 				//����ڴ�ʹ���� 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void myfree(void *ptr);  						//�ڴ��ͷ�
void *mymalloc(uint32_t size);						//�ڴ����
void *myrealloc(void *ptr,uint32_t size);//���·����ڴ�
#endif














