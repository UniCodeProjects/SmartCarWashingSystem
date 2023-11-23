import sys
import subprocess
import re

# Runs pip show pyserial to ensure the sys path includes the pyserial installation location
lib_name = "pyserial"
lib_location = subprocess.run(["pip", "show", lib_name], stdout=subprocess.PIPE, text=True).stdout
if "WARNING: Package(s) not found" in lib_location:
    result = subprocess.run(["pip", "install", lib_name])
    if result.returncode != 0:
        raise RuntimeError
if lib_location not in sys.path:
    match = re.search(r'^Location: (.+)$', lib_location, re.MULTILINE)
    if match:
        lib_location = match.group(1)
    sys.path.append(lib_location)

import serial.tools.list_ports

ports = list(serial.tools.list_ports.comports())

for port in ports:
    if "Arduino Uno" in port.description:
        print(port.name)
