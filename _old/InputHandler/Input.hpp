#include "raylib.h"

namespace RayInput{
	class UserInput{
		
	};

	struct MouseInputSnooper{
		int left = MOUSE_BUTTON_LEFT;
		int right = MOUSE_BUTTON_RIGHT;
		int middle = MOUSE_BUTTON_MIDDLE;
			
		int GetScrollDirection();
		
	};
};

