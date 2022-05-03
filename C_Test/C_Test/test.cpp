#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>
#include <fstream>

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

int pokemoninfo = 1;


// ����ü ����

typedef struct tagInfo {
	char* Name;

	int HP;
	int MAXHP;
	
	int EXP;
	int MAXEXP;

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

	INFO* info[6];
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

int SelectMotion();
int SelectMotionBattle();
void Battle(OBJECT* _Player);
void Attack(OBJECT* _Player, OBJECT* _Enemy);
void CatchPokemon(OBJECT* _Player, OBJECT* _Enemy);
int SelectPokemon(OBJECT* _Player);
void InsertPokemon(OBJECT* _Player, OBJECT* _Enemy, int select);
void SwitchPokemon(OBJECT* _Player);

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

	for (int i = 0; i < 6; ++i) {
		Player->user.info[i] = (INFO*)malloc(sizeof(INFO));
		free(Player->user.info[i]);
		Player->user.info[i] = nullptr;
	}	

	printf_s("�÷��̾� �̸� %s \n", Player->user.userName);



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

	

	printf_s("%s \n", _Player->user.info[0]->Name);
	printf_s("%d \n", _Player->user.info[0]->Att);
	printf_s("%d \n", _Player->user.info[0]->Def);
	printf_s("%d \n", _Player->user.info[0]->EXP);
	printf_s("%d \n", _Player->user.info[0]->HP);
	printf_s("%d \n", _Player->user.info[0]->Level);
	printf_s("%d \n", _Player->user.info[0]->speed);
	printf_s("%s \n", _Player->user.info[0]->skillname1);
	printf_s("%d \n", _Player->user.info[0]->skillpoint1);
	printf_s("%d \n", _Player->user.info[0]->skillpp1);

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
	printf_s("��纯���׽�Ʈ 1\n");
	Sleep(3000);
	printf_s("��纯���׽�Ʈ 2");
	
}

void FirstPokemon(OBJECT* _Player) {
	int i = 0;
	system("cls");
	printf_s("�����ϱ� : ");
	scanf_s("%d", &i);

	char pokemon1[8] = "���α�";
	char skill1[24] = "�����ġ��";

	char* pname1 = (char*)malloc(strlen(pokemon1) + 1);
	strcpy(pname1, pokemon1);
	char* pskill1 = (char*)malloc(strlen(skill1) + 1);
	strcpy(pskill1, skill1);

	_Player->user.info[0] = (INFO*)malloc(sizeof(INFO));

	switch (i) {
	case 1:
		printf_s("%d", i);
		_Player->user.info[0]->Name = pname1;		
		_Player->user.info[0]->Att = 4;
		_Player->user.info[0]->Def = 4;
		_Player->user.info[0]->EXP = 0;
		_Player->user.info[0]->MAXEXP = 0;
		_Player->user.info[0]->HP = 100;
		_Player->user.info[0]->MAXHP = 100;
		_Player->user.info[0]->Level = 1;
		_Player->user.info[0]->speed = 5;
		_Player->user.info[0]->skillname1 = pskill1;
		_Player->user.info[0]->skillpoint1 = 10;
		_Player->user.info[0]->skillpp1 = 10;
		SceneState++;
		break;
	case 2:
		SceneState++;
		break;
	case 3:
		SceneState++;
		break;
	default :
		FirstPokemon(_Player);
		break;
	}

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
	int i = SelectMotion();

	switch (i) {
	case 1 :
		Battle(_Player);
		break;
	case 2 :
		break;
	case 3 :
		break;
	case 4 :
		break;


	}
	
}

int SelectMotion() {
	int i = 0;
	printf_s("�ൿ ���� : ");
	scanf_s("%d", &i);

	return i;
}

int SelectMotionBattle() {
	int i = 0;
	printf_s("��Ʋ�� �ൿ ���� : ");
	scanf_s("%d", &i);

	return i;
}

void Battle(OBJECT* _Player) {
	
	printf_s("��Ʋ\n");

	OBJECT* Enemy = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Enemy);

	while (true) {
		
		int i = SelectMotionBattle();

		switch (i) {
		case 1:
			printf_s("����");
			Attack(_Player, Enemy);
			break;
		case 2:
			printf_s("���ͺ�");
			CatchPokemon(_Player, Enemy);
			break;
		case 3:
			printf_s("��ü");
			break;
		case 4:
			printf_s("����");
			break;
		default:
			break;

		}
	}

}

void Attack(OBJECT* _Player, OBJECT* _Enemy) {

	if (pokemoninfo == 1) {
		if (_Player->user.info[0]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[0]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (_Player->user.info[0]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[0]->Def) {
			printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", _Enemy->user.info[0]->Att - _Player->user.info[0]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[0]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
			Sleep(500);
		}

	}
	else if (pokemoninfo == 2) {
		if (_Player->user.info[1]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[1]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (_Player->user.info[1]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[1]->Def) {
			printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", _Enemy->user.info[0]->Att - _Player->user.info[1]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[1]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 3) {
		if (_Player->user.info[2]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[2]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (_Player->user.info[2]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[2]->Def) {
			printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", _Enemy->user.info[0]->Att - _Player->user.info[2]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[2]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 4) {
		if (_Player->user.info[3]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[3]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (_Player->user.info[3]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[3]->Def) {
			printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", _Enemy->user.info[0]->Att - _Player->user.info[3]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[3]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 5) {
		if (_Player->user.info[4]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[4]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (_Player->user.info[4]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[4]->Def) {
			printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", _Enemy->user.info[0]->Att - _Player->user.info[3]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[4]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 6) {
		if (_Player->user.info[5]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[5]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (_Player->user.info[5]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[5]->Def) {
			printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", _Enemy->user.info[0]->Att - _Player->user.info[5]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[5]->HP -= 1;
			printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
			Sleep(500);
		}
	}
}

void CatchPokemon(OBJECT* _Player, OBJECT* _Enemy) {
	int dice = (int)rand() % 6; // �����Լ��� �̿��� 0, 1�� ���� ��������

	if (dice == 1) { // 1�ϰ��
		printf_s("�ų���!\n");
		printf_s("%s��(��) ��Ҵ�.\n", _Enemy->user.info[0]->Name);

		int select = SelectPokemon(_Player);
		InsertPokemon(_Player, _Enemy, select);
		
		Sleep(500);
	}
	else { // 0�ϰ��
		printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");  // ����ġ�°Ϳ� ����, ���Ϳ��� �������� ����
		
		Sleep(500);
	}

}

int SelectPokemon(OBJECT* _Player) {
	int select = 1;

	printf_s("1. %s \n", _Player->user.info[0]->Name);
	if (_Player->user.info[1] != nullptr) {
		printf_s("2. %s \n", _Player->user.info[1]->Name);
		select++;
	}
		
	if (_Player->user.info[2] != nullptr) {
		printf_s("3. %s \n", _Player->user.info[2]->Name);
		select++;
	}
		
	if (_Player->user.info[3] != nullptr) {
		printf_s("4. %s \n", _Player->user.info[3]->Name);
		select++;
	}
		
	if (_Player->user.info[4] != nullptr) {
		printf_s("5. %s \n", _Player->user.info[4]->Name);
		select++;
	}
		
	if (_Player->user.info[5] != nullptr) {
		printf_s("6. %s \n", _Player->user.info[5]->Name);
		select++;
	}
		
	if (select >= 5) {
		printf_s("������ ��ġ ���� : ");
		scanf_s("%d", &select);
	}
	

	return select;
}

void InsertPokemon(OBJECT* _Player, OBJECT* _Enemy, int select) {

	_Player->user.info[select] = (INFO*)malloc(sizeof(INFO));

	_Player->user.info[select]->Name = _Enemy->user.info[0]->Name;
	_Player->user.info[select]->Att = _Enemy->user.info[0]->Att;
	_Player->user.info[select]->Def = _Enemy->user.info[0]->Def;
	_Player->user.info[select]->EXP = 0;
	_Player->user.info[select]->MAXEXP = _Enemy->user.info[0]->MAXEXP;
	_Player->user.info[select]->HP = _Enemy->user.info[0]->HP;
	_Player->user.info[select]->MAXHP = _Enemy->user.info[0]->MAXHP;
	_Player->user.info[select]->Level = _Enemy->user.info[0]->Level;
	_Player->user.info[select]->speed = _Enemy->user.info[0]->speed;
	_Player->user.info[select]->skillname1 = _Enemy->user.info[0]->skillname1;
	_Player->user.info[select]->skillpoint1 = _Enemy->user.info[0]->skillpoint1;
	_Player->user.info[select]->skillpp1 = _Enemy->user.info[0]->skillpp1;

	free(_Enemy);
}

void SwitchPokemon(OBJECT* _Player) {

}

void InitializeEnemy(OBJECT* _Enemy) {

	_Enemy->user.info[0] = (INFO*)malloc(sizeof(INFO));
	char pokemon[8] = "���̸�";
	char skill1[24] = "ȭ�����";

	char* pname = (char*)malloc(strlen(pokemon) + 1);
	strcpy(pname, pokemon);
	char* pskill1 = (char*)malloc(strlen(skill1) + 1);
	strcpy(pskill1, skill1);

	_Enemy->user.info[0]->Name = pname;
	_Enemy->user.info[0]->Att = 4;
	_Enemy->user.info[0]->Def = 4;
	_Enemy->user.info[0]->EXP = 0;
	_Enemy->user.info[0]->MAXEXP = 0;
	_Enemy->user.info[0]->HP = 100;
	_Enemy->user.info[0]->MAXHP = 100;
	_Enemy->user.info[0]->Level = 1;
	_Enemy->user.info[0]->speed = 5;
	_Enemy->user.info[0]->skillname1 = pskill1;
	_Enemy->user.info[0]->skillpoint1 = 10;
	_Enemy->user.info[0]->skillpp1 = 10;

	
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