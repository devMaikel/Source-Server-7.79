#include "cServer.h"
#include "Basedef.h"
#include "SendFunc.h"
#include <fcntl.h>
#include <io.h>
#include "CThreadTranslator.h"

void BuyItem(int clientId, int type, int page, int slot)
{
	if (clientId <= 0 || clientId >= 1000)
		return;

	if (type < 0 || type > 3)
		return;

	if (page < 0 || page > 3)
		return;

	if (slot < 1 || slot > 12)
		return;


	if (pUser[clientId].Status != 22)
		return;

	for (auto& i : ControlDonateLoja)
	{
		if (i.type != type)
			continue;

		if (i.page != page)
			continue;

		if (i.slot != slot)
			continue;

		if (pUser[clientId].User.Cash < (uint32_t)i.price)
		{
			SendClientMessage(clientId, "Você não possui o valor para realizar essa compra.");
			return;
		}

		if (i.stuck < 1)
		{
			SendClientMessage(clientId, "Acabou o estoque do produto.");
			return;
		}

		/*	if (Func::ReturnSlotEmpty(clientId, SlotType::Storage) == -1)
			{
				Native::SendClientMessage(clientId, "Você não possui espaço no seu Guarda Carga.");
				return;
			}*/


		i.stuck--;
		int DonateValor = (pUser[clientId].User.Cash - i.price);
		pUser[clientId].User.Cash = DonateValor;

		STRUCT_ITEM* item = &i.item;

		PutItem(clientId, &i.item);

		SendClientMessage(clientId, "O item %s chegou no seu inventário.", ItemList[item->Index].Name);
		SendClientPacket(clientId);
		SendEtc(clientId);
		SendLojaDonate(clientId, type, page, slot);
		return;
	}
}

void SendLojaDonate(int clientId, int Type, int Page, int Slot)
{
	struct {
		PacketHeader Header;

		int type;

		int page;

		STRUCT_ITEM item;

		int price;

		int stuck;

		int slot;

	} Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	auto item = ControlDonateLoja;

	Packet.Header.Size = sizeof(Packet);
	Packet.Header.PacketId = 0xAA1;


	for (auto& i : ControlDonateLoja)
	{
		if (i.type != Type)
			continue;

		if (i.page != Page)
			continue;

		if (i.slot != Slot)
			continue;

		Packet.type = i.type;
		Packet.page = i.page;
		Packet.price = i.price;
		Packet.stuck = i.stuck;
		Packet.slot = i.slot;
		memcpy_s(&Packet.item, sizeof(STRUCT_ITEM), &i.item, sizeof(STRUCT_ITEM));
		break;
	}

	for (int i = 0; i < 1000; i++)
	{
		Packet.Header.ClientId = i;
		pUser[i].AddMessage((BYTE*)&Packet, sizeof(Packet));
		pUser[i].SendMessageA();
	}
}

void SendLojaDonate(int clientId)
{
	struct {
		PacketHeader Header;

		int quantidade;

		struct
		{
			int type;

			int page;

			STRUCT_ITEM item;

			int price;

			int stuck;

			int slot;
		}Produts[231];

	} Packet;

	memset(&Packet, 0x0, sizeof(Packet));

	auto item = ControlDonateLoja;

	Packet.Header.Size = sizeof(Packet);
	Packet.Header.PacketId = 0xAA2;
	Packet.Header.ClientId = 0x7530;
	Packet.quantidade = ControlDonateLoja.size();

	int Total = 0;
	for (auto& i : ControlDonateLoja)
	{
		if (Total > 230)
			break;


		Packet.Produts[Total].type = i.type;
		Packet.Produts[Total].page = i.page;
		Packet.Produts[Total].price = i.price;
		Packet.Produts[Total].stuck = i.stuck;
		Packet.Produts[Total].slot = i.slot;

		memcpy_s(&Packet.Produts[Total].item, sizeof(STRUCT_ITEM), &i.item, sizeof(STRUCT_ITEM));

		Total++;
	}

	pUser[clientId].AddMessage((BYTE*)&Packet, sizeof(Packet));
	pUser[clientId].SendMessageA();
}

void SendClientPacket(int clientId)
{
	struct stSendInfoClient
	{
		PacketHeader Header;
		int ExpBonus;
		int DropBonus;
		int AbsDamage;
		int PerfuDamage;
		int Cash;
		char Password[12];
		int UsersRegistres;
	};

	if (clientId <= 0 || clientId >= 1000)
		return;

	stSendInfoClient packet;
	memset(&packet, 0, sizeof stSendInfoClient);

	packet.Header.PacketId = 0x2132;
	packet.Header.ClientId = clientId;
	packet.Header.Size = sizeof stSendInfoClient;

	packet.ExpBonus = pMob[clientId].ExpBonus;
	packet.DropBonus = pMob[clientId].DropBonus;
	packet.AbsDamage = pMob[clientId].ReflectDamage;
	packet.PerfuDamage = pMob[clientId].ForceDamage;

	packet.Cash = pUser[clientId].User.Cash;
	sprintf_s(packet.Password, 8, "%s", pUser[clientId].PartyPassword);
	packet.UsersRegistres = pUser[clientId].Arena.UsersRegistres;


	pUser[clientId].AddMessage((BYTE*)&packet, sizeof stSendInfoClient);
}