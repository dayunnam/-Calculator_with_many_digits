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

	return -1;   // 등록되지 않은 연산자
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
	char * num_out = (char*)malloc(expLen + 1); //num에서 숫자가 몇자리인지 정보가 들어감.
	int i, idx = 0;
	char tok, popOp,tokn, popOpn;
	char curr, before; //현재 바로 이전이 숫자인지 아닌지 확인
	char n = 0; //num 에 집어넣을 값
	int idn = 0; //idx 와 같은 역할

	memset(convExp, 0, sizeof(char)*expLen + 1);
	StackInit(&stack);
	StackInit(&num123);
	//==========num1 에 값 저장========================================

	for (i = 0; i<expLen; i++)
	{
		if (i != 0) {
			before = exp[i - 1];
		}

		curr = exp[i]; //현재 문자 저장
		if (isdigit(curr)) //숫자인지 문자인지 확인
		{
			if (isdigit(before)) {//현재 바로 이전의  숫자가 숫자인지 확인
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
		if (isdigit(tok)) //숫자인지 문자인지 확인
		{
			convExp[idx++] = tok;
			num_out[idn++] = tokn; // num 값에 저장
		}
		else
		{
			n = 0;
			switch (tok)
			{
			case '(':
				SPush(&stack, tok);
				SPush(&num123, tokn); //추가
				break;

			case ')':
				while (1)
				{
					popOp = SPop(&stack);
					popOpn = SPop(&num123); //추가
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
					num_out[idn++] = SPop(&num123);//추가
				}
				SPush(&stack, tok);
				SPush(&num123, tokn);//추가
				break;
			}
		}
	}

	while (!SIsEmpty(&stack)) {
		convExp[idx++] = SPop(&stack);
		num_out[idn++] = SPop(&num123);//추가
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