#include "bullettrace.h"
#include "Interfaces.h"
#include "Entities.h"

void cbullet_tracer::log(IGameEvent* event)
{
	//if we receive bullet_impact event
	if (strstr(event->GetName(), "bullet_impact"))
	{
		//get the user who fired the bullet
		auto index = Interfaces::Engine->GetPlayerForUserID(event->GetInt("userid"));

		//return if the userid is not valid or we werent the entity who was fireing
		if (index != Interfaces::Engine->GetLocalPlayer())
			return;

		//get local player
		auto local = static_cast<IClientEntity*>(Interfaces::EntList->GetClientEntity(index));
		if (!local)
			return;

		//get the bullet impact's position
		Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));

		Ray_t ray;
		ray.Init(local->GetEyePosition(), position);

		//skip local player
		CTraceFilter filter;
		filter.pSkip = local;

		//trace a ray
		trace_t tr;
		Interfaces::Trace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		//use different color when we hit a player
		auto color = (tr.m_pEnt && reinterpret_cast<IClientEntity*>(tr.m_pEnt)->IsPlayer()) ? Color(140, 29, 29, 220) : Color(255, 255, 0, 220);

		//push info to our vector
		logs.push_back(cbullet_tracer_info(local->GetEyePosition(), position, Interfaces::Globals->curtime, color));
	}
}

void cbullet_tracer::render()
{

	//	if (Menu::Window.VisualsTab.OptionsWeapon.GetState())
	//	return;

	//get local player
	IClientEntity *local = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!local)
		return;

	//loop through our vector
	for (size_t i = 0; i < logs.size(); i++)
	{
		//get the current item
		auto current = logs.at(i);

		//draw a line from local player's head position to the hit point
		Interfaces::DebugOverlay->AddLineOverlay(current.src, current.dst, current.color.r(), current.color.g(), current.color.b(), true, -1.f);
		//draw a box at the hit point
		Interfaces::DebugOverlay->AddBoxOverlay(current.dst, Vector(-2, -2, -2), Vector(2, 2, 2), Vector(0, 0, 0), 255, 0, 0, 127, -1.f);

		//if the item is older than 5 seconds, delete it
		if (fabs(Interfaces::Globals->curtime - current.time) > 5.f)
			logs.erase(logs.begin() + i);
	}
}

























































