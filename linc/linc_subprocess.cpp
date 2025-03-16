#include <hxcpp.h>

#include "./linc_filewatch.h"
#include <subprocess.h>

namespace linc {
    namespace subprocess {
        Dynamic run(::Array<::String> _cmdline) {
            struct subprocess_s process;
            int ret = -1;
            FILE *stdout_file;
            FILE *stderr_file;
            char buffer[256];
            std::string result;
            size_t size = _cmdline->size();
            char** command_line = new char*[size+1];

            for (size_t i = 0; i < size; ++i)
                command_line[i] = (char*)_cmdline->__get(i).c_str();
            command_line[size] = 0;

            subprocess_create(command_line, subprocess_option_inherit_environment | subprocess_option_combined_stdout_stderr, &process);

            hx::EnterGCFreeZone();
            subprocess_join(&process, &ret);
            hx::ExitGCFreeZone();
            
            stdout_file = subprocess_stdout(&process);
            stderr_file = subprocess_stderr(&process);

            while(fgets(buffer, 256, stdout_file))
                result += std::string(buffer);
            
            subprocess_destroy(&process);
            
            delete[] command_line;

            hx::Anon o = hx::Anon_obj::Create();
            o->Add(HX_CSTRING("exitCode"), ret);
            o->Add(HX_CSTRING("output"), ::String(result.c_str()));

            return o;
        }
    }
}