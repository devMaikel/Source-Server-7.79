#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "CNPCGener.h"
#include "CEventManager.h"
#include <ctime>
#include <algorithm>
#include <sstream>

void CUser::HandleAdminCommand(p334* p)
{
	if (!p->eValue[0])
	{
		SendClientMessage(clientId, "Utilize /admin +command");
		return;
	}

	char nickName[36];
	int x = -1,
		y = -1,
		slot = -1;

	int rate = 0;
	int id = 0;
	int x2 = 0, y2 = 0;
	int limit = 0;

	char szTMP[4096];
	STRUCT_ITEM Item;
	memset(&Item, 0, 8);

	 if (!strncmp(p->eValue, "+set item", 9))
	{
		short itemID = 0, ef[3] = { 0, 0, 0 }, efv[3] = { 0, 0, 0 };

		int ret = sscanf_s(p->eValue, "+set item %04hd %03hd %03hd %03hd %03hd %03hd %03hd", &itemID, &ef[0], &efv[0], &ef[1], &efv[1], &ef[2], &efv[2]);
		if (ret < 1)
		{
			SendClientMessage(clientId, "Comando invalido");
			return;
		}

		STRUCT_ITEM item;
		memset(&item, 0, sizeof STRUCT_ITEM);

		item.Index = itemID;
		item.Effect[0].Index = ef[0];
		item.Effect[0].Value = efv[0];
		item.Effect[1].Index = ef[1];
		item.Effect[1].Value = efv[1];
		item.Effect[2].Index = ef[2];
		item.Effect[2].Value = efv[2];

		if (ef[0] == 99)
		{
			memset(&item, 0, sizeof STRUCT_ITEM);

			item.Index = itemID;
			SetItemBonus(&item, pMob[clientId].Mobs.Player.Status.Level, 0, 100);
		}

		int i = GetFirstSlot(clientId, 0);
		if (i == -1)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_You_Have_No_Space_To_Trade]);

			return;
		}

		memcpy(&pMob[clientId].Mobs.Player.Inventory[i], &item, sizeof STRUCT_ITEM);

		SendItem(clientId, SlotType::Inv, i, &item);
		Log(clientId, LOG_ADMIN, "%s criou o item %s [%d] [%d %d %d %d %d %d]", pMob[clientId].Mobs.Player.Name, ItemList[item.Index].Name, item.Index, item.EF1, item.EFV1, item.EF2, item.EFV2, item.EF3, item.EFV3);
		Log(SERVER_SIDE, LOG_ADMIN, "%s criou o item %s [%d] [%d %d %d %d %d %d]", pMob[clientId].Mobs.Player.Name, ItemList[item.Index].Name, item.Index, item.EF1, item.EFV1, item.EF2, item.EFV2, item.EF3, item.EFV3);
		return;
	}


	if (!strncmp(p->eValue, "+set move", 9))
	{
		int ret = sscanf_s(p->eValue, "+set move %d %d", &x, &y);
		if (ret != 2 || x < 0 || x >= 4096 || y < 0 || y >= 4096)
		{
			SendClientMessage(clientId, "Coordenadas invalidas");
			return;
		}

		Teleportar(clientId, x, y);
		return;
	}

	else if (sscanf_s(p->eValue, "+set hpmob %d %[^\n] ", &x, nickName, 16))
	{
		for (int i = 1000; i < 30000; i++)
		{
			if (!pMob[i].Mobs.Player.Status.curHP || pMob[i].Mode == 0)
				continue;

			if (!strcmp(nickName, pMob[i].Mobs.Player.Name))
			{
				pMob[i].Mobs.Player.Status.curHP = x;

				p363 sm;
				GetCreateMob(i, (BYTE*)&sm);

				GridMulticast_2(pMob[i].Target.X, pMob[i].Target.Y, (BYTE*)&sm, 0);
				SendClientMessage(clientId, "HPmob setado");
				return;
			}
		}

		SendClientMessage(clientId, "Mob nao encontado");
		return ;
	}
		
	else if (!strncmp(p->eValue, "+set snoop", 10))
	{
		if (pMob[clientId].Mobs.Player.Info.Merchant & 1)
		{
			SendClientMessage(clientId, "SNOOP OFF");

			pMob[clientId].Mobs.Player.Info.Merchant &= 254;
		}
		else
		{
			SendClientMessage(clientId, "SNOOP ON");

			pMob[clientId].Mobs.Player.Info.Merchant = pMob[clientId].Mobs.Player.Info.Merchant | 1;
		}

		pMob[clientId].GetCurrentScore(clientId);
		SendScore(clientId);

		p364 packet;
		GetCreateMob(clientId, (BYTE*)&packet);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packet, 0);
		return;
	}

	else if (sscanf_s(p->eValue, "+set name %s", nickName, 16))
	{
		strcpy_s(pMob[clientId].Mobs.Player.Name, nickName);

		CharLogOut(clientId);
		return;
	}

	else if (!strcmp(p->eValue, "+set dcall"))
	{
		int total = 0;
		int count = 0;
		for (INT32 t = 1; t < MAX_PLAYER; t++)
		{
			if (pUser[t].Status < USER_SELCHAR)
				continue;

			SendClientMessage(t, "Servidor entrando em manutenaao...");
			CloseUser(t);
		}

		SendClientMessage(clientId, "Foram desconectados %d usuarios", total);
		return;
	}

	else if (!strcmp(p->eValue, "+set reboot"))
	{
		sServer.isReboot = true;
		SendClientMessage(clientId, "O servidor entrou em modo de desligamento.");
		return;
	}

	else if (!strcmp(p->eValue, "+set userson"))
	{
		INT32 totalOn = 0,
			on = 0;

		for (INT32 x = 1; x < MAX_PLAYER; x++)
		{
			if (pUser[x].Status < USER_SELCHAR)
				continue;

			totalOn++;

			INT32 t = x;
			for (; t < MAX_PLAYER; t++)
			{
				if (pUser[t].Status < 11)
					continue;

				if (t == x)
					continue;

				if (!memcmp(&pUser[x].MacAddress, &pUser[t].MacAddress, 6))
					break;
			}

			if (t != MAX_PLAYER)
				continue;

			on++;
		}

		SendClientMessage(clientId, "Temos %d (%d) usuarios online", totalOn, on);
		return;
	}

	else if (!strncmp(p->eValue, "+set exp", 8))
	{
		UINT64 exp = 0;
		int ret = sscanf_s(p->eValue, "+set exp %lld", &exp);
		if (ret == 0)
		{
			SendClientMessage(clientId, "andice invalido");
			return;
		}

		pMob[clientId].Mobs.Player.Exp = exp;
		SendScore(clientId);
		SendEtc(clientId);
		return;
	}

	else if (!strncmp(p->eValue, "+set generate", 13))
	{
		int generate = -1;

		int ret = sscanf_s(p->eValue, "+set generate %d", &generate);
		if (generate < 0 || generate >= 8196)
		{
			SendClientMessage(clientId, "Indice invalido");
			return;
		}

		GenerateMob(generate, 0, 0);
		SendClientMessage(clientId, "Criado o mob %s em %dx %dy", mGener.pList[generate].Leader.Name, mGener.pList[generate].Segment_X[0], mGener.pList[generate].Segment_Y[0]);
		return;
	}

	else if (sscanf_s(p->eValue, "+set weekmode %d", &x))
	{
		sServer.ForceWeekDay = x;
		sServer.WeekMode = x - 1;

		if (sServer.WeekMode == -1)
			sServer.WeekMode = 5;

		SendClientMessage(clientId, "SET WEEKMODE");
		return;
	}

	else if (!strncmp(p->eValue, "+setquest", 9))
	{
		int v;
		int ret = sscanf_s(p->eValue, "+setquest %d", &v);

		pMob[clientId].Mobs.DailyQuest.QuestId = v;
	}

	else if (sscanf_s(p->eValue, "+set mission %d", &x))
	{
		pMob[clientId].Mobs.DailyQuest.QuestId = x;
		pMob[clientId].Mobs.DailyQuest.IsAccepted = false;

		SendMissionInfo(clientId);
		SendClientMessage(clientId, "Setado missão");
	}

	else if (!strcmp(p->eValue, "+reload missions"))
	{
		ReadMissions();

		SendClientMessage(clientId, "RELOAD DAILYQUEST");
	}
	else if (sscanf_s(p->eValue, "+set gate %d %s", &x, &nickName, 16))
	{
		if (x < 0 || x >= 4096)
			return;

		int status = 0;
		if (!strcmp(nickName, "abrir"))
			status = 1;
		else
			status = 3;

		p374 p;
		p.Header.PacketId = 0x374;
		p.Header.ClientId = SERVER_SIDE;
		p.Header.Size = sizeof p374;

		p.gateId = 10000 + x;

		p.status = status;
		p.Height = (status == 3) ? 18 : 0;

		GridMulticast_2(g_pInitItem[x].PosX, g_pInitItem[x].PosY, (BYTE*)&p, 0);

		int pa = 0;
		UpdateItem(x, status, &pa);

		sprintf_s(szTMP, "Portao %d %s - %dx %dy", x, (status == 1) ? "aberto" : "fechado", g_pInitItem[x].PosX, g_pInitItem[x].PosY);
		SendClientMessage(clientId, szTMP);
		return;
	} 

	else if (!strcmp(p->eValue, "+set createkefra"))
	{
		if (!sServer.KefraDead)
			return;

		for (INT32 i = GUARDAS_KEFRA; i < GUARDAS_KEFRA + 18; i++)
		{
			// Faz o mob não ficar nascendo após morrer 
			mGener.pList[i].MinuteGenerate = 4;

			// Gera os mobs
			GenerateMob(i, 0, 0);
		}

		// Limpa as variáveis
		sServer.KefraDead = FALSE;
		sServer.KefraKiller = 0;

		// Gera o Kefra no devido local
		GenerateMob(0155, 0, 0);

		// Envia mensagem para o canal completo com o renascimento do Kefra
		SendNotice(g_pLanguageString[_NN_Kefra_Reborn]);

		// Limpa a área
		ClearArea(3200, 1664, 3328, 1791);
		return;
	}
 
	else if (!strncmp(p->eValue, "+set cash", 9))
	{
		int ret = sscanf_s(p->eValue, "+set cash %d", &x);
		if (ret != 1)
			return;

		pUser[clientId].User.Cash = x;
		SendClientMessage(clientId, "SET CASH");
		SendClientPacket(clientId);//aqui

		return;
	}

	else if (!strncmp(p->eValue, "+set runes", 10))
	{
		int ret = sscanf_s(p->eValue, "+set runes %d", &x);
		if (ret != 1)
		{
			SendClientMessage(clientId, "Digite um valor valido");
			return;
		}

		if (x <= 0 || x >= 10)
		{
			SendClientMessage(clientId, "Manimo de 1 e maximo de 10");

			return;
		}

		sServer.RunesPerSanc = x;
		SendClientMessage(clientId, "SET RUNES");
		Log(clientId, LOG_INGAME, "Setado o valor de RunesPerSanc %d", x);
		return;
	}

	else if (!strncmp(p->eValue, "+set kill kefra", 15))
	{
		int ret = sscanf_s(p->eValue, "+set kill kefra %d", &x);
		if (ret != 1)
			return;

		sServer.KefraKiller = x;
		sServer.KefraDead = true;

		for (INT32 i = 1000; i < MAX_MOB; i++)
		{
			if (pMob[i].GenerateID != KEFRA)
				continue;

			MobKilled(i, clientId, 0, 0);
		}

		Log(SERVER_SIDE, LOG_INGAME, "KEFRA - Kefra derrotado por guildId: %d usando o comando.", x);
		return;
	}
	 
	else if (!strncmp(p->eValue, "+set level", 10))
	{
		int ret = sscanf_s(p->eValue, "+set level %d", &x);
		if (ret != 1)
		{
			SendClientMessage(clientId, "Level invalido");
			return;
		}

		pMob[clientId].Mobs.Player.bStatus.Level = x;
		pMob[clientId].Mobs.Player.Status.Level = x;

		if (pMob[clientId].Mobs.Player.Equip[0].EFV2 >= 0 && pMob[clientId].Mobs.Player.Equip[0].EFV2 <= SUBCELESTIAL && x >= 0 && x < 400)
			pMob[clientId].Mobs.Player.Exp = g_pNextLevel[pMob[clientId].Mobs.Player.Equip[0].EFV2][x];
		else
			pMob[clientId].Mobs.Player.Exp = 0;
		pMob[clientId].GetCurrentScore(clientId);

		SendScore(clientId);
		SendEtc(clientId);

		p364 packet;
		GetCreateMob(clientId, (BYTE*)&packet);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packet, 0);
		return;
	}
	
	else if (!strncmp(p->eValue, "+limparinv", 10))
	{
		memset(pMob[clientId].Mobs.Player.Inventory, 0, sizeof STRUCT_ITEM * 60);

		SendCarry(clientId);
		return;
	}

	else if (!_strnicmp(p->eValue, "+guildhour", 10))
	{
		INT32 ret = sscanf_s(p->eValue, "+guildhonour %d", &x);

		sServer.GuildHour = x;
		SendClientMessage(clientId, "SET GUILDHONOUR");
		return;

	}
	else if (!_strnicmp(p->eValue, "+guildday", 9))
	{
		INT32 ret = sscanf_s(p->eValue, "+guildday %d", &x);

		sServer.GuildDay = x;
		SendClientMessage(clientId, "SET GUILDDAY");
		return;
	}
	else if (!_strnicmp(p->eValue, "+guildchall", 11))
	{
		INT32 ret = sscanf_s(p->eValue, "+guildchall %d %d", &x, &y);

		g_pCityZone[x].chall_index = y;
		SendClientMessage(clientId, "SET GUILDCHALL");
		return;
	}

	else if (!_strnicmp(p->eValue, "+guildchall2", 12))
	{
		INT32 ret = sscanf_s(p->eValue, "+guildchall2 %d %d", &x, &y);

		g_pCityZone[x].chall_index_2 = y;
		SendClientMessage(clientId, "SET GUILDCHALL 2");
		return;
	}

	else if (!_strnicmp(p->eValue, "+guildowner", 11))
	{
		INT32 ret = sscanf_s(p->eValue, "+guildowner %d %d", &x, &y);

		ChargedGuildList[sServer.Channel - 1][x] = y;
		g_pCityZone[x].owner_index = y;

		UpdateCityTowers();
		GuildZoneReport();
		SendClientMessage(clientId, "SET GUILDOWNER");
		return;
	}

	else if (!strncmp(p->eValue, "+set guild impost", 17))
	{
		INT64 value = 0;
		sscanf_s(p->eValue, "+set guild impost %d %I64d", &x, &value);

		g_pCityZone[x].impost = value;

		SendClientMessage(clientId, "SET GUILD IMPOST");
		return;
	}
	else if (sscanf_s(p->eValue, "+set guild fame %d %d", &x, &y) == 2)
	{
		SetGuildFame(x, y);

		SendClientMessage(clientId, "SET GUILDFAME");
		return;
	}
	else if (!strncmp(p->eValue, "+set special", 12))
	{
		int ret = sscanf_s(p->eValue, "+set special %d %d", &x, &y);
		if (ret != 2 || x < 0 || x >= 4 || y < 0 || y > 255)
		{
			SendClientMessage(clientId, "Comando invalido");
			return;
		}

		pMob[clientId].Mobs.Player.bStatus.Mastery[x] = y;

		pMob[clientId].GetCurrentScore(clientId);
		SendScore(clientId);

		SendClientMessage(clientId, "SET SPECIAL");
		return;
	}
	else if (sscanf_s(p->eValue, "+set create %s %d", nickName, 16, &x))
	{
		if (x == -1)
			x = 1;

		for (INT32 c = 0; c < x; c++)
			CreateMob(nickName, pMob[clientId].Target.X, pMob[clientId].Target.Y, "npc");
		return;
	}

	else if (!strncmp(p->eValue, "+set removeall", 14))
	{
		INT32 ret = sscanf_s(p->eValue, "+set removeall %[^\n]", nickName, 36);

		INT32 len = strlen(nickName);
		INT32 count = 0;
		for (INT32 i = 1000; i < MAX_MOB; i++)
		{
			if (pMob[i].Mode == 0)
				continue;

			if (!strncmp(pMob[i].Mobs.Player.Name, nickName, len))
			{
				MobKilled(i, clientId, 0, 0);
				count++;
			}
		}

		if (count == 0)
			SendClientMessage(clientId, "Nao foi encontado mobs");
		else
			SendClientMessage(clientId, "Foram removidos %d mobs %s", count, nickName);
		return;
	}
	else if (!strncmp(p->eValue, "+set remove", 11) && sscanf_s(p->eValue, "+set remove %[^\n]", nickName, 16))
	{
		INT32 len = strlen(nickName);
		for (INT32 i = 1000; i < MAX_MOB; i++)
		{
			if (pMob[i].Mode == 0)
				continue;

			if (!strncmp(pMob[i].Mobs.Player.Name, nickName, len))
			{
				MobKilled(i, clientId, 0, 0);

				SendClientMessage(clientId, "Mob %s removido de %dx %dy", nickName, pMob[i].Target.X, pMob[i].Target.Y);
				return;
			}
		}

		SendClientMessage(clientId, "Mob nao encontrado");
		return;
	}

	else if (!strcmp(p->eValue, "+reloadall"))
	{
		ReadSkillData();
		ReadItemList();
		ReadGameConfig();
		ReadGameConfigv2();
		ReadNPCBase();

		SendClientMessage(clientId, "RELOADALL");
		return;
	}

	else if (!strcmp(p->eValue, "+set summonserver"))
	{
		INT32 total = 0;
		for (INT32 i = 1; i < MAX_PLAYER; i++)
		{
			if (pUser[i].Status != USER_PLAY)
				continue;

			if (i == clientId)
				continue;

			INT32 posX = pMob[clientId].Target.X,
				posY = pMob[clientId].Target.Y;

			if (total > 50)
				posX += 3, posY += 3;
			else if (total > 100)
				posX += 6, posY += 6;
			else
				posX += 10, posY += 10;

			Teleportar(i, posX, posY);
			total++;
		}

		SendClientMessage(clientId, "Summonado %d personagens...", total);
		return;
	}

	else if (sscanf_s(p->eValue, "+set summon %36s", nickName, 16))
	{
		int userId = GetUserByName(nickName);
		if (userId == 0)
		{
			SendClientMessage(clientId, "Usuario nao esta conectado");
			return;
		}

		Teleportar(userId, pMob[clientId].Target.X, pMob[clientId].Target.Y);
		SendClientMessage(clientId, "Summonou %s para %dx %dy", pMob[userId].Mobs.Player.Name, pMob[clientId].Target.X, pMob[clientId].Target.Y);
		return;
	}

	else if (sscanf_s(p->eValue, "+set kick %s", nickName, 16))
	{
		int userId = GetUserByName(nickName);
		if (userId == 0)
		{
			SendClientMessage(clientId, "Usuario nao esta conectado");

			return;
		}

		CloseUser(userId);

		SendClientMessage(clientId, "%s - %s foi kickado - ClientId %d", pMob[clientId].Mobs.Player.Name, nickName, userId);
		Log(SERVER_SIDE, LOG_ADMIN, "%s - %s foi kickado - ClientId %d", pMob[clientId].Mobs.Player.Name, nickName, userId);
		return;
	}

	else if (sscanf_s(p->eValue, "+set teleport %36s %d %d", nickName, 16, &x, &y))
	{
		int userId = GetUserByName(nickName);
		if (userId == 0)
		{
			SendClientMessage(clientId, "Usuario nao esta conectado");
			return;
		}
 
		Teleportar(userId, x, y);
		Log(SERVER_SIDE, LOG_ADMIN, "%s - Teleportou %s para %dx %dy", pMob[clientId].Mobs.Player.Name, nickName, x, y);
		return;
	}

	else if (sscanf_s(p->eValue, "+set weather %d", &x))
	{
		sServer.Weather = x;

		SendWeather();
		SendClientMessage(clientId, "SET WEATHER");
		return;
	}

	else if (sscanf_s(p->eValue, "+set drop %d", &x))
	{
		for (int i = 0; i < 64; i++)
			Taxes[i] = x;

		SendClientMessage(clientId, "Drop setado para: %d.", x);
		Log(SERVER_SIDE, LOG_ADMIN, "%s - Setou o drop para %d.", pMob[clientId].Mobs.Player.Name, x);
		return;
	}

	else if (sscanf_s(p->eValue, "+set bonusexp %d", &x))
	{
		sServer.BonusEXP = x;

		SendClientMessage(clientId, "Banus exp setado para: %d.", x);
		Log(SERVER_SIDE, LOG_ADMIN, "%s - Setou o banusexp para %d.", pMob[clientId].Mobs.Player.Name, x);
		return;
	}

	else if (sscanf_s(p->eValue, "+set coin %d", &x))
	{
		pMob[clientId].Mobs.Player.Gold = x;

		SendEtc(clientId);

		SendClientMessage(clientId, "Gold setado para: %d.", x);
		Log(SERVER_SIDE, LOG_ADMIN, "%s - Setou o Gold para %d.", pMob[clientId].Mobs.Player.Name, x);
		return;
	}

	else if (!strncmp(p->eValue, "+reloadpacitem", 10))
	{
		ReadPacItens();

		SendClientMessage(clientId, "RELOAD PACITEM");
		return;
	}

	else if (!strncmp(p->eValue, "+reload npcquest", 17))
	{
		ReadNPCQuest();

		SendClientMessage(clientId, "RELOAD NPCQUEST");
		return;
	}

	else if (!strncmp(p->eValue, "+reload evento", 10))
	{
		LoadNPCEvento();

		SendClientMessage(clientId, "RELOAD EVENTO");
		return;
	}

	else if (!strncmp(p->eValue, "+reloadnpc", 10))
	{
		mGener.ReadNPCGener();

		SendClientMessage(clientId, "RELOADNPC");
		return;
	}

	else if (!strncmp(p->eValue, "+set not", 7))
	{
		char message[96] = { 0 };
		int ret = sscanf_s(p->eValue, "+set not %96[^\n]", message, 95);

		if (ret == 0)
		{
			SendClientMessage(clientId, "Digite uma mensagem");

			return;
		}

		SendNotice(message);
		return;
	}

	else if (!strncmp(p->eValue, "+set status", 4))
	{
		static char cmdSet[4][4] =
		{
			"str",
			"dex",
			"int",
			"con"
		};

		INT32 mode = -1;
		INT32 ret = sscanf_s(p->eValue, "+set %s %d", nickName, 16, &x);

		for (INT32 i = 0; i < 4; i++)
		{
			if (!_strnicmp(nickName, cmdSet[i], 3))
			{
				mode = i;
				break;
			}
		}

		if (mode == -1)
		{
			short itemID = 0, ef[3] = { 0, 0, 0 }, efv[3] = { 0, 0, 0 };
			short index = -1;

			int ret = sscanf_s(p->eValue, "+set status %02hd %04hd %03hd %03hd %03hd %03hd %03hd %03hd", &index, &itemID, &ef[0], &efv[0], &ef[1], &efv[1], &ef[2], &efv[2]);
			if (ret < 2)
			{
				SendClientMessage(clientId, "Comando invalido");
				return;
			}

			if (index < 0 || index > 15)
			{
				SendClientMessage(clientId, "Indice invalido");
				return;
			}

			STRUCT_ITEM item;
			memset(&item, 0, sizeof STRUCT_ITEM);

			item.Index = itemID;
			item.Effect[0].Index = (ef[0] & 255);
			item.Effect[0].Value = (efv[0] & 255);
			item.Effect[1].Index = (ef[1] & 255);
			item.Effect[1].Value = (efv[1] & 255);
			item.Effect[2].Index = (ef[2] & 255);
			item.Effect[2].Value = (efv[2] & 255);

			memcpy(&pMob[clientId].Mobs.Player.Equip[index], &item, sizeof STRUCT_ITEM);

			SendItem(clientId, SlotType::Equip, index, &item);
			return;
		}

		switch (mode)
		{
		case 0:
			pMob[clientId].Mobs.Player.bStatus.STR = x;
			break;

		case 1:
			pMob[clientId].Mobs.Player.bStatus.DEX = x;
			break;

		case 2:
			pMob[clientId].Mobs.Player.bStatus.INT = x;
			break;

		case 3:
			pMob[clientId].Mobs.Player.bStatus.CON = x;
			break;
		}

		pMob[clientId].GetCurrentScore(clientId);

		SendScore(clientId);
		SendEtc(clientId);
		return;
	}

	else if (sscanf_s(p->eValue, "+set relo %s", nickName, 16))
	{

		int userId = GetUserByName(nickName);
		if (userId == 0)
		{
			SendClientMessage(clientId, "Usuario nao esta conectado");

			return;
		}

		Teleportar(clientId, pMob[userId].Target.X, pMob[userId].Target.Y);
		return;
	}


	else if (!strncmp(p->eValue, "+set resetcities", 16))
	{
		for (int i = 0; i < 5; ++i)
		{
			ChargedGuildList[sServer.Channel - 1][i] = 0;
			g_pCityZone[i].owner_index = 0;
			g_pCityZone[i].win_count = 0;
			g_pCityZone[i].impost = 0LL;
		}

		ClearChallanger();	
		UpdateCityTowers();
		SaveGuildZone();

		SendClientMessage(clientId, "Cidades resetadas com sucesso, beba");
		return;
	}

	else if (!strncmp(p->eValue, "+set learn", 9))
	{
		int ret = sscanf_s(p->eValue, "+set learn %d", &x);
		if (x < 0 || x >= 64)
		{
			SendClientMessage(clientId, "Comando invalido");

			return;
		}

		if (x < 32)
		{
			auto learnInfo = (1 << x);
			if (pMob[clientId].Mobs.Player.Learn[0] & learnInfo)
				pMob[clientId].Mobs.Player.Learn[0] -= learnInfo;
			else
				pMob[clientId].Mobs.Player.Learn[0] |= learnInfo;
		}
		else
		{
			auto learnInfo = (1 << (x - 32));
			if (pMob[clientId].Mobs.Player.Learn[1] & learnInfo)
				pMob[clientId].Mobs.Player.Learn[1] -= learnInfo;
			else
				pMob[clientId].Mobs.Player.Learn[1] |= learnInfo;
		}

		SendEtc(clientId);
		SendClientMessage(clientId, "SET LEARN");
		return;
	}


	else if (!strcmp(p->eValue, "+reload questbosses"))
	{
		ReadBossQuest();

		SendClientMessage(clientId, "RELOAD QUESTBOSSES");
		return;
	}

	else if (!strcmp(p->eValue, "+reload nocp"))
	{
		ReadNoCP();

		SendClientMessage(clientId, "RELOAD NOCP");
		return;
	}

	else if (!strcmp(p->eValue, "+reload language"))
	{
		ReadLanguageFile();

		SendClientMessage(clientId, "RELOAD LANGUAGE");
	}

	else if (!strcmp(p->eValue, "+reload blockitem"))
	{
		ReadBlockedItem();

		SendClientMessage(clientId, "RELOAD BLOCKITEM");
		return;
	}

	else if (!strcmp(p->eValue, "+reload message"))
	{
		ReadMessages();

		SendClientMessage(clientId, "RELOAD MESSAGE");
		return;
	}

	else if (!strcmp(p->eValue, "+reload scheduled"))
	{
		ReadScheduled();

		SendClientMessage(clientId, "RELOAD SCHEDULED");
		return;
	}

	else if (!strcmp(p->eValue, "+reload heightmap"))
	{
		ReadHeightMap();
		ApplyAttribute((char*)g_pHeightGrid, 4096);

		SendClientMessage(clientId, "RELOAD HEIGHTMAP");
		return;
	}

	else if (!strcmp(p->eValue, "+reload attributemap"))
	{
		ReadAttributeMap();

		SendClientMessage(clientId, "RELOAD ATTRIBUTEMAP!!!");
		return;
	}

	else if (!strcmp(p->eValue, "+reload teleport"))
	{
		ReadTeleport();

		SendClientMessage(clientId, "RELOAD TELEPORT");
		return;
	}

	else if (!strcmp(p->eValue, "+reload itemlevel"))
	{
		ReadLevelItem();

		SendClientMessage(clientId, "RELOAD LEVELITEM");
		return;

	}

	else if (!strcmp(p->eValue, "+reload premierstore"))
	{
		ReadMerchantStore();

		SendClientMessage(clientId, "RELOAD PREMIERSTORE");
		return;
	}

	return;
}