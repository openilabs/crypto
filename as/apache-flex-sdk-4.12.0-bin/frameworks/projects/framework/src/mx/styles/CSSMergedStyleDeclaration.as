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

package mx.styles
{
    
import flash.display.DisplayObject;
import flash.events.EventDispatcher;
import flash.utils.Dictionary;

import mx.core.Singleton;
import mx.core.mx_internal;
import mx.events.FlexChangeEvent;
import mx.managers.ISystemManager;
import mx.managers.SystemManagerGlobals;
import mx.utils.ObjectUtil;
import flash.events.Event;

use namespace mx_internal;

[ExcludeClass]

/**
 *  The CSSStyleDeclaration class represents a set of CSS style rules.
 *  The MXML compiler automatically generates one CSSStyleDeclaration object
 *  for each selector in the CSS files associated with a Flex application.
 *  
 *  <p>A CSS rule such as
 *  <pre>
 *      Button { color: #FF0000 }
 *  </pre>
 *  affects every instance of the Button class;
 *  a selector like <code>Button</code> is called a type selector
 *  and must not start with a dot.</p>
 *
 *  <p>A CSS rule such as
 *  <pre>
 *      .redButton { color: #FF0000 }
 *  </pre>
 *  affects only components whose <code>styleName</code> property
 *  is set to <code>"redButton"</code>;
 *  a selector like <code>.redButton</code> is called a class selector
 *  and must start with a dot.</p>
 *
 *  <p>You can access the autogenerated CSSStyleDeclaration objects
 *  using the <code>StyleManager.getStyleDeclaration()</code> method,
 *  passing it either a type selector
 *  <pre>
 *  var buttonDeclaration:CSSStyleDeclaration =
 *      StyleManager.getStyleDeclaration("Button");
 *  </pre>
 *  or a class selector
 *  <pre>
 *  var redButtonStyleDeclaration:CSSStyleDeclaration =
 *      StyleManager.getStyleDeclaration(".redButton");
 *  </pre>
 *  </p>
 *
 *  <p>You can use the <code>getStyle()</code>, <code>setStyle()</code>,
 *  and <code>clearStyle()</code> methods to get, set, and clear 
 *  style properties on a CSSStyleDeclaration.</p>
 *
 *  <p>You can also create and install a CSSStyleDeclaration at run time
 *  using the <code>StyleManager.setStyleDeclaration()</code> method:
 *  <pre>
 *  var newStyleDeclaration:CSSStyleDeclaration = new CSSStyleDeclaration(".bigMargins");
 *  newStyleDeclaration.defaultFactory = function():void
 *  {
 *      leftMargin = 50;
 *      rightMargin = 50;
 *  }
 *  StyleManager.setStyleDeclaration(".bigMargins", newStyleDeclaration, true);
 *  </pre>
 *  </p>
 *
 *  @see mx.core.UIComponent
 *  @see mx.styles.StyleManager
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion Flex 3
 */
public class CSSMergedStyleDeclaration extends CSSStyleDeclaration
{
    include "../core/Version.as";
    

    //--------------------------------------------------------------------------
    //
    //  Constructor
    //
    //--------------------------------------------------------------------------
    
    /**
     *  @private
     * 
     *  A CSSStyleDeclaration that is a merger between two styles. The styles are for the same
     *  selector. One style is from the local style manager and the other style is from the style manager's
     *  parent.
     * 
     *  @param style - A style from the local style manager. May be null.
     * 
     *  @param parentStyle - The style in the parent style manager for the same selector. May be null.
     *
     *  @param selector - If the selector is a CSSSelector then advanced
     *  CSS selectors are supported. If a String is used for the selector then
     *  only simple CSS selectors are supported. If the String starts with a
     *  dot it is interpreted as a universal class selector, otherwise it must
     *  represent a simple type selector. If not null, this CSSStyleDeclaration
     *  will be registered with StyleManager. 
     *  
     *  @param styleManager - The style manager to set this declaration into. If the
     *  styleManager is null the top-level style manager will be used.
     * 
     *  @param setSelector - If true set the selector in the styleManager. If setSelector
     *  is false this style declaration can be set in the styleManager at a later time
     *  by calling <code>styleManager.setStyleDeclaration(styleDeclaration.selectorString, styleDeclaration, false);
     *  </code>
     *
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 4
     * 
     */ 
    public function CSSMergedStyleDeclaration(style:CSSStyleDeclaration, parentStyle:CSSStyleDeclaration,
                        selector:Object=null, styleManager:IStyleManager2=null, setSelector:Boolean = false)
    {
        super(selector, styleManager, setSelector);
        
        this.style = style;
        this.parentStyle = parentStyle;

        var i:uint;
        var n:uint;
        var effectsArray:Array;
        
        // combine effects child and parent effects array
        if (style && style.effects)
        {
            effects = [];
            
            effectsArray = style.effects;
            n = effectsArray.length;
            for (i = 0; i < n; i++)
                effects[i] = effectsArray[i];
        }
        
        if (parentStyle && parentStyle.effects)
        {
            if (!effects)
                effects = [];

            effectsArray = parentStyle.effects;
            n = effectsArray.length;
            for (i = 0; i < n; i++)
            {
                effects[i] = effectsArray[i];
                if (effects.indexOf(effectsArray[i]) == -1)
                    effects[i] = effectsArray[i];
            }
        }
        
        updateOverrides = true;
    }

    //--------------------------------------------------------------------------
    //
    //  Variables
    //
    //--------------------------------------------------------------------------
    
    /**
     *  @private
     * 
     *  Local storage for the style in the local style manager.
     */
    private var style:CSSStyleDeclaration;
    
    /**
     *  @private
     * 
     *  Local storage for the style in the parent style manager.
     */
    private var parentStyle:CSSStyleDeclaration;

    /**
     *  @private
     * 
     *  If true then update the overrides array from the style and
     *  parentStyle.
     */
    private var updateOverrides:Boolean;
    
    //--------------------------------------------------------------------------
    //
    //  Properties
    //
    //--------------------------------------------------------------------------
    
    //----------------------------------
    //  defaultFactory
    //----------------------------------
    
    /**
     *  @private
     */
    private var _defaultFactory:Function;
    
    
    [Inspectable(environment="none")]
    
    /**
     *  @private
     */
    override public function get defaultFactory():Function
    {
        if (_defaultFactory != null)
            return _defaultFactory;
        
        if ((style != null && style.defaultFactory != null) || 
           (parentStyle != null && parentStyle.defaultFactory != null))
        {
            _defaultFactory = function():void
            {
                if (parentStyle && parentStyle.defaultFactory != null)
                    parentStyle.defaultFactory.apply(this);
                
                if (style && style.defaultFactory != null)
                    style.defaultFactory.apply(this);
            };            
        }
        
        return _defaultFactory;
    }
    
    /**
     *  @private
     */
    override public function set defaultFactory(f:Function):void
    {
        // not supported
    }
    
    //----------------------------------
    //  factory
    //----------------------------------
    
    /**
     *  @private
     */
    private var _factory:Function;
    
    [Inspectable(environment="none")]
    
    /**
     *  @private
     */
    override public function get factory():Function
    {
        if (_factory != null)
            return _factory;
        
        if ((style != null && style.factory != null) || 
            (parentStyle != null && parentStyle.factory != null))
        {
            _factory = function():void
            {
                if (parentStyle && parentStyle.factory != null)
                    parentStyle.factory.apply(this);
                
                if (style && style.factory != null)
                    style.factory.apply(this);
            };            
        }     
        
        return _factory;
    }

    /**
     *  @private
     */
    override public function set factory(f:Function):void
    {
        // not supported
    }
    
    /**
     *  @private
     */
    override public function get overrides():Object
    {
        if (!updateOverrides)
            return super.overrides;
        
        var obj:Object;
        var mergedOverrides:Object = null;
        
        if (style && style.overrides)
        {
            mergedOverrides = [];
            
            var childOverrides:Object = style.overrides;
            for (obj in childOverrides)
                mergedOverrides[obj] = childOverrides[obj];            
        }
        
        if (parentStyle && parentStyle.overrides)
        {
            if (!mergedOverrides)
                mergedOverrides = [];
                
            var parentOverrides:Object = parentStyle.overrides;
            for (obj in parentOverrides)
            {
                if (mergedOverrides[obj] === undefined)
                    mergedOverrides[obj] = parentOverrides[obj];
            }
        }
        
        super.overrides = mergedOverrides;        
        updateOverrides = false;
        
        return mergedOverrides;
    }
    
    /**
     *  @private
     */
    override public function set overrides(o:Object):void
    {
        // not supported
    }
 
    /**
     *  @private
     */
    override public function setStyle(styleProp:String, newValue:*):void
    {
        // not supported
    }
 
    /**
     *  @private
     */
    override mx_internal function addStyleToProtoChain(chain:Object,
                                              target:DisplayObject,
                                              filterMap:Object = null):Object
    {
        // If we have a local style, then add only it to the chain. It will
        // take are of adding its parent to the chain.
        // If then is no style, but a parentStyle, then add the parent Style
        // to the chain.
        if (style)
            return style.addStyleToProtoChain(chain, target, filterMap);
        else if (parentStyle)
            return parentStyle.addStyleToProtoChain(chain, target, filterMap);
        else
            return chain;
    }    
    
}
}