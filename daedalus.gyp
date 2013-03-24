 {
    'targets': [
      {
        'target_name': 'daedalus',
        'type': 'executable',
        'xcode_settings': {
          'OTHER_CFLAGS': [
            '-Werror',
            '-Wformat=0'
          ],
        },
        'dependencies': [
          'Source/third_party/glfw/glfw.gyp:glfw',
          'Source/third_party/libpng/libpng.gyp:libpng',
          'Source/third_party/webby/webby.gyp:webby',
          'Source/third_party/zlib/zlib.gyp:minizip',
          'Source/third_party/zlib/zlib.gyp:zlib',
        ],
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/AudioToolbox.framework',
          ],
        },
        'include_dirs': [
          'Source',
          'Source/Config/Dev',
        ],
        'defines': [
          'DAEDALUS_ACCURATE_TMEM',
        ],
        'sources': [
          'Source/Core/Cheats.cpp',
          'Source/Core/CPU.cpp',
          'Source/Core/DMA.cpp',
          'Source/Core/Dynamo.cpp',
          'Source/Core/FlashMem.cpp',
          'Source/Core/Interpret.cpp',
          'Source/Core/Interrupts.cpp',
          'Source/Core/JpegTask.cpp',
          'Source/Core/Memory.cpp',
          'Source/Core/PIF.cpp',
          'Source/Core/R4300.cpp',
          'Source/Core/Registers.cpp',
          'Source/Core/ROM.cpp',
          'Source/Core/ROMBuffer.cpp',
          'Source/Core/ROMImage.cpp',
          'Source/Core/RomSettings.cpp',
          'Source/Core/RSP.cpp',
          'Source/Core/RSP_HLE.cpp',
          'Source/Core/Save.cpp',
          'Source/Core/SaveState.cpp',
          'Source/Core/TLB.cpp',
          'Source/Debug/DebugConsoleImpl.cpp',
          'Source/Debug/DebugLog.cpp',
          'Source/Debug/Dump.cpp',
          'Source/DynaRec/BranchType.cpp',
          'Source/DynaRec/Fragment.cpp',
          'Source/DynaRec/FragmentCache.cpp',
          'Source/DynaRec/IndirectExitMap.cpp',
          'Source/DynaRec/StaticAnalysis.cpp',
          'Source/DynaRec/TraceRecorder.cpp',
          'Source/Graphics/ColourValue.cpp',
          'Source/Graphics/TextureTransform.cpp',
          'Source/HLEAudio/ABI1.cpp',
          'Source/HLEAudio/ABI2.cpp',
          'Source/HLEAudio/ABI3.cpp',
          'Source/HLEAudio/ABI3mp3.cpp',
          'Source/HLEAudio/AudioBuffer.cpp',
          'Source/HLEAudio/AudioHLEProcessor.cpp',
          'Source/HLEAudio/HLEMain.cpp',
          'Source/HLEGraphics/BaseRenderer.cpp',
          'Source/HLEGraphics/CachedTexture.cpp',
          'Source/HLEGraphics/ConvertImage.cpp',
          'Source/HLEGraphics/ConvertTile.cpp',
          'Source/HLEGraphics/DLDebug.cpp',
          'Source/HLEGraphics/DLParser.cpp',
          'Source/HLEGraphics/Microcode.cpp',
          'Source/HLEGraphics/RDP.cpp',
          'Source/HLEGraphics/RDPStateManager.cpp',
          'Source/HLEGraphics/TextureCache.cpp',
          'Source/HLEGraphics/TextureInfo.cpp',
          'Source/HLEGraphics/uCodes/Ucode.cpp',
          'Source/Interface/RomDB.cpp',
          'Source/Math/Matrix4x4.cpp',
          'Source/Plugins/GraphicsPlugin.cpp',
          'Source/Test/BatchTest.cpp',
          'Source/Utility/CRC.cpp',
          'Source/Utility/FastMemcpy.cpp',
          'Source/Utility/FramerateLimiter.cpp',
          'Source/Utility/Hash.cpp',
          'Source/Utility/IniFile.cpp',
          'Source/Utility/MemoryHeap.cpp',
          'Source/Utility/Preferences.cpp',
          'Source/Utility/PrintOpCode.cpp',
          'Source/Utility/ROMFile.cpp',
          'Source/Utility/ROMFileCache.cpp',
          'Source/Utility/ROMFileCompressed.cpp',
          'Source/Utility/ROMFileMemory.cpp',
          'Source/Utility/ROMFileUncompressed.cpp',
          'Source/Utility/Stream.cpp',
          'Source/Utility/Synchroniser.cpp',
          'Source/Utility/Timer.cpp',
          'Source/Utility/Translate.cpp',
          'Source/Utility/ZLibWrapper.cpp',
          'Source/ConfigOptions.cpp',
          'Source/System.cpp',
          'Source/SysPSP/Graphics/PngUtilPSP.cpp',

          #FIXME
          'Source/SysW32/Dynarec/x86/AssemblyUtilsX86.cpp',
        ],
        'conditions': [
          ['OS=="win"', {
            'include_dirs': [
              'Source/SysW32/Include',
            ],
            'sources': [
              'Source/SysW32/main.cpp',
              'Source/SysW32/HLEAudio/AudioPluginW32.cpp',
              'Source/SysW32/Debug/DaedalusAssertW32.cpp',
              'Source/SysW32/Debug/DebugConsoleW32.cpp',
              'Source/SysW32/Utility/IOW32.cpp',
              'Source/SysW32/Utility/ThreadW32.cpp',
              'Source/SysW32/Utility/TimingW32.cpp',
            ],
          }],
          ['OS=="mac"', {
            'include_dirs': [
              'Source/SysOSX/Include',
            ],
            'sources': [
              'Source/SysOSX/main.cpp',
              'Source/SysOSX/HLEAudio/AudioPluginOSX.cpp',
              'Source/SysOSX/Debug/DaedalusAssertOSX.cpp',
              'Source/SysOSX/Debug/DebugConsoleOSX.cpp',
              'Source/SysOSX/Debug/WebDebug.cpp',
              'Source/SysOSX/DummyPSP/pspctrl.cpp',
              'Source/SysOSX/DynaRec/CodeBufferManagerOSX.cpp',
              'Source/SysOSX/Graphics/GraphicsContext.cpp',
              'Source/SysOSX/Graphics/NativeTextureOSX.cpp',
              'Source/SysOSX/HLEGraphics/DisplayListDebugger.cpp',
              'Source/SysOSX/HLEGraphics/RendererOSX.cpp',
              'Source/SysOSX/Input/InputManagerOSX.cpp',
              'Source/SysOSX/Plugins/GraphicsPluginOSX.cpp',
              'Source/SysOSX/Utility/IOOSX.cpp',
              'Source/SysOSX/Utility/ThreadOSX.cpp',
              'Source/SysOSX/Utility/TimingOSX.cpp',
            ],
          }],
        ],
      },
    ],
  }
