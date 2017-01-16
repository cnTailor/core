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
#pragma once

#include "Settings.h"

#if defined(_WIN32) || defined (_WIN64)
	#include <windows.h>

	#include <tchar.h>
	#include <atlstr.h>

	#include <tchar.h>
	#include <strsafe.h>
	#include <string>
#else
	#include "../../Base/ASCString.h"
#endif


namespace FileSystem {
	class Directory {
	public:
        static LPCTSTR GetCurrentDirectory();
        static String GetCurrentDirectoryS();
		
        static bool			CreateDirectory(LPCTSTR path);
        static bool			CreateDirectory(const String& path);
        static bool			CreateDirectory(String strFolderPathRoot, String strFolderName);
        static CString		CreateDirectoryWithUniqueName (CString & strFolderPathRoot);
        static std::wstring CreateDirectoryWithUniqueName (const std::wstring & strFolderPathRoot);
        static bool			CreateDirectories(LPCTSTR path);

        static void DeleteDirectory(const CString& path, bool deleteRoot = true);

        static StringArray GetFilesInDirectory(LPCTSTR path, const bool& andSubdirectories = false);
        static StringArray GetFilesInDirectory(const String& path, const bool& andSubdirectories = false);

        static int GetFilesCount(const CString& path, const bool& recursive = false);
        
		static CString	GetFolderPath(const CString& path);
        static CString	GetLongPathName_(const CString& fileName);
        static CString	GetTempPath();
        static CString	CreateTempFileWithUniqueName (const CString & strFolderPathRoot, CString Prefix);
		static std::wstring CreateTempFileWithUniqueName (const std::wstring & strFolderPathRoot, std::wstring Prefix);
        static bool		PathIsDirectory(const CString& pathName);

#if defined (_WIN32) || defined(_WIN64)
		static std::wstring GetFolderPath(const std::wstring & strFolderPath);
		static void DeleteDirectory(std::wstring& path, bool deleteRoot = true);
#endif
        static bool IsExist(const std::wstring&  strFileName);
	};
}