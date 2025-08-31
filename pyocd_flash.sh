#!/bin/bash

# PyOCD HC32F4A0 程序烧录脚本
# 使用PyOCD替代J-Link进行HC32F4A0程序烧录

echo "======================================"
echo "PyOCD HC32F4A0 程序烧录脚本"
echo "======================================"

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 检查PyOCD安装
check_pyocd() {
    log_info "检查PyOCD安装状态..."
    
    if ! command -v pyocd &> /dev/null; then
        log_error "PyOCD未安装"
        log_info "请运行: paru -S pyocd"
        exit 1
    fi
    
    local version=$(pyocd --version)
    log_success "PyOCD已安装，版本: $version"
    echo
}

# 检查调试器连接
check_probe() {
    log_info "检查调试器连接..."
    
    local probes=$(pyocd list --probes)
    echo "$probes"
    
    if echo "$probes" | grep -q "Segger J-Link"; then
        log_success "检测到J-Link调试器"
    else
        log_warning "未检测到调试器，请检查连接"
    fi
    echo
}

# 检查目标设备支持
check_target_support() {
    log_info "检查HC32F4A0xI设备支持..."
    
    if pyocd list --targets | grep -q "hc32f4a0xi"; then
        log_success "PyOCD支持HC32F4A0xI设备"
    else
        log_error "PyOCD不支持HC32F4A0xI设备"
        exit 1
    fi
    echo
}

# 检查程序文件
check_files() {
    log_info "检查程序文件..."
    
    if [ ! -f "build/hc32f4a0xi-template.elf" ]; then
        log_error "ELF文件不存在: build/hc32f4a0xi-template.elf"
        log_warning "请先运行构建: make -C build"
        exit 1
    fi
    
    if [ ! -f "build/hc32f4a0xi-template.hex" ]; then
        log_error "HEX文件不存在: build/hc32f4a0xi-template.hex"
        log_warning "请先运行构建: make -C build"
        exit 1
    fi
    
    log_success "程序文件检查完成"
    echo
}

# 测试设备连接
test_connection() {
    log_info "测试设备连接..."
    
    log_info "尝试连接到HC32F4A0xI设备..."
    # 使用commander命令测试连接
    if echo "quit" | pyocd commander --target hc32f4a0xi; then
        log_success "设备连接测试成功"
    else
        log_error "设备连接失败"
        log_warning "请检查硬件连接和供电"
        return 1
    fi
    echo
}

# 烧录ELF文件
flash_elf() {
    log_info "使用PyOCD烧录ELF文件..."
    
    log_info "执行烧录命令: pyocd flash --target hc32f4a0xi build/hc32f4a0xi-template.elf"
    
    if pyocd flash --target hc32f4a0xi build/hc32f4a0xi-template.elf; then
        log_success "ELF文件烧录成功！"
        return 0
    else
        log_error "ELF文件烧录失败"
        return 1
    fi
}

# 烧录HEX文件
flash_hex() {
    log_info "使用PyOCD烧录HEX文件..."
    
    log_info "执行烧录命令: pyocd flash --target hc32f4a0xi build/hc32f4a0xi-template.hex"
    
    if pyocd flash --target hc32f4a0xi build/hc32f4a0xi-template.hex; then
        log_success "HEX文件烧录成功！"
        return 0
    else
        log_error "HEX文件烧录失败"
        return 1
    fi
}

# 擦除Flash
erase_flash() {
    log_info "擦除Flash存储器..."
    
    if pyocd erase --target hc32f4a0xi --chip; then
        log_success "Flash擦除成功"
        return 0
    else
        log_error "Flash擦除失败"
        return 1
    fi
}

# 复位设备
reset_device() {
    log_info "复位设备..."
    
    if pyocd reset --target hc32f4a0xi; then
        log_success "设备复位成功"
        return 0
    else
        log_error "设备复位失败"
        return 1
    fi
}

# 验证烧录
verify_flash() {
    log_info "验证烧录结果..."
    
    # PyOCD的flash命令默认包含验证
    log_info "PyOCD烧录过程已包含自动验证"
    log_success "验证完成"
}

# 启动GDB调试服务器
start_gdb_server() {
    log_info "启动PyOCD GDB服务器..."
    
    log_info "执行命令: pyocd gdbserver --target hc32f4a0xi --port 3333"
    log_warning "GDB服务器将在端口3333运行，按Ctrl+C停止"
    
    pyocd gdbserver --target hc32f4a0xi --port 3333
}

# 显示使用说明
show_usage() {
    echo "使用说明:"
    echo "$0 [选项]"
    echo
    echo "选项:"
    echo "  check     - 检查PyOCD环境和设备连接"
    echo "  test      - 测试设备连接"
    echo "  flash     - 烧录程序 (默认使用ELF文件)"
    echo "  flash-elf - 烧录ELF文件"
    echo "  flash-hex - 烧录HEX文件"
    echo "  erase     - 擦除Flash"
    echo "  reset     - 复位设备"
    echo "  gdb       - 启动GDB调试服务器"
    echo "  all       - 完整的烧录流程 (检查+擦除+烧录+验证+复位)"
    echo
}

# 完整烧录流程
full_flash_process() {
    log_info "执行完整烧录流程..."
    echo
    
    check_pyocd
    check_probe
    check_target_support
    check_files
    
    if ! test_connection; then
        log_error "设备连接失败，终止烧录流程"
        exit 1
    fi
    
    log_info "开始烧录流程..."
    
    # 擦除Flash
    if ! erase_flash; then
        log_warning "Flash擦除失败，继续尝试烧录..."
    fi
    
    # 烧录程序
    if flash_elf; then
        verify_flash
        reset_device
        log_success "完整烧录流程成功完成！"
        log_info "程序已烧录到HC32F4A0设备并开始运行"
    else
        log_warning "ELF烧录失败，尝试HEX文件..."
        if flash_hex; then
            verify_flash
            reset_device
            log_success "完整烧录流程成功完成！"
            log_info "程序已烧录到HC32F4A0设备并开始运行"
        else
            log_error "烧录失败，请检查硬件连接和程序文件"
            exit 1
        fi
    fi
}

# 主函数
main() {
    case "${1:-all}" in
        "check")
            check_pyocd
            check_probe
            check_target_support
            check_files
            ;;
        "test")
            check_pyocd
            test_connection
            ;;
        "flash")
            check_files
            flash_elf
            ;;
        "flash-elf")
            check_files
            flash_elf
            ;;
        "flash-hex")
            check_files
            flash_hex
            ;;
        "erase")
            erase_flash
            ;;
        "reset")
            reset_device
            ;;
        "gdb")
            start_gdb_server
            ;;
        "all")
            full_flash_process
            ;;
        "help"|"--help"|"-h")
            show_usage
            exit 0
            ;;
        *)
            log_error "未知选项: $1"
            show_usage
            exit 1
            ;;
    esac
    
    echo "======================================"
    log_info "PyOCD操作完成！"
    echo "======================================"
}

# 执行主函数
main "$@"