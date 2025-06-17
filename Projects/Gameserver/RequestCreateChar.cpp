#include "cServer.h"
#include "Basedef.h"

bool CUser::RequestCreateChar(PacketHeader *Header)
{
	p20F *p = (p20F*)Header;

	// Faz as checagens de segurança, somente após isto
	// É feito as checagens de índice invalido

	if (p->ClassID < 0 || p->ClassID > 3)
		return false;

	if (p->SlotID < 0 || p->SlotID > 3)
		return false;

	// BUG Da própria TMsrv
	// Checagem se o usuario esta logado
	// Caso não esteja, ele retorna falso pois não é possível criar personagem ingame.
	if(Status != USER_SELCHAR)
		return false;



	// Null character
	p->Nick[12] = '\0';

	p->Header.PacketId = 0x802;

	AddMessageDB((BYTE*)Header, sizeof p20F);

	//std::time_t rawnow = std::time(nullptr);
	//struct tm now; localtime_s(&now, &rawnow);

	//auto& lastKick = pMob[clientId].Mobs.LastGuildKickOut;
	//lastKick.Ano = 1900 + now.tm_year;
	//lastKick.Mes = now.tm_mon + 1;
	//lastKick.Dia = now.tm_mday;
	//lastKick.Hora = now.tm_hour;
	//lastKick.Minuto = now.tm_min;
	//lastKick.Segundo = now.tm_sec;

	// Seta como quem esta criando um personagem
	Status = USER_CREWAIT;


	return true;
}