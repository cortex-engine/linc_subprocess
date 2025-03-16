# linc_subprocess

Haxe/hxcpp&cppia @:native binding for https://github.com/sheredom/subprocess.h

```haxe
import subprocess.Subprocess;
// ...
final cmdline = ['ls', '-la'];
final result:{exitCode:Int, output:String} = Subprocess.run(cmdline);
trace(result.output);
```
---
This is a [linc](http://snowkit.github.io/linc/) library.
