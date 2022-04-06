#include <stdio.h>

int main(void) {
	double price = 24.0f;

	for (int i = 1627; i < 2021; i++) {
		price *= 1.08f;
	}

	printf_s("총 금액 : %.2lf\n", price);

	
	//1번 오른쪽 아래로 늘어나는 삼각형
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < a + 1 ; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}

	printf_s("\n");
	printf_s("\n");
	//2번 오른쪽아래로 줄어드는 삼각형
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

	//3번 왼쪽 아래로 늘어나는 삼각형
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


	//4번 왼쪽 아래로 줄어드는 삼각형
	for (int a = 0; a < 10; a++) {
		for (int j = 0; j < 10 - a; j++) {
			printf_s("*");
		}
		printf_s("\n");
	}
	

	printf_s("\n");
	printf_s("\n");

	//5번 ▶
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

	//6번 ◀
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

	//7번 마름모
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