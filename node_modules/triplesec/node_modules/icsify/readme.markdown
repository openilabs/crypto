# coffeeify

browserify v2 plugin for iced-coffee-script

mix and match `.coffee`, `iced`, and `.js` files in the same project

**important: when using require('path/to/file.iced') remember to use .iced extension**

[![build status](https://secure.travis-ci.org/substack/coffeeify.png)](http://travis-ci.org/maxtacp/icsify)

# example

given some files written in a mix of `js` `coffee`, and `iced`:

foo.coffee:

``` coffee
console.log(require './bar.js')
```

bar.js:

``` js
module.exports = require('./baz.iced')(5)
```

baz.iced:

``` js
module.exports = (n) -> n * 111
```

install coffeeify into your app:

```
$ npm install coffeeify
```

when you compile your app, just pass `-t icsify` to browserify:

```
$ browserify -t icsify foo.coffee > bundle.js
$ node bundle.js
555
```

# install

With [npm](https://npmjs.org) do:

```
npm install icsify
```

# license

MIT

