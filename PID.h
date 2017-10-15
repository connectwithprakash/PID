#ifndef PID_H
#define PID_H

class PID
{
	private:
	float KP;	//Proportional Constant
	float KI;	//Integral Constant
	float KD;	//Differential Constant
	
	int Set_point;
	int Set_point_max;	//Set the value to it prior to any task else
	int Set_point_min;	//Set the value to it prior to any task else
	
	int Input_value;
	float Integral_term;
	int Input_value_pre;
	
	float Output;
	float Output_max;
	float Output_min;
	
	bool Automatic_state = false;	//Initial State of Manual Mode
	
	#define Automatic 1
	#define Manual 0
	
	public:
	PID(void);		//Contructor to initialize variables	
	void Set_PID(float KP_dum, float KI_dum, float KD_dum)	//Sets PID constraints
	//Set the change in value of KP, KI, KD
	void Inr_KP(void) {KP += 0.001;}	//Increases value of KP by 0.001
	void Dcr_KP(void) {KP -= 0.001;}	//Decreases value of KP by 0.001
	void Inr_KI(void) {KI += 0.0001;}	//Increases value of KP by 0.0001
	void Dcr_KI(void) {KI -= 0.0001;}	//Decreases value of KP by 0.0001
	void Inr_KD(void) {KD += 0.01;}		//Increases value of KP by 0.01
	void Dcr_KD(void) {KD -= 0.01;}		//Decreases value of KP by 0.01
	
	void Set_Set_Point(float Set_point_dum);	//Sets set point to desired value
	void Inr_Set_Point(void);	//Increases Set point value by 5
	void Dcr_Set_Point(void);	//Decreases Set point value by 5
	
	void SetMode(int Mode_dum);		//Selects Automatic or Manual mode by 1 or 0 respectively
	void Manual_To_Auto_Initialize(void);	//Sets the variables affecting Integral and Differential -
	//-term when shifting back from Manual to Automatic mode which eliminates the undesired bumps on -
	//input due to controller jumping back to last output it had
	void Set_Output_Limits(int Out_max_dum, int Out_min_dum);
	//Sets the maximum and minimum output value
	int Calculate_PID(int Input_value_dum);		//Calculates the Output after applying PID
	
	~PID();		//Destructor

	};
#endif