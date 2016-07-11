@Echo off
cd ./
netsh int ip add addr 1 79.110.88.138/24 st=ac
netsh int ip add addr 1 79.110.88.139/24 st=ac
netsh int ip add addr 1 79.110.88.140/24 st=ac
ECHO Welcome to ESEmu!
ECHO Press enter only once you finished playing!
PAUSE
netsh int ip delete addr 1 79.110.88.138 st=ac
netsh int ip delete addr 1 79.110.88.139/24 st=ac
netsh int ip delete addr 1 79.110.88.140/24 st=ac