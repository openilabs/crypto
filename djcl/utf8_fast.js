
/** Speed hack for defensive UTF8 decoding.
 ** Relies on ability to detect tampered Function constructor
 ** (which provides the same functionality as eval)
 **/

(function()
{
 var hex = encoding.hex,
     f = (function g(){
      try{
       var f = g.constructor;
       f.prototype = null;
       if(f instanceof f) return f
      }catch(e){}})(),
     o = "{", t = '"', c = "", i = 0;

 if(typeof f == "function")
 {
  for(i=0; i<65536; i++)
  {
   c = hex[i>>12]+hex[i>>8&15]+hex[i>>4&15]+hex[i&15];
   o += '"\\u'+c+'":'+i+',';
   t += '\\u'+c;
  }

  o = new f('return ['+o+'}'+','+t+'"]')();
  encoding.utf8 = o[1];
  encoding.utf8_table = o[0];
  encoding.charCode = function(x){return this.utf8_table[x]};
  encoding.fromCharCode = function(i){return this.utf8[i]};
 }
})();

