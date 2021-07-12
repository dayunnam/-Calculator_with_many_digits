#include <string.h>
#include <ctype.h>
#include "ListBaseStack.h"

int EvalRPNExp(char exp[], char exp_n[])
{

	Stack stack;
	Stack num123; //추가
	int expLen = strlen(exp);
	int i;
	char tok, op1, op2;
	int a = 1, before = 0, curr; //추가
	char tokn, tok_defore;//추가

	StackInit(&stack);
	StackInit(&num123);//추가
	
	for(i=0; i<expLen; i++)
	{
		tok = exp[i];
		tokn = exp_n[i];

		tok_defore = exp_n[i + 1];
	
		if(isdigit(tok))
		{
			if (tok_defore == 0 && tokn == 0) {//한자리 수 숫자
				before = 0; 
				a = 1;
				SPush(&stack, tok - '0');     // 숫자로 변환하여 PUSH!
			}
			//========추가한 부분
			if (tok_defore != 0) //한자리 이상 숫자 이면,
			{
				
				curr = tok - '0'; 
				before = a*before + curr; // 문제 : 이전의 before 값이 곱해짐.
				 a = 10; //a 에 10을 곱함
			}
			else if (tokn != 0) { //한자리 이상 수의 일의자리 숫자
				
				curr = tok - '0';
				before = a*before + curr;
				SPush(&stack, before);     // 숫자로 변환하여 PUSH!
				a = 1;
				before = 0;
			}
			//--------------------
		}
		else
		{
			op2 = SPop(&stack);     // 먼저 꺼낸 값이 두 번째 피연산자!
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
