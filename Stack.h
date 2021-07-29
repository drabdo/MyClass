#pragma once



template<class t, const int MAX_SIZE_Schedule>
class Stack {

	int top;
	t item[MAX_SIZE_Schedule];


public:
	Stack() {
		top = -1;
	}


	void push(t Element)
	{
		if (top >= MAX_SIZE_Schedule - 1)
		{
			Serial.println("Stack is Full!");
		}
		else
		{
			top++;
			item[top] = Element;
		}

	}

	bool isEmpty()
	{
		return top < 0;
		/*if (top == -1)
		{
			return true;

		}
		else
			return false;*/
	}

	void pop()
	{
		if (!isEmpty())top--;
	}

	t  getTop() {

		return item[top];

	}



	//........................UserInfo....................

	UserInfo getAllUser(uint8_t index)
	{

		return item[index];
	}
	
	uint8_t NumberOfElement()
	{
		return top;
	}

	UserInfo getUser(uint8_t index, char* _value)
	{

		UserInfo user;

		for (uint8_t i = 0; i <= top; i++)
		{
			
			switch (index)
			{
			case 0: // Search by id - fingerprint
			{
				if ((strcasecmp(_value, (char*)item[i].id) == 0) && (item[i].enable == true))
				{
					item[i].index = i;
					return item[i];
				}
				break;
			}break;
			case 1: // Search by password
				{
					if ((strcasecmp(_value, (char*)item[i].pass) == 0) && (item[i].enable == true))
					{
						item[i].index = i;
						return item[i];
					}
				}break;

			case 2: // Search by Card ID
			{
				if ((strcasecmp(_value, (char*)item[i].cardid) == 0) && (item[i].enable == true))
				{
					item[i].index = i;
					return item[i];
				}

			}break;

			

			default:
				break;
			}
		}

		return user;
	}

	UserInfo DeleteUser(t _t)
	{
		item[_t.index] = item[top]; // set curret top in searched item index
		item[top] = _t; // set current searched item in top
		
		pop(); // delete top index;
	}

	//........................UserInfo....................






	//................... Private us with [Schedult] ....................

	void pushSchedule(t _t) // sort by time  and push new item
	{
		if (top >= MAX_SIZE_Schedule - 1)
		{
			Serial.println("Stack is Full!");
			return; // exit
		}
		else
		{
			top++;
		}





		// convert time to second
		unsigned long _new = _t.epoch;

		unsigned long _old = item[top - 1].epoch;

		if (top == 0)
		{
			item[top] = _t;
			return; // exit 
		}

		for (size_t i = 0; i <= top; i++)
		{
			if (_old > _new)
			{
				item[top - i] = _t;
				break; // exit loop
			}
			else {
				item[top - i] = item[top - i - 1];
				if ((top - i - 1) == 0)
				{
					item[top - i - 1] = _t;
					break; // exit loop
				}
				else {
					_old = item[top - i - 2].epoch;
				}
			}
		}

	}

	void printSchedule()
	{

		int id = -1;
		for (uint8_t i = 0; i <= top; i++)
		{

			id = item[i].id;
			Serial.print("id:"); Serial.println(id);
			Serial.print("PIN:"); Serial.println(item[i].pin);
			Serial.print("stamp:"); Serial.println(item[i].epoch);
			Serial.print("Sart time:"); Serial.print(item[i].start_time.hour); Serial.print(":");

			Serial.print(item[i].start_time.minute); Serial.print(":"); Serial.println(item[i].start_time.second);

			Serial.print("Interval:"); Serial.println(item[i].interval);
			Serial.println("...........");
		}

		Serial.print("TOP:"); Serial.println(id);
		Serial.println("...........................");

	}

	//................... Private us with [Schedult] ....................



	//..................ShiftRegister.....................


	// return ShiftString Ports
	ShiftRegPort ShiftString(uint8_t srNo) 
	{
		
		return  item[srNo];

	}

	//update sheftreg
	void update(uint8_t _indexOrShiftNO, t Element)
	{
		item[_indexOrShiftNO] = Element;
	}




	//..................ShiftRegister.....................
};