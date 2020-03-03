#include "global/global.h"
#ifdef LOO_PLATFORM_ANDROID
#include <android/window.h>
#include "core/application/input.h"
#include "core/application/application.h"

namespace loo
{
    namespace core
    {
        struct MsgProcVisitFunc_Local
        {
            SAppEvent* event;
            Input* input;
            AInputEvent* sysevent;
            loo::math::RectF windowGeometry;
            loo::math::RectF screenGeometry;

        public:

            void Reset (Input* input_,
                        SAppEvent* event_,AInputEvent* sysevent_,
                        loo::math::RectF windowGeometry_,
                        loo::math::RectF screenGeometry_)
            {
                input = input_;
                event = event_;
                sysevent = sysevent_;
                screenGeometry = screenGeometry_;
            }

            bool mouse_event (SAppEventType type, KeyCode keyCode, int x, int y)
            {
                input->InitEvent (*event, type);
                event->keyCode = keyCode;
                event->mouseX = x;
                event->mouseY = y;

                return EventManager::Get ().sendEvent (event);
            }

            bool mouse_scroll_event (float x, float y,float sx, float sy)
            {
                input->InitEvent (*event, SAppEventType::SAPP_EVENTTYPE_MOUSE_SCROLL);
                event->scrollX = -x / 30.0f;
                event->scrollY = y / 30.0f;

                return EventManager::Get ().sendEvent (event);
            }
            bool touch_event( SAppEventType touchType)
            {
                input->InitEvent (*event, touchType);
                int touchCount = AMotionEvent_getPointerCount(sysevent);
                event->touches.clear ();
                event->touches.reserve (touchCount);
                for (size_t i = 0; i < touchCount; ++i)
                {
                    TouchPoint touchPoint;
                    touchPoint.pressure = 1.0;
                    touchPoint.id = AMotionEvent_getPointerId(sysevent, i);
                    touchPoint.normalPosition.x = (float)AMotionEvent_getRawX(sysevent, i)/(float)windowGeometry.x*(float)screenGeometry.x;
                    touchPoint.normalPosition.y = (float)AMotionEvent_getRawY(sysevent, i)/(float)windowGeometry.y*(float)screenGeometry.y;
                    touchPoint.pressure = AMotionEvent_getPressure(sysevent,i);
                    //AMotionEvent_getHistoricalPressure
                    event->touches.push_back(touchPoint);
                }
                return EventManager::Get ().sendEvent (event);
            }

        };

        int32_t Input::InputProc (android_app* app, AInputEvent* event)
        {
            Window* win = static_cast<Window*>(app->userData);
            Application* app = win->GetApp();
            SAppEvent& e = app->GetEvent ();
            auto cfg = app->Config ();
            visitor->Reset (this, &e, event, loo::math::RectF((float)windowptr->Left(), (float)windowptr->Top(), (float)windowptr->Width(), (float)windowptr->Height()));

            int32_t source = AInputEvent_getSource(event);
            SAppEventType touchType = SAppEventType::SAPP_EVENTTYPE_INVALID;

            switch (AInputEvent_getType(event))
            {
                case AINPUT_EVENT_TYPE_MOTION:
                {
                    int32_t action = AMotionEvent_getAction(event);
                    int32_t action_code = action & AMOTION_EVENT_ACTION_MASK;
                    int32_t pointer_index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                            >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
                    switch (source)
                    {
                        case AINPUT_SOURCE_MOUSE:
                        {
                            BOOST_ASSERT(1 == AMotionEvent_getPointerCount(event));
                            int x = AMotionEvent_getX(event, pointer_index);
                            int y = AMotionEvent_getY(event, pointer_index);

                            int32_t buttons = AMotionEvent_getButtonState(event);
                            switch (action_code)
                            {
                                case AMOTION_EVENT_ACTION_DOWN:
                                    visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_KEY_DOWN, TranslateKey(buttons), x,y);
                                    //OnMouseDown()(*win, pt, buttons);
                                    break;

                                case AMOTION_EVENT_ACTION_UP:
                                    visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_KEY_UP, TranslateKey(buttons), x,y);
                                    //OnMouseUp()(*win, pt, buttons);
                                    break;

                                case AMOTION_EVENT_ACTION_SCROLL:
                                    visitor->mouse_scroll_event(*win, pt, x, y, AMotionEvent_getAxisValue(event, MOTION_EVENT_AXIS_HSCROLL, pointer_index),
                                                        AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_VSCROLL, pointer_index));
                                    break;

                                default:
                                    visitor->mouse_event (SAppEventType::SAPP_EVENTTYPE_MOUSE_MOVE, TranslateKey(buttons), x,y);
                                    break;
                            }
                        }
                            break;

                        case AINPUT_SOURCE_TOUCHSCREEN:
                            switch (action_code)
                            {
                                case AMOTION_EVENT_ACTION_DOWN:
                                case AMOTION_EVENT_ACTION_POINTER_DOWN:
                                    touchType = SAppEventType::SAPP_EVENTTYPE_TOUCHES_BEGAN;
                                    break;
                                case AMOTION_EVENT_ACTION_UP:
                                case AMOTION_EVENT_ACTION_POINTER_UP:
                                    touchType = SAppEventType::SAPP_EVENTTYPE_TOUCHES_UP;
                                    break;
                                case AMOTION_EVENT_ACTION_MOVE:
                                    touchType = SAppEventType::SAPP_EVENTTYPE_TOUCHES_MOVE;
                                    break;
                                case AMOTION_EVENT_ACTION_CANCEL:
                                    touchType = SAppEventType::SAPP_EVENTTYPE_TOUCHES_CANCELLED;
                                    break;
                                default:
                                    break;
                            }
                            if(touchType != SAppEventType::SAPP_EVENTTYPE_INVALID)
                            {
                                visitor->touch_event(touchType);
                            }
                            break;

                        case AINPUT_SOURCE_JOYSTICK://todo
                        {
                           /* for (uint32_t i = 0; i < 8; i++)
                            {
                                win->OnJoystickAxis()(*win, i, AMotionEvent_getAxisValue(event, i, 0));
                            }*/
                        }
                            break;

                        default:
                            break;
                    }
                }
                    return 1;

                case AINPUT_EVENT_TYPE_KEY:
                    switch (source)
                    {
                        case AINPUT_SOURCE_KEYBOARD:
                        {
                            int32_t key_code = AKeyEvent_getKeyCode(event);
                            switch (AKeyEvent_getAction(event))
                            {
                                case AKEY_EVENT_ACTION_DOWN:
                                    win->OnKeyDown()(*win, key_code);
                                    break;

                                case AKEY_EVENT_ACTION_UP:
                                    win->OnKeyUp()(*win, key_code);
                                    break;

                                default:
                                    break;
                            }
                        }
                            break;

                        case AINPUT_SOURCE_JOYSTICK:
                            win->OnJoystickButtons()(*win, AMotionEvent_getButtonState(event));
                            break;

                        default:
                            break;
                    }
                    return 1;
            }
        }

        void Input::Init(Window& win)
        {
            windowptr = &win;
            //windowptr->OnChar ().connect (&Input::cb_CharEvent,this);
            visitor = new MsgProcVisitFunc_Local ();
        }

        void Input::CleanUp()
        {
            delete visitor;
        }

        KeyCode Input::TranslateKey(int scanCode)
        {
#define DECLARE_KEY_MAP(scanCode,keyCode)\
	case scanCode:return keyCode;
            switch(scanCode)
            {
                case AKEYCODE_BACK:
                default: return  KeyCode::None;break;
            }
#undef DECLARE_KEY_MAP
        }
    }
}


#endif