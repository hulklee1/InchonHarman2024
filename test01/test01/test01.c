#include <stdio.h>
#include <conio.h>
int test01();		// �Լ��� Prototype
void test02(int a);

main()
{
	//test01();
	test02(1);
}

int test01()
{
	char* str[] = {"Zero","One","Two","Three","Four","Five",
		"Six","Seven","Eight","Nine"};  // ���ڿ� ������ �迭
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
		printf("%c : %s\n", c, str[c - 0x30]);
	}	         
}
void test02(int a)  // ���ڿ��� ���ڹ迭
{
	char ca[] = "Hello"; // ca[0]:'H' ... ca[4]:'o' ca[5]:\0
	for (int i = 0; i < 10; i++) // 0 ~ 5
	{
		printf("ca[%d] : %c (%02x)\n", i, ca[i], ca[i]);
	}
	ca[2] -= 1;
	ca[3] -= 1;
	for (int i = 0; i < 10; i++) // 0 ~ 5
	{
		printf("ca[%d] : %c (%02x)\n", i, ca[i], ca[i]);
	}
}
