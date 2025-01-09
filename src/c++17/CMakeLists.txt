FILE( GLOB CPPS [^.]*.cpp [^.]*.c)
FILE( GLOB HPPS [^.]*.hpp [^.]*.h [^.]*.inl)

# GLOBAL_ADD_INCLUDE( rtt/os ${HPPS} )
# GLOBAL_ADD_SRC( ${CPPS})

# 添加共享库
add_library(cpp17 SHARED
    # 列出所有.cpp文件
    ${CPPS}
    # 如果有更多文件，继续添加
)