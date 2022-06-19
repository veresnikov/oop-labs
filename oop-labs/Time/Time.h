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
	Time operator+(Time);
	Time operator-(Time);
	Time operator*(int);
	friend Time operator*(int, Time);
	Time operator/(int);
	unsigned operator/(Time);
	Time operator+=(Time);
	Time operator-=(Time);
	Time operator*=(int);
	Time operator/=(Time);
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
	void TimestampAdjustmentForAdd(unsigned);
	void TimestampAdjustmentForSub(unsigned);
	void TimestampAdjustmentForMul(int);

	unsigned m_timestamp;
};
