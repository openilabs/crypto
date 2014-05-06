/*
 * Lightweight Self-extending arrays
 * Does not typecheck but can be used to
 * extend within a given template
 */
 var LArray = function()
 {
  var block = function(tpl)
  {
   var a = tpl;
   this.content = a;
   this.rest = null;
  };

  block.prototype =
  {
   content:[],
   rest: null
  };

  var state = function(tpl)
  {
   this.tpl = tpl;
  };

  state.prototype =
  {
   blocks: 0,
   tpl: function(){return []},
   content: null,
   last: null,

   extend: function()
   {
    var a = new block(this.tpl()),
        b = this.last;
    if(b===null) this.content = a;
    else b.rest = a;
    this.blocks++;
    this.last = a;
    return a.content;
   },

   iter: function(f)
   {
    var i = 0, a = this.content;
    while(i++ < this.blocks)
    {
     f(a.content);
     a = a.rest;
    }
   },

   G: function(i)
   {
    if(i >= this.blocks) return null;
    for(var j=0, a=this.content; j<i; j++) a=a.rest;
    return a.content;
   }
  };

  return state;
 }();

