/* #pragma once

#include "SDK.h"

IClientEntity* LocalPlayer;

#define TICK_INTERVAL			(Interfaces::Globals->interval_per_tick)
#define TIME_TO_TICKS2( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

int IClientEntity::GetSequenceActivity(int sequence)
{
	auto hdr = Interfaces::ModelInfo->GetStudiomodel(this->GetModel());

	if (!hdr)
		return -1;

	static auto getSequenceActivity = (DWORD)(Utilities::Memory::FindPatternV2("client.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74"));
	static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(getSequenceActivity);

	return GetSequenceActivity(this, hdr, sequence);
}

bool isPartOf(char *a, char *b) {
	if (std::strstr(b, a) != NULL) {    
		return true;
	}
	return false;
}

class CResolver {
public:
	void AntiAimCorrection();
	void AntiAimResolver(CUserCmd * pCmd);
private:
	bool IsFakeWalking();
};

struct ResolverData
{
	float simtime, flcycle[13], flprevcycle[13], flweight[13], flweightdatarate[13], fakewalkdetection[2], fakeanglesimtimedetection[2], fakewalkdetectionsimtime[2];
	float yaw, addyaw, lbycurtime;
	float shotsimtime, oldlby, lastmovinglby, balanceadjustsimtime, balanceadjustflcycle;
	int fakeanglesimtickdetectionaverage[4], amountgreaterthan2, amountequal1or2, amountequal0or1, amountequal1, amountequal0, resetmovetick, resetmovetick2;
	int tick, balanceadjusttick, missedshots, activity[13];
	bool bfakeangle, bfakewalk, playerhurtcalled, weaponfirecalled;
	Vector shotaimangles, hitboxPos, balanceadjustaimangles;
	uint32_t norder[13];
	char* resolvermode = "NONE", *fakewalk = "Not Moving";
};

extern ResolverData pResolverData[64];
extern CResolver* Resolver;

void CResolver::AntiAimResolver(CUserCmd *pCmd)
{
	IClientEntity* pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	player_info_t info{};
	if (!pLocal->IsAlive())
		return;

	for (int i = 0; i < Interfaces::Engine->GetMaxClients(); i++)
	{
		auto pEntity = Interfaces::EntList->GetClientEntity(i);

		if (!pEntity || !pLocal)
			continue;

		if (pEntity == pLocal)
			continue;

		if (Interfaces::Engine->GetPlayerInfo(i, &info))
			continue;

		if (pEntity->IsDormant())
			continue;

		if (pEntity->GetTeam() == pLocal->GetTeam())
			continue;

		if (pEntity->IsAlive())
		{
			if (pResolverData[i].addyaw > 135.f)
				pResolverData[i].addyaw = 0.f;

			if (pResolverData[LocalPlayer->GetIndex()].weaponfirecalled)
			{
				if (!pResolverData[pEntity->GetIndex()].playerhurtcalled)
				{
					if (isPartOf("Brute", pResolverData[i].resolvermode))
					{
						pResolverData[i].addyaw += 45.f;
					}
				}
				else
					pResolverData[i].playerhurtcalled = false;
				pResolverData[LocalPlayer->GetIndex()].weaponfirecalled = false;
			}

			for (int w = 0; w < 13; w++)
			{
				AnimationLayer currentLayer = pEntity->GetAnimOverlay(w);
				const int activity = pEntity->GetSequenceActivity(currentLayer.m_nSequence);
				float flcycle = currentLayer.m_flCycle, flprevcycle = currentLayer.m_flPrevCycle, flweight = currentLayer.m_flWeight, flweightdatarate = currentLayer.m_flWeightDeltaRate;
				uint32_t norder = currentLayer.m_nOrder;
				Vector* pAngles = pEntity->GetEyeAnglesPointer();

				if (norder == 12)
				{
					pResolverData[pEntity->GetIndex()].fakewalkdetection[pCmd->command_number % 2] = flweight;
					pResolverData[pEntity->GetIndex()].fakewalkdetectionsimtime[pCmd->command_number % 2] = pEntity->GetSimulationTime();
					for (int t = 0; t < 2; t++)
					{
						int resetmovetick2{};
						if (pResolverData[pEntity->GetIndex()].fakewalkdetection[t] > 0.f)
							pResolverData[pEntity->GetIndex()].resetmovetick = t;
						else if (t == 1)
						{
							if (pEntity->GetVecVelocity().Length2D() < 0.50 && flweight == 0.f)
							{
								pResolverData[pEntity->GetIndex()].fakewalk = "Not Moving";
								pResolverData[pEntity->GetIndex()].bfakewalk = false;
							}
						}
						else {
							if (pResolverData[pEntity->GetIndex()].resetmovetick > 0)
								resetmovetick2 = pResolverData[pEntity->GetIndex()].resetmovetick - 1;
							else
								resetmovetick2 = pResolverData[pEntity->GetIndex()].resetmovetick + 1;

							if (pResolverData[pEntity->GetIndex()].fakewalkdetection[resetmovetick2] == 0.f)
							{
								pResolverData[pEntity->GetIndex()].fakewalk = "Fake Walking";
								pResolverData[pEntity->GetIndex()].bfakewalk = true;
							}
						}
					}
				}

				if (pEntity->GetVecVelocity().Length2D() >= 0.50 && norder == 6 && flweight >= 0.550000 || pEntity->GetVecVelocity().Length2D() >= 0.50 && norder == 5 && flweight >= 0.550000 || !pResolverData[pEntity->GetIndex()].bfakewalk && pEntity->GetVecVelocity().Length2D() >= 0.50)
				{

				}
				else
				{
					if (activity == ACT_CSGO_IDLE_TURN_BALANCEADJUST && flweight >= 0.05f)
					{
						pResolverData[pEntity->GetIndex()].resolvermode = "Less BA Brute";
						pResolverData[pEntity->GetIndex()].addyaw > 0.f;
					}
					else if (activity == ACT_CSGO_IDLE_ADJUST_STOPPEDMOVING || activity == ACT_CSGO_IDLE_TURN_BALANCEADJUST && flweight == 0.f && flcycle >= 0.970000)
					{
						pResolverData[pEntity->GetIndex()].resolvermode = "LBY Brute";
						pResolverData[pEntity->GetIndex()].addyaw > 0.f;
					}
				}
				GameUtils::NormaliseViewAngle(*pAngles);
			}
		}
	}
}

ResolverData pResolverData[64];
CResolver* Resolver; */