#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{
	keyboard.setPosition (80,16,320,240);
	add(keyboard);
	keyboard.setVisible (false);
	keyboard.invalidate();
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::nameClicked ()
{
	keyboard.setVisible (true);  // show keyboard
	keyboard.invalidate();
	flexButtonOK.setVisible(true);  // show OK
	flexButtonOK.invalidate();
	flexButtonExit.setVisible(true);  // show exit
	flexButtonExit.invalidate();
	namemod = 1;
	agemod = 0;
}

void Screen1View::ageClicked ()
{
	keyboard.setVisible (true);  // show keyboard
	keyboard.invalidate();
	flexButtonOK.setVisible(true);  // show OK
	flexButtonOK.invalidate();
	flexButtonExit.setVisible(true);  // show exit
	flexButtonExit.invalidate();
	agemod = 1;
	namemod = 0;
}

void Screen1View::exitClicked ()
{
	keyboard.setVisible (false);  // hide keyboard
	keyboard.invalidate();
	flexButtonOK.setVisible(false);  // hide OK
	flexButtonOK.invalidate();
	flexButtonExit.setVisible(false);  // hide exit
	flexButtonExit.invalidate();
	namemod = agemod = 0;
}

void Screen1View::okClicked ()
{
	keyboard.setVisible (false);  // hide keyboard
	keyboard.invalidate();
	flexButtonOK.setVisible(false);  // hide OK
	flexButtonOK.invalidate();
	flexButtonExit.setVisible(false);  // hide exit
	flexButtonExit.invalidate();

	if (namemod)
	{
		Unicode::strncpy(textAreaNameBuffer, keyboard.getBuffer(), TEXTAREANAME_SIZE);
		textAreaName.invalidate();
	}
	if (agemod)
	{
		Unicode::strncpy(textAreaAgeBuffer, keyboard.getBuffer(), TEXTAREAAGE_SIZE);
		textAreaAge.invalidate();
	}

	// once the data is copied into text buffers, clear the keyboard
	keyboard.clearBuffer();
}
