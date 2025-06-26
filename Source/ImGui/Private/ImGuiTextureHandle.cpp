// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#include "ImGuiTextureHandle.h"

#include "ImGuiInteroperability.h"


FImGuiTextureHandle::FImGuiTextureHandle()
	: FImGuiTextureHandle(NAME_None, ImGuiInterops::ToImTextureRef(INDEX_NONE))
{
}

FImGuiTextureHandle::FImGuiTextureHandle(const FName& InName, ImTextureRef InTextureRef)
	: Name(InName)
	, TextureRef(InTextureRef)
{
	const TextureIndex Index = ImGuiInterops::ToTextureIndex(TextureRef);
	checkf((Index == INDEX_NONE) == (Name == NAME_None),
		TEXT("Mismatch between Name and TextureRef parameters, with only one indicating a null handle.")
		TEXT(" Name = '%s', TextureIndex(TextureRef) = %d"), *Name.ToString(), Index);
}

// FImGuiTextureHandle::HasValidEntry() is implemented in ImGuiModule.cpp to get access to FImGuiModuleManager instance
// without referencing in this class.
