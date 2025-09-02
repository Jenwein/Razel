import os
import sys

def process_premake_file(filepath):
    """
    处理单个 premake5.lua 文件，根据规则修改 staticruntime 选项。
    """
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except Exception as e:
        print(f"错误: 无法读取文件 {filepath}: {e}")
        return

    new_lines = []
    modified_in_this_file = False
    
    # 状态变量，用于跟踪上下文
    in_project_scope = False  # 是否在 project "..." 之后，但在任何 filter 之前
    in_windows_filter = False # 是否在 filter "system:windows" 内部

    for line in lines:
        stripped_line = line.strip()

        # 更新当前上下文状态
        if stripped_line.startswith('project '):
            # 进入一个新的 project 会重置 filter 状态
            in_project_scope = True
            in_windows_filter = False
        elif stripped_line.startswith('filter '):
            # 进入 filter 会离开 project 的直接作用域
            in_project_scope = False
            if stripped_line == 'filter "system:windows"':
                in_windows_filter = True
            else:
                # 如果是其他 filter，则重置 windows filter 状态
                in_windows_filter = False

        # 检查是否需要修改当前行
        if 'staticruntime' in stripped_line and not modified_in_this_file:
            should_modify = False
            # 规则1: 在 project 之后，且不在任何 filter 之内
            if in_project_scope:
                should_modify = True
            # 规则2: 在 "system:windows" filter 之内
            elif in_windows_filter:
                should_modify = True

            if should_modify:
                new_line = None
                if 'staticruntime "on"' in line:
                    new_line = line.replace('staticruntime "on"', 'staticruntime "off"')
                    print(f"文件 [{filepath}] 中找到 'staticruntime \"on\"' -> 修改为 'off'")
                elif 'staticruntime "off"' in line:
                    new_line = line.replace('staticruntime "off"', 'staticruntime "on"')
                    print(f"文件 [{filepath}] 中找到 'staticruntime \"off\"' -> 修改为 'on'")
                
                if new_line:
                    new_lines.append(new_line)
                    modified_in_this_file = True # 标记此文件已修改，跳过后续可能的匹配
                else:
                    new_lines.append(line) # 未能匹配 on/off，保留原行
            else:
                new_lines.append(line) # 不满足修改条件，保留原行
        else:
            new_lines.append(line) # 其他无关行，直接添加

    # 如果文件内容被修改了，则写回文件
    if modified_in_this_file:
        try:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.writelines(new_lines)
            print(f"成功: 文件 {filepath} 已更新。")
        except Exception as e:
            print(f"错误: 无法写入文件 {filepath}: {e}")
    # else:
    #     print(f"信息: 文件 {filepath} 无需修改。")


def main():
    """
    主函数，遍历目录并启动文件处理。
    """
    # 目标目录，'..' 表示上一级目录
    target_dir = os.path.join('..', 'Razel', 'vendor')

    # 检查目标目录是否存在
    if not os.path.isdir(target_dir):
        print(f"错误: 目录 '{target_dir}' 不存在。请确保脚本相对于正确的位置运行。")
        sys.exit(1)

    print(f"开始扫描目录: {os.path.abspath(target_dir)}")

    # os.walk 会递归遍历所有子目录
    for subdir, _, files in os.walk(target_dir):
        for filename in files:
            if filename == 'premake5.lua':
                filepath = os.path.join(subdir, filename)
                process_premake_file(filepath)
    
    print("\n所有 premake5.lua 文件处理完毕。")

if __name__ == '__main__':
    main()