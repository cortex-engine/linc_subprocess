#pragma once
    
#ifndef HXCPP_H
#include <hxcpp.h>
#endif
#include <subprocess.h>
#include <string>

namespace linc {
    namespace subprocess {       
        Dynamic run(::Array<::String> _cmdline);
    }
}
