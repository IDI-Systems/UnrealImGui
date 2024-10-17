// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#include "ImGuiInteroperability.h"


namespace ImGuiInterops
{
	//====================================================================================================
	// Input Mapping
	//====================================================================================================

	static TMap<FKey, int> UnrealToImGuiMouseMap;
	static TMap<FKey, ImGuiKey> UnrealToImGuiKeyMap;

	void SetUnrealKeyMap()
	{
		UnrealToImGuiMouseMap.Add(EKeys::LeftMouseButton, 0);
		UnrealToImGuiMouseMap.Add(EKeys::RightMouseButton, 1);
		UnrealToImGuiMouseMap.Add(EKeys::MiddleMouseButton, 2);
		UnrealToImGuiMouseMap.Add(EKeys::ThumbMouseButton, 3);
		UnrealToImGuiMouseMap.Add(EKeys::ThumbMouseButton2, 4);

		UnrealToImGuiKeyMap.Add(EKeys::LeftControl, ImGuiKey_LeftCtrl);
		UnrealToImGuiKeyMap.Add(EKeys::RightControl, ImGuiKey_RightCtrl);
		UnrealToImGuiKeyMap.Add(EKeys::LeftShift, ImGuiKey_LeftShift);
		UnrealToImGuiKeyMap.Add(EKeys::RightShift, ImGuiKey_RightShift);
		UnrealToImGuiKeyMap.Add(EKeys::LeftAlt, ImGuiKey_LeftAlt);
		UnrealToImGuiKeyMap.Add(EKeys::RightAlt, ImGuiKey_RightAlt);
		UnrealToImGuiKeyMap.Add(EKeys::LeftCommand, ImGuiKey_LeftSuper);
		UnrealToImGuiKeyMap.Add(EKeys::RightCommand, ImGuiKey_RightSuper);

		UnrealToImGuiKeyMap.Add(EKeys::Tab, ImGuiKey_Tab);

		UnrealToImGuiKeyMap.Add(EKeys::Left,  ImGuiKey_LeftArrow);
		UnrealToImGuiKeyMap.Add(EKeys::Right, ImGuiKey_RightArrow);
		UnrealToImGuiKeyMap.Add(EKeys::Up,    ImGuiKey_UpArrow);
		UnrealToImGuiKeyMap.Add(EKeys::Down,  ImGuiKey_DownArrow);

		UnrealToImGuiKeyMap.Add(EKeys::PageUp,   ImGuiKey_PageUp);
		UnrealToImGuiKeyMap.Add(EKeys::PageDown, ImGuiKey_PageDown);
		UnrealToImGuiKeyMap.Add(EKeys::Home,     ImGuiKey_Home);
		UnrealToImGuiKeyMap.Add(EKeys::End,      ImGuiKey_End);
		UnrealToImGuiKeyMap.Add(EKeys::Insert,   ImGuiKey_Insert);
		UnrealToImGuiKeyMap.Add(EKeys::Delete,   ImGuiKey_Delete);

		UnrealToImGuiKeyMap.Add(EKeys::NumLock,    ImGuiKey_NumLock);
		UnrealToImGuiKeyMap.Add(EKeys::ScrollLock, ImGuiKey_ScrollLock);
		UnrealToImGuiKeyMap.Add(EKeys::Pause,      ImGuiKey_Pause);

		UnrealToImGuiKeyMap.Add(EKeys::BackSpace, ImGuiKey_Backspace);
		UnrealToImGuiKeyMap.Add(EKeys::SpaceBar,  ImGuiKey_Space);
		UnrealToImGuiKeyMap.Add(EKeys::Enter,     ImGuiKey_Enter);
		UnrealToImGuiKeyMap.Add(EKeys::Escape,     ImGuiKey_Escape);

		UnrealToImGuiKeyMap.Add(EKeys::A, ImGuiKey_A);
		UnrealToImGuiKeyMap.Add(EKeys::B, ImGuiKey_B);
		UnrealToImGuiKeyMap.Add(EKeys::C, ImGuiKey_C);
		UnrealToImGuiKeyMap.Add(EKeys::D, ImGuiKey_D);
		UnrealToImGuiKeyMap.Add(EKeys::E, ImGuiKey_E);
		UnrealToImGuiKeyMap.Add(EKeys::F, ImGuiKey_F);
		UnrealToImGuiKeyMap.Add(EKeys::G, ImGuiKey_G);
		UnrealToImGuiKeyMap.Add(EKeys::H, ImGuiKey_H);
		UnrealToImGuiKeyMap.Add(EKeys::I, ImGuiKey_I);
		UnrealToImGuiKeyMap.Add(EKeys::J, ImGuiKey_J);
		UnrealToImGuiKeyMap.Add(EKeys::K, ImGuiKey_K);
		UnrealToImGuiKeyMap.Add(EKeys::L, ImGuiKey_L);
		UnrealToImGuiKeyMap.Add(EKeys::M, ImGuiKey_M);
		UnrealToImGuiKeyMap.Add(EKeys::N, ImGuiKey_N);
		UnrealToImGuiKeyMap.Add(EKeys::O, ImGuiKey_O);
		UnrealToImGuiKeyMap.Add(EKeys::P, ImGuiKey_P);
		UnrealToImGuiKeyMap.Add(EKeys::Q, ImGuiKey_Q);
		UnrealToImGuiKeyMap.Add(EKeys::R, ImGuiKey_R);
		UnrealToImGuiKeyMap.Add(EKeys::S, ImGuiKey_S);
		UnrealToImGuiKeyMap.Add(EKeys::T, ImGuiKey_T);
		UnrealToImGuiKeyMap.Add(EKeys::U, ImGuiKey_U);
		UnrealToImGuiKeyMap.Add(EKeys::V, ImGuiKey_V);
		UnrealToImGuiKeyMap.Add(EKeys::W, ImGuiKey_W);
		UnrealToImGuiKeyMap.Add(EKeys::X, ImGuiKey_X);
		UnrealToImGuiKeyMap.Add(EKeys::Y, ImGuiKey_Y);
		UnrealToImGuiKeyMap.Add(EKeys::Z, ImGuiKey_Z);

		UnrealToImGuiKeyMap.Add(EKeys::F1,  ImGuiKey_F1);
		UnrealToImGuiKeyMap.Add(EKeys::F2,  ImGuiKey_F2);
		UnrealToImGuiKeyMap.Add(EKeys::F3,  ImGuiKey_F3);
		UnrealToImGuiKeyMap.Add(EKeys::F4,  ImGuiKey_F4);
		UnrealToImGuiKeyMap.Add(EKeys::F5,  ImGuiKey_F5);
		UnrealToImGuiKeyMap.Add(EKeys::F6,  ImGuiKey_F6);
		UnrealToImGuiKeyMap.Add(EKeys::F7,  ImGuiKey_F7);
		UnrealToImGuiKeyMap.Add(EKeys::F8,  ImGuiKey_F8);
		UnrealToImGuiKeyMap.Add(EKeys::F9,  ImGuiKey_F9);
		UnrealToImGuiKeyMap.Add(EKeys::F10, ImGuiKey_F10);
		UnrealToImGuiKeyMap.Add(EKeys::F11, ImGuiKey_F11);
		UnrealToImGuiKeyMap.Add(EKeys::F12, ImGuiKey_F12);

		UnrealToImGuiKeyMap.Add(EKeys::Zero,  ImGuiKey_0);
		UnrealToImGuiKeyMap.Add(EKeys::One,   ImGuiKey_1);
		UnrealToImGuiKeyMap.Add(EKeys::Two,   ImGuiKey_2);
		UnrealToImGuiKeyMap.Add(EKeys::Three, ImGuiKey_3);
		UnrealToImGuiKeyMap.Add(EKeys::Four,  ImGuiKey_4);
		UnrealToImGuiKeyMap.Add(EKeys::Five,  ImGuiKey_5);
		UnrealToImGuiKeyMap.Add(EKeys::Six,   ImGuiKey_6);
		UnrealToImGuiKeyMap.Add(EKeys::Seven, ImGuiKey_7);
		UnrealToImGuiKeyMap.Add(EKeys::Eight, ImGuiKey_8);
		UnrealToImGuiKeyMap.Add(EKeys::Nine,  ImGuiKey_9);

		UnrealToImGuiKeyMap.Add(EKeys::Equals,       ImGuiKey_Equal);
		UnrealToImGuiKeyMap.Add(EKeys::Comma,        ImGuiKey_Comma);
		UnrealToImGuiKeyMap.Add(EKeys::Period,       ImGuiKey_Period);
		UnrealToImGuiKeyMap.Add(EKeys::Slash,        ImGuiKey_Slash);
		UnrealToImGuiKeyMap.Add(EKeys::LeftBracket,  ImGuiKey_LeftBracket);
		UnrealToImGuiKeyMap.Add(EKeys::RightBracket, ImGuiKey_RightBracket);
		UnrealToImGuiKeyMap.Add(EKeys::Apostrophe,   ImGuiKey_Apostrophe);
		UnrealToImGuiKeyMap.Add(EKeys::Semicolon,    ImGuiKey_Semicolon);

		UnrealToImGuiKeyMap.Add(EKeys::NumPadZero,  ImGuiKey_Keypad0);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadOne,   ImGuiKey_Keypad1);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadTwo,   ImGuiKey_Keypad2);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadThree, ImGuiKey_Keypad3);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadFour,  ImGuiKey_Keypad4);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadFive,  ImGuiKey_Keypad5);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadSix,   ImGuiKey_Keypad6);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadSeven, ImGuiKey_Keypad7);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadEight, ImGuiKey_Keypad8);
		UnrealToImGuiKeyMap.Add(EKeys::NumPadNine,  ImGuiKey_Keypad9);

		UnrealToImGuiKeyMap.Add(EKeys::Multiply, ImGuiKey_KeypadMultiply);
		UnrealToImGuiKeyMap.Add(EKeys::Add,      ImGuiKey_KeypadAdd);
		UnrealToImGuiKeyMap.Add(EKeys::Subtract, ImGuiKey_KeypadSubtract);
		UnrealToImGuiKeyMap.Add(EKeys::Decimal,  ImGuiKey_KeypadDecimal);
		UnrealToImGuiKeyMap.Add(EKeys::Divide,   ImGuiKey_KeypadDivide);

		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_Special_Right, ImGuiKey_GamepadStart);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_Special_Left, ImGuiKey_GamepadBack);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_FaceButton_Bottom, ImGuiKey_GamepadFaceDown);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_FaceButton_Right, ImGuiKey_GamepadFaceRight);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_FaceButton_Top, ImGuiKey_GamepadFaceUp);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_FaceButton_Left, ImGuiKey_GamepadFaceLeft);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_DPad_Left, ImGuiKey_GamepadDpadLeft);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_DPad_Right, ImGuiKey_GamepadDpadRight);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_DPad_Up, ImGuiKey_GamepadDpadUp);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_DPad_Down, ImGuiKey_GamepadDpadDown);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_LeftShoulder, ImGuiKey_GamepadL1);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_RightShoulder, ImGuiKey_GamepadR1);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_LeftTriggerAxis, ImGuiKey_GamepadL2);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_RightTriggerAxis, ImGuiKey_GamepadR2);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_LeftThumbstick, ImGuiKey_GamepadL3);
		UnrealToImGuiKeyMap.Add(EKeys::Gamepad_RightThumbstick, ImGuiKey_GamepadR3);

		UnrealToImGuiMouseMap.Add(EKeys::LeftMouseButton, 0);
		UnrealToImGuiMouseMap.Add(EKeys::RightMouseButton, 1);
		UnrealToImGuiMouseMap.Add(EKeys::MiddleMouseButton, 2);
		UnrealToImGuiMouseMap.Add(EKeys::ThumbMouseButton, 3);
		UnrealToImGuiMouseMap.Add(EKeys::ThumbMouseButton2, 4);
	}

	ImGuiKey UnrealToImGuiKey(const FKey& Key)
	{
		if (UnrealToImGuiKeyMap.Contains(Key))
		{
			return UnrealToImGuiKeyMap[Key];
		}

		UE_LOG(LogImGuiInput, Warning, TEXT("Key '%s' not supported!"), *Key.ToString());
		return ImGuiKey_None;
	}

	int GetMouseIndex(const FKey& MouseButton)
	{
		if (UnrealToImGuiMouseMap.Contains(MouseButton))
		{
			return UnrealToImGuiMouseMap[MouseButton];
		}

		UE_LOG(LogImGuiInput, Warning, TEXT("Mouse button '%s' not supported!"), *MouseButton.ToString());
		return -1;
	}

	EMouseCursor::Type ToSlateMouseCursor(ImGuiMouseCursor MouseCursor)
	{
		switch (MouseCursor)
		{
			case ImGuiMouseCursor_Arrow:
				return EMouseCursor::Default;
			case ImGuiMouseCursor_TextInput:
				return EMouseCursor::TextEditBeam;
			case ImGuiMouseCursor_ResizeAll:
				return EMouseCursor::CardinalCross;
			case ImGuiMouseCursor_ResizeNS:
				return EMouseCursor::ResizeUpDown;
			case ImGuiMouseCursor_ResizeEW:
				return EMouseCursor::ResizeLeftRight;
			case ImGuiMouseCursor_ResizeNESW:
				return EMouseCursor::ResizeSouthWest;
			case ImGuiMouseCursor_ResizeNWSE:
				return EMouseCursor::ResizeSouthEast;
			case ImGuiMouseCursor_None:
			default:
				return EMouseCursor::None;
		}
	}

	namespace
	{
		inline void UpdateAxisValues(ImGuiIO& IO, ImGuiKey Axis, ImGuiKey Opposite, float Value)
		{
			constexpr float AxisInputThreshold = 0.166f;

			// Filter out small values to avoid false positives (helpful in case of worn controllers).
			const float AxisValue = FMath::Max(0.f, Value - AxisInputThreshold);

			IO.AddKeyAnalogEvent(Axis, AxisValue > 0.10f, AxisValue);
			IO.AddKeyAnalogEvent(Opposite, false, 0.f);
		}

		inline void UpdateSymmetricAxis(ImGuiIO& IO, const FKey& Key, const FKey& KeyCondition, ImGuiKey Negative, ImGuiKey Positive, float Value)
		{
			if (Key == KeyCondition)
			{
				if (Value < 0.f)
				{
					UpdateAxisValues(IO, Negative, Positive, -Value);
				}
				else
				{
					UpdateAxisValues(IO, Positive, Negative, Value);
				}
			}
		}
	}

	void SetGamepadNavigationAxis(ImGuiIO& IO, const FKey& Key, float Value)
	{
#define MAP_SYMMETRIC_AXIS(KeyCondition, NegNavIndex, PosNavIndex) UpdateSymmetricAxis(IO, Key, KeyCondition, NegNavIndex, PosNavIndex, Value)

		if (Key.IsGamepadKey())
		{
			MAP_SYMMETRIC_AXIS(EKeys::Gamepad_LeftX, ImGuiKey_GamepadLStickLeft, ImGuiKey_GamepadLStickRight);
			MAP_SYMMETRIC_AXIS(EKeys::Gamepad_LeftY, ImGuiKey_GamepadLStickDown, ImGuiKey_GamepadLStickUp);
			MAP_SYMMETRIC_AXIS(EKeys::Gamepad_RightX, ImGuiKey_GamepadRStickLeft, ImGuiKey_GamepadRStickRight);
			MAP_SYMMETRIC_AXIS(EKeys::Gamepad_RightY, ImGuiKey_GamepadRStickDown, ImGuiKey_GamepadRStickUp);
		}

#undef MAP_SYMMETRIC_AXIS
	}
}
