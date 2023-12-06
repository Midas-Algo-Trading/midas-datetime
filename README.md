# Datetime library for C++
### Provides a faster, simpler, and more intuitive date/time/datetime library for C++

# Table of Contents
- [Additional Info](#additional-info)
- [Integration](#integration---cmake)
- [Basic Examples](#basic-examples)
  - [Date](#date)
  - [Time](#time)
  - [Datetime](#datetime)
  - [TimeDelta](#timedelta)
  - [Ranges](#ranges)

### Additional Info
* Supports operations between all classes and their components
* Time supports nanosecond precision
* Time supports timezones

## Integration - Cmake
	add_subdirectory(datetime)
	add_executable(foo ...)
	target_link_libraries(foo datetime)

 ### Basic Examples
*There is much more this library offers, these are just some examples*

 ## Date

### Include
	#include <datetime/date/Date.h>

 ### Construction
	Date date = date(2022, 1, 1);  
 
	Date date = Date::today();  
 
	Date date = Date("2022-01-01");  
	
	std::vector<Date> dates = Date::range(Date(2022, 1, 1), Date(2023, 1, 1));
  

 ### Arithmetic 
	date -= Days(3)
 
	date++;
 
	Date res = day1 - day2


 ### Comparison
	bool greater = day1 > day2;
	
	bool equal = day1 == day2;

 ### Operations
 
	std::string str = date.to_string();

 ## Time

### Include
	#include <datetime/time/Time.h>
	#include <datetime/time/Timezone.h>
 

 ### Construction

	// Hours, minutes, seconds, milliseconds, microseconds, nanoseconds, timezone
	Time time = Time(1, 2, 3, 4, 5, 6, TZ::EST);

    Time time = Time("1:02:03.4.5.6+5:00",
                     Time::Component::HOUR,
                     Time::Component::MINUTE,
                     Time::Component::SECOND,
                     Time::Component::MILLISECOND,
                     Time::Component::MICROSECOND,
                     Time::Component::NANOSECOND,
                     Time::Component::TIMEZONE);
	 
	Time time = Time::now();
	
	// Get all the times between 2 times with a minute difference between each time.
	std::vector<Time> times = Time::range(time1, time2, Minutes(1));

### Arithmetic

	time -= Hours(1);

	time += Nanoseconds(3);
	
	Time res = time + Microseconds(2);


### Comparison

	bool less = time1 < time2;

	bool not_equal = time1 != time2;

### Operations
	time.set_timezone(TZ::UTC);

	time.round(Time::Component::Minute);

	Time.floor(Time::Component::Second);
	
	std::string str = time.to_string();
	
	int mins = time.total_minutes();

## Datetime

### Include
	#include <datetime/datetime/Datetime.h>

### Construction
	Datetime datetime = Datetime(date);

	Datetime datetime = Datetime(time);

	Datetime datetime = Datetime(date, time);

	Datetime datetime = Datetime(2022, 1, 1, 1, 2, 3, 4, 5, 6, TZ::EST);

	Datetime datetime = Datetime::now(TZ::CST);

	Datetime datetime = Datetime::from_ms(1641016800000);

	Datetime datetime = Datetime("2022 1:2:3+5:00",  
                                 Date::Component::YEAR,
                                 Time::Component::HOUR,
                                 Time::Component::MINUTE,
                                 Time::Component::SECOND,
                                 Time::Component::TIMEZONE);
								 
	 
	// Get the datetimes between 2 datetimes with 7 days between each datetime
	std::vector<Datetime> datetimes = Datetime::range(datetime1, datetime2, Days(7));

	// Get the datetimes between 2 datetimes with 1 microsecond between each datetime
	std::vector<Datetime> datetimes = Datetime::range(datetime1, datetime2, Microseconds(1));

### Arithmetic
	datetime += Days(2);
	
	datetime += time;

	datetime += Milliseconds(10);

	Datetime res = datetime - Hours(1);

	Datetime res = datetime - time;

### Comparison

	bool greater = datetime1 > datetime2;

	bool equal = datetme1 == datetime2;

### Operations
	Date date = datetime.date();

	Time time = datetime.time();

	std::string str = datetime.to_string();

## TimeDelta

### Include
	#include <datetime/timedelta/TimeDelta.h>

### Construction
	// Days, hours, minutes, seconds, milliseconds, microseconds, nanoseconds
	TimeDelta timedelta = TimeDelta(1, 2, 3, 4, 5, 6, 7);

### Comparisons
	bool less = timedelta1 < timedelta2;
	
	bool equal = timedelta1 == timedelta2;

### Operations
	time_delta.abs();
	
	int hours = time_delta.total_hours();
	
	std::string str = time_delta.to_string();

## Ranges

### Include
	#include <datetime/date/DateRange.h>
	#include <datetime/time/TimeRange.h>
	#include <datetime/datetime/DatetimeRange.h>

### Use
	TimeRange time_range = TimeRange(time1, time2);
	bool is_in = time_range.is_in(time3);
	
	DateRange date_range = DateRange(date1, date2);
	bool is_in = date_range.is_in(date3);
	
	DatetimeRange datetimeRange = Datetimerange(datetime1, datetime2);
	bool is_in = datetime_range.is_in(datetime3);
