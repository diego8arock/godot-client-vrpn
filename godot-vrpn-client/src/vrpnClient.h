/**
  ******************************************************************************
  * @file    vrpnClient.h
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VRPNCLIENT_H
#define VRPNCLIENT_H

/* Includes ------------------------------------------------------------------*/
#include "vrpn_Connection.h"
#include "vrpn_Text.h"
#include "vrpn_Tracker.h"
#include "vrpn_Analog.h"
#include "vrpn_Button.h"
#include <Godot.hpp>
#include <Reference.hpp>
#include <string>
#include <iostream>


/* vrpnServer class ---------------------------------------------------------*/

/** @defgroup vrpnServer_class
  * @{
  */

class vrpnClient  : public godot::GodotScript<godot::Reference>{
	GODOT_CLASS(vrpnClient)
	
public:
	vrpnClient(){}
	~vrpnClient();
	void 		mainloop();
	void 		connect(godot::String name);
	void 		setAnalog(int chnl, double val);
	void 		setButton(int chnl, int val);
	void 		setTracker(double *pos, double *quat);
	static void _register_methods();
	void 		_init();
	
	godot::PoolRealArray 	analog;
	godot::PoolRealArray 	pos;
	godot::PoolRealArray 	quat;
	godot::PoolIntArray 	button;
	
protected:
	vrpn_Tracker_Remote *clientTracker;
	vrpn_Analog_Remote 	*clientAnalog;
	vrpn_Button_Remote 	*clientButton;
};

/**
  * @}
  */


#endif
