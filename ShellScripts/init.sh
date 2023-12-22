#!/bin/bash

#!/bin/bash

# Create an alias for the wt command
alias wt='/mnt/c/Users/<YourUsername>/AppData/Local/Microsoft/WindowsApps/wt.exe'

export PATH=$PATH:"C:\Users\Pedro.PedroMota\AppData\Local\Microsoft\WindowsApps"

# Use the wt alias to open a new WSL terminal and run ShellScripts/launch.sh
wt -w 0 nt wsl ./ShellScripts/launch.sh

# Use the wt alias to open a new WSL terminal and run Monitor/Monitor.py
wt -w 0 nt wsl python3 Monitor/Monitor.py

# Use the wt alias to open a new WSL terminal and run 'make r'
wt -w 0 nt wsl make r