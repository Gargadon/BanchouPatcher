# BanchouPatcher3

BanchouPatcher es una GUI para crear parches para archivos utilizando xdelta3. Esta interfaz puede generar un empaquetado en formato ZIP para su mejor distribución. Evite subir archivos pesados, ahorre ancho de banda y envíe los cambios realizados a sus colegas.

## Instrucciones de compilación

    $ qmake
    $ make

Los siguientes pasos son opcionales

    # make install
    # cp icons/icon.png /usr/share/icons/hicolor/256x256/apps/BanchouPatcher3.png
    # cp BanchouPatcher3.desktop /usr/share/applications/BanchouPatcher3.desktop
El ejecutable se encontrará dentro del directorio del proyecto, o en caso de haberse instalado, en `/usr/bin/BanchouPatcher3`.

## Requisitos

 - qmake
 - Qt5
 - xdelta3
 - zip (Opcional, necesario para comprimir los scripts y el archivo vcdiff)

## Paquetes de instalación
Próximamente.
