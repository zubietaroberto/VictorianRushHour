//
//  Victorian_Rush_HourAppDelegate.h
//  Victorian Rush Hour
//
//  Created by Roger Engelbert on 11/17/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#pragma once

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason to implement with private inheritance is to hide some interface details of CCDirector.
*/
class AppDelegate: private cocos2d::Application{
public:
	AppDelegate();
	virtual ~AppDelegate();

	/**
	@brief    Implement CCDirector and CCScene init code here.
	@return true    Initialize success, app continue.
	@return false   Initialize failed, app terminate.
	*/
	virtual bool applicationDidFinishLaunching();

	/**
	@brief  The function is called when the application enters the background
	@param  the pointer of the application instance
	*/
	virtual void applicationDidEnterBackground();

	/**
	@brief  The function is called when the application enters the foreground
	@param  the pointer of the application instance
	*/
	virtual void applicationWillEnterForeground();
};
