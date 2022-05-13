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

const int LEFT = 0;
const int CENTER = 50;
const int RIGHT = 100;

// ���� ���� ����

int SceneState = 0;

int Check = 1;

int pokemoninfo = 0;


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
}INFO;

typedef struct userInfo {
	char* userName;

	INFO* info[6];
}USER;

typedef struct tagObject {
	USER user;

}OBJECT;


void SceneManager(OBJECT* _Player);
char* SetName();

void LogoScene();
void FirstScene();
void MentFirstPokemon(OBJECT* _Player);
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
int RunBattle();
void SwitchPokemon(OBJECT* _Player);
void CheckPokemon(OBJECT* _Player);

void RecoveryPokemon(OBJECT* _Player);

void InitializeEnemy(OBJECT* _Enemy);

void BigMessageBox();
void SmallMessageBox(int x);

void SetPosition(int _x, int _y, char* _str);
void SetKorPosition(int _x, int _y, char _str[], int i);
void VisibleCursor();
void InvisibleCursor();

int main(void) {
	system("title �赿�� C Text Pokemon");
	system("mode con:cols=150 lines=30");

	LogoScene();

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));

	for (int i = 0; i < 6; ++i) {
		Player->user.info[i] = (INFO*)malloc(sizeof(INFO));
		free(Player->user.info[i]);
		Player->user.info[i] = nullptr;
	}


	while (true) {
		SceneManager(Player);
	}


	return 0;
}


void SceneManager(OBJECT* _Player) {
	switch (SceneState)
	{
	case Scene_Logo:
		FirstScene();
		InitializePlayer(_Player);
		MentFirstPokemon(_Player);
		FirstPokemon(_Player);
		break;
	case Scene_Menu:
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

	SetPosition(6, 17, (char*)"�̸��� �Է��ϼ��� : ");

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
	InvisibleCursor();
	system("color E");

	char LOGO[28][151] = {
		{"                                                                                WXOKW                                                                 "},
		{"                                                                               WKdc:lON                                                               "},
		{"                                                                              Nx:,:c::xX                                                              "},
		{"                                                                            NOl;;lxxd::oKW                                                            "},
		{"                                                         WWWWNNW         WKko:;cdO0O:::;oK                                                            "},
		{"                   WWWNNNNWW                       WWXKOkdddoclkKW     WXxc;;:okkxol:::OKW         WNKOkOkkkkkOX                                      "},
		{"            WNKOkxdoollllllodxOKNW           WNXKOxdoc:::;;'',::cd0N  Nx;,;:;:llc::::::  WXkddddddddl:;;:cccc:;xN       WXKKNNWW                      "},
		{"       WNKOxoc::::clllooollcc:::lxKW       Xxllc::clooddl:;,;cool::oONXo'.,;;;;;::clloxOXXl',;:llllllc::okkkxl;oX      Nx;,:llodxkO0KXNW              "},
		{"    WX0xl:::lodxkOOO0000OOOOkxdlc;:dXW    Wx'.,;lxkO000Oo:;:lk0Okdl::lxo:;cclooddddoolc:cl;';;lkOOOOko:cx000ko:c0W     Xc.,;clolccccclldkkkOKXNWW     "},
		{"  Nkoc;:ldxOO00000000000000000Okxoc;lKW   Wk,';;:clk000Od::dO0000Okdc;;:ldkOOOOOOO0OOkxoc:;;;:d00000OdclO000Odc:xW     Xl',;coxkkkkxdoc:,,;:cclodxkOKN"},
		{" No..,;cx0000000000000000OO00000Okoc;oX    O:,,,,;cx000Odox0000000ko:;cx00OOxolllcok00Odc;;;;ck00000Oxld0000Oxl;oX WNXKOl,,,;;oO0000Oxl:;;coxddool:;oX"},
		{" WO:.',;:dO00000000000OxollloxO00Oxl;c0 WNX0xo;.';:d000OOO000000kdc;;:x00OdccdOklcdOOxl:;,',;lO000000kxk00000ko:cxkdllccc:;;;:d000000ko:::lk000Oko:cOW"},
		{"   Kl'',;:dOOkO0000000Od::oo:;oO00kc;cxkdllccc:;;;:dO000000000Odccol;lO00kl;ckxloOOxl::::,,;:d00000000O000000Odc;:cododxxxdol:cxO0000Odc::d00000xc:xN "},
		{"    Xd,,,;;cc;ck0000000kl:xKo;lO0Od:;;:codddxkxdoc:cxO000000Oxc;:dOd;lk00OdlccokOkoccoddl::;:x000000000000000kl:lxkxllxO00Okxoc:dO000Oxl:lk0000kl:lK  "},
		{"     Nx:,;,,,;;lk000000Od:coccx0Od:;:okOkllxO00Okxoc:dO00000kdolccc:;:d000OOkkO0OxxkO00Okdl:;cx000kkO0000000xc:oO0x:;cxOOkoxOko:ck0000kdcd0000Od:cOW  "},
		{"      WOloo;',,;lO000000Oo:cdk0ko:;cx00xc;cxO0kddOko:cx000000OOOkxdoc::ok00000000000000Oxoc:cxO00Oocx000kkOkl:lO0Odc:;:cc:cx0Odccx0OO0Oxdk000Oxc:xN   "},
		{"       WNWWk;',,;oO000000kkO0kdc;;:d00Oxc;;:clccdOOdc:d00kddxO00000Oxoc:cldxkkOOOOkkxdoc:;;ck0000kl:cx0kllkxc:d00Okxoccclok00Oo:lkkxk00OO0000kl:oK    "},
		{"           Nx,.';:oO000000Oxl:;,;;lk000OxoccccokO0Od::x0Odc;:codxO00Okxolc:::cccccc:;;;'';;oO000Oxc;:lxo:cxxc:oO000OOkkOO000Od:cxOxok0000000Oo:cOW    "},
		{"            Nd'.';:dO00000ko;;,'';ck0000OOOkkO0000xc;oO0Odc;,',;:codkOOOkkxddoc:;;:ldkl..;:ldxxkko:;;:::::dkoc:oO0000000000ko:cxOOolk0000000xc:xN     "},
		{"             Xo..';:d00000Odc;,'.,;oO00000000000Oxc;ck00Od:;cc;''',;:cldxO000ko:ckNW Xl..,,,,;;:::;'';:;;;okkdc:cdkkOOOkxdlccok00klck000000kl:oK      "},
		{"              Xc..',:x00000ko:;,..,;lxO000000Okdl:;;lk00Oxc:kWXOdl;''',;:cloddl;c0   W0kxdoolc::;lo;.',',;cxOkxdlc:cccc:;,;:oO00Oxccx00000Od:cOW      "},
		{"               K:..';cx0000Odc;::'.',;cloooooc:;,'';:oddol::kW   WXOdl;''',,;::;c0           WNXXNWOdd;.';:clllllc::coxo,.,:lxxkko:cx00000xc:xN       "},
		{"                0;..,;ck0000ko:;xOl,...'''',;cdk:..,,,,,,;cdKW       WX0xl;,''''c0                   Nx:;;,,,,,,,,;;dNWk'.',;;;::::cx0000kl:oK        "},
		{"                WO,..,;ck000Oxc;lKWXOxdooodk0N WkclddxkO0KXW             WNK0xod0N                    WNXKKOkxdolcld0WWKxdoollc;'';:dO00Od:cOW        "},
		{"                 Wk,..,;lxxdoc:;;kW                                                                              WW         WWNx'.,:clodoc:xN         "},
		{"                  Wx'..,;;,,,;:okXW                                                                                            Ko:;,'',,;;oK          "},
		{"                   Nd'.,cldxOKXW                                                                                                WWX0kdlclxKW          "},
		{"                    N0OKNW                                                                                                             WW             "}
	};

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 151; ++j) {
			printf_s("%c", LOGO[i][j]);
			Sleep(1);
		}
		printf_s("\n");
	}

	Sleep(100);
	system("color 6");
	Sleep(100);
	system("color E");
	Sleep(100);
	system("color 6");
	Sleep(100);
	system("color E");
	Sleep(100);
	system("color 6");
	Sleep(100);
	system("color E");
	Sleep(100);
	system("color 6");
	Sleep(100);
	system("color E");
	Sleep(500);

	system("color 7");



}


void FirstScene() {

	system("cls");

	char ment[9][128] = {
		{"���ϸ���  ���迡  �߿Դܴ� !"},
		{"���� �̸���  ���ڻ�"},
		{"��ηκ��ʹ�  ���ϸ�ڻ���  ����ް�  �ִܴ�"},
		{"���ϸ���........���ϸ�"},
		{"��  ���迡��  ���ϸ��Ͷ��  �ҷ�����  ����ü����  ��ó��  ����ִ� !"},
		{"������  �츮����  ���ϸ�  ���θ�  �˰�  ������  ���ϴ�"},
		{"���ϸ���  �����  ������  �ܶ�  �ִ� !"},
		{"����  �װ���  ��������  ���Ͽ�  ����  ���ϸ���  ������  ����ϰ�  �ִٴ�  ���̴� !"},
		{"�׷�........����  ����  �̸���  �����Ĵٿ� !"}
	};


	BigMessageBox();

	for (int y = 0; y < 9; ++y) {
		for (int x = 0; x < strlen(ment[y]); x += 2) {

			SetKorPosition(x + 6, y + 17, ment[y], x);

			Sleep(50);
		}
		printf_s("\n");
		Sleep(500);
	}


	Sleep(1000);

}

void MentFirstPokemon(OBJECT* _Player) {
	system("cls");
	InvisibleCursor();
	BigMessageBox();

	char ment[3][128] = {
		{"����  ��������  ����  �̾߱Ⱑ  ���۵Ǿ�����"},
		{"��Ʈ�ʰ�  ��  ���ϸ���  �ְڴ�"},
		{"��  ���Ŷ�  !"},
	};

	char playername[64];
	strcpy(playername, _Player->user.userName);
	strcat(playername, "!");
	SetPosition(6, 17, playername);

	printf_s("\n");

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < strlen(ment[i]); j += 2) {
			SetKorPosition(j + 6, i + 18, ment[i], j);

			Sleep(50);
		}
		printf_s("\n");
		Sleep(1000);
	}



}

void FirstPokemon(OBJECT* _Player) {


	int i = 0;
	system("cls");

	BigMessageBox();
	SmallMessageBox(LEFT);
	SmallMessageBox(CENTER);
	SmallMessageBox(RIGHT);

	char pokemon1[16] = "���α�";
	char pokemon2[16] = "���̸�";
	char pokemon3[16] = "�̻��ؾ�";

	SetPosition(6, 4, (char*)"1. ");
	SetPosition(9, 4, pokemon1);
	SetPosition(6, 5, (char*)"ü�� : 100");
	SetPosition(6, 6, (char*)"���ݷ� : 5");
	SetPosition(6, 7, (char*)"���� : 4");
	SetPosition(6, 8, (char*)"�ӵ� : 4");

	SetPosition(56, 4, (char*)"2. ");
	SetPosition(59, 4, pokemon2);
	SetPosition(56, 5, (char*)"ü�� : 90");
	SetPosition(56, 6, (char*)"���ݷ� : 6");
	SetPosition(56, 7, (char*)"���� : 2");
	SetPosition(56, 8, (char*)"�ӵ� : 5");

	SetPosition(106, 4, (char*)"3. ");
	SetPosition(109, 4, pokemon3);
	SetPosition(106, 5, (char*)"ü�� : 110");
	SetPosition(106, 6, (char*)"���ݷ� : 3");
	SetPosition(106, 7, (char*)"���� : 5");
	SetPosition(106, 8, (char*)"�ӵ� : 2");


	VisibleCursor();

	_Player->user.info[0] = (INFO*)malloc(sizeof(INFO));
	char* pname1 = (char*)malloc(strlen(pokemon1) + 1);
	strcpy(pname1, pokemon1);
	char* pname2 = (char*)malloc(strlen(pokemon2) + 1);
	strcpy(pname2, pokemon2);
	char* pname3 = (char*)malloc(strlen(pokemon3) + 1);
	strcpy(pname3, pokemon3);

	SetPosition(6, 17, (char*)"���ϸ� �����ϱ� : ");
	scanf_s("%d", &i);

	switch (i) {
	case 1:
		_Player->user.info[0]->Name = pname1;
		_Player->user.info[0]->Att = 5;
		_Player->user.info[0]->Def = 4;
		_Player->user.info[0]->EXP = 0;
		_Player->user.info[0]->MAXEXP = 50;
		_Player->user.info[0]->HP = 100;
		_Player->user.info[0]->MAXHP = 100;
		_Player->user.info[0]->Level = 4;
		_Player->user.info[0]->speed = 4;

		SceneState++;
		StageScene(_Player);
		break;
	case 2:
		_Player->user.info[0]->Name = pname2;
		_Player->user.info[0]->Att = 6;
		_Player->user.info[0]->Def = 2;
		_Player->user.info[0]->EXP = 0;
		_Player->user.info[0]->MAXEXP = 50;
		_Player->user.info[0]->HP = 90;
		_Player->user.info[0]->MAXHP = 90;
		_Player->user.info[0]->Level = 4;
		_Player->user.info[0]->speed = 5;

		SceneState++;
		StageScene(_Player);
		break;
	case 3:
		_Player->user.info[0]->Name = pname3;
		_Player->user.info[0]->Att = 3;
		_Player->user.info[0]->Def = 5;
		_Player->user.info[0]->EXP = 0;
		_Player->user.info[0]->MAXEXP = 50;
		_Player->user.info[0]->HP = 110;
		_Player->user.info[0]->MAXHP = 110;
		_Player->user.info[0]->Level = 4;
		_Player->user.info[0]->speed = 2;

		SceneState++;
		StageScene(_Player);
		break;
	default:

		system("cls");

		BigMessageBox();
		SmallMessageBox(LEFT);
		SmallMessageBox(CENTER);
		SmallMessageBox(RIGHT);

		char pokemon1[16] = "���α�";
		char pokemon2[16] = "���̸�";
		char pokemon3[16] = "�̻��ؾ�";

		SetPosition(6, 4, (char*)"1. ");
		SetPosition(9, 4, pokemon1);
		SetPosition(6, 5, (char*)"ü�� : 100");
		SetPosition(6, 6, (char*)"���ݷ� : 5");
		SetPosition(6, 7, (char*)"���� : 4");
		SetPosition(6, 8, (char*)"�ӵ� : 4");

		SetPosition(56, 4, (char*)"2. ");
		SetPosition(59, 4, pokemon2);
		SetPosition(56, 5, (char*)"ü�� : 90");
		SetPosition(56, 6, (char*)"���ݷ� : 6");
		SetPosition(56, 7, (char*)"���� : 2");
		SetPosition(56, 8, (char*)"�ӵ� : 5");

		SetPosition(106, 4, (char*)"3. ");
		SetPosition(109, 4, pokemon3);
		SetPosition(106, 5, (char*)"ü�� : 110");
		SetPosition(106, 6, (char*)"���ݷ� : 3");
		SetPosition(106, 7, (char*)"���� : 5");
		SetPosition(106, 8, (char*)"�ӵ� : 2");
		SetPosition(6, 17, (char*)"�ٽ� �����ϰŶ�  !");
		Sleep(1000);

		FirstPokemon(_Player);

		break;

	}
}

void StageScene(OBJECT* _Player) {
	// ** ����
	PlayerScene(_Player);

}

void InitializePlayer(OBJECT* _Player) {
	system("cls");

	VisibleCursor();
	BigMessageBox();

	_Player->user.userName = SetName();

}

void PlayerScene(OBJECT* _Player) {

	while (true) {
		int i = SelectMotion();

		switch (i) {
		case 1:
			Battle(_Player);
			break;
		case 2:
			RecoveryPokemon(_Player);
			break;
		case 3:
			CheckPokemon(_Player);
			break;
		case 4:
			exit(NULL);
			break;
		default:
			system("cls");
			BigMessageBox();
			SetPosition(6, 17, (char*)"�ٽ� �Է��Ͻÿ�.");
			Sleep(1000);
			break;
		}
	}


}

int SelectMotion() {
	int i = 0;
	system("cls");
	BigMessageBox();
	SetPosition(4, 2, (char*)"1. ����");
	SetPosition(4, 3, (char*)"2. ȸ��");
	SetPosition(4, 4, (char*)"3. ���ϸ� Ȯ��");
	SetPosition(4, 5, (char*)"4. ���� ����");
	SetPosition(6, 17, (char*)"�ൿ�� �����Ͻÿ� : ");
	scanf_s("%d", &i);

	return i;
}

int SelectMotionBattle() {
	int i = 0;

	BigMessageBox();
	SetPosition(4, 2, (char*)"1. ����");
	SetPosition(4, 3, (char*)"2. ��ȹ");
	SetPosition(4, 4, (char*)"3. ���ϸ� ��ü");
	SetPosition(4, 5, (char*)"4. ��������");
	SetPosition(6, 17, (char*)"�ൿ�� �����Ͻÿ� : ");
	scanf_s("%d", &i);

	return i;
}

void Battle(OBJECT* _Player) {

	OBJECT* Enemy = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Enemy);

	while (true) {
		system("cls");

		VisibleCursor();
		SmallMessageBox(CENTER);
		SmallMessageBox(RIGHT);


		char hp[16];
		char maxhp[16];
		char slash[4] = " / ";

		sprintf(hp, "%d", _Player->user.info[pokemoninfo]->HP);
		sprintf(maxhp, "%d", _Player->user.info[pokemoninfo]->MAXHP);
		strcat(hp, slash);
		strcat(hp, maxhp);

		SetPosition(56, 4, (char*)"TEAM");
		SetPosition(56, 5, _Player->user.info[pokemoninfo]->Name);
		SetPosition(56, 6, hp);

		sprintf(hp, "%d", Enemy->user.info[0]->HP);
		sprintf(maxhp, "%d", Enemy->user.info[0]->MAXHP);
		strcat(hp, slash);
		strcat(hp, maxhp);

		SetPosition(106, 4, (char*)"ENEMY");
		SetPosition(106, 5, Enemy->user.info[0]->Name);
		SetPosition(106, 6, hp);


		int i = SelectMotionBattle();

		switch (i) {
		case 1:
			Attack(_Player, Enemy);
			break;
		case 2:
			CatchPokemon(_Player, Enemy);
			break;
		case 3:
			SwitchPokemon(_Player);
			break;
		case 4:
			if (RunBattle() == 1) {
				SceneState = 2;
				StageScene(_Player);
			}
			break;
		default:
			system("cls");
			BigMessageBox();
			SetPosition(6, 17, (char*)"�ٽ� �Է��Ͻÿ�.");
			Sleep(1000);
			break;

		}
	}
}

void Attack(OBJECT* _Player, OBJECT* _Enemy) {

	if (_Player->user.info[pokemoninfo]->Att > _Enemy->user.info[0]->Def) {
		_Enemy->user.info[0]->HP -= _Player->user.info[pokemoninfo]->Att - _Enemy->user.info[0]->Def;
		SetPosition(6, 18, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"");
		printf_s("%d�� �������� ���Ϳ��� �־����ϴ�.\n", (_Player->user.info[pokemoninfo]->Att - _Enemy->user.info[0]->Def));
		Sleep(500);
	}
	else {
		_Enemy->user.info[0]->HP -= 1;
		SetPosition(6, 18, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"");
		printf_s("1�� �������� ���Ϳ��� �־����ϴ�.\n");
		Sleep(500);
	}

	if (_Enemy->user.info[0]->HP <= 0) {
		SetPosition(6, 18, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"");
		SetPosition(6, 17, (char*)"�������� �¸��ߴ�!");
		Sleep(1000);
		free(_Enemy);
		PlayerScene(_Player);
	}

	if (_Enemy->user.info[0]->Att > _Player->user.info[pokemoninfo]->Def) {
		_Player->user.info[pokemoninfo]->HP -= _Enemy->user.info[0]->Att - _Player->user.info[pokemoninfo]->Def;
		SetPosition(6, 18, (char*)"");
		printf_s("%d�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n", _Enemy->user.info[0]->Att - _Player->user.info[pokemoninfo]->Def);
		Sleep(500);
	}
	else {
		_Player->user.info[pokemoninfo]->HP -= 1;
		SetPosition(6, 18, (char*)"");
		printf_s("1�� �������� ���Ϳ��� �޾ҽ��ϴ�.\n");
		Sleep(500);
	}

	if (_Player->user.info[pokemoninfo]->HP <= 0) {

		char name[128];
		strcpy(name, _Player->user.userName);
		strcat(name, "��(��) �� ���� ����������.");

		SetPosition(6, 18, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"                                                                   ");
		SetPosition(6, 17, (char*)"");
		SetPosition(6, 17, name);
		Sleep(1000);
		free(_Enemy);
		PlayerScene(_Player);
	}


}

void CatchPokemon(OBJECT* _Player, OBJECT* _Enemy) {
	int dice = (int)rand() % 6;

	if (dice == 1) {
		char pokemon[64];
		strcpy(pokemon, _Enemy->user.info[0]->Name);
		strcat(pokemon, "��(��) ��Ҵ�.");

		system("cls");
		BigMessageBox();
		SetPosition(6, 17, (char*)"�ų���!");
		SetPosition(6, 18, pokemon);
		Sleep(1000);

		int select = SelectPokemon(_Player);
		InsertPokemon(_Player, _Enemy, select);

	}
	else {

		system("cls");
		BigMessageBox();
		SetPosition(6, 17, (char*)"��ȹ�� ���� �߽��ϴ�.");
		Sleep(500);
	}

}

int SelectPokemon(OBJECT* _Player) {
	int select = 0;


	char name[64];
	char hp[16];
	char maxhp[16];
	char slash[4] = " / ";
	char num[2];
	int j = 0;
	int x = 0;

	system("cls");
	SmallMessageBox(LEFT);
	SmallMessageBox(CENTER);
	BigMessageBox();
	InvisibleCursor();

	for (int i = 0; i < 6; ++i) {
		if (i < 3 && _Player->user.info[i] != nullptr) {
			strcpy(name, _Player->user.info[i]->Name);
			sprintf(num, "%d", i + 1);
			SetPosition(6, 3 + j, num);
			SetPosition(7, 3 + j, (char*)". ");
			SetPosition(9, 3 + j, name);
			sprintf(hp, "%d", _Player->user.info[i]->HP);
			sprintf(maxhp, "%d", _Player->user.info[i]->MAXHP);
			strcat(hp, slash);
			strcat(hp, maxhp);
			SetPosition(6, 4 + j, hp);
			j += 3;
			select++;
		}
		else if (_Player->user.info[i] != nullptr) {
			strcpy(name, _Player->user.info[i]->Name);
			sprintf(num, "%d", i + 1);
			SetPosition(56, 3 + x, num);
			SetPosition(57, 3 + x, (char*)". ");
			SetPosition(59, 3 + x, name);
			sprintf(hp, "%d", _Player->user.info[i]->HP);
			sprintf(maxhp, "%d", _Player->user.info[i]->MAXHP);
			strcat(hp, slash);
			strcat(hp, maxhp);
			SetPosition(56, 4 + x, hp);
			x += 3;
			select++;
		}

	}

	if (select == 6) {
		SetPosition(6, 17, (char*)"���ϸ��� ������ ��ġ ���� : ");
		scanf_s("%d", &select);
		select -= 1;
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

	free(_Enemy);

	SceneState = 2;
	StageScene(_Player);
}

void SwitchPokemon(OBJECT* _Player) {
	int select = 0;

	char name[64];
	char hp[16];
	char maxhp[16];
	char slash[4] = " / ";
	char num[2];
	int j = 0;
	int x = 0;

	system("cls");
	SmallMessageBox(LEFT);
	SmallMessageBox(CENTER);
	BigMessageBox();
	InvisibleCursor();

	for (int i = 0; i < 6; ++i) {
		if (i < 3 && _Player->user.info[i] != nullptr) {
			strcpy(name, _Player->user.info[i]->Name);
			sprintf(num, "%d", i + 1);
			SetPosition(6, 3 + j, num);
			SetPosition(7, 3 + j, (char*)". ");
			SetPosition(9, 3 + j, name);
			sprintf(hp, "%d", _Player->user.info[i]->HP);
			sprintf(maxhp, "%d", _Player->user.info[i]->MAXHP);
			strcat(hp, slash);
			strcat(hp, maxhp);
			SetPosition(6, 4 + j, hp);
			j += 3;
		}
		else if (_Player->user.info[i] != nullptr) {
			strcpy(name, _Player->user.info[i]->Name);
			sprintf(num, "%d", i + 1);
			SetPosition(56, 3 + x, num);
			SetPosition(57, 3 + x, (char*)". ");
			SetPosition(59, 3 + x, name);
			sprintf(hp, "%d", _Player->user.info[i]->HP);
			sprintf(maxhp, "%d", _Player->user.info[i]->MAXHP);
			strcat(hp, slash);
			strcat(hp, maxhp);
			SetPosition(56, 4 + x, hp);
			x += 3;
		}

	}

	SetPosition(6, 17, (char*)"��ü�� ���ϸ��� �����Ͻÿ� : ");
	scanf_s("%d", &select);
	select -= 1;

	pokemoninfo = select;

}

int RunBattle() {
	int dice = (int)rand() % 6; // �����Լ��� �̿��� 0, 1�� ���� ��������

	if (dice == 1) { // 1�ϰ��
		SetPosition(6, 17, (char*)"                                                                               ");
		SetPosition(6, 17, (char*)"���������� �����ƴ�!");
		Sleep(1000);

		return 1;
	}
	else { // 0�ϰ��
		SetPosition(6, 17, (char*)"                                                                              ");
		SetPosition(6, 17, (char*)"������ �����ߴ�.");
		Sleep(500);
	}

	return 0;

}

void RecoveryPokemon(OBJECT* _Player) {

	_Player->user.info[0]->HP = _Player->user.info[0]->MAXHP;
	if (_Player->user.info[1] != nullptr) {
		_Player->user.info[1]->HP = _Player->user.info[1]->MAXHP;
	}

	if (_Player->user.info[2] != nullptr) {
		_Player->user.info[2]->HP = _Player->user.info[2]->MAXHP;
	}

	if (_Player->user.info[3] != nullptr) {
		_Player->user.info[3]->HP = _Player->user.info[3]->MAXHP;
	}

	if (_Player->user.info[4] != nullptr) {
		_Player->user.info[4]->HP = _Player->user.info[4]->MAXHP;
	}

	if (_Player->user.info[5] != nullptr) {
		_Player->user.info[5]->HP = _Player->user.info[5]->MAXHP;
	}
	SetPosition(6, 17, (char*)"                                                                               ");
	SetPosition(6, 17, (char*)"ȸ���Ǿ����ϴ�.");
	Sleep(1000);
}

void CheckPokemon(OBJECT* _Player) {

	char name[64];
	char hp[16];
	char maxhp[16];
	char slash[4] = " / ";
	char num[2];
	int j = 0;
	int x = 0;

	system("cls");
	SmallMessageBox(LEFT);
	SmallMessageBox(CENTER);
	BigMessageBox();
	InvisibleCursor();

	for (int i = 0; i < 6; ++i) {
		if (i < 3 && _Player->user.info[i] != nullptr) {
			strcpy(name, _Player->user.info[i]->Name);
			sprintf(num, "%d", i + 1);
			SetPosition(6, 3 + j, num);
			SetPosition(7, 3 + j, (char*)". ");
			SetPosition(9, 3 + j, name);
			sprintf(hp, "%d", _Player->user.info[i]->HP);
			sprintf(maxhp, "%d", _Player->user.info[i]->MAXHP);
			strcat(hp, slash);
			strcat(hp, maxhp);
			SetPosition(6, 4 + j, hp);
			j += 3;
		}
		else if (_Player->user.info[i] != nullptr) {
			strcpy(name, _Player->user.info[i]->Name);
			sprintf(num, "%d", i + 1);
			SetPosition(56, 3 + x, num);
			SetPosition(57, 3 + x, (char*)". ");
			SetPosition(59, 3 + x, name);
			sprintf(hp, "%d", _Player->user.info[i]->HP);
			sprintf(maxhp, "%d", _Player->user.info[i]->MAXHP);
			strcat(hp, slash);
			strcat(hp, maxhp);
			SetPosition(56, 4 + x, hp);
			x += 3;
		}

	}

	Sleep(2000);

}

void InitializeEnemy(OBJECT* _Enemy) {

	_Enemy->user.info[0] = (INFO*)malloc(sizeof(INFO));
	char pokemon[8] = "���̸�";

	char* pname = (char*)malloc(strlen(pokemon) + 1);
	strcpy(pname, pokemon);

	_Enemy->user.info[0]->Name = pname;
	_Enemy->user.info[0]->Att = 4;
	_Enemy->user.info[0]->Def = 4;
	_Enemy->user.info[0]->EXP = 0;
	_Enemy->user.info[0]->MAXEXP = 0;
	_Enemy->user.info[0]->HP = 100;
	_Enemy->user.info[0]->MAXHP = 100;
	_Enemy->user.info[0]->Level = 1;
	_Enemy->user.info[0]->speed = 5;
}

void BigMessageBox() {

	SetPosition(0, 18, (char*)"    ==============================================================================================================================================\n");
	SetPosition(0, 19, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 20, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 21, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 22, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 23, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 24, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 25, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 26, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 27, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 28, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 29, (char*)"    |                                                                                                                                             |\n");
	SetPosition(0, 30, (char*)"    ==============================================================================================================================================\n");
}

void SmallMessageBox(int x) {
	SetPosition(x, 3, (char*)"    =========================================\n");
	SetPosition(x, 4, (char*)"    |                                        |\n");
	SetPosition(x, 5, (char*)"    |                                        |\n");
	SetPosition(x, 6, (char*)"    |                                        |\n");
	SetPosition(x, 7, (char*)"    |                                        |\n");
	SetPosition(x, 8, (char*)"    |                                        |\n");
	SetPosition(x, 9, (char*)"    |                                        |\n");
	SetPosition(x, 10, (char*)"    |                                        |\n");
	SetPosition(x, 11, (char*)"    |                                        |\n");
	SetPosition(x, 12, (char*)"    |                                        |\n");
	SetPosition(x, 13, (char*)"    |                                        |\n");
	SetPosition(x, 14, (char*)"    |                                        |\n");
	SetPosition(x, 15, (char*)"    =========================================\n");
}


void SetPosition(int _x, int _y, char* _str) {
	COORD Pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	printf_s("%s", _str);
}

void SetKorPosition(int _x, int _y, char _str[], int i) {
	COORD Pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	printf_s("%c%c", _str[i], _str[i + 1]);
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