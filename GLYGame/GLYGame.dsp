# Microsoft Developer Studio Project File - Name="GLYGame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GLYGame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GLYGame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GLYGame.mak" CFG="GLYGame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GLYGame - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GLYGame - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GLYGame - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "GLYGame - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\Dll" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GLYGame - Win32 Release"
# Name "GLYGame - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Astar.cpp
# End Source File
# Begin Source File

SOURCE=.\Avatar.cpp
# End Source File
# Begin Source File

SOURCE=.\BackGround.cpp
# End Source File
# Begin Source File

SOURCE=.\Coordiante.cpp
# End Source File
# Begin Source File

SOURCE=.\GamePoint.cpp
# End Source File
# Begin Source File

SOURCE=.\GLYGame.cpp
# End Source File
# Begin Source File

SOURCE=.\GLYGame.rc
# End Source File
# Begin Source File

SOURCE=.\GLYGameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Image.cpp
# End Source File
# Begin Source File

SOURCE=.\INode.cpp
# End Source File
# Begin Source File

SOURCE=.\ISearchable.cpp
# End Source File
# Begin Source File

SOURCE=.\Isometric.cpp
# End Source File
# Begin Source File

SOURCE=.\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\MapUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\PriorityQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\RenderGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchResults.cpp
# End Source File
# Begin Source File

SOURCE=.\Sort.cpp
# End Source File
# Begin Source File

SOURCE=.\Speed.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tile.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlUtil.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Astar.h
# End Source File
# Begin Source File

SOURCE=.\Avatar.h
# End Source File
# Begin Source File

SOURCE=.\BackGround.h
# End Source File
# Begin Source File

SOURCE=.\Coordiante.h
# End Source File
# Begin Source File

SOURCE=.\GamePoint.h
# End Source File
# Begin Source File

SOURCE=.\GLYGame.h
# End Source File
# Begin Source File

SOURCE=.\GLYGameDlg.h
# End Source File
# Begin Source File

SOURCE=.\Image.h
# End Source File
# Begin Source File

SOURCE=.\INode.h
# End Source File
# Begin Source File

SOURCE=.\ISearchable.h
# End Source File
# Begin Source File

SOURCE=.\Isometric.h
# End Source File
# Begin Source File

SOURCE=.\Item.h
# End Source File
# Begin Source File

SOURCE=.\ItemDefinition.h
# End Source File
# Begin Source File

SOURCE=.\MapUtil.h
# End Source File
# Begin Source File

SOURCE=.\Path.h
# End Source File
# Begin Source File

SOURCE=.\PriorityQueue.h
# End Source File
# Begin Source File

SOURCE=.\RenderGrid.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchResults.h
# End Source File
# Begin Source File

SOURCE=.\Sort.h
# End Source File
# Begin Source File

SOURCE=.\Speed.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tile.h
# End Source File
# Begin Source File

SOURCE=.\XmlUtil.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\GLYGame.ico
# End Source File
# Begin Source File

SOURCE=.\res\GLYGame.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
