Unreal ImGui
============
[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE.md)

Unreal ImGui is an Unreal Engine 4/5 plug-in that integrates [Dear ImGui](https://github.com/ocornut/imgui) developed by Omar Cornut.

Dear ImGui is an immediate-mode graphical user interface library that is very lightweight and easy to use. It can be very useful when creating debugging tools.

Status
------
- [ImGui `v1.89.7`](https://github.com/ocornut/imgui/releases/tag/v1.89.7)
- [NetImgui `v1.9`](https://github.com/sammyfreg/netImgui/releases/tag/v1.9.0)
- [ImPlot `v0.14+cc5e1daa`](https://github.com/epezent/implot/tree/cc5e1daa5c7f2335a9460ae79c829011dc5cef2d)

Supported Unreal Engine version: `4.26`, `5.0`, `5.1`, `5.2`

_Note: Plugin has been tested and if necessary updated to compile and work with these engine versions. As long as possible we will try to maintain backward compatibility of existing features and possibly but not necessarily when adding new features. When it comes to bare-bone ImGui version it should be at least backward compatible with the engine version 4.15. For NetImgui it needs to be determined._

Fork Information
----------------
Please note that this is a forked project from [segross/UnrealImGui](https://github.com/segross/UnrealImGui) with contributions from [benui-dev/UnrealImGui](https://github.com/benui-dev/UnrealImGui) and [WiggleWizard/UnrealImGui](https://github.com/WiggleWizard/UnrealImGui). We do not take credit for the work they put into making Dear ImGui work in Unreal Engine. The work done by this fork is listed below.

Large portions of this `README.md` have been removed to keep redundant information between the base project and this fork to a minimum. If you wish to read the original `README.md`, please see [UnrealImGui `README.md`](https://github.com/segross/UnrealImGui/blob/master/README.md).

- Updated core source files for **Unreal Engine 5** while maintaining **Unreal Engine 4** compatibility.
- Updated Dear ImGui to `v1.89.7`.
- Added ImPlot `v0.14+cc5e1daa`.
- `ImGui::IsKey*` now functional with all known ImGui keys.
- Updated input handling flow to be [standard compliant](https://github.com/ocornut/imgui/issues/4921) with Dear ImGui 1.87 which makes ImGui react better at low FPS. ~~Will add `IMGUI_DISABLE_OBSOLETE_KEYIO` preprocessor once I've ripped out old style input.~~
- Allowed `UTexture` for Texture Manager so render targets can also be rendered to quads rather than just being limited to using `UTexture2D` instances.
- Added the ability to instruct ImGui context to build custom fonts (like FontAwesome).
- Changed Module Type to `Runtime`.
- Replace `strcpy_s` with `strncpy`.

How to Set up
-------------
On top of reading the base repository's [How to Set up](https://github.com/segross/UnrealImGui/blob/master/README.md#how-to-set-up) segment, you'll need to add the following line to your `[GameName].Build.cs` file otherwise you'll get linking errors:

```cpp
// Tell the compiler we want to import the ImPlot symbols when linking against ImGui plugin 
PrivateDefinitions.Add("IMPLOT_API=DLLIMPORT");
```

# Additional Knowledge

## Using ImPlot

It's pretty easy to use ImPlot, it's pretty much the same drill as using Dear ImGui with the UnrealImGui plugin. You can see documentation on how to use ImPlot here: [ImPlot](https://github.com/epezent/implot).

The only thing you won't need to do is call the `ImPlot::CreateContext()` and `ImPlot::DestroyContext` routines as they're already called when ImGui's context is created within UnrealImGui's guts.

## Drawing a UTextureRenderTarget2D

One might want to render viewports into the world in an ImGui window. You can do this pretty simply by generating a `UTextureRenderTarget2D` then assigning that to a `ASceneCapture2D` actor in your world. Here's some sample code for generating an correctly managing the `UTextureRenderTarget2D`:
```cpp
void Init()
{
    TextureRenderTarget = NewObject<UTextureRenderTarget2D>();
    if(IsValid(TextureRenderTarget))
    {
        TextureRenderTarget->InitAutoFormat(512, 512);
        TextureRenderTarget->UpdateResourceImmediate(true);
    }

    // ... Generate a unique TextureName here
    // Register this render target as an ImGui interop handled texture
    ImGuiTextureHandle = FImGuiModule::Get().FindTextureHandle(TextureName);
    if(!ImGuiTextureHandle.IsValid())
    {
        if(IsValid(TextureRenderTarget))
        {
            ImGuiTextureHandle = FImGuiModule::Get().RegisterTexture(TextureName, TextureRenderTarget, true);
        }
    }
}

~Class()
{
    // Requires releasing to avoid memory leak
    FImGuiModule::Get().ReleaseTexture(ImGuiTextureHandle);
}

void Render()
{
    // Actually submit the draw command to ImGui to render the quad with the texture
    if(ImGuiTextureHandle.IsValid())
    {
        ImGui::Image(ImGuiTextureHandle.GetTextureId(), {512.f, 512.f});
    }
}
```

Then generating the `ASceneCapture2D`:
```cpp
void Init()
{
    FActorSpawnParameters SpawnInfo;
    SceneCapture2D = World->SpawnActor<ASceneCapture2D>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
    SceneCaptureComponent2D->TextureTarget = TextureRenderTarget;
    SceneCaptureComponent2D->UpdateContent();

    // Need to use this in order to force capture to use tone curve and also set alpha to scene alpha (1)
    SceneCaptureComponent2D->CaptureSource = ESceneCaptureSource::SCS_FinalToneCurveHDR;
}
```
How to Set up NetImgui
----------------------

To remotely connect to your application's Imgui content using NetImgui, you need to run the **NetImgui Server application**. The appropriate version can be downloaded [here]("https://raw.githubusercontent.com/wiki/sammyfreg/netImgui/UnrealImgui/NetImguiServer_1_9.zip") and see the source project's [documentation](https://github.com/sammyfreg/netImgui) for instructions on its usage.

Once you establish connection, you can use acces the 'NetImgui' entry in the 'Main Menu' top bar to switch between contexts and modes. In standalone game it should be one context and in the editor one editor context, plus one for each PIE instance. Please, note that all those features are experimental and might evolve. Any input is welcomed.

### Troubleshooting
If you're using a scene capture and your quad is not drawing at all, make sure your scene capture "Capture Source" is set to "Final Color (with tone curve) in Linear sRGB gamut" to avoid alpha being set to 0 (since there's no way to instruct ImGui to ignore alpha without modding the core UnrealImGui plugin).

If you're getting crashes or seg faults during rendering, make sure you're using `UPROPERTY()` on your class variables!

## Adding custom fonts
### FontAwesome
Adding custom fonts is fairly simple. As a more complex and more commonly done, we're going to embed and build FontAwesome 6 into the font atlas. First thing you'll need is a binary C version of the FontAwesome font along with the necessary [companion descriptors](https://github.com/juliettef/IconFontCppHeaders/blob/main/IconsFontAwesome6.h). The descriptors are pre-generated, however if you have a new version of FA you wish to use, then use the Python script in that repository. As for the binary C, you'll need to compile Dear ImGui's [binary_to_compressed_c.cpp](https://github.com/ocornut/imgui/blob/master/misc/fonts/binary_to_compressed_c.cpp).

Once you have the necessary files, you'll need to encode your FontAwesome font using the command:
```
binary_to_compressed_c.exe -nocompress fa-solid-900.ttf FontAwesomeFont > FontAwesomeFont.h
```
The only mandatory field here is `-nocompress` as this instructs the encoder to create an uncompressed binary file (1:1) since currently there's no immediate support for compressed fonts.

Move over your descriptors and your binary C font file to an appropriate location for inclusion in your Unreal Engine project. The following code is how to instruct ImGui to build the font atlas with your FontAwesome font:

```cpp
#include "FontAwesomeFont.h"
#include "IconsFontAwesome6.h"

// Add FontAwesome font glyphs from memory
if(TSharedPtr<ImFontConfig> FAFontConfig = MakeShareable(new ImFontConfig()))
{
    static const ImWchar IconRange[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    
    FAFontConfig->FontDataOwnedByAtlas = false; // Global font data lifetime
    FAFontConfig->FontData             = (void*)FontAwesomeData; // Declared in binary C .h file
    FAFontConfig->FontDataSize         = FontAwesomeSize; // Declared in binary C .h file
    FAFontConfig->SizePixels           = 16;
    FAFontConfig->MergeMode            = true; // Forces ImGui to place this font into the same atlas as the previous font
    FAFontConfig->GlyphRanges          = IconRange; // Required; instructs ImGui to use these glyphs
    FAFontConfig->GlyphMinAdvanceX     = 16.f; // Use for monospaced icons
    FAFontConfig->PixelSnapH           = true; // Better rendering (align to pixel grid)
    FAFontConfig->GlyphOffset          = {0, 3}; // Moves icons around, for alignment with general typesets

    FImGuiModule::Get().GetProperties().AddCustomFont("FontAwesome", FAFontConfig);
    FImGuiModule::Get().RebuildFontAtlas();
}
```

That's it. Make sure you execute the above code once at the beginning of the first ImGui frame (or at any point of your framework where the ImGui context has been initialized correctly) and it should build the main atlas with FontAwesome inside it. ImFontConfig lifetime is currently managed via reference counting (`TSharedPtr`).

### Using the icons
```cpp
#include "IconsFontAwesome6.h"

void OnPaint()
{
    ImGui::Text(ICON_FA_AWARD);
}
```

Pretty simple. Building FStrings that incorporate FontAwesome icons however gets a little trickier:
```cpp
FString Str = "Hello " + FString(UTF8_TO_TCHAR(ICON_FA_WAVE_SQUARE)) " World";
ImGui::TextUnformatted(TCHAR_TO_UTF8(*Str));
```

### More info
 - [Dear ImGui: Using Fonts](https://github.com/ocornut/imgui/blob/master/docs/FONTS.md)
 - [IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders)
 - [FontAwesome with general Dear ImGui](https://pixtur.github.io/mkdocs-for-imgui/site/FONTS/)

# Misc

See also
--------
 - [Original Project by segross](https://github.com/segross/UnrealImGui)
 - [Forked Project by benui-dev](https://github.com/benui-dev/UnrealImGui)
 - [Forked Project by WiggleWizard](https://github.com/WiggleWizard/UnrealImGui)
 - [Dear ImGui](https://github.com/ocornut/imgui)
 - [ImPlot](https://github.com/epezent/implot)
 - [NetImgui](https://github.com/sammyfreg/netImgui)


License
-------
Unreal ImGui (and this fork) is licensed under the MIT License, see LICENSE for more information.
