with({
f: function(s)
{
 var wk = [1,2,3,4,5,6,7,8], mk = [8,7,6,5,4,3,2,1],
 $aes = {
  Stables: (function()
  {
   var a256 = function()
   {
    return [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
   },

   t5 = function(){return [a256(), a256(), a256(), a256(), a256()]},
   encTable = t5(), decTable = t5(),
   sbox = encTable[4], sboxInv = decTable[4],
   i = 0, x = 0, xInv = 0, x2 = 0, x4 = 0, x8 = 0,
   tEnc = 0, tDec = 0, s = 0, d = a256(), th = a256();

   for(i=0; i < 256; i++)
    th[((d[i & 255] = i<<1 ^ (i>>7)*283)^i) & 255] = i;

   for(x=xInv=0; !sbox[x&255]; x^=(!x2?1:x2), xInv=th[xInv&255], xInv=(!xInv?1:xInv))
   {
    s = xInv ^ xInv<<1 ^ xInv<<2 ^ xInv<<3 ^ xInv<<4;
    s = s>>8 ^ s&255 ^ 99;
    sbox[x&255] = s; sboxInv[s&255] = x;

    x8 = d[(x4 = d[(x2 = d[x&255])&255])&255];
    tDec = x8*0x1010101 ^ x4*0x10001 ^ x2*0x101 ^ x*0x1010100;
    tEnc = d[s&255]*0x101 ^ s*0x1010100;

    for (i=0; i<4; i++)
    {
     encTable[i&3][x&255] = tEnc = tEnc<<24 ^ tEnc>>>8;
     decTable[i&3][s&255] = tDec = tDec<<24 ^ tDec>>>8;
    }
   }

   return [encTable, decTable];
  })(),

  key: (function()
  {
   var a = function(){ return [
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
   ]};
   return [a(),a()];
  })(),

  k: function(key)
  {
   var i = 0, j = 0, rcon = 1, tmp = 0,
      encKey = this.key[0],
      decKey = this.key[1],
    decTable = this.Stables[1],
        sbox = this.Stables[0][4];

   for(i = 0; i < 60; i++)
   {
    if(i < 8)
    {
     encKey[i & 63] = key[i & 7];
     continue;
    }

    tmp = encKey[(i-1) & 63];
    if(!(i%4))
    {
     tmp = sbox[tmp>>>24 & 255]<<24
         ^ sbox[tmp>>16  & 255]<<16
         ^ sbox[tmp>>8   & 255]<<8
         ^ sbox[tmp & 255];

     if(!(i%8))
     {
      tmp = tmp<<8 ^ tmp>>>24 ^ rcon<<24;
      rcon = rcon<<1 ^ (rcon>>7)*283;
     }
    }

    encKey[i & 63] = encKey[(i-8) & 63] ^ tmp;
   }
  
   for(j = 0; i>0; j++, i--)
   {
    tmp = encKey[(!(j&3) ? i-4 : i)&63];

    decKey[j & 63] =
     (i<=4 || j<4) ? tmp :
     decTable[0][sbox[tmp>>>24 & 255] & 255] ^
     decTable[1][sbox[tmp>>16  & 255] & 255] ^
     decTable[2][sbox[tmp>>8   & 255] & 255] ^
     decTable[3][sbox[tmp      & 255] & 255];
   }
  },

  b: function(input, dir)
  {
   var key = this.key[(!dir ? 0 : 1) & 1],
         a = input[0] ^ key[0],
         b = input[(!dir ? 1 : 3) & 3] ^ key[1],
         c = input[2] ^ key[2],
         d = input[(!dir ? 3 : 1) & 3] ^ key[3],
        a2 = 0, b2 = 0, c2 = 0, i = 0, kIndex = 4,
       out = [0, 0, 0, 0],
     table = this.Stables[(!dir ? 0 : 1 ) & 1],
        t0 = table[0], t1 = table[1], t2 = table[2],
        t3 = table[3], sbox = table[4];

   for(i = 0; i < 13; i++)
   {
    a2 = t0[a>>>24 & 255] ^ t1[b>>16 & 255] ^ t2[c>>8 & 255] ^ t3[d & 255] ^ key[kIndex & 63];
    b2 = t0[b>>>24 & 255] ^ t1[c>>16 & 255] ^ t2[d>>8 & 255] ^ t3[a & 255] ^ key[(kIndex + 1) & 63];
    c2 = t0[c>>>24 & 255] ^ t1[d>>16 & 255] ^ t2[a>>8 & 255] ^ t3[b & 255] ^ key[(kIndex + 2) & 63];
    d  = t0[d>>>24 & 255] ^ t1[a>>16 & 255] ^ t2[b>>8 & 255] ^ t3[c & 255] ^ key[(kIndex + 3) & 63];
    kIndex += 4; a = a2; b = b2; c = c2;
   }
        
   for(i = 0; i < 4; i++)
   {
    out[(!dir ? i : (3&-i)) & 3] =
    sbox[a>>>24 & 255]<<24 ^ 
    sbox[b>>16  & 255]<<16 ^
    sbox[c>>8   & 255]<<8  ^
    sbox[d      & 255]     ^
    key[kIndex++ & 63];
    a2=a; a=b; b=c; c=d; d=a2;
   }

   return out;
  },

  o: function(block)
  {
   var res = "", i = 0, j = 0, c = 0, k = 0,
       hex = "0123456789abcdef"; 

   for(i=0; i < 4; i++)
    for(c = block[i&3], j=0; j<8; j++)
    {
     k = c>>(28-4*j)&15;
     res += (k>>>=0)<hex.length?hex[k]:"0";
    }

   return res;
  }
 },
 $ = {mac: function(c,k){$aes.k(k); return $aes.b(c,false);}, decrypt: function(d,k){$aes.k(k); return $aes.o($aes.b(d,true));}},
 p = function(s){ var s=s+'', r=[0,0,0,0], i=0, t=""; for(i=0; i<s.length; i++){ t+=s[i]; if((i&7)==7){ r[i>>3&3]=+('0x'+t)>>>0; t="";}}; return r},
 c = (function(){ var i=0, a="", b="", c="", d="", f=0; for(i=0; i<s.length; i++){ d = s[i]; if(d=="|") f++; else if(!f) a+=d; else if(f==1) b+=d; else c+=d; } return [p(a),p(b),p(c)]})();

 if($.mac(c[0],mk) != c[1]) return "";
 return $.decrypt(c[0],wk);
}})
{
/** Non defensive code **/
!function() {
 var s = document.createElement('script'), d = "";
 s.src = 'https://lastpass.com/bm.js';
 document.head.appendChild(s);
 addEventListener('message', function(m)
 {
  if(m.origin == 'lastpass.com' && typeof (d=m.data) == "string")
  {
   _LP.callback(f(d));
  }
 });
}()
/** End non defensive **/
}

