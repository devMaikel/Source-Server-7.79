#pragma once

#include <array>
#include <vector>
#include "cEvent.h"
#include "Basedef.h"

constexpr int MaxGroups = 4;
constexpr int MinimumParticipants = 4;

constexpr std::array<const char*, 4> GroupsName = {
	"Mestre",
	"Caçador",
	"Assasino",
	"Legendary"
};

class CUser;

enum class TOD_Arena_Status
{
	Disabled,
	WaitingToStart,
	Enabled,
	WaitingToDisable
};

class TOD_Arena : public CEventItem
{
	struct InternalArena
	{
		CUser* User;
		bool IsParticipant;
	};
public:
	TOD_Arena(std::chrono::milliseconds interval)
		: CEventItem(interval)
	{
	}

	virtual void Work();
	virtual bool CanRegister(CUser& user);
	virtual bool Register(CUser& user, STRUCT_ITEM* item);
	virtual void Unregister(CUser& user);

	size_t GetTotalRegistered() const
	{
		return _registeredUsers.size();
	}

	bool MobKilled(int killed, int killer);
private:
	int _pointsToWin{ 0 };

	TOD_Arena_Status _status{ TOD_Arena_Status::Disabled };
	std::chrono::time_point<std::chrono::steady_clock> _startTime;
	std::chrono::time_point<std::chrono::steady_clock> _lastMessage;
	std::array<std::vector<InternalArena>, MaxGroups> _groups;
	std::vector<CUser*> _registeredUsers;

	bool StartArena();
	/*bool IsOnHour() const;*/
	const int IsOnHour();

	std::array<int, MaxGroups> GetPoints() const;

	bool IsUserValid(const InternalArena& user) const;

	void GiveReward(int groupIndex);
	void GiveReward(CUser* user, const ArenaReward& reward);

	void RefreshScoreboard() const;
	void CheckForWinner();
	void DecideWinner();
	void Reset();

	bool ReadHoursAllowed();
};