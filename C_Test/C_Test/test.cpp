#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>

// ��� ����

const int PLAYER = 0;
const int ENEMY = 1;
const int MAX = 2;

const int Scene_Logo = 0;
const int Scene_Menu = 1;
const int Scene_Stage = 2;
const int Scene_Exit = 3;

// ���� ���� ����

int SceneState = 0;

int Check = 1;


// ����ü ����

typedef struct tagInfo {
	char* Name;

	int HP;
	
	int EXP;

	int Att;
	int Def;
	int speed;

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

// ��� ���� - ��������(�̸�, �ʱ����ϸ�), ����(���������, ���ϸ��Ⱥ�, ��ų����Ʈ���, �����ۻ��), ����(����), 
//             �̵�(Ű�Է�? �����Է�?), ȸ��(Ư����ҷ��̵� �� �ѹ��� ȸ��), ��ȹ(���� ü�� �� + ����)




void SceneManager(OBJECT* _Player);
char* SetName();

void LogoScene();
void MenuScene(OBJECT* _Player);
void FirstScene();
void FirstPokemon(OBJECT* _Player);
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
	system("title �赿�� C Text Pokemon");

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
		FirstPokemon(_Player);
		break;
	case Scene_Menu:
		MenuScene(_Player);
		break;
	case Scene_Stage:
		StageScene(_Player);
		break;
	case Scene_Exit:

		exit(NULL);// ** ���α׷� ����
		break;
	}
}

char* SetName() {
	// ** scanf �Լ��� ���ڿ��� �Է¹ޱ� ���� ���ڿ��� �������ִ� �迭�� ����.
	char Buffer[128] = "";

	printf_s("�̸� �Է� : ");

	// ** ���ڿ��� �Է� ����.
	scanf("%s", Buffer);

	// ** �Է� �������� �迭 ������, ��ȯ ���� ĳ���� ���������̹Ƿ� ���ڿ��� ���������.
	// ** ���ڿ��� ���� �ϱ����� �����Ͱ� ����Ű�� ������ �Է¹��� ���ڿ��� ��ư���ŭ�� ũ��� �޸� �Ҵ�.
	char* pName = (char*)malloc(strlen(Buffer) + 1);

	// ** Buffer �� ���� ���ڿ��� pName ���� ����.
	strcpy(pName, Buffer);

	// ** ��ȯ.
	return pName;
}

void LogoScene() {
	printf_s("logo test\n");

	Sleep(500);
	FirstScene();
}

void MenuScene (OBJECT* _Player) {
	printf_s("MenuScene\n");

	printf_s("%s \n", _Player->user.info1.Name);
	printf_s("%d \n", _Player->user.info1.Att);
	printf_s("%d \n", _Player->user.info1.Def);
	printf_s("%d \n", _Player->user.info1.EXP);
	printf_s("%d \n", _Player->user.info1.HP);
	printf_s("%d \n", _Player->user.info1.Level);
	printf_s("%d \n", _Player->user.info1.speed);
	printf_s("%s \n", _Player->user.info1.skillname1);
	printf_s("%d \n", _Player->user.info1.skillpoint1);
	printf_s("%d \n", _Player->user.info1.skillpp1);

	printf_s("���� �� ����??\n1. �̵�\n2. ����\n�Է� : ");

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
	printf_s("��纯���׽�Ʈ 1");
	
}

void FirstPokemon(OBJECT* _Player) {
	int i = 0;
	printf_s("�����ϱ� : ");
	scanf_s("%d", &i);

	char pokemon1[8] = "���α�";
	char skill1[24] = "������ġ��";

	char* pname1 = (char*)malloc(strlen(pokemon1) + 1);
	strcpy(pname1, pokemon1);
	char* pskill1 = (char*)malloc(strlen(skill1) + 1);
	strcpy(pskill1, skill1);

	switch (i) {
	case 1:
		printf_s("%d", i);
		_Player->user.info1.Name = pname1;
		_Player->user.info1.Att = 4;
		_Player->user.info1.Def = 4;
		_Player->user.info1.EXP = 0;
		_Player->user.info1.HP = 100;
		_Player->user.info1.Level = 1;
		_Player->user.info1.speed = 5;
		_Player->user.info1.skillname1 = pskill1;
		_Player->user.info1.skillpoint1 = 10;
		_Player->user.info1.skillpp1 = 10;
		break;
	case 2:
		break;
	case 3:
		break;
	default :
		FirstPokemon(_Player);
		break;
	}
		
	SceneState++;

}

void StageScene(OBJECT* _Player) {
	// ** ����
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
		// ** �ܼ�â�� ��� ����.
		system("cls");

		printf_s("\n[%s]\n", Objects[PLAYER]->Info.Name);
		printf_s("HP : %d\n", Objects[PLAYER]->Info.HP);
		printf_s("MP : %d\n", Objects[PLAYER]->Info.MP);
		printf_s("���ݷ� : %.2f\n", Objects[PLAYER]->Info.Att);
		printf_s("���� : %.2f\n", Objects[PLAYER]->Info.Def);
		printf_s("EXP : %d\n", Objects[PLAYER]->Info.EXP);
		printf_s("Level : %d\n\n", Objects[PLAYER]->Info.Level);
		// 0.5���� ������
		Sleep(500);

		printf_s("[%s]\n", Objects[ENEMY]->Info.Name);
		printf_s("HP : %d\n", Objects[ENEMY]->Info.HP);
		printf_s("MP : %d\n", Objects[ENEMY]->Info.MP);
		printf_s("���ݷ� : %.2f\n", Objects[ENEMY]->Info.Att);
		printf_s("���� : %.2f\n", Objects[ENEMY]->Info.Def);
		printf_s("EXP : %d\n", Objects[ENEMY]->Info.EXP);
		printf_s("Level : %d\n\n", Objects[ENEMY]->Info.Level);

		Sleep(500);
		// ������
		int iChoice = 0;
		printf_s("���Ϳ� �������ϴ�. �����Ͻðڽ��ϱ� ?\n1. ����\n2. ����\n�Է� : ");
		scanf_s("%d", &iChoice);
		// switch���� �̿��� �б⸦ ����
		switch (iChoice) {
		case 1 : // '1'�ϰ��
			if (Objects[PLAYER]->Info.Att > Objects[ENEMY]->Info.Def) { // �÷��̾��� ���ݷ°� ������ ������ ��
				Objects[ENEMY]->Info.HP -= Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def; // ���ݷ� > ������ ��� ���ݷ� - ������ ��ġ��ŭ ����������
				printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (int)(Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def)); // �������� ǥ�� HP�� ���� int�̹Ƿ� int�� ����ȯ
				Sleep(500);
			}
			else {
				Objects[ENEMY]->Info.HP -= 1; // ���ݷ� < ������ ��� 1�� �������� ��
				printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
				Sleep(500);
			}
			// �÷��̾��� ������ ������ ���͵� ������
			if (Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def) {  // ������ ���ݷ°� �÷��̾��� ������ ��
				Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def; // ���ݷ� > ������ ��� ���ݷ� - ������ ��ġ��ŭ ����������
				printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", (int)(Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def));
				Sleep(500);
			}
			else {
				Objects[PLAYER]->Info.HP -= 1;
				printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
				Sleep(500);
			}

			break;
		case 2 : // '2'�ϰ��
			dice = (int)rand % 2; // �����Լ��� �̿��� 0, 1�� ���� ��������

			if (dice) { // 1�ϰ��
				printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
				InitializeObject(Objects[ENEMY], ENEMY); // ����ġ�°��� ����, ���ο� ���͸� �����Ŵ
				Sleep(500);
			}
			else { // 0�ϰ��
				printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");  // ����ġ�°Ϳ� ����, ���Ϳ��� �������� ����
				if (Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def) {
					Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def;
					printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", (int)(Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def));
				}
				else {
					Objects[PLAYER]->Info.HP -= 1;
					printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
				}
				Sleep(500);
			}

			break;

		default : // �ٸ� ���ڸ� �Է��������
			printf_s("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���. \n");
			Sleep(500);
		}
*/