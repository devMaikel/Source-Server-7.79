#include <Windows.h>
#include <winsock.h>
#include <ctime>

// Windows librarys
#include <fstream>
#include <string>
#include <mutex>

// Include the project files
#include "stBase.h"
#include "KeyTable.h"
#include "Struct.h"
#include "EncDec.h"
#include "CUser.h"
#include "Socket.h"
#include "CMob.h"
#include "ItemEffect.h"
#include "CNPCGener.h"
#include "MessageSender.h"
 

#ifndef __CSERVER_H__
#define __CSERVER_H__

#include <array>
#include <memory>
#include <vector>

// Adiciona a library da winsock
#pragma comment (lib, "WS2_32.lib")

// Define argumentos padr�es para o sistema
// de sockets
#define ACCEPT_USER WM_USER + 1
#define RECV_USER   WM_USER + 2
#define WM_SOCKET   WM_USER 
#define WM_DATASERVER	WM_USER + 3

#define WSA_READ            (WM_USER + 100)
#define WSA_READDB          (WM_USER + 2) 
#define WSA_ACCEPT          (WM_USER + 3) 

// Define os valores maximos 
#define MAX_BUFFER 65535 * 8
#define MAX_PLAYER 1000
#define SCHEDULE_ID MAX_PLAYER - 1
#define CLIVER 7596


#define MAX_MESSAGE_SIZE 8096
#define INITCODE 0x1F11F311

// Define os valores padr�es
#define NOT_CONNECT 0
#define IN_PROCCESS_CONNECT 1
#define WAITING_HELLO 2
#define CONNECTED 4

#define	TIMER_SEC    0
#define TIMER_MIN    1
#define	TIMER_HOUR   2
#define	TIMER_SEND   3

#define MH 8

#define VIEWGRIDX 33
#define VIEWGRIDY 33
#define HALFGRIDX 16
#define HALFGRIDY 16

#define MAX_QUESTDIARIA 256
#define MAX_LEVELITEM 256
#define MAX_PREMIERSTORE 40

constexpr int MaxMessage = 128;

// Struct to GUI user interface
struct STRUCT_GUI_INFO
{
	HWND hGUI,
	hButton[6],
	hLabel[6];

	HFONT Font;
	ATOM Class;
};

struct STRUCT_QUESTBOSS
{
	bool isAlive;
	int  gennerId;
	STRUCT_ITEM Gifts[10];
	INT8 Chances[10];
	int CountToBorn;
};

struct STRUCT_QUESTS
{
	INT16 KillCount;
	STRUCT_QUESTBOSS Boss;
};

struct STRUCT_QUIZQUESTIONS
{
	std::string Question;
	std::array<std::string, 4> Answers;
};


enum class eValley
{
	First,
	Second
};
struct TOD_DailyQuestInfo_RewardItem
{
	STRUCT_ITEM Item;
	unsigned int Amount;
};

enum class TOD_DailyQuestInfo_Type
{
	Normal = 0,
	Special
};

enum class TOD_Valley
{
	First,
	Second
};

struct TOD_MissionInfo
{
	int QuestId;
	TOD_DailyQuestInfo_Type Type; // 0 = mob, 1 = drop, 2 = mob + drop
	std::vector<int> ClassMaster;

	struct
	{
		// Pedido de at� 04 mobs por quest
		// O mob � checado atrav�s do nome
		std::array<std::string, 5> mobName;

		// Quantos mobs devem ser mortos
		std::array<unsigned int, 5> Amount;
	} Mob;

	struct
	{
		// Pedido te at� 08 itens
		std::array<unsigned int, 5> Item;

		// Quantos itens v�o ser pedidos
		std::array<unsigned int, 5> Amount;
	} Drop;

	// Aqui a premia��o entregue pela quest di�ria
	// Capaz de entregar gold, exp e at� 05 itens

	std::array<TOD_DailyQuestInfo_RewardItem, 6> FreeReward;
	std::array<TOD_DailyQuestInfo_RewardItem, 6> BattlePassReward;

	int Gold;
	int Exp;

	int MinLevel;
	int MaxLevel;

	std::string QuestName;
};


#define _REFRESH_DAILYQUEST_OPCODE 0x701
struct stRefreshDailyQuest
{
	PacketHeader Header;
	UINT32 MobCount[5];
	UINT16 MobCountKill[5];

	UINT32 ItemCount[5];
	UINT16 ItemCountDrop[5];
};

struct STRUCT_LEVELITEM
{
	INT32 Evolution;
	INT32 Type;
	INT32 Level;
	INT32 Classe;

	STRUCT_ITEM item;
};

struct STRUCT_DROPBYZONES
{
	int index;
	STRUCT_POSITION Min;
	STRUCT_POSITION Max;

	STRUCT_ITEM Item;
	mutable int Dropped;

	int Rate;
	int Limit;
};

struct STRUCT_KINGDOMBATTLE
{
	bool Status;

	int TowerId;
	int KingId;

	bool isTowerAlive;
	bool isKingAlive;
};
	 
enum class eColosseumType
{
	Normal,
	Mystic,
	Arcane
};

struct STRUCT_INTERNALARENA
{
	unsigned long long Experience;

	int MaximumLevel;
};

struct STRUCT_CHALLENGEINFO
{
	int GuildId;
	int Value;
};

struct STRUCT_SCHEDULED
{
	std::string Command;

	int Month;
	int Day;

	int Hour;
	int Min;

	bool Executed;
	std::chrono::time_point<std::chrono::steady_clock> ExecuteTime;
};

struct STRUCT_MOB_BOSS
{
	std::vector<int> Geners;
	int Index;
	int TimeToReborn;
	int MaxTimeIngame;
	int Fame;
	int GenerGenerated;

	std::chrono::time_point<std::chrono::steady_clock> LastUpdate;
};
struct InternalArena
{
	unsigned long long Experience;

	int MaximumLevel;
};


struct ArenaReward
{
	std::vector<STRUCT_ITEM> Items;
	std::array<std::vector<InternalArena>, 4> Experience;
	int Gold;
};

 
struct STRUCT_NIGHTMARE_INFO
{
	// Membros no grupo, permitidos at� 40
	std::array<unsigned short, 40> Members;
	std::array<std::string, 40>  MembersName;

	// Restante de NPCs
	UINT16 NPCsLeft;

	// Tempo restante no Pesadelo
	UINT16 TimeLeft;

	// True quando o NPC ja morreu
	// False quando ainda n�o morreu
	UINT8 Alive[8];

	UINT16 Status;
};
constexpr int MaxBoss = 64;

// Estrutura do banco de dados
struct STRUCT_SERVER_INFO
{
	struct
	{
		UINT32 Porta;
		char IP[32];
	} Config;

	struct
	{
		UINT32 Porta;
		char IP[32];
	} Data;

	bool Status;

	SOCKADDR_IN Service;
	UINT32 Socket;

	UINT32 UsersON;

	// Level na area de treinamento
	UINT32 NewbieZone;
	bool isReboot;

	// Contadores
	UINT32 MinCounter;
	UINT32 HourCounter;
	UINT32 SecCounter;

	// DeadPoint
	// Perda de experi�ncia em caso de morte?
	UINT32 DeadPoint;

	UINT32 SaveCount; // 4CBBD8

	// Contagem ed Init
	UINT32 InitCount;
	UINT32 ItemCount;

	// B�nus experi�ncia
	UINT32 BonusEXP;

	UINT32 ExpDailyBonus;
	UINT32 GoldDailyBonus;
 

	UINT32 Sapphire;
	UINT32 StatSapphire;

	// Rates para refinar refina��o aben�oada
	UINT8 RateRef[5];

	struct
	{
		INT32 RankingProcess; // 30
		INT32 Timer; // 44

		INT16 Challanger1; // 34
		INT16 Challanger2; // 38

		char RankingName[4][32]; // 0 = 4CBC9C 32 em 32
		INT32 RankingLevel[2];
	} Challanger;

	UINT32 Channel;
	UINT32 TotalServer;
	UINT32 ServerGroup; //4C7BC0


	UINT32 NoviceChannel;
	UINT32 WarChannel;

	UINT32 FirstKefra;
	UINT32 KefraKiller;
	UINT8  KefraDead;

	UINT32 Kingdom1Clear;
	UINT32 Kingdom2Clear;
	
	stWater pWater[3][9];
	
	STRUCT_NIGHTMARE_INFO Nightmare[3];
	UINT32 GoldBonus;

	// �ltima guild registrada
	UINT32 LastGuild;

	// Taxa do dia
	// Se estiver 1 quer dizer que a taxa naquele dia
	// ja foi alterada pelo l�der de guild da cidade
	UINT32 TaxesDay[5];

	// Capa vencedora da guerra de noatun
	INT32 CapeWin; // 4C7D4C
	
	struct
	{
		char msg[108];

		short Hour;
		short Min;

		short Interval;

		short Repeat;

		clock_t Time;

		bool InThisHour;
	} Messages[MaxMessage];
	
	std::vector<STRUCT_SCHEDULED> STRUCT_SCHEDULED;

	struct
	{
		STRUCT_ITEM Target[5];
		INT16 Rate[5];
		INT32 Source;
	} Treasure[8];

	INT32 CastleState;
	INT32 CastleHour{ 21 };

	INT32 AltarId;
	INT32 LiveTower[3];
	INT32 NewbieEventServer; // 8BF17C0
	INT32 BRState;// 8BF185C
	INT32 BRItem; // 8BF1828
	INT32 BRMode; // 8BF1864
	INT32 BRGrid; // 8BF1868
	INT32 BRHour; // 4CBC40
	
	INT32 GuildDay; // 4CBC34
	INT32 GuildHour; // 4CBC38
	INT32 NewbieHour; // 4CBC3C

	INT32 ColoState; // 4CBC2C
	INT32 Colo150Limit; // 8BF180C

	INT32 PotionReady; // 8BF1810
	
	INT32 ForceWeekDay; // 4CBC30
	INT32 WeekMode; // 4CBC28
	INT32 WeekHour{ 20 };

	std::array<std::vector<STRUCT_CHALLENGEINFO>, 5> ChallengerMoney;

	INT32 Weather; //8BF181C
	INT32 ForceWeather; //004CBBE0

	INT32 Staff;

	INT32 ServerTime;
	INT32 LastTime;

	INT32 Encode; // 00BAF180 -> 7556

	struct
	{
		INT32 Hour{ 21 };

		INT32 Points[2];
		INT32 Status; // 1 = online
		INT32 Bonus; // 1 = blue, 2 = red
		INT32 Annoucement_Point;
		INT32 Annoucement;

		std::array<TOD_RvRStore_Item, 27> Items;
	} RvR;

	//stTowerWar TowerWar[10];

	STRUCT_QUESTS QuestsBosses[5];
	
	STRUCT_POSITION AlcateiaPos[128];
	STRUCT_POSITION AloneWolfPos[128];

	int TotalAlcateiaPos;
	int TotalAloneWolfPos;
 

	struct
	{
		eColosseumType Type;

		// Level em que se encontra o Coliseu
		WORD level;
		// Tempo restante para o n�vel 
		WORD time;
 
		WORD npc;

		struct 
		{
			// Port�es ja foram fechados
			bool closedGate;
			// Muralhas desceram
			bool closedWalls;

			// Mobs do level indicado ja nasceram ou n�o
			bool wasBorn;

			// Se o usuario esta no boss do n�vel
			bool boss;
		} inSec;

		std::vector<unsigned int> clients;
	} Colosseum;

	std::vector<TOD_MissionInfo> Missions;

	struct 
	{
		INT32 Status;

		// Membros registrados
		INT32 Registered[MAX_PLAYER];

		// Contador dentro da quest ^^ 
		INT32 Counter; 
	} Zombie;

	struct
	{
		INT32 Status;
		INT32 Guild;
		INT32 Hour{ 22 };
	} TowerWar;

	struct
	{
		STRUCT_ITEM item;

		INT32 Count;

		// Status do evento
		INT32 Status;

		// Taxa de drop
		INT32 Rate;

		// Bonus por possuir XX buff
		INT32 Bonus;
	} AutoTradeEvent;

	struct
	{
		STRUCT_ITEM item;
		INT32 Count;
		INT32 Status;
		INT32 Rate;
		INT32 Bonus;
	} BossEvent;
	
	struct
	{
		STRUCT_ITEM Item;

		INT32 Gold;
		INT32 Last;
		INT32 Second;
		INT32 Interval;
	} PremiumTime;

	struct
	{
		STRUCT_ITEM item[MAX_PREMIERSTORE];
		INT32 Price[MAX_PREMIERSTORE];
	} PremierStore;

	struct
	{
		STRUCT_ITEM item[MAX_PREMIERSTORE];
		INT32 Price[MAX_PREMIERSTORE];
	} ArenaStore;

	std::vector<STRUCT_LEVELITEM> levelItem;

 

	struct
	{
		std::vector<STRUCT_DROPBYZONES> areas;

		bool Message;
		bool Status;
	} DropArea;

	struct
	{
		std::array<STRUCT_KINGDOMBATTLE, 2> Info;
		int Winner;
	} KingdomBattle;

	bool NewRandomMode{ true };

	std::vector<STRUCT_QUIZQUESTIONS> QuizQuestions;

	struct
	{
		int Count;
		int MobId;

		int TotalToKill{ 500 };
	} LanHouseN;

	struct
	{
		STRUCT_ITEM Item[7][4];
	} Daily;

	struct
	{
		int Count;
		int MobId;

		int TotalToKill{ 500 };
	} LanHouseM;

	std::recursive_mutex logMutex;

	struct
	{
		std::vector<int> HoursAllowed;
		int MaxKills;

		ArenaReward WinnerRewards;
		ArenaReward TopKillRewards;
		ArenaReward ParticipantRewards;
	} Arena;

	std::vector<InfoCache<STRUCT_SEALINFO>> SealCache;

	int AnnubisBonus;
	struct
	{
		std::chrono::time_point<std::chrono::steady_clock> StartTime;
		UINT32 Clear;
		bool IsOperating;

		std::vector<unsigned short> Users;

		void Unregister(unsigned short clientId)
		{
			auto it = std::find(std::begin(Users), std::end(Users), clientId);
			if (it != std::end(Users))
				Users.erase(it);
		}
	}Zakum;

	int RunesPerSanc{ 1 };
	unsigned int MaximumPesaLevel{ 120 };

	bool PromotionStatus{ false };
	int MaxWaterEntrance{ 1080 };
	int CliVer{ 759 };

 

	std::array<STRUCT_MOB_BOSS, MaxBoss> Boss;
} ;

typedef struct
{
	UINT8 Status;
	UINT32 Socket;

	BYTE *sendBuffer;
	BYTE *recvBuffer;

	UINT32 SizeOfData;

	SOCKADDR_IN Service;
	WSADATA wsa;
	
	UINT32 nRecvPosition;
	UINT32 nProcPosition;
    UINT32 Init;
} STRUCT_GAMESERVER;

extern char FailAccount[16][16];

// Responsavel pelas variaveis dentro da pr�pria aplica��o
extern STRUCT_SERVER_INFO sServer;
// Responsavel pela estrutura que vai armazenar as variaveis
// responsaveis pela GUI do usuario
extern STRUCT_GUI_INFO GUI;
// Responsavel pela conex�o com o banco de dados
extern STRUCT_GAMESERVER sData;

extern unsigned int CurrentTime;

// Functions
// ----
//  Responsavel pela cria��o da GUI do usuario
// ----
void CreateGUI();

// ----
//  Responsavel pelo processo de analise dos sockets
//  e mensagens da janela
// ----
LONG APIENTRY WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
 
// ----
// ENvio de pacotes para a DBsrv
// ----
bool AddMessageDB(BYTE *pBuffer, UINT32 packetSize);

// ----
// Recebimento de pacoste da DBsrv
// ----
bool PacketControl(BYTE* pBuffer, INT32 size);
char* ReadMessageDB(int*, int*);
BOOL Receive(void);


// Processamento do tempo
void ProcessSendTimer();
void ProcessSecTimer();
void ProcessMinTimer();
void ProcessHourTimer();


void AddFailAcount(char *account);
INT32 CheckFailAccount(char *account);
#endif

extern int RebootCount;

extern int		ExitRebootCount;
extern bool	IsRebootNow;