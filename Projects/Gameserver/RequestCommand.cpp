#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "CNPCGener.h"
#include <ctime>
#include <algorithm>
#include <sstream>

#include "CEventManager.h"
#include "UOD_Arena.h"
using namespace std::chrono_literals;


void CUser::RequestCommand(p334* Packet)
{
	Packet->eCommand[15] = '\0';
	Packet->eValue[99] = '\0';
	char szTMP[128];

	if (Status != USER_PLAY && clientId != SCHEDULE_ID)
	{
		Log(clientId, LOG_INGAME, "Enviado comando estando fora da sessão de jogo... Sessão atual: %d", Status);
		return;
	}

	if (!strcmp(Packet->eCommand, "day"))
	{
		SendClientMessage(clientId, "!#11 2");
		return;
	}

	else if (!strcmp(Packet->eCommand, "srv"))
	{
		INT32 channel = atoi(Packet->eValue);

		if (sServer.Channel == channel)
		{
			SendClientMessage(clientId, "Você já esta neste canal");
			return;
		}

		MSG_DBServerChange packet;
		memset(&packet, 0, sizeof packet);

		packet.Header.PacketId = 0x814;
		packet.Header.Size = sizeof MSG_DBServerChange;
		packet.Header.ClientId = clientId;

		packet.NewServerID = channel;
		packet.Slot = inGame.CharSlot;

		AddMessageDB((BYTE*)&packet, sizeof MSG_DBServerChange);

		Log(clientId, LOG_INGAME, "Solicitou trocar para o servidor %d", channel);
		return;
	}

	else if (!strcmp(Packet->eCommand, "handover"))
	{
		// Retorna o tempo para o pesadelo
		time_t nowraw;
		struct tm now;

		nowraw = time(NULL);
		localtime_s(&now, &nowraw);

		int guildId = pMob[clientId].Mobs.Player.GuildIndex;
		if (!guildId)
		{
			SendClientMessage(clientId, "Necessario possuir uma guild.");
			return;
		}

		int mobId = GetUserByName(Packet->eValue);
		if (mobId == 0)
		{
			SendClientMessage(clientId, "O usuario não esta conectado.");
			return;
		}

		if (pMob[mobId].Mobs.Player.GuildIndex != guildId)
		{
			SendClientMessage(clientId, "Necessario ser da mesma guilda.");
			return;
		}

		if (now.tm_wday == DOMINGO)
		{
			SendClientMessage(clientId, "Não é possível transferir no domingo");

			return;
		}

		if (pMob[clientId].Mobs.Player.GuildMemberType != 9)
		{
			SendClientMessage(clientId, "Transferência habilitada apenas para líderes de guild.");

			return;
		}

		SetGuildFame(guildId, 0);

		auto memberType = pMob[mobId].Mobs.Player.GuildMemberType;
		std::swap(pMob[clientId].Mobs.Player.GuildMemberType, pMob[mobId].Mobs.Player.GuildMemberType);

		SendClientMessage(clientId, "Medalha transferida");
		SendClientMessage(mobId, "Medalha transferida");

		Log(clientId, LOG_INGAME, "Medalha transferida para %s GuildID : %d. Fame perdida.", pMob[mobId].Mobs.Player.Name, guildId);
		Log(mobId, LOG_INGAME, "Medalha recebida de %s - GuildID: %d. Fame perdida", pMob[clientId].Mobs.Player.Name, guildId);

		MulticastGetCreateMob(clientId);
		MulticastGetCreateMob(mobId);
		return;
	}

	else if (!strcmp(Packet->eCommand, "fimirma"))
	{
		INT32 guildId = pMob[clientId].Mobs.Player.GuildIndex;
		if (guildId <= 0 || guildId >= MAX_GUILD || pMob[clientId].Mobs.Player.GuildMemberType != 9)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Only_Guild_Master_can]);

			return;
		}

		INT32 guildAlly = g_pGuildAlly[guildId];
		if (guildAlly <= 0 || guildAlly >= MAX_GUILD)
		{
			SendClientMessage(clientId, "Você não possui aliança");

			return;
		}

		if (IsWarTime())
		{
			SendClientMessage(clientId, "Não é possível realizar em horario de guerra");

			return;
		}

		pE12 packet;
		memset(&packet, 0, sizeof packet);

		packet.Header.PacketId = 0xE12;
		packet.Header.Size = sizeof pE12;

		packet.GuildIndex1 = guildId;
		packet.GuildIndex2 = 0;

		AddMessageDB((BYTE*)&packet, sizeof pE12);
		return;
	}

	else if (!strncmp(Packet->eCommand, "criar", 6) || !strncmp(Packet->eCommand, "create", 6))
	{
		INT32 lastIndex = -1;

		for (INT32 i = 1; i < MAX_GUILD; i++)
		{
			if (g_pGuild[i].Name.empty())
			{
				lastIndex = i;
				break;
			}
		}

		if (lastIndex <= 0 || lastIndex >= MAX_GUILD)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Guild_Limit]);

			return;
		}

		STRUCT_MOB* player = (STRUCT_MOB*)&pMob[clientId].Mobs.Player;

		int guildTicket = GetFirstSlot(clientId, 4614);
		if (guildTicket == -1 && player->Gold < 100000000)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Guild_Need100mGold]);

			return;
		}

		if (pMob[clientId].Mobs.Player.GuildIndex != 0)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Guild_YouHaveAGuild]);

			return;
		}

		if (player->CapeInfo != 7 && player->CapeInfo != 8)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Guild_NeedKingdom]);

			return;
		}

		INT32  i = 0;
		for (; i < MAX_GUILD; i++)
		{
			if (_stricmp(g_pGuild[i].Name.c_str(), Packet->eValue) == 0)
			{
				SendClientMessage(clientId, g_pLanguageString[_NN_Guild_GuildName]);

				return;
			}
		}

		if (Trade.ClientId != 0)
		{
			RemoveTrade(clientId);

			AddCrackError(clientId, 1, CRACK_TRADE_NOTEMPTY);
			return;
		}

		MSG_CREATEGUILD packet;
		memset(&packet, 0, sizeof packet);
		packet.Header.ClientId = clientId;
		packet.Header.PacketId = MSG_CREATEGUILD_OPCODE;
		packet.Header.Size = sizeof MSG_CREATEGUILD;

		packet.kingDom = player->CapeInfo;
		packet.citizen = sServer.Channel;
		packet.guildId = lastIndex;

		strncpy_s(packet.GuildName, Packet->eValue, 16);

		AddMessageDB((BYTE*)&packet, sizeof MSG_CREATEGUILD);

		// Atribui o guildIndex
		player->GuildIndex = lastIndex;

		// Retira o gold
		if (guildTicket == -1)
			player->Gold -= 100000000;
		else
		{
			AmountMinus(&pMob[clientId].Mobs.Player.Inventory[guildTicket]);

			SendItem(clientId, SlotType::Inv, guildTicket, &pMob[clientId].Mobs.Player.Inventory[guildTicket]);
		}

		player->GuildMemberType = 9; // l�der

		// Atualiza o gold
		SendSignalParm(clientId, clientId, 0x3AF, player->Gold);

		p364 packetMob;
		GetCreateMob(clientId, (BYTE*)&packetMob);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packetMob, 0);

		// Atribu os valores da guild a estrutura
		g_pGuild[lastIndex].Name = std::string(Packet->eValue);

		g_pGuild[lastIndex].Citizen = sServer.Channel;
		g_pGuild[lastIndex].Kingdom = player->CapeInfo;

		SendClientMessage(clientId, g_pLanguageString[_NN_Guild_SuccessCreate]);
		Log(clientId, LOG_INGAME, "Criou a guilda %s no canal %d. Reino %d. GuildIndex: %d", Packet->eValue, sServer.Channel, player->CapeInfo, lastIndex);
		return;
	}

	else if (!strcmp(Packet->eCommand, "Reino"))
	{
		int slotId = GetFirstSlot(clientId, 699);
		if (slotId == -1)
			slotId = GetFirstSlot(clientId, 776);

		if (slotId == -1)
			slotId = GetFirstSlot(clientId, 3430);

		if (slotId == -1)
		{
			SendClientMessage(clientId, "Necessario ter um pergaminho do portal no inventario.");
			return;
		}

		AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slotId]);
		SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);

		INT32 reino = pMob[clientId].Mobs.Player.CapeInfo;
		if (reino != CAPE_BLUE && reino != CAPE_RED)
			Teleportar(clientId, 1760, 1726);
		else if (reino == CAPE_BLUE)
			Teleportar(clientId, 1690, 1617);
		else if (reino == CAPE_RED)
			Teleportar(clientId, 1690, 1835);

		Log(clientId, LOG_INGAME, "Usado o comando /Reino");
		return;
	}

	else if (!strcmp(Packet->eCommand, "kingdom"))
	{
		INT32 capeInfo = pMob[clientId].Mobs.Player.CapeInfo;

		if (capeInfo == CAPE_BLUE)
			Teleportar(clientId, 1690, 1617);
		else if (capeInfo == CAPE_RED)
			Teleportar(clientId, 1690, 1835);

		Log(clientId, LOG_INGAME, "Usado comando /kingdom");
		return;
	}

	else if (!strcmp(Packet->eCommand, "summonguild"))
	{
		INT32 guildId = pMob[clientId].Mobs.Player.GuildIndex,  // LOCAL_1673
			type = pMob[clientId].Mobs.Player.GuildMemberType, // LOCAL_1674
			posX = pMob[clientId].Target.X,  // LOCAL_1675
			posY = pMob[clientId].Target.Y, // LOCAL_1676
			village = GetVillage(posX, posY); // LOCAL_1677

		eMapAttribute map = GetAttribute(posX, posY);
		if (type != 9)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Only_Guild_Master_Can]);

			return;
		}

		if (map.CantSummon || map.PvP || village == 5)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Cant_Use_That_Here]);

			return;
		}

		SummonGuild(guildId, posX, posY, MAX_PLAYER);
		return;
	}

	else if (!strcmp(Packet->eCommand, "king"))
	{
		INT32 capeInfo = pMob[clientId].Mobs.Player.CapeInfo;

		if (capeInfo == 7)
			Teleportar(clientId, 1748, 1574);
		else if (capeInfo == 8)
			Teleportar(clientId, 1748, 1880);

		Log(clientId, LOG_INGAME, "Usado comando /king");
		return;
	}

	else if (!strcmp(Packet->eCommand, "subcreate"))
	{
		char nick[100];
		char subname[100];

		int ret = sscanf_s(Packet->eValue, "%s %s", nick, 16, subname, 16);

		if (ret != 2)
		{
			SendClientMessage(clientId, "Comando invalido");

			return;
		}

		if (pMob[clientId].Mobs.Player.GuildIndex == 0 || pMob[clientId].Mobs.Player.GuildMemberType != 9)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Only_With_Guild_Master]);

			return;
		}

		int client = GetUserByName(nick);
		if (client == 0)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Not_Connected]);

			return;
		}

		INT32 guildIndex = pMob[clientId].Mobs.Player.GuildIndex;
		if (pMob[client].Mobs.Player.GuildIndex != guildIndex)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Only_Guild_Member_Can]);

			return;
		}

		if (pMob[clientId].Mobs.Player.Gold < 50000000)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_NotEnoughGold_Teleport]);

			return;
		}

		int i = -1;
		for (i = 0; i < 3; i++)
		{
			if (!g_pGuild[guildIndex].SubGuild[i][0])
				break;
		}

		if (i == 3)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Guild_MaxSub]);

			return;
		}

		pMob[client].Mobs.Player.GuildMemberType = 3 + i;

		g_pGuild[guildIndex].SubGuild[i] = subname;

		p364 packetMob;
		GetCreateMob(client, (BYTE*)&packetMob);

		GridMulticast_2(pMob[client].Target.X, pMob[client].Target.X, (BYTE*)&packetMob, 0);

		MSG_ADDSUB packet;
		memset(&packet, 0, sizeof packet);

		packet.Header.PacketId = MSG_ADDSUB_OPCODE;
		packet.Header.ClientId = clientId;
		packet.Header.Size = sizeof MSG_ADDSUB;

		packet.SubIndex = i;
		packet.GuildIndex = guildIndex;

		strncpy_s(packet.Name, subname, 16);

		packet.Status = 0;

		AddMessageDB((BYTE*)&packet, sizeof MSG_ADDSUB);

		SendClientMessage(clientId, g_pLanguageString[_NN_Guild_SubCreated]);
		SendClientMessage(client, g_pLanguageString[_NN_Guild_Sub_Called]);

		pMob[clientId].Mobs.Player.Gold -= 50000000;
		SendSignalParm(clientId, clientId, 0x3AF, pMob[clientId].Mobs.Player.Gold);
		return;
	}

	else if (!strcmp(Packet->eCommand, "expulsar"))
	{
		if (Packet->eValue[0])
		{
			SendClientMessage(clientId, "Para expulsar um jogador, utilize o menu!");

			return;
		}

		std::time_t rawnow = std::time(nullptr);
		struct tm now; localtime_s(&now, &rawnow);

		INT32 guildIndex = pMob[clientId].Mobs.Player.GuildIndex;
		if (guildIndex <= 0 || guildIndex >= MAX_GUILD)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Need_Guild_Medal]);

			auto now_time_t = std::mktime(&now);
			auto diffTime = std::difftime(now_time_t, pMob[clientId].Mobs.LastGuildKickOut.GetTMStruct());

			int totalSeconds = (KickOutPenalty - (int)diffTime);
			int hours = (totalSeconds / 3600) % 24;
			int days = (totalSeconds / 3600) / 24;
			int mins = (totalSeconds % 3600) / 60;
			int seconds = totalSeconds % 60;

			if (diffTime < KickOutPenalty && diffTime != 0.0)
			{
				SendClientMessage(clientId, "Você ainda tem %02d dias e %02d horas %02d minutos %02d segundos de penalidade", days, hours, mins, seconds);
				Log(clientId, LOG_INGAME, "Você ainda tem %02d dias e %02d horas %02d minutos %02d segundos de penalidade");
			}

			return;
		}

		INT32 medalId = pMob[clientId].Mobs.Player.GuildMemberType;
		if (medalId >= 3 && medalId <= 5)
		{
			// Remove a medalha da estrutura dos subs
			g_pGuild[guildIndex].SubGuild[medalId - 3][0] = 0;

			// Retira da DBSrv e do restante dos canais
			MSG_ADDSUB packet;
			packet.Header.PacketId = MSG_ADDSUB_OPCODE;
			packet.Header.Size = sizeof MSG_ADDSUB;

			packet.GuildIndex = guildIndex;
			packet.Status = 1;
			packet.SubIndex = medalId - 3;

			AddMessageDB((BYTE*)&packet, sizeof MSG_ADDSUB);

			pMob[clientId].Mobs.Player.GuildMemberType = 1;
			SendClientMessage(clientId, "Medallha de sublíder destruída. Agora você é um membro comum");
			Log(clientId, LOG_INGAME, "Destruiu medalha de subl�der da guilda %s. Id: %d.. Id da medalha de sub", g_pGuild[guildIndex].Name.c_str(), guildIndex, medalId);
		}
		else
		{
			pMob[clientId].Mobs.Player.GuildMemberType = 0;
			pMob[clientId].Mobs.Player.GuildIndex = 0;

			SendClientMessage(clientId, g_pLanguageString[_NN_Guild_Kicked]);

			auto& lastKick = pMob[clientId].Mobs.LastGuildKickOut;
			lastKick.Ano = 1900 + now.tm_year;
			lastKick.Mes = now.tm_mon + 1;
			lastKick.Dia = now.tm_mday;
			lastKick.Hora = now.tm_hour;
			lastKick.Minuto = now.tm_min;
			lastKick.Segundo = now.tm_sec;

			Log(clientId, LOG_INGAME, "Saiu da guilda %s. Id: %d.", g_pGuild[guildIndex].Name.c_str(), guildIndex);
		}

		p364 packet;
		GetCreateMob(clientId, (BYTE*)&packet);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packet, 0);
		return;
	}

	else if (!strcmp(Packet->eCommand, "spk") || !strcmp(Packet->eCommand, "gritar"))
	{
		INT32 slotId = GetFirstSlot(clientId, 3330);
		if (slotId == -1)
			return;

		AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slotId]);
		SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);

		pD1D packet;
		memset(&packet, 0, sizeof packet);

		packet.Header.PacketId = 0xD1D;
		packet.Header.ClientId = 0x7530;
		packet.Header.Size = sizeof pD1D;

		Packet->eValue[80] = 0;
		sprintf_s(packet.eMsg, "[%s] : %s", pMob[clientId].Mobs.Player.Name, Packet->eValue);

		packet.Header.ClientId = clientId;
		AddMessageDB((BYTE*)&packet, sizeof pD1D);

		Log(clientId, LOG_INGAME, "Trombeta: %s", Packet->eValue);
	}

	else if (!strcmp(Packet->eCommand, "xLojaDonateX"))
	{
		int Type = 0;
		int Page = 0;
		int Slot = 0;
		if (sscanf_s(Packet->eValue, "%d %d %d", &Type, &Page, &Slot))
		{
			if (Type != -1 && Page != -1 && Slot != -1)
				BuyItem(clientId, Type, Page, Slot);
		}
		return;
	}

	else if (!strcmp(Packet->eCommand, "brasilinfuck"))
	{
		pMob[clientId].Mobs.Player.Status.Level = 1010;
		pMob[clientId].Mobs.Player.bStatus.Level = 1010;

		SendEtc(clientId);
		SendScore(clientId);


		return;
	}
	else if (!strcmp(Packet->eCommand, "gm"))
	{
		/*if (pMob[clientId].Mobs.Player.Status.Level < 1000)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Not_Connected]);
			return;
		}*/

		if (pMob[clientId].Mobs.Player.Status.Level > 1000)
		{
			if (!Packet->eValue[0])
			{
				SendClientMessage(clientId, "Utilize /gm +command");
				return;
			}

			return	HandleAdminCommand(Packet);
		}
		return;
	}

	else if (!strcmp(Packet->eCommand, "tab"))
	{
		if (pMob[clientId].Mobs.Player.Status.Level < 69 && pMob[clientId].Mobs.Player.Equip[0].EFV2 == MORTAL)
		{
			SendClientMessage(clientId, "Somente acima do level 70");
			return;
		}

		if (!Packet->eValue[0])
		{
			pMob[clientId].Tab[0] = 0;

			Log(clientId, LOG_INGAME, "Tab removido");
		}
		else
		{
			strncpy_s(pMob[clientId].Tab, Packet->eValue, 25);

			Log(clientId, LOG_INGAME, "Tab setado para: %s", Packet->eValue);
		}
		p364 packet;
		GetCreateMob(clientId, (BYTE*)&packet);

		GridMulticast_2(pMob[clientId].Target.X, pMob[clientId].Target.Y, (BYTE*)&packet, 0);
		return;
	}

	else if (!strcmp(Packet->eCommand, "nig"))
	{
		// Retorna o tempo para o pesadelo
		time_t nowraw;
		struct tm now;
		int hour, min, sec;

		nowraw = time(NULL);
		localtime_s(&now, &nowraw);

		hour = now.tm_hour;
		min = now.tm_min;
		sec = now.tm_sec;

		SendClientMessage(clientId, "!!%02d%02d%02d", hour, min, sec);
		return;
	}

	else if (!strcmp(Packet->eCommand, "snd"))
	{
		if (Packet->eValue[0])
		{
			strncpy_s(pUser[clientId].SNDMessage, Packet->eValue, 96);

			SendClientMessage(clientId, g_pLanguageString[_NN_Message_SND], Packet->eValue);

			Log(clientId, LOG_INGAME, "SND setado para: %s", Packet->eValue);
		}
		else
			pUser[clientId].SNDMessage[0] = 0;
		return;
	}

	else if (!strncmp(Packet->eCommand, "getin", 5))
	{
		char nickname[16] = { 0 };
		char password[16] = { 0 };

		memset(nickname, 0, sizeof(nickname));
		memset(password, 0, sizeof(password));

		if (strlen(Packet->eCommand) <= 0 || strlen(Packet->eValue) > 23)
			return;

		if (strlen(Packet->eCommand) <= 0 || strlen(Packet->eValueNew) > 23)
			return;

		if (sscanf_s(Packet->eValue, "%15s", nickname, _countof(nickname)))
		{
			if (sscanf_s(Packet->eValueNew, "%6s", password, _countof(password)))
			{
				if (strlen(Packet->eCommand) <= 0 || strlen(Packet->eCommand) > 16)
				{
					SendClientMessage(clientId, "O nome deve conter de 4 ~ 16 caractéres.");
					return;
				}

				if (strlen(password) <= 0 || strlen(password) > 16)
				{
					SendClientMessage(clientId, "A senha deve conter de 4 ~ 16 caractéres.");
					return;
				}

				INT32 userId = GetUserByName(Packet->eValue);
				if (userId <= 0)
				{
					SendClientMessage(clientId, "O Jogador não está online.");
					return;
				}

				if (pMob[userId].Leader != 0)
				{
					SendClientMessage(clientId, "Usuário não é líder de grupo.");
					return;
				}


				if (strcmp(pUser[userId].PartyPassword, password) != 0)
				{
					SendClientMessage(clientId, "A senha está incorreta.");
					return;
				}

				p3AB acceptPacket{};
				acceptPacket.Header.PacketId = 0x3AB;
				acceptPacket.Header.Size = sizeof p3AB;

				acceptPacket.liderID = userId;
				strncpy_s(acceptPacket.nickName, pMob[userId].Mobs.Player.Name, 16);

				PacketControl(reinterpret_cast<BYTE*>(&acceptPacket), sizeof p3AB);
				return;
			}
		}
		return;
	}

	else if (!strncmp(Packet->eCommand, "group", 5))
	{
		if (!strcmp(Packet->eValue, "atived"))
		{
			char Chave[4096] = { 0, };
			memset(Chave, 0x0, 4096);
			int valorGerado = rand() % (9991 - 1123 + 1321) + 33;
			std::string s = std::to_string(valorGerado);
			sprintf_s(Chave, 4096, "%s", s.c_str());

			memset(&pUser[clientId].PartyPassword, 0, sizeof(pUser[clientId].PartyPassword));

			strncpy(pUser[clientId].PartyPassword, Chave, 6);
			SendClientPacket(clientId);
			SendEtc(clientId);
			return;
		}

		if (!strcmp(Packet->eValue, "desatived"))
		{
			memset(&pUser[clientId].PartyPassword, 0, sizeof(pUser[clientId].PartyPassword));
			strcpy(pUser[clientId].PartyPassword, "0");
			SendClientPacket(clientId);
			SendEtc(clientId);	
			return;
		}


		return;
	}

	else if (!strcmp(Packet->eCommand, "cp"))
	{
		SendClientMessage(clientId, g_pLanguageString[_NN_CPPoint], GetPKPoint(clientId) - 75);
		return;
	}

	else if (!strcmp(Packet->eCommand, "nt"))
	{
		int value = pMob[clientId].Mobs.PesaEnter;
		if (value <= 0)
			SendClientMessage(clientId, g_pLanguageString[_NN_NT_Zero]);
		else
			SendClientMessage(clientId, g_pLanguageString[_NN_NT_Amount], value);
		return;
	}

	else if (!strcmp(Packet->eCommand, "time"))
	{
		char tmp3[108];

		time_t rawtime;
		struct tm timeinfo;
		rawtime = time(0);
		localtime_s(&timeinfo, &rawtime);

		strftime(tmp3, 80, "%H:%M:%S %d-%m-%Y", &timeinfo);
		SendClientMessage(clientId, "[%s] - %s %dx %dy - Canal %d", pMob[clientId].Mobs.Player.Name, tmp3, pMob[clientId].Target.X, pMob[clientId].Target.Y, sServer.Channel);
		return;
	}

	else if (!strcmp(Packet->eCommand, "guildfame"))
	{
		INT32 gId = pMob[clientId].Mobs.Player.GuildIndex;
		if (gId <= 0)
			return;

		SendClientMessage(clientId, "Você possui um total de %d pontos de fame guild", g_pGuild[gId].Fame);
		return;
	}

	else if (!strcmp(Packet->eCommand, "relo"))
	{
		INT32 userId = GetUserByName(Packet->eValue);
		if (userId <= 0)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Not_Connected]);
			return;
		}

		bool accepted = false;
		if (pMob[clientId].Mobs.Player.ClassInfo != 1)
		{
			if (pUser[userId].SummonedUser == 0)
			{
				SendClientMessage(clientId, "Só pode usar quando convocado pelo grupo ou pelo L�der de Guild");

				return;
			}

			accepted = true;
		}

		if (!pMob[clientId].Mobs.Player.Status.curHP)
		{
			SendClientMessage(clientId, "Você não pode ir até o usuario, pois esta morto.");
			if (accepted)
				pUser[userId].SummonedUser = 0;

			return;
		}

		INT32 leader = pMob[clientId].Leader;
		if (leader == 0)
			leader = clientId;

		bool canMove = false;
		if (leader == userId)
			canMove = true;
		else
		{
			for (INT32 i = 0; i < 12; i++)
			{
				INT32 mobId = pMob[leader].PartyList[i];
				if (mobId <= 0 || mobId >= MAX_PLAYER)
					continue;

				if (mobId == userId)
				{
					canMove = true;

					break;
				}
			}
		}

		INT32 guildIndex = pMob[clientId].Mobs.Player.GuildIndex;
		INT32 userGuild = pMob[userId].Mobs.Player.GuildIndex;

		if (guildIndex != 0 && userGuild != 0 && guildIndex == userGuild)
			canMove = true;

		eMapAttribute map = GetAttribute(pMob[userId].Target.X, pMob[userId].Target.Y);
		if (map.CantSummon)
			canMove = false;

		INT32 slotId = GetFirstSlot(clientId, 699);
		if (slotId == -1)
			slotId = GetFirstSlot(clientId, 776);

		if (slotId == -1)
			slotId = GetFirstSlot(clientId, 3430);

		if (slotId == -1)
			SendClientMessage(clientId, "Necessario Pergaminho Portal para dar relo");
		else
		{
			if (canMove)
			{
				if (slotId != -1)
				{
					AmountMinus(&pMob[clientId].Mobs.Player.Inventory[slotId]);

					SendItem(clientId, SlotType::Inv, slotId, &pMob[clientId].Mobs.Player.Inventory[slotId]);
				}

				Teleportar(clientId, pMob[userId].Target.X, pMob[userId].Target.Y);
				Log(clientId, LOG_INGAME, "Relo no personagem %s %dx %dy", pMob[userId].Mobs.Player.Name, pMob[userId].Target.X, pMob[userId].Target.Y);
			}
			else
				SendClientMessage(clientId, g_pLanguageString[_NN_Cant_Use_That_Here]);
		}
		if (accepted)
			pUser[userId].SummonedUser = 0;
	}

	else if (!strcmp(Packet->eCommand, "registerbattle"))
	{

		auto event = static_cast<TOD_Arena*>(CEventManager::GetInstance().GetEvent(eEventType::Arena));

		if (event == nullptr)
		{
			SendClientMessage(clientId, "Evento associado com este NPC não encontrado");

			return;
		}

		if (!event->CanRegister(*this))
		{
			SendClientMessage(clientId, "Não está na hora da batalha ou está no limite de participantes");

			return;
		}

		const auto& mob = pMob[clientId].Mobs.Player;

		if (event->Register(*this, nullptr))
			SendClientMessage(clientId, "%s, você foi registrado. Total de registros: %u/52", pMob[clientId].Mobs.Player.Name, event->GetTotalRegistered());
		else
			SendClientMessage(clientId,"Você já está registrado, %s", pMob[clientId].Mobs.Player.Name);

		return;
	}

	else if (!strcmp(Packet->eCommand, "summon"))
	{
		INT32 userId = GetUserByName(Packet->eValue);
		if (userId <= 0)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Not_Connected]);

			return;
		}

		if (pMob[clientId].Mobs.Player.ClassInfo != 1 || !(pMob[clientId].Mobs.Player.Learn[0] & 0x40000))
		{
			SendClientMessage(clientId, "Só pode usar quando convocado pelo grupo ou pelo Líder de Guild");

			return;
		}

		p3B2 packet{};

		packet.Header.PacketId = 0x3B2;
		packet.Header.ClientId = 0x7530;

		int len = strlen(pMob[clientId].Mobs.Player.Name);
		if (len >= 12)
			len = 11;
		for (int i = 0; i < len; i++)
			packet.Nickname[i] = pMob[clientId].Mobs.Player.Name[i];

		pUser[userId].AddMessage(reinterpret_cast<BYTE*>(&packet), sizeof p3B2);

		SummonedUser = userId;

		Log(clientId, LOG_INGAME, "Solicitado summon %s", Packet->eValue);
		Log(userId, LOG_INGAME, "Recebido solicitação de summon de %s", Packet->eValue);
		return;
	}

	else if (Packet->eValue[0] == '@' && Packet->eCommand[0] == 0)
	{
		INT32 myKingdom = pMob[clientId].Mobs.Player.CapeInfo;
		INT32 myCitizen = pMob[clientId].Mobs.Citizen;

		strncpy_s(Packet->eCommand, pMob[clientId].Mobs.Player.Name, 12);

		auto last = std::chrono::high_resolution_clock::now() - citizenChatTime;
		if (last <= 5s && AccessLevel == 0)
		{
			SendClientMessage(clientId, "Tempo mínimo para enviar outra mensagem é de 5 segundos.");

			return;
		}

		for (INT32 i = 1; i < MAX_PLAYER; i++)
		{
			if (pUser[i].Status != USER_PLAY || i == clientId)
				continue;

			if (Packet->eValue[1] != '@')
			{
				if (pUser[i].AllStatus.Kingdom)
					continue;

				if (pMob[i].Mobs.Player.CapeInfo == 0 || pMob[i].Mobs.Player.CapeInfo == myKingdom || myKingdom == 0 || pUser[i].AccessLevel != 0)
					pUser[i].AddMessage((BYTE*)Packet, sizeof p334);
			}
			else
			{
				if (pUser[i].AllStatus.Citizen)
					continue;

				if (pMob[i].Mobs.Citizen == myCitizen || pUser[i].AccessLevel != 0)
					pUser[i].AddMessage((BYTE*)Packet, sizeof p334);
			}
		}

		Log(clientId, LOG_INGAME, "Mensagem enviada: %s", Packet->eValue);
		citizenChatTime = std::chrono::high_resolution_clock::now();
	}

	else if (Packet->eValue[0] == '=' && Packet->eCommand[0] == 0)
	{
		INT32 leader = pMob[clientId].Leader;
		if (leader <= 0)
			leader = clientId;

		strncpy_s(Packet->eCommand, pMob[clientId].Mobs.Player.Name, 12);
		for (INT32 i = 0; i < 12; i++)
		{
			INT32 memberId = pMob[leader].PartyList[i];
			if (memberId <= 0 || memberId >= MAX_PLAYER || pUser[memberId].Status != USER_PLAY || pUser[memberId].AllStatus.Chat || clientId == memberId)
				continue;

			pUser[memberId].AddMessage((BYTE*)Packet, sizeof p334);
		}

		if (leader != clientId)
			pUser[leader].AddMessage((BYTE*)Packet, sizeof p334);

		Log(clientId, LOG_INGAME, "Mensagem enviada: %s", Packet->eValue);
	}

	else if ((Packet->eValue[0] == '-' || (Packet->eValue[0] == '-' && Packet->eValue[1] == '-')) && Packet->eCommand[0] == 0)
	{
		INT32 myGuild = pMob[clientId].Mobs.Player.GuildIndex;
		if (!myGuild)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Only_Guild_Member_Can]);

			return;
		}

		strncpy_s(Packet->eCommand, pMob[clientId].Mobs.Player.Name, 12);
		for (INT32 i = 1; i < MAX_PLAYER; i++)
		{
			if (pUser[i].Status != USER_PLAY || i == clientId || pUser[i].AllStatus.Guild)
				continue;

			INT32 ally = g_pGuildAlly[myGuild];
			if (ally == 0)
				ally = -1;

			if (pMob[i].Mobs.Player.GuildIndex == myGuild /*|| pUser[i].IsAdmin*/)
				pUser[i].AddMessage((BYTE*)Packet, sizeof p334);
			else if (pMob[i].Mobs.Player.GuildIndex == ally && Packet->eValue[1] == '-')
				pUser[i].AddMessage((BYTE*)Packet, sizeof p334);
		}

		Log(clientId, LOG_INGAME, "Mensagem enviada: %s", Packet->eValue);
	}

	else if (Packet->eCommand[0] == 'r' && Packet->eCommand[1] == 0)
	{
		INT32 userId = pUser[clientId].LastWhisper;
		if (userId <= 0 || userId >= MAX_PLAYER || pUser[userId].Status != USER_PLAY)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Not_Connected]);

			return;
		}

		if (pUser[userId].AllStatus.Whisper)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Whisper_MP]);

			return;
		}

		if (!Packet->eValue[0])
		{
			if (pMob[userId].Mobs.Player.GuildIndex != 0)
				sprintf_s(szTMP, "%s Fame: %d Guild: %s", pMob[userId].Mobs.Player.Name, pMob[userId].Mobs.Fame, g_pGuild[pMob[userId].Mobs.Player.GuildIndex].Name.c_str());
			else
				sprintf_s(szTMP, "%s Fame: %d", pMob[userId].Mobs.Player.Name, pMob[userId].Mobs.Fame);

			SendClientMessage(clientId, szTMP);

			if (pUser[userId].SNDMessage[0])
				SendClientMessage(clientId, g_pLanguageString[_NN_Message_SND], pUser[userId].SNDMessage);
		}
		else
		{
			pUser[clientId].LastWhisper = userId;
			pUser[userId].LastWhisper = clientId;

			p334 packet;
			memset(&packet, 0, sizeof p334);

			packet.Header.ClientId = userId;
			packet.Header.Size = sizeof p334;
			packet.Header.PacketId = 0x334;

			strncpy_s(packet.eCommand, pMob[clientId].Mobs.Player.Name, 16);
			strncpy_s(packet.eValue, Packet->eValue, 100);

			pUser[userId].AddMessage((BYTE*)&packet, sizeof p334);

			Log(clientId, LOG_INGAME, "Mensagem Privada para: %s: %s", pMob[userId].Mobs.Player.Name, Packet->eValue);
			Log(userId, LOG_INGAME, "Mensagem Privada recebida: %s: %s", pMob[clientId].Mobs.Player.Name, Packet->eValue);

			LogPlayer(clientId, "Mensagem Privada para: %s: %s", pMob[userId].Mobs.Player.Name, Packet->eValue);
			LogPlayer(userId, "Mensagem Privada recebida: %s: %s", pMob[clientId].Mobs.Player.Name, Packet->eValue);

			if (pUser[userId].SNDMessage[0])
				SendClientMessage(clientId, g_pLanguageString[_NN_Message_SND], pUser[userId].SNDMessage);
		
		}
	}
	else
	{
		INT32 userId = GetUserByName(Packet->eCommand);

		if (userId <= 0 || userId >= MAX_PLAYER || pUser[userId].Status != USER_PLAY)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Not_Connected]);

			return;
		}

		if (pUser[userId].AllStatus.Whisper)
		{
			SendClientMessage(clientId, g_pLanguageString[_NN_Whisper_MP]);

			return;
		}

		if (!Packet->eValue[0])
		{
			if (pMob[userId].Mobs.Player.GuildIndex != 0)
			{
				sprintf_s(szTMP, "%s Fame: %d Guild: %s", pMob[userId].Mobs.Player.Name, pMob[userId].Mobs.Fame, g_pGuild[pMob[userId].Mobs.Player.GuildIndex].Name.c_str());
			}
			else
				sprintf_s(szTMP, "%s Fame: %d", pMob[userId].Mobs.Player.Name, pMob[userId].Mobs.Fame);

			if (pMob[userId].Mobs.Player.GuildIndex != 0)
				sprintf_s(szTMP, "Nome: %s /  Fame: %d / Cidanania: %d / Guild: %s", pMob[userId].Mobs.Player.Name, pMob[userId].Mobs.Fame, pMob[userId].Mobs.Citizen, g_pGuild[pMob[userId].Mobs.Player.GuildIndex].Name.c_str());

			else
			{
				sprintf_s(szTMP, "Nome: %s /  Fame: %d / Cidanania: %d", pMob[userId].Mobs.Player.Name, pMob[userId].Mobs.Fame, pMob[userId].Mobs.Citizen);
			}

			SendClientMessage(clientId, szTMP);

			if (pUser[userId].SNDMessage[0])
				SendClientMessage(clientId, g_pLanguageString[_NN_Message_SND], pUser[userId].SNDMessage);
		}
		else
		{
			pUser[clientId].LastWhisper = userId;
			pUser[userId].LastWhisper = clientId;

			p334 packet;
			memset(&packet, 0, sizeof p334);

			packet.Header.ClientId = userId;
			packet.Header.Size = sizeof p334;
			packet.Header.PacketId = 0x334;

			strncpy_s(packet.eCommand, pMob[clientId].Mobs.Player.Name, 16);
			strncpy_s(packet.eValue, Packet->eValue, 100);

			pUser[userId].AddMessage((BYTE*)&packet, sizeof p334);

			Log(clientId, LOG_INGAME, "Mensagem Privada para: %s: %s", pMob[userId].Mobs.Player.Name, Packet->eValue);
			Log(userId, LOG_INGAME, "Mensagem Privada recebida: %s: %s", pMob[clientId].Mobs.Player.Name, Packet->eValue);

			LogPlayer(clientId, "Mensagem privada para %s: %s", pMob[userId].Mobs.Player.Name, Packet->eValue);
			LogPlayer(userId, "Mensagem Privada recebida: %s: %s", pMob[clientId].Mobs.Player.Name, Packet->eValue);

			if (pUser[userId].SNDMessage[0])
				SendClientMessage(clientId, g_pLanguageString[_NN_Message_SND], pUser[userId].SNDMessage);
		}
	}

	return;
}
