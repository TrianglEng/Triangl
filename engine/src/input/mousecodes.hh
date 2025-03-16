#ifndef TRIANGL_INPUT_MOUSECODES_HH
#define TRIANGL_INPUT_MOUSECODES_HH 1

namespace triangl {
	
	typedef unsigned int mousecode;
	namespace mouse_buttons {
	
		enum : mousecode
		{
			button1 = 0,
			button2 = 1,
			button3 = 2,
			button4 = 3,
			button5 = 4,
			button6 = 5,
			button7 = 6,
			button8 = 7,

			left   = button1,
			right  = button2,
			middle = button3
		};
	
	}

}

#endif
