#pragma  once

#include "global/types.h"
#include "looreflect/looreflect.h"
#include "looreflect/looreflectmanager.h"
#include "core/event/event.h"

namespace loo
{
	namespace core
	{
		enum {
			SAPP_MAX_TOUCHPOINTS = 8,
			SAPP_MAX_MOUSEBUTTONS = 3,
			SAPP_MAX_KEYCODES = 512,
		};

		enum class LOOENUM () TouchType :uint32_t
		{
			//已发生移动。不能与 TOUCHEVENTF_DOWN 结合使用。
			Move LOOPROPERTY (Serialized) = 1,
			//通过新的触控点创建了相应的触控点。不能与 TOUCHEVENTF_MOVE 或 TOUCHEVENTF_UP 结合使用。
			Down LOOPROPERTY (Serialized) = 0x0002,
			//已删除触某个触控点。
			//Up LOOPROPERTY (Serialized) = 0x0004,
			//触控点在范围内。此标志用于在兼容硬盘上启用触控悬停支持。不需要悬停支持的应用程序可忽略此标志。
			Inrange LOOPROPERTY (Serialized) = 0x0008,
			//指示此 TOUCHINPUT 结构对应于主触控点。有关主触控点的更多信息，请参见以下文本。
			Primary LOOPROPERTY (Serialized) = 0x0010,
			//在使用 GetTouchInputInfo 接收时，未合并此输入。
			Nocoalesce LOOPROPERTY (Serialized) = 0x0020,
			Pen LOOPROPERTY (Serialized) = 0x0040,
			//触控事件来自用户的手掌。
			Palm LOOPROPERTY (Serialized) = 0x0080
		};

		enum class LOOENUM () TouchPointState :uint32_t
		{
			TouchPointPressed LOOPROPERTY (Serialized) = 0x01,
			TouchPointMoved LOOPROPERTY (Serialized) = 0x02,
			TouchPointStationary LOOPROPERTY (Serialized) = 0x04,
			TouchPointReleased LOOPROPERTY (Serialized) = 0x08
		};

		//todo reflact all members
		class LOOCLASS() TouchPoint //: public Object
		{
			LOOMETA_OBJECT;
		public:
			enum InfoFlag {
				Pen = 0x0001
			};
		public:
			virtual ~TouchPoint () {}
			LOOPROPERTY (Serialized)
			int id;//touch id,-1无效
			//LOOPROPERTY (Serialized)
			TouchPointState state;
			loo::math::float2 normalPosition;// touch device coordinates, (0 to 1, 0 to 1)
			loo::math::RectF area; // the touched area, centered at position in screen coordinates
			float pressure;// 0 to 1
			loo::math::float2 velocity;// in screen coordinate system, pixels / seconds
			InfoFlag flags;
			std::vector<loo::math::float2> rawPositions; // in screen coordinates
		};

		enum class LOOENUM() KeyCode:int
		{
			None LOOPROPERTY(Serialized) = 0,
			Backspace LOOPROPERTY(Serialized) = 8,
			Tab LOOPROPERTY(Serialized) = 9,
			Clear LOOPROPERTY(Serialized) = 12,
			Return LOOPROPERTY(Serialized) = 13,
			Pause LOOPROPERTY(Serialized) = 19,
			Escape LOOPROPERTY(Serialized) = 27,
			Space LOOPROPERTY(Serialized) = 32,
			Exclaim LOOPROPERTY(Serialized) = 33,
			DoubleQuote LOOPROPERTY(Serialized) = 34,
			Hash LOOPROPERTY(Serialized) = 35,
			Dollar LOOPROPERTY(Serialized) = 36,
			Percent LOOPROPERTY(Serialized) = 37,
			Ampersand LOOPROPERTY(Serialized) = 38,
			Quote LOOPROPERTY(Serialized) = 39,
			LeftParen LOOPROPERTY(Serialized) = 40,
			RightParen LOOPROPERTY(Serialized) = 41,
			Asterisk LOOPROPERTY(Serialized) = 42,
			Plus LOOPROPERTY(Serialized) = 43,
			Comma LOOPROPERTY(Serialized) = 44,
			Minus LOOPROPERTY(Serialized) = 45,
			Period LOOPROPERTY(Serialized) = 46,
			Slash LOOPROPERTY(Serialized) = 47,
			Alpha0 LOOPROPERTY(Serialized) = 48,
			Alpha1 LOOPROPERTY(Serialized) = 49,
			Alpha2 LOOPROPERTY(Serialized) = 50,
			Alpha3 LOOPROPERTY(Serialized) = 51,
			Alpha4 LOOPROPERTY(Serialized) = 52,
			Alpha5 LOOPROPERTY(Serialized) = 53,
			Alpha6 LOOPROPERTY(Serialized) = 54,
			Alpha7 LOOPROPERTY(Serialized) = 55,
			Alpha8 LOOPROPERTY(Serialized) = 56,
			Alpha9 LOOPROPERTY(Serialized) = 57,
			Colon LOOPROPERTY(Serialized) = 58,
			Semicolon LOOPROPERTY(Serialized) = 59,
			Less LOOPROPERTY(Serialized) = 60,
			Equals LOOPROPERTY(Serialized) = 61,
			Greater LOOPROPERTY(Serialized) = 62,
			Question LOOPROPERTY(Serialized) = 63,
			At LOOPROPERTY(Serialized) = 64,
			LeftBracket LOOPROPERTY(Serialized) = 91,
			Backslash LOOPROPERTY(Serialized) = 92,
			RightBracket LOOPROPERTY(Serialized) = 93,
			Caret LOOPROPERTY(Serialized) = 94,
			Underscore LOOPROPERTY(Serialized) = 95,
			BackQuote LOOPROPERTY(Serialized) = 96,
			A LOOPROPERTY(Serialized) = 97,
			B LOOPROPERTY(Serialized) = 98,
			C LOOPROPERTY(Serialized) = 99,
			D LOOPROPERTY(Serialized) = 100,
			E LOOPROPERTY(Serialized) = 101,
			F LOOPROPERTY(Serialized) = 102,
			G LOOPROPERTY(Serialized) = 103,
			H LOOPROPERTY(Serialized) = 104,
			I LOOPROPERTY(Serialized) = 105,
			J LOOPROPERTY(Serialized) = 106,
			K LOOPROPERTY(Serialized) = 107,
			L LOOPROPERTY(Serialized) = 108,
			M LOOPROPERTY(Serialized) = 109,
			N LOOPROPERTY(Serialized) = 110,
			O LOOPROPERTY(Serialized) = 111,
			P LOOPROPERTY(Serialized) = 112,
			Q LOOPROPERTY(Serialized) = 113,
			R LOOPROPERTY(Serialized) = 114,
			S LOOPROPERTY(Serialized) = 115,
			T LOOPROPERTY(Serialized) = 116,
			U LOOPROPERTY(Serialized) = 117,
			V LOOPROPERTY(Serialized) = 118,
			W LOOPROPERTY(Serialized) = 119,
			X LOOPROPERTY(Serialized) = 120,
			Y LOOPROPERTY(Serialized) = 121,
			Z LOOPROPERTY(Serialized) = 122,
			LeftCurlyBracket LOOPROPERTY(Serialized) = 123,
			Pipe LOOPROPERTY(Serialized) = 124,
			RightCurlyBracket LOOPROPERTY(Serialized) = 125,
			Tilde LOOPROPERTY(Serialized) = 126,
			Delete LOOPROPERTY(Serialized) = 127,
			Keypad0 LOOPROPERTY(Serialized) = 256,
			Keypad1 LOOPROPERTY(Serialized) = 257,
			Keypad2 LOOPROPERTY(Serialized) = 258,
			Keypad3 LOOPROPERTY(Serialized) = 259,
			Keypad4 LOOPROPERTY(Serialized) = 260,
			Keypad5 LOOPROPERTY(Serialized) = 261,
			Keypad6 LOOPROPERTY(Serialized) = 262,
			Keypad7 LOOPROPERTY(Serialized) = 263,
			Keypad8 LOOPROPERTY(Serialized) = 264,
			Keypad9 LOOPROPERTY(Serialized) = 265,
			KeypadPeriod LOOPROPERTY(Serialized) = 266,
			KeypadDivide LOOPROPERTY(Serialized) = 267,
			KeypadMultiply LOOPROPERTY(Serialized) = 268,
			KeypadMinus LOOPROPERTY(Serialized) = 269,
			KeypadPlus LOOPROPERTY(Serialized) = 270,
			KeypadEnter LOOPROPERTY(Serialized) = 271,
			KeypadEquals LOOPROPERTY(Serialized) = 272,
			UpArrow LOOPROPERTY(Serialized) = 273,
			DownArrow LOOPROPERTY(Serialized) = 274,
			RightArrow LOOPROPERTY(Serialized) = 275,
			LeftArrow LOOPROPERTY(Serialized) = 276,
			Insert LOOPROPERTY(Serialized) = 277,
			Home LOOPROPERTY(Serialized) = 278,
			End LOOPROPERTY(Serialized) = 279,
			PageUp LOOPROPERTY(Serialized) = 280,
			PageDown LOOPROPERTY(Serialized) = 281,
			F1 LOOPROPERTY(Serialized) = 282,
			F2 LOOPROPERTY(Serialized) = 283,
			F3 LOOPROPERTY(Serialized) = 284,
			F4 LOOPROPERTY(Serialized) = 285,
			F5 LOOPROPERTY(Serialized) = 286,
			F6 LOOPROPERTY(Serialized) = 287,
			F7 LOOPROPERTY(Serialized) = 288,
			F8 LOOPROPERTY(Serialized) = 289,
			F9 LOOPROPERTY(Serialized) = 290,
			F10 LOOPROPERTY(Serialized) = 291,
			F11 LOOPROPERTY(Serialized) = 292,
			F12 LOOPROPERTY(Serialized) = 293,
			F13 LOOPROPERTY(Serialized) = 294,
			F14 LOOPROPERTY(Serialized) = 295,
			F15 LOOPROPERTY(Serialized) = 296,
			Numlock LOOPROPERTY(Serialized) = 300,
			CapsLock LOOPROPERTY(Serialized) = 301,
			ScrollLock LOOPROPERTY(Serialized) = 302,
			RightShift LOOPROPERTY(Serialized) = 303,
			LeftShift LOOPROPERTY(Serialized) = 304,
			RightControl LOOPROPERTY(Serialized) = 305,
			LeftControl LOOPROPERTY(Serialized) = 306,
			RightAlt LOOPROPERTY(Serialized) = 307,
			LeftAlt LOOPROPERTY(Serialized) = 308,
			RightCommand LOOPROPERTY(Serialized) = 309,
			RightApple LOOPROPERTY(Serialized) = 309,
			LeftCommand LOOPROPERTY(Serialized) = 310,
			LeftApple LOOPROPERTY(Serialized) = 310,
			LeftWindows LOOPROPERTY(Serialized) = 311,
			RightWindows LOOPROPERTY(Serialized) = 312,
			AltGr LOOPROPERTY(Serialized) = 313,
			Help LOOPROPERTY(Serialized) = 315,
			Print LOOPROPERTY(Serialized) = 316,
			SysReq LOOPROPERTY(Serialized) = 317,
			Break LOOPROPERTY(Serialized) = 318,
			Menu LOOPROPERTY(Serialized) = 319,
			// left
			Mouse0 LOOPROPERTY(Serialized) = 323,
			// right
			Mouse1 LOOPROPERTY(Serialized) = 324,
			// middle
			Mouse2 LOOPROPERTY(Serialized) = 325,
			// x1
			Mouse3 LOOPROPERTY(Serialized) = 326,
			// x2
			Mouse4 LOOPROPERTY(Serialized) = 327,
			Mouse5 LOOPROPERTY(Serialized) = 328,
			Mouse6 LOOPROPERTY(Serialized) = 329,
			JoystickButton0 LOOPROPERTY(Serialized) = 330,
			JoystickButton1 LOOPROPERTY(Serialized) = 331,
			JoystickButton2 LOOPROPERTY(Serialized) = 332,
			JoystickButton3 LOOPROPERTY(Serialized) = 333,
			JoystickButton4 LOOPROPERTY(Serialized) = 334,
			JoystickButton5 LOOPROPERTY(Serialized) = 335,
			JoystickButton6 LOOPROPERTY(Serialized) = 336,
			JoystickButton7 LOOPROPERTY(Serialized) = 337,
			JoystickButton8 LOOPROPERTY(Serialized) = 338,
			JoystickButton9 LOOPROPERTY(Serialized) = 339,
			JoystickButton10 LOOPROPERTY(Serialized) = 340,
			JoystickButton11 LOOPROPERTY(Serialized) = 341,
			JoystickButton12 LOOPROPERTY(Serialized) = 342,
			JoystickButton13 LOOPROPERTY(Serialized) = 343,
			JoystickButton14 LOOPROPERTY(Serialized) = 344,
			JoystickButton15 LOOPROPERTY(Serialized) = 345,
			JoystickButton16 LOOPROPERTY(Serialized) = 346,
			JoystickButton17 LOOPROPERTY(Serialized) = 347,
			JoystickButton18 LOOPROPERTY(Serialized) = 348,
			JoystickButton19 LOOPROPERTY(Serialized) = 349,
			Joystick1Button0 LOOPROPERTY(Serialized) = 350,
			Joystick1Button1 LOOPROPERTY(Serialized) = 351,
			Joystick1Button2 LOOPROPERTY(Serialized) = 352,
			Joystick1Button3 LOOPROPERTY(Serialized) = 353,
			Joystick1Button4 LOOPROPERTY(Serialized) = 354,
			Joystick1Button5 LOOPROPERTY(Serialized) = 355,
			Joystick1Button6 LOOPROPERTY(Serialized) = 356,
			Joystick1Button7 LOOPROPERTY(Serialized) = 357,
			Joystick1Button8 LOOPROPERTY(Serialized) = 358,
			Joystick1Button9 LOOPROPERTY(Serialized) = 359,
			Joystick1Button10 LOOPROPERTY(Serialized) = 360,
			Joystick1Button11 LOOPROPERTY(Serialized) = 361,
			Joystick1Button12 LOOPROPERTY(Serialized) = 362,
			Joystick1Button13 LOOPROPERTY(Serialized) = 363,
			Joystick1Button14 LOOPROPERTY(Serialized) = 364,
			Joystick1Button15 LOOPROPERTY(Serialized) = 365,
			Joystick1Button16 LOOPROPERTY(Serialized) = 366,
			Joystick1Button17 LOOPROPERTY(Serialized) = 367,
			Joystick1Button18 LOOPROPERTY(Serialized) = 368,
			Joystick1Button19 LOOPROPERTY(Serialized) = 369,
			Joystick2Button0 LOOPROPERTY(Serialized) = 370,
			Joystick2Button1 LOOPROPERTY(Serialized) = 371,
			Joystick2Button2 LOOPROPERTY(Serialized) = 372,
			Joystick2Button3 LOOPROPERTY(Serialized) = 373,
			Joystick2Button4 LOOPROPERTY(Serialized) = 374,
			Joystick2Button5 LOOPROPERTY(Serialized) = 375,
			Joystick2Button6 LOOPROPERTY(Serialized) = 376,
			Joystick2Button7 LOOPROPERTY(Serialized) = 377,
			Joystick2Button8 LOOPROPERTY(Serialized) = 378,
			Joystick2Button9 LOOPROPERTY(Serialized) = 379,
			Joystick2Button10 LOOPROPERTY(Serialized) = 380,
			Joystick2Button11 LOOPROPERTY(Serialized) = 381,
			Joystick2Button12 LOOPROPERTY(Serialized) = 382,
			Joystick2Button13 LOOPROPERTY(Serialized) = 383,
			Joystick2Button14 LOOPROPERTY(Serialized) = 384,
			Joystick2Button15 LOOPROPERTY(Serialized) = 385,
			Joystick2Button16 LOOPROPERTY(Serialized) = 386,
			Joystick2Button17 LOOPROPERTY(Serialized) = 387,
			Joystick2Button18 LOOPROPERTY(Serialized) = 388,
			Joystick2Button19 LOOPROPERTY(Serialized) = 389,
			Joystick3Button0 LOOPROPERTY(Serialized) = 390,
			Joystick3Button1 LOOPROPERTY(Serialized) = 391,
			Joystick3Button2 LOOPROPERTY(Serialized) = 392,
			Joystick3Button3 LOOPROPERTY(Serialized) = 393,
			Joystick3Button4 LOOPROPERTY(Serialized) = 394,
			Joystick3Button5 LOOPROPERTY(Serialized) = 395,
			Joystick3Button6 LOOPROPERTY(Serialized) = 396,
			Joystick3Button7 LOOPROPERTY(Serialized) = 397,
			Joystick3Button8 LOOPROPERTY(Serialized) = 398,
			Joystick3Button9 LOOPROPERTY(Serialized) = 399,
			Joystick3Button10 LOOPROPERTY(Serialized) = 400,
			Joystick3Button11 LOOPROPERTY(Serialized) = 401,
			Joystick3Button12 LOOPROPERTY(Serialized) = 402,
			Joystick3Button13 LOOPROPERTY(Serialized) = 403,
			Joystick3Button14 LOOPROPERTY(Serialized) = 404,
			Joystick3Button15 LOOPROPERTY(Serialized) = 405,
			Joystick3Button16 LOOPROPERTY(Serialized) = 406,
			Joystick3Button17 LOOPROPERTY(Serialized) = 407,
			Joystick3Button18 LOOPROPERTY(Serialized) = 408,
			Joystick3Button19 LOOPROPERTY(Serialized) = 409,
			Joystick4Button0 LOOPROPERTY(Serialized) = 410,
			Joystick4Button1 LOOPROPERTY(Serialized) = 411,
			Joystick4Button2 LOOPROPERTY(Serialized) = 412,
			Joystick4Button3 LOOPROPERTY(Serialized) = 413,
			Joystick4Button4 LOOPROPERTY(Serialized) = 414,
			Joystick4Button5 LOOPROPERTY(Serialized) = 415,
			Joystick4Button6 LOOPROPERTY(Serialized) = 416,
			Joystick4Button7 LOOPROPERTY(Serialized) = 417,
			Joystick4Button8 LOOPROPERTY(Serialized) = 418,
			Joystick4Button9 LOOPROPERTY(Serialized) = 419,
			Joystick4Button10 LOOPROPERTY(Serialized) = 420,
			Joystick4Button11 LOOPROPERTY(Serialized) = 421,
			Joystick4Button12 LOOPROPERTY(Serialized) = 422,
			Joystick4Button13 LOOPROPERTY(Serialized) = 423,
			Joystick4Button14 LOOPROPERTY(Serialized) = 424,
			Joystick4Button15 LOOPROPERTY(Serialized) = 425,
			Joystick4Button16 LOOPROPERTY(Serialized) = 426,
			Joystick4Button17 LOOPROPERTY(Serialized) = 427,
			Joystick4Button18 LOOPROPERTY(Serialized) = 428,
			Joystick4Button19 LOOPROPERTY(Serialized) = 429,
			Joystick5Button0 LOOPROPERTY(Serialized) = 430,
			Joystick5Button1 LOOPROPERTY(Serialized) = 431,
			Joystick5Button2 LOOPROPERTY(Serialized) = 432,
			Joystick5Button3 LOOPROPERTY(Serialized) = 433,
			Joystick5Button4 LOOPROPERTY(Serialized) = 434,
			Joystick5Button5 LOOPROPERTY(Serialized) = 435,
			Joystick5Button6 LOOPROPERTY(Serialized) = 436,
			Joystick5Button7 LOOPROPERTY(Serialized) = 437,
			Joystick5Button8 LOOPROPERTY(Serialized) = 438,
			Joystick5Button9 LOOPROPERTY(Serialized) = 439,
			Joystick5Button10 LOOPROPERTY(Serialized) = 440,
			Joystick5Button11 LOOPROPERTY(Serialized) = 441,
			Joystick5Button12 LOOPROPERTY(Serialized) = 442,
			Joystick5Button13 LOOPROPERTY(Serialized) = 443,
			Joystick5Button14 LOOPROPERTY(Serialized) = 444,
			Joystick5Button15 LOOPROPERTY(Serialized) = 445,
			Joystick5Button16 LOOPROPERTY(Serialized) = 446,
			Joystick5Button17 LOOPROPERTY(Serialized) = 447,
			Joystick5Button18 LOOPROPERTY(Serialized) = 448,
			Joystick5Button19 LOOPROPERTY(Serialized) = 449,
			Joystick6Button0 LOOPROPERTY(Serialized) = 450,
			Joystick6Button1 LOOPROPERTY(Serialized) = 451,
			Joystick6Button2 LOOPROPERTY(Serialized) = 452,
			Joystick6Button3 LOOPROPERTY(Serialized) = 453,
			Joystick6Button4 LOOPROPERTY(Serialized) = 454,
			Joystick6Button5 LOOPROPERTY(Serialized) = 455,
			Joystick6Button6 LOOPROPERTY(Serialized) = 456,
			Joystick6Button7 LOOPROPERTY(Serialized) = 457,
			Joystick6Button8 LOOPROPERTY(Serialized) = 458,
			Joystick6Button9 LOOPROPERTY(Serialized) = 459,
			Joystick6Button10 LOOPROPERTY(Serialized) = 460,
			Joystick6Button11 LOOPROPERTY(Serialized) = 461,
			Joystick6Button12 LOOPROPERTY(Serialized) = 462,
			Joystick6Button13 LOOPROPERTY(Serialized) = 463,
			Joystick6Button14 LOOPROPERTY(Serialized) = 464,
			Joystick6Button15 LOOPROPERTY(Serialized) = 465,
			Joystick6Button16 LOOPROPERTY(Serialized) = 466,
			Joystick6Button17 LOOPROPERTY(Serialized) = 467,
			Joystick6Button18 LOOPROPERTY(Serialized) = 468,
			Joystick6Button19 LOOPROPERTY(Serialized) = 469,
			Joystick7Button0 LOOPROPERTY(Serialized) = 470,
			Joystick7Button1 LOOPROPERTY(Serialized) = 471,
			Joystick7Button2 LOOPROPERTY(Serialized) = 472,
			Joystick7Button3 LOOPROPERTY(Serialized) = 473,
			Joystick7Button4 LOOPROPERTY(Serialized) = 474,
			Joystick7Button5 LOOPROPERTY(Serialized) = 475,
			Joystick7Button6 LOOPROPERTY(Serialized) = 476,
			Joystick7Button7 LOOPROPERTY(Serialized) = 477,
			Joystick7Button8 LOOPROPERTY(Serialized) = 478,
			Joystick7Button9 LOOPROPERTY(Serialized) = 479,
			Joystick7Button10 LOOPROPERTY(Serialized) = 480,
			Joystick7Button11 LOOPROPERTY(Serialized) = 481,
			Joystick7Button12 LOOPROPERTY(Serialized) = 482,
			Joystick7Button13 LOOPROPERTY(Serialized) = 483,
			Joystick7Button14 LOOPROPERTY(Serialized) = 484,
			Joystick7Button15 LOOPROPERTY(Serialized) = 485,
			Joystick7Button16 LOOPROPERTY(Serialized) = 486,
			Joystick7Button17 LOOPROPERTY(Serialized) = 487,
			Joystick7Button18 LOOPROPERTY(Serialized) = 488,
			Joystick7Button19 LOOPROPERTY(Serialized) = 489,
			Joystick8Button0 LOOPROPERTY(Serialized) = 490,
			Joystick8Button1 LOOPROPERTY(Serialized) = 491,
			Joystick8Button2 LOOPROPERTY(Serialized) = 492,
			Joystick8Button3 LOOPROPERTY(Serialized) = 493,
			Joystick8Button4 LOOPROPERTY(Serialized) = 494,
			Joystick8Button5 LOOPROPERTY(Serialized) = 495,
			Joystick8Button6 LOOPROPERTY(Serialized) = 496,
			Joystick8Button7 LOOPROPERTY(Serialized) = 497,
			Joystick8Button8 LOOPROPERTY(Serialized) = 498,
			Joystick8Button9 LOOPROPERTY(Serialized) = 499,
			Joystick8Button10 LOOPROPERTY(Serialized) = 500,
			Joystick8Button11 LOOPROPERTY(Serialized) = 501,
			Joystick8Button12 LOOPROPERTY(Serialized) = 502,
			Joystick8Button13 LOOPROPERTY(Serialized) = 503,
			Joystick8Button14 LOOPROPERTY(Serialized) = 504,
			Joystick8Button15 LOOPROPERTY(Serialized) = 505,
			Joystick8Button16 LOOPROPERTY(Serialized) = 506,
			Joystick8Button17 LOOPROPERTY(Serialized) = 507,
			Joystick8Button18 LOOPROPERTY(Serialized) = 508,
			Joystick8Button19 LOOPROPERTY(Serialized) = 509
		};
	}
}

namespace loo
{
	namespace core
	{
		enum class LOOENUM () SAppEventType:uint32
		{
			SAPP_EVENTTYPE_INVALID LOOPROPERTY (Serialized) = 0,
			SAPP_EVENTTYPE_KEY_DOWN LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_KEY_UP LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_CHAR LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_MOUSE_DOWN LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_MOUSE_UP LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_MOUSE_SCROLL LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_MOUSE_MOVE LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_MOUSE_ENTER LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_MOUSE_LEAVE LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_TOUCHES LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_TOUCHES_BEGAN LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_TOUCHES_MOVED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_TOUCHES_ENDED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_TOUCHES_CANCELLED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_RESIZED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_ICONIFIED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_RESTORED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_SUSPENDED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_RESUMED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_UPDATE_CURSOR LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_QUIT_REQUESTED LOOPROPERTY (Serialized),
			SAPP_EVENTTYPE_CLIPBOARD_PASTED LOOPROPERTY (Serialized),
			_SAPP_EVENTTYPE_NUM LOOPROPERTY (Serialized),
			_SAPP_EVENTTYPE_FORCE_U32 LOOPROPERTY (Serialized) = 0x7FFFFFFF
		};

		class LOOCLASS () SAppTouchPoint
		{
			LOOMETA_OBJECT;
		public:
			LOOPROPERTY (Serialized)
			std::uintptr_t identifier;
			LOOPROPERTY (Serialized)
			float x;
			LOOPROPERTY (Serialized)
			float y;
			LOOPROPERTY (Serialized)
			bool changed;

		};

		struct LOOCLASS () SAppEvent:public loo::core::Event
		{
			virtual ~SAppEvent () {}
			LOOMETA_OBJECT;
			LOOPROPERTY (Serialized)
			uint64 frameCount;
			LOOPROPERTY (Serialized)
			SAppEventType type;
			LOOPROPERTY (Serialized)
			KeyCode keyCode;
			LOOPROPERTY (Serialized)
			uint32_t charCode;
			LOOPROPERTY (Serialized)
			bool keyRepeat;
			LOOPROPERTY (Serialized)
			uint32_t modifiers;
			LOOPROPERTY (Serialized)
			int mouseX;
			LOOPROPERTY (Serialized)
			int mouseY;
			LOOPROPERTY (Serialized)
			float scrollX;
			LOOPROPERTY (Serialized)
			float scrollY;
			//LOOPROPERTY (Serialized)
			//int numTouchs;
			//LOOPROPERTY (Serialized)
			//TouchPoint touches[SAPP_MAX_TOUCHPOINTS];
			//TODO reflect vector
			//LOOPROPERTY (Serialized)
			std::vector< TouchPoint> touches;
			LOOPROPERTY (Serialized)
			int windowWidth;
			LOOPROPERTY (Serialized)
			int windowHeight;
			LOOPROPERTY (Serialized)
			int framebufferWidth;
			LOOPROPERTY (Serialized)
			int framebufferHeight;

			SAppEvent ()
				:Event("SAppEvent")
			{

			}
			void clear ()
			{
				frameCount = 0;
				type = SAppEventType::SAPP_EVENTTYPE_INVALID;
				keyCode = KeyCode::None;
				charCode = 0;
				keyRepeat = false;
				modifiers = 0;
				mouseX = 0;
				mouseY = 0;
				scrollX = 0;
				scrollY = 0;
				//LOOPROPERTY (Serialized)
				//int numTouchs;
				//LOOPROPERTY (Serialized)
				//TouchPoint touches[SAPP_MAX_TOUCHPOINTS];
				touches.clear ();
				windowWidth = 0;
				windowHeight = 0;
				framebufferWidth = 0;
				framebufferHeight = 0;
			}
		};


		enum class LOOENUM () SAppModifierType:uint32{
			SAPP_MODIFIER_LSHIFT 	LOOPROPERTY (Serialized) = (1 << 0),
			SAPP_MODIFIER_RSHIFT 	LOOPROPERTY (Serialized) = (1 << 1),
			SAPP_MODIFIER_LCTRL 	LOOPROPERTY (Serialized) = (1 << 2),
			SAPP_MODIFIER_RCTRL 	LOOPROPERTY (Serialized) = (1 << 3),
			SAPP_MODIFIER_LALT 		LOOPROPERTY (Serialized) = (1 << 4),
			SAPP_MODIFIER_RALT 		LOOPROPERTY (Serialized) = (1 << 5),
			SAPP_MODIFIER_LMETA		LOOPROPERTY (Serialized) = (1 << 6),
			SAPP_MODIFIER_RMETA		LOOPROPERTY (Serialized) = (1 << 7),//win
			// add lock keys to the same bits
			SAPP_MODIFIER_CAPSLOCK		LOOPROPERTY (Serialized) = (1 << 8),
			SAPP_MODIFIER_NUMLOCK		LOOPROPERTY (Serialized) = (1 << 9),
			SAPP_MODIFIER_SCROLLLOCK	LOOPROPERTY (Serialized) = (1 << 10),
		};
		LOO_BIT_OPERATORS (SAppModifierType);
	}
}

#ifndef __LOOREFLECT__
#include "core/application/generate/keycode.loo.h"
#endif