#include <stdio.h>
#include <conio.h>
int test01();		// �Լ��� Prototype
void test02(int a);
void test03();
void Dump(char* p, int len);	// �޸� ���� ��¿� �����Լ�
void Copy(char* p1, char* p2);

main()
{
	//test01();
	//test02(1);
	test03();
}

int test01()
{
	char* str[] = { "Zero","One","Two","Three","Four","Five",
		"Six","Seven","Eight","Nine" };  // ���ڿ� ������ �迭
	printf("���� Ű�� �Է��ϼ���. �ش��ϴ� ���ܾ �˷��帮�ڽ��ϴ�.\n");
	printf("���α׷��� �����÷��� 'Q' Ű�� �Է��ϼ���.\n\n");
	int n = 1;
	while (n)
	{
		printf(">");
		char c = getch(); // no echo : Ű���� ������� �ʰ� ��ȯ
		/*/char c1 = getchar();  // [enter] �ʿ�.

		//if (c == '1') printf("%c : One\n", c);
		//else if (c == '2') printf("%c : Two\n", c);
		//else if (c == '3') printf("%c : Three\n", c);
		//else if (c | 0x20 == 'q') break;	// 40H  60H*/
		/*switch (c)
		{
		case '1': printf("%c : One\n", c); break;
		case '2': printf("%c : Two\n", c); break;
		case '3': printf("%c : Three\n", c); break;
		case '4': printf("%c : Four\n", c); break;
		case '5': printf("%c : Five\n", c); break;
		case '6': printf("%c : Six\n", c); break;
		case '7': printf("%c : Seven\n", c); break;
		case '8': printf("%c : Eight\n", c); break;
		case '9': printf("%c : Nine\n", c); break;
		case '0': printf("%c : Zero\n", c); break;
		case 'q':
		case 'Q': n = 0; break;
		}*/
		//int m = c - 0x30;  // ASCII --> num
		printf("%c : %s\n", c, str[c - 0x30]);//str[n][m]
	}
}
void test02(int a)  // ���ڿ��� ���ڹ迭
{
	char ca[] = "Hello"; // ca[0]:'H' ... ca[4]:'o' ca[5]:\0
	for (int i = 0; i < 6; i++) // 0 ~ 5
	{
		printf("ca[%d] : %c (%02x) [%08x]\n", i, ca[i], ca[i], ca + i);
	}
	int ia[] = { 10,20,30,40,50 };
	for (int i = 0; i < 6; i++) // 0 ~ 5
	{
		printf("ia[%d] : %d (%08x) [%08x]\n", i, ia[i], ia[i], ia + i);
	}
	int ia2[2][3] = {10,20,30,40,50,60};
	for (int y = 0; y < 2; y++) // 0 ~ 2
	{
		for (int x = 0; x < 3; x++)
		{
			printf("ia2[%d][%d] : %d [%08x]\n", y, x, ia2[y][x], ia2 + y);
		}
	}
}
void test03()
{
	char buf[100];  // ���� �޸� ���� Ȯ��
	char* pBuf;		// ���� �޸� �������� ��� ��ġ
	unsigned int addr;		// ��� ��ġ ������ ���� �Էº���(�ּ�)
	char kBuf[100];	// ��� ���ڿ� �Է� ����
	printf("���������� �ּҴ� %d[%08x] �Դϴ�.\n", (unsigned int)buf, buf);
	printf("�Է��� ������ �ּҸ� �Է��ϼ��� : ");
	scanf("%d", &addr);  // �������� �ּ� ���� 
	pBuf = buf + addr;
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf("%s", kBuf);
	Copy(pBuf, kBuf);	// ���ڿ� ����
	Dump(buf, 100);
}

void Copy(char* p1, char* p2)
{
	while (*p2) *p1++ = *p2++; *p1 = 0;
}

void Dump(char *p, int len)	// �޸� ���� ��¿� �����Լ�
{
	for (int i = 0; i < len; i++)	// �������� �޸� ����
	{
		if(i % 16 == 0) printf("\n%08x ", p);
		if (i % 8 == 0) printf("  ");
		printf("%02x ", (unsigned char)*p++);
	}
}