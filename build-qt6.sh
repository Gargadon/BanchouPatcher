#!/bin/bash

echo "🔨 Compilando BanchouPatcher (solo Qt6)..."

# Verificar que qmake6 esté disponible
if ! command -v qmake6 &> /dev/null; then
    echo "❌ Error: qmake6 no encontrado. Este proyecto requiere Qt6."
    echo "   Instala Qt6: sudo apt install qt6-base-dev qt6-tools-dev"
    exit 1
fi

# Limpiar build anterior
echo "🧹 Limpiando build anterior..."
make clean 2>/dev/null || true

# Generar Makefile con Qt6
echo "⚙️  Generando Makefile con qmake6..."
qmake6 BanchouPatcher3.pro

if [ $? -ne 0 ]; then
    echo "❌ Error en qmake6. Verifica que tienes Qt6 instalado."
    exit 1
fi

# Compilar
echo "🔧 Compilando..."
make

if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa con Qt6!"
    echo "📂 Ejecutable: ./BanchouPatcher"

    # Mostrar información de Qt6
    echo ""
    echo "ℹ️  Información de Qt6:"
    qmake6 --version
    echo ""
    echo "📚 Dependencias Qt6:"
    ldd BanchouPatcher3 | grep Qt
    echo ""
    echo "🚀 Para ejecutar: ./BanchouPatcher"
else
    echo "❌ Error en la compilación"
    exit 1
fi
