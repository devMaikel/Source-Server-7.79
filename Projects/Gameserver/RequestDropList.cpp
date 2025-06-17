#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include "GetFunc.h"


void SendDropList(int conn)
{
	if (conn <= 0 || conn >= MAX_PLAYER)
		return;

	pUser[conn].LastTimeRequestDrop = CurrentTime;

	auto player = &pMob[conn];

	if (player == NULL)
		return;

	p2568 Packet;
	memset(&Packet, 0, sizeof(Packet));

	auto Mobs = GetMobInArea(pMob[conn].Target.X - 25, pMob[conn].Target.Y - 25, pMob[conn].Target.X + 25, pMob[conn].Target.Y + 25);
	if (Mobs.size() > 0)
	{
		for (auto& i : Mobs)
		{

			if (pMob[i].Mobs.Player.Status.Merchant.Merchant != 0)
				continue;

			if (Packet.amount == 10)
				break;

			auto exists = false;

			for (int x = 0; x < Packet.amount; x++)
			{
				if (!strcmp(Packet.Drop[x].name, pMob[i].Mobs.Player.Name))
				{
					exists = true;
					break;
				}
			}
			if (exists)
				continue;

			strcpy(Packet.Drop[Packet.amount].name, pMob[i].Mobs.Player.Name);

			Packet.Drop[Packet.amount].X = pMob[i].Target.X;
			Packet.Drop[Packet.amount].Y = pMob[i].Target.Y;

			Packet.Drop[Packet.amount].exp = (int)pMob[i].Mobs.Player.Exp;
			Packet.Drop[Packet.amount].gold = pMob[i].Mobs.Player.Gold;

			for (int a = 0; a < 64; a++)
				memcpy(&Packet.Drop[Packet.amount].carry[a], &pMob[i].Mobs.Player.Inventory[a], sizeof(STRUCT_ITEM));

			Packet.amount++;
		}
	}

	Packet.Header.Size = sizeof(p2568);
	Packet.Header.PacketId = 2568;
	Packet.Header.ClientId = conn;

	pUser[conn].AddMessage((BYTE*)&Packet, sizeof p2568);
	pUser[conn].SendMessageA();
}