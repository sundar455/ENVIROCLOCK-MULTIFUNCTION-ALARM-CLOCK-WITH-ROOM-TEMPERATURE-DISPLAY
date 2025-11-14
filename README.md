# ENVIROCLOCK-MULTIFUNCTION-ALARM-CLOCK-WITH-ROOM-TEMPERATURE-DISPLAY
EnviroClock is a simple project using LPC2148 that shows the current time, alarm, and room temperature on an LCD. Users can set or change the time and alarm using a keypad. When the alarm time is reached, a buzzer sounds. The system combines clock, temperature sensing, and alarm features in one easy-to-use device.

#PROJECT WORK FLOW:  
In this project, first the required peripherals such as the LCD, LEDs, keypad, RTC, ADC (for LM35) and external interrupt are initialized inside the main function before entering the super loop. 
Inside the continuous loop, the system reads the current time and date from the on-chip RTC and displays it on the LCD along with the day information. And additionally reads the current room temperature from LM35 sensor and display it on LCD.  If the current time matches with the alarm time, activate the buzzer to alert the user. To stop the alarm user, need to press the alarm stop button otherwise after one minute alarm need to stop.
To ensure proper system operation, it is essential that the RTC always displays the correct time. If the displayed time is found to be incorrect, the user can press a dedicated switch to generate an interrupt request. Upon receiving the interrupt, the system temporarily halts its normal operation, and the LCD displays a small menu with options for the user to choose from.
1. Time 2.Date 3.Day
4. SET ALARM 	5. EXIT.
If the user selects exit, the program simply resumes the main loop; but if the user selects the TIME, the LCD shows a second menu allowing modification of hours, minutes, seconds, day,along with exit option.
1.hours 2.minutes
3.seconds 5.Exit
If the user selects exit, the program simply resumes the TIME MENU loop; but if the user selects the HOURS, the LCD shows a "Enter hour(0-23)"allowing modification of hours. similarly for minutes and seconds.
This process supports an interactive multifunction clock and environment monitor where the system runs real-time timekeeping with room temperature display, alarm functionality, and a user-friendly time and alarm editing routine via interrupt and keypad input.
