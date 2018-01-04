/*
 * Framework.h
 *
 *  Created on: Mar 7, 2017
 *      Author: jeff
 */

#ifndef INCLUDE_DP_EVENTS_H_
#define INCLUDE_DP_EVENTS_H_

#include <list>
#include <string>

namespace DP
{

/**
 * framework errors
 */
#define ERR_NONE			 0
#define ERR_UNKNOWN			-1
#define ERR_INITIALIZATION	-1001
#define ERR_CONNECT			-1002
#define ERR_READ			-1003
#define ERR_WRITE			-1004
#define ERR_SELECT			-1005
#define ERR_PARAMS			-1006
#define ERR_RESPONSE		-1007
#define ERR_REGISTRATION	-1008

/**
 * \brief This class represents an error encountered in the execution of the application.
 *
 * ...
 */
class FrameworkException : public std::exception
{
private:
	std::string msg;
	int error;

public:
	FrameworkException(const char* _msg, int _error) : msg(_msg), error(_error)
	{}
	~FrameworkException() throw()
	{}
	virtual const char* what() const throw()
	{
		return msg.c_str();
	}
	int Error()
	{
		return error;
	}
};

/**
 * \brief The base class for periodic functions.
 *
 * The object contains the function and period at which it will be called.  This
 * class is pure virtual and is the basis of a PeriodicRoutine.
*/
class Callback
{
friend class EventContext;

private:
	unsigned long long to;		// uSec since the epoch of Jan 1, 1970 to timeout
	unsigned period;			// period in uSec
	bool HasExpired(unsigned long long now);
	void UpdateTimeout(unsigned long long now);
	unsigned long long GetNextTimeout(unsigned long long curTimeout);

protected:
	/**
	 * The actual function that is called when the callback period is reached.  This pure
	 * virtual function will be defined in the PeriodicRoutine.
	 */
	virtual void Routine() = 0;

public:
	/**
	 * @param _period The period at which the callback will be called
	 */
	Callback(unsigned _period);
	virtual ~Callback()
	{}
};

/**
 * These macros define the callback routine of periodic routine
 */
#define BEGIN_PERIODIC_ROUTINE(f)				\
struct t_##f									\
{												\
	void Routine()								\
	{
// <the body of the periodic routine goes here>
#define END_PERIODIC_ROUTINE(f) 				\
	}											\
}; 												\
DP::PeriodicRoutine<t_##f> f

/**
 * \brief A class that contains a specific function that is called periodically.
 *
 * Template for a periodic routine class.
 */
template <class T>
class PeriodicRoutine : public Callback
{
private:
	T* callbackCode;

protected:
	/**
	 * The definition of the function that will be called when the period expires.
	 */
	void Routine()
	{
		callbackCode->Routine();
	}

public:
	/**
	 * @param period The period of the periodic routine
	 */
	PeriodicRoutine(unsigned period) : Callback(period)
	{
		callbackCode = new T;
	}
	virtual ~PeriodicRoutine()
	{
		delete callbackCode;
	}
};

/**
 * \brief Base class for a non DP sensor.
 *
 * A generic sensor is a peripheral whose data must be explicitly read by a
 * Callback function.
 */
class GenericSensor : public Callback
{
protected:
	int fd;

public:
	/**
	 * @param period The specified period of the callback
	 */
	GenericSensor(unsigned period) : Callback(period), fd(-1)
	{}
	virtual ~GenericSensor()
	{}
};

/**
 * \brief Base class for a DP sensor.
 *
 * A DP sensor is a peripheral that sends an interrupt when its data is available.
 * The availability of its data can be detected in a select loop.
 */
class SelectableSensor
{
friend class EventContext;

protected:
	int dataFd;
	virtual void Handler() = 0;

public:
	SelectableSensor() : dataFd(-1)
	{}
	virtual ~SelectableSensor()
	{}
};

// event dispatcher and controller
/**
 * \brief This class contains all of the event-driven aspect of an application.
 *
 * ...
 */
class EventContext
{
private:
	// list of sensors that are intrinsically selectable, i.e. those derived from DP_Sensor
	std::list<SelectableSensor*> selectableSensors;
	std::list<Callback*> periodicRoutines;
	int maxFd;
	timeval* ExecRoutines();

	int OpenConnection();

public:
	static int cmdfd;

	EventContext();
	virtual ~EventContext()
	{}

	static unsigned long long Tv2us(struct timeval *ptv);

	/**
	 * \brief Registers a selectable sensor
	 *
	 * All sensors must be registered in the event context of the application.  This
	 * registration function is used for selectable sensors, which will allow the
	 * data to be automatically retrieved.
	 */
	void Register(SelectableSensor*);

	/**
	 * \brief Registers a sensor that cannot be selected.
	 *
	 * All sensors must be registered in the event context of the application.  This
	 * registration function is used for non-DP sensors which will allow the data of
	 * the sensor to be explicitly retrieved.
	 */
	void Register(Callback*);

	/**
	 * \brief The main event loop of the application.
	 *
	 * This is the main event handling function to be called by the application.
	 */
	void MainEventLoop();
};

} // namespace DP

/**
 * Application initialization function that must be provided by the application.
 */
void InitControlProgram(int argc, char* argv[], DP::EventContext& framework);

/**
 * Normal application shutdown function that must be provided by the application.
 */
void Shutdown();

/**
 * Abnormal application shutdown function that must be provided by the application.
 * @param msg A string containing the cause of the error
 * @param err An error code
 */
void Shutdown(const char* msg, int err);

#endif /* INCLUDE_DP_EVENTS_H_ */
