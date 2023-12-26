#include "stdafx.h"

GID TWindows = 0;
GID TCheckboxes = 0;
GID TTabs = 0;
GID TProgressBars = 0;
GID TLabels = 0;
GID TDropMenus = 0;
GID TButtons = 0;

Vector2 CGUI::CursorPos = Vector2();
INT CGUI::LastClick = 0;
INT CGUI::LastTick = 0;
INT CGUI::CurrentTick = 60000;

BOOLEAN GUIElements::Initialized = FALSE;


void GUIElements::InitGUIElements() 
{
	//YAML LOADING GUI STUFF
	Color MainWndColor;
	if (MyYAML::Initialized)
	{
		MainWndColor = Color(MyYAML::GetValueFromNode<int>("Menu_Color", "Red"), MyYAML::GetValueFromNode<int>("Menu_Color", "Green"), MyYAML::GetValueFromNode<int>("Menu_Color", "Blue"), MyYAML::GetValueFromNode<int>("Menu_Color", "Alpha"));

		//MAIN WINDOW
		GID MainWindow = GUIElements::GUICreateWindow(new CWindow(Rect(200, 200, 485, 375), "UnKnoWnCheaTs GTA V Ultimatum - By Tonyx97", Vector2(380, 300), 2, MainWndColor, Color(255, 255, 255, 255), 0, -1, "")); //STORES TAB SIZE

		//TABS
		GID MainTab = GUIElements::GUICreateTab(new CTab(Rect(10, 10, 0, 30), "Main", Color(0, 0, 0, 180), Color(255, 255, 255, 255), Color(255, 255, 255, 255), MainWindow, "window", 0));
		GID WeaponsTab = GUIElements::GUICreateTab(new CTab(Rect(10, 10, 0, 30), "Weapons", Color(0, 0, 0, 180), Color(255, 255, 255, 255), Color(255, 255, 255, 255), MainWindow, "window", 1));
		GID TeleportTab = GUIElements::GUICreateTab(new CTab(Rect(10, 10, 0, 30), "Teleport", Color(0, 0, 0, 180), Color(255, 255, 255, 255), Color(255, 255, 255, 255), MainWindow, "window", 2));
		GID ESPTab = GUIElements::GUICreateTab(new CTab(Rect(10, 10, 0, 30), "ESP", Color(0, 0, 0, 180), Color(255, 255, 255, 255), Color(255, 255, 255, 255), MainWindow, "window", 3));
		GID CustomizationTab = GUIElements::GUICreateTab(new CTab(Rect(10, 10, 0, 30), "Customization", Color(0, 0, 0, 180), Color(255, 255, 255, 255), Color(255, 255, 255, 255), MainWindow, "window", 4));
		//GID SettingsTab = GUIElements::GUICreateTab(new CTab(Rect(10, 10, 0, 30), "Settings", Color(0, 0, 0, 180), Color(255, 255, 255, 255), Color(255, 255, 255, 255), MainWindow, "window", 5));

		//DEFAULT TABS FOR CUSTOMIZATION
		CDropMenuElements* VirtualKeys = new CDropMenuElements("VKeys");
		VirtualKeys->InsertItem("F1", VK_F1);
		VirtualKeys->InsertItem("F2", VK_F2);
		VirtualKeys->InsertItem("F3", VK_F3);
		VirtualKeys->InsertItem("F4", VK_F4);
		VirtualKeys->InsertItem("F5", VK_F5);
		VirtualKeys->InsertItem("F6", VK_F6);
		VirtualKeys->InsertItem("F7", VK_F7);
		VirtualKeys->InsertItem("F8", VK_F8);
		VirtualKeys->InsertItem("F9", VK_F9);
		VirtualKeys->InsertItem("F10", VK_F10);
		VirtualKeys->InsertItem("F11", VK_F11);
		VirtualKeys->InsertItem("F12", VK_F12);
		VirtualKeys->InsertItem("NUMPAD 0", VK_NUMPAD0);
		VirtualKeys->InsertItem("NUMPAD 1", VK_NUMPAD1);
		VirtualKeys->InsertItem("NUMPAD 2", VK_NUMPAD2);
		VirtualKeys->InsertItem("NUMPAD 3", VK_NUMPAD3);
		VirtualKeys->InsertItem("NUMPAD 4", VK_NUMPAD4);
		VirtualKeys->InsertItem("NUMPAD 5", VK_NUMPAD5);
		VirtualKeys->InsertItem("NUMPAD 6", VK_NUMPAD6);
		VirtualKeys->InsertItem("NUMPAD 7", VK_NUMPAD7);
		VirtualKeys->InsertItem("NUMPAD 8", VK_NUMPAD8);
		VirtualKeys->InsertItem("NUMPAD 9", VK_NUMPAD9);
		VirtualKeys->InsertItem("0", 0x30);
		VirtualKeys->InsertItem("1", 0x31);
		VirtualKeys->InsertItem("2", 0x32);
		VirtualKeys->InsertItem("3", 0x33);
		VirtualKeys->InsertItem("4", 0x34);
		VirtualKeys->InsertItem("5", 0x35);
		VirtualKeys->InsertItem("6", 0x36);
		VirtualKeys->InsertItem("7", 0x37);
		VirtualKeys->InsertItem("8", 0x38);
		VirtualKeys->InsertItem("9", 0x39);
		VirtualKeys->InsertItem("A", 0x41);
		VirtualKeys->InsertItem("B", 0x42);
		VirtualKeys->InsertItem("C", 0x43);
		VirtualKeys->InsertItem("D", 0x44);
		VirtualKeys->InsertItem("E", 0x45);
		VirtualKeys->InsertItem("F", 0x46);
		VirtualKeys->InsertItem("G", 0x47);
		VirtualKeys->InsertItem("H", 0x48);
		VirtualKeys->InsertItem("I", 0x49);
		VirtualKeys->InsertItem("J", 0x4A);
		VirtualKeys->InsertItem("K", 0x4B);
		VirtualKeys->InsertItem("J", 0x4C);
		VirtualKeys->InsertItem("M", 0x4D);
		VirtualKeys->InsertItem("N", 0x4E);
		VirtualKeys->InsertItem("O", 0x4F);
		VirtualKeys->InsertItem("P", 0x50);
		VirtualKeys->InsertItem("Q", 0x51);
		VirtualKeys->InsertItem("R", 0x52);
		VirtualKeys->InsertItem("S", 0x53);
		VirtualKeys->InsertItem("T", 0x54);
		VirtualKeys->InsertItem("U", 0x55);
		VirtualKeys->InsertItem("V", 0x56);
		VirtualKeys->InsertItem("W", 0x57);
		VirtualKeys->InsertItem("X", 0x58);
		VirtualKeys->InsertItem("Y", 0x59);
		VirtualKeys->InsertItem("Z", 0x5A);
		VirtualKeys->InsertItem("Multiply", VK_MULTIPLY);
		VirtualKeys->InsertItem("Divide", VK_DIVIDE);
		VirtualKeys->InsertItem("Add", VK_ADD);
		VirtualKeys->InsertItem("Substract", VK_SUBTRACT);
		VirtualKeys->InsertItem("Separator", VK_SEPARATOR);
		VirtualKeys->InsertItem("Decimal", VK_DECIMAL);

		GID ImpulseKey_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(10, 40, 0, 0), "virtualkeys", "Impulse Key", VirtualKeys, Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), CustomizationTab, "tab", "Impulse Key"));
		GID InstantStopKey_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(140, 40, 0, 0), "virtualkeys", "Instant Stop Key", VirtualKeys->GetCopy(), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), CustomizationTab, "tab", "Instant Stop Key"));
		GID OpenMenuKey_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(300, 40, 0, 0), "virtualkeys", "Menu Key", VirtualKeys->GetCopy(), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), CustomizationTab, "tab", "Menu Key"));
		GID KillAllPeds_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(180, 195, 0, 0), "virtualkeys", "Kill Peds Key", VirtualKeys->GetCopy(), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), CustomizationTab, "tab", "Kill All Peds"));

		GID MenuRed_PB = GUIElements::GUICreateProgressBar(new CProgressBar("menured", Rect(10, 180, 150, 5), "Menu Red: %i", (int)MainWndColor.R(), Color(0, 255, 0, 255), Color(100, 100, 100, 175), CustomizationTab, "tab"));
		GID MenuGreen_PB = GUIElements::GUICreateProgressBar(new CProgressBar("menugreen", Rect(10, 210, 150, 5), "Menu Green: %i", (int)MainWndColor.G(), Color(0, 255, 0, 255), Color(100, 100, 100, 175), CustomizationTab, "tab"));
		GID MenuBlue_PB = GUIElements::GUICreateProgressBar(new CProgressBar("menublue", Rect(10, 240, 150, 5), "Menu Blue: %i", (int)MainWndColor.B(), Color(0, 255, 0, 255), Color(100, 100, 100, 175), CustomizationTab, "tab"));
		GID MenuAlpha_PB = GUIElements::GUICreateProgressBar(new CProgressBar("menualpha", Rect(10, 270, 150, 5), "Menu Alpha: %i", (int)MainWndColor.A(), Color(0, 255, 0, 255), Color(100, 100, 100, 175), CustomizationTab, "tab"));

		GUIDropMenus[ImpulseKey_DM]->SetMainItem(MyYAML::GetValueFromNode<std::string>("Customizables", "Vehicle_Impulse_Key").c_str());
		GUIDropMenus[InstantStopKey_DM]->SetMainItem(MyYAML::GetValueFromNode<std::string>("Customizables", "Vehicle_Instant_Stop_Key").c_str());
		GUIDropMenus[OpenMenuKey_DM]->SetMainItem(MyYAML::GetValueFromNode<std::string>("Customizables", "Menu_Key").c_str());
		GUIDropMenus[KillAllPeds_DM]->SetMainItem(MyYAML::GetValueFromNode<std::string>("Customizables", "Kill_All_Peds_Key").c_str());

		//MAIN TAB
		GID FullGodMode_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 10, 0, 0), "Full God Mode", "full_godmode", Features::IsFullGodMode = MyYAML::GetValueFromNode<bool>("Main", "Full_God_Mode"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID GodMode_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 30, 0, 0), "Broken lol", "asm_godmode", Features::IsGodMode, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		//GID FallFromVehicle_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 50, 0, 0), "Developing...", "fallfromvehicle", Features::FallFromVehicle, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID InvisiblePlayer_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 70, 0, 0), "Invisible Player", "invisibleplayer", Features::InvisiblePlayer, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID InvisibleVehicle_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 90, 0, 0), "Invisible Vehicle", "invisiblevehicle", Features::InvisibleVehicle, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID FastSwimSprint_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 110, 0, 0), "Fast Swim & Sprint", "fastswimetc", Features::FastSwimSprint = MyYAML::GetValueFromNode<bool>("Main", "Fast_Movement"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID NeverWanted_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 130, 0, 0), "Never Wanted", "neverwanted", Features::NeverWanted, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID AlwaysWanted_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 150, 0, 0), "Always Wanted", "alwayswanted", Features::AlwaysWanted, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID SuperJump_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 170, 0, 0), "Super Jump", "superjump", Features::SuperJump, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID ExplosiveMelee_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 190, 0, 0), "Explosive Melee", "explosivemelee", Features::ExplosiveMelee, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID FireAmmo_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 210, 0, 0), "Fire Ammo", "fireammo", Features::FireAmmo, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));
		GID ExplosiveAmmo_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 230, 0, 0), "Explosive Ammo", "explosiveammo", Features::ExplosiveAmmo, Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), MainTab, "tab"));

		//GID RPMultiplier_PB = GUIElements::GUICreateProgressBar(new CProgressBar("rpmultiplier", Rect(10, 260, 200, 5), "RP Multiplier: %.2f", 1.f, Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		GID DamageMod_PB = GUIElements::GUICreateProgressBar(new CProgressBar("damagemod", Rect(10, 290, 200, 5), "Damage Mod: %.2f", Features::fDamageMod = MyYAML::GetValueFromNode<float>("Main", "Damage_Mod"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		GID VehImpulse_PB = GUIElements::GUICreateProgressBar(new CProgressBar("vehimpulse", Rect(225, 50, 175, 5), "Vehicle Impulse: %.2f", Features::fVehImpulse = MyYAML::GetValueFromNode<float>("Main", "Vehicle_Impulse"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		GID MeleeDamage_PB = GUIElements::GUICreateProgressBar(new CProgressBar("meleedamage", Rect(225, 80, 175, 5), "Melee Damage: %.2f", Features::fMeleeDamage = MyYAML::GetValueFromNode<float>("Main", "Melee_Damage"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		GID VehicleGravity_PB = GUIElements::GUICreateProgressBar(new CProgressBar("vehiclegravity", Rect(225, 110, 175, 5), "Vehicle Gravity: %.1f", Features::fVehGravity = MyYAML::GetValueFromNode<float>("Main", "Vehicle_Gravity"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		GID PedAmount_PB = GUIElements::GUICreateProgressBar(new CProgressBar("pedamount", Rect(225, 140, 175, 5), "Ped Amount: %.2f", MyYAML::GetValueFromNode<float>("Main", "Ped_Amount"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		GID VehicleAmount_PB = GUIElements::GUICreateProgressBar(new CProgressBar("vehicleamount", Rect(225, 170, 175, 5), "Vehicle Amount: %.2f", MyYAML::GetValueFromNode<float>("Main", "Vehicle_Amount"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		GID VehicleDeformation_PB = GUIElements::GUICreateProgressBar(new CProgressBar("vehdeformation", Rect(225, 200, 175, 5), "Vehicle Deformation: %.1f", Features::fDeformation, Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));
		//GID SurvivalCashModifier_PB = GUIElements::GUICreateProgressBar(new CProgressBar("survivalcash", Rect(225, 230, 175, 5), "Coming soon %.1f", 1.f, Color(0, 255, 0, 255), Color(100, 100, 100, 175), MainTab, "tab"));

		GID GiveHealth_BTN = GUIElements::GUICreateButton(new CButton("givehparmor", Rect(250, 40, 125, 25), "Fill HP & Armor", Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 255, 0, 175), -1, MainTab, "tab"));

		//WEAPONS TAB
		GID NoReload_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 10, 0, 0), "Fast Reload", "fastreload", Features::SuperReload = MyYAML::GetValueFromNode<bool>("Weapons", "Fast_Reload"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), WeaponsTab, "tab"));
		GID SuperImpulse_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 30, 0, 0), "Super Impulse", "superimpulse", Features::SuperImpulse = MyYAML::GetValueFromNode<bool>("Weapons", "Super_Impulse"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), WeaponsTab, "tab"));
		GID UltraPenetration_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 50, 0, 0), "Ultra Penetration", "ultrapenetration", Features::UltraPenetration = MyYAML::GetValueFromNode<bool>("Weapons", "Ultra_Penetration"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), WeaponsTab, "tab"));
		GID InstantKill_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 70, 0, 0), "No Spread", "nospread", Features::NoSpread = MyYAML::GetValueFromNode<bool>("Weapons", "No_Spread"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), WeaponsTab, "tab"));
		GID NoRecoil_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 90, 0, 0), "No Recoil", "norecoil", Features::NoRecoil = MyYAML::GetValueFromNode<bool>("Weapons", "No_Recoil"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), WeaponsTab, "tab"));

		GID AimingFOV_PB = GUIElements::GUICreateProgressBar(new CProgressBar("aimingfov", Rect(175, 20, 175, 5), "Aiming FOV: %.0f", Features::fAimingFOV = MyYAML::GetValueFromNode<float>("Weapons", "Aiming_FOV"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), WeaponsTab, "tab"));

		CDropMenuElements* WeaponsAvailable = new CDropMenuElements("WeaponList");
		WeaponsAvailable->InsertItem("Baseball Bat", WEAPON_BAT);
		WeaponsAvailable->InsertItem("Little Knife", WEAPON_KNIFE);
		WeaponsAvailable->InsertItem("Nightstick", WEAPON_NIGHTSTICK);
		WeaponsAvailable->InsertItem("Crowbar", WEAPON_CROWBAR);
		WeaponsAvailable->InsertItem("Golf Stick", WEAPON_GOLFCLUB);
		WeaponsAvailable->InsertItem("Bottle", WEAPON_BOTTLE);
		WeaponsAvailable->InsertItem("Dagger", WEAPON_DAGGER);
		WeaponsAvailable->InsertItem("Hatchet", WEAPON_HATCHET);
		WeaponsAvailable->InsertItem("Knuckledusters", WEAPON_KNUCKLE);
		WeaponsAvailable->InsertItem("Machete", WEAPON_MACHETE);
		WeaponsAvailable->InsertItem("Hammer", WEAPON_HAMMER);
		WeaponsAvailable->InsertItem("Flashlight", WEAPON_FLASHLIGHT);
		WeaponsAvailable->InsertItem("Switchblade", WEAPON_SWITCHBLADE);
		WeaponsAvailable->InsertItem("Pistol", WEAPON_PISTOL);
		WeaponsAvailable->InsertItem("Combat Pistol", WEAPON_COMBATPISTOL);
		WeaponsAvailable->InsertItem("AP Pistol", WEAPON_APPISTOL);
		WeaponsAvailable->InsertItem("Tazer", WEAPON_STUNGUN);
		WeaponsAvailable->InsertItem("Deagle", WEAPON_PISTOL50);
		WeaponsAvailable->InsertItem("SNS Pistol", WEAPON_SNSPISTOL);
		WeaponsAvailable->InsertItem("Heavy Pistol", WEAPON_HEAVYPISTOL);
		WeaponsAvailable->InsertItem("Vintage Pistol", WEAPON_VINTAGEPISTOL);
		WeaponsAvailable->InsertItem("Flare Gun", WEAPON_FLAREGUN);
		WeaponsAvailable->InsertItem("Marksman Pistol", WEAPON_MARKSMANPISTOL);
		WeaponsAvailable->InsertItem("Revolver", WEAPON_REVOLVER);
		WeaponsAvailable->InsertItem("Micro SMG", WEAPON_MICROSMG);
		WeaponsAvailable->InsertItem("SMG", WEAPON_SMG);
		WeaponsAvailable->InsertItem("Assault SMG", WEAPON_ASSAULTSMG);
		WeaponsAvailable->InsertItem("PDW", WEAPON_COMBATPDW);
		WeaponsAvailable->InsertItem("TEC-9", WEAPON_TEC9);
		WeaponsAvailable->InsertItem("Pump Shotgun", WEAPON_PUMPSHOTGUN);
		WeaponsAvailable->InsertItem("Sawed-Off", WEAPON_SAWNOFFSHOTGUN);
		WeaponsAvailable->InsertItem("Assault Shotgun", WEAPON_ASSAULTSHOTGUN);
		WeaponsAvailable->InsertItem("Bullpup Shotgun", WEAPON_BULLPUPSHOTGUN);
		WeaponsAvailable->InsertItem("Musket", WEAPON_MUSKET);
		WeaponsAvailable->InsertItem("Heavy Shotgun", WEAPON_HEAVYSHOTGUN);
		WeaponsAvailable->InsertItem("Double Barreled", WEAPON_DOUBLEBARRELED);
		WeaponsAvailable->InsertItem("Assault Rifle", WEAPON_ASSAULTRIFLE);
		WeaponsAvailable->InsertItem("Carbine Rifle", WEAPON_CARBINERIFLE);
		WeaponsAvailable->InsertItem("Advanced Rifle", WEAPON_ADVANCEDRIFLE);
		WeaponsAvailable->InsertItem("Special Carbine", WEAPON_SPECIALCARBINE);
		WeaponsAvailable->InsertItem("Bullpup Rifle", WEAPON_BULLPUPRIFLE);
		WeaponsAvailable->InsertItem("Compact Rifle", WEAPON_COMPACTRIFLE);
		WeaponsAvailable->InsertItem("Shrewsbury MG", WEAPON_MG);
		WeaponsAvailable->InsertItem("Combat MG", WEAPON_COMBATMG);
		WeaponsAvailable->InsertItem("Gusenberg", WEAPON_GUSENBERG);
		WeaponsAvailable->InsertItem("Sniper Rifle", WEAPON_SNIPERRIFLE);
		WeaponsAvailable->InsertItem("Heavy Sniper", WEAPON_HEAVYSNIPER);
		WeaponsAvailable->InsertItem("Marksman Rifle", WEAPON_MARKSMANRIFLE);
		WeaponsAvailable->InsertItem("RPG", WEAPON_RPG);
		WeaponsAvailable->InsertItem("Grenade Launcher", WEAPON_GRENADELAUNCHER);
		WeaponsAvailable->InsertItem("Minigun", WEAPON_MINIGUN);
		WeaponsAvailable->InsertItem("Firework Launcher", WEAPON_FIREWORK);
		WeaponsAvailable->InsertItem("Railgun", WEAPON_RAILGUN);
		WeaponsAvailable->InsertItem("Heat RPG", WEAPON_HOMINGLAUNCHER);
		WeaponsAvailable->InsertItem("Grenade", WEAPON_GRENADE);
		WeaponsAvailable->InsertItem("Tear Gas", WEAPON_SMOKEGRENADE);
		WeaponsAvailable->InsertItem("Molotov", WEAPON_MOLOTOV);
		WeaponsAvailable->InsertItem("Sticky Bomb", WEAPON_STICKYBOMB);
		WeaponsAvailable->InsertItem("Mine", WEAPON_PROXMINE);
		WeaponsAvailable->InsertItem("Snowballs", WEAPON_SNOWBALL);
		WeaponsAvailable->InsertItem("Petrol Can", WEAPON_PETROLCAN);
		WeaponsAvailable->InsertItem("Dog Ball", WEAPON_BALL);
		WeaponsAvailable->InsertItem("Fire Extinguisher", WEAPON_FIREEXTINGUISHER);
		WeaponsAvailable->InsertItem("Parachute", WEAPON_PARACHUTE);
		WeaponsAvailable->InsertItem("Briefcase", WEAPON_BRIEFCASE);
		WeaponsAvailable->InsertItem("Garbage Bag", WEAPON_GARBAGEBAG);
		WeaponsAvailable->InsertItem("Handcuffs", WEAPON_HANDCUFFS);

		GID GiveWeapon_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(10, 160, 40, 0), "weaponsdm", "Weapons", WeaponsAvailable, Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), WeaponsTab, "tab", "All Weapons"));

		CDropMenuElements* PlayersOnline = new CDropMenuElements("Players Online");
		PlayersOnline->InsertItem("Me");

		GID Players_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(155, 160, 40, 0), "playersweaponsdm", "Players Online", PlayersOnline, Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), WeaponsTab, "tab", "Players List"));

		GID GiveWeapon_BTN = GUIElements::GUICreateButton(new CButton("GiveWeaponBTN", Rect(345, 160, 50, 30), "Give", Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 255, 0, 175), GiveWeapon_DM, WeaponsTab, "tab"));
		GID GiveAllWeapon_BTN = GUIElements::GUICreateButton(new CButton("GiveAllWeaponBTN", Rect(340, 200, 60, 30), "Give All", Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 255, 0, 175), -1, WeaponsTab, "tab"));

		//TELEPORT TAB
		CDropMenuElements* TeleportBookMark = new CDropMenuElements("Teleports Places");
		TeleportBookMark->InsertItem("Michael's Home");
		TeleportBookMark->InsertItem("Trevor's Home");
		TeleportBookMark->InsertItem("Franklin's Home");
		TeleportBookMark->InsertItem("Airport");
		TeleportBookMark->InsertItem("FIB Building");
		TeleportBookMark->InsertItem("IAA Office");
		TeleportBookMark->InsertItem("Mount Chiliad");
		TeleportBookMark->InsertItem("Bank Tower");

		for (GID i = 0; i < MyYAML::GetNodeSize("Teleport_Bookmark"); i++)
		{
			std::string TeleportIndexName = "Teleport_" + std::to_string(i + 1);

			std::string TeleportName = MyYAML::GetValueFromArrayNode<std::string>("Teleport_Bookmark", TeleportIndexName, 3);

			Vector3 TeleportPosition = Vector3(MyYAML::GetValueFromArrayNode<float>("Teleport_Bookmark", TeleportIndexName, 0),
											   MyYAML::GetValueFromArrayNode<float>("Teleport_Bookmark", TeleportIndexName, 1),
											   MyYAML::GetValueFromArrayNode<float>("Teleport_Bookmark", TeleportIndexName, 2));

			TeleportBookMark->InsertItem(TeleportName, TeleportPosition, TRUE);
		}

		GID TeleportBookmark_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(10, 40, 0, 0), "teleportdm", "Teleport Bookmark", TeleportBookMark, Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), TeleportTab, "tab", "Default Locations"));
		GID PlayersTeleportList_DM = GUIElements::GUICreateDropMenu(new CDropMenu(Rect(195, 40, 0, 0), "tptoplaya", "Teleport To Player", PlayersOnline, Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 100, 255, 150), TeleportTab, "tab", "Players List"));

		GID ButtonTeleportToPlayer_BTN = GUIElements::GUICreateButton(new CButton("TPPlayerButton", Rect(380, 40, 50, 30), "GO!", Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 255, 0, 175), PlayersTeleportList_DM, TeleportTab, "tab"));
		GID Waypoint_BTN = GUIElements::GUICreateButton(new CButton("waypointtp", Rect(10, 200, 75, 30), "Waypoint", Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(0, 0, 0, 0), Color(0, 255, 0, 175), -1, TeleportTab, "tab"));

		//ESP TAB
		GID Enable_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 10, 0, 0), "Enable", "enableesp", Features::ESP = MyYAML::GetValueFromNode<bool>("ESP", "Enable"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), ESPTab, "tab"));
		GID Boxes3D_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 30, 0, 0), "3D Boxes", "3dboxes", Features::Boxes3D = MyYAML::GetValueFromNode<bool>("ESP", "Boxes3D"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), ESPTab, "tab"));
		GID ShowPeds_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 50, 0, 0), "Show Peds", "showpeds", Features::ShowPeds = MyYAML::GetValueFromNode<bool>("ESP", "Show_Peds"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), ESPTab, "tab"));
		GID ShowPlayers_CB = GUIElements::GUICreateCheckBox(new CCheckBox(Rect(10, 70, 0, 0), "Show Players", "showplayers", Features::ShowPlayers = MyYAML::GetValueFromNode<bool>("ESP", "Show_Players"), Color(255, 255, 255, 255), Color(255, 0, 0, 255), Color(0, 0, 0, 0), ESPTab, "tab"));

		GID ESPDistance_PB = GUIElements::GUICreateProgressBar(new CProgressBar("espdistance", Rect(150, 20, 175, 5), "ESP Max Distance: %.0f", Features::fESPMaxDistance = MyYAML::GetValueFromNode<float>("ESP", "ESP_Max_Distance"), Color(0, 255, 0, 255), Color(100, 100, 100, 175), ESPTab, "tab"));

		Initialized = TRUE;
	}
}

GID GUIElements::GUICreateWindow(CWindow* data)
{
	GUIWindows[TWindows] = data;
	TWindows++;
	return TWindows - 1;
}

GID GUIElements::GUICreateCheckBox(CCheckBox* data)
{
	GUICheckBoxes[TCheckboxes] = data;
	TCheckboxes++;
	return TCheckboxes - 1;
}

GID GUIElements::GUICreateTab(CTab* data)
{
	std::wstring text = DX11->ConvertToWStr(data->text);
	XMVECTOR size = DX11->DX11Purista->MeasureString(text.c_str());
	data->SizeX = (XMVectorGetX(size) / 2) + 10;

	GUITabs[TTabs] = data;

	if (data->parent != -1)
	{
		if (data->parentType == "window")
		{
			GUIWindows[data->parent]->Tabs[data->windowTabID] = TTabs;
		}
	}
	TTabs++;
	return TTabs - 1;
}

GID GUIElements::GUICreateProgressBar(CProgressBar* data)
{
	XMVECTOR size = DX11->DX11Purista->MeasureString(DX11->ConvertToWStr(data->p_text).c_str());
	data->TextSize = (XMVectorGetX(size) / 2) + 10;

	GUIProgressBars[TProgressBars] = data;
	TProgressBars++;
	return TProgressBars - 1;
}

GID GUIElements::GUICreateLabel(CLabel* data)
{
	GUILabels[TLabels] = data;
	TLabels++;
	return TLabels - 1;
}

GID GUIElements::GUICreateDropMenu(CDropMenu* data)
{
	XMVECTOR size = DX11->DX11Purista->MeasureString(DX11->ConvertToWStr(data->text).c_str());
	data->TextSize = (XMVectorGetX(size) / 2) + 10;
	data->TextSizeY = (XMVectorGetY(size) / 2) + 10;

	GUIDropMenus[TDropMenus] = data;

	TDropMenus++;
	return TDropMenus - 1;
}

GID GUIElements::GUICreateButton(CButton* data)
{
	GUIButtons[TButtons] = data;
	TButtons++;
	return TButtons - 1;
}

std::string CGUI::StrVars(const char* _text, ...)
{
	std::string NewTextCall;
	char TempBuff[512] = { '\0' };
	va_list VAL;
	va_start(VAL, _text);
	vsprintf_s(TempBuff, _text, VAL);
	va_end(VAL);

	NewTextCall = TempBuff;

	return NewTextCall;
}

void CGUI::SaveInClipBoard(const std::string &s)
{
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg) 
	{
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

CCheckBox* CGUI::GetCheckboxFromName(const char* _Name)
{
	for (GID i = 0; i < TCheckboxes; i++)
	{
		if (GUICheckBoxes[i]->Name == _Name) return GUICheckBoxes[i];
	}
	return nullptr;
}

CDropMenu* CGUI::GetDropMenuFromName(const char* _Name)
{
	for (GID i = 0; i < TDropMenus; i++)
	{
		if (GUIDropMenus[i]->Name == _Name) return GUIDropMenus[i];
	}
	return nullptr;
}

/*CProgressBar* CGUI::GetProgressBarFromName(const char* _Name)
{
	for (GID i = 0; i < TProgressBars; i++)
	{
		if (GUIProgressBars[i]->Name == _Name) return GUIProgressBars[i];
	}
	return nullptr;
}*/


//GUI FUNCTIONALITY
//GUI FUNCTIONALITY
float co = 0.03f;

void CGUI::RefreshCursor()
{
	POINT Pos;
	GetCursorPos(&Pos);
	CursorPos = Vector2(Pos.x - DX11->ScreenX, Pos.y - DX11->ScreenY); 

	if (GetAsyncKeyState(VK_F6))
	{
		co += 0.0001f;
	}
	if (GetAsyncKeyState(VK_F5))
	{
		co -= 0.0001f;
	}

	//CUSTOM REFRESH CODE
	//CUSTOM REFRESH CODE
	if (CurrentTick - LastTick > 60000) //player weapon list refreshed each 60 seconds
	{
		CDropMenu* PlayerListForWeapons = GetDropMenuFromName("Players Online");
		CDropMenu* PlayerListForTP = GetDropMenuFromName("Teleport To Player");
		PlayerListForWeapons->DeleteAllItems();
		PlayerListForTP->DeleteAllItems();
		
		for (GID i = 0; i < 0x1E; i++)
		{
			CPed* Player = (CPed*)Game::GetPlayerByIndex(i);
			if (Mem::IsValid(Player))
			{
				if (Player->Health >= 50)
				{
					if (Mem::IsValid(Player->PlayerInfo))
						PlayerListForWeapons->ItemsInside->InsertItem(Player->PlayerInfo->PlayerName);
				}
			}
		}
		for (GID i = 0; i < 0x1E; i++)
		{
			CPed* Player = (CPed*)Game::GetPlayerByIndex(i);
			if (Mem::IsValid(Player))
			{
				if (Player->Health >= 50)
				{
					if (Mem::IsValid(Player->PlayerInfo))
						PlayerListForTP->ItemsInside->InsertItem(Player->PlayerInfo->PlayerName);
				}
			}
		}
		
		LastTick = GetTickCount();
	}

	//CUSTOM REFRESH CODE
	//CUSTOM REFRESH CODE

	if (!GetAsyncKeyState(VK_LBUTTON) && MouseLeftPressed) MouseLeftPressed = false;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		//PROGRESS BAR FUNCTION

		for (GID _pb = 0; _pb < TProgressBars; _pb++)
		{
			CProgressBar* bar = GUIProgressBars[_pb];
			Rect r = bar->EventRect;
			Rect r2 = bar->rect;
			float Limit = bar->LimitLeft;
			if (IsCursorHover(Rect(Limit - 10, r.y - 15, r2.sx + 20, r2.sy + 35), bar->Active))
			{
				bar->Progress = CursorPos.x - 2.5f;
				if (bar->Progress < Limit) bar->Progress = Limit;
				if (bar->Progress > Limit + r2.sx - 5) bar->Progress = Limit + r2.sx - 5;

				OnProgressBarMove(_pb);

				GUI.ElementSelected = 1;
				break;
			}
		}

		if (GUI.ElementSelected == -1)  //AVOID MOVING WINDOWS WHEN CLICKING BUTTONS ETC
		{
			//WINDOWS MOVING FUNCTIONS
			for (GID _wi = 0; _wi < TWindows; _wi++) 
			{
				if (IsCursorHover(GUIWindows[_wi]->rect, true))
				{
					if (!MouseLeftPressed) 
					{
						MouseLeftPressed = true;
						LatestCursorPos = CursorPos - Vector2(GUIWindows[_wi]->rect.x, GUIWindows[_wi]->rect.y); 
					}
					GUIWindows[_wi]->rect.x = CursorPos.x - LatestCursorPos.x; 
					GUIWindows[_wi]->rect.y = CursorPos.y - LatestCursorPos.y;
					break;
				}
			}
		}
	}
	else 
	{
		//CURSORHOVER CHECKS COLOR ETC
		for (GID _dd = 0; _dd < TDropMenus; _dd++)
		{
			CDropMenu* DM = GUIDropMenus[_dd];

			if (IsCursorHover(DM->EventRect, DM->IsActive)) DM->BoxColor = DM->HighlightColor;
			else DM->BoxColor = DM->DefaultBoxColor;

			if (DM->IsOpened)
			{
				for (GID i = DM->RollPage; i < DM->RollPage + 4; i++)
				{
					if (i < DM->ItemsInside->Items)
					{
						GID ItemID = (i + 1) - DM->RollPage;
						Rect ItemPos = DM->EventRect + Rect(0, ItemID * DM->EventRect.sy, 0, 0);
						if (IsCursorHover(ItemPos, DM->IsActive))
						{
							DM->ItemSelected = CDropMenu::ItemInfo(DM->ItemsInside->text[i], i - DM->RollPage);
							break;
						}
						else
						{
							if (DM->ItemSelected.ID != -1) DM->ItemSelected = CDropMenu::ItemInfo("", -1);
						}
					}
				}
			}
		}

		for (GID _ta = 0; _ta < TTabs; _ta++)
		{
			CTab* Tab = GUITabs[_ta];

			if (IsCursorHover(Tab->EventRect, true)) Tab->BoxColor = Color(0, 255, 255, 170);
			else Tab->BoxColor = Tab->DefaultBoxColor;
		}

		for (GID _btn = 0; _btn < TButtons; _btn++)
		{
			CButton* Button = GUIButtons[_btn];

			if (IsCursorHover(Button->EventRect, Button->IsActive)) Button->BoxColor = Button->HighlightColor;
			else
			{
				Button->BoxColor = Button->DefaultBoxColor;

				if (Button->IsClicked)  //if cursor is out but the button is up then this will help to reset it
				{
					Button->rect.x -= 2.f;
					Button->rect.y -= 2.f;
					Button->rect.sx += 4.f;
					Button->rect.sy += 4.f;

					GUI.ElementSelected = -1;

					Button->IsClicked = FALSE;
				}
			}
		}
	}
	CurrentTick = GetTickCount();
}

bool CGUI::IsCursorHover(Rect rect, bool IsElementActive)
{
	if (CursorPos.x >= rect.x && CursorPos.x <= rect.x + rect.sx &&
		CursorPos.y >= rect.y && CursorPos.y <= rect.y + rect.sy && IsElementActive)
	{
		return true;
	}
	return false;
}

void CGUI::OnLeftMouseButtonDown()
{
	if (!Features::MenuOpened) return;

	GUI.ElementSelected = -1;

	if (OnClick()) GUI.ElementSelected = 1;

	BOOLEAN EfficientCheck = FALSE;

	for (GID i = 0; i < TButtons; i++)
	{
		CButton* Button = GUIButtons[i];

		if (IsCursorHover(Button->EventRect, Button->IsActive))
		{
			ButtonEvents(Button);
			EfficientCheck = TRUE;

			break;
		}
	}
	if (!EfficientCheck)
	{
		for (GID i = 0; i < TDropMenus; i++) //drop down items selection
		{
			CDropMenu* DM = GUIDropMenus[i];
			if (IsCursorHover(DM->EventRect, DM->IsActive))
			{
				if (DM->IsOpened) DM->IsClosing = true;
				else DM->IsOpening = true;

				EfficientCheck = TRUE;

				break;
			}
			if (DM->IsOpened && !EfficientCheck)
			{
				for (GID i = DM->RollPage; i < DM->RollPage + 4; i++)
				{
					if (i < DM->ItemsInside->Items)
					{
						Rect ItemPos = DM->EventRect + Rect(0, ((i + 1) - DM->RollPage) * DM->EventRect.sy, 0, 0);
						if (IsCursorHover(ItemPos, DM->IsActive))
						{
							OnDropMenuItemClick(DM, i);
							EfficientCheck = TRUE;
							DM->IsClosing = true;

							break;
						}
					}
				}
			}
		}
		for (GID i = 0; i < TCheckboxes; i++)
		{
			CCheckBox* Checkbox = GUICheckBoxes[i];
			if (IsCursorHover(Checkbox->EventRect, Checkbox->IsActive))
			{
				CheckboxEvents(Checkbox);
				EfficientCheck = TRUE;

				break;
			}
		}
	}
	if (EfficientCheck) GUI.ElementSelected = 1;
}

void CGUI::OnLeftMouseButtonUp()
{
	if (!Features::MenuOpened) return;

	if (GUI.ElementSelected >= 0)
	{
		for (GID i = 0; i < TButtons; i++)
		{
			CButton* Button = GUIButtons[i];

			if (IsCursorHover(Rect(Button->EventRect.x, Button->EventRect.y, Button->EventRect.sx, Button->EventRect.sy), Button->IsActive))
			{
				Button->rect.x -= 2.f;
				Button->rect.y -= 2.f;
				Button->rect.sx += 4.f;
				Button->rect.sy += 4.f; 

				Button->IsClicked = FALSE;
			}
		}
		GUI.ElementSelected = -1;
	}
}

void CGUI::OnProgressBarMove(GID ProgressBar)
{
	if (!Features::MenuOpened) return;

	CProgressBar* bar = GUIProgressBars[ProgressBar];
	if (bar->Name == "rpmultiplier")
	{
		float Value = 1.f + ((bar->Progress - bar->LimitLeft) * 0.005115f);
		if (Value >= 1.f && Value <= 2.f)
		{
			Features::fRPMultiplier = Value;
			bar->p_text = GUI.StrVars("RP Multiplier: %.2f", Value);
		}
	}
	else if (bar->Name == "damagemod")
	{
		float Value = 0.72f + ((bar->Progress - bar->LimitLeft) * 0.047583f);
		Features::fDamageMod = Value;
		bar->p_text = GUI.StrVars("Damage Mod: %.2f", Features::fDamageMod);
	}
	else if (bar->Name == "vehimpulse")
	{
		float Value = -100.f + ((bar->Progress - bar->LimitLeft) * 1.176498f);
		Features::fVehImpulse = Value;
		bar->p_text = GUI.StrVars("Vehicle Impulse: %.2f", Features::fVehImpulse);
	}
	else if (bar->Name == "meleedamage")
	{
		float Value = 1.f + ((bar->Progress - bar->LimitLeft) * 5.876474);
		Features::fMeleeDamage = Value;
		bar->p_text = GUI.StrVars("Melee Damage: %.2f", Features::fMeleeDamage);
	}
	else if (bar->Name == "menured") //MENU COLORS
	{
		int Value = (bar->Progress - bar->LimitLeft) * 1.761026f;
		GUIWindows[0]->color.R(Value);
		bar->p_text = GUI.StrVars("Menu Red: %i", Value);
	}
	else if (bar->Name == "menugreen") //MENU COLORS
	{
		int Value = (bar->Progress - bar->LimitLeft) * 1.761026f;
		GUIWindows[0]->color.G(Value);
		bar->p_text = GUI.StrVars("Menu Green: %i", Value);
	}
	else if (bar->Name == "menublue") //MENU COLORS
	{
		int Value = (bar->Progress - bar->LimitLeft) * 1.761026f;
		GUIWindows[0]->color.B(Value);
		bar->p_text = GUI.StrVars("Menu Blue: %i", Value);
	}
	else if (bar->Name == "menualpha") //MENU COLORS
	{
		int Value = (bar->Progress - bar->LimitLeft) * 1.761026f;
		GUIWindows[0]->color.A(Value);
		bar->p_text = GUI.StrVars("Menu Alpha: %i", Value);
	}
	else if (bar->Name == "vehiclegravity")
	{
		float Value = -20.f + (bar->Progress - bar->LimitLeft) * 0.235403f;
		Features::fVehGravity = Value;
		bar->p_text = GUI.StrVars("Vehicle Gravity: %.1f", Value);
	}
	else if (bar->Name == "aimingfov")
	{
		float Value = 10.f + (bar->Progress - bar->LimitLeft) * 0.235903f;
		Features::fAimingFOV = Value;
		bar->p_text = GUI.StrVars("Aiming FOV: %.0f", Value);
	}
	else if (bar->Name == "pedamount")
	{
		float Value = (bar->Progress - bar->LimitLeft) * 0.00589f;
		LocalPlayer::SetPedAmount(Value);
		bar->p_text = GUI.StrVars("Ped Amount: %.2f", Value);
	}
	else if (bar->Name == "vehicleamount")
	{
		float Value = (bar->Progress - bar->LimitLeft) * 0.00589f;
		LocalPlayer::SetVehicleAmount(Value);
		bar->p_text = GUI.StrVars("Vehicle Amount: %.2f", Value);
	}
	else if (bar->Name == "espdistance")
	{
		float Value = (bar->Progress - bar->LimitLeft) * 11.765175f;
		Features::fESPMaxDistance = Value;
		bar->p_text = GUI.StrVars("ESP Max Distance: %.0f", Value);
	}
	else if (bar->Name == "vehdeformation")
	{
		float Value = (bar->Progress - bar->LimitLeft) * 0.589301f;
		Features::fDeformation = Value;
		bar->p_text = GUI.StrVars("Vehicle Deformation: %.1f", Value);
	}
	else if (bar->Name == "survivalcash")
	{
		float Value = 1.f + (bar->Progress - bar->LimitLeft) * 0.0235f;
		if (Value >= 1.f && Value <= 5.5f)
		{
			//Features::fSurvivalCash = Value;
			bar->p_text = GUI.StrVars("Coming Soon", Value);
		}
	}
	
}

void CGUI::OnDropMenuItemClick(CDropMenu* DropMenu, GID index)
{
	if (!Features::MenuOpened) return;

	DropMenu->MainItem = DropMenu->ItemSelected;
	DropMenu->MainItem.ID = index;
	DropMenu->MainItem.bUsingStrText = DropMenu->ItemsInside->UsingStrText[index];
	if (DropMenu->MainItem.bUsingStrText)
		DropMenu->MainItem.Name = DropMenu->ItemsInside->strText[index].c_str();


	if (DropMenu->Name == "Teleport Bookmark")
	{
		if (DropMenu->MainItem.Name == "Michael's Home")
			LocalPlayer::Teleport(Vector3(-812.084656, 179.722183, 72.15923));
		else if (DropMenu->MainItem.Name == "Trevor's Home")
			LocalPlayer::Teleport(Vector3(1981.892822, 3816.623779, 32.30817));
		else if (DropMenu->MainItem.Name == "Franklin's Home")
			LocalPlayer::Teleport(Vector3(6.047129, 533.308960, 175.34393));
		else if (DropMenu->MainItem.Name == "Airport")
			LocalPlayer::Teleport(Vector3(-1148.327271, -2883.376709, 13.94442));
		else if (DropMenu->MainItem.Name == "FIB Building")
			LocalPlayer::Teleport(Vector3(135.947464, -749.110535, 258.15167));
		else if (DropMenu->MainItem.Name == "IAA Office")
			LocalPlayer::Teleport(Vector3(113.713234, -619.143066, 206.04679));
		else if (DropMenu->MainItem.Name == "Mount Chiliad")
			LocalPlayer::Teleport(Vector3(446.700073, 5572.014160, 781.18939));
		else if (DropMenu->MainItem.Name == "Bank Tower")
			LocalPlayer::Teleport(Vector3(-75.030563, -819.588928, 326.17517));
		else
		{
			if (DropMenu->ItemsInside->VarType == "Vector3") //CUSTOM TELEPORTS
				LocalPlayer::Teleport(DropMenu->GetItemDataFromName<Vector3>(DropMenu->MainItem.Name));
		}
	}
}

void CGUI::OnWheelMove(short Dir)
{
	if (!Features::MenuOpened) return;

	for (GID i = 0; i < TDropMenus; i++)
	{
		CDropMenu* DM = GUIDropMenus[i];

		if (DM->IsOpened && IsCursorHover(Rect(DM->EventRect.x, DM->EventRect.y, DM->EventRect.sx, DM->EventRect.sy + (DM->ItemsInside->Items * DM->TextSizeY)), DM->IsActive))
		{
			if (DM->RollPage > 0 && Dir == 0) DM->RollPage--;
			else if (DM->RollPage + 4 < DM->ItemsInside->Items && Dir == -1) DM->RollPage++;
		}
	}
}

void CGUI::ButtonEvents(CButton* btn)
{
	btn->rect.x += 2.f;
	btn->rect.y += 2.f;
	btn->rect.sx -= 4.f;
	btn->rect.sy -= 4.f;	//THIS SHOULD BE CHANGED WITH FASTER OPERATIONS AND FIX RECT STRUCT

	if (btn->LinkedDropMenu == -1) //NORMAL BUTTONS
	{
		if (btn->Name == "givehparmor")
		{
			LocalPlayer::GiveHealthArmor();
		}
		else if (btn->Name == "GiveAllWeaponBTN")
		{
			const char* szPlayerName = GetDropMenuFromName("Players Online")->ItemSelected.Name;
			if (szPlayerName != "Players Online")
			{
				Game::Ped Player = LocalPlayer::GetPlayerPedFromName(szPlayerName);
				if (Player) Game::GiveWeaponsToPlayer(Player);
				else		GUIDropMenus[btn->LinkedDropMenu]->MainItem = CDropMenu::ItemInfo("Players Online", -1);
			}
		}
		else if (btn->Name == "waypointtp")
		{
			if (Game::GetWaypointPosition().Length() > 211)
				LocalPlayer::Teleport(Game::GetWaypointPosition());
		}
	}
	else	//buttons with dropdownmenu linked
	{
		CDropMenu* ButtonDropMenu = GUIDropMenus[btn->LinkedDropMenu];
		if (btn->Name == "TPPlayerButton")
		{
			const char* szPlayerName = GetDropMenuFromName("Teleport To Player")->MainItem.Name;
			if (szPlayerName != "Teleport To Player")
			{
				CPed* Player = LocalPlayer::GetPlayerPTRFromName(szPlayerName);
				if (Mem::IsValid(Player)) LocalPlayer::Teleport(Player->VisualPosition + Vector3(1, 1, 0));
				else					  ButtonDropMenu->MainItem = CDropMenu::ItemInfo("Teleport To Player", -1);
			}
		}
		else if (btn->Name == "GiveWeaponBTN")
		{
			Game::Hash Weapon;

			if (ButtonDropMenu->IsUsingDataAndRead(Weapon))
			{
				const char* szPlayerName = GetDropMenuFromName("Players Online")->MainItem.Name;
				if (szPlayerName != "Players Online")
				{
					Game::Ped Player = LocalPlayer::GetPlayerPedFromName(szPlayerName);
					if (Player) Game::GiveWeaponsToPlayer(Player, Weapon);
					else		ButtonDropMenu->MainItem = CDropMenu::ItemInfo("Players Online", -1);
				}
			}
		}
	}

	btn->IsClicked = TRUE;
	GUI.ElementSelected = 1;
}

void CGUI::CheckboxEvents(CCheckBox* checkbox)
{
	if (checkbox->Name == "full_godmode")
	{
		checkbox->ToggleWithValue(Features::IsFullGodMode);
		GetCheckboxFromName("asm_godmode")->DisableWithValue(Features::IsGodMode);
	}
	else if (checkbox->Name == "asm_godmode")
	{
		//checkbox->ToggleWithValue(Features::IsGodMode);
		//GetCheckboxFromName("full_godmode")->DisableWithValue(Features::IsFullGodMode);
		//LocalPlayer::ToggleASMGodMode(); //EDIT THIS IF U HAVE A FUNCTION HOOK LIBRARY
	}
	else if (checkbox->Name == "fallfromvehicle")
	{
		checkbox->ToggleWithValue(Features::FallFromVehicle);
	}
	else if (checkbox->Name == "invisibleplayer")
	{
		checkbox->ToggleWithValue(Features::InvisiblePlayer);
		//Game::SetEntityVisible(Game::GetPlayerPed(Game::GetPlayerID()), !Features::InvisiblePlayer, TRUE);
	}
	else if (checkbox->Name == "invisiblevehicle")
	{
		checkbox->ToggleWithValue(Features::InvisibleVehicle);
		Game::SetEntityVisible(Game::GetVehiclePedIsIn(Game::GetPlayerPed(Game::GetPlayerID()), TRUE), !Features::InvisibleVehicle, TRUE);
	}
	else if (checkbox->Name == "fastswimetc")
	{
		checkbox->ToggleWithValue(Features::FastSwimSprint);
		LocalPlayer::ToogleSwimSprintVel();
	}
	else if (checkbox->Name == "neverwanted")
	{
		checkbox->ToggleWithValue(Features::NeverWanted);
		GetCheckboxFromName("alwayswanted")->DisableWithValue(Features::AlwaysWanted);
	}
	else if (checkbox->Name == "alwayswanted")
	{
		checkbox->ToggleWithValue(Features::AlwaysWanted);
		GetCheckboxFromName("neverwanted")->DisableWithValue(Features::NeverWanted);
	}
	else if (checkbox->Name == "superjump")
	{
		checkbox->ToggleWithValue(Features::SuperJump);
		GetCheckboxFromName("explosivemelee")->DisableWithValue(Features::ExplosiveMelee);
		GetCheckboxFromName("fireammo")->DisableWithValue(Features::FireAmmo);
		GetCheckboxFromName("explosiveammo")->DisableWithValue(Features::ExplosiveAmmo);
	}
	else if (checkbox->Name == "explosivemelee")
	{
		checkbox->ToggleWithValue(Features::ExplosiveMelee);
		GetCheckboxFromName("superjump")->DisableWithValue(Features::SuperJump);
		GetCheckboxFromName("fireammo")->DisableWithValue(Features::FireAmmo);
		GetCheckboxFromName("explosiveammo")->DisableWithValue(Features::ExplosiveAmmo);
	}
	else if (checkbox->Name == "fireammo")
	{
		checkbox->ToggleWithValue(Features::FireAmmo);
		GetCheckboxFromName("superjump")->DisableWithValue(Features::SuperJump);
		GetCheckboxFromName("explosivemelee")->DisableWithValue(Features::ExplosiveMelee);
		GetCheckboxFromName("explosiveammo")->DisableWithValue(Features::ExplosiveAmmo);
	}
	else if (checkbox->Name == "explosiveammo")
	{
		checkbox->ToggleWithValue(Features::ExplosiveAmmo);
		GetCheckboxFromName("superjump")->DisableWithValue(Features::SuperJump);
		GetCheckboxFromName("explosivemelee")->DisableWithValue(Features::ExplosiveMelee);
		GetCheckboxFromName("fireammo")->DisableWithValue(Features::FireAmmo);
	}
	else if (checkbox->Name == "fastreload")
	{
		checkbox->ToggleWithValue(Features::SuperReload);
	}
	else if (checkbox->Name == "superimpulse")
	{
		checkbox->ToggleWithValue(Features::SuperImpulse);
	}
	else if (checkbox->Name == "ultrapenetration")
	{
		checkbox->ToggleWithValue(Features::UltraPenetration);
	}
	else if (checkbox->Name == "norecoil")
	{
		checkbox->ToggleWithValue(Features::NoRecoil);
	}
	else if (checkbox->Name == "nospread")
	{
		checkbox->ToggleWithValue(Features::NoSpread);
	}
	else if (checkbox->Name == "enableesp")
	{
		checkbox->ToggleWithValue(Features::ESP);
	}
	else if (checkbox->Name == "3dboxes")
	{
		checkbox->ToggleWithValue(Features::Boxes3D);
	}
	else if (checkbox->Name == "showpeds")
	{
		checkbox->ToggleWithValue(Features::ShowPeds);
	}
	else if (checkbox->Name == "showplayers")
	{
		checkbox->ToggleWithValue(Features::ShowPlayers);
	}
	
	
	GUI.ElementSelected = 1;
}

bool CGUI::OnClick()
{
	bool AnythingClicked = false;

	for (GID i = 0; i < TTabs; i++) //OPEN TABS
	{
		if (IsCursorHover(GUITabs[i]->EventRect, true))
		{
			GUIWindows[0]->ActiveTab = i;
			AnythingClicked = true;
			break;
		}
	}

	return AnythingClicked;
}


CWindow* GUIWindows[40];
CCheckBox* GUICheckBoxes[40];
CTab* GUITabs[40];
CProgressBar* GUIProgressBars[40];
CLabel* GUILabels[40];
CDropMenu* GUIDropMenus[40];
CButton* GUIButtons[40];
CGUI GUI;