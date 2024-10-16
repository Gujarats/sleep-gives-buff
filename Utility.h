#pragma once

class Utility {
public:
	RE::SpellItem* Sleep_AwakeBUff;
	uintptr_t PlayerSingletonAddress;

	static Utility* GetSingleton()
	{
		static Utility playerStatus;
		return &playerStatus;
	}

    static RE::PlayerCharacter* GetPlayer()
	{
		REL::Relocation<RE::NiPointer<RE::PlayerCharacter>*> singleton{ Utility::GetSingleton()->PlayerSingletonAddress };
		return singleton->get();
	}

}