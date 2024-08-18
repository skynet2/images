FetchContent_Declare(echo_nginx_module
        GIT_REPOSITORY https://github.com/openresty/echo-nginx-module.git
        GIT_TAG v0.63
        )

FetchContent_MakeAvailable(echo_nginx_module)

set(ECHO_MODULE_SOURCE ${echo_nginx_module_SOURCE_DIR} PARENT_SCOPE)
