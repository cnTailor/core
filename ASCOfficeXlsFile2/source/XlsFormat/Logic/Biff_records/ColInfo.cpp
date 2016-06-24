﻿/*
 * (c) Copyright Ascensio System SIA 2010-2016
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at Lubanas st. 125a-25, Riga, Latvia,
 * EU, LV-1021.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include "ColInfo.h"

namespace XLS
{

ColInfo::ColInfo()
{
}


ColInfo::~ColInfo()
{
}


BaseObjectPtr ColInfo::clone()
{
	return BaseObjectPtr(new ColInfo(*this));
}


void ColInfo::writeFields(CFRecord& record)
{
	unsigned short flags = 0;
	SETBIT(flags, 0, fHidden);
	SETBIT(flags, 1, fUserSet);
	SETBIT(flags, 2, fBestFit);
	SETBIT(flags, 3, fPhonetic);
	SETBITS(flags, 8, 10, iOutLevel);
	SETBIT(flags, 12, fCollapsed);
	record << colFirst << colLast << coldx << ixfe << flags;
	record.reserveNunBytes(2); // unused
}


void ColInfo::readFields(CFRecord& record)
{
	unsigned short flags;
	record >> colFirst >> colLast >> coldx >> ixfe >> flags;
	
	fHidden		= GETBIT(flags, 0);
	fUserSet	= GETBIT(flags, 1);
	fBestFit	= GETBIT(flags, 2);
	fPhonetic	= GETBIT(flags, 3);
	iOutLevel	= GETBITS(flags, 8, 10);
	fCollapsed	= GETBIT(flags, 12);
	
	record.skipNunBytes(record.getDataSize() - record.getRdPtr()); // unused
	//0x0600 - 2 bytes; lower - 1 byte
}

} // namespace XLS

