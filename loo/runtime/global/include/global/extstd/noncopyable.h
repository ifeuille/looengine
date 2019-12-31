#ifndef LOO_NONCOPYABLE_H
#define LOO_NONCOPYABLE_H
#pragma once
namespace loo
{
	class noncopyable {
	protected:
		constexpr noncopyable() = default;
		~noncopyable() = default;
	private:
		noncopyable(const noncopyable&) = delete;
		noncopyable& operator=(const noncopyable&) = delete;
	};
}

#endif