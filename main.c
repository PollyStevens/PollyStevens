#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	struct Group												//struct grp;
	{
		long long int inp;
		long long int outp;
		long int inm;
		long int outm;
		int pc;
	}grp;
	FILE* pac, * rule, * ans;										//����ָ��
	char s1[30], s2[30];										//����ļ���
	int i, flag;														//��ǵڼ���
	scanf("./main%s%s", s2, s1);								//�����ļ���
	if ((pac = fopen(s1, "r")) == NULL)							//open rule; 
	{
		printf("Can not open this file!");
		exit(0);
	}
	if ((ans = fopen("res.txt", "w")) == NULL)					//open res;
	{
		printf("Can not open this file!");
		exit(0);
	}
	if ((rule = fopen(s2, "r")) == NULL)					//open rule;
	{
		printf("Can not open this file!");
		exit(0);
	}
	while (!feof(pac))
	{
		fscanf(pac, "%lld%lld%ld%ld%d",
			&grp.inp, &grp.outp, &grp.inm, &grp.outm, &grp.pc); //read packet��
		rewind(rule);											//�ļ�λ�ûص���ʼ����
		long long int a, b, c, d, sum, les;
		i = 0;													//ʹi�ص�0��
		while (!feof(rule))
		{
			flag = 0;
			fscanf(rule, "@%lld.%lld.%lld.%lld/%lld", &a, &b, &c, &d, &les);		//read rule;
			//fscanf(rule, "\n");												//read /n;
			sum = (long long int)(d + c * pow(2, 8) + b * pow(2, 16) + a * pow(2, 24));
			a = pow(2, 32 - les);
			sum = sum - sum % a;
			b = grp.inp - grp.inp % a;
			if (sum == b)		flag--;																//compare first ip;
			fscanf(rule, "%lld.%lld.%lld.%lld/%lld", &a, &b, &c, &d, &les);	//read rule;
			sum = (long long int) (d + c * pow(2, 8) + b * pow(2, 16) + a * pow(2, 24));
			a = pow(2, 32 - les);
			sum = sum - sum % a;
			b = grp.outp - grp.outp % a;
			if (sum == b)	flag--;															//compare second ip;
			fscanf(rule, "%lld :%lld%lld :%lld", &a, &b, &c, &d);										//compre third;
			if (a <= grp.inm && grp.inm <= b && c <= grp.outm && grp.outm <= d)		flag--;
			char e, f, g, h;
			fscanf(rule, "%d", &les);																		//��F��0��
			fscanf(rule, "x%c%c/0x%c%c\n", &g, &h, &e, &f);
			a = g - '0';
			b = h - '0';
			if (e == '0')	flag--;														//compare fourth;
			else if (a * 10 + b == grp.pc)
			{
				flag--;
			}
			if (flag == -4)
			{
				fprintf(ans, "%d\n", i);
				flag--;
				break;
			}
			i++;
		}
		if (flag != -5) fprintf(ans, "-1\n");									//�޷�ƥ�䣬���-1��
		fscanf(pac, "\n");										//��ȡ�س�
	}
	fclose(pac);												//close pac;
	fclose(rule);												//close rule;
	fclose(ans);
	return 0;
}