# ASSIGNMENT_Group_Project

## Setup Environment
### Windows10
1. Follow the [instruction to install WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) on your Windows10. **Just need the top 7 steps.**
2. Update your WSL packages
```shell
sudo apt update
sudo apt upgrade
```
3. Install necessary package
```shell
sudo apt install gcc gdb make cmake git
```
4. Download [Visual Studio Code](https://code.visualstudio.com/)
5. Clone This Repo
```shell
git clone https://github.com/teamgc35/ASSIGNMENT_Group_Project.git      #Use git to clone this repo
cd ASSIGNMENT_Group_Project       #Change Directory to ASSIGNMENT_Group_Project which is the defaul repo name
code . # Open Vscode in current Directory
```
6. Install Vscode Plugin  
> On the left side, you shall see a menu with icons. Click the fifth one. And Search `C`. Just install the first one. After this is done, you are good to go.
### How to Execute TestCase
```shell
mkdir build       #Create Directory call build
cd build      #Change Directory to build
cmake .. 
make
./TestCase
```
