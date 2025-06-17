#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include <chrono>


INT32 CreateMobAutoTrade(int posX, int posY, int seller)
{
	INT32 LOCAL_1 = mGener.GetEmptyNPCMob();
	if (LOCAL_1 == 0)
		return -1;

	pMob[LOCAL_1] = CMob{};
	pMob[LOCAL_1].BossInfoId = MAXUINT32;
	pMob[LOCAL_1].clientId = LOCAL_1;
	strncpy_s(pMob[LOCAL_1].Mobs.Player.Name, "Aki", 16);

	memset(&pMob[LOCAL_1].PartyList, 0, sizeof INT16 * 12);

	INT32 LOCAL_2 = ReadMob(&pMob[LOCAL_1].Mobs.Player, "npc");
	if (LOCAL_2 == 0)
		return false;

	strncpy_s(pMob[LOCAL_1].Mobs.Player.Name, pMob[seller].Mobs.Player.Name, 16);

	pMob[LOCAL_1].Mobs.Player.Name[15] = 0;

	INT32 LOCAL_3;
	for (LOCAL_3 = 0; LOCAL_3 < 16; LOCAL_3++)
	{
		if (pMob[LOCAL_1].Mobs.Player.Name[LOCAL_3] == '_')
			pMob[LOCAL_1].Mobs.Player.Name[LOCAL_3] = ' ';
		if (pMob[LOCAL_1].Mobs.Player.Name[LOCAL_3] == '@')
			pMob[LOCAL_1].Mobs.Player.Name[LOCAL_3] = ' ';
	}

	memset(&pMob[LOCAL_1].Mobs.Affects, 0, sizeof STRUCT_AFFECT * 32);

	//trava pra nao andar
	for (LOCAL_3 = 0; LOCAL_3 < 5; LOCAL_3++)
	{
		pMob[LOCAL_1].Segment.ListX[LOCAL_3] = posX;
		pMob[LOCAL_1].Segment.ListY[LOCAL_3] = posY;
	}

	strncpy_s(pMob[LOCAL_1].Tab, "AUTO VENDA", 16);
	

	pMob[LOCAL_1].Ingame.IsRealSeller = seller;
	pMob[LOCAL_1].Ingame.IsAutoTrading = true;

	pMob[LOCAL_1].Mobs.Player.Equip[0].Index = 348;
	pMob[LOCAL_1].Mobs.Player.Equip[6].Index = 0;
	pMob[LOCAL_1].Mobs.Player.Equip[7].Index = 0;
	pMob[LOCAL_1].Mobs.Player.Equip[14].Index = 0;
	pMob[LOCAL_1].Mobs.Player.Status.CON = 0;



	pMob[LOCAL_1].GenerateID = -1;
	pMob[LOCAL_1].Formation = 0;
	pMob[LOCAL_1].RouteType = 0;
	pMob[LOCAL_1].Mode = 4;
	pMob[LOCAL_1].Segment.Progress = 0;
	pMob[LOCAL_1].Leader = 0;
	pMob[LOCAL_1].WaitSec = 10;

	pMob[LOCAL_1].clientId = LOCAL_1;

	pMob[LOCAL_1].GetCurrentScore(MAX_PLAYER);

	pMob[LOCAL_1].Mobs.Player.Status.curHP = pMob[LOCAL_1].Mobs.Player.Status.maxHP;
	pMob[LOCAL_1].Segment.Direction = 0;

	memset(&pMob[LOCAL_1].EnemyList, 0, 8);

	UINT32 LOCAL_5 = pMob[LOCAL_1].Segment.ListX[0];
	UINT32 LOCAL_6 = pMob[LOCAL_1].Segment.ListY[0];

	INT32 LOCAL_7 = GetEmptyMobGrid(LOCAL_1, &LOCAL_5, &LOCAL_6);
	if (LOCAL_7 == 0)
	{
		pMob[LOCAL_1].Mode = 0;
		pMob[LOCAL_1].Mobs.Player.Name[0] = 0;
		pMob[LOCAL_1].GenerateID = -1;

		return -2;
	}

	pMob[LOCAL_1].Last.Time = clock();

	pMob[LOCAL_1].Segment.X = LOCAL_5;
	pMob[LOCAL_1].Target.X = LOCAL_5;
	pMob[LOCAL_1].Last.X = LOCAL_5;

	pMob[LOCAL_1].Segment.Y = LOCAL_6;
	pMob[LOCAL_1].Target.Y = LOCAL_6;
	pMob[LOCAL_1].Last.Y = LOCAL_6;

	INT32 LOCAL_17 = pMob[LOCAL_1].Mobs.Player.bStatus.maxMP;
	if (LOCAL_17 != 0)
	{
		SetAffect(LOCAL_1, LOCAL_17, 30000, 200);
		SetTick(LOCAL_1, LOCAL_17, 30000, 200);
	}

	g_pMobGrid[LOCAL_6][LOCAL_5] = LOCAL_1;

	pMob[LOCAL_1].SpawnType = 2;
	SendGridMob(LOCAL_1);
	pMob[LOCAL_1].SpawnType = 0;

	return LOCAL_1;
}


bool CUser::RequestCreateAutoTrade(PacketHeader* Header)
{
	p397 *p = (p397*)(Header);

	if(!pMob[clientId].Mobs.Player.Status.curHP || Status != USER_PLAY)
	{
		SendHpMode(clientId);
		AddCrackError(clientId, 10, 88);

		RemoveTrade(clientId);
		return true;
	}

	if (pUser[clientId].Trade.ClientId)
	{
		RemoveTrade(clientId);
		return true;
	}

	if(User.Block.Blocked)
	{
		SendClientMessage(clientId, "Desbloqueie seus itens para poder movimenta-los");

		RemoveTrade(clientId);
		return true;
	}

	INT32 posX = pMob[clientId].Target.X;
	INT32 posY = pMob[clientId].Target.Y;
	INT32 villageId = GetVillage(posX, posY);

	if(villageId < 0 || villageId >= 5)
	{
		SendClientMessage(clientId, g_pLanguageString[_NN_OnlyVillage]);

		RemoveTrade(clientId);
		return true;
	}

	if(!sServer.NoviceChannel)
	{
		SendClientMessage(clientId, "Somente no canal novato para criação de lojas");

		RemoveTrade(clientId);
		return true;
	}

	if (clientId <= 0 || clientId >= MAX_PLAYER)
		return true;

	INT32 itemId = p->Index; // LOCAL_1204
	INT32 i = 0;
	int total = 0;
	for( ; i < 12; i ++)
	{
		if(p->Gold[i] < 0 || p->Gold[i] > 1999999999)
			return false;

		if(p->Item[i].Index == 0 && p->Gold[i] != 0)
			return false;

		if(p->Item[i].Index == 0)
			continue;

		if(p->Item[i].Index == 508 || p->Item[i].Index == 509 || p->Item[i].Index == 522 || (p->Item[i].Index >= 526 && p->Item[i].Index <= 531) || p->Item[i].Index == 446
			|| p->Item[i].Index == 3993 || p->Item[i].Index == 3994)
			return false;

		if (GetItemAbility(&p->Item[i], EF_NOTRADE))
		{
			SendClientMessage(clientId, "Este item não é negociavel.");

			return false;
		}

		INT32 itemSlot = p->Slot[i]; // LOCAL1206
		if(itemSlot < 0 || itemSlot >= 168)
			return false;

		INT32 verify = memcmp(&User.Storage.Item[itemSlot], &p->Item[i], 8);
		if (verify != 0)
		{
			RemoveTrade(clientId);

			return true;
		}

		if (p->Gold[i] >= 10000000)
			total++;
	}

	p->Unknown = g_pCityZone[villageId].perc_impost;
	p->Name[23] = '\0';
	p->Name[22] = '\0';


	strncpy_s((char*)pMob[clientId].Ingame.AutoTradeName, 24, p->Name, 24);


	pMob[clientId].Ingame.IsAutoTrading = true;	
	memcpy(&pMob[clientId].Ingame.AutoTrade, p, sizeof pMob[clientId].Ingame.AutoTrade);

	int mobid = CreateMobAutoTrade(posX, posY, clientId);
	if (mobid <= 0)
	{
		SendClientMessage(clientId, "Não foi possivel abrir a loja.");
		RemoveTrade(clientId);
		return true;
	}

	pMob[clientId].Ingame.IsRealSeller = mobid;


	p363 sm{};
	GetCreateMobTrade(mobid, (BYTE*)&sm);
	GridMulticast_2(posX, posY, (BYTE*)&sm, 0);
	std::stringstream str;
	str << "Informações dos itens da loja\n";
	str << "Nome da loja: " << p->Name << "\n";
	str << "Posição criada: " << pMob[clientId].Target.X << "x " << pMob[clientId].Target.Y << "\n";
	str << "Total de itens com valor superior a 10 milhões: " << total << "\n";
	str << "[ITENS]" << "\n";

	for (int i = 0; i < 12; i++)
	{
		if (p->Item[i].Index == 0 && p->Gold[i] != 0)
			return false;

		if (p->Item[i].Index == 0)
			continue;

		str << "Slot [" << std::to_string(p->Slot[i]) << "] - " << ItemList[p->Item[i].Index].Name << " " << p->Item[i].toString().c_str() << ". Preço de " << p->Gold[i] << "\n";
	}

	Log(clientId, LOG_INGAME, str.str().c_str());
	return true;
}


//backup
/*bool CUser::RequestCreateAutoTrade(PacketHeader* Header)
{
	p397 *p = (p397*)(Header);
	
	if(!pMob[clientId].Mobs.Player.Status.curHP || Status != USER_PLAY)
	{
		SendHpMode(clientId);
		AddCrackError(clientId, 10, 88);

		RemoveTrade(clientId);
		return true;
	}

	if (pUser[clientId].Trade.ClientId)
	{
		RemoveTrade(clientId);
		return true;
	}
	
	if(User.Block.Blocked)
	{
		SendClientMessage(clientId, "Desbloqueie seus itens para poder movimenta-los");
		
		RemoveTrade(clientId);
		return true;
	}
		
	INT32 posX = pMob[clientId].Target.X;
	INT32 posY = pMob[clientId].Target.Y;
	INT32 villageId = GetVillage(posX, posY);

	if(villageId < 0 || villageId >= 5)
	{
		SendClientMessage(clientId, g_pLanguageString[_NN_OnlyVillage]);
		
		RemoveTrade(clientId);
		return true;
	}

	if(!sServer.NoviceChannel)
	{
		SendClientMessage(clientId, "Somente no canal novato para criação de lojas");
		
		RemoveTrade(clientId);
		return true;
	}

	if (clientId <= 0 || clientId >= MAX_PLAYER)
		return true;

	INT32 itemId = p->Index; // LOCAL_1204
	INT32 i = 0;
	int total = 0;
	for( ; i < 12; i ++)
	{
		if(p->Gold[i] < 0 || p->Gold[i] > 1999999999) 
			return false;

		if(p->Item[i].Index == 0 && p->Gold[i] != 0)
			return false;

		if(p->Item[i].Index == 0)
			continue;

		if(p->Item[i].Index == 508 || p->Item[i].Index == 509 || p->Item[i].Index == 522 || (p->Item[i].Index >= 526 && p->Item[i].Index <= 531) || p->Item[i].Index == 446
			|| p->Item[i].Index == 3993 || p->Item[i].Index == 3994)
			return false;

		if (GetItemAbility(&p->Item[i], EF_NOTRADE))
		{
			SendClientMessage(clientId, "Este item não é negociavel.");

			return false;
		}

		INT32 itemSlot = p->Slot[i]; // LOCAL1206
		if(itemSlot < 0 || itemSlot >= 168)
			return false;

		INT32 verify = memcmp(&User.Storage.Item[itemSlot], &p->Item[i], 8);
		if (verify != 0)
		{
			RemoveTrade(clientId);

			return true;
		}

		if (p->Gold[i] >= 10000000)
			total++;
	}

	p->Unknown = g_pCityZone[villageId].perc_impost;
	p->Name[23] = '\0';
	p->Name[22] = '\0';

	strncpy_s((char*)AutoTradeName, 24, p->Name, 24);

	if (sServer.AutoTradeEvent.Status && strstr(AutoTradeName, "#EventoLoja") != nullptr)
	{
		CUser* userWithAutoTrade = nullptr;
		CUser* userWithEventOnline = nullptr;
		for (int i = 1; i < MAX_PLAYER; i++)
		{
			auto& user = pUser[i];
			if (user.Status != USER_PLAY || i == clientId)
				continue;

			if (memcmp(MacAddress, user.MacAddress, 8) != 0)
				continue;
 
			if (!user.IsAutoTrading || strstr(user.AutoTradeName, "#EventoLoja") == nullptr)
				continue;

			userWithAutoTrade = &user;
			break;
		}

		if (userWithAutoTrade != nullptr)
		{
			Log(clientId, LOG_INGAME, "Loja não valida para recebimento do item do evento pois a conta %s estava online também", userWithAutoTrade->User.Username);
			SendClientMessage(clientId, "!Esta loja não esta valida para recebimento do item do evento.");

			EventAutoTrade.IsValid = false;
		}
		else if (userWithEventOnline != nullptr)
		{
			Log(clientId, LOG_INGAME, "Loja não valida para recebimento do item do evento pois a conta %s estava com o evento online ativo", userWithEventOnline->User.Username);
			SendClientMessage(clientId, "!Esta loja não esta valida para recebimento do item do evento.");

			EventAutoTrade.IsValid = false;
		}
		else
		{
			Log(clientId, LOG_INGAME, "Esta loja valida para recebimento do item do evento");
			SendClientMessage(clientId, "!Loja valida para recebimento do item do evento");

			EventAutoTrade.IsValid = true;
			EventAutoTrade.LastTime = std::chrono::high_resolution_clock::now();

			GenerateNewAutoTradeTime();
		}
	}

	// Verifica se o total de itens com 10 milhaes de gold a maior que 5
	if (total >= 5)
	{
		bool has = false;
		for (int j = 1; j < MAX_PLAYER; j++)
		{
			if (pUser[j].Status != USER_PLAY || j == clientId || !pUser[j].IsAutoTrading || !pUser[j].PremierStore.Status)
				continue;

			if (!memcmp(pUser[j].MacAddress, pUser[clientId].MacAddress, 6))
			{
				has = true;

				break;
			}
		}

		if (!has)
		{
			if (PremierStore.Wait == 0 || (PremierStore.Wait != 0 && PremierStore.Wait > 300))
			{ // abre a loja normalmente com o status normal 
				PremierStore.Status = 1;
				PremierStore.Time = 0;
				PremierStore.Count = 0;

				SendClientMessage(clientId, "Loja premiada ativada!");
			}
			else
				PremierStore.Wait = 0;
		}
	}

	IsAutoTrading = true;

	memcpy(&AutoTrade, p, sizeof AutoTrade);

	p363 sm{};
	GetCreateMobTrade(clientId, (BYTE*)&sm);
	GridMulticast_2(posX, posY, (BYTE*)&sm, 0);
	std::stringstream str;
	str << "Informações dos itens da loja\n";
	str << "Nome da loja: " << p->Name << "\n";
	str << "Posição criada: " << pMob[clientId].Target.X << "x " << pMob[clientId].Target.Y << "\n";
	str << "Total de itens com valor superior a 10 milhões: " << total << "\n";
	str << "[ITENS]" << "\n";

	for (int i = 0; i < 12; i++)
	{
		if (p->Item[i].Index == 0 && p->Gold[i] != 0)
			return false;

		if (p->Item[i].Index == 0)
			continue;

		str << "Slot [" << std::to_string(p->Slot[i]) << "] - " << ItemList[p->Item[i].Index].Name << " " << p->Item[i].toString().c_str() << ". Preço de " << p->Gold[i] << "\n";
	}

	Log(clientId, LOG_INGAME, str.str().c_str());
	return true;
}*/
