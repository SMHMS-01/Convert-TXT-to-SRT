def process_srt_file(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    processed_lines = []
    skip_line = False
    for line in lines:
        if skip_line:
            skip_line = False
            continue

        if '<br>' in line:
            # 删除'<br>'及其后面的内容
            line = line.split('<br>')[0] + '\n'
        processed_lines.append(line)

    with open(output_file, 'w', encoding='utf-8') as f:
        f.writelines(processed_lines)
    print(f"{output_file} already converted.")


# 用法示例
# 输入SRT文件路径
filename = "齐泽克：天下大乱 北京大学吴晓宇对话齐泽克.srt"
input_file = f"[ENG&ZH]{filename}"
# 输出SRT文件路径
output_file = f"[ZH]{filename}"

process_srt_file(input_file, output_file)
