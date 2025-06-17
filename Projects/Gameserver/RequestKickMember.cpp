#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"

bool CUser::RequestKickMember(PacketHeader *Header)
{
	pMsgSignal *p = (pMsgSignal*)(Header);

	INT32 userId = p->Value;
	if(userId <= 0 || userId >= MAX_PLAYER)
		return false;

	INT32 memberType = pMob[clientId].Mobs.Player.GuildMemberType;
	if(memberType != 9 && (memberType < 3 || memberType > 9))
	{
		SendClientMessage(clientId, g_pLanguageString[_NN_Guild_CantKick_Guild]);

		return true;
	}

	INT32 guildIndex = pMob[clientId].Mobs.Player.GuildIndex;
	if(guildIndex != pMob[userId].Mobs.Player.GuildIndex)
	{
		SendClientMessage(clientId, g_pLanguageString[_NN_Guild_CantKick_Guild]);

		return true;
	}
	
	// Somente l�der ou comandante pode excluir o cidad�o caso ele seja subl�der
	INT32 userType = pMob[userId].Mobs.Player.GuildMemberType;
	if(userType >= 3 && userType <= 5 && memberType != 9)// && memberType != 6)
	{
		SendClientMessage(clientId, g_pLanguageString[_NN_Guild_CantKick_Guild]);

		return true;
	}

	if(userType >= 3 && userType <= 5)
	{
		// Remove a medalha da estrutura dos subs
		g_pGuild[guildIndex].SubGuild[pMob[userId].Mobs.Player.GuildMemberType - 3][0] = 0;

		// Retira da DBSrv e do restante dos canais
		MSG_ADDSUB packet;
		packet.Header.PacketId = MSG_ADDSUB_OPCODE;
		packet.Header.Size = sizeof MSG_ADDSUB;
		
		packet.GuildIndex = guildIndex;
		packet.Status = 1;
		packet.SubIndex = pMob[userId].Mobs.Player.GuildMemberType - 3;

		AddMessageDB((BYTE*)&packet, sizeof MSG_ADDSUB);
	}

	Log(clientId, LOG_GUILD, "Expulsou o usuario %s da guild", pMob[userId].Mobs.Player.Name);
	Log(userId  , LOG_GUILD, "Foi expuslo da guild por %s (%d) (%d)", pMob[clientId].Mobs.Player.Name, guildIndex, pMob[userId].Mobs.Player.GuildMemberType);

	LogPlayer(clientId, "Expulsou o usuario %s da guild", pMob[userId].Mobs.Player.Name);
	LogPlayer(userId,   "Voc� foi expulso da guild %s por %s", pMob[clientId].Mobs.Player.Name, g_pGuild[guildIndex].Name.c_str());

	std::time_t rawnow = std::time(nullptr);
	struct tm now; localtime_s(&now, &rawnow);

	auto& lastKick = pMob[userId].Mobs.LastGuildKickOut;
	lastKick.Ano = 1900 + now.tm_year;
	lastKick.Mes = now.tm_mon + 1;
	lastKick.Dia = now.tm_mday;
	lastKick.Hora = now.tm_hour;
	lastKick.Minuto = now.tm_min;
	lastKick.Segundo = now.tm_sec;

	pMob[userId].Mobs.Player.GuildIndex = 0;
	pMob[userId].Mobs.Player.GuildMemberType = 0;

	p364 packet;
	GetCreateMob(userId, (BYTE*)&packet);

	GridMulticast_2(pMob[userId].Target.X, pMob[userId].Target.Y, (BYTE*)&packet, 0);
	
	SendClientMessage(userId, g_pLanguageString[_NN_Guild_Kicked]);
	SendClientMessage(clientId, g_pLanguageString[_NN_Guild_Kicked]); 

	return true;
}