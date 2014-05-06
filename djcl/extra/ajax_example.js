var _lib = {secret: function(s){return s+''}};

var defensive = (function(origin, keys)
{
 var _djcl = DJCL;

 var request = function(s) {
  return _djcl.jwe_encrypt(s, keys.hostKey, keys.publicKey);
 };

 var response = function(s) {
  return _djcl.jwt_decrypt(s, keys.hostKey);
 };

 var _ = function(s)
 {
  var o = {action: "", param: ""};

  _djcl.parse(s, o, {type:"object", props:[
   {name:"action", value:{type: "string", props:[]}},
   {name:"param", value:{type: "string", props:[]}}]});

  switch(o.action)
  {
   case "request": return request(o.param);
   case "response": return response(o.param);
  }

  return origin;
 }

 return function(s){ if(typeof s != "string") return ""; return _(s); };
})("http://www.defensivejs.com", {hostKey: "", publicKey: ""});

(function()
{
 var _lib = {
  request: function(url, callback) { /* Translate to WebSpi */
   var o = /* new */ XMLHttpRequest();
   o.open("GET", url);
   o.onload = function() { callback(this._o.responseText); }
   o.send();
  },

  public: function(s) { alert(s); } /* Translate to public channel out */
 };

 var req = JSON.stringify({action: "request", param: "get_time"});
 var url = defensive(JSON.stringify({action: "origin", param: ""}))+"/?req="+defensive(req);

 _lib.request(url, function(s)
 {
  var r = JSON.parse(defensive(JSON.stringify({action:"response", param: s})));
  var msg = (!!r.error ? r.error : r.response);
  _lib.public('The time is: '+msg);
 });
})();

