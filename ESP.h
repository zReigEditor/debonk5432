/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "Hacks.h"

class CEsp : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:

	// Other shit

	struct ESPBox
	{
		int x, y, w, h;
	};

	// Draw a player
	void DrawPlayer(IClientEntity* pEntity, player_info_t pinfo);

	// Get player info
	Color GetPlayerColor(IClientEntity* pEntity);
	bool GetBox(IClientEntity* pEntity, ESPBox &result);

	// Draw shit about player
	void SpecList();
	void DrawGlow(IClientEntity *pEntity, int r, int g, int b, int a);
	void DrawBox(ESPBox size, Color color);
	void DrawName(player_info_t pinfo, ESPBox size);
	void DrawMoney(IClientEntity * pEntity, CEsp::ESPBox size);
	void Barrel(CEsp::ESPBox size, Color color, IClientEntity * pEntity);
	void DrawHealth(ESPBox box, IClientEntity* pEntity);
	void Armor(ESPBox box, IClientEntity* pEntity);
	void BacktrackingCross(IClientEntity * pEntity);
	void DrawInfo(IClientEntity* pEntity, ESPBox size);
	void DrawGlow();
	void DrawCross(IClientEntity* pEntity);
	void DrawSkeleton(IClientEntity* pEntity);

	void BulletTrace(IClientEntity * pEntity, Color color);

	void DrawChicken(IClientEntity* pEntity, ClientClass* cClass);
	void DrawDrop(IClientEntity* pEntity, ClientClass* cClass);
	void WallBangIndicator();
	void DrawBombPlanted(IClientEntity* pEntity, ClientClass* cClass);
	void DrawBomb(IClientEntity* pEntity, ClientClass* cClass);
};


void DiLight();