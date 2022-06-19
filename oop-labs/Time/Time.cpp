#include "pch.h"
#include "Time.h"
#include <iomanip>
#include <iostream>
#include <cmath>

constexpr unsigned SECONDS_PER_HOUR = 60 * 60;
constexpr unsigned SECONDS_PER_MINUTE = 60;
constexpr unsigned MAX_TIMESTAMP = 23 * SECONDS_PER_HOUR + 59 * SECONDS_PER_MINUTE + 60;

Time::Time(unsigned hours, unsigned minutes, unsigned seconds)
	: Time(hours * SECONDS_PER_HOUR + minutes * SECONDS_PER_MINUTE + seconds)
{
	if (hours > 23 || minutes > 59 || seconds > 59 || hours < 0 || minutes < 0 || seconds < 0)
	{
		throw std::logic_error("Invalid input arguments");
	}
}

Time::Time(unsigned timestamp)
	: m_timestamp(timestamp)
{
	if (timestamp > MAX_TIMESTAMP || timestamp < 0)
	{
		throw std::logic_error("Invalid timestamp value");
	}
}

unsigned Time::GetHours() const
{
	return m_timestamp / SECONDS_PER_HOUR;
}

unsigned Time::GetMinutes() const
{
	return (m_timestamp - GetHoursTimestamp()) / SECONDS_PER_MINUTE;
}

unsigned Time::GetSeconds() const
{
	return m_timestamp - GetHoursTimestamp() - GetMinutesTimestamp();
}

Time& Time::operator++()
{
	TimestampAdjustmentForAdd(1);
	return *this;
}

Time Time::operator++(int)
{
	const Time old = *this;
	operator++();
	return old;
}

Time& Time::operator--()
{
	TimestampAdjustmentForSub(1);
	return *this;
}

Time Time::operator--(int)
{
	const Time old = *this;
	operator--();
	return old;
}

Time Time::operator+(Time right)
{
	TimestampAdjustmentForAdd(right.m_timestamp);
	return *this;
}

Time Time::operator-(Time right)
{
	TimestampAdjustmentForSub(right.m_timestamp);
	return *this;
}

Time Time::operator*(int mul)
{
	TimestampAdjustmentForMul(mul);
	return *this;
}

Time Time::operator/(int div)
{
	auto h = GetHours() / div;
	auto m = GetMinutes() / div;
	m += std::round(((static_cast<double>(GetHours()) / div - h) * SECONDS_PER_HOUR) / SECONDS_PER_MINUTE);
	auto s = GetSeconds() / div;
	m_timestamp = h * SECONDS_PER_HOUR + m * SECONDS_PER_MINUTE + s;
	return *this;
}

unsigned Time::operator/(Time div)
{
	return m_timestamp / div.m_timestamp;
}

Time Time::operator+=(Time right)
{
	operator+(right);
	return *this;
}

Time Time::operator-=(Time right)
{
	operator-(right);
	return *this;
}

Time Time::operator*=(int mul)
{
	operator*(mul);
	return *this;
}

Time Time::operator/=(Time div)
{
	operator/(div);
	return *this;
}

Time Time::operator/=(int div)
{
	operator/(div);
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Time& time)
{
	stream << std::setw(2) << std::setfill('0') << time.GetHours();
	stream << ":";
	stream << std::setw(2) << std::setfill('0') << time.GetMinutes();
	stream << ":";
	stream << std::setw(2) << std::setfill('0') << time.GetSeconds();
	return stream;
}

std::istream& operator>>(std::istream& stream, Time& time)
{
	return stream;
}

bool Time::operator==(const Time& right) const
{
	return m_timestamp == right.m_timestamp;
}

bool Time::operator<(const Time& right) const
{
	return m_timestamp < right.m_timestamp;
}

bool Time::operator>(const Time& right) const
{
	return m_timestamp > right.m_timestamp;
}

bool Time::operator<=(const Time& right) const
{
	return m_timestamp <= right.m_timestamp;
}

bool Time::operator>=(const Time& right) const
{
	return m_timestamp >= right.m_timestamp;
}

unsigned Time::GetHoursTimestamp() const
{
	return GetHours() * SECONDS_PER_HOUR;
}

unsigned Time::GetMinutesTimestamp() const
{
	return GetMinutes() * SECONDS_PER_MINUTE;
}

void Time::TimestampAdjustmentForAdd(unsigned diffTimestamp)
{
	m_timestamp += diffTimestamp;
	if (m_timestamp >= MAX_TIMESTAMP)
	{
		auto excess = m_timestamp / MAX_TIMESTAMP;
		m_timestamp -= excess * MAX_TIMESTAMP;
	}
}

void Time::TimestampAdjustmentForSub(unsigned diffTimestamp)
{
	m_timestamp -= diffTimestamp;
	if (m_timestamp > MAX_TIMESTAMP)
	{
		m_timestamp = MAX_TIMESTAMP;
		m_timestamp -= diffTimestamp;
	}
}

void Time::TimestampAdjustmentForMul(int mul)
{
	auto newTimestamp = GetHours() * mul * SECONDS_PER_HOUR + GetMinutes() * mul * SECONDS_PER_MINUTE + GetSeconds() * mul;
	if (newTimestamp >= MAX_TIMESTAMP)
	{
		auto excess = newTimestamp / MAX_TIMESTAMP;
		newTimestamp -= excess * MAX_TIMESTAMP;
	}
	m_timestamp = newTimestamp;
}
