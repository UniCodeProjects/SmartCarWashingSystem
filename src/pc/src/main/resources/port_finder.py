import sys
import os
import subprocess
import re

# Runs pip show pyserial to ensure the sys path includes the pyserial installation location.
lib_name = "pyserial"
lib_location = subprocess.run(["pip", "show", lib_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
# Installing missing library, then restarting the script.
if lib_location.returncode != 0:    
    result = subprocess.run(["pip", "install", lib_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    os.execl(sys.executable, sys.executable, *sys.argv)
if lib_location.stdout.strip() not in sys.path:
    match = re.search(r'^Location: (.+)$', lib_location.stdout, re.MULTILINE)
    if match:
        lib_location = match.group(1)
        sys.path.append(lib_location)

import serial.tools.list_ports

ports = list(serial.tools.list_ports.comports())

for port in ports:
    if "Arduino Uno" in port.description:
        print(port.name)
