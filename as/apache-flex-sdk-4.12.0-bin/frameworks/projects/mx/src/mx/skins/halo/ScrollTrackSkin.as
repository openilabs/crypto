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

package mx.skins.halo
{

import flash.display.GradientType;
import mx.skins.Border;
import mx.styles.StyleManager;
import mx.utils.ColorUtil;

/**
 *  The skin for the track in a ScrollBar.
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion Flex 3
 */
public class ScrollTrackSkin extends Border
{
	include "../../core/Version.as";

	//--------------------------------------------------------------------------
	//
	//  Constructor
	//
	//--------------------------------------------------------------------------

	/**
	 *  Constructor.
	 *  
	 *  @langversion 3.0
	 *  @playerversion Flash 9
	 *  @playerversion AIR 1.1
	 *  @productversion Flex 3
	 */
	public function ScrollTrackSkin()
	{
		super(); 
	}

    //--------------------------------------------------------------------------
    //
    //  Overridden properties
    //
    //--------------------------------------------------------------------------

    //----------------------------------
	//  measuredWidth
    //----------------------------------
    
    /**
     *  @private
     */    
    override public function get measuredWidth():Number
    {
        return 16;
    }
    
    //----------------------------------
	//  measuredHeight
    //----------------------------------
    
    /**
     *  @private
     */        
    override public function get measuredHeight():Number
    {
        return 1;
    }
		
	//--------------------------------------------------------------------------
	//
	//  Overridden methods
	//
	//--------------------------------------------------------------------------
		
	/**
	 *  @private
	 */
	override protected function updateDisplayList(w:Number, h:Number):void
	{
		super.updateDisplayList(w, h);

		// User-defined styles.
		var fillColors:Array = getStyle("trackColors");
        styleManager.getColorNames(fillColors);
		
		var borderColor:uint =
			ColorUtil.adjustBrightness2(getStyle("borderColor"), -20);
		
		var borderColorDrk1:uint =
			ColorUtil.adjustBrightness2(borderColor, -30);
		
		graphics.clear();
		
		var fillAlpha:Number = 1;
		
		if (name == "trackDisabledSkin")
			fillAlpha = .2;
		
		// border
		drawRoundRect(
			0, 0, w, h, 0,
			[ borderColor, borderColorDrk1 ], fillAlpha,
			verticalGradientMatrix(0, 0, w, h),
			GradientType.LINEAR, null,
			{ x: 1, y: 1, w: w - 2, h: h - 2, r: 0 }); 

		// fill
		drawRoundRect(
			1, 1, w - 2, h - 2, 0,
			fillColors, fillAlpha, 
			horizontalGradientMatrix(1, 1, w / 3 * 2, h - 2)); 
	}
}

}
