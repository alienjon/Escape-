/*
 * SFMLInput.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: alienjon
 */
#include "sfmlinput.hpp"

#include "../exception.hpp"

namespace gcn
{
	SFMLInput::SFMLInput() :
		mMouseDown(false)
	{
	}

	KeyInput SFMLInput::dequeueKeyInput()
	{
		if(mKeyQueue.empty())
			throw GCN_EXCEPTION("Key queue is empty.");
		KeyInput input(mKeyQueue.front());
		mKeyQueue.pop();
		return input;
	}

	MouseInput SFMLInput::dequeueMouseInput()
	{
		if(mMouseQueue.empty())
			throw GCN_EXCEPTION("Mouse queue is empty.");
		MouseInput input(mMouseQueue.front());
		mMouseQueue.pop();
		return input;
	}

	void SFMLInput::pushInput(sf::Event& event)
	{
		KeyInput keyInput;
		MouseInput mouseInput;

		switch(event.Type)
		{
			case sf::Event::KeyPressed:
			{
				keyInput.setKey(convertSFToGCNKey(event.Key.Code));
				keyInput.setType(KeyInput::PRESSED);
				keyInput.setShiftPressed(event.Key.Shift);
				keyInput.setAltPressed(event.Key.Alt);
				keyInput.setControlPressed(event.Key.Control);
				keyInput.setMetaPressed(event.Key.Code == sf::Keyboard::LSystem);
				keyInput.setNumericPad(isNumpad(event));
				mKeyQueue.push(keyInput);
				break;
			}
			case sf::Event::KeyReleased:
			{
				keyInput.setKey(convertSFToGCNKey(event.Key.Code));
				keyInput.setType(KeyInput::RELEASED);
				keyInput.setShiftPressed(event.Key.Shift);
				keyInput.setAltPressed(event.Key.Alt);
				keyInput.setControlPressed(event.Key.Control);
				keyInput.setMetaPressed(event.Key.Code == sf::Keyboard::LSystem);
				keyInput.setNumericPad(isNumpad(event));
				mKeyQueue.push(keyInput);
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				mMouseDown = true;
				mouseInput.setX(event.MouseButton.X);
				mouseInput.setY(event.MouseButton.Y);
				mouseInput.setButton(convertSFToGCNButton(event.MouseButton.Button));
				mouseInput.setType(MouseInput::PRESSED);//@fixme SDLKeyInput also includes a mouse wheel, how do I implement this in sf?
				mouseInput.setTimeStamp(mTimestampClock.GetElapsedTime() * 1000);
				mMouseQueue.push(mouseInput);
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				mMouseDown = false;
				mouseInput.setX(event.MouseButton.X);
				mouseInput.setY(event.MouseButton.Y);
				mouseInput.setButton(convertSFToGCNButton(event.MouseButton.Button));
				mouseInput.setType(MouseInput::RELEASED);
				mouseInput.setTimeStamp(mTimestampClock.GetElapsedTime() * 1000);
				mMouseQueue.push(mouseInput);
				break;
			}
			case sf::Event::MouseMoved:
			{
				mouseInput.setX(event.MouseMove.X);
				mouseInput.setY(event.MouseMove.Y);
				mouseInput.setButton(MouseInput::EMPTY);
				mouseInput.setType(MouseInput::MOVED);
				mouseInput.setTimeStamp(mTimestampClock.GetElapsedTime() * 1000);
				mMouseQueue.push(mouseInput);
				break;
			}
			case sf::Event::LostFocus:
			{
				if(!mMouseDown)
				{
					mouseInput.setX(-1);
					mouseInput.setY(-1);
					mouseInput.setButton(MouseInput::EMPTY);
					mouseInput.setType(MouseInput::MOVED);
					mMouseQueue.push(mouseInput);
				}
				break;
			}
			default:
			{}
		}
	}

	int SFMLInput::convertSFToGCNButton(sf::Mouse::Button button)
	{
		switch(button)
		{
			case sf::Mouse::Left:
				return MouseInput::LEFT;
			case sf::Mouse::Right:
				return MouseInput::RIGHT;
			case sf::Mouse::Middle:
				return MouseInput::MIDDLE;
			default:
				return button;
		}
	}

	int SFMLInput::convertSFToGCNKey(sf::Keyboard::Key key)
	{
		switch(key)
		{
			case sf::Keyboard::Escape:
				return Key::ESCAPE;
			case sf::Keyboard::F1:
				return Key::F1;
			case sf::Keyboard::F2:
				return Key::F2;
			case sf::Keyboard::F3:
				return Key::F3;
			case sf::Keyboard::F4:
				return Key::F4;
			case sf::Keyboard::F5:
				return Key::F5;
			case sf::Keyboard::F6:
				return Key::F6;
			case sf::Keyboard::F7:
				return Key::F7;
			case sf::Keyboard::F8:
				return Key::F8;
			case sf::Keyboard::F9:
				return Key::F9;
			case sf::Keyboard::F10:
				return Key::F10;
			case sf::Keyboard::F11:
				return Key::F11;
			case sf::Keyboard::F12:
				return Key::F12;
			case sf::Keyboard::F13:
				return Key::F13;
			case sf::Keyboard::F14:
				return Key::F14;
			case sf::Keyboard::F15:
				return Key::F15;
			case sf::Keyboard::Pause:
				return Key::PAUSE;
			case sf::Keyboard::Insert:
				return Key::INSERT;
			case sf::Keyboard::Delete:
				return Key::DELETE;
			case sf::Keyboard::PageUp:
				return Key::PAGE_UP;
			case sf::Keyboard::PageDown:
				return Key::PAGE_DOWN;
			case sf::Keyboard::Home:
				return Key::HOME;
			case sf::Keyboard::End:
				return Key::END;

//			case sf::Keyboard::Tilde://@todo tilde doesn't seem to work
//				return '~';
			case sf::Keyboard::Num1:
				return '1';
			case sf::Keyboard::Num2:
				return '2';
			case sf::Keyboard::Num3:
				return '3';
			case sf::Keyboard::Num4:
				return '4';
			case sf::Keyboard::Num5:
				return '5';
			case sf::Keyboard::Num6:
				return '6';
			case sf::Keyboard::Num7:
				return '7';
			case sf::Keyboard::Num8:
				return '8';
			case sf::Keyboard::Num9:
				return '9';
			case sf::Keyboard::Num0:
				return '0';
			case sf::Keyboard::Dash:
				return '-';
			case sf::Keyboard::Equal:
				return '=';
			case sf::Keyboard::Back:
				return Key::BACKSPACE;
			case sf::Keyboard::Divide:
				return '/';
			case sf::Keyboard::Multiply:
				return '*';
			case sf::Keyboard::Subtract:
				return '-';


			case sf::Keyboard::Tab:
				return Key::TAB;
			case sf::Keyboard::Q:
				return 'q';
			case sf::Keyboard::W:
				return 'w';
			case sf::Keyboard::E:
				return 'e';
			case sf::Keyboard::R:
				return 'r';
			case sf::Keyboard::T:
				return 't';
			case sf::Keyboard::Y:
				return 'y';
			case sf::Keyboard::U:
				return 'u';
			case sf::Keyboard::I:
				return 'i';
			case sf::Keyboard::O:
				return 'o';
			case sf::Keyboard::P:
				return 'p';
			case sf::Keyboard::LBracket:
				return '[';
			case sf::Keyboard::RBracket:
				return ']';
			case sf::Keyboard::BackSlash:
				return '\\';
			case sf::Keyboard::Numpad7:
				return '7';
			case sf::Keyboard::Numpad8:
				return '8';
			case sf::Keyboard::Numpad9:
				return '9';
			case sf::Keyboard::Add:
				return '+';

			case sf::Keyboard::A:
				return 'a';
			case sf::Keyboard::S:
				return 's';
			case sf::Keyboard::D:
				return 'd';
			case sf::Keyboard::F:
				return 'f';
			case sf::Keyboard::G:
				return 'g';
			case sf::Keyboard::H:
				return 'h';
			case sf::Keyboard::J:
				return 'j';
			case sf::Keyboard::K:
				return 'k';
			case sf::Keyboard::L:
				return 'l';
			case sf::Keyboard::SemiColon:
				return ';';
			case sf::Keyboard::Quote://@fixme single quote doesn't work?
				return '\'';
			case sf::Keyboard::Return:
				return Key::ENTER;
			case sf::Keyboard::Numpad4:
				return '4';
			case sf::Keyboard::Numpad5:
				return '5';
			case sf::Keyboard::Numpad6:
				return '6';

			case sf::Keyboard::LShift:
				return Key::LEFT_SHIFT;
			case sf::Keyboard::Z:
				return 'z';
			case sf::Keyboard::X:
				return 'x';
			case sf::Keyboard::C:
				return 'c';
			case sf::Keyboard::V:
				return 'v';
			case sf::Keyboard::B:
				return 'b';
			case sf::Keyboard::N:
				return 'n';
			case sf::Keyboard::M:
				return 'm';
			case sf::Keyboard::Comma:
				return ',';
			case sf::Keyboard::Period:
				return '.';
			case sf::Keyboard::RShift:
				return Key::RIGHT_SHIFT;
			case sf::Keyboard::Numpad1:
				return '1';
			case sf::Keyboard::Numpad2:
				return '2';
			case sf::Keyboard::Numpad3:
				return '3';

			case sf::Keyboard::Up:
				return Key::UP;
			case sf::Keyboard::Down:
				return Key::DOWN;
			case sf::Keyboard::Left:
				return Key::LEFT;
			case sf::Keyboard::Right:
				return Key::RIGHT;

			case sf::Keyboard::LControl:
				return Key::LEFT_CONTROL;
			case sf::Keyboard::LSystem:
				return Key::LEFT_META;
			case sf::Keyboard::LAlt:
				return Key::LEFT_ALT;
			case sf::Keyboard::Space:
				return Key::SPACE;
			case sf::Keyboard::RAlt:
				return Key::RIGHT_ALT;
			case sf::Keyboard::RControl:
				return Key::RIGHT_CONTROL;
			case sf::Keyboard::Numpad0:
				return '0';
			default:
				return 0;
		}
	}

	bool SFMLInput::isNumpad(const sf::Event& event)
	{
		return true;//@todo implement checking the numpad.
	}
}
