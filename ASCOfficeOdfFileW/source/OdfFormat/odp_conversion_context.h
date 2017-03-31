﻿/*
 * (c) Copyright Ascensio System SIA 2010-2017
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
#pragma once

#include "odf_conversion_context.h"
#include "odp_slide_context.h"

namespace cpdoccore { 
namespace odf_writer {

class office_presentation;
class odf_text_context;


class odp_conversion_context : public odf_conversion_context
{
public:
	odp_conversion_context(package::odf_document * outputDocument);
	
	virtual void start_document();
	virtual void end_document();

	void start_slide();
	void end_slide();

	void start_master_slide(std::wstring name);
	void end_master_slide();

///////////////////////////////////////////////////////
	odp_page_state &		current_slide() { return slide_context_.state();}
/////////////////////////////////////////////////////
	virtual void start_text_context();
	virtual void end_text_context();

	virtual odf_drawing_context		* drawing_context()	{return current_slide().drawing_context();}
	virtual odf_text_context		* text_context()	{return current_text_context_;}
	
	void start_drawings();
	void end_drawings();

    virtual void start_image(const std::wstring & image_file_name);

private:
	odp_slide_context			slide_context_;
	
	odf_text_context*			current_text_context_;
	office_presentation*		root_presentation_;
};


}
}
