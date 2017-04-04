//Precondition: There may or may not be characters left in the keyboard buffer
//Postcondition: There will be no characters left in the keyboard buffer
void clearKeyboardBuffer(void);

void clearKeyboardBuffer(void)
{
	while (getchar() != '\n');//grabs the next char from keyboard buffer, if it is not the newline character, it loops again
}