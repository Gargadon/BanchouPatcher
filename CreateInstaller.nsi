; BanchouPatcher3.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install BanchouPatcher3.nsi into a directory that the user selects.
;
; in !define ARCH, please select 32 or 64 depending your detsination processor.

!define BANCHOUVER "3.2.1"
!define ARP "Software\Microsoft\Windows\CurrentVersion\Uninstall\BanchouPatcher"
!define ARCH "32"

!include "MUI2.nsh"
!include "FileFunc.nsh"

!insertmacro MUI_PAGE_LICENSE "LICENSE"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_LANGUAGE "SpanishInternational"

;--------------------------------

; The name of the installer
Name "BanchouPatcher"

; The file to write
OutFile "BanchouPatcher-${BANCHOUVER}-Win${ARCH}.exe"

; The default installation directory
InstallDir $PROGRAMFILES${ARCH}\BanchouPatcher

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\BanchouPatcher" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

;Page components
;Page directory
;Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

;Version Information

  VIProductVersion "${BANCHOUVER}.0"
  VIAddVersionKey "ProductName" "BanchouPatcher"
  VIAddVersionKey "CompanyName" "David Kantun"
  VIAddVersionKey "FileDescription" "xdelta3 GUI"
  VIAddVersionKey "FileVersion" "${BANCHOUVER}"
  VIAddVersionKey "LegalCopyright" ""

;--------------------------------

; The stuff to install
Section "BanchouPatcher (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r "..\build-BanchouPatcher3-Desktop_Qt_5_12_2_MinGW_${ARCH}_bit-Release\release\*"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\BanchouPatcher "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "${ARP}" "DisplayName" "BanchouPatcher"
  WriteRegStr HKLM "${ARP}" "DisplayVersion" "${BANCHOUVER}"
  WriteRegStr HKLM "${ARP}" "Publisher" "David Kantun"
  WriteRegStr HKLM "${ARP}" "DisplayIcon" '"$INSTDIR\BanchouPatcher3.exe"'
  WriteRegStr HKLM "${ARP}" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "${ARP}" "NoModify" 1
  WriteRegDWORD HKLM "${ARP}" "NoRepair" 1
  
  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"
  WriteUninstaller "$INSTDIR\uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\BanchouPatcher"
  CreateShortcut "$SMPROGRAMS\BanchouPatcher\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\BanchouPatcher\BanchouPatcher.lnk" "$INSTDIR\BanchouPatcher3.exe" "" "$INSTDIR\BanchouPatcher3.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "${ARP}"
  DeleteRegKey HKLM SOFTWARE\BanchouPatcher

  ; Remove files and uninstaller
  Delete $INSTDIR\*
  RMDir /r $INSTDIR\iconengines
  RMDir /r $INSTDIR\imageformats
  RMDir /r $INSTDIR\platforms
  RMDir /r $INSTDIR\styles
  RMDir /r $INSTDIR\translations
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\BanchouPatcher\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\BanchouPatcher"
  RMDir "$INSTDIR"

SectionEnd
