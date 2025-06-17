#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "CNPCGener.h"

bool CUser::RequestDeleteChar(PacketHeader* header)
{
	p211 *p = (p211*)(header);
	p->Name[15] = '\0';
	p->Pwd[11] = '\0';

	STRUCT_MOB* mob = &pMob[clientId].Mobs.Player;
	if (Status != USER_SELCHAR)
	{
		SendClientMessage(clientId, "Deleting Character, wait a moment");

		Log(clientId, LOG_HACK, "Tentativa de deletar personagem enquanto não na CharList. Status atual: %d", Status);
		return true;
	}

	/*time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (rawtime < (pMob[clientId].Mobs.LastGuildKickOut.GetTMStruct() + 7200))
	{
		int rtime = (int)((7200 - (rawtime - pMob[clientId].Mobs.LastGuildKickOut.GetTMStruct())) / 60 / 60);
		int rmin = (int)((7200 - (rawtime - pMob[clientId].Mobs.LastGuildKickOut.GetTMStruct())) / 60 - (rtime * 60));

		char temp[4096];
		sprintf(temp, "Deve aguardar {%d} horas e {%d} minuto(s) para apagar o personagem.", rtime, rmin);
		SendClientMessage(clientId, temp);
		return true;
	}*/

	//std::time_t rawnow = std::time(nullptr);
	//struct tm now; localtime_s(&now, &rawnow);
	//auto now_time_t = std::mktime(&now);
	//auto diffTime = std::difftime(now_time_t, pMob[clientId].Mobs.LastGuildKickOut.GetTMStruct());

	//int totalSeconds = (KickOutPenalty - (int)diffTime);
	//int hours = (totalSeconds / 3600) % 24;
	//int days = (totalSeconds / 3600) / 24;
	//int mins = (totalSeconds % 3600) / 60;
	//int seconds = totalSeconds % 60;

	//if (diffTime < KickOutPenalty && diffTime != 0.0)
	//{
	//	SendClientMessage(clientId, "Você deve aguardar %02d horas %02d minutos %02d segundos para apagar o personagem.", hours, mins, seconds);
	//	return true;
	//}

	for (int i = 1; i < 15; i++)
	{
		if (mob->Equip[i].Index <= 0 || mob->Equip[i].Index >= MAX_ITEMLIST)
			continue;

		SendClientMessage(clientId, "Desequipe todos os itens do personagem para excluir");
		return true;
	}

	if (pMob[clientId].Mobs.Player.Gold != 0)
	{
		SendClientMessage(clientId, "Não é possível excluir enquanto possuir gold no inventario");
		return true;
	}

	Log(clientId, LOG_INGAME, "Solicitado deletar personagem %s", p->Name);

	Status = USER_DELWAIT;

	header->PacketId = 0x809;
	return AddMessageDB((BYTE*)header, sizeof p211);
}