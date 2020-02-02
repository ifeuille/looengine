#ifndef LE_CORE_COLOR_H
#define LE_CORE_COLOR_H
#include "global/global.h"
#include "global/extstd/typetraits.h"
#include "global/extstd/operators.h"
#include "global/math/mathcore.h"
#include "global/template/externalstring.h"
#include "global/template/hash.h"

namespace loo
{
	namespace math
	{
		enum class EGammaSpace
		{
			/** No gamma correction is applied to this space, the incoming colors are assumed to already be in linear space. */
			Linear,
			/** A simplified sRGB gamma correction is applied, pow(1/2.2). */
			Pow22,
			/** Use the standard sRGB conversion. */
			sRGB,
		};

		struct FColor;
		/**
		 * A linear, 32-bit/component floating point RGBA color.
		 */
		struct FLinearColor
		{
			float	R,G,B,A;

			/** Static lookup table used for FColor -> FLinearColor conversion. Pow(2.2) */
			static float Pow22OneOver255Table[256];

			/** Static lookup table used for FColor -> FLinearColor conversion. sRGB */
			static float sRGBToLinearTable[256];

			LOO_FORCEINLINE FLinearColor ( ) {}
			LOO_FORCEINLINE explicit FLinearColor ( EForceInit )
				: R ( 0 ), G ( 0 ), B ( 0 ), A ( 0 )
			{}
			LOO_FORCEINLINE FLinearColor ( float InR, float InG, float InB, float InA = 1.0f ) : R ( InR ), G ( InG ), B ( InB ), A ( InA ) {}

			/**
			 * Converts an FColor which is assumed to be in sRGB space, into linear color space.
			 * @param Color The sRGB color that needs to be converted into linear space.
			 */
			FLinearColor ( const FColor& Color );

			FLinearColor ( const vec3& Vector );

			explicit FLinearColor ( const vec4& Vector );

			//explicit FLinearColor ( const FFloat16Color& C );

			// Serializer.

			friend std::ostream& operator<<( std::ostream& Ar, FLinearColor& Color )
			{
				return Ar << Color.R << Color.G << Color.B << Color.A;
			}

			bool Serialize ( std::ostream& Ar )
			{
				Ar << *this;
				return true;
			}

			// Conversions.
			FColor ToRGBE ( ) const;

			/**
			 * Converts an FColor coming from an observed sRGB output, into a linear color.
			 * @param Color The sRGB color that needs to be converted into linear space.
			 */
			static FLinearColor FromSRGBColor ( const FColor& Color );

			/**
			 * Converts an FColor coming from an observed Pow(1/2.2) output, into a linear color.
			 * @param Color The Pow(1/2.2) color that needs to be converted into linear space.
			 */
			static FLinearColor FromPow22Color ( const FColor& Color );

			// Operators.

			LOO_FORCEINLINE float& Component ( int32 Index )
			{
				return (&R)[Index];
			}

			LOO_FORCEINLINE const float& Component ( int32 Index ) const
			{
				return (&R)[Index];
			}

			LOO_FORCEINLINE FLinearColor operator+( const FLinearColor& ColorB ) const
			{
				return FLinearColor (
					this->R + ColorB.R,
					this->G + ColorB.G,
					this->B + ColorB.B,
					this->A + ColorB.A
				);
			}
			LOO_FORCEINLINE FLinearColor& operator+=( const FLinearColor& ColorB )
			{
				R += ColorB.R;
				G += ColorB.G;
				B += ColorB.B;
				A += ColorB.A;
				return *this;
			}

			LOO_FORCEINLINE FLinearColor operator-( const FLinearColor& ColorB ) const
			{
				return FLinearColor (
					this->R - ColorB.R,
					this->G - ColorB.G,
					this->B - ColorB.B,
					this->A - ColorB.A
				);
			}
			LOO_FORCEINLINE FLinearColor& operator-=( const FLinearColor& ColorB )
			{
				R -= ColorB.R;
				G -= ColorB.G;
				B -= ColorB.B;
				A -= ColorB.A;
				return *this;
			}

			LOO_FORCEINLINE FLinearColor operator*( const FLinearColor& ColorB ) const
			{
				return FLinearColor (
					this->R * ColorB.R,
					this->G * ColorB.G,
					this->B * ColorB.B,
					this->A * ColorB.A
				);
			}
			LOO_FORCEINLINE FLinearColor& operator*=( const FLinearColor& ColorB )
			{
				R *= ColorB.R;
				G *= ColorB.G;
				B *= ColorB.B;
				A *= ColorB.A;
				return *this;
			}

			LOO_FORCEINLINE FLinearColor operator*( float Scalar ) const
			{
				return FLinearColor (
					this->R * Scalar,
					this->G * Scalar,
					this->B * Scalar,
					this->A * Scalar
				);
			}

			LOO_FORCEINLINE FLinearColor& operator*=( float Scalar )
			{
				R *= Scalar;
				G *= Scalar;
				B *= Scalar;
				A *= Scalar;
				return *this;
			}

			LOO_FORCEINLINE FLinearColor operator/( const FLinearColor& ColorB ) const
			{
				return FLinearColor (
					this->R / ColorB.R,
					this->G / ColorB.G,
					this->B / ColorB.B,
					this->A / ColorB.A
				);
			}
			LOO_FORCEINLINE FLinearColor& operator/=( const FLinearColor& ColorB )
			{
				R /= ColorB.R;
				G /= ColorB.G;
				B /= ColorB.B;
				A /= ColorB.A;
				return *this;
			}

			LOO_FORCEINLINE FLinearColor operator/( float Scalar ) const
			{
				const float	InvScalar = 1.0f / Scalar;
				return FLinearColor (
					this->R * InvScalar,
					this->G * InvScalar,
					this->B * InvScalar,
					this->A * InvScalar
				);
			}
			LOO_FORCEINLINE FLinearColor& operator/=( float Scalar )
			{
				const float	InvScalar = 1.0f / Scalar;
				R *= InvScalar;
				G *= InvScalar;
				B *= InvScalar;
				A *= InvScalar;
				return *this;
			}

			// clamped in 0..1 range
			LOO_FORCEINLINE FLinearColor GetClamped ( float InMin = 0.0f, float InMax = 1.0f ) const
			{
				FLinearColor Ret;

				Ret.R = clamp ( R, InMin, InMax );
				Ret.G = clamp ( G, InMin, InMax );
				Ret.B = clamp ( B, InMin, InMax );
				Ret.A = clamp ( A, InMin, InMax );

				return Ret;
			}

			/** Comparison operators */
			LOO_FORCEINLINE bool operator==( const FLinearColor& ColorB ) const
			{
				return this->R == ColorB.R && this->G == ColorB.G && this->B == ColorB.B && this->A == ColorB.A;
			}
			LOO_FORCEINLINE bool operator!=( const FLinearColor& Other ) const
			{
				return this->R != Other.R || this->G != Other.G || this->B != Other.B || this->A != Other.A;
			}

			// Error-tolerant comparison.
			LOO_FORCEINLINE bool Equals ( const FLinearColor& ColorB, float Tolerance = KINDA_SMALL_NUMBER ) const
			{
				return loo::math::equal ( this->R, ColorB.R, Tolerance )&&
					loo::math::equal ( this->G, ColorB.G, Tolerance )&&
					loo::math::equal ( this->B, ColorB.B, Tolerance )&&
					loo::math::equal ( this->A, ColorB.A, Tolerance );
			}

			FLinearColor CopyWithNewOpacity ( float NewOpacicty ) const
			{
				FLinearColor NewCopy = *this;
				NewCopy.A = NewOpacicty;
				return NewCopy;
			}

			/**
			 * Converts byte hue-saturation-brightness to floating point red-green-blue.
			 */
			static FLinearColor FGetHSV ( uint8 H, uint8 S, uint8 V );

			/**
			* Makes a random but quite nice color.
			*/
			static FLinearColor MakeRandomColor ( );

			/**
			* Converts temperature in Kelvins of a black body radiator to RGB chromaticity.
			*/
			static FLinearColor MakeFromColorTemperature ( float Temp );

			/**
			 * Euclidean distance between two points.
			 */
			static inline float Dist ( const FLinearColor &V1, const FLinearColor &V2 )
			{
				return loo::math::sqrt( loo::math::square ( V2.R - V1.R ) + loo::math::square ( V2.G - V1.G ) + loo::math::square ( V2.B - V1.B ) + loo::math::square ( V2.A - V1.A ) );
			}

			/**
			 * Generates a list of sample points on a Bezier curve defined by 2 points.
			 *
			 * @param	ControlPoints	Array of 4 Linear Colors (vert1, controlpoint1, controlpoint2, vert2).
			 * @param	NumPoints		Number of samples.
			 * @param	OutPoints		Receives the output samples.
			 * @return					Path length.
			 */
			static float EvaluateBezier ( const FLinearColor* ControlPoints, int32 NumPoints, std::vector<FLinearColor>& OutPoints );

			/** Converts a linear space RGB color to an HSV color */
			FLinearColor LinearRGBToHSV ( ) const;

			/** Converts an HSV color to a linear space RGB color */
			FLinearColor HSVToLinearRGB ( ) const;

			/**
			 * Linearly interpolates between two colors by the specified progress amount.  The interpolation is performed in HSV color space
			 * taking the shortest path to the new color's hue.  This can give better results than FMath::Lerp(), but is much more expensive.
			 * The incoming colors are in RGB space, and the output color will be RGB.  The alpha value will also be interpolated.
			 *
			 * @param	From		The color and alpha to interpolate from as linear RGBA
			 * @param	To			The color and alpha to interpolate to as linear RGBA
			 * @param	Progress	Scalar interpolation amount (usually between 0.0 and 1.0 inclusive)
			 * @return	The interpolated color in linear RGB space along with the interpolated alpha value
			 */
			static FLinearColor LerpUsingHSV ( const FLinearColor& From, const FLinearColor& To, const float Progress );

			/** Quantizes the linear color and returns the result as a FColor.  This bypasses the SRGB conversion. */
			FColor Quantize ( ) const;

			/** Quantizes the linear color with rounding and returns the result as a FColor.  This bypasses the SRGB conversion. */
			FColor QuantizeRound ( ) const;

			/** Quantizes the linear color and returns the result as a FColor with optional sRGB conversion and quality as goal. */
			FColor ToFColor ( const bool bSRGB ) const;

			/**
			 * Returns a desaturated color, with 0 meaning no desaturation and 1 == full desaturation
			 *
			 * @param	Desaturation	Desaturation factor in range [0..1]
			 * @return	Desaturated color
			 */
			FLinearColor Desaturate ( float Desaturation ) const;

			/** Computes the perceptually weighted luminance value of a color. */
			inline float ComputeLuminance ( ) const
			{
				return R * 0.3f + G * 0.59f + B * 0.11f;
			}

			/**
			 * Returns the maximum value in this color structure
			 *
			 * @return The maximum color channel value
			 */
			LOO_FORCEINLINE float GetMax ( ) const
			{
				return loo::math::max( loo::math::max( loo::math::max( R, G ), B ), A );
			}

			/** useful to detect if a light contribution needs to be rendered */
			bool IsAlmostBlack ( ) const
			{
				return loo::math::square ( R ) < DELTA && loo::math::square ( G ) < DELTA && loo::math::square ( B ) < DELTA;
			}

			/**
			 * Returns the minimum value in this color structure
			 *
			 * @return The minimum color channel value
			 */
			LOO_FORCEINLINE float GetMin ( ) const
			{
				return loo::math::min ( loo::math::min ( loo::math::min ( R, G ), B ), A );
			}

			LOO_FORCEINLINE float GetLuminance ( ) const
			{
				return R * 0.3f + G * 0.59f + B * 0.11f;
			}

			std::string ToString ( ) const
			{
				
				return loo::global::Printf ( "(R=%f,G=%f,B=%f,A=%f)" , R, G, B, A );
			}

			/**
			 * Initialize this Color based on an std::string. The String is expected to contain R=, G=, B=, A=.
			 * The FLinearColor will be bogus when InitFromString returns false.
			 *
			 * @param InSourceString std::string containing the color values.
			 * @return true if the R,G,B values were read successfully; false otherwise.
			 */
			//bool InitFromString ( const std::string& InSourceString )
			//{
			//	R = G = B = 0.f;
			//	A = 1.f;

			//	// The initialization is only successful if the R, G, and B values can all be parsed from the string
			//	const bool bSuccessful = FParse::Value ( *InSourceString, TEXT ( "R=" ), R ) && FParse::Value ( *InSourceString, TEXT ( "G=" ), G ) && FParse::Value ( *InSourceString, TEXT ( "B=" ), B );

			//	// Alpha is optional, so don't factor in its presence (or lack thereof) in determining initialization success
			//	FParse::Value ( *InSourceString, TEXT ( "A=" ), A );

			//	return bSuccessful;
			//}

			// Common colors.	
			static const FLinearColor White;
			static const FLinearColor Gray;
			static const FLinearColor Black;
			static const FLinearColor Transparent;
			static const FLinearColor Red;
			static const FLinearColor Green;
			static const FLinearColor Blue;
			static const FLinearColor Yellow;
		};

		LOO_FORCEINLINE FLinearColor operator*( float Scalar, const FLinearColor& Color )
		{
			return Color.operator*( Scalar );
		}


		//
		//	FColor
		//	Stores a color with 8 bits of precision per channel.  
		//	Note: Linear color values should always be converted to gamma space before stored in an FColor, as 8 bits of precision is not enough to store linear space colors!
		//	This can be done with FLinearColor::ToFColor(true) 
		//

		struct FColor
		{
		public:
			// Variables.
		
#if defined(LOO_PLATFORM_LITTLE_ENDIAN)
#ifdef _MSC_VER
			// Win32 x86
			union { struct { uint8 B, G, R, A; }; uint32 AlignmentDummy; };
#else
	// Linux x86, etc
			uint8 B GCC_ALIGN ( 4 );
			uint8 G, R, A;
#endif
#else // PLATFORM_LITTLE_ENDIAN
			union { struct { uint8 A, R, G, B; }; uint32 AlignmentDummy; };
#endif

			uint32& DWColor ( void ) { return *((uint32*)this); }
			const uint32& DWColor ( void ) const { return *((uint32*)this); }

			// Constructors.
			LOO_FORCEINLINE FColor ( ) {}
			LOO_FORCEINLINE explicit FColor ( EForceInit )
			{
				// put these into the body for proper ordering with INTEL vs non-INTEL_BYTE_ORDER
				R = G = B = A = 0;
			}
			LOO_FORCEINLINE FColor ( uint8 InR, uint8 InG, uint8 InB, uint8 InA = 255 )
			{
				// put these into the body for proper ordering with INTEL vs non-INTEL_BYTE_ORDER
				R = InR;
				G = InG;
				B = InB;
				A = InA;

			}

			LOO_FORCEINLINE explicit FColor ( uint32 InColor )
			{
				DWColor ( ) = InColor;
			}

			// Serializer.
			friend std::ostream& operator<< ( std::ostream &Ar, FColor &Color )
			{
				return Ar << Color.DWColor ( );
			}

			bool Serialize ( std::ostream& Ar )
			{
				Ar << *this;
				return true;
			}

			// Operators.
			LOO_FORCEINLINE bool operator==( const FColor &C ) const
			{
				return DWColor ( ) == C.DWColor ( );
			}

			LOO_FORCEINLINE bool operator!=( const FColor& C ) const
			{
				return DWColor ( ) != C.DWColor ( );
			}

			LOO_FORCEINLINE void operator+=( const FColor& C )
			{
				R = (uint8)loo::math::min ( (int32)R + (int32)C.R, 255 );
				G = (uint8)loo::math::min ( (int32)G + (int32)C.G, 255 );
				B = (uint8)loo::math::min ( (int32)B + (int32)C.B, 255 );
				A = (uint8)loo::math::min ( (int32)A + (int32)C.A, 255 );
			}

			FLinearColor FromRGBE ( ) const;

			/**
			 * Creates a color value from the given hexadecimal string.
			 *
			 * Supported formats are: RGB, RRGGBB, RRGGBBAA, #RGB, #RRGGBB, #RRGGBBAA
			 *
			 * @param HexString - The hexadecimal string.
			 * @return The corresponding color value.
			 * @see ToHex
			 */
			//static FColor FromHex ( const std::string& HexString );

			/**
			 * Makes a random but quite nice color.
			 */
			static FColor MakeRandomColor ( );

			/**
			 * Makes a color red->green with the passed in scalar (e.g. 0 is red, 1 is green)
			 */
			static FColor MakeRedToGreenColorFromScalar ( float Scalar );

			/**
			* Converts temperature in Kelvins of a black body radiator to RGB chromaticity.
			*/
			static FColor MakeFromColorTemperature ( float Temp );

			/**
			 *	@return a new FColor based of this color with the new alpha value.
			 *	Usage: const FColor& MyColor = FColorList::Green.WithAlpha(128);
			 */
			FColor WithAlpha ( uint8 Alpha ) const
			{
				return FColor ( R, G, B, Alpha );
			}

			/**
			 * Reinterprets the color as a linear color.
			 *
			 * @return The linear color representation.
			 */
			LOO_FORCEINLINE FLinearColor ReinterpretAsLinear ( ) const
			{
				return FLinearColor ( R / 255.f, G / 255.f, B / 255.f, A / 255.f );
			}

			/**
			 * Converts this color value to a hexadecimal string.
			 *
			 * The format of the string is RRGGBBAA.
			 *
			 * @return Hexadecimal string.
			 * @see FromHex, ToString
			 */
			LOO_FORCEINLINE std::string ToHex ( ) const
			{
				return loo::global::Printf ( ( "%02X%02X%02X%02X" ), R, G, B, A );
			}

			/**
			 * Converts this color value to a string.
			 *
			 * @return The string representation.
			 * @see ToHex
			 */
			LOO_FORCEINLINE std::string ToString ( ) const
			{
				return loo::global::Printf (  ( "(R=%i,G=%i,B=%i,A=%i)" ), R, G, B, A );
			}

			/**
			 * Initialize this Color based on an std::string. The String is expected to contain R=, G=, B=, A=.
			 * The FColor will be bogus when InitFromString returns false.
			 *
			 * @param	InSourceString	std::string containing the color values.
			 * @return true if the R,G,B values were read successfully; false otherwise.
			 */
			//bool InitFromString ( const std::string& InSourceString )
			//{
			//	R = G = B = 0;
			//	A = 255;

			//	// The initialization is only successful if the R, G, and B values can all be parsed from the string
			//	const bool bSuccessful = FParse::Value ( *InSourceString, TEXT ( "R=" ), R ) && FParse::Value ( *InSourceString, TEXT ( "G=" ), G ) && FParse::Value ( *InSourceString, TEXT ( "B=" ), B );

			//	// Alpha is optional, so don't factor in its presence (or lack thereof) in determining initialization success
			//	FParse::Value ( *InSourceString, TEXT ( "A=" ), A );

			//	return bSuccessful;
			//}

			/**
			 * Gets the color in a packed uint32 format packed in the order ARGB.
			 */
			LOO_FORCEINLINE uint32 ToPackedARGB ( ) const
			{
				return (A << 24) | (R << 16) | (G << 8) | (B << 0);
			}

			/**
			 * Gets the color in a packed uint32 format packed in the order ABGR.
			 */
			LOO_FORCEINLINE uint32 ToPackedABGR ( ) const
			{
				return (A << 24) | (B << 16) | (G << 8) | (R << 0);
			}

			/**
			 * Gets the color in a packed uint32 format packed in the order RGBA.
			 */
			LOO_FORCEINLINE uint32 ToPackedRGBA ( ) const
			{
				return (R << 24) | (G << 16) | (B << 8) | (A << 0);
			}

			/**
			 * Gets the color in a packed uint32 format packed in the order BGRA.
			 */
			LOO_FORCEINLINE uint32 ToPackedBGRA ( ) const
			{
				return (B << 24) | (G << 16) | (R << 8) | (A << 0);
			}

			/** Some pre-inited colors, useful for debug code */
			static const FColor White;
			static const FColor Black;
			static const FColor Transparent;
			static const FColor Red;
			static const FColor Green;
			static const FColor Blue;
			static const FColor Yellow;
			static const FColor Cyan;
			static const FColor Magenta;
			static const FColor Orange;
			static const FColor Purple;
			static const FColor Turquoise;
			static const FColor Silver;
			static const FColor Emerald;

		private:
			/**
			 * Please use .ToFColor(true) on FLinearColor if you wish to convert from FLinearColor to FColor,
			 * with proper sRGB conversion applied.
			 *
			 * Note: Do not implement or make public.  We don't want people needlessly and implicitly converting between
			 * FLinearColor and FColor.  It's not a free conversion.
			 */
			explicit FColor ( const FLinearColor& LinearColor );
		};

		LOO_FORCEINLINE uint32 GetTypeHash ( const FColor& Color )
		{
			return Color.DWColor ( );
		}


		//LOO_FORCEINLINE uint32 GetTypeHash ( const FLinearColor& LinearColor )
		//{
		//	// Note: this assumes there's no padding in FLinearColor that could contain uncompared data.
		//	return FCrc::MemCrc_DEPRECATED ( &LinearColor, sizeof ( FLinearColor ) );
		//}


		/** Computes a brightness and a fixed point color from a floating point color. */
		extern void ComputeAndFixedColorAndIntensity ( const FLinearColor& InLinearColor, FColor& OutColor, float& OutIntensity );

		struct FDXTColor565
		{
			/** Blue component, 5 bit. */
			uint16 B : 5;

			/** Green component, 6 bit. */
			uint16 G : 6;

			/** Red component, 5 bit */
			uint16 R : 5;
		};


		/**
		 * Helper struct for a 16 bit 565 color of a DXT1/3/5 block.
		 */
		struct FDXTColor16
		{
			union
			{
				/** 565 Color */
				FDXTColor565 Color565;
				/** 16 bit entity representation for easy access. */
				uint16 Value;
			};
		};


		/**
		 * Structure encompassing single DXT1 block.
		 */
		struct FDXT1
		{
			/** Color 0/1 */
			union
			{
				FDXTColor16 Color[2];
				uint32 Colors;
			};
			/** Indices controlling how to blend colors. */
			uint32 Indices;
		};


		/**
		 * Structure encompassing single DXT5 block
		 */
		struct FDXT5
		{
			/** Alpha component of DXT5 */
			uint8	Alpha[8];
			/** DXT1 color component. */
			FDXT1	DXT1;
		};



		// RGBA，float4:r, g, b, a
		///////////////////////////////////////////////////////////////////////////////
		//template <typename T>
		//class Color_T final : boost::addable<Color_T<T>,
		//	boost::subtractable<Color_T<T>,
		//	boost::dividable2<Color_T<T>, T,
		//	boost::multipliable<Color_T<T>,
		//	boost::multipliable2<Color_T<T>, T,
		//	boost::equality_comparable<Color_T<T>>>>>>>
		//{
		//public:
		//	typedef T value_type;
		//	
		//	typedef typename vec4::pointer pointer;
		//	typedef typename vec4::const_pointer const_pointer;

		//	typedef typename vec4::reference reference;
		//	typedef typename vec4::const_reference const_reference;

		//	typedef typename vec4::iterator iterator;
		//	typedef typename vec4::const_iterator const_iterator;

		//public:
		//	constexpr Color_T ( ) noexcept
		//	{
		//	}
		//	explicit constexpr Color_T ( T const * rhs ) noexcept
		//		: col_ ( rhs )
		//	{
		//	}
		//	Color_T ( Color_T const & rhs ) noexcept;
		//	Color_T ( Color_T&& rhs ) noexcept;
		//	constexpr Color_T ( T r, T g, T b, T a ) noexcept
		//		: col_ ( r, g, b, a )
		//	{
		//	}
		//	explicit Color_T ( uint32_t dw ) noexcept;

		//	// 
		//	iterator begin ( ) noexcept
		//	{
		//		return col_.begin ( );
		//	}
		//	constexpr const_iterator begin ( ) const noexcept
		//	{
		//		return col_.begin ( );
		//	}
		//	iterator end ( ) noexcept
		//	{
		//		return col_.end ( );
		//	}
		//	constexpr const_iterator end ( ) const noexcept
		//	{
		//		return col_.end ( );
		//	}
		//	reference operator[]( size_t index ) noexcept
		//	{
		//		return col_[index];
		//	}
		//	constexpr const_reference operator[]( size_t index ) const noexcept
		//	{
		//		return col_[index];
		//	}

		//	reference r ( ) noexcept
		//	{
		//		return col_[0];
		//	}
		//	constexpr const_reference r ( ) const noexcept
		//	{
		//		return col_[0];
		//	}
		//	reference g ( ) noexcept
		//	{
		//		return col_[1];
		//	}
		//	constexpr const_reference g ( ) const noexcept
		//	{
		//		return col_[1];
		//	}
		//	reference b ( ) noexcept
		//	{
		//		return col_[2];
		//	}
		//	constexpr const_reference b ( ) const noexcept
		//	{
		//		return col_[2];
		//	}
		//	reference a ( ) noexcept
		//	{
		//		return col_[3];
		//	}
		//	constexpr const_reference a ( ) const noexcept
		//	{
		//		return col_[3];
		//	}

		//	void RGBA ( uint8_t& R, uint8_t& G, uint8_t& B, uint8_t& A ) const noexcept;

		//	uint32_t ARGB ( ) const noexcept;
		//	uint32_t ABGR ( ) const noexcept;

		//	// 
		//	Color_T& operator+=( Color_T<T> const & rhs ) noexcept;
		//	Color_T& operator-=( Color_T<T> const & rhs ) noexcept;
		//	Color_T& operator*=( T rhs ) noexcept;
		//	Color_T& operator*=( Color_T<T> const & rhs ) noexcept;
		//	Color_T& operator/=( T rhs ) noexcept;

		//	Color_T& operator=( Color_T const & rhs ) noexcept;
		//	Color_T& operator=( Color_T&& rhs ) noexcept;

		//	// 
		//	Color_T const operator+( ) const noexcept;
		//	Color_T const operator-( ) const noexcept;

		//	bool operator==( Color_T<T> const & rhs ) const noexcept;

		//private:
		//	vec4 col_;
		//};


	}
}


namespace loo
{
	namespace math
	{
		template <typename T>
		struct RGBAColor
		{
			// types
			using Self = RGBAColor<T>;
			using value_type = T;

			// variables
			T	r, g, b, a;

			// methods
			constexpr RGBAColor () : r{ T (0) }, g{ T (0) }, b{ T (0) }, a{ T (0) }
			{
				// check if supported cast from Color to array
				STATIC_ASSERT (offsetof (Self, r) + sizeof (T) == offsetof (Self, g));
				STATIC_ASSERT (offsetof (Self, g) + sizeof (T) == offsetof (Self, b));
				STATIC_ASSERT (offsetof (Self, b) + sizeof (T) == offsetof (Self, a));
				STATIC_ASSERT (sizeof (T)*(size () - 1) == (offsetof (Self, a) - offsetof (Self, r)));
			}

			constexpr RGBAColor (T r, T g, T b, T a) : r{ r }, g{ g }, b{ b }, a{ a }
			{}

			constexpr explicit RGBAColor (T val) : r{ val }, g{ val }, b{ val }, a{ val }
			{}

			template <typename B>
			constexpr explicit RGBAColor (const RGBAColor<B> &other);

			explicit RGBAColor (struct HSVColor const& hsv, T alpha = MaxValue ());


			constexpr bool operator == (const RGBAColor<T> &rhs) const
			{
				const T  eps = Epsilon ();
				return	Equals (r, rhs.r, eps) &
					Equals (g, rhs.g, eps) &
					Equals (b, rhs.b, eps) &
					Equals (a, rhs.a, eps);
			}

			constexpr bool operator != (const RGBAColor<T> &rhs) const { return not (*this == rhs); }

			static constexpr T  MaxValue ()
			{
				if constexpr (IsFloatPoint<T>)
					return T (1.0);
				else
					return std::numeric_limits<T>::max ();
			}

			static constexpr T  Epsilon ()
			{
				if (IsFloatPoint<T>)
					return T (0.001);
				else
					return T (0);
			}

			static constexpr size_t		size () { return 4; }

			T *			data () { return std::addressof (r); }
			T const *	data ()					const { return std::addressof (r); }

			T &			operator [] (size_t i) { LOO_ASSUME (i < size ());  return std::addressof (r)[i]; }
			T const&	operator [] (size_t i)	const { LOO_ASSUME (i < size ());  return std::addressof (r)[i]; }
		};

		using RGBA32f = RGBAColor< float >;
		using RGBA32i = RGBAColor< int >;
		using RGBA32u = RGBAColor< uint32 >;
		using RGBA8u = RGBAColor< uint8_t >;

		//
		// Depth Stencil
		//
		struct DepthStencil
		{
			// variables
			float	depth;
			uint32	stencil;

			// mathods
			constexpr DepthStencil () : depth (0.0f), stencil (0) {}
			constexpr explicit DepthStencil (float depth, uint32 stencil = 0) : depth (depth), stencil (stencil) {}

			bool operator == (const DepthStencil &rhs) const
			{
				return Equals (depth, rhs.depth) & (stencil == rhs.stencil);
			}
		};



		//
		// HSV Color
		//
		struct HSVColor
		{
			// variables
			float	h;	// hue
			float	s;	// saturation
			float	v;	// value, brightness

		// methods
			constexpr HSVColor () : h{ 0.0f }, s{ 0.0f }, v{ 0.0f } {}

			explicit constexpr HSVColor (float h, float s = 1.0f, float v = 1.0f) : h{ h }, s{ s }, v{ v } {}

			explicit HSVColor (const RGBA32f &c)
			{
				// from http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl			
				f32vec4 K = f32vec4 (0.0f, -1.0f / 3.0f, 2.0f / 3.0f, -1.0f);
				f32vec4 p = c.g < c.b ? f32vec4 (c.b, c.g, K.w, K.z) : f32vec4 (c.g, c.b, K.x, K.y);
				f32vec4 q = c.r < p.x ? f32vec4 (p.x, p.y, p.w, c.r) : f32vec4 (c.r, p.y, p.z, p.x);
				float  d = q.x - glm::min (q.w, q.y);
				float  e = 1.0e-10f;
				h = glm::abs (q.z + (q.w - q.y) / (6.0f * d + e));
				s = d / (q.x + e);
				v = q.x;
			}

			constexpr bool  operator == (const HSVColor &rhs) const
			{
				const float eps = RGBA32f::Epsilon ();

				return Equals (h, rhs.h, eps) & Equals (s, rhs.s, eps) & Equals (v, rhs.v, eps);
			}

			float *			data () { return std::addressof (h); }
			float const *	data ()	const { return std::addressof (h); }
		};

		/*
		=================================================
			RGBA32f
		=================================================
		*/
		template <>
		inline RGBAColor<float>::RGBAColor (const HSVColor &c, float alpha)
		{
			// from http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
			f32vec4 K = f32vec4 (1.0f, 2.0f / 3.0f, 1.0f / 3.0f, 3.0f);
			f32vec3 p = glm::abs (glm::fract (c.h + f32vec3 (K.x, K.y, K.z)) * 6.0f - K.w);
			r = c.v * glm::lerp (K.x, glm::clamp (p.x - K.x, 0.0f, 1.0f), c.s);
			g = c.v * glm::lerp (K.x, glm::clamp (p.y - K.x, 0.0f, 1.0f), c.s);
			b = c.v * glm::lerp (K.x, glm::clamp (p.z - K.x, 0.0f, 1.0f), c.s);
			a = alpha;
		}

		template <> template <>
		inline constexpr RGBAColor<float>::RGBAColor (const RGBAColor<uint8_t> &other) :
			r{ float (other.r) / 255.0f }, g{ float (other.g) / 255.0f },
			b{ float (other.b) / 255.0f }, a{ float (other.a) / 255.0f }
		{}

		template <> template <>
		inline constexpr RGBAColor<float>::RGBAColor (const RGBAColor<uint32> &other) :
			r{ float (other.r) / 0xFFFFFFFFu }, g{ float (other.g) / 0xFFFFFFFFu },
			b{ float (other.b) / 0xFFFFFFFFu }, a{ float (other.a) / 0xFFFFFFFFu }
		{}

		/*
		=================================================
			RGBA32i
		=================================================
		*/
		template <> template <>
		inline constexpr RGBAColor<int>::RGBAColor (const RGBAColor<uint32> &other) :
			r{ int (other.r) }, g{ int (other.g) }, b{ int (other.b) }, a{ int (other.a) }
		{}

		template <> template <>
		inline constexpr RGBAColor<int>::RGBAColor (const RGBAColor<uint8_t> &other) :
			r{ int (other.r) }, g{ int (other.g) }, b{ int (other.b) }, a{ int (other.a) }
		{}

		/*
		=================================================
			RGBA32u
		=================================================
		*/
		template <> template <>
		inline constexpr RGBAColor<uint32>::RGBAColor (const RGBAColor<int> &other) :
			r{ uint32 (other.r) }, g{ uint32 (other.g) }, b{ uint32 (other.b) }, a{ uint32 (other.a) }
		{}

		template <> template <>
		inline constexpr RGBAColor<uint32>::RGBAColor (const RGBAColor<uint8_t> &other) :
			r{ uint32 (other.r) }, g{ uint32 (other.g) }, b{ uint32 (other.b) }, a{ uint32 (other.a) }
		{}

		/*
		=================================================
			RGBA8u
		=================================================
		*/
		template <> template <>
		inline constexpr RGBAColor<uint8_t>::RGBAColor (const RGBAColor<int> &other) :
			r{ uint8_t (other.r) }, g{ uint8_t (other.g) }, b{ uint8_t (other.b) }, a{ uint8_t (other.a) }
		{}

		template <> template <>
		inline constexpr RGBAColor<uint8_t>::RGBAColor (const RGBAColor<uint32> &other) :
			r{ uint8_t (other.r) }, g{ uint8_t (other.g) }, b{ uint8_t (other.b) }, a{ uint8_t (other.a) }
		{}

		template <> template <>
		inline constexpr RGBAColor<uint8_t>::RGBAColor (const RGBAColor<float> &other) :
			r{ uint8_t (other.r * 255.0f + 0.5f) }, g{ uint8_t (other.g * 255.0f + 0.5f) },
			b{ uint8_t (other.b * 255.0f + 0.5f) }, a{ uint8_t (other.a * 255.0f + 0.5f) }
		{}

		inline constexpr RGBA8u  AdjustContrast (const RGBA8u &col, float factor)
		{
			constexpr float	mid = 127.0f;
			RGBA8u			result;
			result.r = uint8_t (mid + factor * (float (col.r) - mid) + 0.5f);
			result.g = uint8_t (mid + factor * (float (col.g) - mid) + 0.5f);
			result.b = uint8_t (mid + factor * (float (col.b) - mid) + 0.5f);
			result.a = col.a;
			return result;
		}

		inline constexpr float  Luminance (const RGBA8u &col)
		{
			constexpr float  scale = 1.0f / (255.0f * 255.0f * 255.0f);
			return (float (col.r) * 0.2126f + float (col.g) * float (col.b) * 0.7152f + 0.0722f) * scale;
		}

		inline constexpr RGBA8u  AdjustSaturation (const RGBA8u &col, float factor)
		{
			RGBA8u			result;
			const float		lum = Luminance (col);
			result.r = uint8_t (lum + factor * (float (col.r) - lum) + 0.5f);
			result.g = uint8_t (lum + factor * (float (col.g) - lum) + 0.5f);
			result.b = uint8_t (lum + factor * (float (col.b) - lum) + 0.5f);
			result.a = col.a;
			return result;
		}

		inline /*constexpr*/ RGBA8u  Lerp (const RGBA8u &x, const RGBA8u &y, float factor)
		{
			f32vec4 v = glm::lerp (f32vec4{ float (x.r), float (x.g), float (x.b), float (x.a) },
				f32vec4{ float (y.r), float (y.g), float (y.b), float (y.a) }, factor);

			return RGBA8u{ uint8_t (v.x + 0.5f), uint8_t (v.y + 0.5f),
						   uint8_t (v.z + 0.5f), uint8_t (v.w + 0.5f) };
		}



		/*
		=================================================
			Min/Max/Clamp
		=================================================
		*/
		template <typename T>
		inline constexpr RGBAColor<T>  Min (const RGBAColor<T> &lhs, const RGBAColor<T> &rhs)
		{
			return RGBAColor<T>{ Min (lhs.r, rhs.r), Min (lhs.g, rhs.g), Min (lhs.b, rhs.b), Min (lhs.a, rhs.a) };
		}

		template <typename T>
		inline constexpr RGBAColor<T>  Max (const RGBAColor<T> &lhs, const RGBAColor<T> &rhs)
		{
			return RGBAColor<T>{ Max (lhs.r, rhs.r), Max (lhs.g, rhs.g), Max (lhs.b, rhs.b), Max (lhs.a, rhs.a) };
		}

		template <typename T>
		inline constexpr RGBAColor<T>  Clamp (const RGBAColor<T> &value, const RGBAColor<T> &minVal, const RGBAColor<T> &maxVal)
		{
			return Min (maxVal, Max (value, minVal));
		}

		/*
		=================================================
			Equals
		=================================================
		*/
		template <typename T>
		inline constexpr bvec4  Equals (const RGBAColor<T> &lhs, const RGBAColor<T> &rhs, const T &err = std::numeric_limits<T>::epsilon () * T (2))
		{
			return bvec4{ Equals (lhs.r, rhs.r, err), Equals (lhs.g, rhs.g, err), Equals (lhs.b, rhs.b, err), Equals (lhs.a, rhs.a, err) };
		}

		/*
		=================================================
			HtmlColor
		=================================================
		*/
		struct HtmlColor
		{
			// see https://www.w3schools.com/colors/colors_names.asp
#		define DEF_COLOR( _name_, _color_ )	static constexpr RGBA8u	_name_ \
											{ (_color_ >> 16) & 0xFF, (_color_ >> 8) & 0xFF, (_color_ >> 0) & 0xFF, 0xFF };

			DEF_COLOR (AliceBlue, 0xF0F8FF)
			DEF_COLOR (AntiqueWhite, 0xFAEBD7)
			DEF_COLOR (Aqua, 0x00FFFF)
			DEF_COLOR (Aquamarine, 0x7FFFD4)
			DEF_COLOR (Azure, 0xF0FFFF)
			DEF_COLOR (Beige, 0xF5F5DC)
			DEF_COLOR (Bisque, 0xFFE4C4)
			DEF_COLOR (Black, 0x000000)
			DEF_COLOR (BlanchedAlmond, 0xFFEBCD)
			DEF_COLOR (Blue, 0x0000FF)
			DEF_COLOR (BlueViolet, 0x8A2BE2)
			DEF_COLOR (Brown, 0xA52A2A)
			DEF_COLOR (BurlyWood, 0xDEB887)
			DEF_COLOR (CadetBlue, 0x5F9EA0)
			DEF_COLOR (Chartreuse, 0x7FFF00)
			DEF_COLOR (Chocolate, 0xD2691E)
			DEF_COLOR (Coral, 0xFF7F50)
			DEF_COLOR (CornflowerBlue, 0x6495ED)
			DEF_COLOR (Cornsilk, 0xFFF8DC)
			DEF_COLOR (Crimson, 0xDC143C)
			DEF_COLOR (Cyan, 0x00FFFF)
			DEF_COLOR (DarkBlue, 0x00008B)
			DEF_COLOR (DarkCyan, 0x008B8B)
			DEF_COLOR (DarkGoldenRod, 0xB8860B)
			DEF_COLOR (DarkGray, 0xA9A9A9)
			DEF_COLOR (DarkGreen, 0x006400)
			DEF_COLOR (DarkKhaki, 0xBDB76B)
			DEF_COLOR (DarkMagenta, 0x8B008B)
			DEF_COLOR (DarkOliveGreen, 0x556B2F)
			DEF_COLOR (DarkOrange, 0xFF8C00)
			DEF_COLOR (DarkOrchid, 0x9932CC)
			DEF_COLOR (DarkRed, 0x8B0000)
			DEF_COLOR (DarkSalmon, 0xE9967A)
			DEF_COLOR (DarkSeaGreen, 0x8FBC8F)
			DEF_COLOR (DarkSlateBlue, 0x483D8B)
			DEF_COLOR (DarkSlateGray, 0x2F4F4F)
			DEF_COLOR (DarkTurquoise, 0x00CED1)
			DEF_COLOR (DarkViolet, 0x9400D3)
			DEF_COLOR (DeepPink, 0xFF1493)
			DEF_COLOR (DeepSkyBlue, 0x00BFFF)
			DEF_COLOR (DimGray, 0x696969)
			DEF_COLOR (DodgerBlue, 0x1E90FF)
			DEF_COLOR (FireBrick, 0xB22222)
			DEF_COLOR (FloralWhite, 0xFFFAF0)
			DEF_COLOR (ForestGreen, 0x228B22)
			DEF_COLOR (Fuchsia, 0xFF00FF)
			DEF_COLOR (Gainsboro, 0xDCDCDC)
			DEF_COLOR (GhostWhite, 0xF8F8FF)
			DEF_COLOR (Gold, 0xFFD700)
			DEF_COLOR (GoldenRod, 0xDAA520)
			DEF_COLOR (Gray, 0x808080)
			DEF_COLOR (Green, 0x008000)
			DEF_COLOR (GreenYellow, 0xADFF2F)
			DEF_COLOR (HoneyDew, 0xF0FFF0)
			DEF_COLOR (HotPink, 0xFF69B4)
			DEF_COLOR (IndianRed, 0xCD5C5C)
			DEF_COLOR (Indigo, 0x4B0082)
			DEF_COLOR (Ivory, 0xFFFFF0)
			DEF_COLOR (Khaki, 0xF0E68C)
			DEF_COLOR (Lavender, 0xE6E6FA)
			DEF_COLOR (LavenderBlush, 0xFFF0F5)
			DEF_COLOR (LawnGreen, 0x7CFC00)
			DEF_COLOR (LemonChiffon, 0xFFFACD)
			DEF_COLOR (LightBlue, 0xADD8E6)
			DEF_COLOR (LightCoral, 0xF08080)
			DEF_COLOR (LightCyan, 0xE0FFFF)
			DEF_COLOR (LightGoldenRodYellow, 0xFAFAD2)
			DEF_COLOR (LightGray, 0xD3D3D3)
			DEF_COLOR (LightGreen, 0x90EE90)
			DEF_COLOR (LightPink, 0xFFB6C1)
			DEF_COLOR (LightSalmon, 0xFFA07A)
			DEF_COLOR (LightSeaGreen, 0x20B2AA)
			DEF_COLOR (LightSkyBlue, 0x87CEFA)
			DEF_COLOR (LightSlateGray, 0x778899)
			DEF_COLOR (LightSteelBlue, 0xB0C4DE)
			DEF_COLOR (LightYellow, 0xFFFFE0)
			DEF_COLOR (Lime, 0x00FF00)
			DEF_COLOR (LimeGreen, 0x32CD32)
			DEF_COLOR (Linen, 0xFAF0E6)
			DEF_COLOR (Magenta, 0xFF00FF)
			DEF_COLOR (Maroon, 0x800000)
			DEF_COLOR (MediumAquaMarine, 0x66CDAA)
			DEF_COLOR (MediumBlue, 0x0000CD)
			DEF_COLOR (MediumOrchid, 0xBA55D3)
			DEF_COLOR (MediumPurple, 0x9370DB)
			DEF_COLOR (MediumSeaGreen, 0x3CB371)
			DEF_COLOR (MediumSlateBlue, 0x7B68EE)
			DEF_COLOR (MediumSpringGreen, 0x00FA9A)
			DEF_COLOR (MediumTurquoise, 0x48D1CC)
			DEF_COLOR (MediumVioletRed, 0xC71585)
			DEF_COLOR (MidnightBlue, 0x191970)
			DEF_COLOR (MintCream, 0xF5FFFA)
			DEF_COLOR (MistyRose, 0xFFE4E1)
			DEF_COLOR (Moccasin, 0xFFE4B5)
			DEF_COLOR (NavajoWhite, 0xFFDEAD)
			DEF_COLOR (Navy, 0x000080)
			DEF_COLOR (OldLace, 0xFDF5E6)
			DEF_COLOR (Olive, 0x808000)
			DEF_COLOR (OliveDrab, 0x6B8E23)
			DEF_COLOR (Orange, 0xFFA500)
			DEF_COLOR (OrangeRed, 0xFF4500)
			DEF_COLOR (Orchid, 0xDA70D6)
			DEF_COLOR (PaleGoldenRod, 0xEEE8AA)
			DEF_COLOR (PaleGreen, 0x98FB98)
			DEF_COLOR (PaleTurquoise, 0xAFEEEE)
			DEF_COLOR (PaleVioletRed, 0xDB7093)
			DEF_COLOR (PapayaWhip, 0xFFEFD5)
			DEF_COLOR (PeachPuff, 0xFFDAB9)
			DEF_COLOR (Peru, 0xCD853F)
			DEF_COLOR (Pink, 0xFFC0CB)
			DEF_COLOR (Plum, 0xDDA0DD)
			DEF_COLOR (PowderBlue, 0xB0E0E6)
			DEF_COLOR (Purple, 0x800080)
			DEF_COLOR (Red, 0xFF0000)
			DEF_COLOR (RosyBrown, 0xBC8F8F)
			DEF_COLOR (RoyalBlue, 0x4169E1)
			DEF_COLOR (SaddleBrown, 0x8B4513)
			DEF_COLOR (Salmon, 0xFA8072)
			DEF_COLOR (SandyBrown, 0xF4A460)
			DEF_COLOR (SeaGreen, 0x2E8B57)
			DEF_COLOR (SeaShell, 0xFFF5EE)
			DEF_COLOR (Sienna, 0xA0522D)
			DEF_COLOR (Silver, 0xC0C0C0)
			DEF_COLOR (SkyBlue, 0x87CEEB)
			DEF_COLOR (SlateBlue, 0x6A5ACD)
			DEF_COLOR (SlateGray, 0x708090)
			DEF_COLOR (Snow, 0xFFFAFA)
			DEF_COLOR (SpringGreen, 0x00FF7F)
			DEF_COLOR (SteelBlue, 0x4682B4)
			DEF_COLOR (Tan, 0xD2B48C)
			DEF_COLOR (Teal, 0x008080)
			DEF_COLOR (Thistle, 0xD8BFD8)
			DEF_COLOR (Tomato, 0xFF6347)
			DEF_COLOR (Turquoise, 0x40E0D0)
			DEF_COLOR (Violet, 0xEE82EE)
			DEF_COLOR (Wheat, 0xF5DEB3)
			DEF_COLOR (White, 0xFFFFFF)
			DEF_COLOR (WhiteSmoke, 0xF5F5F5)
			DEF_COLOR (Yellow, 0xFFFF00)
			DEF_COLOR (YellowGreen, 0x9ACD32)

#		undef DEF_COLOR
		};
	}
}

namespace std
{
	template <typename T>
	struct hash< loo::math::RGBAColor<T> >
	{
		size_t  operator () (const loo::math::RGBAColor<T> &value) const
		{
			return	size_t (loo::HashOf (value.r) + loo::HashOf (value.g) +
				loo::HashOf (value.b) + loo::HashOf (value.a));
		}
	};


	template <>
	struct hash< loo::math::DepthStencil >
	{
		size_t  operator () (const loo::math::DepthStencil &value) const
		{
			return size_t (loo::HashOf (value.depth) + loo::HashOf (value.stencil));
		}
	};

}	// std

#endif			// LE_CORE_COLOR_H
