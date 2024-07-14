/*
Copyright (C) 2006 StrmnNrmn

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


#include "Base/Types.h"
#include "AboutComponent.h"

#include "UIContext.h"
#include "UIScreen.h"
#include <iostream>
#include "Graphics/ColourValue.h"
#include "Graphics/NativeTexture.h"
#include "Utility/MathUtil.h"
#include "Math/Vector2.h"
#include "DrawTextUtilities.h"

#include "Base/Macros.h"
#include "Utility/Translate.h"
#include "PSPMenu.h"

#include <cstring>

class IAboutComponent : public CAboutComponent
{
	public:

		IAboutComponent( CUIContext * p_context );
		~IAboutComponent();

		// CUIComponent
		virtual void				Update( f32 elapsed_time, const v2 & stick, u32 old_buttons, u32 new_buttons );
		virtual void				Render();

	private:
		std::shared_ptr<CNativeTexture>		mpTexture;
};


CAboutComponent::CAboutComponent( CUIContext * p_context )
:	CUIComponent( p_context )
 {}


CAboutComponent::~CAboutComponent() {}


CAboutComponent *	CAboutComponent::Create( CUIContext * p_context )
{
	return new IAboutComponent( p_context );
}

IAboutComponent::IAboutComponent( CUIContext * p_context )
:	CAboutComponent( p_context )
,	mpTexture( CNativeTexture::CreateFromPng( LOGO_FILENAME, TexFmt_8888 ) )
{}


IAboutComponent::~IAboutComponent() {}

void	IAboutComponent::Update( float elapsed_time [[maybe_unused]], const v2 & stick [[maybe_unused]], u32 old_buttons [[maybe_unused]], u32 new_buttons [[maybe_unused]] ) {}


void	IAboutComponent::Render()
{	
	// // Render Logo	
	// if(mpTexture != NULL)
	// {	
	// 	s16	width =  mpTexture->GetWidth();
	// 	s16	height =  mpTexture->GetHeight();

	// 	f32	desired_height = LIST_TEXT_TOP;
	// 	f32	scale  = desired_height / static_cast<f32>(height);
	// 	v2	wh( static_cast<f32>(width) * scale, static_cast<f32>(height) * scale );
	// 	v2	tl( static_cast<f32>( (SCREEN_WIDTH - wh.x)/2 ), (SCREEN_HEIGHT / 2));

	// 	mpContext->RenderTexture( mpTexture, tl, wh, c32::White );


	// }
	s16 text_top = SCREEN_HEIGHT / 4;

	const s16	line_height =  mpContext->GetFontHeight() + 2;
	// Render the text in the middle of the screen
	s16 y = text_top + 20;

	std::string	version = DAEDALUS_VERSION_TEXT;


	std::string	date = DATE_TEXT + __DATE__;
	mpContext->DrawTextAlign( LIST_TEXT_LEFT, LIST_TEXT_WIDTH, AT_CENTRE, y, version.data(), DrawTextUtilities::TextWhite ); y += line_height;

	// Spacer
	y += line_height;

	mpContext->DrawTextAlign( LIST_TEXT_LEFT, LIST_TEXT_WIDTH, AT_CENTRE, y, date.data(), DrawTextUtilities::TextWhite ); y += line_height;

	// Spacer
	y += line_height;


	for( size_t i = 0; i < std::size( INFO_TEXT ); ++i )
	{
		const char * str( INFO_TEXT[ i ] );

		mpContext->DrawTextAlign( LIST_TEXT_LEFT, LIST_TEXT_WIDTH, AT_CENTRE, y, str, DrawTextUtilities::TextWhite );
		y += line_height;
	}

	mpContext->DrawTextAlign( LIST_TEXT_LEFT, LIST_TEXT_WIDTH, AT_CENTRE, y, URL_TEXT_1, DrawTextUtilities::TextRed, c32( 255,255,255,160 ) );	y += line_height;
	mpContext->DrawTextAlign( LIST_TEXT_LEFT, LIST_TEXT_WIDTH, AT_CENTRE, y, URL_TEXT_2, DrawTextUtilities::TextRed, c32( 255,255,255,255 ) );	y += line_height;
}
