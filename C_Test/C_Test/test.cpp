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

// �÷��̾�, ������ ������ ���� ����ü ����
typedef struct tagInfo {
	char* Name;
	int HP;
	int MP;

	int EXP;

	float Att;
	float Def;

	int Level;

}INFO;

// tagInfo(INFO)����ü�� ������ ������ ����ü ����
typedef struct tagObject {
	INFO Info;

}OBJECT;



// �Լ� ���漱��
void InitializeObject(OBJECT* _Obj, int ObjectType);
char* SetName();


int main(void) {
	/*
	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Player, TYPE_PLAYER);
	OBJECT* Enemy = (OBJECT*)malloc(sizeof(OBJECT));;
	InitializeObject(Enemy, TYPE_ENEMY);
	*/

	// ����ü ������ ����
	OBJECT* Objects[MAX];
	// ����ü �÷��̾� �ʱ�ȭ
	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[PLAYER], PLAYER);
	// ����ü ���� �ʱ�ȭ
	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[ENEMY], ENEMY);
	// ������ɿ��� ����� ���� ���� ����
	int dice;


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
	}

	return 0;
}



// �÷��̾�� ������ �����͸� ����ü�� ��Ͻ�Ű�� �Լ�
void InitializeObject(OBJECT* _Obj, int ObjectType)
{
	switch (ObjectType) {
	case PLAYER : // �÷��̾��ϰ��
		_Obj->Info.Name = SetName(); // SetName�Լ����� �Է¹��� �̸��� ����

		_Obj->Info.Att = 10;
		_Obj->Info.Def = 10;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 100;
		_Obj->Info.MP = 10;
		_Obj->Info.Level = 1;
		break;
	case ENEMY : // ������ ���
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

char* SetName() { // �̸��� �Է¹޴� �Լ�
	char Buffer[128] = ""; // �̸��� �Է¹��� ������ �迭�� ����

	printf_s("�̸� �Է� : ");
	scanf("%s", Buffer);

	char* pName = (char*)malloc(strlen(Buffer) + 1); // ������ �������� �Է¹��� �̸��� ���ڼ���ŭ �����Ҵ�
	strcpy(pName, Buffer); // �����Ϳ� �̸��� ������

	return pName; // �Է¹��� �̸��� ����� ������ ��ȯ
}