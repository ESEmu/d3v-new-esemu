#pragma once
#ifndef _IDATAPROVIDER_H_
#define _IDATAPROVIDER_H_

#include "..\..\Common\Constants.h"
#include "..\..\LUAEngine\LUASystem.h"

namespace Providers
{
	namespace Items
	{
		#define IPD_LOADERMODE_LUA		1
		#define IPD_LOADERMODE_KIM		2
		#define IPD_LOADERMODE_DATABASE	3

		void				Init(short Modality);

		Constants::itemType GetItemType(unsigned int ItemID);
		bool				IsDecorative(unsigned int ItemID);
		int					GetItemLevel(unsigned int ItemID);
		int					GetItemGrade(unsigned int ItemID);
		int					MapToInvType(unsigned int ItemID, bool IsEquipped, bool IsDecorative);
	}
}

#endif