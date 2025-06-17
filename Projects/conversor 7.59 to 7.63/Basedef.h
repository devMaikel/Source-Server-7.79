/*
*   Copyright (C) {2015}  {VK, Charles TheHouse}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*   Contact at: 
*/


#ifndef _BASEDEF_ // Last updated 27/01/2013
#define _BASEDEF_

#include <time.h>
#include <Windows.h>
#include <cstdint>
#include <cassert>
#include <vector>
#include <mbstring.h>
#include <map>
#include <string>
#include <functional>
#include <tuple>
#include <unordered_map>
#include <array>
#include <ctime>
#include <memory>
#include <fstream>
#include <iostream>
#include <time.h>
#include <sstream>
#include <WinSock.h>
#include <Rpc.h>


#pragma region Defines
#define Snow                    0xFFFFFAFA
#define GhostWhite              0xFFF8F8FF
#define WhiteSmoke              0xFFF5F5F5
#define Gainsboro               0xFFDCDCDC
#define FloralWhite             0xFFFFFAF0
#define OldLace                 0xFFFDF5E6
#define Linen                   0xFFFAF0E6
#define AntiqueWhite            0xFFFAEBD7
#define PapayaWhip              0xFFFFEFD5
#define BlanchedAlmond			0xFFFFEBCD
#define Bisque					0xFFFFE4C4
#define PeachPuff				0xFFFFDAB9
#define NavajoWhite				0xFFFFDEAD
#define Moccasin				0xFFFFE4B5
#define Cornsilk				0xFFFFF8DC
#define Ivory					0xFFFFFFF0
#define LemonChiffon			0xFFFFFACD
#define Seashell				0xFFFFF5EE
#define Honeydew				0xFFF0FFF0
#define MintCream				0xFFF5FFFA
#define Azure					0xFFF0FFFF
#define AliceBlue				0xFFF0F8FF
#define lavender				0xFFE6E6FA
#define LavenderBlush			0xFFFFF0F5
#define MistyRose				0xFFFFE4E1
#define White					0xFFFFFFFF
#define Black					0xFF000000
#define DarkSlateGray			0xFF2F4F4F
#define DimGrey					0xFF696969
#define SlateGrey				0xFF708090
#define LightSlateGray			0xFF778899
#define Grey					0xFFBEBEBE
#define LightGray				0xFFD3D3D3
#define MidnightBlue			0xFF191970
#define NavyBlue				0xFF000080
#define CornflowerBlue			0xFF6495ED
#define DarkSlateBlue			0xFF483D8B
#define SlateBlue				0xFF6A5ACD
#define MediumSlateBlue			0xFF7B68EE
#define LightSlateBlue			0xFF8470FF
#define MediumBlue				0xFF0000CD
#define RoyalBlue				0xFF4169E1
#define Blue					0xFF0000FF
#define DodgerBlue				0xFF1E90FF
#define DeepSkyBlue				0xFF00BFFF
#define SkyBlue					0xFF87CEEB
#define LightSkyBlue			0xFF87CEFA
#define SeaGreen				0xFF2E8B57
#define MediumSeaGreen			0xFF3CB371
#define LightSeaGreen			0xFF20B2AA
#define PaleGreen				0xFF98FB98
#define SpringGreen				0xFF00FF7F
#define LawnGreen				0xFF7CFC00
#define Green					0xFF00FF00
#define Yellow					0xFFFFFF00

//#define PKDrop

#define IDC_EXIT 9000
#define IDC_MOBRELOAD 9001
#define IDC_REBOOT 9002
#define IDC_SAVEALL 9003
#define IDC_READGUILD 9004
#define IDC_READGUILDNAME 9005
#define IDC_READGAMECONFIG 9006

#define IDC_SHUTDOWNNP 9050


#define		APP_VERSION				6978

#define		GAME_PORT				8281	  // Game server listening port, client connects to it
#define		DB_PORT					7514      // DB server listening port, Game server connects to it
#define		ADMIN_PORT				8895	  // DB server listening port, NPTool connects to it

#define		MAX_SERVER				10      // Max number of game servers that can connect to DB server
#define		MAX_SERVERGROUP			10		// Max number of servers that can exist
#define		MAX_SERVERNUMBER		(MAX_SERVER+1) // DB + TMSrvs + BISrv

#define		MAX_IP_LENGTH			16

#define		SECSTANDINGBY			8
#define		SECBATTLE				8
#define		MAX_USER				1000      // Max users on CUser pUser and starting index of npcs and mobs
#define		ADMIN_RESERV			10		  // Max reserv slot in gameserver for admin's
#define		MAX_ADMIN				10        // Max number of NP that can connect to DB server

#define		MAX_DBACCOUNT			(MAX_USER * MAX_SERVER) // Max players connected to a single DBSrv at the same time
#define		MAX_RANK_INDEX			500

#pragma region Account related defines

#define		ACCOUNTNAME_LENGTH		16		// Max length of the account login
#define		ACCOUNTPASS_LENGTH		12      // Max length of the account password
#define		REALNAME_LENGTH			24      // Max length of the name of the account owner
#define		EMAIL_LENGTH			48      // Max length of the email address of the account owner
#define		ADDRESS_LENGTH			78      // Max length of the real address of the account owner
#define		TELEPHONE_LENGTH		16      // Max length of the telephone number of the account owner
#define		MOB_PER_ACCOUNT			4       // Max number of mobs an account can have

#pragma endregion

#define		MAX_EQUIP				18
#define		MAX_CARRY				64
#define		MAX_CARGO				160
 

#define		MAX_TRADE				15
#define		MAX_AUTOTRADE			12
#define		MAX_AUTOTRADETITLE		24
#define		MAX_SHOPLIST			27

#define		MAX_GROUNDMASK			6

#define		ITEM_PLACE_EQUIP		0
#define		ITEM_PLACE_CARRY		1
#define		ITEM_PLACE_CARGO		2

#define		CARGOGRIDX				9
#define		CARGOGRIDY				14
#define		CARRYGRIDX				9
#define		CARRYGRIDY				7

#define		VIEWGRIDX				33
#define		VIEWGRIDY				33
#define		HALFGRIDX				16
#define		HALFGRIDY				16

#define		MAX_GRIDX				4096
#define		MAX_GRIDY				4096

#define		MAX_ITEM				5000

#define		MAX_SUMMONLIST			50

#define		MAX_MOB					25000

#define		MAX_NPCGENERATOR		8192

#define		MAX_SKILL				24

#define		MAX_COMBINE				8

#define		MAX_CLASS				4

#define		MAX_LEVEL				399
#define		MAX_CLEVEL				199 // 199  //PARA TRAVAR LEVEL

#define		MAX_CLASSMASTER			4

#define		MAX_AFFECT				32

#define		MAX_ROUTE				24

#define		MAX_TRANS				20480
#define		MAX_ITEM_REBUY			10
#define		MAX_NOTIFY_LENGTH		96
#define		MESSAGE_LENGTH			96 
#define		MESSAGEWHISPER_LENGTH	100 

#define		NAME_LENGTH				16

#define		MH						8

#define		TIMER_SEC				0
#define		TIMER_MIN				1

#define		MAX_ITEMLIST			6500
#define		MAX_SKILLINDEX			248
#define		MAX_INITITEM			256
#define		MAX_EFFECTINDEX			255
#define		ITEMNAME_LENGTH			64
#define		MAX_STATICEFFECT		12

#define		GUILDNAME_LENGTH		12
#define		MAX_GUILD				4096
#define		MAX_GUILDZONE			5

#define		MAX_STRING				2000
#define		MAX_ENGLISH				600
#define		MAX_MAC					200
#define		MAX_ACCOUNTMAC			2

#define     MAX_CASTLE_POS			9
#define		MAX_CASTLE_QUEST		64

#define		MAX_MOB_MERC			128

#define		MAX_CAMP_QUEST			64

#define		MAX_CAMP_PRIZE			12

#define		MAX_PIN_LENGTH			37

#define		KILL_MARK				63

#define		MAX_PARTY				12

#define		ESCENE_FIELD			30000 // Identifier for the server sent messages

#define		SKIPCHECKTICK			235543242 // base number for the tick checking so people don't get kicked out before doing something
#define		MAX_TARGET				13

#define		REINO_RED				8
#define		REINO_BLUE				7

#define		MORTAL					2
#define		ARCH					1
#define		CELESTIAL				3
#define		CELESTIALCS				4
#define		SCELESTIAL				5
#define     HARDCORE                6
#define		HARDCOREA				7
#define		HARDCORECS				8
#define		SHARDCORE				9

#define		RSV_FROST    0x01
#define		RSV_DRAIN    0x02
#define		RSV_VISION   0x04
#define		RSV_PARRY    0x08
#define		RSV_HIDE	 0x10
#define		RSV_HASTE    0x20
#define		RSV_CAST     0x40
#define		RSV_BLOCK    0x80
#define		RSV_IMUNIDADE 0x100

#define		MSV_SNOOP	0x01

#define		REF_10					10
#define		REF_11					12
#define		REF_12					15
#define		REF_13					18
#define		REF_14					22
#define		REF_15					27

#define		MAX_HP					2000000
#define		MAX_MP					2000000
#define		MAX_DAMAGE				1000000
#define		MAX_DAMAGE_MG			255
#define		AFFECT_1H				450
#define		AFFECT_1D				10800

#define		SOUL_NULL				0
#define		SOUL_KIBITA				1

#define		SOUL_F					2
#define		SOUL_I					3
#define		SOUL_D					4
#define		SOUL_C					5

#define		SOUL_FI					6
#define		SOUL_FD					7
#define		SOUL_FC					8

#define		SOUL_IF					9
#define		SOUL_ID					10
#define		SOUL_IC					11

#define		SOUL_DF					12
#define		SOUL_DI					13
#define		SOUL_DC					14

#define		SOUL_CF					15
#define		SOUL_CI					16
#define		SOUL_CD					17

//////////////////// QST ////////////////////////////////////

#define	QST_AMUMISTICO			1

////////////////////MSG_Quest NPC's//////////////////////////

#define GOLD_DRAGON				1
#define AMU_MISTICO				2
#define MESTREHAB				3
#define EXPLOIT_LEADER			4
#define ARZAN_DRAGON			5
#define TREINADORNEWBIE1		6
#define TREINADORNEWBIE2		7
#define TREINADORNEWBIE3		8
#define TREINADORNEWBIE4		9
#define COMP_SEPHI				10
#define CAPAVERDE_TELEPORT		11
#define MOUNT_MASTER			12
#define ZAKUM					13
#define JEFFI					14
#define SHAMA					15
#define KING					16
#define KINGDOM					17
#define URNAMMU					18
#define CAPAVERDE_TRADE			19
#define QUEST_COVEIRO			20
#define QUEST_JARDINEIRO		21
#define QUEST_KAIZEN			22
#define QUEST_HIDRA				23
#define QUEST_ELFOS				24
#define UXMAL					25
#define MOLARGARGULA			26
#define BLACKORACLE				27
#define QUEST_CAPAREAL			28
#define CARBUNCLE_WIND			29
#define PERZEN					30
#define KIBITA					31
#define GODGOVERNMENT			32
#define SOBREVIVENTE			33
#define LIDER_APRENDIZ			34
#define GUARDA_REAL_I			35
#define GUARDA_REAL_II  		36
#define GUARDA_REAL_III 		37
#define GUARDA_REAL_IV  		38
#define GUARDA_REAL_V   		39
#define GUARDA_REAL_VI  		40
#define GUARDA_REAL_VII  		80
#define CURANDEIRA				41
#define MESTREHAB2				42
#define UPADOR   				43
#define QUEST_BENCAODEDEUS  	44
#define KRUNO                   45
#define MESTREGRIFO             46
#define QUEST_EQUILIBRIO        47
#define AMELIA                  48
#define JULIARZAN               49
#define JULIGELO                50
#define UNICORNIO_PURO          51
#define EVENTO_DROP				52
#define BATALHA_REAL			53
#define XAMACOLISEU				54
#define TELEPORTEVENTO1  		55
#define TELEPORTEVENTO2  		56
#define TELEPORTEVENTO3  		57
#define TELEPORTEVENTO4  		58
#define LANHOUSEN  				59
#define LANHOUSEM		  		60
#define LANHOUSEA		  		61
#define GUARDACARGA		  		62
#define FRAGMENTODAALMA  		63
#define BATLEROYALE		        64

/////////////////////////////////////////////////////////////
#define Escuridao							299
#define Kara								300
#define Kei									301
#define Erin								302
#define Kemi								303
#define Fenix								304
#define Yue									305
#define Leao								306
///////////////////////NPCGENER IDS//////////////////////////

#define ZAKUM_LORD							4
#define ORC_GUERREIRO						3

#define REI_HARABARD						8
#define REI_GLANTUAR						9

#define TORRE_NOATUM1						23
#define TORRE_NOATUM2						24
#define TORRE_NOATUM3						25

#define WATER_M_INITIAL						10
#define WATER_N_INITIAL						171
#define WATER_A_INITIAL						183

#define ORC_ARQUEIRO                        1697

#define SECRET_ROOM_N_INITIAL				2395

#define SECRET_ROOM_N_SALA1_MOB_1			2395
#define SECRET_ROOM_N_SALA1_MOB_2			2396
#define SECRET_ROOM_N_SALA2_MOB_1			2397
#define SECRET_ROOM_N_SALA2_MOB_2			2398
#define SECRET_ROOM_N_SALA3_MOB_1			2399
#define SECRET_ROOM_N_SALA3_MOB_2			2400
#define SECRET_ROOM_N_SALA4_MOB_1			2401
#define SECRET_ROOM_N_SALA4_MOB_2			2402
#define SECRET_ROOM_N_SALA4_MOB_3			2403
#define SECRET_ROOM_N_SALA4_MOB_4			2404

#define SECRET_ROOM_N_END					2402
#define SECRET_ROOM_N_BOSS_INITIAL			2403

#define SECRET_ROOM_M_INITIAL				2405

#define SECRET_ROOM_M_SALA1_MOB_1			2405
#define SECRET_ROOM_M_SALA1_MOB_2			2406
#define SECRET_ROOM_M_SALA2_MOB_1			2407
#define SECRET_ROOM_M_SALA2_MOB_2			2408
#define SECRET_ROOM_M_SALA3_MOB_1			2409
#define SECRET_ROOM_M_SALA3_MOB_2			2410
#define SECRET_ROOM_M_SALA4_MOB_1			2411
#define SECRET_ROOM_M_SALA4_MOB_2			2412
#define SECRET_ROOM_M_SALA4_MOB_3			2413
#define SECRET_ROOM_M_SALA4_MOB_4			2414

#define SECRET_ROOM_M_END					2412
#define SECRET_ROOM_M_BOSS_INITIAL			2413

#define SECRET_ROOM_A_INITIAL				2415

#define SECRET_ROOM_A_SALA1_MOB_1			2415
#define SECRET_ROOM_A_SALA1_MOB_2			2416
#define SECRET_ROOM_A_SALA2_MOB_1			2417
#define SECRET_ROOM_A_SALA2_MOB_2			2418
#define SECRET_ROOM_A_SALA3_MOB_1			2419
#define SECRET_ROOM_A_SALA3_MOB_2			2420
#define SECRET_ROOM_A_SALA4_MOB_1			2421
#define SECRET_ROOM_A_SALA4_MOB_2			2422
#define SECRET_ROOM_A_SALA4_MOB_3			2423
#define SECRET_ROOM_A_SALA4_MOB_4			2424

#define SECRET_ROOM_A_END					2422
#define SECRET_ROOM_A_BOSS_INITIAL			2423

#define NIGHTMARE_N_INITIAL					2368
#define NIGHTMARE_N_END						2375

#define NIGHTMARE_M_INITIAL					2377
#define NIGHTMARE_M_END						2384

#define NIGHTMARE_A_INITIAL					2385
#define NIGHTMARE_A_END						2394

#define RUNEQUEST_LV0_LICH1					5653
#define RUNEQUEST_LV0_LICH2					5654

#define RUNEQUEST_LV1_TORRE1				5706
#define RUNEQUEST_LV1_TORRE2				5707
#define RUNEQUEST_LV1_TORRE3				5708

#define RUNEQUEST_LV1_MOB_INITIAL			5709
#define RUNEQUEST_LV1_MOB_END				5764

#define RUNEQUEST_LV2_MOB_BOSS				5789
#define RUNEQUEST_LV2_MOB_INITIAL			5790
#define RUNEQUEST_LV2_MOB_END				5848

#define RUNEQUEST_LV3_MOB_SULRANG_INITIAL	5972
#define RUNEQUEST_LV3_MOB_SULRANG_END		5975

#define RUNEQUEST_LV3_MOB_BOSS_INITIAL		5948
#define RUNEQUEST_LV3_MOB_BOSS_END			5955

#define RUNEQUEST_LV4_MOB_INITIAL			5854
#define RUNEQUEST_LV4_MOB_END				5898
#define RUNEQUEST_LV4_MOB_BOSS				5849

#define RUNEQUEST_LV5_MOB_BOSS				5899

#define RUNEQUEST_LV6_MOB_INITIAL			5775
#define RUNEQUEST_LV6_MOB_END				5785
#define RUNEQUEST_LV6_MOB_INITIAL2			5768
#define RUNEQUEST_LV6_MOB_END2				5774
#define RUNEQUEST_LV6_MOB_BOSS				5767

#define RVRTORRE_1							4236
#define RVRTORRE_2							4237

#define GTORRE								1078

#define KEFRA_BOSS							396
#define KEFRA_MOB_INITIAL					397
#define KEFRA_MOB_END						400
#define CHEFE_DE_TREINO						3140

//////////////////////////////////castelo do gelo//////////////////////////////////////
#define SOMBRANEGRA							4655
#define ESPELHO_RAINHAG						4653
#define VERIDRAINHAG						4654

#define BOSS1_INITIAL						4041
#define BOSS1_END							4066
#define BOSS1_INITIAL2						4041
#define BOSS1_END2							4066
//////////////////////////////////zona inf//////////////////////////////////////
#define PI_INITIAL1							4656 // Inicio
#define PI_END1								4665
#define TARANTULA							4666
#define CTARANTULA							4667

#define PI_INITIAL2							4668 // Quadra 1
#define PI_END2								4676
#define LICHBOSS1							4677

#define PI_INITIAL3							4678 // Quadra 2
#define PI_END3								4686
#define LICHBOSS2							4687

#define PI_INITIAL4							4689 // Quadra 3
#define PI_END4								4697
#define LICHBOSS3							4698

#define PI_INITIAL5							4688 // Quadra 4
#define PI_END5								4696
#define LICHBOSS4							4697

#define PI_INITIAL6							4708
#define PI_END6								4721

////////////////////////////////////////////////////////////


typedef struct
{
	char min, hora, dia, mes, ano;

	char Permanente, Analyze;



	char Grade[102];

}AccountBanned;
typedef struct
{
	char min, hora, dia, mes, ano;

	char Grade[102];
	char AccountDay[ACCOUNTNAME_LENGTH];
}AccountDiaria;
enum Diaria
{

	Tempo1dia,

};

enum Banned
{
	Tempo3horas,
	Tempo3dias,
	Tempo7dias,
	Tempo15dias,
	Tempo30dias,
	Permanente,
	Analise,
	Mac,
};
#pragma endregion
struct MSG_Diaria
{
	short NumMobs;
	short NumMobs1;
	short NumMobs2;
	short NumMobs3;
	short NumMobs4;
	short NumMobs5;
	short NumMobs6;
	short NumMobs7;

	struct
	{
		char Name[16];
	} Members[1000];
};
#pragma region Structures

struct MSG_BattleReal
{
	short Vidas;
	short NumMembers;
	int Reward;
	short Timer;
	char WeekWinner[16];
	char WinningSpree;
	bool start;
	struct
	{
		short Id;
		int MacId;
		char Name[16];
	} Members[60];
};

struct STRUCT_ITEM
{
	short sIndex;
	union
	{
		short sValue;

		struct
		{
			unsigned char cEffect;
			unsigned char cValue;
		};

	}stEffect[3];

	bool EquipCostume()
	{
		//Trajes communs
		if (this->sIndex >= 4150 && this->sIndex <= 4189)
			return true;

		//Trajes novos
		if (this->sIndex >= 4300 && this->sIndex < 4430)
			return true;

		return false;
	}
	int GetTimePet(int DefaultValue = 30)
	{
		//3 Dias
		if (this->sIndex >= 3980 && this->sIndex <= 3982)
			return 3;
		//15 Dias
		else if (this->sIndex >= 3983 && this->sIndex <= 3985)
			return 15;
		//30 Dias
		else if (this->sIndex >= 3986 && this->sIndex <= 3989)
			return 30;

		//Other
		return DefaultValue;
	}
	bool EsferaPet()
	{
		//Esferas communs
		if (this->sIndex >= 3980 && this->sIndex <= 3992)
			return true;

		//Esferas novos
		if (this->sIndex >= 3995 && this->sIndex < 3999)
			return true;

		return false;
	}
	unsigned char getSancValue()
	{
		if (this->sIndex >= 2360 && this->sIndex <= 2389)
			return this->stEffect[2].cValue;

		if (this->stEffect[0].cEffect == 43)
			return this->stEffect[0].cValue;
		else if (this->stEffect[1].cEffect == 43)
			return this->stEffect[1].cValue;
		else if (this->stEffect[2].cEffect == 43)
			return this->stEffect[2].cValue;

		else if (this->stEffect[0].cEffect >= 116 && this->stEffect[0].cEffect <= 125)
			return this->stEffect[0].cValue;

		else if (this->stEffect[1].cEffect >= 116 && this->stEffect[1].cEffect <= 125)
			return this->stEffect[1].cValue;

		else if (this->stEffect[2].cEffect >= 116 && this->stEffect[2].cEffect <= 125)
			return this->stEffect[2].cValue;

		else
			return 0;
	}
	void Item(int Item, int cEF0, int cVA0, int cEF1, int cVA1, int cEF2, int cVA2)
	{
		this->sIndex = Item;
		this->stEffect[0].cEffect = cEF0;
		this->stEffect[0].cValue = cVA0;
		this->stEffect[1].cEffect = cEF1;
		this->stEffect[1].cValue = cVA1;
		this->stEffect[2].cEffect = cEF2;
		this->stEffect[2].cValue = cVA2;
	}
	short Amount()
	{
		int amount = 0;
		if (stEffect[0].cEffect == 61 || stEffect[1].cEffect == 61 || stEffect[2].cEffect == 61)
		{
			if (stEffect[0].cEffect == 61)
				amount = stEffect[0].cValue;
			else if (stEffect[1].cEffect == 61)
				amount = stEffect[1].cValue;
			else
				amount = stEffect[2].cValue;
		}

		return amount == 0 ? 1 : amount;
	}
	void AmountMinus()
	{
		short amount = Amount();
		if (amount > 1) {
			if ((amount - 1) == 1)
				this->clearAddons();
			else {
				SetAmount(amount - 1);
			}
		}
		else {
			clear();
		}
	}
	void AmountMinus(short  Count) {
		short amount = Amount();
		if (amount > Count) {
			if ((amount - Count) == 1)
				this->clearAddons();
			else {
				SetAmount(amount - Count);
			}
		}
		else {
			clear();
		}
	}
	void clear()
	{
		this->sIndex = 0;
		this->stEffect[0].cEffect = 0;
		this->stEffect[0].cValue = 0;
		this->stEffect[1].cEffect = 0;
		this->stEffect[1].cValue = 0;
		this->stEffect[2].cEffect = 0;
		this->stEffect[2].cValue = 0;
	}
	void clearAddons()
	{
		this->stEffect[0].cEffect = 0;
		this->stEffect[0].cValue = 0;
		this->stEffect[1].cEffect = 0;
		this->stEffect[1].cValue = 0;
		this->stEffect[2].cEffect = 0;
		this->stEffect[2].cValue = 0;
	}
	char SetAmount(char Amount)
	{
		if (stEffect[0].cEffect == 61 || stEffect[1].cEffect == 61 || stEffect[2].cEffect == 61) {

			if (stEffect[0].cEffect == 61)
				stEffect[0].cValue = Amount;

			else if (stEffect[1].cEffect == 61)
				stEffect[1].cValue = Amount;

			else
				stEffect[2].cValue = Amount;
		}
		else if (stEffect[0].cEffect == 0 || stEffect[1].cEffect == 0 || stEffect[2].cEffect == 0)
		{
			if (stEffect[0].cEffect == 0) {
				stEffect[0].cEffect = 61;
				stEffect[0].cValue = Amount;
			}
			else if (stEffect[1].cEffect == 0) {
				stEffect[1].cEffect = 61;
				stEffect[1].cValue = Amount;
			}
			else
			{
				stEffect[2].cEffect = 61;
				stEffect[2].cValue = Amount;
			}
		}
		return Amount;
	}
};
 
struct STRUCT_SCORE // SIZE 44
{
	short Level;
	int Ac;
	int Damage;
	char Reserved;
	char AttackRun;
	int MaxHp;
	int MaxMp;
	int Hp;
	int Mp;
	short Str;
	short Int;
	short Dex;
	short Con;
	unsigned short Special[4];
};

struct STRUCT_MOB
{
	char MobName[16];
	char Clan;
	char Merchant;
	unsigned short Guild;
	char Class;
	char Rsv;
	unsigned short Quest;
	int Coin;
	long long Exp;
	unsigned short HomeTownX;
	unsigned short HomeTownY;
	STRUCT_SCORE BaseScore;
	STRUCT_SCORE CurrentScore;
	STRUCT_ITEM Equip[20];
	STRUCT_ITEM Carry[64];
	unsigned int LearnedSkill[2];
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	uint8_t  Critical;
	char SaveMana;
	char ShortSkill[4];
	char GuildLevel;
	unsigned short Magician;
	char RegenHP;
	char RegenMP;
	char Resist[4];


	bool HasSoulSkill() const
	{
		return this->LearnedSkill[0] & 0x40000000;
	}
};


//int ee = sizeof STRUCT_MOB;
//int ee = sizeof STRUCT_MOBEXTRA;
struct STRUCT_MOBEXTRA
{
	BYTE  ClassMaster;
	BYTE  Citizen;
	unsigned short	  Fame;
	BYTE  Soul;
	unsigned short MortalFace;

	struct
	{
		BYTE Circle;

		struct
		{
			BYTE Newbie;//00_01_02_03_04  quest com quatro etapas
			BYTE TerraMistica;//0 : não pegou a quest 1: pegou a quest e não concluiu 2: quest completa
			BYTE MolarGargula;
			BYTE PilulaOrc;
		}Mortal;

		struct
		{
			BYTE MortalSlot;
			BYTE MortalLevel;
			BYTE Level355;
			BYTE Level370;
			BYTE Cristal;//00_01_02_03_04 quest com quatro etapas
		}Arch;

		struct
		{
			unsigned short ArchLevel;
			unsigned short CelestialLevel;
			unsigned short SubCelestialLevel;
			BYTE Lv40;
			BYTE Lv90;
			BYTE Lv240;
			BYTE Lv280;
			BYTE Lv320;
			BYTE Lv360;
			BYTE Add120;
			BYTE Add150;
			BYTE Add180;
			BYTE Add200;
			BYTE Arcana;
			BYTE Reset;
		}Celestial;

	}QuestInfo;

	struct
	{
		BYTE Class;

		long long   Exp;			  // The ammount of experience the mob has to level up

		short		   SPX;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll
		short		   SPY;			 // The Y position saved by the stellar gem, to teleport the mob there when using warp scroll

		STRUCT_SCORE   BaseScore;    // The base score of the mob 

		long LearnedSkill; // The skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)
		long nLearnedSkill; // The new skills the mob learned, divided into four categories (00 _ 00 _ 00 _ 00)

		unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
		unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
		unsigned short SkillBonus;	 // The points the mob can use to buy skills

		unsigned char  SkillBar1[4];  // The skills saved on the first 4 slots of the skill bar
		unsigned char  SkillBar2[16];  // The skills saved on the first 4 slots of the skill bar

		BYTE Soul;
 
	}SaveCelestial[2];


	char EMPTY[240];
 
	time_t DivineEnd;

	time_t LastNT;
	unsigned short NT;

	unsigned short KefraTicket;

	unsigned int Hold;

};


//int rrr = sizeof STRUCT_MOBEXTRA;

struct STRUCT_AFFECT
{
	unsigned char Type;
	unsigned char Value;
	unsigned short Level;
	int Time;
};

struct STRUCT_LEVELBONUS
{
	unsigned short Level;
	unsigned short ScoreBonus;   // The points the mob can use to increase score (Str, Int, Dex, Con)
	unsigned short SpecialBonus; // The points the mob can use to increase special, to increase effect of learned skills (score->Special[4])
	unsigned short SkillBonus;	 // The points the mob can use to buy skills
	unsigned short Ac;
};

struct STRUCT_CAPSULE
{
	STRUCT_MOB MOB;
	STRUCT_MOBEXTRA extra;
};

struct STRUCT_BEASTBONUS
{
	int Unk; // MinDamAdd ? // 0
	int Unk2; // MaxDamAdd ? // 4
	int Unk3; // MinAcAdd ? // 8
	int Unk4; // MaxAcAdd ? //12
	int Unk5; // MinHpAdd ? // 16
	int Unk6; // MaxHpAdd ? // 20
	int Unk7; // RunSpeedBonus ? // 24
	int Unk8; // 28
	int Unk9; // AttackSpeedBonus ? // 32
	int Unk10; // 36
	int Unk11; // 40
	int Unk12; // 44 
	int Unk13; // 48
	int Unk14; // 52
	int Unk15; // 56
	int Unk16; // 60
	int Unk17; // BaseSanc ? // 64
};

struct STRUCT_TREASURE
{
	short Source;

	STRUCT_ITEM Target[5];

	short Rate[5];
};
enum TNColor
{
	None = 0xFF000000,//0x+ cod da cor em hexadecimal
	CornBlueName = None | 0xAAAAFF,
	CornBlue = None | 0x6495ED,
	NewYellow = None | 0xFFFF00,
	GoldenEscuro = None | 0xfeaa00,
	GreenYellow = None | 0xADFF2F,
	GoldenClaro = None | 0xfefeaa,
	DeepPink = None | 0xFF1493,
	Default = None | 0xCCAAFF,
	NewWhite = None | 0xFFFFFF,
	NewBlue = None | 0x0174DF,
	Orange = None | 0xCD6600,  //laranja escuro
	Red = None | 0xFF2F4F4F,
	DarkOrange = None | 0xFFFF5500, //laranja claro
	Speak = 0xFFFF5500 //verde padrão do /gritar

};

struct STRUCT_PISTA
{
	struct
	{
		short LeaderID;
		char  LeaderName[NAME_LENGTH];

		int Sala;
		int MobCount;
	}Party[3];
};

struct STRUCT_CASTLEQUEST
{
	int MOB_INITIAL;
	int MOB_END;
	int BOSS[2];

	STRUCT_ITEM Prize[MAX_CARRY];
	int			CoinPrize;
	int			ExpPrize[6];
	int			PartyPrize;

	int			QuestTime;
};

struct STRUCT_MERC
{
	int GenerateIndex;
	char MobName[NAME_LENGTH];

	STRUCT_ITEM Carry[MAX_CARRY];
	short		Stock[MAX_CARRY];
	short		MaxStock[MAX_CARRY];
	int			RenewTime;
	int			RebornTime;
};

struct STRUCT_CAMP
{
	int			BauIndex;
	int			BauQuest;
	char		BauName[256];
	int			KeyIndex;

	int			MOB_INITIAL;
	int			MOB_END;

	int			MobX;
	int			MobY;
	int			BauX;
	int			BauY;
	int			BauRotate;


	STRUCT_ITEM Prize[MAX_CAMP_PRIZE];
	int			CoinPrize;
	int			ExpPrize[6];
	int			PartyPrize;

	int			RenewTime;
};

struct STRUCT_ITEMLOG
{
	int	Num;
};

struct STRUCT_GUILDZONE
{
	int ChargeGuild;
	int ChallangeGuild;

	int GuildSpawnX;
	int GuildSpawnY;

	int CitySpawnX;
	int CitySpawnY;

	int CityLimitX1;
	int CityLimitY1;
	int CityLimitX2;
	int CityLimitY2;

	int WarAreaX1;
	int WarAreaY1;
	int WarAreaX2;
	int WarAreaY2;

	int ChargeWarSpawnX;
	int ChargeWarSpawnY;

	int ChallangeWarSpawnX;
	int ChallangeWarSpawnY;

	int CityTax;
	int Clan;
	int Victory;
};

struct STRUCT_SEALOFSOUL
{
	int Read;
	int MortalClass;
	int ClassCele;
	int SubClass;
	int LevelCele;
	int LevelSub;
	int For;
	int Int;
	int Dex;
	int Con;
	int ScoreBonus;
	int SkillPoint;
	int ArchQuest;
	int CelestialQuest;
	int ArcanaQuest;
};

struct STRUCT_SELCHAR
{
	short SPX[4];
	short SPY[4];
	char Name[4][16];

	STRUCT_SCORE Score[4];
	STRUCT_ITEM  Equip[4][MAX_EQUIP];

	unsigned short Guild[4];

	int Coin[4];
	long long Exp[4];
};

struct STRUCT_ACCOUNTINFO
{
	char AccountName[ACCOUNTNAME_LENGTH];
	char AccountPass[ACCOUNTPASS_LENGTH];

	char RealName[REALNAME_LENGTH];
	int  SSN1;
	int  SSN2;
	char Email[EMAIL_LENGTH];
	char Telephone[TELEPHONE_LENGTH];
	char Address[ADDRESS_LENGTH];
	char NumericToken[6];

	int Year;
	int YearDay;
};
typedef struct
{
	short Fame;

	char Clan;
	char Citizen;

	char Sub1;
	char Sub2;
	char Sub3;
} STRUCT_GUILDINFO;

#pragma pack(push, 1)
struct STRUCT_RANKING
{
	STRUCT_RANKING()
	{
		Name[0] = '\0';
		Value = 0;
		ClassMaster = 0;
		Level = 0;
		Class = 0;
	}

	STRUCT_RANKING(char* name, long long value, int classvalue, int level, int cls, int g, int clan)
	{
		strncpy(Name, name, sizeof(Name));
		Value = value;
		ClassMaster = classvalue;
		Level = level;
		Class = cls;
		GuildIndex = g;
		Clan = clan;
	}

	char Name[32];
	long long Value;
	int ClassMaster;
	int Level;
	int Class;
	int GuildIndex;
	int Clan;
};
#pragma pack(pop)
#pragma endregion

#pragma region File Structures

struct stPosition
{
	short X;

	short Y;
};


struct STRUCT_ACCOUNTFILE
{
	STRUCT_ACCOUNTINFO Info; // 0 - 216

	STRUCT_MOB	Char[MOB_PER_ACCOUNT]; // 216 - 3480
	STRUCT_ITEM Cargo[MAX_CARGO]; // 3480 - 4504
	int			Coin; // 4504 - 4508
	unsigned char ShortSkill[MOB_PER_ACCOUNT][16]; // 4508 - 4572

	STRUCT_AFFECT affect[MOB_PER_ACCOUNT][MAX_AFFECT];
	STRUCT_MOBEXTRA mobExtra[MOB_PER_ACCOUNT];

	char TempKey[52];
	int Donate;
	int Honra;
	int Admin;
	int chave1;
	int chave2;
	int chave3;
	int NumMobs;
	int NumMobs1;
	int NumMobs2;
	int NumMobs3;
	int NumMobs4;
	int NumMobs5;
	int NumMobs6;
};
 

struct STRUCT_SPELL
{
	int	SkillPoint;
	int	TargetType;
	int	ManaSpent;
	int	Delay;
	int	Range;
	int	InstanceType;
	int	InstanceValue;
	int	TickType;
	int	TickValue;
	int	AffectType;
	int	AffectValue;
	int	AffectTime;
	unsigned char Act[8];
	unsigned char Act2[8];
	int	InstanceAttribute;
	int	TickAttribute;
	int	Aggressive;
	int	MaxTarget;
	int	bParty;
	int	AffectResist;
	int	Passive;
	int UseOnMacro;
};

struct STRUCT_ITEMLIST
{
	char				Name[ITEMNAME_LENGTH];
	short				IndexMesh;
	short				IndexTexture;
	short				IndexVisualEffect;
	short				ReqLvl;
	short				ReqStr;
	short				ReqInt;
	short				ReqDex;
	short				ReqCon;

	struct
	{
		short sEffect;
		short sValue;

	} stEffect[MAX_STATICEFFECT];

	int					Price;  
	short				nUnique; 
	short               Unk;
	int 				nPos;  
	short				Extra;  
	short				Grade;  
	int                 FameRequest;
	short               MountType;
	short               MountData;
};

struct STRUCT_INITITEM
{
	short PosX;
	short PosY;
	short ItemIndex;
	short Rotate;
};

struct STRUCT_BLOCKMAC
{
	int Mac[4];
};

#pragma endregion

#pragma region Messages defines and structures

#define _MSG      	short		  Size;			\
					char		  KeyWord;		\
					char		  CheckSum;		\
					short		  Type;			\
					short		  ID;			\
					unsigned int  ClientTick;

const int FLAG_GAME2CLIENT			= 0x0100;
const int FLAG_CLIENT2GAME			= 0x0200;

const int FLAG_DB2GAME				= 0x0400;
const int FLAG_GAME2DB				= 0x0800;

const int FLAG_DB2NP				= 0x1000;
const int FLAG_NP2DB				= 0x2000;

const int FLAG_NEW					= 0x4000;

struct		 MSG_STANDARD
{
	_MSG;
};

struct		 MSG_STANDARDPARM
{
	_MSG;
	int Parm;
};

struct		 MSG_STANDARDPARM2
{
	_MSG;
	int Parm1;
	int Parm2;
};

struct		 MSG_STANDARDSHORTPARM2	
{
	_MSG;
	short Parm1;
	short Parm2;
};

struct		 MSG_STANDARDPARM3
{
	_MSG;
	int Parm1;
	int Parm2;
	int Parm3;
};

const short _MSG_DBMessagePanel				= (1 | FLAG_DB2GAME);
const short _MSG_DBMessageBoxOk				= (2 | FLAG_DB2GAME);
const short _MSG_DBAccountLogin				= (3 | FLAG_GAME2DB);
const short _MSG_DBCharacterLogin			= (4 | FLAG_GAME2DB);
const short _MSG_DBNoNeedSave				= (5 | FLAG_GAME2DB);

const short _MSG_DBSaveMob					= (7 | FLAG_GAME2DB);
struct		 MSG_DBSaveMob
{
	_MSG;

	int             Slot;
	STRUCT_MOB      MOB;
	STRUCT_ITEM     Cargo[MAX_CARGO];
	int				Coin;
	unsigned char			ShortSkill[16];
	char			AccountName[ACCOUNTNAME_LENGTH];
	int				Export;
	STRUCT_MOBEXTRA extra;
	STRUCT_AFFECT	affect[MAX_AFFECT];
	int Donate;
	int Honra;
	int Admin;
	int chave1;
	int chave2;
	int chave3;
	int NumMobs;
	int NumMobs1;
	int NumMobs2;
	int NumMobs3;
	int NumMobs4;
	int NumMobs5;
	int NumMobs6;
};

const short _MSG_DBDeleteCharacter			= (9 | FLAG_GAME2DB);
const short _MSG_DBUpdateSapphire			= (10 | FLAG_GAME2DB);

const short _MSG_DBSavingQuit				= (10 | FLAG_DB2GAME);
struct		 MSG_DBSavingQuit
{
	_MSG;
	char AccountName[ACCOUNTNAME_LENGTH];
	int  Mode;
};

const short _MSG_DBCNFAccountLogOut			= (11 | FLAG_DB2GAME);

const short _MSG_MessageDBRecord			= (12 | FLAG_GAME2DB);
struct		 MSG_MessageDBRecord
{
	_MSG;
	char Record[256];
};

const short _MSG_GuildZoneReport			= (13 | FLAG_GAME2DB);
struct		 MSG_GuildZoneReport
{
	_MSG;
	int	Guild[MAX_GUILDZONE];
};

const short _MSG_DBCNFArchCharacterSucess	= (14 | FLAG_DB2GAME);
const short _MSG_DBCNFArchCharacterFail		= (15 | FLAG_DB2GAME);

const short _MSG_DBCNFCapsuleCharacterFail	= (16 | FLAG_DB2GAME);
const short _MSG_DBCNFCapsuleCharacterFail2 = (17 | FLAG_DB2GAME);

const short _MSG_DBCNFCapsuleSucess			= (18 | FLAG_DB2GAME);
const short _MSG_DBClientMessage			= (19 | FLAG_DB2GAME);
struct		 MSG_DBClientMessage
{
	_MSG;
	
	char String[MESSAGE_LENGTH];
};

const short _MSG_DBCheckPrimaryAccount		= (20 | FLAG_DB2GAME);
struct		 MSG_DBCheckPrimaryAccount
{
	_MSG;

	char AccountName[ACCOUNTNAME_LENGTH];

	unsigned int Mac[4];
};

const short _MSG_DBCNFServerChange			= (42 | FLAG_DB2GAME | FLAG_GAME2CLIENT); //SignalParm
struct		 MSG_DBCNFServerChange
{
	_MSG;

	char AccountName[ACCOUNTNAME_LENGTH];
	char Enc[52];
};
const short _MSG_DBServerSend1				= (43 | FLAG_DB2GAME | FLAG_GAME2CLIENT); //SignalParm

const short _MSG_DBServerChange				= (20 | FLAG_GAME2DB);
struct		 MSG_DBServerChange
{
	_MSG;

	int NewServerID;
	int Slot;
};
const short _MSG_DBItemDayLog				= (21 | FLAG_GAME2DB); //SignalParm

const short _MSG_PartyEvocation = (234 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_PartyEvocation
{
	_MSG; // 0 - 11

	short Leader; // 12 - 13
	short EvocationList[MAX_PARTY]; // 14 - 37

	char Unknown[2]; // 38 - 39
};


const short _MSG_DBActivatePinCode			= (22 | FLAG_GAME2DB);
struct		 MSG_DBActivatePinCode
{
	_MSG;

	char PinCode[MAX_PIN_LENGTH];

	char AccountName[ACCOUNTNAME_LENGTH];
	char MobName[NAME_LENGTH];

	unsigned int  Mac[4];
	unsigned int IP;
};

const short _MSG_DBPrimaryAccount			= (23 | FLAG_GAME2DB);
struct		 MSG_DBPrimaryAccount
{
	_MSG;

	unsigned int  Mac[4];
	unsigned int IP;
};

const short _MSG_DBCNFAccountLogin			= (22 | FLAG_DB2GAME);
struct		 MSG_DBCNFAccountLogin // TODO : Check and rename if it's used for MSG_CNFAccountLogin, rename to MSG_CNFAccountLogin and change references in DB source
{
	_MSG;

	char HashKeyTable[16];

	int Unknow_28;

	STRUCT_SELCHAR sel;
	STRUCT_ITEM Cargo[MAX_CARGO];
	BYTE Vago[64];
	int Coin;
	char AccountName[ACCOUNTNAME_LENGTH];
	char Keys[12];
	int Donate;
	int Honra;
	int Admin;
	int chave1;
	int chave2;
	int chave3;

	int NumMobs;
	int NumMobs1;
	int NumMobs2;
	int NumMobs3;
	int NumMobs4;
	int NumMobs5;
	int NumMobs6;
};

 

const short _MSG_DBCNFCharacterLogin		= (23 | FLAG_DB2GAME);
const short _MSG_DBCNFNewCharacter			= (24 | FLAG_DB2GAME);
const short _MSG_DBCNFDeleteCharacter		= (25 | FLAG_DB2GAME);
const short _MSG_DBNewAccountFail			= (26 | FLAG_DB2GAME);

const short _MSG_DBCharacterLoginFail		= (28 | FLAG_DB2GAME);
const short _MSG_DBNewCharacterFail			= (29 | FLAG_DB2GAME);
const short _MSG_DBDeleteCharacterFail		= (30 | FLAG_DB2GAME);
const short _MSG_DBAlreadyPlaying			= (31 | FLAG_DB2GAME);
const short _MSG_DBStillPlaying				= (32 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Account = (33 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Pass	= (34 | FLAG_DB2GAME);
const short _MSG_DBSetIndex					= (35 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Block	= (36 | FLAG_DB2GAME);
const short _MSG_DBAccountLoginFail_Disable = (37 | FLAG_DB2GAME);
const short _MSG_DBOnlyOncePerDay			= (38 | FLAG_DB2GAME);

const short _MSG_GuildReport				= (39 | FLAG_DB2GAME);
struct		 MSG_GuildReport
{
	_MSG;
	int ChargedGuildList[MAX_SERVER][MAX_GUILDZONE];
};



//////////////////////////////////////////////////////////////////////
//																	//
//							 TM > DB								//
//																	//
//////////////////////////////////////////////////////////////////////

const short  _MSG_DBNewAccount				= (1 | FLAG_GAME2DB);
struct		  MSG_NewAccount
{
	_MSG;
	STRUCT_ACCOUNTINFO AccountInfo;
	int hue;
};

const short _MSG_DBCreateCharacter			= (2 | FLAG_GAME2DB);

const short _MSG_DBCreateArchCharacter		= (31 | FLAG_GAME2DB);
struct		 MSG_DBCreateArchCharacter
{
	_MSG;

	char MobName[NAME_LENGTH];
	int  MobClass;
	int  MortalFace;
	int  MortalSlot;
	bool isDivina;
	int DivinaTimer;
	int DivinaEndTimer;
};

const short  _MSG_SavingQuit			    = (6 | FLAG_GAME2DB);
struct		  MSG_SavingQuit
{
	_MSG;

	int             Slot;
	STRUCT_MOB      MOB;
	STRUCT_ITEM     Cargo[MAX_CARGO];
	int				Coin;
	unsigned char			ShortSkill[16];
	char			AccountName[ACCOUNTNAME_LENGTH];
	STRUCT_MOBEXTRA extra;
	STRUCT_AFFECT	affect[MAX_AFFECT];
	int Donate;
	int Honra;
	int Admin;
	int chave1;
	int chave2;
	int chave3;	
	int NumMobs;
	int NumMobs1;
	int NumMobs2;
	int NumMobs3;
	int NumMobs4;
	int NumMobs5;
	int NumMobs6;
};

const short	_MSG_MessageDBImple				= (11 | FLAG_GAME2DB | FLAG_DB2GAME); //   Parm 
struct		 MSG_MessageDBImple
{
	_MSG;
	int  Level;
	char String[MESSAGE_LENGTH];
};

//////////////////////////////////////////////////////////////////////
//																	//
//					    	 Client <> TM	     					//
//																	//
//////////////////////////////////////////////////////////////////////

const short  _MSG_MessagePanel				= (1 | FLAG_GAME2CLIENT);
struct		  MSG_MessagePanel
{
	_MSG;
	char     String[128]; //Correct size to fix SendScore Hp Bug
};

const short  _MSG_MessageBoxOk				= (2 | FLAG_GAME2CLIENT);
struct		  MSG_MessageBoxOk
{
	_MSG;
	int Useless1;
	int Useless2;
	char String[MESSAGE_LENGTH];
};

const short  _MSG_AccountLogin				= (13 | FLAG_CLIENT2GAME);
const short  _MSG_CNFAccountLogin			= (10 | FLAG_GAME2CLIENT);
#pragma pack(push, 1)
struct		  MSG_AccountLogin
{
	_MSG;

	char AccountPassword[ACCOUNTPASS_LENGTH];
	char AccountName[ACCOUNTNAME_LENGTH];
	char Zero[52];
	int  ClientVersion;
	int  DBNeedSave;
    int AdapterInfos[4];
};

struct		  MSG_AccountLogin_HWID
{
	_MSG;

	char AccountPassword[ACCOUNTPASS_LENGTH];
	char AccountName[ACCOUNTNAME_LENGTH];

	char Zero[52];

	int  ClientVersion;

	int  DBNeedSave;

	int AdapterName[4];

	char HwId[50];
};
#pragma pack(pop)

const short  _MSG_AccountSecure				= (222 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
const short  _MSG_AccountSecureFail			= (223 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct		  MSG_AccountSecure
{
	_MSG;

	char NumericToken[6];
	char Unknown[10];
	int ChangeNumeric;
};

const short  _MSG_CreateCharacter			= (15 | FLAG_CLIENT2GAME);
struct		  MSG_CreateCharacter
{
	_MSG;

	int  Slot;
	char MobName[NAME_LENGTH];
	int  MobClass;

	bool isDivina;
	int DivinaTimer;
	int DivinaEndTimer;
};

const short  _MSG_DeleteCharacter			= (17 | FLAG_CLIENT2GAME);
struct		  MSG_DeleteCharacter
{
	_MSG;
	int Slot;
	char MobName[NAME_LENGTH];
	char Password[12];
};

const short _MSG_War						= (14 | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);

const short	_MSG_DBSendItem					= (15 | FLAG_GAME2DB | FLAG_DB2GAME); // 0xC0F
struct		 MSG_DBSendItem
{
	_MSG;
	int Result;
	char Account[ACCOUNTNAME_LENGTH];
	STRUCT_ITEM	Item;
};

const short	_MSG_DBSendDonate				= (17 | FLAG_GAME2DB | FLAG_DB2GAME); // 0xC0F
struct		 MSG_DBSendDonate
{
	_MSG;
	int Result;
	char Account[ACCOUNTNAME_LENGTH];
	int Donate;
	int Honra;
	int chave1;
	int chave2;
	int chave3;
	int NumMobs;
	int NumMobs1;
	int NumMobs2;
	int NumMobs3;
	int NumMobs4;
	int NumMobs5;
	int NumMobs6;
};

const short  _MSG_CNFNewCharacter			= (16 | FLAG_GAME2CLIENT);
struct		  MSG_CNFNewCharacter
{
	_MSG;

	STRUCT_SELCHAR sel;
};

const short  _MSG_CNFDeleteCharacter		= (18 | FLAG_GAME2CLIENT);
struct		  MSG_CNFDeleteCharacter
{
	_MSG;

	STRUCT_SELCHAR sel;
};

const short _MSG_GuildAlly					= (18 | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);
struct		 MSG_GuildAlly
{
	_MSG;

	int Guild;
	int Ally;
};

const short _MSG_GuildInfo					= (19 | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);
struct		 MSG_GuildInfo
{
	_MSG;

	int Guild;

	STRUCT_GUILDINFO GuildInfo;
};

const short  _MSG_CharacterLogin			= (19 | FLAG_CLIENT2GAME);
struct		  MSG_CharacterLogin
{
	_MSG;

	int Slot;
	int Force;
	bool isDivina;
	int DivinaTimer;
	int DivinaEndTimer;
};

const short  _MSG_CNFCharacterLogin			= (20 | FLAG_GAME2CLIENT);
struct		  MSG_CNFCharacterLogin
{
	_MSG;

	short PosX, PosY;

	STRUCT_MOB mob;

	unsigned short Slot;
	unsigned short ClientID;
	unsigned short Weather;

	unsigned char ShortSkill[16];
	char Unk[2];
	STRUCT_AFFECT affect[MAX_AFFECT];
	STRUCT_MOBEXTRA mobExtra;
};

//int eee = sizeof MSG_CNFCharacterLogin;
struct		  MSG_CNFClientCharacterLogin
{
	_MSG;

	short PosX, PosY;

	STRUCT_MOB mob;

	unsigned short Slot;
	unsigned short ClientID;
	unsigned short Weather;

	unsigned char ShortSkill[16];
	char Unk[2];
	STRUCT_AFFECT affect[MAX_AFFECT];
	STRUCT_MOBEXTRA mobExtra;
};
const short  _MSG_CharacterLogout			= (21 | FLAG_CLIENT2GAME);

const short  _MSG_CNFCharacterLogout		= (22 | FLAG_GAME2CLIENT);
const short  _MSG_NewAccountFail			= (23 | FLAG_GAME2CLIENT);

const short  _MSG_CharacterLoginFail		= (25 | FLAG_GAME2CLIENT);
const short  _MSG_NewCharacterFail			= (26 | FLAG_GAME2CLIENT);
const short  _MSG_DeleteCharacterFail		= (27 | FLAG_GAME2CLIENT);
const short  _MSG_AlreadyPlaying			= (28 | FLAG_GAME2CLIENT);
const short  _MSG_StillPlaying				= (29 | FLAG_GAME2CLIENT);

const short  _MSG_SetClan					= (147 | FLAG_GAME2CLIENT);  // STANDARD PARM

const short  _MSG_MagicTrumpet				= (29 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		  MSG_MagicTrumpet
{
	_MSG;
	char String[MESSAGE_LENGTH];
};
struct MSG_ChatColor
{
	_MSG;

	char Message[92];
	int Color;
};
const short  _MSG_DBNotice					= (30 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		  MSG_DBNotice
{
	_MSG;
	char String[MESSAGE_LENGTH];
};
const short  _MSG_DBCapsuleInfo				= (60 | FLAG_DB2GAME | FLAG_GAME2DB);
const short  _MSG_DBPutInCapsule			= (61 | FLAG_DB2GAME | FLAG_GAME2DB);
const short  _MSG_DBOutCapsule				= (62 | FLAG_DB2GAME | FLAG_GAME2DB);
struct		  MSG_DBOutCapsule
{
	_MSG;

	int Slot;

	int      SourType;
	int      SourPos;
	int      DestType;
	int      DestPos;
	unsigned short GridX, GridY;
	unsigned short WarpID;

	char MobName[NAME_LENGTH];
};
const short  _MSG_CNFDBCapsuleInfo			= (31 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		  MSG_CNFDBCapsuleInfo
{
	_MSG;
	int Index;
	STRUCT_SEALOFSOUL Capsule;
};

const short  _MSG_MessageChat				= (51 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_MessageChat
{
	_MSG;
	char String[MESSAGE_LENGTH];
};


const short  _MSG_MessageWhisper			= (52 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_MessageWhisper
{
	_MSG;
	char MobName[NAME_LENGTH];
	char String[MESSAGEWHISPER_LENGTH];
};

const short  _MSG_UpdateCarry				= (133 | FLAG_GAME2CLIENT);
struct		  MSG_UpdateCarry
{
	_MSG;

	STRUCT_ITEM Carry[MAX_CARRY];

	int Coin;
};
 
const short  _MSG_UpdateScore				= (54 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateScore
{
	_MSG;
	STRUCT_SCORE   Score;
	char Critical;
	char SaveMana;
	unsigned short Affect[32];
	unsigned short Guild;
	unsigned short GuildLevel;
	char Resist[4];
	int ReqHp;
	int ReqMp;
	unsigned short Magician;
	unsigned short Rsv;
	char LearnedSkill;

};

const short  _MSG_UpdateEtc					= (55 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

struct		  MSG_UpdateEtc
{
	_MSG;
	int FakeExp;
	long long Exp;
	unsigned int LearnedSkill[2];
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	int Coin;
};

const short  _MSG_CNFMobKill				= (56 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // TODO: Check, confirm, confirm structure.
struct		  MSG_CNFMobKill
{
	_MSG;
	int			   Hold;

	unsigned short KilledMob;
	unsigned short Killer;
	long long   Exp;
};


const short  _MSG_UpdateCargoCoin			= (57 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);//TODO: Use MSG_STANDARDPARM

const short  _MSG_CreateMobTrade			= (99 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_CreateMobTrade
{
	_MSG;

	short          PosX, PosY;
	unsigned short MobID;

	char           MobName[NAME_LENGTH];

	unsigned short Equip[MAX_EQUIP];
	unsigned short Affect[MAX_AFFECT];
	unsigned short Guild;
	char GuildMemberType;
	char Unknow;
	short MortalFace;


	STRUCT_SCORE   Score;

	unsigned short CreateType;

	unsigned char AnctCode[MAX_EQUIP];
	char Tab[26];
	char           Desc[MAX_AUTOTRADETITLE];
	unsigned char   RefValue[MAX_EQUIP];
	BYTE            Unk[2];

	
};

const short  _MSG_CreateMob = (100 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_CreateMob
{
	_MSG;

	short          PosX, PosY;
	unsigned short MobID;

	char           MobName[NAME_LENGTH];

	unsigned short Equip[MAX_EQUIP];
	unsigned short Affect[MAX_AFFECT];
	unsigned short Guild;
	char GuildMemberType;
	char Unknow;
	short MortalFace;
	STRUCT_SCORE   Score;
	unsigned short CreateType;
	unsigned char AnctCode[MAX_EQUIP];
	char Tab[26];


	unsigned char   RefValue[MAX_EQUIP];
	BYTE            Unk[2];
};
 
 
const short  _MSG_NoViewMob					= (105 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short	 _MSG_RemoveMob					= (101 | FLAG_GAME2CLIENT);
struct		  MSG_RemoveMob
{
	_MSG;

	int RemoveType;   // 1 : morte, 2 : logout
};

const short	 _MSG_PKInfo					= (102 | FLAG_GAME2CLIENT); //MSG_STANDARDPARM

const short  _MSG_CreateItem				= (110 | FLAG_CLIENT2GAME);
struct		  MSG_CreateItem
{
	_MSG;
	unsigned short GridX, GridY;

	unsigned short ItemID;

	STRUCT_ITEM    Item;

	unsigned char  Rotate;
	unsigned char  State;
	unsigned char  Height;
	unsigned char  Create;

};

const short	 _MSG_DecayItem					= (111 | FLAG_GAME2CLIENT);
struct		  MSG_DecayItem 
{
	_MSG;

	short ItemID;
	short unk;
};

const short  _MSG_GetItem					= (112 | FLAG_CLIENT2GAME);
struct		  MSG_GetItem
{
	_MSG;

	int      DestType;
	int      DestPos;
	unsigned short	ItemID;
	unsigned short GridX, GridY;
};

const short  _MSG_CNFGetItem				= (113 | FLAG_GAME2CLIENT);
struct		  MSG_CNFGetItem
{
	_MSG;
	int      DestType;
	int	   DestPos;
	STRUCT_ITEM		Item;
};

const short  _MSG_DropItem					= (114 | FLAG_CLIENT2GAME);
struct		  MSG_DropItem
{
	_MSG;

	int      SourType;
	int      SourPos;
	int      Rotate;
	unsigned short GridX, GridY;
	unsigned short ItemID;
};

const short  _MSG_ShopList					= (124 | FLAG_GAME2CLIENT);
struct		  MSG_ShopList
{
	_MSG;
	int         ShopType;
	STRUCT_ITEM List[MAX_SHOPLIST];
	int         Tax;
};

const short  _MSG_SetHpMp					= (129 | FLAG_GAME2CLIENT);
struct		  MSG_SetHpMp
{
	_MSG;

	int Hp;
	int Mp;

	int ReqHp;
	int ReqMp;

};

const short  _MSG_SendItem					= (130 | FLAG_GAME2CLIENT);
struct		  MSG_SendItem
{
	_MSG;

	short invType;
	short Slot;

	STRUCT_ITEM item;

};

const short  _MSG_SetHpDam					= (138 | FLAG_GAME2CLIENT);
struct		  MSG_SetHpDam
{
	_MSG;
	int Hp;
	int Dam;

};
const short  _MSG_Exp_Msg_Panel_ = 0x5000;
struct		  MSG_Exp_Msg_Panel_
{
	_MSG;
	char Msg[128];
	int Color32;
};
const short	_MSG_Action						= (108 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short	_MSG_Action2					= (102 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short	_MSG_Action3					= (104 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Action
{
	_MSG;

	short PosX, PosY;

	int Effect; // 0 = walking, 1 = teleporting
	int Speed;

	char Route[MAX_ROUTE];

	short TargetX, TargetY;
};

struct p3B2
{
	_MSG;
	int unknown;
	char Nickname[16];
};


const short  _MSG_Motion					= (106 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_Motion
{
	_MSG;

	short Motion;
	short Parm;
	int   NotUsed;
};

const short  _MSG_UpdateEquip				= (107 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateEquip
{
	_MSG;
	unsigned short  Equip[MAX_EQUIP];
	unsigned char   AnctCode[MAX_EQUIP];
	unsigned char   RefValue[MAX_EQUIP];
	BYTE            HideCostume;
	BYTE            Unk[3];
};

 
const short _MSG_0x5003Ch = 0x457;
struct		  MSG_0x5003Ch
{
		_MSG;

	char Name[5][16];
	int Point[5];

};
const short _MSG_TradingItem				= (118 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct		 MSG_TradingItem
{
	_MSG;

	unsigned char DestPlace;
	unsigned char DestSlot;
	unsigned char SrcPlace;
	unsigned char SrcSlot;

	int WarpID;
};

const short _MSG_SetShortSkill				= (120 | FLAG_CLIENT2GAME | FLAG_GAME2CLIENT);
struct		 MSG_SetShortSkill
{
	_MSG;
	unsigned char  Skill1[4];
	unsigned char  Skill2[16];
};

const short _MSG_Buy						= (121 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Buy
{
	_MSG;

	unsigned short TargetID;
	short TargetInvenPos;
	short MyInvenPos;
	int   Coin;
};


const short _S_SSP_REQ_DIVINE_END_ = (321 | FLAG_GAME2DB);
struct MSG_SSP_EndDivine
{
	_MSG;

	int Values;
	int Skiped;
};

struct		 MSG_STANDARDPARM4
{
	_MSG;
	int Parm1;
	int Parm2;
	int Parm3;
	int Parm4;
};

const short _MSG_Sell						= (122 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Sell
{
	_MSG;
	unsigned short TargetID;
	short MyType;
	short MyPos;
};

const short _MSG_ApplyBonus					= (119 | FLAG_CLIENT2GAME);
struct		 MSG_ApplyBonus
{
	_MSG;
	short      BonusType;    // 0:ScoreBonus 1:Special  2:Skill
	short      Detail;       // 0:Str        1:Int      2:Dex      3:Con

	unsigned short TargetID;
};

const short _MSG_REQShopList				= (123 | FLAG_CLIENT2GAME); //STARNDARDPARM
struct		 MSG_REQShopList
{
	_MSG;
	unsigned short Target;
	unsigned short Unk;
};

const short _MSG_Restart					= (137 | FLAG_CLIENT2GAME); // STANDARD
const short _MSG_Withdraw					= (135 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_Deposit					= (136 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_PKMode						= (153 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_ReqTradeList				= (154 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARDPARM

const short  _MSG_UpdateWeather				= (139 | FLAG_GAME2CLIENT);
struct		  MSG_UpdateWeather
{
	_MSG;

	int CurrentWeather;
};

const short _MSG_Quest						= (139 | FLAG_CLIENT2GAME); // STANDARDPARM2
const short _MSG_Deprivate					= (140 | FLAG_CLIENT2GAME); // STANDARDPARM
const short _MSG_ReqChallange				= (141 | FLAG_GAME2CLIENT); // STANDARD
const short _MSG_Challange					= (142 | FLAG_CLIENT2GAME);  // STANDARDPARM
const short _MSG_ChallangeConfirm			= (143 | FLAG_CLIENT2GAME);  // ReqChallange
const short _MSG_ReqTeleport				= (144 | FLAG_CLIENT2GAME);
const short _MSG_ChangeCity					= (145 | FLAG_CLIENT2GAME);  //STANDARD



const short _MSG_SetHpMode					= (146 | FLAG_CLIENT2GAME);
struct		 MSG_SetHpMode
{
	_MSG;
	unsigned int Hp;
	short Mode;

};
const short _MSG_CloseShop					= (150 | FLAG_GAME2CLIENT);  // STANDARD

const short  _MSG_UseItem					= (115 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UseItem
{
	_MSG;
	int      SourType;
	int      SourPos;
	int      DestType;
	int      DestPos;

	unsigned short GridX, GridY;
	unsigned short WarpID;
};

const short   STATE_NOTHING					= 0;
const short   STATE_OPEN					= 1;
const short   STATE_CLOSED					= 2;
const short   STATE_LOCKED					= 3;

const short  _MSG_UpdateItem				= (116 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_UpdateItem
{
	_MSG;
	int ItemID;

	//short  Height;
	int State;
};


const short  _MSG_CNFDropItem				= (117 | FLAG_GAME2CLIENT);
struct		  MSG_CNFDropItem
{
	_MSG;
	int      SourType;
	int      SourPos;
	int      Rotate;

	unsigned short GridX, GridY;
};

const short  _MSG_CNFAddParty				= (125 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_CNFAddParty
{
	_MSG;

	short Leaderconn;
	short Level;
	short MaxHp;
	short Hp;

	short PartyID;

	char MobName[NAME_LENGTH];

	short Target;
};

const short  _MSG_SendReqParty				= (127 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendReqParty
{
	_MSG;

	char Class;
	char PartyPos;

	short Level;
	short MaxHp;
	short Hp;

	short PartyID;

	char MobName[NAME_LENGTH];

	int unk;
	short Target;
};

const short  _MSG_RemoveParty				= (126 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_RemoveParty
{
	_MSG;

	short Leaderconn;
	short unk;
};


const short  _MSG_SendAutoTrade				= (151 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendAutoTrade
{
	_MSG;

	char Title[MAX_AUTOTRADETITLE];

	STRUCT_ITEM Item[MAX_AUTOTRADE];

	char CarryPos[MAX_AUTOTRADE];

	int Coin[MAX_AUTOTRADE];

	short Tax;
	short Index;
};

const short _MSG_ReqBuy						= (152 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_ReqBuy
{
	_MSG;

	int Pos;

	unsigned short TargetID;

	int Price;
	int Tax;

	STRUCT_ITEM item;
};

const short _MSG_ItemSold					= (155 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // Standard Parm2  Parm1:Seller Parm2:Pos


const short _MSG_CombineItem				= (166 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CombineItemTiny			= (192 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CombineItemLindy			= (195 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemShany			= (196 | FLAG_CLIENT2GAME);
const short _MSG_CapsuleInfo				= (205 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemOdin			= (210 | FLAG_CLIENT2GAME);
const short _MSG_CombineDedekinto           = (230 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemExtracao		= (212 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemAlquimia		= (225 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemOdin2			= (226 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemEhre			= (211 | FLAG_CLIENT2GAME);
const short _MSG_CombineItemAilyn			= (181 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CombineItemAgatha			= (186 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

struct		 MSG_CombineItem
{
	_MSG;

	STRUCT_ITEM    Item[MAX_COMBINE];

	char           InvenPos[MAX_COMBINE];
};

const short _MSG_CombineComplete			= (167 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM
const short _MSG_InviteGuild				= (213 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM2

const short  _MSG_PutoutSeal				= (204 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_PutoutSeal
{
	_MSG;
	int      SourType;
	int      SourPos;
	int      DestType;
	int      DestPos;
	unsigned short GridX, GridY;
	unsigned short WarpID;

	char MobName[16];
};

const short  _MSG_SendInfoPlay = 0x2132;
struct		  MSG_SendInfoPlay
{
	_MSG;
	int ExpBonus;
	int DropBonus;
	int AbsDamage;
	int PerfuDamage;

};

const short _MSG_DeleteItem					= (228 | FLAG_CLIENT2GAME);
struct		 MSG_DeleteItem
{
	_MSG;

	int Slot;

	int sIndex;
};

const short _MSG_SplitItem					= (229 | FLAG_CLIENT2GAME);
struct		 MSG_SplitItem
{
	_MSG;

	int Slot;

	int sIndex;

	int Num;
};

struct	STRUCT_DAM
{
	int		TargetID;
	int		Damage;

};

const short  _MSG_Attack					= (103 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_Attack
{
	_MSG;

	char Unk_1[4];

	int  CurrentHp;

	char Unk_2[4];

	long long CurrentExp;
	short unk0;

	unsigned short		PosX, PosY;
	unsigned short		TargetX, TargetY;

	unsigned short		AttackerID;
	unsigned short		Progress;

	unsigned char		Motion;
	unsigned char		SkillParm;
	unsigned char		DoubleCritical;
	unsigned char		FlagLocal;

	short				Rsv;

	int					CurrentMp;

	short 				SkillIndex;
	short				ReqMp;

	STRUCT_DAM			Dam[MAX_TARGET];
};

const short _MSG_Trade						= (131 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Trade
{
	_MSG;

	STRUCT_ITEM		Item[MAX_TRADE];

	char			InvenPos[MAX_TRADE];
	int				TradeMoney;
	unsigned char	MyCheck;
	unsigned short	OpponentID;
};

const short _MSG_QuitTrade					= (132 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short _MSG_CNFCheck					= (134 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // STANDARD

const short  _MSG_AttackOne					= (157 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
#pragma pack(push, 1)
struct		  MSG_AttackOne
{
	_MSG;

	char Unk_1[4];

	int  CurrentMp;

	char Unk_2[4];

	long long CurrentExp;
	short unk0;

	unsigned short		PosX, PosY;
	unsigned short		TargetX, TargetY;

	unsigned short		AttackerID;
	unsigned short		Progress;

	unsigned char		Motion;
	unsigned char		SkillParm;
	unsigned char		DoubleCritical;
	unsigned char		FlagLocal;

	short				Rsv;

	int					CurrentHp;

	short 				SkillIndex;
	short				ReqMp;

	STRUCT_DAM			Dam[1];
};
#pragma pack(pop)

const short  _MSG_AttackTwo					= (158 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_AttackTwo
{
	_MSG;

	char Unk_1[4];

	int  CurrentMp;

	char Unk_2[4];

	long long CurrentExp;
	short unk0;

	unsigned short		PosX, PosY;
	unsigned short		TargetX, TargetY;

	unsigned short		AttackerID;
	unsigned short		Progress;

	unsigned char		Motion;
	unsigned char		SkillParm;
	unsigned char		DoubleCritical;
	unsigned char		FlagLocal;

	short				Rsv;

	int					CurrentHp;

	short 				SkillIndex;
	short				ReqMp;


	STRUCT_DAM			Dam[2];
};

const short	 _MSG_ReqRanking				= (159 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARD_PARM2  PARM1:TargetID, PARM2: 0:1vs1 1:5vs5   2:10vs10  3:Ok
const short  _MSG_Ping						= (160 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short  _MSG_StartTime					= (161 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short  _MSG_EnvEffect					= (162 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_EnvEffect
{
	_MSG;
	short		x1;
	short		y1;

	short		x2;
	short		y2;

	short		Effect;
	short		EffectParm;
};

const short	 _MSG_SoundEffect				= (163 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM
const short  _MSG_GuildDisable				= (164 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
const short  _MSG_GuildBoard				= (165 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);  // STANDARDPARM2
const short  _MSG_SendWarInfo				= (168 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);

const short  _MSG_AcceptParty				= (171 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_AcceptParty
{
	_MSG;

	short LeaderID;
	char MobName[NAME_LENGTH];
};

const short _MSG_TransperCharacter			= (169 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME | FLAG_DB2GAME);
const short _MSG_ReqTransper				= (170 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME | FLAG_DB2GAME | FLAG_GAME2DB);  // STANDARDPARM2 
struct		 MSG_ReqTransper
{
	_MSG;
	int		Result;							// 0:Success		1:Same Name Exist		2:No Space at Transper Server   3:Unknown Error	
	int		Slot;
	char	OldName[NAME_LENGTH];
	char	NewName[NAME_LENGTH];
};

const short _MSG_SendCastleState			= (172 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // SignalParm
const short _MSG_SendCastleState2			= (173 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // SignalParm	

const short  _MSG_MobLeft					= (176 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); //SignalParm

const short _MSG_SendArchEffect				= (180 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); // SignalParm	

const short  _MSG_SendAffect				= (185 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		  MSG_SendAffect
{
	_MSG;
	STRUCT_AFFECT Affect[MAX_AFFECT];
};


const short  _MSG_MobCount					= (187 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME); //SignalParm2

const short _MSG_GrindRankingData			= (1 | FLAG_NEW | FLAG_DB2GAME | FLAG_GAME2CLIENT);
struct		 MSG_SendExpRanking
{
	_MSG;

	int RankPosition;

	STRUCT_RANKING PlayerAbove;
	STRUCT_RANKING PlayerRank;
	STRUCT_RANKING PlayerUnder;

	MSG_SendExpRanking(int myID) :
	RankPosition(0), PlayerAbove(),
	PlayerRank(), PlayerUnder()
	{
		Type = _MSG_GrindRankingData;
		ID = myID;
		Size = sizeof(MSG_SendExpRanking);
	}
};
struct STRUCT_REBUY
{
	int Price; // 0 - 3

	STRUCT_ITEM Item; // 4 - 11

	int Ticks; // 12 - 15 - 16
};


const short _MSG_DropList = 2568;
struct MSG_DropList
{
	_MSG;

	int amount;

	struct
	{
		char name[16];

		short X;

		short Y;

		int exp;

		int gold;

		STRUCT_ITEM carry[64];

	}Drop[10];

};
const short _MSG_AnswerQuiz = (199 | FLAG_CLIENT2GAME);
const short _MSG_Quiz = (198 | FLAG_GAME2CLIENT);//novo
struct       MSG_Quiz
{
	_MSG;

	char Title[128];
	char Answer[4][32];
	int CorrectAlternative;
};
struct QuizInfo
{
	int RespostaCorreta; //de 0 a 3
	int RespostaCorretaLanN; //de 0 a 3
	int RespostaCorretaLanM; //de 0 a 3
	int RespostaCorretaLanA; //de 0 a 3
	int RespostaCorretaDragao; //de 0 a 3
	bool Status;
	bool StatusN;
	bool StatusM;
	bool StatusA;
	bool StatusDragao;
};
const short _MSG_Rebuy = (232 | FLAG_GAME2CLIENT | FLAG_CLIENT2GAME);
struct		 MSG_Rebuy
{
	_MSG;

	STRUCT_REBUY Rebuy[MAX_ITEM_REBUY];

	int Not;
	int Pot;
	int Dot;
};

const short _MSG_UpdateExpRanking			= (2 | FLAG_NEW | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_GAME2CLIENT);
struct		 MSG_UpdateExpRanking
{
	_MSG;

	STRUCT_RANKING RankInfo;

	MSG_UpdateExpRanking(int myID, STRUCT_RANKING rankInfo) :
	RankInfo()
	{
		Type = _MSG_UpdateExpRanking;
		ID = myID;
		Size = sizeof(MSG_UpdateExpRanking);

		RankInfo = rankInfo;
	}
};


//////////////////////////////////////////////////////////////////////
//																	//
//					         	 NP			     					//
//																	//
//////////////////////////////////////////////////////////////////////


const short  _MSG_NPReqIDPASS				= (1 | FLAG_DB2NP);
const short  _MSG_NPIDPASS					= (2 | FLAG_NP2DB);
struct		  MSG_NPIDPASS
{
	_MSG;
	char Account[ACCOUNTNAME_LENGTH];
	int  Encode1;
	char Pass[ACCOUNTPASS_LENGTH];
	int  Encode2;
};

const short  _MSG_NPReqAccount				= (3 | FLAG_NP2DB);
struct		  MSG_NPReqAccount
{
	_MSG;
	char Account[ACCOUNTNAME_LENGTH];
	char Char[NAME_LENGTH];
};

const short  _MSG_NPNotFound				= (4 | FLAG_DB2NP); //   Signal

const short  _MSG_NPAccountInfo				= (5 | FLAG_DB2NP);
struct		  MSG_NPAccountInfo
{
	_MSG;
	STRUCT_ACCOUNTFILE account;
	short Session;
	short State;  // 0:Normal  1:Blocked= (@);  2:Deleted= (_);  3:Disabled= (#);
};

const short  _MSG_NPReqSaveAccount			= (6 | FLAG_NP2DB); //   MSG_NPAccountInfo

const short  _MSG_NPDisable					= (7 | FLAG_NP2DB | FLAG_DB2NP);

const short  _MSG_NPEnable					= (8 | FLAG_NP2DB | FLAG_DB2NP); //   NPEnableParm 
struct		  MSG_NPEnable
{
	_MSG;
	char AccountName[ACCOUNTNAME_LENGTH];
	int Year;
	int YearDay;
};

const short  _MSG_NPNotice					= (9 | FLAG_NP2DB | FLAG_DB2NP | FLAG_DB2GAME); //   Parm 
struct		  MSG_NPNotice
{
	_MSG;
	int  Parm1;
	int  Parm2;
	char AccountName[ACCOUNTNAME_LENGTH];
	char String[MAX_NOTIFY_LENGTH];
};

const short  _MSG_NPState					= (10 | FLAG_NP2DB | FLAG_DB2NP); //   Parm 

const short _MSG_NPCreateCharacter			= (11 | FLAG_NP2DB | FLAG_DB2NP);
struct		 MSG_NPCreateCharacter
{
	_MSG;
	int  Slot;
	char Account[ACCOUNTNAME_LENGTH];
	STRUCT_MOB Mob;
};

const short _MSG_NPCreateCharacter_Reply	= (12 | FLAG_DB2NP | FLAG_NP2DB);
struct		 MSG_NPCreateCharacter_Reply
{
	_MSG;
	int  Slot;
	char Account[ACCOUNTNAME_LENGTH];
	int  Result;
	char Name[NAME_LENGTH];
};

const short  _MSG_NPDonate					= (13 | FLAG_NP2DB | FLAG_DB2NP);
struct		  MSG_NPDonate
{
	_MSG;
	char AccountName[ACCOUNTNAME_LENGTH];
	int Donate;
	int Honra;
};

const short _MSG_NPAppeal					= (16 | FLAG_DB2GAME | FLAG_GAME2DB | FLAG_DB2NP);

#pragma endregion

#pragma region Basedef functions prototypes

int  BASE_NeedLog(STRUCT_ITEM *item, int money);
int  BASE_GetBonusSkillPoint(STRUCT_MOB *mob, STRUCT_MOBEXTRA *extra);
int  BASE_GetBonusScorePoint(STRUCT_MOB *mob, STRUCT_MOBEXTRA *extra);
int  BASE_GetHpMp(STRUCT_MOB *mob, STRUCT_MOBEXTRA *extra);
int  BASE_GetSpeed(STRUCT_SCORE *score);
int  BASE_GetDamage(int dam, int ac, int combat);
void BASE_GetLanguage(char *str, int idx);
void BASE_GetLanguage(char *str, int idx, char *parm1);
void BASE_GetLanguage(char *str, int idx, char *parm1, char *parm2);
void BASE_GetLanguage(char *str, int idx, int parm1);
void BASE_GetLanguage(char *str, int idx, int parm1, int parm2);
void BASE_GetLanguage(char *str, int idx, char * parm1, int parm2);
void BASE_GetLanguage(char *str, int idx, int parm1, char *parm2);
void BASE_GetGuildName(int ServerGroup, unsigned short usGuild, char *szGuildName);
void BASE_GetClientGuildName(int ServerGroup, unsigned short usGuild, char *szGuildName, int Sub = 0);
int  BASE_GetSkillDamage(int dam, int ac, int combat);
void BASE_GetItemCode(STRUCT_ITEM * item, char * str);
int  BASE_GetItemAbilityNosanc(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetItemAbility(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetStaticItemAbility(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetBonusItemAbility(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetBonusItemAbilityNosanc(STRUCT_ITEM *item, unsigned char Type);
int  BASE_GetItemSanc(STRUCT_ITEM *item);
int BASE_GetItemGem(STRUCT_ITEM *item);
int  BASE_GetItemSancSuccess(STRUCT_ITEM *item);
int  BASE_GetSuccessRate(STRUCT_ITEM *item, int OriLacto);
int  BASE_GetGrowthRate(STRUCT_ITEM *item);
int  BASE_SetItemSanc(STRUCT_ITEM *dest, int sanc, int success);
int  BASE_GetItemAmount(STRUCT_ITEM *item);
void BASE_SetItemAmount(STRUCT_ITEM *item, int amount);
STRUCT_ITEM *GetItemPointer(STRUCT_MOB *mob, STRUCT_ITEM *cargo, int type, int pos);
int  BASE_GetMobAbility(STRUCT_MOB *mob, unsigned char Type);
int  BASE_GetMaxAbility(STRUCT_MOB *mob, unsigned char Type);
int  BASE_GetMobCheckSum(STRUCT_MOB *mob);
bool BASE_CheckValidString(char *name);
bool BASE_CheckHangul(unsigned short word);
int  BASE_InitializeBaseDef();
void BASE_ApplyAttribute(char *pHeight, int size);
void BASE_InitModuleDir();
int  BASE_GetSum(char * p, int size);
int  BASE_GetSum2(char *p, int size);
void BASE_CheckArmor(STRUCT_ITEM* Item);
void BASE_WriteSkillBin();
void BASE_WriteItemList(int nItemList);
int  BASE_ReadSkillBin();
int  BASE_ReadItemList();
void BASE_SpaceToUnderBar(char *szStr);
void BASE_UnderBarToSpace(char *szStr);
void BASE_ClearMob(STRUCT_MOB *mob);
void BASE_ClearMobExtra(STRUCT_MOBEXTRA *extra);
void BASE_GetCurrentScore(STRUCT_MOB & MOB, STRUCT_AFFECT *Affect, STRUCT_MOBEXTRA *extra, int *ExpBonus, int *ForceMobDamage, int isSummon, int *Accuracy, int *AbsHp, int *ForceDamage);
void BASE_GetFirstKey(char * source, char * dest);
int  BASE_GetGuild(int x, int y);
int  BASE_GetIndex(STRUCT_ITEM *item);
int  BASE_GetGuild(STRUCT_ITEM *item);
int  BASE_GetSubGuild(int item);
int  BASE_GetArena(int x, int y);
int  BASE_GetVillage(int x, int y);
void BASE_GetKorFirst(int temp, int *a);
void BASE_ClearItem(STRUCT_ITEM *item);
int  BASE_CanEquip(STRUCT_ITEM *item, STRUCT_SCORE *score, int Pos, int Class, STRUCT_ITEM *pBaseEquip, STRUCT_MOBEXTRA *extra);
int  BASE_CanCarry(STRUCT_ITEM *item, STRUCT_ITEM *carry, int DestX, int DestY, int *error);
int  BASE_CanCargo(STRUCT_ITEM *item, STRUCT_ITEM *cargo, int DestX, int DestY);
void BASE_SortTradeItem(STRUCT_ITEM *Item, int Type);
int  BASE_CanTrade(STRUCT_ITEM *Dest, STRUCT_ITEM *Carry, unsigned char *MyTrade, STRUCT_ITEM *OpponentTrade, int MaxCarry);
void BASE_InitializeMessage(char *file);
void BASE_InitializeMobname(char *file, int offset);
void BASE_WriteMessageBin();
int  BASE_ReadMessageBin();
void BASE_InitializeItemList();
int  BASE_ReadItemListFile(char *filename, int Build);
void BASE_InitializeEffectName();
void BASE_InitializeHitRate();
int  BASE_UpdateItem(int maskidx, int CurrentState, int NextState, int xx, int yy, char *pHeight, int rotate, int *height);
int  BASE_UpdateItem2(int maskidx, int CurrentState, int NextState, int xx, int yy, char *pHeight, int rotate, int height);
INT32 GetRoute(unsigned int x, unsigned int y, unsigned int* targetX, unsigned int* targetY, char* route, int distance);
//void BASE_GetDestByAction(unsigned short *x, unsigned short *y, struct MSG_Action *mv);
int  BASE_GetManaSpent(int SkillNumber, int SaveMana, int Special);
int  BASE_GetHitRate(STRUCT_SCORE *att, STRUCT_SCORE *def);
int  BASE_GetDamageRate(STRUCT_SCORE* att, int skill);
int  BASE_GetAccuracyRate(STRUCT_SCORE *att);
int  BASE_GetDoubleCritical(STRUCT_MOB *mob, unsigned short *sProgress, unsigned short *cProgress, unsigned char *bDoubleCritical);
int  BASE_GetRoute(int x, int y, int *targetx, int *targety, char *Route, int distance, char *pHeight);
int  BASE_GetDistance(int x1, int y1, int x2, int y2);
//void BASE_GetHitPosition		(int,int,int *,int *,char *)
//void BASE_GetHitPosition2		(int,int,int *,int *,char *)
void BASE_WriteInitItem();
int  BASE_ReadInitItem();
void BASE_InitializeInitItem();
void BASE_InitializeSkill();
int  IsClearString3(char *str, int nTarget);
void BASE_InitializeClientGuildName(int group);
void BASE_InitializeGuildName();
int  BASE_InitializeServerList();
BOOL BASE_CheckPacket(MSG_STANDARD* m);
int  BASE_InitializeAttribute();
int  BASE_GetHttpRequest(char *httpname, char *Request, int MaxBuffer);
int  BASE_GetSkillDamage_PVP(int skillnum, STRUCT_MOB *mob, int weather, int weapondamage, STRUCT_MOBEXTRA* extra);
int  BASE_GetSkillDamage_PVM(int skillnum, STRUCT_MOB* mob, int weather, int weapondamage, STRUCT_MOBEXTRA* extra);
int  BASE_GetEnglish(char *name);
int  BASE_GetWeekNumber();

int  BASE_VisualItemCode(STRUCT_ITEM *Item, int mnt);
int  BASE_VisualAnctCode(STRUCT_ITEM *Item);

void BASE_SetItemDate(STRUCT_ITEM *Item, int day);
int  BASE_CheckItemDate(STRUCT_ITEM *Item);
void BASE_CheckFairyDate(STRUCT_ITEM *Item);

#pragma endregion

#pragma region Basedef Externs

extern STRUCT_GUILDZONE g_pGuildZone[MAX_GUILDZONE];

extern int				g_pIncrementHp[4];
extern int				g_pIncrementMp[4];

extern int g_pIncrementHpCelestial[4];
extern int g_pIncrementMpCelestial[4];

extern int				g_pGroundMask[MAX_GROUNDMASK][4][6][6];

extern int				g_pDropBonus[64];
extern int				g_pDropRate[64];

extern int				DungeonPos[30][2];
extern int				DungeonItem[10];

extern long long		g_pNextLevel[MAX_LEVEL + 2];
extern long long	    g_pNextLevel_2[MAX_CLEVEL + 202];
extern STRUCT_BEASTBONUS pSummonBonus[MAX_SUMMONLIST];
extern STRUCT_BEASTBONUS pTransBonus[5];

extern int  ChargedGuildList[MAX_SERVER][MAX_GUILDZONE];
extern char g_pGuildName[10][16][MAX_GUILD][GUILDNAME_LENGTH];
extern char g_pMessageStringTable[MAX_STRING][128];
extern char EffectNameTable[MAX_EFFECTINDEX][24];

extern STRUCT_SPELL g_pSpell[MAX_SKILLINDEX];
extern STRUCT_INITITEM g_pInitItem[MAX_INITITEM];

extern STRUCT_ITEMLIST g_pItemList[MAX_ITEMLIST];

extern unsigned char g_pAttribute[1024][1024];

extern char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];

extern int g_dwInitItem;

extern int g_HeightWidth;
extern int g_HeightHeight;
extern int g_HeightPosX;
extern int g_HeightPosY;
extern char g_pFormation[5][12][2];
extern int g_pClanTable[9][9];

extern int g_pSancRate[3][15];
extern int g_pSancGrade[2][5];
extern int g_pEhreRate[22];
extern int g_pOdinRate[12];
extern int g_pDedekintoRate[11];
extern int g_pCelestialRate[10];
extern int g_pTinyBase;
extern int g_pShanyBase;
extern int g_pAilynBase;
extern int g_pAgathaBase;
extern int g_pAnctChance[3];
extern int g_pItemSancRate12[11];
extern int g_pItemSancRate12Minus[4];
extern int BaseSIDCHM[4][6];
extern int g_pItemSancRateValkyrie[4];
extern int g_pHeightGrid[4096][4096];
extern int g_pBonusValue[10][2][2];
extern int g_pBonusType[10];
extern int g_pBonusValue2[52][4];//Peito calça
extern int g_pBonusValue3[25][4];//Elmo
extern int g_pBonusValue4[39][4];//Luva
extern int g_pBonusValue5[30][4];//Bota

#pragma endregion

#endif
