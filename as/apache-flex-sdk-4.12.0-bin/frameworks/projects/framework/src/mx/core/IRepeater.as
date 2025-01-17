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

package mx.core
{

/**
 *  The IRepeater interface defines the 
 *  public APIs of the Repeater object.
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion Flex 3
 */
public interface IRepeater
{
    //--------------------------------------------------------------------------
    //
    //  Properties
    //
    //--------------------------------------------------------------------------

    //----------------------------------
    //  container
    //----------------------------------

    /**
     *  The container that contains this Repeater,
     *  and in which it will create its children.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function get container():IContainer;

    //----------------------------------
    //  count
    //----------------------------------

    /**
     *  The number of times this Repeater should execute.
     *
     *  <p>If the Repeater reaches the end of the data provider while
     *  executing, the number of times it actually executes will be less
     *  that the requested count.</p>
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function get count():int;
    
    /**
     *  @private
     */
    function set count(value:int):void;

    //----------------------------------
    //  currentIndex
    //----------------------------------

    /**
     *  The index of the item in the <code>dataProvider</code> currently
     *  being processed while this Repeater is executing.
     *
     *  <p>After the Repeater has finished executing,
     *  this property is <code>-1</code>.
     *  However, the <code>repeaterIndex</code> property of a repeated
     *  component instance remembers the index of the
     *  <code>dataProvider</code> item from which it was created.
     *  In the case of nested Repeaters, you can use the
     *  <code>repeaterIndices</code> array.</p>
     *
     *  @see mx.core.UIComponent#repeaterIndex
     *  @see mx.core.UIComponent#repeaterIndices
     *  @see mx.core.UIComponent#instanceIndex
     *  @see mx.core.UIComponent#instanceIndices
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function get currentIndex():int;

    //----------------------------------
    //  currentItem
    //----------------------------------

    /**
     *  The item in the <code>dataProvider</code> currently being processed
     *  while this Repeater is executing.
     *
     *  <p>After the Repeater has finished executing,
     *  this property is <code>null</code>.
     *  However, in this case you can call the <code>getRepeaterItem()</code>
     *  method of the repeated component instance to get the
     *  <code>dataProvider</code> item from which it was created.</p>
     *
     *  @see mx.core.UIComponent#getRepeaterItem()
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function get currentItem():Object;

    //----------------------------------
    //  dataProvider
    //----------------------------------

    /**
     *  The data provider used by this Repeater to create repeated instances
     *  of its children.
     *  
     *  <p>If you read the <code>dataProvider</code> property, you always get
     *  an ICollectionView object or <code>null</code>.
     *  If you set the <code>dataProvider</code> property to anything other than
     *  <code>null</code>, it is converted into an ICollectionView object,
     *  according the following rules:</p>
     *
     *  <ul>
     *    <li>If you set it to an Array, it is converted into an ArrayCollection.</li>
     *    <li>If you set it to an ICollectionView, no conversion is performed.</li>
     *    <li>If you set it to an IList, it is converted into a ListCollectionView.</li>
     *    <li>If you set it to an XML or XMLList, it is converted
     *      into an XMLListCollection.</li>
     *    <li>Otherwise, it is converted to a single-element ArrayCollection.</li>
     *  </ul>
     *
     *  <p>You must specify a value for the <code>dataProvider</code> property 
     *  or the Repeater component will not execute.</p>
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function get dataProvider():Object;
    
    /**
     *  @private
     */
    function set dataProvider(value:Object):void;

    //----------------------------------
    //  recycleChildren
    //----------------------------------

    /**
     *  A Boolean flag indicating whether this Repeater should re-use
     *  previously created children, or create new ones.
     *
     *  <p>If <code>true</code>, when this Repeater's
     *  <code>dataProvider</code>, <code>startingIndex</code>,
     *  or <code>count</code> changes, it will recycle the existing
     *  children by binding the new data into them.
     *  If more children are required, they are created and added.
     *  If fewer children are required, the extra ones are removed
     *  and garbage collected.</p>
     *
     *  <p>If <code>false</code>, when this Repeater's 
     *  <code>dataProvider</code>, <code>startingIndex</code>,
     *  or <code>count</code> changes, it will remove any previous
     *  children that it created and then create and 
     *  add new children from the new data items.</p>
     *
     *  <p>This property is <code>false</code> by default.
     *  Setting it to <code>true</code> can increase performance,
     *  but is not appropriate in all situations.
     *  For example, if the previously created children have state
     *  information such as text typed in by a user, then this
     *  state will not get reset when the children are recycled.</p>
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function get recycleChildren():Boolean;
    
    /**
     *  @private
     */
    function set recycleChildren(value:Boolean):void;

    //----------------------------------
    //  startingIndex
    //----------------------------------

    /**
     *  The index into the <code>dataProvider</code> at which this Repeater
     *  starts creating children.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function get startingIndex():int;
    
    /**
     *  @private
     */
    function set startingIndex(value:int):void;

    //--------------------------------------------------------------------------
    //
    //  Methods
    //
    //--------------------------------------------------------------------------

    /**
     *  Initializes a new Repeater object.
     *
     *  <p>This method is called by the Flex framework.
     *  Developers should not need to call it.</p>
     *
     *  @param container The Container that contains this Repeater,
     *  and in which this Repeater will create its children.
     *
     *  @param recurse A Boolean flag indicating whether this Repeater
     *  should create all descendants of its children.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function initializeRepeater(container:IContainer, recurse:Boolean):void;
        
    /**
     *  Executes the bindings into all the UIComponents created
     *  by this Repeater.
     *
     *  <p>This method is called by the Flex framework.
     *  Developers should not need to call it.</p>
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    function executeChildBindings():void;
}

}
