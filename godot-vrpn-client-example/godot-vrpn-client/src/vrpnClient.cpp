/**
  ******************************************************************************
  * @file    vrpnServer.cpp
  * @author  Lucas Matías Angarola
  * @version V1.0.0
  * @date    19-Dec-2014
  * @brief   
  ******************************************************************************
  * @copyright
  *
  *  Permission is hereby granted, free of charge, to any person obtaining a copy of
  *  this software and associated documentation files (the "Software"), to deal in
  *  the Software without restriction, including without limitation the rights to use,
  *  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
  *  Software, and to permit persons to whom the Software is furnished to do so,
  *  subject to the following conditions:
  *
  *  The above copyright notice and this permission notice shall be included in all
  *  copies or substantial portions of the Software.
  *
  *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  *  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  *  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  * 
  * 
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "vrpnClient.h"
#include <Defs.hpp>


/* Global private variables ---------------------------------------------------------*/
static vrpnClient *p = NULL;


/* Private global functions ---------------------------------------------------------*/

/** @defgroup private_global_Functions
  * @{
  */


void VRPN_CALLBACK analog_callback( void* userData, const vrpn_ANALOGCB a ){
	for( int i=0; i < a.num_channel; i++ ){
		p->setAnalog(i, a.channel[i]);
	}
}


void VRPN_CALLBACK button_callback( void* userData, const vrpn_BUTTONCB b ){
	p->setButton(b.button,b.state);
}


void VRPN_CALLBACK tracker_callback(void* userData, const vrpn_TRACKERCB t ){
	p->setTracker((double *)t.pos,(double *)t.quat);
}


/**
  * @}
  */



/* vrpnClient class functions ---------------------------------------------------------*/
void vrpnClient::setAnalog(int chnl, double val){
	while( chnl >= analog.size() ){
		analog.append(0.0);
	}
	analog.set(chnl,(real_t)val);
}

void vrpnClient::setButton(int chnl, int val){
	while( chnl >= button.size() ){
		button.append(0);
	}
	button.set(chnl,val);
}

void vrpnClient::setTracker(double *pos, double *quat){
	this->pos.set(0,pos[0]);
	this->pos.set(1,pos[1]);
	this->pos.set(2,pos[2]);
	this->quat.set(0,quat[0]);
	this->quat.set(1,quat[1]);
	this->quat.set(2,quat[2]);
	this->quat.set(3,quat[3]);
}

void vrpnClient::_register_methods()
{
	godot::register_method((char *)"mainloop", &vrpnClient::mainloop);
	godot::register_method((char *)"connect", &vrpnClient::connect);
	
	godot::register_property((char *)"analog", &vrpnClient::analog, godot::PoolRealArray() );
	godot::register_property((char *)"pos", &vrpnClient::pos, godot::PoolRealArray() );
	godot::register_property((char *)"quat", &vrpnClient::quat, godot::PoolRealArray() );
	godot::register_property((char *)"button", &vrpnClient::button, godot::PoolIntArray() );
}

void vrpnClient::_init(){
	godot::Godot::print("Init... ");
	
	/* Create memory for Tracker Positions */
	for(int i=0;i<3;i++)
		pos.append(0.0);
	
	/* Create memory for Tracker Positions */
	for(int i=0;i<4;i++)
		quat.append(0.0);
	
	godot::Godot::print("[OK]");
}


/**
  * @brief  VRPN client calss contructor function
  * @param  None.
  * @retval None.
  */
void vrpnClient::connect(godot::String name){
	godot::Godot::print("Connecting... ");

	/* */
	clientTracker = new vrpn_Tracker_Remote( name.ascii().get_data() );
	if(clientTracker == NULL){
	    std::cout << "vrpnServer() Error: trackerVrpnServer could not be created" << std::endl;
	    //return;
	}
	
	clientTracker->register_change_handler( 0, tracker_callback );

    /* */
	clientAnalog = new vrpn_Analog_Remote( name.ascii().get_data() );
	if(clientAnalog == NULL){
	    std::cout << "vrpnServer() Error: analogVrpnServer could not be created" << std::endl;
	    //return;
	}
	
	clientAnalog->register_change_handler( 0, analog_callback );

    
	/* */
	clientButton = new vrpn_Button_Remote( name.ascii().get_data() );
	if(clientButton == NULL){
	    std::cout << "vrpnServer() Error: buttonVrpnServer could not be created" << std::endl;
	    //return;
	}
	
	clientButton->register_change_handler( 0, button_callback );
	
	godot::Godot::print("[OK]");
}

/**
  * @brief  VRPN client main loop function
  * @note   One option is: place this in the same loop where update_tracking() is, and call it before update_tracking().
  * 	    A second option is creating a new thread for the main loop that runs faster that the loop where the update_tracking is located.
  * @param  None.
  * @retval None.
  */
void vrpnClient::mainloop(){
	p = this;
	clientTracker->mainloop();
	clientAnalog->mainloop();
	clientButton->mainloop();
}


/**
  * @brief  VRPN client calss destructor function
  * @param  None.
  * @retval None.
  */
vrpnClient::~vrpnClient(){
	if(clientTracker != NULL)
	  delete clientTracker;
	
	if(clientAnalog != NULL)
	  delete clientAnalog;
	
	if(clientButton != NULL)
	  delete clientButton;
}


