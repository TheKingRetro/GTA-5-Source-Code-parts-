#pragma once

#ifndef FILEREADER_H
#define FILEREADER_H

#include "stdafx.h"

class MyYAML
{
private:
	static std::fstream SettingsFile;
	static const char* Filename;

public:
	static YAML::Node Settings;
	static BOOLEAN Initialized;
	static INT CSaveTick;
	static INT LSaveTick;

	static BOOLEAN OpenSettingsFile(const char* _fileName)
	{
		Filename = _fileName;
		Settings = YAML::LoadFile(_fileName);
		if (Settings.IsNull())
			return FALSE;

		std::ifstream tempSettingsFile(_fileName);
		std::string Buffer((std::istreambuf_iterator<char>(tempSettingsFile)), std::istreambuf_iterator<char>());

		SettingsFile.open(_fileName);
		if (!SettingsFile.is_open())
		{
			return FALSE;
		}
		SettingsFile << Buffer.c_str();

		return (Initialized = TRUE);
	}

	static unsigned short GetNodeSize(std::string _Node)
	{
		if (Settings[_Node].IsNull())
			return 0;
		return Settings[_Node].size();
	}

	template <class vType>
	static vType GetValueFromNode(std::string _Node, std::string _Value)
	{
		YAML::Node _TempNode = Settings[_Node];
		if (_TempNode.IsNull() || _TempNode[_Value].IsNull())
			return vType();
		return (vType)_TempNode[_Value].as<vType>();
	}

	template <class vType>
	static vType GetValueFromArrayNode(std::string _Node, std::string _Value, int _index)
	{
		YAML::Node _TempNode = Settings[_Node];
		if (_TempNode.IsNull())
			return vType();
		return (vType)_TempNode[_Value][_index].as<vType>();
	}

	static BOOLEAN ClearFile()
	{
		SettingsFile.close();
		SettingsFile.open(Filename, std::ios::out);
		SettingsFile.close();

		SettingsFile.open(Filename);
		if (!SettingsFile.is_open())
		{
			return FALSE;
		}
		return TRUE;
	}

	static void SaveData()		//THIS IS CUSTOM FOR DIFFERENT GAMES
	{
		if (ClearFile() && GUIElements::Initialized)
		{
			YAML::Emitter Saver;

			Saver << YAML::BeginMap;

			Saver << YAML::Comment("YAML File for GTA V Ultimatum Hack by Tonyx97\nTeleport Bookmark Formatting: Teleport_ID[x, y, z, BookMark Name] (follow the order of Teleport_ID, Teleport_1, Teleport_2 etc.)");

			/*MENU COLOR*/
			Saver << YAML::Key << "Menu_Color";
			Saver << YAML::BeginMap;

			Saver << YAML::Key << "Red";
			Saver << YAML::Value << GUIWindows[0]->color.R();
			Saver << YAML::Key << "Green";
			Saver << YAML::Value << GUIWindows[0]->color.G();
			Saver << YAML::Key << "Blue";
			Saver << YAML::Value << GUIWindows[0]->color.B();
			Saver << YAML::Key << "Alpha";
			Saver << YAML::Value << GUIWindows[0]->color.A();

			Saver << YAML::EndMap;
			/*MENU COLOR*/
			
			/*CUSTOMIZABLES*/
			Saver << YAML::Key << "Customizables";
			Saver << YAML::BeginMap;

			Saver << YAML::Key << "Vehicle_Impulse_Key";
			Saver << YAML::Value << YAML::Value << CGUI::GetDropMenuFromName("Impulse Key")->MainItem.Name;
			Saver << YAML::Key << "Vehicle_Instant_Stop_Key";
			Saver << YAML::Value << YAML::Value << CGUI::GetDropMenuFromName("Instant Stop Key")->MainItem.Name;
			Saver << YAML::Key << "Menu_Key";
			Saver << YAML::Value << YAML::Value << CGUI::GetDropMenuFromName("Menu Key")->MainItem.Name;
			Saver << YAML::Key << "Kill_All_Peds_Key";
			Saver << YAML::Value << YAML::Value << CGUI::GetDropMenuFromName("Kill Peds Key")->MainItem.Name;

			Saver << YAML::EndMap;
			/*CUSTOMIZABLES*/

			/*TELEPORT BOOKMARK*/
			Saver << YAML::Key << "Teleport_Bookmark";
			Saver << YAML::BeginMap;

			for (unsigned short i = 0; i < Settings["Teleport_Bookmark"].size(); i++)
			{
				Saver << YAML::Key << "Teleport_" + std::to_string(i + 1);
				Saver << YAML::Flow;
				Saver << YAML::BeginSeq << GetValueFromArrayNode<float>("Teleport_Bookmark", "Teleport_" + std::to_string(i + 1), 0) << 
										   GetValueFromArrayNode<float>("Teleport_Bookmark", "Teleport_" + std::to_string(i + 1), 1) << 
										   GetValueFromArrayNode<float>("Teleport_Bookmark", "Teleport_" + std::to_string(i + 1), 2) <<
										   GetValueFromArrayNode<std::string>("Teleport_Bookmark", "Teleport_" + std::to_string(i + 1), 3) << YAML::EndSeq;
			}

			Saver << YAML::EndMap;
			/*TELEPORT BOOKMARK*/

			/*MAIN*/
			Saver << YAML::Key << "Main";
			Saver << YAML::BeginMap;

			Saver << YAML::Key << "Full_God_Mode";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("full_godmode")->state);
			Saver << YAML::Key << "Fast_Movement";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("fastswimetc")->state);
			Saver << YAML::Key << "Damage_Mod";
			Saver << YAML::Value << Features::fDamageMod;
			Saver << YAML::Key << "Vehicle_Impulse";
			Saver << YAML::Value << Features::fVehImpulse;
			Saver << YAML::Key << "Melee_Damage";
			Saver << YAML::Value << Features::fMeleeDamage;
			Saver << YAML::Key << "Vehicle_Gravity";
			Saver << YAML::Value << Features::fVehGravity;
			Saver << YAML::Key << "Ped_Amount";
			Saver << YAML::Value << LocalPlayer::GetPedAmount();
			Saver << YAML::Key << "Vehicle_Amount";
			Saver << YAML::Value << LocalPlayer::GetVehicleAmount();
		
			Saver << YAML::EndMap;
			/*MAIN*/

			/*WEAPONS*/
			Saver << YAML::Key << "Weapons";
			Saver << YAML::BeginMap;

			Saver << YAML::Key << "Fast_Reload";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("fastreload")->state);
			Saver << YAML::Key << "Super_Impulse";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("superimpulse")->state);
			Saver << YAML::Key << "Ultra_Penetration";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("ultrapenetration")->state);
			Saver << YAML::Key << "No_Spread";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("nospread")->state);
			Saver << YAML::Key << "No_Recoil";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("norecoil")->state);
			Saver << YAML::Key << "Aiming_FOV";
			Saver << YAML::Value << Features::fAimingFOV;

			Saver << YAML::EndMap;
			/*WEAPONS*/

			/*ESP*/
			Saver << YAML::Key << "ESP";
			Saver << YAML::BeginMap;

			Saver << YAML::Key << "Enable";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("enableesp")->state);
			Saver << YAML::Key << "Boxes3D";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("3dboxes")->state);
			Saver << YAML::Key << "Show_Peds";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("showpeds")->state);
			Saver << YAML::Key << "Show_Players";
			Saver << YAML::Value << (bool)(CGUI::GetCheckboxFromName("showplayers")->state);
			Saver << YAML::Key << "ESP_Max_Distance";
			Saver << YAML::Value << Features::fESPMaxDistance;

			Saver << YAML::EndMap;
			/*ESP*/

			Saver << YAML::EndMap;

			if (SettingsFile.is_open())
				SettingsFile << Saver.c_str();

			SettingsFile.close();
		}
	}

	static void CloseSettingsFile()
	{
		if (Initialized)
			SaveData();
	}
};


#endif