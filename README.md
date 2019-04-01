# BanchouPatcher3

BanchouPatcher es una GUI para crear parches para archivos utilizando xdelta3. Esta interfaz puede generar un empaquetado en formato ZIP para su mejor distribución. Evite subir archivos pesados, ahorre ancho de banda y envíe los cambios realizados a sus colegas.

## Instrucciones de compilación

    $ qmake
    $ make
    # make install // Opcional
    
El ejecutable se encontrará dentro del directorio del proyecto, o en caso de haberse instalado, en `/usr/bin/BanchouPatcher3`.

## Requisitos

 - qmake
 - Qt5
 - xdelta3
 - zip (Opcional, necesario para comprimir los scripts y el archivo vcdiff)

## Paquetes de instalación
BanchouPatcher3 ya está disponible para Windows. Revisa la sección "Releases" para bajar el paquete correspondiente a tu arquitectura.

Los usuarios de Linux por el momento deberán compilar el código fuente. No es nada complicado, pero en caso de encontrar algún error de compilación, favor de abrir un ticket en "Issues".
