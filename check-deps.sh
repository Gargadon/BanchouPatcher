#!/bin/bash

echo "🔍 Verificando dependencias de BanchouPatcher..."
echo ""

# Función para verificar comandos
check_command() {
    local cmd=$1
    local name=$2
    local install_hint=$3

    if command -v "$cmd" &> /dev/null; then
        local version=$($cmd --version 2>&1 | head -1)
        echo "✅ $name: $version"
        return 0
    else
        echo "❌ $name: NO ENCONTRADO"
        if [ ! -z "$install_hint" ]; then
            echo "   💡 Instalación: $install_hint"
        fi
        return 1
    fi
}

# Verificar Qt6
echo "📦 Qt6 y herramientas de desarrollo:"
check_command "qmake6" "qmake6" "sudo apt install qt6-tools-dev"
check_command "g++" "G++ Compiler" "sudo apt install build-essential"

echo ""
echo "🛠️  Dependencias de runtime:"
check_command "xdelta3" "xdelta3" "sudo apt install xdelta3"
echo "✅ ZIP compression: Comandos nativos del sistema (PowerShell/zip)"

echo ""
echo "🏗️  Verificando soporte de Qt6..."

# Verificar que Qt6 tiene widgets
if command -v qmake6 &> /dev/null; then
    qt_version=$(qmake6 --version | grep "Using Qt version" | cut -d' ' -f4)
    if [[ "$qt_version" == 6.* ]]; then
        echo "✅ Qt6 version: $qt_version"

        # Verificar que se puede crear un proyecto básico
        temp_dir=$(mktemp -d)
        cd "$temp_dir"
        echo "QT += widgets" > test.pro
        echo "TARGET = test" >> test.pro
        echo "TEMPLATE = app" >> test.pro
        echo "SOURCES += main.cpp" >> test.pro
        echo '#include <QApplication>' > main.cpp
        echo 'int main(int argc, char *argv[]) { QApplication app(argc, argv); return 0; }' >> main.cpp

        if qmake6 test.pro &> /dev/null; then
            echo "✅ Qt6 widgets: Disponible"
        else
            echo "❌ Qt6 widgets: NO DISPONIBLE"
            echo "   💡 Instalación: sudo apt install qt6-base-dev"
        fi

        cd - > /dev/null
        rm -rf "$temp_dir"
    else
        echo "❌ Qt6: Version incorrecta ($qt_version)"
    fi
else
    echo "❌ Qt6: qmake6 no encontrado"
fi

echo ""
echo "📋 Resumen de compatibilidad GPL:"
echo "   📄 BanchouPatcher: GPL-3"
echo "   📄 xdelta3: Compatible (GPL-2+ o Apache 2.0)"
echo "   📄 Qt6: Compatible (LGPL-3/GPL-3)"

echo ""
echo "🚀 Para compilar: ./build-qt6.sh"