#include <string.h>
#include <stdlib.h>
#include "InfixToPostfix.h"
#include "PostCalculator.h"
#pragma warning ( disable : 4996 )

int EvalInfixExp(char exp[])
{
	int len = strlen(exp);
	int ret;
	int i;//test 용
	char * expcpy = (char*)malloc(len+1);
	char * expcpy_n = (char*)malloc(len + 1); //추가
	strcpy(expcpy, exp);

	expcpy_n =  ConvToRPNExp(expcpy);    
	ret = EvalRPNExp(expcpy,expcpy_n); //**

	free(expcpy);
	free(expcpy_n);//추가
	return ret;
}
