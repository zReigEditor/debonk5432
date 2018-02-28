#include "Menu.h"
#include "Controls.h"
#include "Hooks.h" 
#include "Interfaces.h"
#include "CRC32.h"

#define WINDOW_WIDTH 535
#define WINDOW_HEIGHT 430

AyyWareWindow Menu::Window;

void SaveCallbk()
{
	switch (Menu::Window.ConfigBox.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&Menu::Window, "ReigWareLegit.cfg");
		break;
	case 1:
		GUI.SaveWindowState(&Menu::Window, "ReigWareLegit2.cfg");
		break;
	case 2:
		GUI.SaveWindowState(&Menu::Window, "ReigWareRage.cfg");
		break;
	case 3:
		GUI.SaveWindowState(&Menu::Window, "ReigWareRage2.cfg");
		break;
	case 4:
		GUI.SaveWindowState(&Menu::Window, "ReigWareHvH.cfg");
		break;
	case 5:
		GUI.SaveWindowState(&Menu::Window, "ReigWareHvH2.cfg");
		break;
	}
}

void LoadCallbk()
{
	switch (Menu::Window.ConfigBox.GetIndex())
	{
	case 0:
		GUI.LoadWindowState(&Menu::Window, "ReigWareLegit.cfg");
		break;
	case 1:
		GUI.LoadWindowState(&Menu::Window, "ReigWareLegit2.cfg");
		break;
	case 2:
		GUI.LoadWindowState(&Menu::Window, "ReigWareRage.cfg");
		break;
	case 3:
		GUI.LoadWindowState(&Menu::Window, "ReigWareRage2.cfg");
		break;
	case 4:
		GUI.LoadWindowState(&Menu::Window, "ReigWareHvH.cfg");
		break;
	case 5:
		GUI.LoadWindowState(&Menu::Window, "ReigWareHvH2.cfg");
		break;
	}
}

void UnLoadCallbk()
{
	Hooks::UndoHooks();
}

void KnifeApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");
	bGlovesNeedUpdate = true;
}

void GlovesApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");
	bGlovesNeedUpdate = true;
}

void AyyWareWindow::Setup()
{
	SetPosition(350, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("ReigWare");

	RegisterTab(&RageBotTab);
	RegisterTab(&LegitBotTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);
	RegisterTab(&SkinchangerTab);
//	RegisterTab(&Playerlist);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	RageBotTab.Setup();
	LegitBotTab.Setup();
	VisualsTab.Setup();
	MiscTab.Setup();
	SkinchangerTab.Setup();
//	Playerlist.Setup();
#pragma region Bottom Buttons
	ConfigBox.SetFileId("cfg_box");
	ConfigBox.AddItem("Legit");
	ConfigBox.AddItem("Legit 2");
	ConfigBox.AddItem("Rage");
	ConfigBox.AddItem("Rage 2");
	ConfigBox.AddItem("HvH");
	ConfigBox.AddItem("HvH 2");
	ConfigBox.SetSize(112, 350);
	ConfigBox.SetPosition(405, Client.bottom - 510);

	SaveButton.SetText("Save");
	SaveButton.SetCallback(SaveCallbk);
	SaveButton.SetSize(112, 350);
	SaveButton.SetPosition(405, Client.bottom - 480);

	LoadButton.SetText("Load");
	LoadButton.SetCallback(LoadCallbk);
	LoadButton.SetSize(112, 350);
	LoadButton.SetPosition(405, Client.bottom - 450);

	UnloadButton.SetText("Uninject");
	UnloadButton.SetCallback(UnLoadCallbk);
	UnloadButton.SetSize(112, 350);
	UnloadButton.SetPosition(405, Client.bottom - 420);

	MiscTab.RegisterControl(&LoadButton);

	MiscTab.RegisterControl(&SaveButton);

	MiscTab.RegisterControl(&ConfigBox);

	MiscTab.RegisterControl(&UnloadButton);
#pragma endregion Setting up the settings buttons
}

void CRageBotTab::Setup()
{
	SetTitle("RAGE");

//	ActiveLabel.SetPosition(26, 16);
//	ActiveLabel.SetText("Active");
//	RegisterControl(&ActiveLabel);

//	Active.SetFileId("active");
//	Active.SetPosition(70, 18);
//	RegisterControl(&Active);

#pragma region Aimbot

	AimbotGroup.SetPosition(16, 11);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(270, 377); 
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable aimbot", this, &AimbotEnable);

	TargetSelection.SetFileId("tgt_selection");
//	TargetSelection.AddItem("Target by crosshair");
	TargetSelection.AddItem("Target by distance");
	TargetSelection.AddItem("Target by health");
	TargetSelection.AddItem("Target by threat");
	TargetSelection.AddItem("Target by next shot");
	AimbotGroup.PlaceLabledControl("", this, &TargetSelection);

//	TargetFriendlyFire.SetFileId("tgt_friendlyfire");
//	AimbotGroup.PlaceLabledControl("Friendly fire", this, &TargetFriendlyFire);

	TargetHitbox.SetFileId("tgt_hitbox");
	TargetHitbox.AddItem("Hitbox on head");
	TargetHitbox.AddItem("Hitbox on neck");
	TargetHitbox.AddItem("Hitbox on chest");
	TargetHitbox.AddItem("Hitbox on stomach");
	TargetHitbox.AddItem("Hitbox on legs");
	AimbotGroup.PlaceLabledControl("", this, &TargetHitbox);

	TargetMultipoint.SetFileId("tgt_multipoint");
	AimbotGroup.PlaceLabledControl("Multi point", this, &TargetMultipoint);

	TargetPointscale.SetFileId("tgt_pointscale");
	TargetPointscale.SetBoundaries(0.f, 10.f);
	TargetPointscale.SetValue(5.f);
	AimbotGroup.PlaceLabledControl("Scale", this, &TargetPointscale);

	TargetHitscan.SetFileId("tgt_hitscan");
	TargetHitscan.AddItem("Hitscan off");
	TargetHitscan.AddItem("Hitscan low");
	TargetHitscan.AddItem("Hitscan medium");
	TargetHitscan.AddItem("Hitscan high");
	AimbotGroup.PlaceLabledControl("", this, &TargetHitscan);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("Automatic firing", this, &AimbotAutoFire);

	AccuracyAutoWall.SetFileId("acc_awall");
	AimbotGroup.PlaceLabledControl("Automatic penetration", this, &AccuracyAutoWall);

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotGroup.PlaceLabledControl("Silent aim", this, &AimbotSilentAim);

//	AimbotMinimumHitchance.SetFileId("aim_minhitchance");
//	AimbotGroup.PlaceLabledControl("Minimum hit chance", this, &AimbotMinimumHitchance);

	AccuracyHitchance.SetFileId("acc_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(0);
	AimbotGroup.PlaceLabledControl("Hit chance", this, &AccuracyHitchance);

//	Meme.SetFileId("acc_meme");
//	Meme.SetBoundaries(0, 100);
//	Meme.SetValue(0);
//	AimbotGroup.PlaceLabledControl("Hit chance precision", this, &Meme);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0, 180);
	AimbotFov.SetValue(1);
	AimbotGroup.PlaceLabledControl("Maximum FOV", this, &AimbotFov);

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(0, 99);
	AccuracyMinimumDamage.SetValue(1);
	AimbotGroup.PlaceLabledControl("Minimum penetration", this, &AccuracyMinimumDamage);

	AutoRevolver.SetFileId("aim_autorevolver");
	AimbotGroup.PlaceLabledControl("Automatic revolver", this, &AutoRevolver);

//	AimbotAimStep.SetFileId("aim_aimstep");
//	AimbotGroup.PlaceLabledControl("Reduced aim step", this, &AimbotAimStep);

	AccuracyAutoScope.SetFileId("acc_scope");
	AimbotGroup.PlaceLabledControl("Automatic scoping", this, &AccuracyAutoScope);

	OtherAimbotDebug.SetFileId("acc_fakepingmen");
	AimbotGroup.PlaceLabledControl("Backtracking exploit", this, &OtherAimbotDebug);

	BaimKey.SetFileId("acc_polakwaremode");
	AimbotGroup.PlaceLabledControl("Body aim on key", this, &BaimKey);

	Baimiflethal.SetFileId("acc_anotheraimwaremode");
	AimbotGroup.PlaceLabledControl("Body aim if lethal", this, &Baimiflethal);

//	PreferBodyAim.SetFileId("acc_aimwaremode");
//	AimbotGroup.PlaceLabledControl("Adaptive baim", this, &PreferBodyAim);

//	AccuracyBacktracking.SetFileId("acc_becctrecc");
//	AimbotGroup.PlaceLabledControl("Backtracking", this, &AccuracyBacktracking);
#pragma endregion Aimbot Controls Get Setup in here

/* #pragma region Keklag
	KeklagGroup.SetPosition(16, 333);
	KeklagGroup.SetText("Fake lag");
	KeklagGroup.SetSize(270, 55);
	RegisterControl(&KeklagGroup);

	FakeLagEnable.SetFileId("fakelag_enable");
	KeklagGroup.PlaceLabledControl("Enable fake lag", this, &FakeLagEnable);

	FakeLagChoke.SetFileId("fakelag_choke");
	FakeLagChoke.SetBoundaries(0, 16);
	FakeLagChoke.SetValue(0);
	KeklagGroup.PlaceLabledControl("Factor", this, &FakeLagChoke);
#pragma endregion Keklag */

#pragma region Target
	TargetGroup.SetPosition(300, 11);
	TargetGroup.SetText("Other");
	TargetGroup.SetSize(216, 183);
	RegisterControl(&TargetGroup);

	PVSFix.SetFileId("tgt_pvsfix");
	TargetGroup.PlaceLabledControl("PVS fix", this, &PVSFix);

	EnginePrediction.SetFileId("tgt_enginepred");
	TargetGroup.PlaceLabledControl("Engine prediction", this, &EnginePrediction);

	AccuracyRecoil.SetFileId("acc_norecoil");
	TargetGroup.PlaceLabledControl("Recoil correction", this, &AccuracyRecoil);

	AccuracyPositionAdjustment.SetFileId("acc_posadj");
	TargetGroup.PlaceLabledControl("Position adjustment", this, &AccuracyPositionAdjustment);

	LowerbodyFix.SetFileId("acc_lowerbodyfix");
	TargetGroup.PlaceLabledControl("LBY correction", this, &LowerbodyFix);

	AdvancedResolver.SetFileId("acc_advancedresolver");
	TargetGroup.PlaceLabledControl("Pitch correction", this, &AdvancedResolver);

	AimbotResolver.SetFileId("acc_resilver");
	AimbotResolver.AddItem("Off");
	AimbotResolver.AddItem("On");
	TargetGroup.PlaceLabledControl("Resolver", this, &AimbotResolver);

	AccuracyResolver2.SetFileId("acc_fag");
	TargetGroup.PlaceLabledControl("Fake walk correction", this, &AccuracyResolver2);
#pragma endregion Targetting controls 

/* #pragma region Accuracy
	AccuracyGroup.SetPosition(408, 11);
	AccuracyGroup.SetText("Accuracy");
	AccuracyGroup.SetSize(360, 270);
	RegisterControl(&AccuracyGroup);

	AccuracyRecoil.SetFileId("acc_norecoil");
	AccuracyGroup.PlaceLabledControl("Remove Recoil", this, &AccuracyRecoil);

	AccuracyAutoWall.SetFileId("acc_awall");
	AccuracyGroup.PlaceLabledControl("Auto Wall", this, &AccuracyAutoWall);

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(1.f, 99.f);
	AccuracyMinimumDamage.SetValue(1.f);
	AccuracyGroup.PlaceLabledControl("Autowall Damage", this, &AccuracyMinimumDamage);

	AccuracyAutoScope.SetFileId("acc_scope");
	AccuracyGroup.PlaceLabledControl("Auto Scope", this, &AccuracyAutoScope);

	AccuracyPositionAdjustment.SetFileId("acc_posadj");
	AccuracyGroup.PlaceLabledControl("Position Adjustment", this, &AccuracyPositionAdjustment);

	LowerbodyFix.SetFileId("acc_lowerbodyfix");
	AccuracyGroup.PlaceLabledControl("LBY Correction", this, &LowerbodyFix);

	AdvancedResolver.SetFileId("acc_advancedresolver");
	AccuracyGroup.PlaceLabledControl("Pitch Correction", this, &AdvancedResolver);

	AimbotResolver.SetFileId("acc_aaa");
	AimbotResolver.AddItem("Off");
	AimbotResolver.AddItem("Level 1");
	AimbotResolver.AddItem("Level 2");
	AimbotResolver.AddItem("Level 3");
	AccuracyGroup.PlaceLabledControl("Resolver", this, &AimbotResolver);

	ResolverDebug.SetFileId("acc_debugresolver");
	AccuracyGroup.PlaceLabledControl("Resolver debug", this, &ResolverDebug);

	AccuracyHitchance.SetFileId("acc_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(0);
	AccuracyGroup.PlaceLabledControl("Hit Chance", this, &AccuracyHitchance);

	BaimIfUnderXHealth.SetFileId("acc_BaimIfUnderXHealth");
	BaimIfUnderXHealth.SetBoundaries(0, 100);
	BaimIfUnderXHealth.SetValue(0);
	AccuracyGroup.PlaceLabledControl("Body-Aim if HP is lower than X", this, &BaimIfUnderXHealth);

	PreferBodyAim.SetFileId("acc_preferbaim");
	AccuracyGroup.PlaceLabledControl("Prefer Body-Aim", this, &PreferBodyAim);
#pragma endregion  Accuracy controls get Setup in here */

#pragma region AntiAim
	AntiAimGroup.SetPosition(300, 209);
	AntiAimGroup.SetText("Anti aim");
	AntiAimGroup.SetSize(216, 179);
	RegisterControl(&AntiAimGroup);

	AntiAimEnable.SetFileId("aa_enable");
	AntiAimGroup.PlaceLabledControl("Enable anti aim", this, &AntiAimEnable);

/*	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("Off");		// 0
	AntiAimPitch.AddItem("Halfdown");	// 1
	AntiAimPitch.AddItem("Jitter");		// 2
	AntiAimPitch.AddItem("Emotion");	// 3
	AntiAimPitch.AddItem("Up");			// 4
	AntiAimPitch.AddItem("Zero");		// 5
	AntiAimPitch.AddItem("Custom");		// 6
	AntiAimGroup.PlaceLabledControl("Pitch", this, &AntiAimPitch); */

	AntiAimYaw.SetFileId("aa_y");
	AntiAimYaw.AddItem("Off");
//	AntiAimYaw.AddItem("Fast Spin");
//	AntiAimYaw.AddItem("Slow Spin");
	AntiAimYaw.AddItem("Jitter");
//	AntiAimYaw.AddItem("180 Jitter");
	AntiAimYaw.AddItem("Backwards");
//	AntiAimYaw.AddItem("Backwards Jitter");
//	AntiAimYaw.AddItem("Sideways Switch");
	AntiAimYaw.AddItem("Sideways");
//	AntiAimYaw.AddItem("Sideways Left");
	AntiAimYaw.AddItem("LBY");
//	AntiAimYaw.AddItem("LBY Jitter");
//	AntiAimYaw.AddItem("LBY Sideways");
//	AntiAimYaw.AddItem("LBY Spin");
//	AntiAimYaw.AddItem("LBY Break");
//	AntiAimYaw.AddItem("Side jitter (test)");
	AntiAimGroup.PlaceLabledControl("Real yaw", this, &AntiAimYaw);

	FakeYaw.SetFileId("fakeaa");
	FakeYaw.AddItem("Off");
//	FakeYaw.AddItem("Fast Spin");
//	FakeYaw.AddItem("Slow Spin");
	FakeYaw.AddItem("Jitter");
//	FakeYaw.AddItem("180 Jitter");
	FakeYaw.AddItem("Backwards");
//	FakeYaw.AddItem("Backwards Jitter");
//	FakeYaw.AddItem("Sideways Switch");
//	FakeYaw.AddItem("Sideways Right");
	FakeYaw.AddItem("Sideways");
	FakeYaw.AddItem("LBY");
//	FakeYaw.AddItem("Fake Jitter");
//	FakeYaw.AddItem("LBY Sideways");
//	FakeYaw.AddItem("LBY Spin");
//	FakeYaw.AddItem("LBY Break");
//	FakeYaw.AddItem("Side jitter (test)");
	AntiAimGroup.PlaceLabledControl("Fake yaw", this, &FakeYaw);

//	AntiAimKnife.SetFileId("aa_knife");
//	AntiAimGroup.PlaceLabledControl("Anti aim on knife", this, &AntiAimKnife);

//	AntiAimTarget.SetFileId("aa_target");
//	AntiAimGroup.PlaceLabledControl("Player adjustment", this, &AntiAimTarget);

	BreakLBY.SetFileId("aa_break");
	BreakLBY.AddItem("Off");
	BreakLBY.AddItem("45�");
	BreakLBY.AddItem("90�");
	BreakLBY.AddItem("180�");
	AntiAimGroup.PlaceLabledControl("LBY breaker", this, &BreakLBY);

	ManualAA.SetFileId("aa_manualaa");
	AntiAimGroup.PlaceLabledControl("Manual sideways", this, &ManualAA);

	OtherFakeWalk.SetFileId("otr_fakewalk");
	AntiAimGroup.PlaceLabledControl("Fake walk", this, &OtherFakeWalk);
#pragma endregion  AntiAim controls get setup in here
}
void CLegitBotTab::Setup()
{
	SetTitle("LEGIT");

//	ActiveLabel.SetPosition(20, 16);
//	ActiveLabel.SetText("Active");
//	RegisterControl(&ActiveLabel);

//	Active.SetFileId("active");
//	Active.SetPosition(70, 18);
//	RegisterControl(&Active);

#pragma region Aimbot
	AimbotGroup.SetPosition(16, 11);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(240, 145);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable aimbot", this, &AimbotEnable);

//	AimbotAutoFire.SetFileId("aim_autofire");
//	AimbotGroup.PlaceLabledControl("Automatic firing", this, &AimbotAutoFire);

//	AimbotFriendlyFire.SetFileId("aim_friendfire");
//	AimbotGroup.PlaceLabledControl("Friendly fire", this, &AimbotFriendlyFire);

//	AimbotSmokeCheck.SetFileId("otr_smokecheck");
//	AimbotGroup.PlaceLabledControl("Smoke check", this, &AimbotSmokeCheck);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("On key", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("Key", this, &AimbotKeyBind);

	AimbotBacktrack.SetFileId("legit_backtrack");
	AimbotGroup.PlaceLabledControl("Backtracking", this, &AimbotBacktrack);

//	TickModulation.SetFileId("tick_modulate");
//	TickModulation.SetBoundaries(0.1f, 13.f);
	TickModulation.SetValue(13.f);
//	AimbotGroup.PlaceLabledControl("Ticks", this, &TickModulation);
#pragma endregion Aimbot shit

#pragma region Triggerbot
	TriggerGroup.SetPosition(272, 11);
	TriggerGroup.SetText("Triggerbot");
	TriggerGroup.SetSize(244, 145);
	RegisterControl(&TriggerGroup);

	TriggerEnable.SetFileId("trig_enable");
	TriggerGroup.PlaceLabledControl("Enable triggerbot", this, &TriggerEnable);

	TriggerKeyPress.SetFileId("trig_onkey");
	TriggerGroup.PlaceLabledControl("On key", this, &TriggerKeyPress);

	TriggerKeyBind.SetFileId("trig_key");
	TriggerGroup.PlaceLabledControl("Key", this, &TriggerKeyBind);

//	OtherxGodWalk.SetFileId("trig_moonwalk");
//	TriggerGroup.PlaceLabledControl("Legit anti aim", this, &OtherxGodWalk);

#pragma endregion TriggerbotFilter stuff

#pragma region Main Weapon
	WeaponMainGroup.SetPosition(16, 168);
	WeaponMainGroup.SetText("Rifles");
	WeaponMainGroup.SetSize(240, 105);
	RegisterControl(&WeaponMainGroup);

	WeaponMainHitbox.SetFileId("main_hitbox");
	WeaponMainHitbox.AddItem("Head");
	WeaponMainHitbox.AddItem("Neck");
	WeaponMainHitbox.AddItem("Chest");
	WeaponMainHitbox.AddItem("Stomach");
//	WeaponMainHitbox.AddItem("Closest");
	WeaponMainGroup.PlaceLabledControl("Hitbox", this, &WeaponMainHitbox);

	WeaponMainSpeed.SetFileId("main_speed");
	WeaponMainSpeed.SetBoundaries(0.f, 100.f);
	WeaponMainSpeed.SetValue(1.f);
	WeaponMainGroup.PlaceLabledControl("Speed", this, &WeaponMainSpeed);

	WeaponMainFoV.SetFileId("main_fov");
	WeaponMainFoV.SetBoundaries(0.f, 30.f);
	WeaponMainFoV.SetValue(3.5f);
	WeaponMainGroup.PlaceLabledControl("Field of view", this, &WeaponMainFoV);

	WeaponMainRecoil.SetFileId("main_recoil");
	WeaponMainRecoil.SetBoundaries(0.f, 2.f);
	WeaponMainRecoil.SetValue(1.f);
	WeaponMainGroup.PlaceLabledControl("Rcs", this, &WeaponMainRecoil);

	WeaponMainAimtime.SetValue(0);
	WeaoponMainStartAimtime.SetValue(0);

#pragma endregion

#pragma region Pistols
	WeaponPistGroup.SetPosition(272, 168);
	WeaponPistGroup.SetText("Pistols");
	WeaponPistGroup.SetSize(244, 105);
	RegisterControl(&WeaponPistGroup);

	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("Head");
	WeaponPistHitbox.AddItem("Neck");
	WeaponPistHitbox.AddItem("Chest");
	WeaponPistHitbox.AddItem("Stomach");
	//WeaponPistHitbox.AddItem("Closest");
	WeaponPistGroup.PlaceLabledControl("Hitbox", this, &WeaponPistHitbox);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.f, 100.f);
	WeaponPistSpeed.SetValue(1.0f);
	WeaponPistGroup.PlaceLabledControl("Speed", this, &WeaponPistSpeed);

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.f, 30.f);
	WeaponPistFoV.SetValue(3.f);
	WeaponPistGroup.PlaceLabledControl("Field of View", this, &WeaponPistFoV);

	WeaponPistRecoil.SetFileId("pist_recoil");
	WeaponPistRecoil.SetBoundaries(0.f, 2.f);
	WeaponPistRecoil.SetValue(1.f);
	WeaponPistGroup.PlaceLabledControl("Rcs", this, &WeaponPistRecoil);

	WeaponPistAimtime.SetValue(0);
	WeaoponPistStartAimtime.SetValue(0);

#pragma endregion

 #pragma region Snipers
	WeaponSnipGroup.SetPosition(272, 283);
	WeaponSnipGroup.SetText("Snipers");
	WeaponSnipGroup.SetSize(244, 105);
	RegisterControl(&WeaponSnipGroup);

	WeaponSnipHitbox.SetFileId("snip_hitbox");
	WeaponSnipHitbox.AddItem("Head");
	WeaponSnipHitbox.AddItem("Neck");
	WeaponSnipHitbox.AddItem("Chest");
	WeaponSnipHitbox.AddItem("Stomach");
//	WeaponSnipHitbox.AddItem("Closest");
	WeaponSnipGroup.PlaceLabledControl("Hitbox", this, &WeaponSnipHitbox);

	WeaponSnipSpeed.SetFileId("snip_speed");
	WeaponSnipSpeed.SetBoundaries(0.f, 100.f);
	WeaponSnipSpeed.SetValue(1.5f);
	WeaponSnipGroup.PlaceLabledControl("Speed", this, &WeaponSnipSpeed);

	WeaponSnipFoV.SetFileId("snip_fov");
	WeaponSnipFoV.SetBoundaries(0.f, 30.f);
	WeaponSnipFoV.SetValue(2.f);
	WeaponSnipGroup.PlaceLabledControl("Field of View", this, &WeaponSnipFoV);

	WeaponSnipRecoil.SetFileId("snip_recoil");
	WeaponSnipRecoil.SetBoundaries(0.f, 2.f);
	WeaponSnipRecoil.SetValue(1.f);
	WeaponSnipGroup.PlaceLabledControl("Rcs", this, &WeaponSnipRecoil);

	WeaponSnipAimtime.SetValue(0);
	WeaoponSnipStartAimtime.SetValue(0);

#pragma region MPs
	WeaponMpGroup.SetPosition(16, 283);
	WeaponMpGroup.SetText("SMGs");
	WeaponMpGroup.SetSize(240, 105);
	RegisterControl(&WeaponMpGroup);

	WeaponMpHitbox.SetFileId("mps_hitbox");
	WeaponMpHitbox.AddItem("Head");
	WeaponMpHitbox.AddItem("Neck");
	WeaponMpHitbox.AddItem("Chest");
	WeaponMpHitbox.AddItem("Stomach");
	//WeaponMpHitbox.AddItem("Closest");
	WeaponMpGroup.PlaceLabledControl("Hitbox", this, &WeaponMpHitbox);

	WeaponMpSpeed.SetFileId("mps_speed");
	WeaponMpSpeed.SetBoundaries(0.f, 100.f);
	WeaponMpSpeed.SetValue(1.0f);
	WeaponMpGroup.PlaceLabledControl("Speed", this, &WeaponMpSpeed);

	WeaponMpFoV.SetFileId("mps_fov");
	WeaponMpFoV.SetBoundaries(0.f, 30.f);
	WeaponMpFoV.SetValue(4.f);
	WeaponMpGroup.PlaceLabledControl("Field of View", this, &WeaponMpFoV);

	WeaponMpRecoil.SetFileId("mps_recoil");
	WeaponMpRecoil.SetBoundaries(0.f, 2.f);
	WeaponMpRecoil.SetValue(1.f);
	WeaponMpGroup.PlaceLabledControl("Rcs", this, &WeaponMpRecoil);

	WeaponMpAimtime.SetValue(0);
	WeaoponMpStartAimtime.SetValue(0);
#pragma endregion

/* #pragma region Shotguns
	WeaponShotgunGroup.SetPosition(272, 365);
	WeaponShotgunGroup.SetText("Shotguns");
	WeaponShotgunGroup.SetSize(240, 136);
	RegisterControl(&WeaponShotgunGroup);

	WeaponShotgunHitbox.SetFileId("shotgun_hitbox");
	WeaponShotgunHitbox.AddItem("Head");
	WeaponShotgunHitbox.AddItem("Neck");
	WeaponShotgunHitbox.AddItem("Chest");
	WeaponShotgunHitbox.AddItem("Stomach");
	WeaponShotgunHitbox.AddItem("Multihitbox");
	WeaponShotgunGroup.PlaceLabledControl("Hitbox", this, &WeaponShotgunHitbox);

	WeaponShotgunSpeed.SetFileId("shotgun_speed");
	WeaponShotgunSpeed.SetBoundaries(0.f, 100.f);
	WeaponShotgunSpeed.SetValue(1.0f);
	WeaponShotgunGroup.PlaceLabledControl("Max Speed", this, &WeaponShotgunSpeed);

	WeaponShotgunFoV.SetFileId("shotgun_fov");
	WeaponShotgunFoV.SetBoundaries(0.f, 30.f);
	WeaponShotgunFoV.SetValue(3.f);
	WeaponShotgunGroup.PlaceLabledControl("Field of View", this, &WeaponShotgunFoV);

	WeaponShotgunRecoil.SetFileId("snip_recoil");
	WeaponShotgunRecoil.SetBoundaries(0.f, 2.f);
	WeaponShotgunRecoil.SetValue(1.f);
	WeaponShotgunGroup.PlaceLabledControl("Recoil Control", this, &WeaponShotgunRecoil);

	WeaponShotgunAimtime.SetValue(0);
	WeaoponShotgunStartAimtime.SetValue(0);

#pragma endregion

#pragma region Machineguns
	WeaponMGGroup.SetPosition(528, 365);
	WeaponMGGroup.SetText("Heavy");
	WeaponMGGroup.SetSize(240, 136);
	RegisterControl(&WeaponMGGroup);

	WeaponMGHitbox.SetFileId("mg_hitbox");
	WeaponMGHitbox.AddItem("Head");
	WeaponMGHitbox.AddItem("Neck");
	WeaponMGHitbox.AddItem("Chest");
	WeaponMGHitbox.AddItem("Stomach");
	WeaponMGHitbox.AddItem("Multihitbox");
	WeaponMGGroup.PlaceLabledControl("Hitbox", this, &WeaponMGHitbox);

	WeaponMGSpeed.SetFileId("mg_speed");
	WeaponMGSpeed.SetBoundaries(0.f, 100.f);
	WeaponMGSpeed.SetValue(1.0f);
	WeaponMGGroup.PlaceLabledControl("Max Speed", this, &WeaponMGSpeed);

	WeaponMGFoV.SetFileId("mg_fov");
	WeaponMGFoV.SetBoundaries(0.f, 30.f);
	WeaponMGFoV.SetValue(4.f);
	WeaponMGGroup.PlaceLabledControl("Field of View", this, &WeaponMGFoV);

	WeaponMGRecoil.SetFileId("mg_recoil");
	WeaponMGRecoil.SetBoundaries(0.f, 2.f);
	WeaponMGRecoil.SetValue(1.f);
	WeaponMGGroup.PlaceLabledControl("Recoil Control", this, &WeaponMGRecoil);

	WeaponMGAimtime.SetValue(0);
	WeaoponMGStartAimtime.SetValue(0);

#pragma endregion*/
}

void CVisualTab::Setup()
{
	SetTitle("ESP");

//	ActiveLabel.SetPosition(16, 16);
//	ActiveLabel.SetText("Active");
//	RegisterControl(&ActiveLabel);

//	Active.SetFileId("active");
//	Active.SetPosition(66, 16);
//	RegisterControl(&Active);

#pragma region Options
	OptionsGroup.SetText("Player");
	OptionsGroup.SetPosition(16, 11);
	OptionsGroup.SetSize(240, 377);
	RegisterControl(&OptionsGroup);

	Box.SetFileId("opt_boxerino");
	OptionsGroup.PlaceLabledControl("Box", this, &Box);

//	OptionsBox.SetFileId("opt_box");
//	OptionsBox.AddItem("Off");
//	OptionsBox.AddItem("Cornered");
//	OptionsBox.AddItem("Full");
//	OptionsGroup.PlaceLabledControl("Box", this, &OptionsBox);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	OptionsGroup.PlaceLabledControl("Enemies only", this, &FiltersEnemiesOnly);

//	FiltersWeapons.SetFileId("ftr_weaps");
//	OptionsGroup.PlaceLabledControl("Dropped weapons", this, &FiltersWeapons);

//	FiltersC4.SetFileId("ftr_c4");
//	OptionsGroup.PlaceLabledControl("Bomb", this, &FiltersC4);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl("Name", this, &OptionsName);

	OptionsHealth.SetFileId("opt_hp");
	OptionsGroup.PlaceLabledControl("Health", this, &OptionsHealth);

//	OptionsArmor.SetFileId("opt_armor");
//	OptionsGroup.PlaceLabledControl("Armor", this, &OptionsArmor);

//	OptionsMoney.SetFileId("opt_money");
//	OptionsGroup.PlaceLabledControl("Money", this, &OptionsMoney);

	OptionsWeapon.SetFileId("opt_weapon");
	OptionsGroup.PlaceLabledControl("Weapon", this, &OptionsWeapon);
	
//	OptionsBarrels.SetFileId("opt_barrels");
//	OptionsGroup.PlaceLabledControl("Trace Lines", this, &OptionsBarrels);

	OtherHitmarker.SetFileId("otr_hitmarker");
	OptionsGroup.PlaceLabledControl("Hitmarker", this, &OtherHitmarker);

	HitmarkerSound.SetFileId("otr_hitmarkersound");
	OptionsGroup.PlaceLabledControl("Hitmarker sound", this, &HitmarkerSound);

	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl("Info", this, &OptionsInfo);

	Chams.SetFileId("opt_chamerinos");
	OptionsGroup.PlaceLabledControl("Chams", this, &Chams);

	WallHaxChams.SetFileId("opt_wallhaxchamerinos");
	OptionsGroup.PlaceLabledControl("Wallhack chams", this, &WallHaxChams);

//	sceneend.SetFileId("gaytest");
//	OptionsGroup.PlaceLabledControl("SceneEnd chams", this, &sceneend);

//	OptionsChams.SetFileId("opt_chams");
//	OptionsChams.AddItem("Off");
//	OptionsChams.AddItem("Textured");
//	OptionsChams.AddItem("Flat");
//	OptionsGroup.PlaceLabledControl("Legit chams", this, &OptionsChams);

	Glow.SetFileId("opt_glowerino");
	OptionsGroup.PlaceLabledControl("Glow", this, &Glow);

//	OptionsGlow.SetFileId("opt_glow");
//	OptionsGlow.AddItem("Off");
//	OptionsGlow.AddItem("On");
//	OptionsGroup.PlaceLabledControl("Glow", this, &OptionsGlow);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl("Skeleton", this, &OptionsSkeleton);

	AngleChams.SetFileId("opt_aimware");
	OptionsGroup.PlaceLabledControl("Ghost fake angle chams", this, &AngleChams);

//	Logs.SetFileId("opt_eventlog");
//	OptionsGroup.PlaceLabledControl("Event log", this, &Logs);

//	BacktrackingLol.SetFileId("opt_meme");
//	OptionsGroup.PlaceLabledControl("Show backtrack ticks", this, &BacktrackingLol);

//	OptionsCompRank.SetFileId("opt_comprank");
//	OptionsGroup.PlaceLabledControl("Comp Rank", this, &OptionsCompRank);

	lbyidicador.SetFileId("opt_lbymemey");
	OptionsGroup.PlaceLabledControl("LBY indicator", this, &lbyidicador);

	BacktrackingLol.SetFileId("opt_idkwhatImDoing");
	OptionsGroup.PlaceLabledControl("Visualize backtracking", this, &BacktrackingLol);

	OtherSpreadCrosshair.SetFileId("opt_spreadcrosshair");
	OptionsGroup.PlaceLabledControl("Spread crosshair", this, &OtherSpreadCrosshair);

	WallbangIndicator.SetFileId("opt_anal");
	OptionsGroup.PlaceLabledControl("Automatic penetration indicator", this, &WallbangIndicator);

	bullettrace.SetFileId("opt_asnruo");
	OptionsGroup.PlaceLabledControl("Bullet impacts", this, &bullettrace);

//	BulletTraceLength.SetFileId("ayylmao");
//	BulletTraceLength.SetBoundaries(0.f, 100.f);
//	OptionsGroup.PlaceLabledControl("Bullet tracers", this, &BulletTraceLength);
//	LeftHandKnife.SetFileId("gayshizzle");
//	OptionsGroup.PlaceLabledControl("Knife in left hand", this, &LeftHandKnife);
#pragma endregion Setting up the Options controls

/* #pragma region Filters
	FiltersGroup.SetText("Filters");
	FiltersGroup.SetPosition(225, 48);
	FiltersGroup.SetSize(193, 430);
	RegisterControl(&FiltersGroup);

	FiltersAll.SetFileId("ftr_all");
	FiltersGroup.PlaceLabledControl("All", this, &FiltersAll);

	FiltersPlayers.SetFileId("ftr_players");
	FiltersGroup.PlaceLabledControl("Players", this, &FiltersPlayers);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	FiltersGroup.PlaceLabledControl("Enemies Only", this, &FiltersEnemiesOnly);

	FiltersWeapons.SetFileId("ftr_weaps");
	FiltersGroup.PlaceLabledControl("Weapons", this, &FiltersWeapons);

	FiltersC4.SetFileId("ftr_c4");
	FiltersGroup.PlaceLabledControl("C4", this, &FiltersC4);
#pragma endregion Setting up the Filters controls */

#pragma region Other
	OtherGroup.SetText("World");
	OtherGroup.SetPosition(266, 11);
	OtherGroup.SetSize(250, 377);
	RegisterControl(&OtherGroup);

/*	OtherCrosshair.SetFileId("otr_crosshair");
	OtherCrosshair.AddItem("Off");
	OtherCrosshair.AddItem("Recoil");
	OtherCrosshair.AddItem("Spread");
	OtherGroup.PlaceLabledControl("Override Crosshair", this, &OtherCrosshair);

	OtherNoHands.SetFileId("otr_hands");
	OtherNoHands.AddItem("Off");
	OtherNoHands.AddItem("None");
	OtherNoHands.AddItem("Transparent");
	OtherNoHands.AddItem("Chams");
	OtherNoHands.AddItem("Rainbow");
	OtherGroup.PlaceLabledControl("Hands", this, &OtherNoHands); */

	SniperCrosshair.SetFileId("otr_snipercrosshair");
	OtherGroup.PlaceLabledControl("Crosshair on sniper", this, &SniperCrosshair);

//	NightSky.SetFileId("otr_nightsky");
//	OtherGroup.PlaceLabledControl("Night Sky", this, &NightSky);

	FiltersWeapons.SetFileId("ftr_weaps");
	OtherGroup.PlaceLabledControl("Dropped weapons", this, &FiltersWeapons);

	FiltersC4.SetFileId("ftr_c4");
	OtherGroup.PlaceLabledControl("Bomb", this, &FiltersC4);

	DisablePostProcess.SetFileId("otr_disablepostprocess");
	OtherGroup.PlaceLabledControl("Disable post processing", this, &DisablePostProcess);

	OtherNoFlash.SetFileId("otr_noflash");
	OtherGroup.PlaceLabledControl("Remove flash", this, &OtherNoFlash);

	OtherNoSmoke.SetFileId("otr_nosmoke");
	OtherGroup.PlaceLabledControl("Remove smoke", this, &OtherNoSmoke);

	OtherNoScope.SetFileId("otr_noscope");
	OtherGroup.PlaceLabledControl("Remove scope", this, &OtherNoScope);

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	OtherGroup.PlaceLabledControl("Remove visual recoil", this, &OtherNoVisualRecoil);

//	Clock.SetFileId("otr_clock");
//	OtherGroup.PlaceLabledControl("Hours", this, &Clock);

//	Watermark.SetFileId("otr_watermarker");
//	OtherGroup.PlaceLabledControl("Watermark", this, &Watermark);

	OtherRadar.SetFileId("otr_radar");
	OtherGroup.PlaceLabledControl("Radar", this, &OtherRadar);

	OtherSpectators.SetFileId("otr_speclist");
	OtherGroup.PlaceLabledControl("Spectators list", this, &OtherSpectators);

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(0.f, 180.f);
	OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl("Viewmodel FOV", this, &OtherViewmodelFOV);

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(90.f);
	OtherGroup.PlaceLabledControl("Field of View", this, &OtherFOV);

	NightMod.SetFileId("night_amm");
	NightMod.SetBoundaries(0.f, .3f);
	NightMod.SetValue(.1f);
	OtherGroup.PlaceLabledControl("Night mode amount", this, &NightMod);

	OtherNightMode.SetFileId("otr_nightsky");
	OtherGroup.PlaceLabledControl("Update night mode", this, &OtherNightMode);

	AsusWalls.SetFileId("otr_asuswalls");
	AsusWalls.SetBoundaries(0.f, 1.f);
	AsusWalls.SetValue(1.f);
	OtherGroup.PlaceLabledControl("Asus walls", this, &AsusWalls);

	AsusProps.SetFileId("otr_asusprops");
	AsusProps.SetBoundaries(0.f, 1.f);
	AsusProps.SetValue(1.f);
	OtherGroup.PlaceLabledControl("Asus props", this, &AsusProps);

	UpdateAsusWalls.SetFileId("otr_updateasus");
	OtherGroup.PlaceLabledControl("Update asus walls", this, &UpdateAsusWalls);

	UpdateAsusProps.SetFileId("otr_updateasusprops");
	OtherGroup.PlaceLabledControl("Update asus props", this, &UpdateAsusProps);

/*	AmbientRed.SetFileId("otr_ambientred");
	AmbientRed.SetBoundaries(0.f, 10.f);
	AmbientRed.SetValue(0.f);
	OtherGroup.PlaceLabledControl("Ambient Red", this, &AmbientRed);

	AmbientGreen.SetFileId("otr_ambientgreen");
	AmbientGreen.SetBoundaries(0.f, 10.f);
	AmbientGreen.SetValue(0.f);
	OtherGroup.PlaceLabledControl("Ambient Green", this, &AmbientGreen);

	AmbientBlue.SetFileId("otr_ambientblue");
	AmbientBlue.SetBoundaries(0.f, 10.f);
	AmbientBlue.SetValue(0.f);
	OtherGroup.PlaceLabledControl("Ambient Blue", this, &AmbientBlue); */

#pragma endregion Setting up the Other controls
}

void CMiscTab::Setup()
{
	SetTitle("MISC");

#pragma region Other
	OtherGroup.SetPosition(16, 11);
	OtherGroup.SetSize(276, 227);
	OtherGroup.SetText("Misc");
	RegisterControl(&OtherGroup);

#pragma region GloveModel
	Gloves.SetPosition(16, 250);
	Gloves.SetText("Glovechanger");
	Gloves.SetSize(276, 110);
	RegisterControl(&Gloves);

	EnableGloves.SetFileId("gloves_enable");
	Gloves.PlaceLabledControl("Enable glovechanger", this, &EnableGloves);

	GloveModel.SetFileId("glove_model");
	GloveModel.AddItem("Off");
	GloveModel.AddItem("Bloodhound");
	GloveModel.AddItem("Handwrap");
	GloveModel.AddItem("Driver");
	GloveModel.AddItem("Sport");
	GloveModel.AddItem("Motorcycle");
	GloveModel.AddItem("Specialist");
	Gloves.PlaceLabledControl("Glove Model", this, &GloveModel);

	GloveSkin.SetFileId("glove_skin");
	GloveSkin.AddItem("Off");
	GloveSkin.AddItem("Bloodhound - Snakebite");
	GloveSkin.AddItem("Bloodhound - Charred");
	GloveSkin.AddItem("Bloodhound - Guerrilla");
	GloveSkin.AddItem("Bloodhound - Bronzed");
	GloveSkin.AddItem("Handwrap - Slaughter");
	GloveSkin.AddItem("Handwrap - Badlands");
	GloveSkin.AddItem("Handwrap - Leather");
	GloveSkin.AddItem("Handwrap - Spruce DDPAT");
	GloveSkin.AddItem("Driver - Crimson Weave");
	GloveSkin.AddItem("Driver - Lunar Weave");
	GloveSkin.AddItem("Driver - Diamondback");
	GloveSkin.AddItem("Driver - Convoy");
	GloveSkin.AddItem("Sport - Pandoras Box");
	GloveSkin.AddItem("Sport - Hedge Naze");
	GloveSkin.AddItem("Sport - Superconductor");
	GloveSkin.AddItem("Sport - Arid");
	GloveSkin.AddItem("Motorcycle - Spearmint");
	GloveSkin.AddItem("Motorcycle - Cool Mint");
	GloveSkin.AddItem("Motorcycle - Boom");
	GloveSkin.AddItem("Motorcycle - Eclipse");
	GloveSkin.AddItem("Specialist - Crimson Kimono");
	GloveSkin.AddItem("Specialist - Emerald Web");
	GloveSkin.AddItem("Specialist - Foundation");
	GloveSkin.AddItem("Specialist - Forest DDPAT");
	Gloves.PlaceLabledControl("Glove Skin", this, &GloveSkin);

	GlovesApply.SetText("Apply Gloves");
	GlovesApply.SetCallback(GlovesApplyCallbk);
	GlovesApply.SetPosition(16, 365);//400, 480
	GlovesApply.SetSize(276, 520);
	RegisterControl(&GlovesApply);

#pragma endregion

#pragma region Knife
	KnifeGroup.SetPosition(300, 11);
	KnifeGroup.SetText("Knifechanger");
	KnifeGroup.SetSize(216, 80);
	RegisterControl(&KnifeGroup);

	KnifeModel.SetFileId("knife_model");
	KnifeModel.AddItem("Bayonet");
	KnifeModel.AddItem("Bowie Knife");
	KnifeModel.AddItem("Butterfly Knife");
	KnifeModel.AddItem("Falchion Knife");
	KnifeModel.AddItem("Flip Knife");
	KnifeModel.AddItem("Gut Knife");
	KnifeModel.AddItem("Huntsman Knife");
	KnifeModel.AddItem("Karambit");
	KnifeModel.AddItem("M9 Bayonet");
	KnifeModel.AddItem("Shadow Daggers");
	KnifeGroup.PlaceLabledControl("Knife", this, &KnifeModel);

	KnifeSkin.SetFileId("knife_skin");
	KnifeGroup.PlaceLabledControl("Skin ID", this, &KnifeSkin);

	SkinApply.SetText("Apply knife");
	SkinApply.SetCallback(KnifeApplyCallbk);
	SkinApply.SetPosition(300, 97);
	SkinApply.SetSize(216, 106);
	RegisterControl(&SkinApply);
#pragma endregion

//	OtherAutoJump.SetFileId("otr_autojump");
//	OtherAutoJump.AddItem("Off");
//	OtherAutoJump.AddItem("On");
//	OtherGroup.PlaceLabledControl("Bunnyhop", this, &OtherAutoJump);

	Bhop.SetFileId("otr_bhop");
	OtherGroup.PlaceLabledControl("Bunnyhop", this, &Bhop);

	AutoStrafe.SetFileId("otr_autostrafe");
	OtherGroup.PlaceLabledControl("Auto strafe", this, &AutoStrafe);

//	OtherEdgeJump.SetFileId("otr_edgejump");
//	OtherGroup.PlaceLabledControl("Edge Jump", this, &OtherEdgeJump);

//	OtherAutoStrafe.SetFileId("otr_strafe");
//	OtherAutoStrafe.AddItem("Off");
//	OtherAutoStrafe.AddItem("Legit");
//	OtherAutoStrafe.AddItem("Rage");
//	OtherGroup.PlaceLabledControl("Auto strafe", this, &OtherAutoStrafe);

//	OtherSafeMode.SetFileId("otr_safemode");
//	OtherSafeMode.SetState(true);
//	OtherGroup.PlaceLabledControl("Anti untrusted", this, &OtherSafeMode);

//	OtherChatSpam.SetFileId("otr_spam");
//	OtherChatSpam.AddItem("Off");
//	OtherChatSpam.AddItem("Name steal");
//	OtherChatSpam.AddItem("Chat spam");
//	OtherChatSpam.AddItem("Name spam");
//	OtherChatSpam.AddItem("Remove name");
//	OtherGroup.PlaceLabledControl("Spammers", this, &OtherChatSpam);

//	TrashTalk.SetFileId("otr_trashtalk");
//	OtherGroup.PlaceLabledControl("ChatSpam Kill", this, &TrashTalk);

	Clantag.SetFileId("otr_clantag");
	OtherGroup.PlaceLabledControl("ReigWare clantag", this, &Clantag);

	OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.SetState(true);
	OtherGroup.PlaceLabledControl("Anti untrusted", this, &OtherSafeMode);

//	OtherClantag.SetFileId("otr_spam");
//	OtherClantag.AddItem("Off");
//	OtherClantag.AddItem("Petite 1");
//	OtherClantag.AddItem("Petite 2");
//	OtherClantag.AddItem("Valve");
//	OtherClantag.AddItem("Hours");
//	OtherGroup.PlaceLabledControl("Custom clantag", this, &OtherClantag);

//	OtherTeamChat.SetFileId("otr_teamchat");
//	OtherGroup.PlaceLabledControl("Team Chat Only", this, &OtherTeamChat);

//	OtherChatDelay.SetFileId("otr_chatdelay");
//	OtherChatDelay.SetBoundaries(0.1, 3.0);
//	OtherChatDelay.SetValue(1.0);
//	OtherGroup.PlaceLabledControl("Spam delay", this, &OtherChatDelay);

//	OtherAirStuck.SetFileId("otr_astuck");
//	OtherGroup.PlaceLabledControl("Air Stuck", this, &OtherAirStuck);

//	OtherSpectators.SetFileId("otr_speclist");
//	OtherGroup.PlaceLabledControl("Spectators list", this, &OtherSpectators);

	tpkey.SetFileId("otr_tpkey");
	OtherGroup.PlaceLabledControl("Third person", this, &tpkey);

//	legitaa.SetFileId("otr_legitaniteim");
//	OtherGroup.PlaceLabledControl("Legit AA", this, &legitaa);

//	OtherThirdperson.SetFileId("aa_thirdpsr");
//	OtherGroup.PlaceLabledControl("Thirdperson", this, &OtherThirdperson);

//	OtherSafeMode.SetFileId("otr_safemode");
//	OtherSafeMode.SetState(true);
//	OtherGroup.PlaceLabledControl("Anti untrusted", this, &OtherSafeMode);

//	OtherAutoAccept.SetFileId("otr_autoaccept");
//	OtherGroup.PlaceLabledControl("Automatic accept matchmaking", this, &OtherAutoAccept);

#pragma endregion other random options

/* #pragma region FakeLag
	FakeLagGroup.SetPosition(16, 10);
	FakeLagGroup.SetSize(370, 120);
	FakeLagGroup.SetText("Fakelag");
	RegisterControl(&FakeLagGroup);

	FakeLagEnable.SetFileId("fakelag_enable");
	FakeLagGroup.PlaceLabledControl("Fake Lag", this, &FakeLagEnable);

	FakeLagChoke.SetFileId("fakelag_choke");
	FakeLagChoke.SetBoundaries(0, 16);
	FakeLagChoke.SetValue(0);
	FakeLagGroup.PlaceLabledControl("Choke Factor", this, &FakeLagChoke);

	FakeLagSend.SetFileId("fakelag_send");
	FakeLagSend.SetBoundaries(0, 16);
	FakeLagSend.SetValue(0);
	FakeLagGroup.PlaceLabledControl("Send Factor", this, &FakeLagSend);

	ChokeRandomize.SetFileId("choke_random");
	FakeLagGroup.PlaceLabledControl("Randomize Choke", this, &ChokeRandomize);

	SendRandomize.SetFileId("send_random");
	FakeLagGroup.PlaceLabledControl("Randomize Send", this, &SendRandomize);

#pragma region Buybot
	BuyBotGroup.SetPosition(16, 140);
	BuyBotGroup.SetSize(370, 150);
	BuyBotGroup.SetText("Buybot");
	RegisterControl(&BuyBotGroup);

	EnableBuyBot.SetFileId("bb_enable");
	BuyBotGroup.PlaceLabledControl("Enable", this, &EnableBuyBot);

	BuyBot.SetFileId("buybot");
	BuyBot.AddItem("Off");
	BuyBot.AddItem("Ak/M4");
	BuyBot.AddItem("AWP");
	BuyBot.AddItem("Auto + Duals");
	BuyBotGroup.PlaceLabledControl("Buy Bot", this, &BuyBot);

	BuyBotGrenades.SetFileId("buybot_grenades");
	BuyBotGrenades.AddItem("Off");
	BuyBotGrenades.AddItem("Flash + Smoke + HE");
	BuyBotGrenades.AddItem("Flash + Smoke + HE + Molo");
	BuyBotGroup.PlaceLabledControl("Buy Grenades", this, &BuyBotGrenades);

	BuyBotKevlar.SetFileId("buybot_kevlar");
	BuyBotGroup.PlaceLabledControl("Buy Armor", this, &BuyBotKevlar);

	BuyBotDefuser.SetFileId("buybot_defuser");
	BuyBotGroup.PlaceLabledControl("Buy Defuse Kit", this, &BuyBotDefuser);

#pragma endregion Buybot
#pragma endregion fakelag shit */
}

void CSkinchangerTab::Setup()
{
	SetTitle("SKINS");

	SkinActive.SetPosition(35, 16);
	SkinActive.SetText("Enable skinchanger");
	RegisterControl(&SkinActive);

	SkinEnable.SetFileId("Skin_enable");
	SkinEnable.SetPosition(21, 17);
	RegisterControl(&SkinEnable);

/* #pragma region Knife
	KnifeGroup.SetPosition(16, 11);
	KnifeGroup.SetText("Knife Beta");
	KnifeGroup.SetSize(376, 80);
	RegisterControl(&KnifeGroup);

	KnifeModel.SetFileId("knife_model");
	KnifeModel.AddItem("Bayonet");
	KnifeModel.AddItem("Bowie Knife");
	KnifeModel.AddItem("Butterfly Knife");
	KnifeModel.AddItem("Falchion Knife");
	KnifeModel.AddItem("Flip Knife");
	KnifeModel.AddItem("Gut Knife");
	KnifeModel.AddItem("Huntsman Knife");
	KnifeModel.AddItem("Karambit");
	KnifeModel.AddItem("M9 Bayonet");
	KnifeModel.AddItem("Shadow Daggers");
	KnifeGroup.PlaceLabledControl("Knife", this, &KnifeModel);

	KnifeSkin.SetFileId("knife_skin");
	KnifeGroup.PlaceLabledControl("Skin ID", this, &KnifeSkin);
#pragma endregion */

/* #pragma region Machineguns
	MachinegunsGroup.SetPosition(408, 11);
	MachinegunsGroup.SetText("Heavy");
	MachinegunsGroup.SetSize(360, 80);
	RegisterControl(&MachinegunsGroup);

	NEGEVSkin.SetFileId("negev_skin");
	NEGEVSkin.AddItem("Anodized Navy");
	NEGEVSkin.AddItem("Man-o'-war");
	NEGEVSkin.AddItem("Bratatat");
	NEGEVSkin.AddItem("Desert-Strike");
	NEGEVSkin.AddItem("Nuclear Waste");
	NEGEVSkin.AddItem("Loudmouth");
	NEGEVSkin.AddItem("Power Loader");
	MachinegunsGroup.PlaceLabledControl("Negev", this, &NEGEVSkin);

	M249Skin.SetFileId("m249_skin");
	M249Skin.AddItem("System Lock");
	M249Skin.AddItem("Shipping Forecast");
	M249Skin.AddItem("Impact Drill");
	M249Skin.AddItem("Nebula Crusader");
	M249Skin.AddItem("Spectre");
	MachinegunsGroup.PlaceLabledControl("M249", this, &M249Skin); */

#pragma endregion

#pragma region Snipers
	Snipergroup.SetPosition(16, 11);
	Snipergroup.SetText("Snipers");
	Snipergroup.SetSize(276, 125);
	RegisterControl(&Snipergroup);

	AWPSkin.SetFileId("awp_skin");
	AWPSkin.AddItem("BOOM");
	AWPSkin.AddItem("Dragon Lore");
	AWPSkin.AddItem("Pink DDPAT");
	AWPSkin.AddItem("Fever Dream");
	AWPSkin.AddItem("Lightning Strike");
	AWPSkin.AddItem("Corticera");
	AWPSkin.AddItem("Redline");
	AWPSkin.AddItem("Man-o'-war");
	AWPSkin.AddItem("Graphite");
	AWPSkin.AddItem("Electric Hive");
	AWPSkin.AddItem("Pit Viper");
	AWPSkin.AddItem("Asiimov");
	AWPSkin.AddItem("Oni Taiji");
	AWPSkin.AddItem("Medusa");
	AWPSkin.AddItem("Sun in Leo");
	AWPSkin.AddItem("Hyper Beast");
	AWPSkin.AddItem("Elite Build");
	Snipergroup.PlaceLabledControl("AWP", this, &AWPSkin);

	SSG08Skin.SetFileId("sgg08_skin");
	SSG08Skin.AddItem("Dragonfire");
	SSG08Skin.AddItem("Blood in the Water");
	SSG08Skin.AddItem("Ghost Crusader");
	SSG08Skin.AddItem("Detour");
	SSG08Skin.AddItem("Abyss");
	SSG08Skin.AddItem("Big Iron");
	Snipergroup.PlaceLabledControl("SGG 08", this, &SSG08Skin);

	SCAR20Skin.SetFileId("scar20_skin");
	SCAR20Skin.AddItem("Splash Jam");
	SCAR20Skin.AddItem("Emerald");
	SCAR20Skin.AddItem("Crimson Web");
	SCAR20Skin.AddItem("Cardiac");
	SCAR20Skin.AddItem("Bloodsport");
	SCAR20Skin.AddItem("Cyrex");
	SCAR20Skin.AddItem("Grotto");
	Snipergroup.PlaceLabledControl("SCAR-20", this, &SCAR20Skin);

	G3SG1Skin.SetFileId("g3sg1_skin");
	G3SG1Skin.AddItem("Demeter");
	G3SG1Skin.AddItem("Azure Zebra");
	G3SG1Skin.AddItem("Green Apple");
	G3SG1Skin.AddItem("Orange Kimono");
	G3SG1Skin.AddItem("Neon Kimono");
	G3SG1Skin.AddItem("Murky");
	G3SG1Skin.AddItem("Chronos");
	G3SG1Skin.AddItem("Flux");
	G3SG1Skin.AddItem("The Executioner");
	Snipergroup.PlaceLabledControl("G3SG1", this, &G3SG1Skin);
#pragma endregion

/* #pragma region Shotguns
	Shotgungroup.SetPosition(408, 98);
	Shotgungroup.SetText("Shotguns");
	Shotgungroup.SetSize(360, 125);
	RegisterControl(&Shotgungroup);

	MAG7Skin.SetFileId("mag7_skin");
	MAG7Skin.AddItem("Counter Terrace");
	MAG7Skin.AddItem("Bulldozer");
	MAG7Skin.AddItem("Heat");
	Shotgungroup.PlaceLabledControl("Mag-7", this, &MAG7Skin);

	XM1014Skin.SetFileId("xm1014_skin");
	XM1014Skin.AddItem("Tranquality");
	XM1014Skin.AddItem("Teclu Burner");
	XM1014Skin.AddItem("Scumbria");
	XM1014Skin.AddItem("Heaven Guard");
	XM1014Skin.AddItem("Quicksilver");
	Shotgungroup.PlaceLabledControl("XM1014", this, &XM1014Skin);

	SAWEDOFFSkin.SetFileId("sawedoff_skin");
	SAWEDOFFSkin.AddItem("Serenity");
	SAWEDOFFSkin.AddItem("Orange DDPAT");
	SAWEDOFFSkin.AddItem("Fade");
	SAWEDOFFSkin.AddItem("The Kraken");
	SAWEDOFFSkin.AddItem("Wasteland Princess");
	SAWEDOFFSkin.AddItem("Highwayman");
	Shotgungroup.PlaceLabledControl("Sawed-Off", this, &SAWEDOFFSkin);

	NOVASkin.SetFileId("nova_skin");
	NOVASkin.AddItem("Candy Apple");
	NOVASkin.AddItem("Blaze Orange");
	NOVASkin.AddItem("Modern Hunter");
	NOVASkin.AddItem("Forest Leaves");
	NOVASkin.AddItem("Bloomstick");
	NOVASkin.AddItem("Sand Dune");
	NOVASkin.AddItem("Polar Mesh");
	NOVASkin.AddItem("Walnut");
	NOVASkin.AddItem("Predator");
	NOVASkin.AddItem("Tempest");
	NOVASkin.AddItem("Graphite");
	NOVASkin.AddItem("Ghost Camo");
	NOVASkin.AddItem("Rising Skull");
	NOVASkin.AddItem("Antique");
	NOVASkin.AddItem("Green Apple");
	NOVASkin.AddItem("Caged Steel");
	NOVASkin.AddItem("Koi");
	NOVASkin.AddItem("Moon in Libra");
	NOVASkin.AddItem("Ranger");
	NOVASkin.AddItem("HyperBeast");
	Shotgungroup.PlaceLabledControl("Nova", this, &NOVASkin);
#pragma endregion */

#pragma region Rifles
	Riflegroup.SetPosition(16, 147);
	Riflegroup.SetText("Rifles");
	Riflegroup.SetSize(276, 200);
	RegisterControl(&Riflegroup);

	AK47Skin.SetFileId("ak47_skin");
	AK47Skin.AddItem("First Class");
	AK47Skin.AddItem("Red Laminate");
	AK47Skin.AddItem("Case Hardened");
	AK47Skin.AddItem("Black Laminate");
	AK47Skin.AddItem("Fire Serpent");
	AK47Skin.AddItem("Cartel");
	AK47Skin.AddItem("Emerald Pinstripe");
	AK47Skin.AddItem("Blue Laminate");
	AK47Skin.AddItem("Redline");
	AK47Skin.AddItem("Vulcan");
	AK47Skin.AddItem("Jaguar");
	AK47Skin.AddItem("Jet Set");
	AK47Skin.AddItem("Wasteland Rebel");
	AK47Skin.AddItem("Orbit Mk01");
	AK47Skin.AddItem("Hydroponic");
	AK47Skin.AddItem("Aquamarine Revenge");
	AK47Skin.AddItem("Frontside Misty");
	AK47Skin.AddItem("Point Disarray");
	AK47Skin.AddItem("Fuel Injector");
	AK47Skin.AddItem("Neon Revolution");
	AK47Skin.AddItem("Bloodsport");
	Riflegroup.PlaceLabledControl("AK-47", this, &AK47Skin);

	M41SSkin.SetFileId("m4a1s_skin");
	M41SSkin.AddItem("Dark Water");
	M41SSkin.AddItem("Hyper Beast");
	M41SSkin.AddItem("Decimator");
	M41SSkin.AddItem("VariCamo");
	M41SSkin.AddItem("Nitro");
	M41SSkin.AddItem("Bright Water");
	M41SSkin.AddItem("Atomic Alloy");
	M41SSkin.AddItem("Blood Tiger");
	M41SSkin.AddItem("Guardian");
	M41SSkin.AddItem("Master Piece");
	M41SSkin.AddItem("Knight");
	M41SSkin.AddItem("Cyrex");
	M41SSkin.AddItem("Basilisk");
	M41SSkin.AddItem("Icarus Fell");
	M41SSkin.AddItem("Hot Rod");
	M41SSkin.AddItem("Golden Coi");
	M41SSkin.AddItem("Chantico's Fire");
	M41SSkin.AddItem("Mecha Industries");
	M41SSkin.AddItem("Flashback");
	Riflegroup.PlaceLabledControl("M4A1-S", this, &M41SSkin);

	M4A4Skin.SetFileId("m4a4_skin");
	M4A4Skin.AddItem("Bullet Rain");
	M4A4Skin.AddItem("Zirka");
	M4A4Skin.AddItem("Asiimov");
	M4A4Skin.AddItem("Howl");
	M4A4Skin.AddItem("X-Ray");
	M4A4Skin.AddItem("Desert-Strike");
	M4A4Skin.AddItem("Griffin");
	M4A4Skin.AddItem("Dragon King");
	M4A4Skin.AddItem("Poseidon");
	M4A4Skin.AddItem("Daybreak");
	M4A4Skin.AddItem("Evil Daimyo");
	M4A4Skin.AddItem("Royal Paladin");
	M4A4Skin.AddItem("The BattleStar");
	M4A4Skin.AddItem("Desolate Space");
	M4A4Skin.AddItem("Buzz Kill");
	M4A4Skin.AddItem("Hellfire");
	Riflegroup.PlaceLabledControl("M4A4", this, &M4A4Skin);

	AUGSkin.SetFileId("aug_skin");
	AUGSkin.AddItem("Bengal Tiger");
	AUGSkin.AddItem("Hot Rod");
	AUGSkin.AddItem("Chameleon");
	AUGSkin.AddItem("Torque");
	AUGSkin.AddItem("Radiation Hazard");
	AUGSkin.AddItem("Asterion");
	AUGSkin.AddItem("Daedalus");
	AUGSkin.AddItem("Akihabara Accept");
	AUGSkin.AddItem("Ricochet");
	AUGSkin.AddItem("Fleet Flock");
	AUGSkin.AddItem("Syd Mead");
	Riflegroup.PlaceLabledControl("AUG", this, &AUGSkin);

	FAMASSkin.SetFileId("famas_skin");
	FAMASSkin.AddItem("Djinn");
	FAMASSkin.AddItem("Afterimage");
	FAMASSkin.AddItem("Doomkitty");
	FAMASSkin.AddItem("Spitfire");
	FAMASSkin.AddItem("Teardown");
	FAMASSkin.AddItem("Hexane");
	FAMASSkin.AddItem("Pulse");
	FAMASSkin.AddItem("Sergeant");
	FAMASSkin.AddItem("Styx");
	FAMASSkin.AddItem("Neural Net");
	FAMASSkin.AddItem("Survivor");
	FAMASSkin.AddItem("Valence");
	FAMASSkin.AddItem("Roll Cage");
	FAMASSkin.AddItem("Mecha Industries");
	Riflegroup.PlaceLabledControl("FAMAS", this, &FAMASSkin);

	GALILSkin.SetFileId("galil_skin");
	GALILSkin.AddItem("Orange DDPAT");
	GALILSkin.AddItem("Eco");
	GALILSkin.AddItem("Stone Cold");
	GALILSkin.AddItem("Cerberus");
	GALILSkin.AddItem("Aqua Terrace");
	GALILSkin.AddItem("Chatterbox");
	GALILSkin.AddItem("Firefight");
	GALILSkin.AddItem("Rocket Pop");
	GALILSkin.AddItem("Sugar Rush");
	Riflegroup.PlaceLabledControl("GALIL", this, &GALILSkin);

	SG553Skin.SetFileId("sg552_skin");
	SG553Skin.AddItem("Bulldozer");
	SG553Skin.AddItem("Ultraviolet");
	SG553Skin.AddItem("Damascus Steel");
	SG553Skin.AddItem("Fallout Warning");
	SG553Skin.AddItem("Damascus Steel");
	SG553Skin.AddItem("Pulse");
	SG553Skin.AddItem("Army Sheen");
	SG553Skin.AddItem("Traveler");
	SG553Skin.AddItem("Fallout Warning");
	SG553Skin.AddItem("Cyrex");
	SG553Skin.AddItem("Tiger Moth");
	SG553Skin.AddItem("Atlas");
	Riflegroup.PlaceLabledControl("SG553", this, &SG553Skin);
#pragma endregion

#pragma region MPs
	MPGroup.SetPosition(304, 11);
	MPGroup.SetText("SMGs");
	MPGroup.SetSize(212, 173);
	RegisterControl(&MPGroup);

	MAC10Skin.SetFileId("mac10_skin");
	MAC10Skin.AddItem("Fade");
	MAC10Skin.AddItem("Neon Rider");
	MAC10Skin.AddItem("Ultraviolet");
	MAC10Skin.AddItem("Palm");
	MAC10Skin.AddItem("Graven");
	MAC10Skin.AddItem("Tatter");
	MAC10Skin.AddItem("Amber Fade");
	MAC10Skin.AddItem("Heat");
	MAC10Skin.AddItem("Curse");
	MAC10Skin.AddItem("Indigo");
	MAC10Skin.AddItem("Commuter");
	MAC10Skin.AddItem("Nuclear Garden");
	MAC10Skin.AddItem("Malachite");
	MAC10Skin.AddItem("Rangeen");
	MAC10Skin.AddItem("Lapis Gator");
	MPGroup.PlaceLabledControl("MAC-10", this, &MAC10Skin);

	P90Skin.SetFileId("p90_skin");
	P90Skin.AddItem("Cold Blooded");
	P90Skin.AddItem("Death by Kitty");
	P90Skin.AddItem("Shapewood");
	P90Skin.AddItem("Emerald Dragon");
	P90Skin.AddItem("Asiimov");
	P90Skin.AddItem("Virus");
	MPGroup.PlaceLabledControl("P90", this, &P90Skin);

	UMP45Skin.SetFileId("ump45_skin");
	UMP45Skin.AddItem("Blaze");
	UMP45Skin.AddItem("Primal Saber");
	UMP45Skin.AddItem("Minotaurs Labyrinth");
	UMP45Skin.AddItem("Grand Prix");
	MPGroup.PlaceLabledControl("UMP-45", this, &UMP45Skin);

	BIZONSkin.SetFileId("bizon_skin");
	BIZONSkin.AddItem("Blue Streak");
	BIZONSkin.AddItem("Antique");
	BIZONSkin.AddItem("Judgement of Anubis");
	BIZONSkin.AddItem("Osiris");
	BIZONSkin.AddItem("Fuel Rod");
	MPGroup.PlaceLabledControl("PP-Bizon", this, &BIZONSkin);

	MP7Skin.SetFileId("mp7_skin");
	MP7Skin.AddItem("Whiteout");
	MP7Skin.AddItem("Nemesis");
	MP7Skin.AddItem("Impire");
	MPGroup.PlaceLabledControl("MP7", this, &MP7Skin);

	MP9Skin.SetFileId("mp9_skin");
	MP9Skin.AddItem("Ruby Poison Dart");
	MP9Skin.AddItem("Hot Rod");
	MPGroup.PlaceLabledControl("MP9", this, &MP9Skin);

#pragma endregion

#pragma region Pistols
	PistolGroup.SetPosition(304, 192);
	PistolGroup.SetText("Pistols");
	PistolGroup.SetSize(212, 180);
	RegisterControl(&PistolGroup);

	GLOCKSkin.SetFileId("glock_skin");
	GLOCKSkin.AddItem("Wasteland Rebel");
	GLOCKSkin.AddItem("Twillight Galaxy");
	GLOCKSkin.AddItem("Fade");
	GLOCKSkin.AddItem("Dragon Tattoo");
	GLOCKSkin.AddItem("Water Elemental");
	GLOCKSkin.AddItem("Royal Legion");
	GLOCKSkin.AddItem("Grinder");
	GLOCKSkin.AddItem("Reactor");
	GLOCKSkin.AddItem("Weasel");
	PistolGroup.PlaceLabledControl("Glock", this, &GLOCKSkin);

	USPSSkin.SetFileId("usps_skin");
	USPSSkin.AddItem("Dark Water");;
	USPSSkin.AddItem("Overgrowth");
	USPSSkin.AddItem("Caiman");
	USPSSkin.AddItem("Blood Tiger");
	USPSSkin.AddItem("Serum");
	USPSSkin.AddItem("Neo-Noir");
	USPSSkin.AddItem("Stainless");
	USPSSkin.AddItem("Guardian");
	USPSSkin.AddItem("Orion");
	USPSSkin.AddItem("Road Rash");
	USPSSkin.AddItem("Royal Blue");
	USPSSkin.AddItem("Business Class");
	USPSSkin.AddItem("Para Green");
	USPSSkin.AddItem("Torque");
	USPSSkin.AddItem("Kill Confirmed");
	USPSSkin.AddItem("Lead Conduit");
	USPSSkin.AddItem("Cyrex");
	PistolGroup.PlaceLabledControl("USP-S", this, &USPSSkin);

	DUALSSkin.SetFileId("duals_skin");
	DUALSSkin.AddItem("Dualing Dragons");
	DUALSSkin.AddItem("Anodized Navy");
	DUALSSkin.AddItem("Duelist");
	DUALSSkin.AddItem("Hemoglobin");
	DUALSSkin.AddItem("Marina");
	DUALSSkin.AddItem("Urban Shock");
	PistolGroup.PlaceLabledControl("Duals", this, &DUALSSkin);

	RevolverSkin.SetFileId("revolver_skin");
	RevolverSkin.AddItem("Fade");
	RevolverSkin.AddItem("Crimson Web");
	RevolverSkin.AddItem("Amber Fade");
	RevolverSkin.AddItem("Reboot");
	PistolGroup.PlaceLabledControl("Revolver", this, &RevolverSkin);

	FIVESEVENSkin.SetFileId("fiveseven_skin");
	FIVESEVENSkin.AddItem("Case Hardened");
	FIVESEVENSkin.AddItem("Fowl Play");
	FIVESEVENSkin.AddItem("Retrobution");
	FIVESEVENSkin.AddItem("Triumvirate");
	FIVESEVENSkin.AddItem("Neon Kimono");
	FIVESEVENSkin.AddItem("Monkey Business");
	FIVESEVENSkin.AddItem("Copper Galaxy");
	FIVESEVENSkin.AddItem("Hyper Beast");
	PistolGroup.PlaceLabledControl("Five-Seven", this, &FIVESEVENSkin);

	TECNINESkin.SetFileId("tec9_skin");
	TECNINESkin.AddItem("Terrace");
	TECNINESkin.AddItem("Isaac");
	TECNINESkin.AddItem("Red Quartz");
	TECNINESkin.AddItem("Avalanche");
	TECNINESkin.AddItem("Toxic");
	TECNINESkin.AddItem("Fuel Injector");
	TECNINESkin.AddItem("Re-Entry");
	TECNINESkin.AddItem("Bamboo Forest");
	TECNINESkin.AddItem("Nuclear Threat");
	PistolGroup.PlaceLabledControl("Tec-9", this, &TECNINESkin);

#pragma endregion

#pragma region Skinsettings
/*	SkinsettingsGroup.SetPosition(408, 496);
	SkinsettingsGroup.SetText("Customisation");
	SkinsettingsGroup.SetSize(360, 118);
	RegisterControl(&SkinsettingsGroup);

	StatTrakEnable.SetFileId("skin_stattrack");
	SkinsettingsGroup.PlaceLabledControl("Stat Trak", this, &StatTrakEnable);

	StatTrackAmount.SetFileId("skin_stamount");
	SkinsettingsGroup.PlaceLabledControl("Value", this, &StatTrackAmount);

	KnifeName.SetFileId("knife_name");
	SkinsettingsGroup.PlaceLabledControl("Knife Name", this, &KnifeName);

	SkinName.SetFileId("skin_name");
	SkinsettingsGroup.PlaceLabledControl("Skin Name", this, &SkinName); */

	SkinApply.SetText("Apply skins");
	SkinApply.SetCallback(GlovesApplyCallbk);
	SkinApply.SetPosition(16, 363);
	SkinApply.SetSize(276, 10);
	RegisterControl(&SkinApply);

#pragma endregion

#pragma endregion other random options

} 


void Menu::SetupMenu()
{
	Window.Setup();

	GUI.RegisterWindow(&Window);
	GUI.BindWindow(VK_INSERT, &Window);
}

void Menu::DoUIFrame()
{
		if (Window.VisualsTab.FiltersAll.GetState())
	{
		Window.VisualsTab.FiltersC4.SetState(true);
		Window.VisualsTab.FiltersChickens.SetState(true);
		Window.VisualsTab.FiltersPlayers.SetState(true);
		Window.VisualsTab.FiltersWeapons.SetState(true);
		Window.VisualsTab.FiltersEnemiesOnly.SetState(true);
	}

		if (Window.RageBotTab.AimbotEnable.GetState() == true)
		{
			Window.RageBotTab.Active.SetState(true);
		}

		if (Window.RageBotTab.AimbotEnable.GetState() == false)
		{
			Window.RageBotTab.Active.SetState(false);
		}

		if (Window.LegitBotTab.AimbotEnable.GetState() == true)
		{
			Window.LegitBotTab.Active.SetState(true);
		}

		if (Window.LegitBotTab.AimbotEnable.GetState() == false)
		{
			Window.LegitBotTab.Active.SetState(false);
		}

		if (Window.VisualsTab.Active.GetState() == true)
		{
			Window.VisualsTab.FiltersPlayers.SetState(true);
		}

		if (Window.MiscTab.Bhop.GetState() == true)
		{
			Window.MiscTab.OtherAutoJump.SetIndex(1);
		}

		if (Window.MiscTab.Bhop.GetState() == false)
		{
			Window.MiscTab.OtherAutoJump.SetIndex(0);
		}

		if (Window.MiscTab.AutoStrafe.GetState() == true)
		{
			Window.MiscTab.OtherAutoStrafe.SetIndex(2);
		}

		if (Window.MiscTab.AutoStrafe.GetState() == false)
		{
			Window.MiscTab.OtherAutoStrafe.SetIndex(0);
		}

		if (Window.RageBotTab.AntiAimEnable.GetState() == true)
		{
			Window.RageBotTab.AntiAimKnife.SetState(true);
		}

		if (Window.RageBotTab.AntiAimEnable.GetState() == false)
		{
			Window.RageBotTab.AntiAimKnife.SetState(false);
		}

		if (Window.VisualsTab.Box.GetState() == true)
		{
			Window.VisualsTab.OptionsBox.SetIndex(2);
		}

		if (Window.VisualsTab.Box.GetState() == false)
		{
			Window.VisualsTab.OptionsBox.SetIndex(0);
		}

		if (Window.VisualsTab.Glow.GetState() == true)
		{
			Window.VisualsTab.OptionsGlow.SetIndex(1);
		}

		if (Window.VisualsTab.Glow.GetState() == false)
		{
			Window.VisualsTab.OptionsGlow.SetIndex(0);
		}

		if (Window.VisualsTab.Chams.GetState() == true)
		{
			Window.VisualsTab.OptionsChams.SetIndex(2);
		}

		if (Window.VisualsTab.Chams.GetState() == false)
		{
			Window.VisualsTab.OptionsChams.SetIndex(0);
		}

		if (Window.MiscTab.Clantag.GetState() == true)
		{
			Window.MiscTab.OtherClantag.SetIndex(1);
		}

		if (Window.MiscTab.Clantag.GetState() == false)
		{
			Window.MiscTab.OtherClantag.SetIndex(0);
		}

		if (Window.RageBotTab.AntiAimEnable.GetState() == true)
		{
			Window.RageBotTab.AntiAimPitch.SetIndex(3);
		}

		if (Window.RageBotTab.AntiAimEnable.GetState() == false)
		{
			Window.RageBotTab.AntiAimPitch.SetIndex(0);
		}

		if (Window.RageBotTab.FakeLagEnable.GetState() == true)
		{
			Window.RageBotTab.FakeLagTyp.SetIndex(1);
		}

		if (Window.RageBotTab.FakeLagEnable.GetState() == false)
		{
			Window.RageBotTab.FakeLagTyp.SetIndex(0);
		}

		if (Window.LegitBotTab.TriggerEnable.GetState() == true)
		{
			Window.LegitBotTab.TriggerHead.SetState(true);
			Window.LegitBotTab.TriggerChest.SetState(true);
			Window.LegitBotTab.TriggerStomach.SetState(true);
			Window.LegitBotTab.TriggerArms.SetState(true);
			Window.LegitBotTab.TriggerLegs.SetState(true);
			Window.LegitBotTab.TriggerRecoil.SetState(true);
		}

		if (Window.LegitBotTab.TriggerEnable.GetState() == false)
		{
			Window.LegitBotTab.TriggerHead.SetState(false);
			Window.LegitBotTab.TriggerChest.SetState(false);
			Window.LegitBotTab.TriggerStomach.SetState(false);
			Window.LegitBotTab.TriggerArms.SetState(false);
			Window.LegitBotTab.TriggerLegs.SetState(false);
			Window.LegitBotTab.TriggerRecoil.SetState(false);
		}

	GUI.Update();
	GUI.Draw();

	
}




























































