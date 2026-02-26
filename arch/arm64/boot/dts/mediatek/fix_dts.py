import re

def fix_dts():
    file_path = 'mt6879.dts'
    with open(file_path, 'r') as f:
        content = f.read()

    # 1. Forzar que la raíz y el SOC usen 2 y 2 (64-bit estándar)
    # Buscamos el inicio del archivo / { ... }
    content = re.sub(r'\/ \{', '/ {\n\t#address-cells = <2>;\n\t#size-cells = <2>;', content, count=1)
    
    # 2. Corregir nodos específicos que mencionaste en el log
    # Estos nodos necesitan explícitamente decir que sus hijos usan 1 celda de tamaño
    nodos_rebeldes = ['usb0@11201000', 'usb0-phy@11e40000', 'mtk_lpm', 'reserved-memory']
    
    for nodo in nodos_rebeldes:
        pattern = r'(' + re.escape(nodo) + r'\s*\{)'
        # Insertamos las reglas para que el hijo coincida con lo que el compilador espera
        content = re.sub(pattern, r'\1\n\t\t#address-cells = <2>;\n\t\t#size-cells = <1>;', content)

    # 3. Limpieza de duplicados por si acaso
    # Si hay un #address-cells = <2>; seguido de otro igual, borramos uno.
    content = re.sub(r'(#address-cells = <2>;\s*)+', r'#address-cells = <2>;\n', content)
    content = re.sub(r'(#size-cells = <2>;\s*)+', r'#size-cells = <2>;\n', content)

    with open(file_path, 'w') as f:
        f.write(content)
    print("Unificación completada. Intenta compilar ahora.")

fix_dts()
