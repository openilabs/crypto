with({
 /*** Origin of the service that uses this bookmarklet ***/
 O: 'https://lp.com',
 /*** THIS IS THE DEFENSIVE WRAPPER ***/
 DJS: function()
 {
   /*** SECRET BOOKMARKLET KEY ***/
   var MACKEY = '85214b9e25a7a8a6715076c49dc376b0',
   hex = "0123456789abcdef",
   h2b = function(n){return +('0x'+n)|0},
   b2h = function(n){return (n>>>=0)<hex.length ? hex[n] : "0"},
   _round = function(H, w)
   {
    var a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], i = 0,
        k = [0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6],
        S = function(n,x){return (x << n)|(x >>> 32-n)}, tmp = 0,

    f = function(r, b, c, d)
    {
     if(r < 20) return (b & c) | (~b & d);
     if(r < 40) return b ^ c ^ d;
     if(r < 60) return (b & c) | (b & d) | (c & d);
     return b ^ c ^ d;
    }

    for(i=0; i < 80; i++)
    {
     if(i >= 16) w[i&127] = S(1, w[(i-3)&127]  ^ w[(i-8)&127]
                               ^ w[(i-14)&127] ^ w[(i-16)&127]);
     tmp = (S(5, a) + f(i, b, c, d) + e + w[i&127] + k[(i/20)&3])|0;
     e = d; d = c; c = S(30, b); b = a; a = tmp;
    }

    H[0] = (H[0]+a)|0; H[1] = (H[1]+b)|0; H[2] = (H[2]+c)|0;
    H[3] = (H[3]+d)|0; H[4] = (H[4]+e)|0;
   },
   sha = function(s)
   {
    var len = (s+='80').length>>1, blocks = len >> 6,
        chunck = len&63, res = "", i = 0, j = 0,
        H = [0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0],
        w = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

    while(chunck++ != 56)
    {
     s+='00';
     if(chunck == 64){ blocks++; chunck = 0; }
    }

    for(s+='00000000', chunck=7, len=8*(len-1); chunck >= 0; chunck--)
     s += b2h(len >> (4*chunck) & 15);

    for(i=0; i < s.length; i++)
    {
     res += s[i];
     if((i&7)==7){ w[(i>>3)&15] = h2b(res); res = ''}
     if((i&127)==127) _round(H, w);
    }

    res='';
    for(i=0; i < H.length; i++)
     for(j=7; j >= 0; j--)
      res += b2h(H[i] >> (4*j) & 15);

    return res;
   },
   HMAC = function(key, msg)
   {
    var key = key+'', msg = msg+'', i = 0,
        c = 0, inner = "", outer = "";

    if(key.length > 128) key = sha(key);
    while(key.length < 128) key+='0';

    for(i=0; i < key.length; i++)
    {
     c = h2b(key[i]);
     inner += b2h(c ^ (3<<(i%2)));
     outer += b2h(c ^ (5+7*(i%2)));
    }

    return sha(outer + sha(inner + msg));
   },
   used = 0,
   _ = function(x){return !used++ ? HMAC(MACKEY, x) : ''};
   return (function(x){if(typeof x=="string") return _(x)});
 }(),
 /*** END OF DEFENSIVE FUNCTION ***/
 d:document, w:window
})
{
 w.addEventListener('message', function(e){
  if(e.origin == O)
   e.source.postMessage(DJS(e.data), e.origin);
 });
 +function(){
  var f = d.createElement('iframe');
  f.src = O+'/bm';
  d.body.appendChild(f);
 }();
}

