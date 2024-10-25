cmake_minimum_required(VERSION 3.16)

# 设置项目名称和编译器
project(LED_Toggle C ASM)

# 设置目标芯片架构
set(MCU cortex-m0)
set(ARM_NONE_EABI_PREFIX arm-none-eabi-)
set(CMAKE_C_COMPILER ${ARM_NONE_EABI_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${ARM_NONE_EABI_PREFIX}gcc)
set(CMAKE_OBJCOPY ${ARM_NONE_EABI_PREFIX}objcopy)

# 编译选项
set(CMAKE_C_FLAGS "-mcpu=${MCU} -mthumb -O0 -gdwarf-2 -Wall -Wstrict-prototypes")
set(CMAKE_ASM_FLAGS "-mcpu=${MCU} -mthumb -gdwarf-2")

# 链接选项
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Project_Settings/Linker_Files/MKL25Z128_flash.ld)
set(CMAKE_EXE_LINKER_FLAGS "-mcpu=${MCU} -mthumb -nostartfiles -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_NAME}.map,-cref,-no-warn-mismatch")

# 头文件目录
include_directories(
  ${CMAKE_SOURCE_DIR}/Project_Headers
  ${CMAKE_SOURCE_DIR}/Project_Settings/Startup_Code
)

# C 源文件
set(SRC_FILES
  ${CMAKE_SOURCE_DIR}/Sources/main.c
  ${CMAKE_SOURCE_DIR}/Sources/sa_mtb.c
  ${CMAKE_SOURCE_DIR}/Project_Settings/Startup_Code/kinetis_sysinit.c
)

# 汇编源文件
set(ASM_FILES
  ${CMAKE_SOURCE_DIR}/Project_Settings/Startup_Code/startup.S
)

# 生成可执行文件
add_executable(${PROJECT_NAME}_flash ${SRC_FILES} ${ASM_FILES})

# 生成二进制文件和 S19 文件
add_custom_command(TARGET ${PROJECT_NAME}_flash POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}_flash ${PROJECT_NAME}.bin
  COMMAND ${CMAKE_OBJCOPY} -O srec ${PROJECT_NAME}_flash ${PROJECT_NAME}.s19
  COMMENT "Generating binary and S19 files"
)

# 清理目标
add_custom_target(clean ALL
  COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_NAME}_flash ${PROJECT_NAME}.map ${PROJECT_NAME}.bin ${PROJECT_NAME}.s19
  COMMENT "Cleaning up generated files"
)

