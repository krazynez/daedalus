/*
Copyright (C) 2003 Azimer
Copyright (C) 2012 StrmnNrmn

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

//
//	N.B. This source code is derived from Azimer's Audio plugin (v0.55?)
//	and modified by StrmnNrmn to work with Daedalus PSP. Thanks Azimer!
//	Drop me a line if you get chance :)
//

#include "stdafx.h"

#include "Plugins/AudioPlugin.h"
#include "AudioOutput.h"
#include "HLEAudio/audiohle.h"

#include "SysPSP/Utility/JobManager.h"

#include "Core/Interrupt.h"
#include "Core/Memory.h"
#include "Core/ROM.h"
#include "Core/CPU.h"
#include "Core/RSP_HLE.h"

#include "ConfigOptions.h"


class CAudioPluginOSX : public CAudioPlugin
{
private:
	CAudioPluginOSX();
public:
	static CAudioPluginOSX *		Create();

	virtual ~CAudioPluginOSX();
	virtual bool			StartEmulation();
	virtual void			StopEmulation();

	virtual void			DacrateChanged( int SystemType );
	virtual void			LenChanged();
	virtual u32				ReadLength();
	virtual EProcessResult	ProcessAList();
	virtual void			RomClosed();

//			void			SetAdaptFrequecy( bool adapt );

private:
	AudioOutput *			mAudioOutput;
};


EAudioPluginMode gAudioPluginEnabled( APM_DISABLED );
//bool gAdaptFrequency( false );

CAudioPluginOSX::CAudioPluginOSX()
:	mAudioOutput( new AudioOutput )
{
	//mAudioOutput->SetAdaptFrequency( gAdaptFrequency );
	//gAudioPluginEnabled = APM_ENABLED_SYNC; // for testing
}

CAudioPluginOSX::~CAudioPluginOSX()
{
	delete mAudioOutput;
}

CAudioPluginOSX *	CAudioPluginOSX::Create()
{
	return new CAudioPluginOSX();
}

/*
void CAudioPluginOSX::SetAdaptFrequecy( bool adapt )
{
	mAudioOutput->SetAdaptFrequency( adapt );
}
*/

bool CAudioPluginOSX::StartEmulation()
{
	return true;
}

void CAudioPluginOSX::StopEmulation()
{
	Audio_Reset();
	mAudioOutput->StopAudio();
}

void CAudioPluginOSX::DacrateChanged( int SystemType )
{
//	printf( "DacrateChanged( %s )\n", (SystemType == ST_NTSC) ? "NTSC" : "PAL" );
	u32 type = (SystemType == ST_NTSC) ? VI_NTSC_CLOCK : VI_PAL_CLOCK;
	u32 dacrate = Memory_AI_GetRegister(AI_DACRATE_REG);
	u32	frequency = type / (dacrate + 1);

	mAudioOutput->SetFrequency( frequency );
}

void CAudioPluginOSX::LenChanged()
{
	if( gAudioPluginEnabled > APM_DISABLED )
	{
		//mAudioOutput->SetAdaptFrequency( gAdaptFrequency );

		u32		address( Memory_AI_GetRegister(AI_DRAM_ADDR_REG) & 0xFFFFFF );
		u32		length(Memory_AI_GetRegister(AI_LEN_REG));

		u32		result( mAudioOutput->AddBuffer( g_pu8RamBase + address, length ) );

		use(result);
	}
	else
	{
		mAudioOutput->StopAudio();
	}
}

u32 CAudioPluginOSX::ReadLength()
{
	return 0;
}


EProcessResult CAudioPluginOSX::ProcessAList()
{
	Memory_SP_SetRegisterBits(SP_STATUS_REG, SP_STATUS_HALT);

	EProcessResult	result( PR_NOT_STARTED );

	switch( gAudioPluginEnabled )
	{
		case APM_DISABLED:
			result = PR_COMPLETED;
			break;
		case APM_ENABLED_ASYNC:
			DAEDALUS_ERROR("Unimplemented");
			result = PR_STARTED;
			break;
		case APM_ENABLED_SYNC:
			Audio_Ucode();
			result = PR_COMPLETED;
			break;
	}

	return result;
}

void CAudioPluginOSX::RomClosed()
{
	mAudioOutput->StopAudio();
}

CAudioPlugin * CreateAudioPlugin()
{
	return CAudioPluginOSX::Create();
}
