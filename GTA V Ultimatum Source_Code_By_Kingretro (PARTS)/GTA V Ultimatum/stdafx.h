#pragma once

//#define V64_2015DBG
//#define YAMLDBG

#define V64_2015
//#define DEBUG_CONSOLE
//#define SC_VERSION
#define STEAM_VERSION

#if defined(V64_2015)
#pragma comment (lib, "DirectXTK.lib")
#elif defined(V32_2015)
#pragma comment (lib, "DirectXTK32_2015.lib")
#elif defined(V64_2013)
#pragma comment (lib, "DirectXTK_2.lib")
#elif defined(V64_2015DBG)
#pragma comment (lib, "DirectXTK_64_Debug.lib")
#endif


#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "libyaml-cppmd.lib")

#include <Windows.h>
#include <mutex>
#include <DbgHelp.h>
#include <string>
#include <vector>
#include <stdarg.h>
#include <CommonStates.h>
#include <DDSTextureLoader.h>
#include <Effects.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <PrimitiveBatch.h>
#include <ScreenGrab.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <SpriteFont.h>
#include <VertexTypes.h>
#include <DDSTextureLoader.h>
#include <D3DX11tex.h>
#include <DXGI.h>
#include <D3D11.h>
#include <D3DCompiler.h>
#include <DWrite.h>
#include <d3d9.h>
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <directxcolors.h>
#include <dwmapi.h>
#include <SimpleMath.h>
#include <limits>

#include <ctime>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <thread>
#include <map>
#include <exception>
#include <Capstone\capstone.h>
#include <yaml-cpp\yaml.h>


#include "PolyHook.h"
#include "IMem.h"
#include "Hashes.h"
#include "UCIcon.h"
#include "Cursor.h"
#include "VLogo.h"
#include "Purista.h"
#include "IDX11.h"
#include "GUI.h"
#include "IHook.h"
//#include "HookTypes.h"
#include "Game.h"
#include "FileReader.h"