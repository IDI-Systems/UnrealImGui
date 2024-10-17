// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#include "ImGuiInputState.h"

#include <algorithm>
#include <limits>
#include <type_traits>


FImGuiInputState::FImGuiInputState()
{
	Reset();
}

void FImGuiInputState::AddCharacter(TCHAR Char)
{
	IO.AddInputCharacter(ImGuiInterops::CastInputChar(Char));
}

void FImGuiInputState::SetKeyDown(const FKeyEvent& KeyEvent, bool bIsDown)
{
	const FKey& Key = KeyEvent.GetKey();
	SetKeyDown(Key, bIsDown);
}

void FImGuiInputState::SetKeyDown(const FKey& Key, bool bIsDown)
{
	const ImGuiKey& ImKey = ImGuiInterops::UnrealToImGuiKey(Key);
	IO.AddKeyEvent(ImKey, bIsDown);

	if (ImKey == ImGuiKey_LeftCtrl || ImKey == ImGuiKey_RightCtrl)
	{
		bIsControlDown = bIsDown;
	}
	else if (ImKey == ImGuiKey_LeftShift || ImKey == ImGuiKey_RightShift)
	{
		bIsShiftDown = bIsDown;
	}
	else if (ImKey == ImGuiKey_LeftAlt || ImKey == ImGuiKey_RightAlt)
    {
        bIsAltDown = bIsDown;
    }
	else if (ImKey == ImGuiKey_LeftSuper || ImKey == ImGuiKey_RightSuper)
	{
		bIsCommandDown = bIsDown;
	}
}

void FImGuiInputState::SetMouseDown(const FPointerEvent& MouseEvent, bool bIsDown)
{
	const uint32 MouseIndex = ImGuiInterops::GetMouseIndex(MouseEvent);
	IO.AddMouseButtonEvent(MouseIndex, bIsDown);
}

void FImGuiInputState::SetMouseDown(const FKey& MouseButton, bool bIsDown)
{
	const uint32 MouseIndex = ImGuiInterops::GetMouseIndex(MouseButton);
	IO.AddMouseButtonEvent(MouseIndex, bIsDown);
}

void FImGuiInputState::AddMouseWheelDelta(float DeltaValue)
{
	IO.AddMouseWheelEvent(0, DeltaValue);
}

void FImGuiInputState::SetMousePosition(const FVector2D& Position)
{
	IO.AddMousePosEvent(Position.X, Position.Y);
	MousePosition = Position;
}

void FImGuiInputState::SetMousePointer(bool bInHasMousePointer)
{
	IO.MouseDrawCursor = bInHasMousePointer;
	bHasMousePointer = bInHasMousePointer;
}

void FImGuiInputState::SetTouchDown(bool bIsDown)
{
	IO.AddMouseButtonEvent(0, bIsDown);
	bTouchDown = bIsDown;
}

void FImGuiInputState::SetTouchPosition(const FVector2D& Position)
{
	IO.AddMousePosEvent(Position.X, Position.Y);
}

void FImGuiInputState::SetGamepadNavigationAxis(const FAnalogInputEvent& AnalogInputEvent, float Value)
{
	ImGuiInterops::SetGamepadNavigationAxis(IO, AnalogInputEvent.GetKey(), Value);
}

void FImGuiInputState::SetKeyboardNavigationEnabled(bool bEnabled)
{
	ImGuiInterops::SetFlag(IO.ConfigFlags, ImGuiConfigFlags_NavEnableKeyboard, bEnabled);
	bKeyboardNavigationEnabled = bEnabled;
}

void FImGuiInputState::SetGamepadNavigationEnabled(bool bEnabled)
{
	ImGuiInterops::SetFlag(IO.ConfigFlags, ImGuiConfigFlags_NavEnableGamepad, bEnabled);
	bGamepadNavigationEnabled = bEnabled;
}

void FImGuiInputState::SetGamepad(bool bInHasGamepad)
{
	ImGuiInterops::SetFlag(IO.BackendFlags, ImGuiBackendFlags_HasGamepad, bInHasGamepad);
	bHasGamepad = bInHasGamepad;
}

void FImGuiInputState::ClearUpdateState()
{
	bTouchProcessed = bTouchDown;
}

void FImGuiInputState::ClearMouseAnalogue()
{
	MousePosition = FVector2D::ZeroVector;
}

void FImGuiInputState::ClearModifierKeys()
{
	bIsControlDown = false;
	bIsShiftDown = false;
	bIsAltDown = false;
	bIsCommandDown = false;
}

