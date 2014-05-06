 // This should be included in the function body of a defensive program
 var deflib =
 {
   DObject: function(){this.O = {}},
   DArray: function()
   {
    this.A = new deflib.DObject();
    for(var i=0; i < arguments.length; i++)
     this.push(arguments[i]);
   },
   DString: function(s){this.C = s+''},
   stringify: function (o, stack)
   {
    if(typeof stack == "undefined") stack = new this.DArray();
    try {
     stack.forEach(function(i,e){if(e===o) throw "recursive"});
    }
    finally{}

    if(o === null || o === +'a' || o*o === 1/0) return "null";
    switch(typeof o)
    {
     case "number":
     case "boolean":
      return o+'';
     case "object":
      if(o instanceof this.DString) return '"'+o.escape()+'"';
      var a = (o instanceof this.DArray);
      if(!(a || o instanceof this.DObject)) return "null";
      var res = (a ? '[' : '{'), c=0; stack.push(o);

      o.forEach(function(i,p){
       if(typeof p == 'undefined' || typeof p == 'function') return;
       res += (c++ > 0 ? ',' : '')+(a?'':'"'+(new deflib.DString(i).escape())+'":')+deflib.stringify(p, stack);
      });
	
      res += (a?']':'}'); stack.pop();
      return res;
     break;

     default: return undefined;
    }
   }
  };
   
  deflib.DObject.prototype =
  {
   O: null,
   DS: "f^àçé$,ù²~k3€",
   valueOf: function(){return this;},
   toString: function(){return '[object DObject]';},
   S: function(k,v){return this.O[this.DS+k] = v},
   G: function(k){return this.O[this.DS+k]},
   hasOwnProperty: function(k){return (this.DS+k) in this.O},
   serialize: null,
   forEach: function(f)
   {
    if(typeof f != "function") return;
    for(var i in this.O)
    {
     for(var j=0, c = i.length >= this.DS.length, n = ''; j < i.length; j++)
     {
      if(j>=this.DS.length) n+=i[j];
      else if(this.DS[j] != i[j]) c = 0;
     }
     if(c) f(n, this.O[i]);
    }
   }
  };

  deflib.DArray.prototype =
  {
   A: null,
   length: 0,
   toString: function(){
    var out = '', len = this.length;
    this.forEach(function(k,v){out+=v+(k < len-1?',':'')});
    return out;
   },
   valueOf: function(){return this},
   push: function(v){this.S(this.length++, v);},
   pop: function(){var v; if(this.length){v = this.G(this.length-1); this.length--; return v}},
   shift: function(){
    if(!this.length) return;
    for(var r = this.G(0), i=0; i < this.length-1; i++)
     this.S(i, this.G(i+1));
    this.length--; return r;
   },
   G: function(i){
    if(+i !== NaN && +i == (+i|0) && +i >= this.length) return;
    return this.A.G(i);
   },
   S: function(i,v){
    if(+i !== NaN && +i == (+i|0) && +i >= this.length) this.length = +i+1;
    return this.A.S(i,v);
   },
   apply: function(f){
    if(typeof f != "function") return;
    this.A.forEach(function(k,v){this.S(k, f(v))});
   },
   map: function(f){
    var r = new deflib.DArray();
    this.A.forEach(function(k,v){r.S(k,f(v))});
    return r;
   },
   forEach: function(f){return this.A.forEach(f)}
  };
  
  deflib.DString.prototype =
  {
   C: "",
   
   valueOf: function(){return this.C;},
   toString: function(){return this.C;},
   
   get length(){return this.C.length},
   G: function(k){
    if((k = +k) !== NaN && k >= 0 && k < this.length) return this.C[k];
   },
   S: function(){},
   
   append: function(t){this.C += (t+'');},
   
   escape: function()
   {
    for(var i=0, out=''; i < this.length; i++)
    {
     if(this.C[i] == '"' || this.C[i] == '\\') out += '\\';
     out += this.C[i];
    }
    return new deflib.DString(out);
   },
   
   indexOf: function(w, all)
   {
    var m = 0, i = 0, pos, cnd, sl = this.C.length, wl = w.length,
        res = new deflib.DArray(), t = new deflib.DArray(-1);

    if(typeof all != "boolean") all = false;
    
    if(!wl)
    {
     for(i=0; i < sl; i++) res.push(i);
     return all ? res : 0;
    }

    for(pos=2, cnd=0; pos < wl;)
    {
     if (w.G(pos-1) == w.G(cnd)) t.S(pos++,cnd+++1);
     else if(cnd > 0) cnd = t.G(cnd);
     else t.S(pos++, 0);
    }

    while(m+i < sl)
    {
     if(this.G(m+i) == w.G(i))
     {
      if(++i == wl)
      {
       if(all){ res.push(m); m += i; i = 0; }
       else return m;
      }
     }
     else
     {
      m += i - t.G(i);
      i = (t.G(i) > -1) ? t.G(i) : 0;
     }
    }
    return all ? res : -1;
   },
   
   split: function(w)
   {
    var res = new deflib.DArray(), i, j, p, pos, sl = this.length, wl = w.length;
    pos = this.indexOf(w, true);
    j = pos.shift();

    for(i=0, p = ''; i < sl;)
    {
     if(i === j)
     {
      if(wl+i > 0) res.push(new deflib.DString(p));
	     i += wl; p = '';
	     j = pos.shift();
     }
     else p += this.G(i++);
    }
    res.push(new deflib.DString(p));
    return res;
   },
   
   substr: function(i, j)
   {
    if((i |= 0) >= this.length) return new deflib.DString('');
    if(i < 0) i += this.length; if(i < 0) i = 0;
  
    if(j === undefined || typeof j != 'number') j = this.length;
    if(j < 0) j += this.length; else j += i;
  
    if(j < 0) return new deflib.DString('');
    if(j > this.length ) j = this.length;
  
    for(var k=i, out=''; k < j; k++) out += this.C[k];
    return new deflib.DString(out);
   }
  };
