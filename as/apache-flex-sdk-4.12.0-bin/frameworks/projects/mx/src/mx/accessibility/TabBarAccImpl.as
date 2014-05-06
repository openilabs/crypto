////////////////////////////////////////////////////////////////////////////////
//
//  Licensed to the Apache Software Foundation (ASF) under one or more
//  contributor license agreements.  See the NOTICE file distributed with
//  this work for additional information regarding copyright ownership.
//  The ASF licenses this file to You under the Apache License, Version 2.0
//  (the "License"); you may not use this file except in compliance with
//  the License.  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////

package mx.accessibility
{

import flash.accessibility.Accessibility;
import flash.events.Event;
import mx.accessibility.AccConst;
import mx.containers.TabNavigator;
import mx.controls.TabBar;
import mx.controls.tabBarClasses.Tab;
import mx.core.UIComponent;
import mx.core.mx_internal;

use namespace mx_internal;

/**
 *  TabBarAccImpl is a subclass of AccessibilityImplementation
 *  which implements accessibility for the TabBar class.
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion Flex 3
 */
public class TabBarAccImpl extends AccImpl
{
    include "../core/Version.as";

	//--------------------------------------------------------------------------
	//
	//  Class methods
	//
	//--------------------------------------------------------------------------

	/**
	 *  Enables accessibility in the TabBar class.
	 * 
	 *  <p>This method is called by application startup code
	 *  that is autogenerated by the MXML compiler.
	 *  Afterwards, when instances of TabBar are initialized,
	 *  their <code>accessibilityImplementation</code> property
	 *  will be set to an instance of this class.</p>
	 *  
	 *  @langversion 3.0
	 *  @playerversion Flash 9
	 *  @playerversion AIR 1.1
	 *  @productversion Flex 3
	 */
	public static function enableAccessibility():void
	{
		TabBar.createAccessibilityImplementation =
			createAccessibilityImplementation;
	}

	/**
	 *  @private
	 *  Creates a TabBar's AccessibilityImplementation object.
	 *  This method is called from UIComponent's
	 *  initializeAccessibility() method.
	 */
	mx_internal static function createAccessibilityImplementation(
								component:UIComponent):void
	{
		component.accessibilityImplementation =
			new TabBarAccImpl(component);
	}

	//--------------------------------------------------------------------------
	//
	//  Constructor
	//
	//--------------------------------------------------------------------------

	/**
	 *  Constructor.
	 *
	 *  @param master The UIComponent instance that this AccImpl instance
	 *  is making accessible.
	 *  
	 *  @langversion 3.0
	 *  @playerversion Flash 9
	 *  @playerversion AIR 1.1
	 *  @productversion Flex 3
	 */
	public function TabBarAccImpl(master:UIComponent)
	{
		super(master);

		role = AccConst.ROLE_SYSTEM_PAGETABLIST;
	}

	//--------------------------------------------------------------------------
	//
	//  Overridden properties: AccImpl
	//
	//--------------------------------------------------------------------------

	//----------------------------------
	//  eventsToHandle
	//----------------------------------

	/**
	 *  @private
	 *	Array of events that we should listen for from the master component.
	 */
	override protected function get eventsToHandle():Array
	{
		return super.eventsToHandle.concat([ "itemClick", "focusDraw" ]);
	}
	
	//--------------------------------------------------------------------------
	//
	//  Overridden methods: AccessibilityImplementation
	//
	//--------------------------------------------------------------------------

	/**
	 *  @private
	 *  Gets the role for the component.
	 *
	 *  @param childID children of the component
	 */
	override public function get_accRole(childID:uint):uint
	{
		return childID == 0 ? role : AccConst.ROLE_SYSTEM_PAGETAB;
	}

	/**
	 *  @private
	 *  IAccessible method for returning the state of the Tabs.
	 *  States are predefined for all the components in MSAA. Values are assigned to each state.
	 *  Depending upon the Tab being Focusable, Focused and Moveable, a value is returned.
	 *
	 *  @param childID:uint
	 *
	 *  @return STATE:uint
	 */
	override public function get_accState(childID:uint):uint
	{
		var accState:uint = getState(childID);

		var tabBar:TabBar = TabBar(master);
		
		if (childID > 0)
		{
			accState = AccConst.STATE_SYSTEM_SELECTABLE | AccConst.STATE_SYSTEM_FOCUSABLE;

			var index:int = childID - 1;

			if (index == tabBar.selectedIndex)
				accState |= AccConst.STATE_SYSTEM_SELECTED;
				
			if (index == tabBar.focusedIndex)
				accState |= AccConst.STATE_SYSTEM_FOCUSED;
		}		
		return accState;
	}

	/**
	 *  @private
	 *  IAccessible method for returning the Default Action.
	 *
	 *  @param childID uint
	 *
	 *  @return focused childID.
	 */
	override public function get_accDefaultAction(childID:uint):String
	{
		return "Switch";
	}

	/**
	 *  @private
	 *  IAccessible method for executing the Default Action.
	 *
	 *  @param childID uint
	 *
	 *  @return focused childID.
	 */
	override public function accDoDefaultAction(childID:uint):void
	{
		if (childID > 0)
			TabBar(master).selectButton(childID - 1, true);
	}

	/**
	 *  @private
	 *  Method to return the childID Array.
	 *
	 *  @return Array
	 */
	override public function getChildIDArray():Array
	{
		var n:int = TabBar(master).numChildren;

		return createChildIDArray(n);
	}

	/**
	 *  @private
	 *  IAccessible method for returning the bounding box of the Tabs.
	 *
	 *  @param childID:uint
	 *
	 *  @return Location:Object
	 */
	override public function accLocation(childID:uint):*
	{
		return TabBar(master).getChildAt(childID - 1);
	}

	/**
	 *  @private
	 *  IAccessible method for returning the childFocus of the TabBar.
	 *
	 *  @param childID uint
	 *
	 *  @return focused childID.
	 */
	override public function get_accFocus():uint
	{
		var index:int = TabBar(master).focusedIndex;
		
		return index >= 0 ? index + 1 : 0;
	}

	//--------------------------------------------------------------------------
	//
	//  Overridden methods: AccImpl
	//
	//--------------------------------------------------------------------------

	/**
	 *  @private
	 *  method for returning the name of the Tab
	 *  which is spoken out by the screen reader.
	 *
	 *  @param childID:uint
	 *
	 *  @return Name:String
	 */
	override protected function getName(childID:uint):String
	{
		if (childID == 0)
			return "";

		var tabBar:TabBar = TabBar(master);

		var index:int = childID - 1;
		
		// With new version of JAWS, when we add a new child, we get nonsense number
		// not caught above. In this case, return last tab.
		if (index > tabBar.numChildren || index < 0)
			index = tabBar.numChildren -1;
		
		var item:Tab = Tab(tabBar.getChildAt(index));

		return item.label;
	}

	//--------------------------------------------------------------------------
	//
	//  Overridden event handlers: AccImpl
	//
	//--------------------------------------------------------------------------

	/**
	 *  @private
	 *  Override the generic event handler.
	 *  All AccImpl must implement this to listen for events
	 *  from its master component. 
	 */
	override protected function eventHandler(event:Event):void
	{
		// Let AccImpl class handle the events
		// that all accessible UIComponents understand.
		$eventHandler(event);

		var index:int;
				
		switch (event.type)
		{
			case "focusDraw":
			{
				index = TabBar(master).focusedIndex;
				
				if (index >= 0)
				{
					Accessibility.sendEvent(master, index + 1,
											AccConst.EVENT_OBJECT_FOCUS);
				}
				break;
			}
			
			case "itemClick":
			{
				// use selectedIndex until #126565 is fixed.
				index = TabBar(master).selectedIndex;
				
				if (index >= 0)
				{
					Accessibility.sendEvent(master, index + 1,
											AccConst.EVENT_OBJECT_SELECTION);
					Accessibility.sendEvent(master, index + 1,
											AccConst.EVENT_OBJECT_FOCUS);
				}
				break;
			}
		}
	}
}

}
