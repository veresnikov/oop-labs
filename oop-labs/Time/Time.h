#pragma once
#include <ostream>

class Time
{
public:
	Time(unsigned hours, unsigned minutes, unsigned seconds = 0);
	Time(unsigned timestamp = 0);
	unsigned GetHours() const;
	unsigned GetMinutes() const;
	unsigned GetSeconds() const;

	Time& operator++();
	Time operator++(int);
	Time& operator--();
	Time operator--(int);
	friend Time operator+(Time, Time);
	friend Time operator-(Time, Time);
	friend Time operator*(Time, int);
	friend Time operator*(int, Time);
	friend Time operator/(Time, int);
	friend unsigned operator/(Time, Time);
	Time operator+=(Time);
	Time operator-=(Time);
	Time operator*=(int);
	Time operator/=(int);
	friend std::ostream& operator<<(std::ostream&, const Time&);
	friend std::istream& operator>>(std::istream&, Time&);
	bool operator==(const Time&) const;
	bool operator<(const Time&) const;
	bool operator>(const Time&) const;
	bool operator<=(const Time&) const;
	bool operator>=(const Time&) const;

private:
	unsigned GetHoursTimestamp() const;
	unsigned GetMinutesTimestamp() const;
	static Time TimestampAdjustmentForAdd(Time, unsigned);
	static Time TimestampAdjustmentForSub(Time, unsigned);
	static Time TimestampAdjustmentForMul(Time, int);

	unsigned m_timestamp;
};
