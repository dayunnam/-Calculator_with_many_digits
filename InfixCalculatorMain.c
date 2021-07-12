/*
#include <stdio.h>
#include "InfixCalculator.h"

int main(void)
{
	char exp1[] = "1+2*3";
	char exp2[] = "(1+2)*3";
	char exp3[] = "((1-2)+3)*(5-2)";

	printf("%s = %d \n", exp1, EvalInfixExp(exp1));
	printf("%s = %d \n", exp2, EvalInfixExp(exp2));
	printf("%s = %d \n", exp3, EvalInfixExp(exp3));
	return 0;
}

*/
#include <stdio.h>
#include "InfixCalculator.h"
#include<string.h>
#define STRING_LEN	100
#define MAX_TEST_LEN	50

int main(void)
{
	int C;// 데스트 케이스 개수 
	char in_s[STRING_LEN];
	int out; //출력 문자열
	int i;
	printf("test case 개수 입력 : ");
	scanf_s("%d", &C);//테스트 케이스 입력 받음
	for (i = 0; i< C; i++)
	{
		printf("수식 입력 : ");
		scanf_s("%s", in_s, (int)sizeof(char)*STRING_LEN);
		printf("\n");
		out = EvalInfixExp(in_s);
		printf("%s = %d \n", in_s, out);
	}
	return 0;

}
