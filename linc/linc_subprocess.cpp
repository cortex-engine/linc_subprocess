#include <hxcpp.h>

#include "./linc_filewatch.h"
#include <subprocess.h>

namespace linc {
    namespace subprocess {
        Dynamic run(::Array<::String> _cmdline) {
            // convert the input
            size_t size = _cmdline->size();
            char** command_line = new char*[size+1];
            for (size_t i = 0; i < size; ++i)
                command_line[i] = (char*)_cmdline->__get(i).c_str();
            command_line[size] = 0;

            // create the process with env and combined pipes
            struct subprocess_s process;
            subprocess_create(command_line, subprocess_option_inherit_environment | subprocess_option_combined_stdout_stderr, &process);

            int ret = -1;
            hx::EnterGCFreeZone();
            // wait for the process to complete
            subprocess_join(&process, &ret);
            hx::ExitGCFreeZone();
            
            FILE *stdout_file;
            stdout_file = subprocess_stdout(&process);
            FILE *stderr_file; // needed bc combined? in sp-tests they do this
            stderr_file = subprocess_stderr(&process);

            // collect output
            char buffer[256];
            std::string result;
            while(fgets(buffer, 256, stdout_file))
                result += std::string(buffer);
            
            // clean up
            subprocess_destroy(&process);            
            delete[] command_line;

            // dynamic to the rescue!
            hx::Anon o = hx::Anon_obj::Create();
            o->Add(HX_CSTRING("exitCode"), ret);
            o->Add(HX_CSTRING("output"), ::String(result.c_str()));
            return o;
        }
    }
}