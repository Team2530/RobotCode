import WPILib;

public class JavaAuto extends SimpleRobot {
	RobotDrive myRobot = new RobotDrive(1,2,3,4);
	public void Autonomous() {
		myRobot.Drive(5);
	}
}
