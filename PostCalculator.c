#include <string.h>
#include <ctype.h>
#include "ListBaseStack.h"

int EvalRPNExp(char exp[], char exp_n[])
{

	Stack stack;
	Stack num123; //�߰�
	int expLen = strlen(exp);
	int i;
	char tok, op1, op2;
	int a = 1, before = 0, curr; //�߰�
	char tokn, tok_defore;//�߰�

	StackInit(&stack);
	StackInit(&num123);//�߰�
	
	for(i=0; i<expLen; i++)
	{
		tok = exp[i];
		tokn = exp_n[i];

		tok_defore = exp_n[i + 1];
	
		if(isdigit(tok))
		{
			if (tok_defore == 0 && tokn == 0) {//���ڸ� �� ����
				before = 0; 
				a = 1;
				SPush(&stack, tok - '0');     // ���ڷ� ��ȯ�Ͽ� PUSH!
			}
			//========�߰��� �κ�
			if (tok_defore != 0) //���ڸ� �̻� ���� �̸�,
			{
				
				curr = tok - '0'; 
				before = a*before + curr; // ���� : ������ before ���� ������.
				 a = 10; //a �� 10�� ����
			}
			else if (tokn != 0) { //���ڸ� �̻� ���� �����ڸ� ����
				
				curr = tok - '0';
				before = a*before + curr;
				SPush(&stack, before);     // ���ڷ� ��ȯ�Ͽ� PUSH!
				a = 1;
				before = 0;
			}
			//--------------------
		}
		else
		{
			op2 = SPop(&stack);     // ���� ���� ���� �� ��° �ǿ�����!
			op1 = SPop(&stack);

			switch(tok)
			{
			case '+':
				SPush(&stack, op1+op2);
				break;
			case '-':
				SPush(&stack, op1-op2);
				break;
			case '*':
				SPush(&stack, op1*op2);
				break;
			case '/':
				SPush(&stack, op1/op2);
				break;
			}
		}
	}
	return SPop(&stack);
}
