#include <stdio.h>

int main(void) {
	double price = 24.0f;

	for (int i = 1627; i < 2021; i++) {
		price *= 1.08f;
	}

	printf_s("�� �ݾ� : %.2lf\n", price);

	
	//1�� ������ �Ʒ��� �þ�� �ﰢ��
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < a + 1 ; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}

	printf_s("\n");
	printf_s("\n");
	//2�� �����ʾƷ��� �پ��� �ﰢ��
	for (int a = 0; a < 10; a++) {

		for (int j = 0; j < a + 1; j++) {
			printf_s(" ");
		}
		for (int j = 0; j < 10 - a; j++) {
			printf_s("*");
			
		}
		printf_s("\n");
	}
	
	printf_s("\n");
	printf_s("\n");

	//3�� ���� �Ʒ��� �þ�� �ﰢ��
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < 10 - a; j++) {
			printf_s(" ");
		}
		for (int j = 0; j < a + 1; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}
	

	printf_s("\n");
	printf_s("\n");


	//4�� ���� �Ʒ��� �پ��� �ﰢ��
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < 10 - a; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}
	

	printf_s("\n");
	printf_s("\n");

	//5�� ��
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < a + 1; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < 10 - a; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}

	printf_s("\n");
	printf_s("\n");

	//6�� ��
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < 10 - a; j++) {
			printf_s(" ");
		}
		for (int j = 0; j < a + 1; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}
	for (int a = 0; a < 10; a++) {

		for (int j = 0; j < a + 1; j++) {
			printf_s(" ");
		}
		for (int j = 0; j < 10 - a; j++) {
			printf_s("*");

		}
		printf_s("\n");
	}


	printf_s("\n");
	printf_s("\n");

	//7�� ������
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < 10 - a; j++) {
			printf_s(" ");
		}
		for (int j = 0; j < a + 1; j++) {
			printf_s("**");
		}
		printf_s("\n");
	}
	for (int a = 0; a < 10; a++) {

		for (int j = 0; j < a + 1; j++) {
			printf_s(" ");
		}
		for (int j = 0; j < 10 - a; j++) {
			printf_s("**");

		}
		printf_s("\n");
	}
	
	
}