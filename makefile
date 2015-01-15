AT = @
INCDIR = -I/home/benjamin/wpilib/cpp/current/include
CPPFLAGS += -g -Wall -W $(INCDIR) -std=c++14 -fPIC
LFLAGS = -L/home/benjamin/wpilib/cpp/current/lib -lwpi
CXX = arm-frc-linux-gnueabi-g++
TEAM = 3181
RMCOMMAND = rm -f
DEPLOYTARGET = roboRIO-$(TEAM).local

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.hpp)
OBJECTS = $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp))



all: $(OBJECTS)
	test -d bin/ || mkdir -p bin/
	$(CXX) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o bin/FRCUserProgram
clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/*
	rm -rf doxygen
	
deploy:
	ssh lvuser$(AT)$(DEPLOYTARGET) "rm /home/lvuser/FRCUserProgram || true"
	sftp -oBatchMode=no -b sftpbatchfile lvuser$(AT)$(DEPLOYTARGET)
	ssh lvuser$(AT)$(DEPLOYTARGET) "chmod a+x /home/lvuser/robotCommand; . /etc/profile.d/natinst-path.sh; chmod a+x /home/lvuser/FRCUserProgram; /usr/local/frc/bin/frcKillRobot.sh -t -r"

kill-robot:
	ssh lvuser$(AT)$(DEPLOYTARGET) "/usr/local/frc/bin/frcKillRobot.sh"
