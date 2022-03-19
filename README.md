## Overview
DP Framework is a C++ class library that can be used to create an event-driven control program for systems that use [DP peripherals](http://demandperipherals.com/), such as the behavior control program for a DP-based robot.  It contains three main elements, C++ bindings for all DP peripherals, an event controller, and an application framework.

## Peripherals
Each DP peripheral has a corresponding C++ class that provides a set of accessor functions for each resource.  These C++ wrappers allow any peripheral to be accessed from within an application; these functions take care of everything needed to interact with the peripheral via dpdaemon.  The resources for any peripheral are either writable, for configuring the peripheral, readable, for accessing single data values, or selectable, for accessing a stream of asynchronous data.  If the peripheral is selectable, the asynchronous data is buffered in the object and the contents of the buffer are accessable via its corresponding access function.

The basic DP peripheral classes are very minimal; they provide accessor functions to all of the peripheral's resources, as described above.  But, typically, an application will derive much more robust classes from these base classes provided in the framework.  For that matter, base classes can be created that use multiple inheritance.  One example is to create a new class, say called locomotive, that is derived from both the COUNT4 event counter and DC2 H-bridge motor controller peripherals to create a class that describes a robot motor/encoder combination, where the DC2 part allows the motor inputs to be controlled and the COUNT4 part deals with movement information fed back from the encoders.

## Event Controller
DP framework is event driven.  There are two different types of events, the arrival of data from a selectable sensor and arbitrary periodic events.  All events must be registered with the framework so that they can be handled at a specified period.  Selectable sensors objects register asynchronous data arrival events automatically when they are instantiated; the period is defined in the class.  Arbitrary periodic events, on the other hand, must be explicitly registered to be handled at a specified period, i.e. every n microseconds.  Accordingly, the main event handler contains both a list of periodic callback routines and and a list of selectable sensors.  The main event handler will first check the callback list to see if any callback's period has been met, and if so, the callback is called.  Next, the main event handler will check to see if any asynchronous data has been sent back from any sensor on the selectable sensor list, and if so, the sensor's handler function is called.

## Application Framework
All of the mechanics of the event handling are taken care of by the framework.  In order to make it as simple as possible to define all of the elements of the application, the framework only requires the DP peripheral object declarations, the definitions of all of the periodic routines, and the presence of two functions, the initialization function, **InitControlProgram(int argc, char* argv[], DP::EventContext& framework)**, and the application shutdown function, **Shutdown(const char* msg, int err)**.

Periodic routines are defined in the BEGIN_PERIODIC_ROUTINE/END_PERIODIC_ROUTINE macro pairs.  The begin macro allow the routine to be named and the the end macro attaches a period to the named routine.  These macros essentially create a struct with the routine's name and defines a single public member function, Routine(), that is the handler.  So, for instance, the following periodic function definition can be used to create a new object called "Foo" that contains the periodic routine handler code:

    BEGIN_PERIODIC_ROUTINE(Foo)
        <code>
    END_PERIODIC_ROUTINE(Foo)(PERIOD_100_mSEC);
  
In the InitControlProgram() function, all of the peripheral objects must be instantiated and all of the periodic routines must be registered.  Again, peripherals are implicitly registered when they are instantiated, but periodic routines must be registered with the main event controller.  As an example, the periodic routine called Foo, as defined above, is registered as follows:

    evtCtx.Register(&Foo);
    
where evtCtx is the event context, i.e. a collection of all callback routines that the main event controller will deal with, which is passed to the InitControlProgram().  All said and done, this process will cause a function that contains the periodic routine handler code to be called every 100mSec.

The control program initialization function must contain the instantiation of all peripheral objects and registration of all of the periodic routines.

The shutdown function is where all objects are destroyed and any error messages are printed.

## Example
The following example application will use the DP Baseboard4 as a user interface to check for button presses and either display which button is pressed on the LEDs or exit the app.


```
// instantiate the BB4IO object to be used as a user interface
DP::BB4IO userInterface;
    
// define the periodic routine to test for button presses every 100mSec
BEGIN_PERIODIC_ROUTINE(CheckInput)

	try
	{
		if (userInterface->IsButtonPressed(S1))
		{
		    // turn on LED 1 if button S1 is pressed
			userInterface->SetLeds(1);
		}
		else if (userInterface->IsButtonPressed(S2)
		{
		    // turn on LED 2 if button S2 is pressed
			userInterface->SetLeds(2);
		}
		else if (userInterface->IsButtonPressed(S3))
		{
		    // exit if button S3 is pressed
			Shutdown("", ERR_NONE);
		}
		
	} catch (DP::FrameworkException& e) {
		Shutdown(e.what(), e.Error());
	}

END_PERIODIC_ROUTINE(CheckInput)(PERIOD_100_mSEC);

// init the control program
void InitControlProgram(int argc, char* argv[], DP::EventContext& evtCtx)
{
	try
	{
		// create the user interface
		ui = new UserInterface(evtCtx);

		// register an input handler routine for the UI
		evtCtx.Register(&CheckInput);

	} catch (DP::FrameworkException& e) {
		Shutdown(e.what(), e.Error());
	}
}

// routine to properly shut down the application
void Shutdown(const char* msg, int error)
{
	// clear LEDs
	ui->Display(0);

	// allow dpserver to catch up
    sleep(1);

	// release all objects
    delete ui;

    exit(error);
}
```

## References
For a much more involved application, see https://www.github.com/jwesterinen/jefebot-controller.git.

