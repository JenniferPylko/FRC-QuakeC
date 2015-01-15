#include "WPILib.h"
#include "kzqcvm.h"
#include "data.h"
#include <iostream>

using namespace kzqcvm;

extern void register_builtins(Kzqcvm* vm);

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
		QuakeC_VM = new Kzqcvm("frcprogs.dat");
		register_builtins(QuakeC_VM);
		robotInit = QuakeC_VM->GetFunction("RobotInit");
		autonomousInit = QuakeC_VM->GetFunction("AutonomousInit");
		autonomousThink = QuakeC_VM->GetFunction("AutonomousThink");
		teleopInit = QuakeC_VM->GetFunction("TeleopInit");
		teleopThink = QuakeC_VM->GetFunction("TeleopThink");
		testThink = QuakeC_VM->GetFunction("TestThink");
		robotInit.Run();
	}

	void AutonomousInit()
	{
		autonomousInit.Run();
	}

	void AutonomousPeriodic()
	{
		autonomousThink.Run();
	}

	void TeleopInit()
	{
		teleopInit.Run();
	}

	void TeleopPeriodic()
	{
		teleopThink.Run();
	}

	void TestPeriodic()
	{
		lw->Run();
		testThink.Run();
	}
};

START_ROBOT_CLASS(Robot);

