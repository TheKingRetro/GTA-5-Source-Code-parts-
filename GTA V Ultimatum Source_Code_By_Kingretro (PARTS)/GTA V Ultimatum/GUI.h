#ifndef GUI_INCLUDE
#define GUI_INCLUDE

#pragma once

#include "stdafx.h"

using namespace DirectX::SimpleMath;

extern GID TWindows;
extern GID TCheckboxes;
extern GID TTabs;
extern GID TProgressBars;
extern GID TLabels;
extern GID TDropMenus;
extern GID TButtons;


struct Rect
{
	float x, y, sx, sy;
	Rect() {}
	Rect(float _x, float _y, float _sx, float _sy) { x = _x; y = _y; sx = _sx; sy = _sy; }
	Rect operator - (Rect vec) const
	{
		return Rect(x - vec.x, y - vec.y, sx, sy);
	}
	Rect operator + (Rect vec) const
	{
		return Rect(x + vec.x, y + vec.y, sx, sy);
	}
};

class CButton;
class CCheckBox;
class CDropMenu;

class CGUI
{
public:

	static Vector2 CursorPos;
	Vector2 LatestCursorPos;
	static INT LastClick;
	static INT LastTick;
	static INT CurrentTick;
	GID ElementSelected = 0;
	bool MouseLeftPressed = false;

	static bool OnClick();
	static void ButtonEvents(CButton* btn);
	static void CheckboxEvents(CCheckBox* checkbox);
	static void OnDropMenuItemClick(CDropMenu* DropMenu, GID index);
	static void OnWheelMove(short Dir);
	static void OnLeftMouseButtonDown();
	static void OnLeftMouseButtonUp();
	void OnProgressBarMove(GID ProgressBar);
	void RefreshCursor();
	static bool IsCursorHover(Rect rect, bool IsActive);
	static CCheckBox* GetCheckboxFromName(const char* _Name);
	static CDropMenu* GetDropMenuFromName(const char* _Name);
	//static CProgressBar* GetProgressBarFromName(const char* _Name);
	std::string StrVars(const char* _text, ...);
	static void SaveInClipBoard(const std::string &s);

	template <class vType>
	vType GetDataFromDropMenuName(const char* _Name)
	{
		CDropMenu* DM = GetDropMenuFromName(_Name);
		if (DM->ItemsInside->UsingData)
			return (vType)DM->GetMainItemData<vType>();
		return 0;
	}
};

class CDropMenuElements
{
public:
	const char* text[200];
	std::string strText[200];
	const char* StorageName;
	const char* VarType = "init";
	float MovementPos[200];

	//STORAGE DATA
	DWORD iData[200];
	Vector3 vecData[200];
	BOOLEAN UsingData = FALSE;
	BOOLEAN UsingStrText[200];

	//TOTAL ITEMS
	GID Items = 0;

	CDropMenuElements() {}
	CDropMenuElements(const char* _StorageName) { StorageName = _StorageName; }

	GID InsertItem(const char* _text, DWORD _iData = 0)
	{
		if (_iData != 0)
		{
			if (!UsingData) UsingData = TRUE;
			iData[Items] = _iData;
			if (!strcmp("init", VarType))
				VarType = "DWORD";
		}
		text[Items] = _text;
		UsingStrText[Items] = FALSE;
		Items++;
		return Items - 1;
	}
	GID InsertItem(std::string _text, Vector3 _vecData, BOOLEAN bUsingStrText = FALSE)
	{
		if (!std::isnan(_vecData.x) && !std::isnan(_vecData.y) && !std::isnan(_vecData.z))
		{
			if (!UsingData) UsingData = TRUE;
			vecData[Items] = _vecData;
			if (!strcmp("init", VarType))
				VarType = "Vector3";
			char* nszStr;

			if (bUsingStrText)
			{
				UsingStrText[Items] = bUsingStrText;
				strText[Items] = _text;
			}
			else
			{
				UsingStrText[Items] = FALSE;
				text[Items] = _text.c_str();
			}

			Items++;
			return Items - 1;
		}
		return -1;
	}
	void InsertIntData(DWORD* Data)
	{
		memcpy(iData, Data, sizeof(Data));
	}
	CDropMenuElements* GetCopy()
	{
		CDropMenuElements* newStorage = new CDropMenuElements();
		memcpy(newStorage, this, sizeof(CDropMenuElements));
		return newStorage;
	}
};

class CWindow
{
public:
	Rect rect;
	Rect EventRect;
	Vector2 TabSize;
	Color color;
	Color border;
	GID Tabs[5];
	float borderPx;
	GID parent;
	GID ActiveTab;
	const char* parentType;
	const char* title;

	CWindow() {}
	CWindow(Rect _rect, const char* _title, Vector2 _TabSize, float _borderPx, Color _color, Color _border, GID _ActiveTab, GID _parent, const char* _parentType)
	{
		rect = _rect;
		title = _title;
		TabSize = _TabSize;
		borderPx = _borderPx;
		color = _color;
		border = _border;
		parent = _parent;
		parentType = _parentType;
		ActiveTab = _ActiveTab;
	}
};

extern CWindow* GUIWindows[40];

class CCheckBox
{
public:
	Rect rect;
	Rect EventRect;
	Color TextColor;
	Color IsChecked;
	Color IsNotChecked;
	GID parent;
	const char* Name;
	const char* text;
	const char* parentType;
	BOOLEAN state;
	BOOLEAN IsActive;

	CCheckBox() {}
	CCheckBox(Rect _rect, const char* _text, const char* _Name, bool _state, Color _TextColor, Color _IsChecked, Color _IsNotChecked, GID _parent, const char* _parentType)
	{
		rect = _rect;
		text = _text;
		state = _state;
		Name = _Name;
		TextColor = _TextColor;
		IsChecked = _IsChecked;
		IsNotChecked = _IsNotChecked;
		parent = _parent;
		parentType = _parentType;
		IsActive = FALSE;
	}
	void Toggle()
	{
		state = !state;
	}
	void ToggleWithValue(BOOLEAN& bValue)
	{
		 bValue = !(bValue);
		 state = bValue;
	}
	void DisableWithValue(BOOLEAN& bValue)
	{
		bValue = FALSE;
		state = FALSE;
	}
};

extern CCheckBox* GUICheckBoxes[40];

class CTab
{
public:
	Rect rect;
	Rect EventRect;
	Color TabColor;
	Color TextColor;
	Color DefaultBoxColor;
	Color BoxColor;
	Color BorderColor;
	float SizeX;
	float PosSize;
	GID windowTabID;
	GID parent;
	const char* parentType;
	const char* text;

	CTab() {}
	CTab(Rect _rect, const char* _text, Color _TabColor, Color _TextColor, Color _BorderColor, GID _parent, const char* _parentType, GID _windowTabID)
	{
		rect = _rect;
		text = _text;
		TabColor = _TabColor;
		TextColor = _TextColor;
		BorderColor = _BorderColor;
		BoxColor = Color(0, 0, 0, 0);
		DefaultBoxColor = Color(0, 0, 0, 0);
		parent = _parent;
		parentType = _parentType;
		windowTabID = _windowTabID;
	}
};

extern CTab* GUITabs[40];

class CProgressBar
{
public:
	Rect rect;
	Rect EventRect;
	Color TextColor;
	Color BarColor;
	GID parent;
	bool Active;
	float Progress;
	float Defect;
	float LimitLeft;
	float TextSize;
	const char* Name;
	const char* parentType;
	std::string p_text;

	CProgressBar() {}
	template <class vType>
	CProgressBar(const char* _Name, Rect _rect, const char* _p_text, vType _Progress, Color _TextColor, Color _BarColor, GID _parent, const char* _parentType)
	{
		Name = _Name;
		rect = _rect;
		p_text = _p_text;
		Progress = 20; //((100 * rect.sx) / _Progress)
		TextColor = _TextColor;
		BarColor = _BarColor;
		parent = _parent;
		parentType = _parentType;
		SetProgressValue(_p_text, (vType)_Progress);
	}

	void SetText(std::string szText)
	{
		p_text = szText;
	}

	void SetProgressValue(const char* _NewText, ...)
	{
		std::string NewText;
		char TempBuff[512] = { '\0' };
		va_list VAL;
		va_start(VAL, _NewText);
		vsprintf_s(TempBuff, _NewText, VAL);
		va_end(VAL);

		p_text = TempBuff;
	}
};

extern CProgressBar* GUIProgressBars[40];


class CLabel
{
public:
	Rect rect;
	Color TextColor;
	GID parent;
	const char* parentType;
	bool Active;
	const char* text;

	CLabel() {}
	CLabel(Rect _rect, const char* _text, float _Progress, Color _TextColor, Color _BarColor, GID _parent, const char* _parentType)
	{
		rect = _rect;
		text = _text;
		TextColor = _TextColor;
		parent = _parent;
		parentType = _parentType;
	}
};

extern CLabel* GUILabels[40];

class CDropMenu
{
public:
	struct ItemInfo
	{
	public:
		const char* Name;
		std::string StrName;
		GID ID;
		BOOLEAN bUsingStrText;
		ItemInfo() {}
		ItemInfo(const char* _Name, GID _ID, BOOLEAN _bUsingStrText = FALSE, std::string _StrName = "")
		{
			Name = _Name;
			ID = _ID;
			bUsingStrText = _bUsingStrText;
			StrName = _StrName;
		}
	};
	Rect rect;
	Rect EventRect;
	CDropMenuElements* ItemsInside;
	const char* text;
	const char* text_2;
	const char* Name;
	const char* parentType;
	Color TextColor;
	Color DefaultBoxColor;
	Color BoxColor;
	Color HighlightColor;
	ItemInfo ItemSelected;
	ItemInfo MainItem;
	float TextSize;
	float TextSizeY;
	float ExpandLimit;
	float ArrowRotation;
	int RollPage;
	GID parent;
	bool IsActive;
	bool IsOpening;
	bool IsClosing;
	bool IsOpened;

	CDropMenu() {}
	CDropMenu(Rect _rect, const char* _Name, const char* _text, CDropMenuElements* _ItemsInside, Color _TextColor, Color _BoxColor, Color _HighlightColor, GID _parent, const char* _parentType, const char* _Text_2 = "")
	{
		ItemSelected = ItemInfo("", -1);
		MainItem = ItemInfo("", -1);
		rect = _rect;
		Name = _text;
		text = _text;
		text_2 = _Text_2;
		ItemsInside = _ItemsInside;
		TextColor = _TextColor;
		BoxColor = _BoxColor;
		DefaultBoxColor = _BoxColor;
		HighlightColor = _HighlightColor;
		parent = _parent;
		parentType = _parentType;
		IsOpening = false;
		IsClosing = false;
		IsOpened = false;
		IsActive = false;
		RollPage = 0;
	}
	void DeleteAllItems()
	{
		this->ItemsInside = new CDropMenuElements("DELETED");
	}

	void SetMainItem(const char* _Name)
	{
		for (GID i = 0; i < ItemsInside->Items; i++)
		{
			if (!strcmp(ItemsInside->text[i], _Name))
				this->MainItem = ItemInfo(ItemsInside->text[i], i);
		}
	}

	template <class vType>
	BOOLEAN IsUsingDataAndRead(vType &_Data)
	{
		if (this->MainItem.ID >= 0)
		{
			if (this->ItemsInside->UsingData) //check items that contains data in each item 
			{
				if ((_Data = this->ItemsInside->iData[this->MainItem.ID])) 
					return TRUE;
			}
		}
		return FALSE;
	}

	template <class vType>
	vType GetMainItemData()
	{
		return (vType)this->ItemsInside->iData[this->MainItem.ID];
	}

	template <class vType>
	vType GetItemDataFromName(const char* _Data)
	{
		auto CompareData = [](const char* _VarType, CDropMenu* _this, int i)
		{
			if (_VarType == "DWORD")
				return (vType)_this->ItemsInside->iData[i];
			else if (_VarType == "Vector3")
				return (vType)_this->ItemsInside->vecData[i];
		};

		for (GID i = 0; i < ItemsInside->Items; i++)
		{
			if (!this->ItemsInside->UsingStrText)
			{
				if (!strcmp(this->ItemsInside->text[i], _Data))
					return CompareData(this->ItemsInside->VarType, this, i);
			}
			else
			{
				if (!strcmp(this->ItemsInside->strText[i].c_str(), _Data))
					return CompareData(this->ItemsInside->VarType, this, i);
			}
		}
		return vType();
	}
};

extern CDropMenu* GUIDropMenus[40];


class CButton
{
public:
	Rect rect;
	Rect EventRect;
	const char* Name;
	const char* text;
	const char* parentType;
	Color TextColor;
	Color BorderColor;
	Color DefaultBoxColor;
	Color BoxColor;
	Color HighlightColor;
	GID LinkedDropMenu;
	GID parent;
	BOOLEAN IsActive;
	BOOLEAN IsClicked;

	CButton() {}
	CButton(const char* _Name, Rect _rect, const char* _text, Color _TextColor, Color _BorderColor, Color _BoxColor, Color _HighlightColor, GID _LinkedDropMenu, GID _parent, const char* _parentType)
	{
		Name = _Name;
		rect = _rect;
		text = _text;
		TextColor = _TextColor;
		BorderColor = _BorderColor;
		BoxColor = _BoxColor;
		DefaultBoxColor = _BoxColor;
		HighlightColor = _HighlightColor;
		LinkedDropMenu = _LinkedDropMenu;
		parent = _parent;
		parentType = _parentType;
		IsActive = FALSE;
		IsClicked = FALSE;
	}
};

extern CButton* GUIButtons[40];

class GUIElements
{
public:
	static BOOLEAN Initialized;

	static void InitGUIElements();

	static GID GUICreateWindow(CWindow* data);
	static GID GUICreateCheckBox(CCheckBox* data);
	static GID GUICreateTab(CTab* data);
	static GID GUICreateProgressBar(CProgressBar* data);
	static GID GUICreateLabel(CLabel* data);
	static GID GUICreateDropMenu(CDropMenu* data);
	static GID GUICreateButton(CButton* data);
};



extern CGUI GUI;


#endif