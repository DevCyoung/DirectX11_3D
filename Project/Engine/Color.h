#pragma once

namespace helper
{
	class Color
	{
	public:
		constexpr inline static const Vector4 WHITE = Vector4(1.f, 1.f, 1.f, 1.f);
		constexpr inline static const Vector4 BLACK = Vector4(0.f, 0.f, 0.f, 1.f);
		constexpr inline static const Vector4 RED = Vector4(1.f, 0.f, 0.f, 1.f);
		constexpr inline static const Vector4 GREEN = Vector4(0.f, 1.f, 0.f, 1.f);
		constexpr inline static const Vector4 BLUE = Vector4(0.f, 0.f, 1.f, 1.f);
		constexpr inline static const Vector4 MAGENTA = Vector4(1.f, 0.f, 1.f, 1.f);
		constexpr inline static const Vector4 YELLOW = Vector4(1.f, 1.f, 0.f, 1.f);		
		
	};
}