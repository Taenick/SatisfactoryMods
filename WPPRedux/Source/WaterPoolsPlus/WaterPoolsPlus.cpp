#include "WaterPoolsPlus.h"

#include "Hologram/FGWaterPumpHologram.h"
#include "Buildables/FGBuildable.h"
#include "Patching/NativeHookManager.h"

void FWaterPoolsPlusModule::StartupModule() {
	if (!WITH_EDITOR)
	{
		SUBSCRIBE_METHOD(AFGWaterPumpHologram::CheckMinimumDepth, [](auto& Scope, AFGWaterPumpHologram* Self)
		{
			Scope.Cancel();
		});

		// PlayDismantleEffect ignores ShouldSkipBuildEffect/mSkipBuildEffect, unlike the build effect path.
		// Buildables that opt out of the build effect (e.g. ones with a broken BuildEffect material remap)
		// should also skip the dismantle effect, so honor the same flag here.
		SUBSCRIBE_METHOD(AFGBuildable::PlayDismantleEffect, [](auto& Scope, AFGBuildable* Self)
		{
			if (Self->ShouldSkipBuildEffect())
			{
				Scope.Cancel();
			}
		});
	}
}

IMPLEMENT_GAME_MODULE(FWaterPoolsPlusModule, WaterPoolsPlus);