# BanchouPatcher

BanchouPatcher es una GUI moderna para crear parches para archivos utilizando xdelta3. Esta interfaz puede generar un empaquetado en formato ZIP para su mejor distribución. Evite subir archivos pesados, ahorre ancho de banda y envíe los cambios realizados a sus colegas.

**Desarrollado con Qt6 y licencia GPL-3** - Aprovecha las últimas características de Qt para mejor rendimiento y modernidad, manteniendo compatibilidad total con el ecosistema GPL.

## Licencia y Compatibilidad

- **Licencia**: GNU General Public License v3.0
- **Compatible con**: xdelta3 (tanto versión GPL como Apache 2.0)
- **Código fuente**: 100% compatible con el ecosistema de software libre

## Instrucciones de compilación

### Compilación automática (Recomendado)
    $ ./build-qt6.sh

### Compilación manual
    $ qmake6 BanchouPatcher3.pro
    $ make
    # make install // Opcional

### Verificar dependencias
    $ ./check-deps.sh

El ejecutable se encontrará dentro del directorio del proyecto, o en caso de haberse instalado, en `/usr/bin/BanchouPatcher3`.

## Requisitos

 - **Qt6.0 o superior** con widgets (qt6-base, qt6-tools)
 - qmake6
 - **xdelta3** (cualquier versión compatible)
 - Compilador compatible con C++17

**Nota:** La compresión ZIP usa comandos nativos del sistema:
- **Windows**: PowerShell `Compress-Archive` (incluido en Windows 10+)
- **Linux**: Comando `zip` del sistema (instalable con el gestor de paquetes)

### Instalación de dependencias

#### Ubuntu/Debian:
```bash
sudo apt install qt6-base-dev qt6-tools-dev xdelta3
```

#### Fedora/RHEL:
```bash
sudo dnf install qt6-qtbase-devel qt6-qttools-devel xdelta
```

#### Arch Linux:
```bash
sudo pacman -S qt6-base qt6-tools xdelta3
```

## Paquetes de instalación
BanchouPatcher ya está disponible para Windows. Revisa la sección "Releases" para bajar el paquete correspondiente a tu arquitectura.

Los usuarios de Linux por el momento deberán compilar el código fuente. No es nada complicado, pero en caso de encontrar algún error de compilación, favor de abrir un ticket en "Issues".
