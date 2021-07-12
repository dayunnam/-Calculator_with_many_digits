#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ListBaseStack.h"
#pragma warning ( disable : 4996 )

int GetOpPrec(char op)
{
	switch (op)
	{
	case '*':
	case '/':
		return 5;
	case '+':
	case '-':
		return 3;
	case '(':
		return 1;
	}

	return -1;   // ��ϵ��� ���� ������
}

int WhoPrecOp(char op1, char op2)
{
	int op1Prec = GetOpPrec(op1);
	int op2Prec = GetOpPrec(op2);

	if (op1Prec > op2Prec)
		return 1;
	else if (op1Prec < op2Prec)
		return -1;
	else
		return 0;
}

char* ConvToRPNExp(char exp[])
{
	Stack stack;
	Stack num123;
	int expLen = strlen(exp);
	char * convExp = (char*)malloc(expLen + 1); 
	char * num_in = (char*)malloc(expLen + 1);
	char * num_out = (char*)malloc(expLen + 1); //num���� ���ڰ� ���ڸ����� ������ ��.
	int i, idx = 0;
	char tok, popOp,tokn, popOpn;
	char curr, before; //���� �ٷ� ������ �������� �ƴ��� Ȯ��
	char n = 0; //num �� ������� ��
	int idn = 0; //idx �� ���� ����

	memset(convExp, 0, sizeof(char)*expLen + 1);
	StackInit(&stack);
	StackInit(&num123);
	//==========num1 �� �� ����========================================

	for (i = 0; i<expLen; i++)
	{
		if (i != 0) {
			before = exp[i - 1];
		}

		curr = exp[i]; //���� ���� ����
		if (isdigit(curr)) //�������� �������� Ȯ��
		{
			if (isdigit(before)) {//���� �ٷ� ������  ���ڰ� �������� Ȯ��
				++n;
			}
			else {
				n = 0;
			}
		}
		else
		{
			n = 0;
		}
		num_in[idn++] = n;
	}
	idn = 0;

	

	//=================================================================


	for (i = 0; i<expLen; i++)
	{
		tok = exp[i];
		tokn = *(num_in + i);
		if (isdigit(tok)) //�������� �������� Ȯ��
		{
			convExp[idx++] = tok;
			num_out[idn++] = tokn; // num ���� ����
		}
		else
		{
			n = 0;
			switch (tok)
			{
			case '(':
				SPush(&stack, tok);
				SPush(&num123, tokn); //�߰�
				break;

			case ')':
				while (1)
				{
					popOp = SPop(&stack);
					popOpn = SPop(&num123); //�߰�
					if (popOp == '(')
						break;
					convExp[idx++] = popOp;
					num_out[idn++] = popOpn;
				}
				break;

			case '+': case '-':
			case '*': case '/':
				while (!SIsEmpty(&stack) &&
					WhoPrecOp(SPeek(&stack), tok) >= 0) {
					convExp[idx++] = SPop(&stack);
					num_out[idn++] = SPop(&num123);//�߰�
				}
				SPush(&stack, tok);
				SPush(&num123, tokn);//�߰�
				break;
			}
		}
	}

	while (!SIsEmpty(&stack)) {
		convExp[idx++] = SPop(&stack);
		num_out[idn++] = SPop(&num123);//�߰�
	}
	strcpy(exp, convExp);
	//strcpy(exp_num, num_out);
//	exp_num = num_out;
	
	return num_out;
	free(convExp);
	free(num_in);
	free(num_out);
	//return num_out;
}