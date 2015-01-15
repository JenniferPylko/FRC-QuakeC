#include "WPILib.h"
#include "kzqcvm.h"
#include "data.h"
#include <iostream>

using namespace kzqcvm;

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Kzqcvm* QuakeC_VM;
	Function robotInit;
	Function autonomousInit;
	Function autonomousThink;
	Function teleopInit;
	Function teleopThink;
	Function testThink;
	Function globalThink;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		std::cout << "tahueo" << std::endl;
		QuakeC_VM = new Kzqcvm("rprogs.dat");
		robotInit = QuakeC_VM->GetFunction("RobotInit");
		autonomousInit = QuakeC_VM->GetFunction("AutonomousInit");
		autonomousThink = QuakeC_VM->GetFunction("AutonomousThink");
		teleopInit = QuakeC_VM->GetFunction("TeleopInit");
		teleopThink = QuakeC_VM->GetFunction("TeleopThink");
		testThink = QuakeC_VM->GetFunction("TestThink");
		globalThink = QuakeC_VM->GetFunction("GlobalThink");
		robotInit.Run();
	}

	void AutonomousInit()
	{
		autonomousInit.Run();
	}

	void AutonomousPeriodic()
	{
		globalThink.Run();
		autonomousThink.Run();
	}

	void TeleopInit()
	{
		teleopInit.Run();
	}

	void TeleopPeriodic()
	{
		globalThink.Run();
		teleopThink.Run();
	}

	void TestPeriodic()
	{
		lw->Run();
		globalThink.Run();
		testThink.Run();
	}
};

START_ROBOT_CLASS(Robot);

