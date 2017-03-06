# EK-SPL

## Dependencies
The following software is needed:
gcc, cmake, qt, qt-creator

## Flash NAO
Get the following:
* nao-flasher-1.12.5-linux[ARCH].tar.gz
* opennao-atom-system-image-1.14.5.opn
* USB memory with at least 2 GB 

```bash
cd ~/nao-flasher-1.12.5-linux[ARCH]
sudo ./flasher
```
To flash the robot, it must be connected to a power supply and turn off:

1. Connect the USB to the NAO
2. Turn on NAO holding the button for 5 seconds (until the botton turns blue)
3. Wait and follow NAO instructions


## Install SDK
1. Create working directory
2. Download software
3. Extract:
	* naoqui-sdk-1.14.5-linux64
	* qibuild-1.14.3
	* linux64-nao-atom-cross-toolchain-1.14.5
4. Install qibuild

	```bash
	cd ~/qibuild-1.14.3/
	./install-qibuild.sh
	```
5. Configure qibuild with the following options:
	1. Unix Makefiles
	2. default
	3. default
	```bash
	qibuild config --wizard
	```
6. Download the repo and initializate the working directory

	```bash
	qibuild init
	```
7. Configurate compilers

	```bash
	qitoolchain create cross-atom ~/[...]/linux64-nao-atom-cross-toolchain-1.14.5/toolchain.xml
	```

## Create a New Module:
```bash
cd ~/[PATH_TO_REPO]
qibuild create [MODULE_NAME]
qibuild configure -c cross-atom 
qibuild make -c cross-atom
```

## Upload code to the robot
Use scp to upload the compiled code to the robot.

Edit home/nao/naoqi/preferences/autoload.ini and under [user], add the line: /home/nao/lib[MODULE_NAME].so for each module.






































































