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
package flashx.undo
{   
    /**
     * IUndoManager defines the interface for managing the undo and redo stacks.
     * 
     * <p>An undo manager maintains a stack of operations that can be undone and redone.</p>
     * 
     * @playerversion Flash 10
     * @playerversion AIR 1.5
     * @langversion 3.0
     */
    public interface IUndoManager 
    {   
        /**
         * Clears both the undo and the redo histories.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */ 
        function clearAll():void;
        
        /**
         * The maximum number of undoable or redoable operations to track.
         * 
         * <p>To disable the undo function, set this value to 0.</p> 
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function get undoAndRedoItemLimit():int;
        function set undoAndRedoItemLimit(value:int):void;

        /**
         * Indicates whether there is currently an operation that can be undone.
         * 
         * @return Boolean <code>true</code>, if there is an operation on the undo stack that can be reversed.
         * Otherwise, <code>false</code>.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function canUndo():Boolean;
        
        /**
         * Returns the next operation to be undone.
         * 
         * @return The undoable IOperation object, or <code>null</code>, if no undoable operation
         * is on the stack.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function peekUndo():IOperation;
        
        /**
         * Removes the next operation to be undone from the undo stack, and returns it.
         * 
         * @return The undoable IOperation object, or <code>null</code>, if no undoable operation
         * is on the stack.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function popUndo():IOperation;

        /**
         * Adds an undoable operation to the undo stack.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function pushUndo(operation:IOperation):void;
        
        /**
         * Clears the redo stack.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function clearRedo():void;

        /**
         * Indicates whether there is currently an operation that can be redone.
         * 
         * @return Boolean <code>true</code>, if there is an operation on the redo stack that can be redone.
         * Otherwise, <code>false</code>.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function canRedo():Boolean;

        /**
         * Returns the next operation to be redone.
         * 
         * @return The redoable IOperation object, or <code>null</code>, if no redoable operation
         * is on the stack.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function peekRedo():IOperation;
        
        /**
         * Removes the next operation to be redone from the redo stack, and returns it.
         * 
         * @return The redoable IOperation object, or <code>null</code>, if no redoable operation
         * is on the stack.
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function popRedo():IOperation;

        /**
         * Adds a redoable operation to the redo stack.
         * 
         * @playerversion Flash 10
         * @playerversion AIR 1.5
         * @langversion 3.0
         */
        function pushRedo(operation:IOperation):void;

        /** 
         * Removes the next IOperation object from the undo stack and calls the performUndo() 
         * function of that object.
         * 
         * @see flashx.textLayout.edit.IEditManager#undo()
         * @see flashx.undo.IUndoManager#canUndo()
         * @see flashx.undo.IUndoManager#clearUndo()
         * @see flashx.undo.IUndoManager#peekUndo()
         * @see flashx.undo.IUndoManager#pushUndo()
         * @see flashx.undo.IUndoManager#popUndo()
         */
        function undo():void;
        
        /** 
         * Removes the next IOperation object from the redo stack and calls the performRedo() 
         * function of that object.
         * 
         * @see flashx.textLayout.edit.IEditManager#redo()
         * @see flashx.undo.IUndoManager#canRedo()
         * @see flashx.undo.IUndoManager#clearRedo()
         * @see flashx.undo.IUndoManager#peekRedo()
         * @see flashx.undo.IUndoManager#pushRedo()
         * @see flashx.undo.IUndoManager#popRedo()
         */
        function redo():void;                       
    }
}
