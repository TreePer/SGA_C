#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>

// 상수 선언
const int PLAYER = 0;
const int ENEMY = 1;
const int MAX = 2;

// 플레이어, 몬스터의 정보를 넣을 구조체 선언
typedef struct tagInfo {
	char* Name;
	int HP;
	int MP;

	int EXP;

	float Att;
	float Def;

	int Level;

}INFO;

// tagInfo(INFO)구조체를 변수로 가지는 구조체 선언
typedef struct tagObject {
	INFO Info;

}OBJECT;



// 함수 전방선언
void InitializeObject(OBJECT* _Obj, int ObjectType);
char* SetName();


int main(void) {
	/*
	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Player, TYPE_PLAYER);
	OBJECT* Enemy = (OBJECT*)malloc(sizeof(OBJECT));;
	InitializeObject(Enemy, TYPE_ENEMY);
	*/

	// 구조체 포인터 생성
	OBJECT* Objects[MAX];
	// 구조체 플레이어 초기화
	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[PLAYER], PLAYER);
	// 구조체 몬스터 초기화
	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[ENEMY], ENEMY);
	// 도망기능에서 사용할 랜덤 변수 선언
	int dice;


	while (true) {
		// ** 콘솔창을 모두 지움.
		system("cls");

		printf_s("\n[%s]\n", Objects[PLAYER]->Info.Name);
		printf_s("HP : %d\n", Objects[PLAYER]->Info.HP);
		printf_s("MP : %d\n", Objects[PLAYER]->Info.MP);
		printf_s("공격력 : %.2f\n", Objects[PLAYER]->Info.Att);
		printf_s("방어력 : %.2f\n", Objects[PLAYER]->Info.Def);
		printf_s("EXP : %d\n", Objects[PLAYER]->Info.EXP);
		printf_s("Level : %d\n\n", Objects[PLAYER]->Info.Level);
		// 0.5초의 딜레이
		Sleep(500);

		printf_s("[%s]\n", Objects[ENEMY]->Info.Name);
		printf_s("HP : %d\n", Objects[ENEMY]->Info.HP);
		printf_s("MP : %d\n", Objects[ENEMY]->Info.MP);
		printf_s("공격력 : %.2f\n", Objects[ENEMY]->Info.Att);
		printf_s("방어력 : %.2f\n", Objects[ENEMY]->Info.Def);
		printf_s("EXP : %d\n", Objects[ENEMY]->Info.EXP);
		printf_s("Level : %d\n\n", Objects[ENEMY]->Info.Level);

		Sleep(500);
		// 선택지
		int iChoice = 0;
		printf_s("몬스터와 만났습니다. 공격하시겠습니까 ?\n1. 공격\n2. 도망\n입력 : ");
		scanf_s("%d", &iChoice);
		// switch문을 이용해 분기를 나눔
		switch (iChoice) {
		case 1 : // '1'일경우
			if (Objects[PLAYER]->Info.Att > Objects[ENEMY]->Info.Def) { // 플레이어의 공격력과 몬스터의 방어력을 비교
				Objects[ENEMY]->Info.HP -= Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def; // 공격력 > 방어력일 경우 공격력 - 방어력의 수치만큼 데미지를줌
				printf_s("%d의 데미지를 몬스터에게 주었습니다.\n", (int)(Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def)); // 데미지를 표시 HP의 값이 int이므로 int로 형변환
				Sleep(500);
			}
			else { 
				Objects[ENEMY]->Info.HP -= 1; // 공격력 < 방어력일 경우 1의 데미지를 줌
				printf_s("1의 데미지를 몬스터에게 주었습니다.\n");
				Sleep(500);
			}
			// 플레이어의 공격이 끝나고 몬스터도 공격함
			if (Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def) {  // 몬스터의 공격력과 플레이어의 방어력을 비교
				Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def; // 공격력 > 방어력일 경우 공격력 - 방어력의 수치만큼 데미지를줌
				printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", (int)(Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def));
				Sleep(500);
			}
			else {
				Objects[PLAYER]->Info.HP -= 1;
				printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
				Sleep(500);
			}
			
			break;
		case 2 : // '2'일경우
			dice = (int)rand % 2; // 랜덤함수를 이용해 0, 1의 값이 나오게함
			
			if (dice) { // 1일경우
				printf_s("도망치는것에 [성공] 했습니다.\n"); 
				InitializeObject(Objects[ENEMY], ENEMY); // 도망치는것을 성공, 새로운 몬스터를 등장시킴
				Sleep(500);
			}
			else { // 0일경우
				printf_s("도망치는것에 [실패] 했습니다.\n");  // 도망치는것에 실패, 몬스터에게 데미지를 입음
				if (Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def) {
					Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def;
					printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", (int)(Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def));
				}
				else {
					Objects[PLAYER]->Info.HP -= 1;
					printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
				}
				Sleep(500);
			}
			
			break;

		default : // 다른 숫자를 입력했을경우
			printf_s("잘못된 입력입니다. 다시 입력하세요. \n");
			Sleep(500);
		}
	}

	return 0;
}



// 플레이어와 몬스터의 데이터를 구조체에 등록시키는 함수
void InitializeObject(OBJECT* _Obj, int ObjectType)
{
	switch (ObjectType) {
	case PLAYER : // 플레이어일경우
		_Obj->Info.Name = SetName(); // SetName함수에서 입력받은 이름을 저장

		_Obj->Info.Att = 10;
		_Obj->Info.Def = 10;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 100;
		_Obj->Info.MP = 10;
		_Obj->Info.Level = 1;
		break;
	case ENEMY : // 몬스터일 경우
		_Obj->Info.Name = (char*)"Enemy";

		_Obj->Info.Att = 5;
		_Obj->Info.Def = 5;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 30;
		_Obj->Info.MP = 5;
		_Obj->Info.Level = 1;
		break;
	}
}

char* SetName() { // 이름을 입력받는 함수
	char Buffer[128] = ""; // 이름을 입력받을 공간을 배열로 생성

	printf_s("이름 입력 : ");
	scanf("%s", Buffer);

	char* pName = (char*)malloc(strlen(Buffer) + 1); // 포인터 변수에게 입력받은 이름의 글자수만큼 동적할당
	strcpy(pName, Buffer); // 포인터에 이름을 전달함

	return pName; // 입력받은 이름이 저장된 포인터 반환
}