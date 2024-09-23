Lab 2 - Test Procedure

This document outlines the steps required to set up, exercise, and verify the behavior of the system. Follow the instructions carefully to ensure the system operates as expected.

# Setting up the Test Scenario

1. Build and Flash the Project.

2. Reinitialize the USB Connection:
   - After flashing, unplug and replug the USB cable connected to the microcontroller to ensure it resets properly.

# Exercising the System
1. Upon completing the flashing process, promptly open the serial monitor to begin monitoring. First, input all uppercase and lowercase alphabetic characters to evaluate the function's behavior. Results should be compared to expected outcomes; any discrepancies will be considered a failure of the test.

2. Monitor the onboard LED:
   - The LED should exhibit a blinking pattern. During this time, verify the actual state of the GPIO alongside the variable state to ensure the intended behavior is achieved. Additionally, the loop is designed to execute 100 times out of a total of 110 iterations. This will serve as a safety measure to confirm consistent performance.

Note: When you run the test, immediately open the serial monitor. If you delay, you won't be able to see the results.