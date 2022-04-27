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

const int Scene_Logo = 0;
const int Scene_Menu = 1;
const int Scene_Stage = 2;
const int Scene_Exit = 3;

// 전역 변수 선언

int SceneState = 0;

int Check = 1;


// 구조체 선언

typedef struct tagInfo {
	char* Name;

	int HP;
	
	int EXP;

	float Att;
	float Def;
	float speed;

	int Level;

	char* skillname1;
	int skillpp1;
	int skillpoint1;

	char* skillname2;
	int skillpp2;
	int skillpoint2;

	char* skillname3;
	int skillpp3;
	int skillpoint3;

	char* skillname4;
	int skillpp4;
	int skillpoint4;

}INFO;

typedef struct userInfo {
	char* userName;

	INFO info1;
	INFO info2;
	INFO info3;
	INFO info4;
	INFO info5;
	INFO info6;
}USER;

typedef struct tagObject {
	USER user;

}OBJECT;

// 기능 정리 - 유저생성(이름, 초기포켓몬), 전투(데미지계산, 포켓몬스탯비교, 스킬포인트사용, 아이템사용), 도망(랜덤), 
//             이동(키입력? 문자입력?), 회복(특정장소로이동 후 한번에 회복), 포획(현재 체력 비교 + 랜덤)




void SceneManager(OBJECT* _Player);
char* SetName();

void LogoScene();
void MenuScene();
void FirstScene();
void StageScene(OBJECT* _Player);

void InitializePlayer(OBJECT* _Player);
void PlayerScene(OBJECT* _Player);

void InitializeEnemy(OBJECT* _Enemy);
void EnemyScene(OBJECT* _Enemy);

void SetPosition(int _x, int _y, char* _str, int _Color = 15);
void SetColor(int _Color);
void VisibleCursor();
void InvisibleCursor();

int main(void) {
	
	system("mode con: cols=150 lines=60");
	system("title 김동욱 C Text Pokemon");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	printf_s("%s \n", Player->user.userName);

	while (true) {
		SceneManager(Player);
	}
	

	return 0;
}


void SceneManager(OBJECT* _Player) {
	switch (SceneState)
	{
	case Scene_Logo:
		LogoScene();
		break;
	case Scene_Menu:
		MenuScene();
		break;
	case Scene_Stage:
		StageScene(_Player);
		break;
	case Scene_Exit:

		exit(NULL);// ** 프로그램 종료
		break;
	}
}

char* SetName() {
	// ** scanf 함수로 문자열을 입력받기 위해 문자열을 받을수있는 배열을 선언.
	char Buffer[128] = "";

	printf_s("이름 입력 : ");

	// ** 문자열을 입력 받음.
	scanf("%s", Buffer);

	// ** 입력 받은값은 배열 이지만, 반환 값은 캐릭터 포인터형이므로 문자열을 복사햐야함.
	// ** 문자열을 복사 하기위해 포인터가 가르키는 공간에 입력받은 문자열이 들아갈만큼의 크기로 메모리 할당.
	char* pName = (char*)malloc(strlen(Buffer) + 1);

	// ** Buffer 가 받은 문자열을 pName 으로 복사.
	strcpy(pName, Buffer);

	// ** 반환.
	return pName;
}

void LogoScene() {
	printf_s("logo test\n");

	Sleep(500);
	FirstScene();
	SceneState++;
}

void MenuScene() {
	printf_s("MenuScene\n");

	printf_s("다음 씬 ㄱㄱ??\n1. 이동\n2. 종료\n입력 : ");

	int i = 0;
	scanf("%d", &i);

	if (i == 1)
		SceneState++;
	else if (i == 2)
		SceneState = Scene_Exit;
}

void FirstScene() {

	Sleep(3000);
	system("cls");
	printf_s("대사변경테스트 1");

	Sleep(3000);
	system("cls");
	printf_s("대사변경테스트 2");

	Sleep(3000);
	system("cls");
	printf_s("대사변경테스트 3");

	Sleep(3000);
	system("cls");
	printf_s("대사변경테스트 4");

	Sleep(3000);
	system("cls");
	printf_s("대사변경테스트 5\n");



}

void StageScene(OBJECT* _Player) {
	// ** 전투
	PlayerScene(_Player);
	
}

void InitializePlayer(OBJECT* _Player) {
	_Player->user.userName = SetName();

}

DWORD SetnameTime = 0;

void PlayerScene(OBJECT* _Player) {
	
}

void InitializeEnemy(OBJECT* _Enemy) {
	
}

void EnemyScene(OBJECT* _Enemy) {

}



void SetPosition(int _x, int _y, char* _str, int _Color) {
	COORD Pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}


void SetColor(int _Color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}



void VisibleCursor() {
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = true;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void InvisibleCursor() {
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

/*

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
*/