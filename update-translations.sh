#!/bin/bash

echo "🌍 Actualizando traducciones de BanchouPatcher..."
echo ""

# Check if Qt6 tools are available
LUPDATE_PATH=""
LRELEASE_PATH=""

# Try to find lupdate
if command -v lupdate6 &> /dev/null; then
    LUPDATE_PATH="lupdate6"
elif command -v lupdate &> /dev/null; then
    LUPDATE_PATH="lupdate"
elif [ -f "/usr/lib/qt6/bin/lupdate" ]; then
    LUPDATE_PATH="/usr/lib/qt6/bin/lupdate"
else
    echo "❌ lupdate no encontrado. Instala: sudo apt install qt6-tools-dev"
    exit 1
fi

# Try to find lrelease
if command -v lrelease6 &> /dev/null; then
    LRELEASE_PATH="lrelease6"
elif command -v lrelease &> /dev/null; then
    LRELEASE_PATH="lrelease"
elif [ -f "/usr/lib/qt6/bin/lrelease" ]; then
    LRELEASE_PATH="/usr/lib/qt6/bin/lrelease"
else
    echo "❌ lrelease no encontrado. Instala: sudo apt install qt6-tools-dev"
    exit 1
fi

echo "📝 Actualizando archivos .ts desde el código fuente..."
$LUPDATE_PATH *.cpp *.h *.ui -ts translations/spanish.ts translations/english.ts

echo ""
echo "🔧 Archivo .pro actualizado automáticamente..."

echo ""
echo "🔨 Compilando archivos .qm..."
$LRELEASE_PATH translations/spanish.ts translations/english.ts

echo ""
echo "✅ Traducciones actualizadas:"
ls -la translations/*.qm

echo ""
echo "💡 Para aplicar los cambios:"
echo "   1. Recompila el proyecto: ./build-qt6.sh"
echo "   2. O usa: qmake6 && make"