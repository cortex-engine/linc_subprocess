package subprocess;

import haxe.io.Path;

@:keep
@:include('linc_subprocess.h')
#if !display
@:build(linc.Linc.touch())
@:build(linc.Linc.xml('subprocess'))
#end
extern class Native_Subprocess {
    @:native('linc::subprocess::run')
    public static function run(_cmdline:Array<String>):Dynamic;
}

#if (scriptable || cppia)
    class Subprocess {
        public static function run(_cmdline:Array<String>):Dynamic {
            return Native_Subprocess.run(_cmdline);
        }
    }
#else
    typedef Subprocess = Native_Subprocess;
#end
