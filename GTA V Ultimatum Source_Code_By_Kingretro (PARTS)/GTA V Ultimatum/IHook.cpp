#include "stdafx.h"

LRESULT __stdcall HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WNDPROC OldWndProc = nullptr;

HWND IHooks::tWindow = nullptr;
BOOLEAN IHooks::KeysPressed[256] = { FALSE };

void IHooks::Initialize(const char* Target)
{
	tWindow = FindWindow(0, Target);
	if (tWindow) OldWndProc = (WNDPROC)SetWindowLongPtr(tWindow, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
}
	
void IHooks::Restore()
{
	SetWindowLongPtr(tWindow, GWLP_WNDPROC, (LONG_PTR)OldWndProc);
}

void bus(float fSpeed)
{
	unsigned int a2 = Game::GetPlayerPed(Game::GetPlayerID());
	if (a2)
	{
		unsigned int a3 = Game::GetVehiclePedIsIn(a2, FALSE);
		if (a3)
		{
			Game::SetVehicleForwardSpeed(a3, fSpeed);
		}
	}
}

void IHooks::HooksInput()
{
	if (GUIElements::Initialized)
	{
		/*auto SetVehicleForwardSpeedFunc = [](float fSpeed)
		{
			if (Game::GetVehiclePedIsIn(Game::GetPlayerPed(Game::GetPlayerID()), FALSE))
			{
				Game::SetVehicleForwardSpeed(Game::GetVehiclePedIsIn(Game::GetPlayerPed(Game::GetPlayerID()), FALSE), fSpeed);
			}
		};

		if (KeysPressed[GUI.GetDataFromDropMenuName<DWORD>("Impulse Key")]) SetVehicleForwardSpeedFunc(Features::fVehImpulse);
		else if (KeysPressed[GUI.GetDataFromDropMenuName<DWORD>("Instant Stop Key")]) SetVehicleForwardSpeedFunc(0);*/
		if (KeysPressed[GUI.GetDataFromDropMenuName<DWORD>("Impulse Key")]) bus(Features::fVehImpulse);
		else if (KeysPressed[GUI.GetDataFromDropMenuName<DWORD>("Instant Stop Key")]) bus(0);


		/*if (KeysPressed[VK_NUMPAD4])
		{
			CPed* me = (CPed*)Game::GetPlayerByIndex(Game::GetPlayerID());
			if (Mem::IsValid(me))
			{
				float rot = acos(me->Navigation->Rotation.x) * 180 / D3DX_PI;

				if (asin(me->Navigation->Rotation.y) * 180 / D3DX_PI < 0) rot *= -1;

				rot = XMConvertToRadians(rot + 90);

				if (Game::GetVehiclePedIsIn(Game::GetPlayerPed(Game::GetPlayerID()), FALSE))
					Game::SetEntityVelocity(Game::GetVehiclePedIsIn(Game::GetPlayerPed(Game::GetPlayerID()), TRUE), PVector3(cos(rot) * 30.f, sin(rot) * 30.f, 0.f));
				else
					Game::SetEntityVelocity(Game::GetPlayerPed(Game::GetPlayerID()), PVector3(cos(rot) * 30.f, sin(rot) * 30.f, 0.f));
			}
		}*/
	}
}


LRESULT __stdcall HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		GUI2::OnMouseMove(GXLPARAM(lParam), GYLPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
		IHooks::KeysPressed[VK_LBUTTON] = TRUE;
		CGUI::OnLeftMouseButtonDown();
		GUI2::LastMousePosition = Vector2(GXLPARAM(lParam), GYLPARAM(lParam));
		break;
	case WM_LBUTTONUP:
		CGUI::OnLeftMouseButtonUp();
		IHooks::KeysPressed[VK_LBUTTON] = FALSE;
		break;
	case WM_RBUTTONDOWN:
		IHooks::KeysPressed[VK_RBUTTON] = TRUE;
		break;
	case WM_RBUTTONUP:
		IHooks::KeysPressed[VK_RBUTTON] = FALSE;
		break;
	case WM_KEYDOWN:
		IHooks::KeysPressed[wParam] = TRUE;

		//CONSOLE KEYS

		if (IHooks::KeysPressed[GUI.GetDataFromDropMenuName<DWORD>("Menu Key")])
		{
			Features::MenuOpened = !Features::MenuOpened;
		}

		if (IHooks::KeysPressed[GUI.GetDataFromDropMenuName<DWORD>("Kill Peds Key")])
		{
			LocalPlayer::KillAllPeds();
		}

		if (IHooks::KeysPressed[VK_F11])
		{
			CPed* me = (CPed*)Game::GetPlayerByIndex(Game::GetPlayerID());
			if (Mem::IsValid(me))
				CGUI::SaveInClipBoard(std::to_string(me->VisualPosition.x) + ", " + std::to_string(me->VisualPosition.y) + ", " + std::to_string(me->VisualPosition.z));
		}

		/*if (IHooks::KeysPressed[VK_F5])
		{
			QWORD Address = Mem::GetBase() + 0xCA13D4; //E124E8
			
			Shoot = new PLH::VEHHook;

			Shoot->SetupHook((BYTE*)Address, (BYTE*)&hkFire, PLH::VEHHook::VEHMethod::INT3_BP);
			Shoot->Hook();
			Fire = Shoot->GetOriginal<Fire_t>();

			Debug::Log(Debug::ErrorType::NORMAL, "Hooked");
		}
		if (IHooks::KeysPressed[VK_F6])
		{
			Shoot->UnHook();
			Debug::Log(Debug::ErrorType::NORMAL, "Unhooked");
		}*/


		//TESTING
		//TESTING
		//TESTING
		/*if (IHooks::KeysPressed[VK_F5])
		{
			DX11->TestVar -= 2.f;
			Debug::Log(Debug::ErrorType::NORMAL, "%f", DX11->TestVar);
		}
		if (IHooks::KeysPressed[VK_F6])
		{
			DX11->TestVar += 2.f;
			Debug::Log(Debug::ErrorType::NORMAL, "%f", DX11->TestVar);
		}*/

		/*if (IHooks::KeysPressed[VK_NUMPAD4])
		{
			Vector3 MyPos = ((CPed*)Game::GetPlayerByIndex(Game::GetPlayerID()))->VisualPosition;
			Debug::Log(Debug::ErrorType::NORMAL, "Pos: %.2f %.2f %.2f", MyPos.x, MyPos.y, MyPos.z);
			GUI.SaveInClipBoard(std::to_string(MyPos.x) + ", " + std::to_string(MyPos.y) + ", " + std::to_string(MyPos.z));
		}*/


		break;
	case WM_KEYUP:
		IHooks::KeysPressed[wParam] = FALSE;
		break;
	case WM_MOUSEWHEEL:
		CGUI::OnWheelMove((short)(HIWORD(GET_WHEEL_DELTA_WPARAM(wParam))));
		break;
	default: break;
	}



	/*short Dir = (short)(HIWORD(GET_WHEEL_DELTA_WPARAM(wParam)));
	if (Dir == -1 && Debug::Page < Debug::LogsNumber - 10) Debug::Page++;
	else if (Dir == 0 && Debug::Page > 1) Debug::Page--;*/


	return CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam);
}
