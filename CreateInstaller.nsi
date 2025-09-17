; BanchouPatcher.nsi - Qt6 Modern Edition
;
; Instalador moderno para BanchouPatcher con Qt6
; - Sin dependencias de zip.exe embebido
; - Usa PowerShell nativo de Windows para compresión
; - Verificación automática de capacidades del sistema
; - GPL-3 compatible
;
; Características modernas:
; * Verificación de Windows 10+ para funciones de compresión
; * Compatible exclusivamente con Qt6
; * Instalación limpia sin archivos ZIP externos
;
; Selecciona ARCH: 32 o 64 según arquitectura de destino

!define BANCHOUVER "4.0.0"
!define QTVER "6"
!define ARP "Software\Microsoft\Windows\CurrentVersion\Uninstall\BanchouPatcher"
!define ARCH "64"

!include "MUI2.nsh"
!include "FileFunc.nsh"
!include "LogicLib.nsh"
!include "WinVer.nsh"

!insertmacro MUI_PAGE_LICENSE "LICENSE"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "SpanishInternational"

;--------------------------------
; Custom Functions
;--------------------------------

; Check PowerShell availability for compression (Windows 10+)
Function CheckPowerShellCompression
  ; Check Windows version - PowerShell Compress-Archive requires Windows 10+
  ${If} ${AtLeastWin10}
    ; PowerShell should be available
    DetailPrint "Windows 10+ detectado - Compresión PowerShell disponible"
  ${Else}
    ; Older Windows versions may not have Compress-Archive
    MessageBox MB_ICONINFORMATION "Nota: Este sistema usa Windows anterior a 10. La funcionalidad de compresión puede requerir herramientas adicionales."
  ${EndIf}
FunctionEnd

;--------------------------------

; The name of the installer
Name "BanchouPatcher ${BANCHOUVER} (Qt${QTVER})"

; The file to write
OutFile "BanchouPatcher-${BANCHOUVER}-Qt${QTVER}-Win${ARCH}.exe"

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
  VIAddVersionKey "ProductName" "BanchouPatcher Qt${QTVER}"
  VIAddVersionKey "CompanyName" "David Kantun"
  VIAddVersionKey "FileDescription" "GUI moderna para xdelta3 con Qt${QTVER}"
  VIAddVersionKey "FileVersion" "${BANCHOUVER}"
  VIAddVersionKey "LegalCopyright" "GPL-3.0 License"
  VIAddVersionKey "Comments" "Sin dependencias de ZIP - Usa PowerShell/zip nativo del sistema"

;--------------------------------

; The stuff to install
Section "BanchouPatcher (requerido)"

  SectionIn RO

  ; Check PowerShell compression capabilities
  Call CheckPowerShellCompression

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  ; Put file there - Actualizar ruta para Qt6
  File /r "..\build-BanchouPatcher-Desktop_Qt_${QTVER}_*_MinGW_${ARCH}_bit-Release\release\*"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\BanchouPatcher "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "${ARP}" "DisplayName" "BanchouPatcher"
  WriteRegStr HKLM "${ARP}" "DisplayVersion" "${BANCHOUVER}"
  WriteRegStr HKLM "${ARP}" "Publisher" "David Kantun"
  WriteRegStr HKLM "${ARP}" "DisplayIcon" '"$INSTDIR\BanchouPatcher.exe"'
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
  CreateShortcut "$SMPROGRAMS\BanchouPatcher\BanchouPatcher.lnk" "$INSTDIR\BanchouPatcher.exe" "" "$INSTDIR\BanchouPatcher.exe" 0
  
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
