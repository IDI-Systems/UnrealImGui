// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#pragma once

#include "ImGuiInteroperability.h"
#include "Utilities/Arrays.h"

#include <Containers/Array.h>


// Collects and stores input state and updates for ImGui IO.
class FImGuiInputState
{
public:

	// Characters buffer.
	using FCharactersBuffer = TArray<TCHAR, TInlineAllocator<8>>;

	// Create empty state with whole range instance with the whole update state marked as dirty.
	FImGuiInputState();

	// Add a character to the characters buffer. We can store and send to ImGui up to 16 characters per frame. Any
	// character beyond that limit will be discarded.
	// @param Char - Character to add
	void AddCharacter(TCHAR Char);

	// Change state of the key in the keys array and expand range bounding dirty part of the array.
	// @param KeyEvent - Key event representing the key
	// @param bIsDown - True, if key is down
	void SetKeyDown(const FKeyEvent& KeyEvent, bool bIsDown);

	// Change state of the key in the keys array and expand range bounding dirty part of the array.
	// @param Key - Keyboard key
	// @param bIsDown - True, if key is down
	void SetKeyDown(const FKey& Key, bool bIsDown);

	// Change state of the mouse button.
	// @param MouseEvent - Mouse event representing mouse button
	// @param bIsDown - True, if button is down
	void SetMouseDown(const FPointerEvent& MouseEvent, bool bIsDown);

	// Change state of the mouse button.
	// @param MouseButton - Mouse button key
	// @param bIsDown - True, if button is down
	void SetMouseDown(const FKey& MouseButton, bool bIsDown);

	// Add mouse wheel delta.
	// @param DeltaValue - Mouse wheel delta to add
	void AddMouseWheelDelta(float DeltaValue);

	// Get the mouse position.
	const FVector2D& GetMousePosition() const { return MousePosition; }

	// Set the mouse position.
	// @param Position - Mouse position
	void SetMousePosition(const FVector2D& Position);

	// Check whether input has active mouse pointer.
	bool HasMousePointer() const { return bHasMousePointer; }

	// Set whether input has active mouse pointer.
	// @param bHasPointer - True, if input has active mouse pointer
	void SetMousePointer(bool bInHasMousePointer);

	// Check whether touch input is in progress. True, after touch is started until one frame after it has ended.
	// One frame delay is used to process mouse release in ImGui since touch-down is simulated with mouse-down.
	bool IsTouchActive() const { return bTouchDown || bTouchProcessed; }

	// Check whether touch input is down.
	bool IsTouchDown() const { return bTouchDown; }

	// Set whether touch input is down.
	// @param bIsDown - True, if touch is down (or started) and false, if touch is up (or ended)
	void SetTouchDown(bool bIsDown);

	// Get the touch position.
	const FVector2D& GetTouchPosition() const { return TouchPosition; }

	// Set the touch position.
	// @param Position - Touch position
	void SetTouchPosition(const FVector2D& Position);

	// Get Control down state.
	bool IsControlDown() const { return bIsControlDown; }

	// Get Shift down state.
	bool IsShiftDown() const { return bIsShiftDown; }

	// Get Alt down state.
	bool IsAltDown() const { return bIsAltDown; }

	// Get Command down state.
	bool IsCommandDown() const { return bIsCommandDown; }

	// Change state of the navigation input associated with this gamepad axis.
	// @param AnalogInputEvent - Analogue input event with gamepad axis input
	// @param Value - Analogue value that should be set for this axis
	void SetGamepadNavigationAxis(const FAnalogInputEvent& AnalogInputEvent, float Value);

	// Check whether keyboard navigation is enabled.
	bool IsKeyboardNavigationEnabled() const { return bKeyboardNavigationEnabled; }

	// Set whether keyboard navigation is enabled.
	// @param bEnabled - True, if navigation is enabled
	void SetKeyboardNavigationEnabled(bool bEnabled);

	// Check whether gamepad navigation is enabled.
	bool IsGamepadNavigationEnabled() const { return bGamepadNavigationEnabled; }

	// Set whether gamepad navigation is enabled.
	// @param bEnabled - True, if navigation is enabled
	void SetGamepadNavigationEnabled(bool bEnabled);

	// Check whether gamepad is attached.
	bool HasGamepad() const { return bHasGamepad; }

	// Set whether gamepad is attached.
	// @param bInHasGamepad - True, if gamepad is attached
	void SetGamepad(bool bInHasGamepad);

	// Reset the whole input state and mark it as dirty.
	void Reset()
	{
		ResetKeyboard();
		ResetMouse();
	}

	// Reset the keyboard input state and mark it as dirty.
	void ResetKeyboard()
	{
		ClearModifierKeys();
	}

	// Reset the mouse input state and mark it as dirty.
	void ResetMouse()
	{
		ClearMouseAnalogue();
	}

	// Clear part of the state that is meant to be updated in every frame like: accumulators, buffers, navigation data
	// and information about dirty parts of keys or mouse buttons arrays.
	void ClearUpdateState();

	ImGuiIO IO;

private:
	void ClearMouseAnalogue();
	void ClearModifierKeys();

	FVector2D MousePosition = FVector2D::ZeroVector;
	FVector2D TouchPosition = FVector2D::ZeroVector;
	float MouseWheelDelta = 0.f;

	FCharactersBuffer InputCharacters;

	bool bHasMousePointer = false;
	bool bTouchDown = false;
	bool bTouchProcessed = false;

	bool bIsControlDown = false;
	bool bIsShiftDown = false;
	bool bIsAltDown = false;
	bool bIsCommandDown = false;

	bool bKeyboardNavigationEnabled = false;
	bool bGamepadNavigationEnabled = false;
	bool bHasGamepad = false;
};
