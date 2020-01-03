#ifndef LE_CORE_COLOR_H
#define LE_CORE_COLOR_H
#include "global/global.h"
#include "global/extstd/operators.h"
#include "global/math/math.h"
#include "global/template/externalstring.h"

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
		
#if defined(LE_PLATFORM_LITTLE_ENDIAN)
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

#endif			// LE_CORE_COLOR_H
