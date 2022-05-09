#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>
#include <fstream>

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

int pokemoninfo = 1;


// 구조체 선언

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
int RunBattle();

void RecoveryPokemon(OBJECT* _Player);

void InitializeEnemy(OBJECT* _Enemy);

void SetPosition(int _x, int _y, char* _str, int _Color = 7);
void SetColor(int _Color);
void VisibleCursor();
void InvisibleCursor();

int main(void) {
	system("title 김동욱 C Text Pokemon");

	LogoScene();

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	for (int i = 0; i < 6; ++i) {
		Player->user.info[i] = (INFO*)malloc(sizeof(INFO));
		free(Player->user.info[i]);
		Player->user.info[i] = nullptr;
	}

	printf_s("플레이어 이름 %s \n", Player->user.userName);



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
		FirstPokemon(_Player);
		break;
	case Scene_Menu:
		MenuScene(_Player);
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
	InvisibleCursor();
	system("mode con:cols=150 lines=30");
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


	system("mode con: cols=150 lines=60");
	system("color 7");

	VisibleCursor();

}

void MenuScene(OBJECT* _Player) {
	printf_s("MenuScene\n");



	printf_s("%s \n", _Player->user.info[0]->Name);
	printf_s("%d \n", _Player->user.info[0]->Att);
	printf_s("%d \n", _Player->user.info[0]->Def);
	printf_s("%d \n", _Player->user.info[0]->EXP);
	printf_s("%d \n", _Player->user.info[0]->HP);
	printf_s("%d \n", _Player->user.info[0]->Level);
	printf_s("%d \n", _Player->user.info[0]->speed);

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
	printf_s("대사변경테스트 1\n");
	Sleep(3000);
	printf_s("대사변경테스트 2");

}

void FirstPokemon(OBJECT* _Player) {

	int i = 0;
	system("cls");
	printf_s("선택하기 : ");
	scanf_s("%d", &i);

	char pokemon1[8] = "꼬부기";

	char* pname1 = (char*)malloc(strlen(pokemon1) + 1);
	strcpy(pname1, pokemon1);

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

		SceneState++;
		break;
	case 2:
		SceneState++;
		break;
	case 3:
		SceneState++;
		break;
	default:
		FirstPokemon(_Player);
		break;
	}

}

void StageScene(OBJECT* _Player) {
	// ** 전투
	PlayerScene(_Player);

}

void InitializePlayer(OBJECT* _Player) {
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
			break;
		case 4:
			break;
		}
	}


}

int SelectMotion() {
	int i = 0;
	printf_s("행동 선택 : ");
	scanf_s("%d", &i);

	return i;
}

int SelectMotionBattle() {
	int i = 0;
	printf_s("배틀중 행동 선택 : ");
	scanf_s("%d", &i);

	return i;
}

void Battle(OBJECT* _Player) {

	printf_s("배틀\n");

	OBJECT* Enemy = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Enemy);

	while (true) {

		int i = SelectMotionBattle();

		switch (i) {
		case 1:
			printf_s("공격");
			Attack(_Player, Enemy);
			break;
		case 2:
			printf_s("몬스터볼");
			CatchPokemon(_Player, Enemy);
			break;
		case 3:
			printf_s("교체");
			SwitchPokemon(_Player);
			break;
		case 4:
			if (RunBattle() == 1) {
				SceneState = 2;
				StageScene(_Player);

			}
			printf_s("도망");
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
			printf_s("%d의 데미지를 몬스터에게 주었습니다.\n", (_Player->user.info[0]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 주었습니다.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[0]->Def) {
			printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", _Enemy->user.info[0]->Att - _Player->user.info[0]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[0]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
			Sleep(500);
		}

	}
	else if (pokemoninfo == 2) {
		if (_Player->user.info[1]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[1]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d의 데미지를 몬스터에게 주었습니다.\n", (_Player->user.info[1]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 주었습니다.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[1]->Def) {
			printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", _Enemy->user.info[0]->Att - _Player->user.info[1]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[1]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 3) {
		if (_Player->user.info[2]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[2]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d의 데미지를 몬스터에게 주었습니다.\n", (_Player->user.info[2]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 주었습니다.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[2]->Def) {
			printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", _Enemy->user.info[0]->Att - _Player->user.info[2]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[2]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 4) {
		if (_Player->user.info[3]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[3]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d의 데미지를 몬스터에게 주었습니다.\n", (_Player->user.info[3]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 주었습니다.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[3]->Def) {
			printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", _Enemy->user.info[0]->Att - _Player->user.info[3]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[3]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 5) {
		if (_Player->user.info[4]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[4]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d의 데미지를 몬스터에게 주었습니다.\n", (_Player->user.info[4]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 주었습니다.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[4]->Def) {
			printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", _Enemy->user.info[0]->Att - _Player->user.info[3]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[4]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
			Sleep(500);
		}
	}
	else if (pokemoninfo == 6) {
		if (_Player->user.info[5]->Att > _Enemy->user.info[0]->Def) {
			_Enemy->user.info[0]->HP -= _Player->user.info[5]->Att - _Enemy->user.info[0]->Def;
			printf_s("%d의 데미지를 몬스터에게 주었습니다.\n", (_Player->user.info[5]->Att - _Enemy->user.info[0]->Def));
			Sleep(500);
		}
		else {
			_Enemy->user.info[0]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 주었습니다.\n");
			Sleep(500);
		}

		if (_Enemy->user.info[0]->Att > _Player->user.info[5]->Def) {
			printf_s("%d의 데미지를 몬스터에게 받았습니다.\n", _Enemy->user.info[0]->Att - _Player->user.info[5]->Def);
			Sleep(500);
		}
		else {
			_Player->user.info[5]->HP -= 1;
			printf_s("1의 데미지를 몬스터에게 받았습니다.\n");
			Sleep(500);
		}
	}
}

void CatchPokemon(OBJECT* _Player, OBJECT* _Enemy) {
	int dice = (int)rand() % 6; // 랜덤함수를 이용해 0, 1의 값이 나오게함

	if (dice == 1) { // 1일경우
		printf_s("신난다!\n");
		printf_s("%s를(을) 잡았다.\n", _Enemy->user.info[0]->Name);

		int select = SelectPokemon(_Player);
		InsertPokemon(_Player, _Enemy, select);

		Sleep(500);
	}
	else { // 0일경우
		printf_s("도망치는것에 [실패] 했습니다.\n");  // 도망치는것에 실패, 몬스터에게 데미지를 입음

		Sleep(500);
	}

}

int SelectPokemon(OBJECT* _Player) {
	int select = 1;


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
		printf_s("저장할 위치 선택 : ");
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

	printf_s("1. %s \n", _Player->user.info[0]->Name);
	if (_Player->user.info[1] != nullptr) {
		printf_s("2. %s \n", _Player->user.info[1]->Name);
	}

	if (_Player->user.info[2] != nullptr) {
		printf_s("3. %s \n", _Player->user.info[2]->Name);
	}

	if (_Player->user.info[3] != nullptr) {
		printf_s("4. %s \n", _Player->user.info[3]->Name);
	}

	if (_Player->user.info[4] != nullptr) {
		printf_s("5. %s \n", _Player->user.info[4]->Name);
	}

	if (_Player->user.info[5] != nullptr) {
		printf_s("6. %s \n", _Player->user.info[5]->Name);
	}

	if (select >= 5) {
		printf_s("저장할 위치 선택 : ");
		scanf_s("%d", &select);
	}

	pokemoninfo = select;

}

int RunBattle() {
	int dice = (int)rand() % 6; // 랜덤함수를 이용해 0, 1의 값이 나오게함

	if (dice == 1) { // 1일경우
		printf_s("도망성공!\n");

		Sleep(500);

		return 1;
	}
	else { // 0일경우
		printf_s("도망치는것에 [실패] 했습니다.\n");  // 도망치는것에 실패, 몬스터에게 데미지를 입음

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

}

void InitializeEnemy(OBJECT* _Enemy) {

	_Enemy->user.info[0] = (INFO*)malloc(sizeof(INFO));
	char pokemon[8] = "파이리";

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