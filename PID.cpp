#include <iostream>
#include <cmath>
#include "PID.h"

PID::PID()
{
	KP = 0;
	KI = 0;
	KD = 0;
	Input_value_pre = 0;
	Integral_term = 0;
}

void PID::Set_PID(float KP_dum, float KI_dum, float KD_dum)
{
	KP = KP_dum;
	KI = KI_dum;
	KD = KD_dum;
}

void PID::Set_Set_Point(int Set_point_dum)
{
	if (Set_point_dum > Set_point_max) Set_point = Set_point_max;
	else if (Set_point_dum < Set_point_min) Set_point = Set_point_min;
	else Set_point = Set_point_dum;
}

void PID::Inr_Set_Point()
{
	Set_point += 5;
	
	if (Set_point>Set_point_max)
	Set_point = Set_point_max;
}

void PID::Dcr_Set_Point()
{
	Set_point -= 5;
	
	if (Set_point<Set_point_min)
	Set_point = Set_point_min;
}


void PID::SetMode(int Mode_dum)
{
	bool New_automatic_state = (Mode_dum == Automatic);
	if(New_automatic_state && !Automatic_state) Manual_To_Auto_Initialize();
	Automatic_state = New_automatic_state;
}

void PID::Manual_To_Auto_Initialize(void)
{
	Input_value_pre = Input_value;
	Integral_term = Output;
	if(Integral_term> Output_max) Integral_term= Output_max;
	else if(Integral_term< Output_min) Integral_term= Output_min;
}

void PID::Set_Output_Limits(int Out_max_dum, int Out_min_dum)
{
	Output_max = Out_max_dum;
	Output_min = Out_min_dum;
	
	if (Integral_term > Output_max) Integral_term = Output_max;
	else if (Integral_term < Output_min) Integral_term = Output_min;
	
	if (Output > Output_max) Output = Output_max;
	else if (Output < Output_min) Output = Output_min;
}

int PID::Calculate_PID(int Input_value_dum)
{
	if (!Automatic_state) return;
	
	Input_value = Input_value_dum;
	float Error = Set_point - Input_value_dum;
	
	Integral_term += KI*Error;
	if (Integral_term > Output_max) Integral_term = Output_max;
	else if (Integral_term < Output_min) Integral_term = Output_min;
	
	Output = KP*Error + Integral_term + KD*(Input_value_dum - Input_value_pre);
	if (Output > Output_max) Output = Output_max;
	else if (Output < Output_min) Output = Output_min;
	
	Input_value_pre = Input_value_dum;
	return Output;
}	